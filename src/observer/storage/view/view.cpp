#include "view.h"
#include "sql/expr/expression.h"
#include "common/log/log.h"

View::~View() 
{
    if (db_!=nullptr) {
        delete db_;
        db_=nullptr;
    }
    if (name_!="") {
        name_="";
    }
    if (select_stmt_!=nullptr) {
        delete select_stmt_;
        select_stmt_=nullptr;
    }
    for (auto t:tables_) {
        delete t;
    }
    if (nullptr != dumy_table_)
        delete dumy_table_;
    tables_.clear();
}

RC View::create(Db *db, string name, SelectStmt *select_stmt,std::vector<std::string> &infos,bool has_schema,SelectSqlNode *select_node)
{
    has_schema_=has_schema;
    if (name=="") {
        LOG_WARN("Name cannot be empty");
        return RC::INVALID_ARGUMENT;
    }
    db_=db;
    name_=name;
    select_stmt_=select_stmt;
    select_node_=select_node;
    infos_.assign(infos.begin(),infos.end());
    std::vector<Table*> select_tables=select_stmt->tables();
    tables_.assign(select_tables.begin(),select_tables.end());
    int table_size=select_tables.size();
    
    if (table_size==1) is_one_table=true;
    std::vector<std::unique_ptr<Expression>> &exprs=select_stmt->query_expressions();
    if (exprs.empty()) {
      LOG_WARN("no fields selected, view=%s",name_);
      return RC::INVALID_ARGUMENT;
    }
    int expr_size=exprs.size();
    
    for (int i=0;i<expr_size;i++) {
        if (exprs[i]->type()==ExprType::STAR) {
            if (has_schema) {
                
                size_t name_i=0;
                for (int j=0;j<table_size;j++) {
                    std::vector<FieldMeta> fmetas=*tables_[j]->table_meta().field_metas();
                    fieldmetas_.push_back(fmetas);
                    for (size_t k=0;k<fmetas.size();k++) {
                        string name=infos[name_i];
                        name_to_meta.insert({name,&fmetas[k]});
                        name_i++;
                    } 
                }
            }
            else {
                size_t name_i=0;
                for (int j=0;j<table_size;j++) {
                    std::vector<FieldMeta> fmetas=*tables_[j]->table_meta().field_metas();
                    fieldmetas_.push_back(fmetas);
                    for (size_t k=0;k<fmetas.size();k++) {
                        string name=infos[name_i];
                        name_to_meta.insert({name,&fmetas[k]});
                        name_i++;
                    }
                }
            }
            
        }
        else if (exprs[i]->type()==ExprType::FIELD) {
            has_schema_=has_schema;
            FieldExpr* expr=dynamic_cast<FieldExpr*>(exprs[i].get());
            Field& expr_field=expr->field();
            auto meta = expr->field().meta();
            name_to_meta.insert({infos[i],meta});
            for (int j=0;j<table_size;j++) { 
                std::vector<FieldMeta> fs;
                fieldmetas_.push_back(fs);
                if (strcmp(expr_field.table_name(),tables_[j]->name())==0) {
                    fieldmetas_[j].push_back(*expr_field.meta());
                }
            }
        }
        else return RC::INVALID_ARGUMENT;
    }
    for (int i=0;i<table_size;i++) {
        std::vector<FieldMeta> fmetas=*tables_[i]->table_meta().field_metas();
        std::vector<bool> ni;
        null_info_.push_back(ni);
        for (int j=0;j<fmetas.size();j++) {
            bool ij=false;
            for (int k=0;k<fieldmetas_[i].size();k++) {
                if (strcmp(fieldmetas_[i][k].name(),fmetas[j].name())==0) ij=true;
            }
            null_info_[i].push_back(ij);
        }
    }
    std::vector<const FieldMeta*> metas;
    for (auto info : infos) {
      auto meta = name_to_meta.find(info)->second;
      metas.emplace_back(meta);
    }
    dumy_table_ = new Table;
    dumy_table_->init_meta(metas, infos);
    return RC::SUCCESS;
}