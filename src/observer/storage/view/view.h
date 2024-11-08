#pragma once

#include "storage/db/db.h"
#include "sql/stmt/select_stmt.h"
#include "common/rc.h"
/**
 * @brief 视图
 *
 */
class Db;
class View
{
public:
    View()=default;
    ~View();
   /**
   * 创建一个视图
   * @param name 视图名
   * @param select_stmt 包含的select语句
   */
    RC create(Db *db,string name,SelectStmt *select_stmt);
    SelectStmt *get_select() {return select_stmt_;};
    string name(){return name_;};
private:
    Db *db_=nullptr;
    SelectStmt *select_stmt_=nullptr;
    string name_;
};