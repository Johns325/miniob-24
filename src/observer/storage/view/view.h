#pragma once

#include "storage/db/db.h"
#include "sql/stmt/select_stmt.h"
#include "common/rc.h"
#include "storage/table/table.h"
#include "storage/field/field_meta.h"
#include "storage/field/field.h"
/**
 * @brief 视图
 *
 */
class Db;
class Table;
class FieldMeta;
class View
{
public:
    friend class Stmt;
    View()=default;
    ~View();
   /**
   * 创建一个视图
   * @param name 视图名
   * @param select_stmt 包含的select语句
   */
    RC create(Db *db,string name,SelectStmt *select_stmt,std::vector<std::string> &infos,bool has_schema);
    SelectStmt *get_select() {return select_stmt_;};
    string name(){return name_;};
    std::vector<Table*> &get_tables() {return tables_;}
    bool onetable() {return is_one_table;}
    bool get_null_info(int i,int j) {return null_info_[i][j];}
    bool has_schema() {return has_schema_;}
private:
    Db *db_=nullptr;
    SelectStmt *select_stmt_=nullptr;
    string name_;
    std::vector<Table*> tables_;
    bool is_one_table=false;
    bool has_schema_=false;
    std::vector<std::vector<FieldMeta>> fieldmetas_;
    std::vector<std::vector<bool>> null_info_;
public:  
    Table * dumy_table_ {nullptr};
    std::unordered_map<std::string,const FieldMeta *> name_to_meta;
    std::vector<std::string> infos_;
};