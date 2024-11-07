#include "view.h"

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
}

RC View::create(Db *db, string name, SelectStmt *select_stmt)
{
    if (name=="") {
        LOG_WARN("Name cannot be empty");
        return RC::INVALID_ARGUMENT;
    }
    db_=db;
    name_=name;
    select_stmt_=select_stmt;
    return RC::SUCCESS;
}