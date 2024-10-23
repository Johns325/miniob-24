
%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/yacc_sql.hpp"
#include "sql/parser/lex_sql.h"
#include "sql/expr/expression.h"

using namespace std;

string token_name(const char *sql_string, YYLTYPE *llocp)
{
  return string(sql_string + llocp->first_column, llocp->last_column - llocp->first_column + 1);
}

int yyerror(YYLTYPE *llocp, const char *sql_string, ParsedSqlResult *sql_result, yyscan_t scanner, const char *msg)
{
  std::unique_ptr<ParsedSqlNode> error_sql_node = std::make_unique<ParsedSqlNode>(SCF_ERROR);
  error_sql_node->error.error_msg = msg;
  error_sql_node->error.line = llocp->first_line;
  error_sql_node->error.column = llocp->first_column;
  sql_result->add_sql_node(std::move(error_sql_node));
  return 0;
}

ArithmeticExpr *create_arithmetic_expression(ArithmeticExpr::Type type,
                                             Expression *left,
                                             Expression *right,
                                             const char *sql_string,
                                             YYLTYPE *llocp)
{
  ArithmeticExpr *expr = new ArithmeticExpr(type, left, right);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

UnboundAggregateExpr *create_aggregate_expression(const char *aggregate_name,
                                           Expression *child,
                                           const char *sql_string,
                                           YYLTYPE *llocp)
{
  UnboundAggregateExpr *expr = new UnboundAggregateExpr(aggregate_name, child);
  expr->set_name(token_name(sql_string, llocp));
  return expr;
}

%}

%define api.pure full
%define parse.error verbose
/** 启用位置标识 **/
%locations
%lex-param { yyscan_t scanner }
/** 这些定义了在yyparse函数中的参数 **/
%parse-param { const char * sql_string }
%parse-param { ParsedSqlResult * sql_result }
%parse-param { void * scanner }

//标识tokens
%token  SEMICOLON
        BY
        CREATE
        DROP
        GROUP
        TABLE
        TABLES
        INDEX
        CALC
        null
        SELECT
        ALIAS
        ASC
        ORDER
        DESC
        SHOW
        SYNC
        INSERT
        DELETE
        UPDATE
        UNIQUE
        LBRACE
        RBRACE
        COMMA
        INNER
        JOIN
        TRX_BEGIN
        TRX_COMMIT
        TRX_ROLLBACK
        INT_T
        STRING_T
        FLOAT_T
        DATE_T
        LIKE
        NOT
        VECTOR_T
        HELP
        EXIT
        DOT //QUOTE
        INTO
        VALUES
        FROM
        WHERE
        AND
        SET
        ON
        LOAD
        DATA
        INFILE
        EXPLAIN
        STORAGE
        FORMAT
        EQ
        LT
        GT
        LE
        GE
        NE
        L2_DISTANCE
        INNER_PRODUCT
        COSINE_DISTANCE


/** union 中定义各种数据类型，真实生成的代码也是union类型，所以不能有非POD类型的数据 **/
%union {
  ParsedSqlNode *                            sql_node;
  Expression *                          condition;
  Value *                                    value;
  enum CompOp                                comp;
  RelAttrSqlNode *                           rel_attr;
  std::vector<AttrInfoSqlNode> *             attr_infos;
  AttrInfoSqlNode *                          attr_info;
  Expression *                               expression;
  std::vector<std::unique_ptr<Expression>> * expression_list;
  std::vector<Value> *                       value_list;
  std::vector<Expression*> *                 condition_list;
  std::vector<RelAttrSqlNode> *              rel_attr_list;
  std::vector<std::string> *                 relation_list;
  char *                                     string;
  int                                        number;
  float                                      floats;
  bool                                       boolean;
  bool *                                     boolean_ptr;
  std::vector<float> *                       vector;
  std::vector<order_by>*                     order_by_type;
  std::vector<rel_info>*                     rel_list_type;             
}

%token <number> NUMBER
%token <floats> FLOAT
%token <string> ID
%token <string> SSS
%token <vector> VECTOR_DATA
//非终结符

/** type 定义了各种解析后的结果输出的是什么类型。类型对应了 union 中的定义的成员变量名称 **/
%type <number>              type
%type <condition>           condition
%type <value>               value
%type <value>               insert_val
%type <number>              number
%type <number>              null_def
%type <string>              relation
%type <comp>                comp_op
%type <rel_attr>            rel_attr
%type <attr_infos>          attr_def_list
%type <attr_info>           attr_def
%type <value_list>          value_list
%type <condition_list>      where
%type <condition_list>      condition_list
%type <string>              storage_format
// %type <relation_list>       rel_list
%type <rel_list_type>       rel_list
%type <expression>          expression
%type <expression>          aggr_func_expr
%type <expression_list>     expression_list
%type <expression_list>     group_by
%type <boolean_ptr>         asc_stmt
%type <condition_list>      on_stmt
%type <expression_list>     rel_attrs
%type <sql_node>            calc_stmt
%type <relation_list>       attr_list
%type <sql_node>            select_stmt
%type <sql_node>            insert_stmt
%type <sql_node>            update_stmt
%type <sql_node>            delete_stmt
%type <sql_node>            create_table_stmt
%type <sql_node>            drop_table_stmt
%type <sql_node>            show_tables_stmt
%type <sql_node>            desc_table_stmt
%type <sql_node>            create_index_stmt
%type <boolean>             unique_stmt
%type <string>              alias_stmt
%type <order_by_type>       order_by_seq
%type <order_by_type>       order_by
%type <sql_node>            drop_index_stmt
%type <sql_node>            sync_stmt
%type <sql_node>            begin_stmt
%type <sql_node>            commit_stmt
%type <sql_node>            rollback_stmt
%type <sql_node>            load_data_stmt
%type <sql_node>            explain_stmt
%type <sql_node>            set_variable_stmt
%type <sql_node>            help_stmt
%type <sql_node>            exit_stmt
%type <sql_node>            command_wrapper
// commands should be a list but I use a single command instead
%type <sql_node>            commands

%left '+' '-'
%left '*' '/'
%nonassoc UMINUS
%%

commands: command_wrapper opt_semicolon  //commands or sqls. parser starts here.
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>($1);
    sql_result->add_sql_node(std::move(sql_node));
  }
  ;

command_wrapper:
    calc_stmt
  | select_stmt
  | insert_stmt
  | update_stmt
  | delete_stmt
  | create_table_stmt
  | drop_table_stmt
  | show_tables_stmt
  | desc_table_stmt
  | create_index_stmt
  | drop_index_stmt
  | sync_stmt
  | begin_stmt
  | commit_stmt
  | rollback_stmt
  | load_data_stmt
  | explain_stmt
  | set_variable_stmt
  | help_stmt
  | exit_stmt
    ;

exit_stmt:      
    EXIT {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      $$ = new ParsedSqlNode(SCF_EXIT);
    };

help_stmt:
    HELP {
      $$ = new ParsedSqlNode(SCF_HELP);
    };

sync_stmt:
    SYNC {
      $$ = new ParsedSqlNode(SCF_SYNC);
    }
    ;
alias_stmt:
  /* empty */
  {
    $$ = nullptr;
  }
  | ALIAS ID {
    $$ = $2;
  }
  ;
begin_stmt:
    TRX_BEGIN  {
      $$ = new ParsedSqlNode(SCF_BEGIN);
    }
    ;

commit_stmt:
    TRX_COMMIT {
      $$ = new ParsedSqlNode(SCF_COMMIT);
    }
    ;

rollback_stmt:
    TRX_ROLLBACK  {
      $$ = new ParsedSqlNode(SCF_ROLLBACK);
    }
    ;

drop_table_stmt:    /*drop table 语句的语法解析树*/
    DROP TABLE ID {
      $$ = new ParsedSqlNode(SCF_DROP_TABLE);
      $$->drop_table.relation_name = $3;
      free($3);
    };

show_tables_stmt:
    SHOW TABLES {
      $$ = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
    ;

desc_table_stmt:
    DESC ID  {
      $$ = new ParsedSqlNode(SCF_DESC_TABLE);
      $$->desc_table.relation_name = $2;
      free($2);
    }
    ;

create_index_stmt:    /*create index 语句的语法解析树*/
    CREATE unique_stmt INDEX ID ON ID LBRACE ID attr_list RBRACE
    {
      $$ = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = $$->create_index;
      create_index.index_name = $4;
      create_index.unique = $2;
      create_index.relation_name = $6;
      if ($9 != nullptr) {
        create_index.attribute_names.swap(*$9);
        delete $9;  
      }
      create_index.attribute_names.emplace_back($8);
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      free($4);
      free($6);
      free($8);
    }
    ;
unique_stmt:
  /* empty */
  {
    $$ = false;
  }
  | UNIQUE {
    $$ = true;
  }
attr_list:
  /* empty */
  {
    $$ = nullptr;
  }
  | COMMA ID attr_list {
    if ($3 != nullptr) {
      $$ = $3;
    } else {
      $$ = new vector<std::string>;
    }
    $$->emplace_back($2);
    free($2);
  }

drop_index_stmt:      /*drop index 语句的语法解析树*/
    DROP INDEX ID ON ID
    {
      $$ = new ParsedSqlNode(SCF_DROP_INDEX);
      $$->drop_index.index_name = $3;
      $$->drop_index.relation_name = $5;
      free($3);
      free($5);
    }
    ;
create_table_stmt:    /*create table 语句的语法解析树*/
    CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format
    {
      $$ = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = $$->create_table;
      create_table.relation_name = $3;
      free($3);

      std::vector<AttrInfoSqlNode> *src_attrs = $6;

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*$5);
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete $5;
      if ($8 != nullptr) {
        create_table.storage_format = $8;
        free($8);
      }
    }
    ;
attr_def_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA attr_def attr_def_list
    {
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<AttrInfoSqlNode>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
    
attr_def:
    ID type LBRACE number RBRACE null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      if ($$->type == AttrType::VECTORS) {  // 检查类型是否为 vector_type
          $$->length = 4 * $4;
      } else {
          $$->length = $4;
      }
      free($1);
      $$->nullable = ($6 == 1);
    }
    | ID type null_def
    {
      $$ = new AttrInfoSqlNode;
      $$->type = (AttrType)$2;
      $$->name = $1;
      $$->length = 4;
      free($1);
      $$->nullable = ($3 == 1);
    }
    ;
null_def: // 0 stands not null and 1 stands for nullable
  /* empty */
  {
    $$ = 0;
  }
  | null {
    $$ = 1;
  }
  | NOT null {
    $$ = 1;
  }
number:
    NUMBER {$$ = $1;}
    ;
type:
    INT_T      { $$ = static_cast<int>(AttrType::INTS); }
    | STRING_T { $$ = static_cast<int>(AttrType::CHARS); }
    | FLOAT_T  { $$ = static_cast<int>(AttrType::FLOATS); }
    | DATE_T   { $$ = static_cast<int>(AttrType::DATES); }
    | VECTOR_T { $$ = static_cast<int>(AttrType::VECTORS); }
    ;
insert_stmt:        /*insert   语句的语法解析树*/
    INSERT INTO ID VALUES LBRACE insert_val value_list RBRACE 
    {
      $$ = new ParsedSqlNode(SCF_INSERT);
      $$->insertion.relation_name = $3;
      if ($7 != nullptr) {
        $$->insertion.values.swap(*$7);
        delete $7;
      }
      $$->insertion.values.emplace_back(*$6);
      std::reverse($$->insertion.values.begin(), $$->insertion.values.end());
      delete $6;
      free($3);
    }
    ;



value_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | COMMA insert_val value_list  { 
      if ($3 != nullptr) {
        $$ = $3;
      } else {
        $$ = new std::vector<Value>;
      }
      $$->emplace_back(*$2);
      delete $2;
    }
    ;
insert_val:
  value  {
    $$ = $1;
  }
  | '-' value {
    $$ = $2;
    if ($$->attr_type() == AttrType::INTS) {
      $$->set_int($$->get_int() *(-1));
    } else if ($$->attr_type() == AttrType::FLOATS) {
      $$->set_float($$->get_float() *(-1));
    }
  }
  ;
value:
    NUMBER {
      $$ = new Value((int)$1);
      @$ = @1;
    }
    |FLOAT {
      $$ = new Value((float)$1);
      @$ = @1;
    }
    |SSS {
      char *tmp = common::substr($1,1,strlen($1)-2);
      $$ = new Value(tmp);
      free(tmp);
      free($1);
    }
    | VECTOR_DATA {
      // 这里我们已经在词法分析阶段解析并获得了 std::vector<float> 指针
      Value *value = new Value();

      // 设置 vector 数据，假设 $1 是 std::vector<float> 指针
      if ($1 != nullptr) {
          // 获取底层的 float* 数组指针以及元素个数
          float* vector_data = $1->data();      // 获取底层的 float* 指针
          size_t vector_size = $1->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          value->set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete $1;
      } else {
          // yyerror(&@$, NULL, sql_result, scanner, "vector data invalid", SCF_VECTOR);
          YYABORT;  // 停止解析
      }

      $$ = value;  // 将结果赋值给解析树
    };
storage_format:
    /* empty */
    {
      $$ = nullptr;
    }
    | STORAGE FORMAT EQ ID
    {
      $$ = $4;
    }
    ;
    
delete_stmt:    /*  delete 语句的语法解析树*/
    DELETE FROM ID where 
    {
      $$ = new ParsedSqlNode(SCF_DELETE);
      $$->deletion.relation_name = $3;
      if ($4 != nullptr) {
        $$->deletion.conditions = $4;
      }
      free($3);
    }
    ;
update_stmt:      /*  update 语句的语法解析树*/
    UPDATE ID SET ID EQ value where 
    {
      $$ = new ParsedSqlNode(SCF_UPDATE);
      $$->update.relation_name = $2;
      $$->update.attribute_name = $4;
      $$->update.value = *$6;
      // TODO 
      if ($7 != nullptr) {
        $$->update.conditions= $7;
      }
      free($2);
      free($4);
    }
    ;
select_stmt:        /*  select 语句的语法解析树*/
    SELECT expression_list FROM relation alias_stmt rel_list where group_by order_by
    {
      $$ = new ParsedSqlNode(SCF_SELECT);
      auto &selection = $$->selection;
      // select
      if ($2 != nullptr) {
        selection.expressions.swap(*$2);
        delete $2;
      }
      // from
      
      rel_info r;
      r.relation_name = $4;
      if ($5) {
        r.relation_alias = $5;
        free($5);
      }
      selection.relations.emplace_back(std::move(r));
      if ($6 != nullptr) {
        for(size_t i = 0; i < $6->size();++i) {
          
          selection.relations.emplace_back(std::move((*$6)[i]));
        }
        printf("size:%ld.%s\n",selection.relations.size(),selection.relations[0].relation_name.c_str());
      }
      free($4);
      
      // where 
      if ($7 != nullptr) {
        selection.conditions = $7;
      }
    
      if ($8 != nullptr) {
        selection.group_by = $8;
      }
    }
    ;
calc_stmt:
    CALC expression_list
    {
      $$ = new ParsedSqlNode(SCF_CALC);
      $$->calc.expressions.swap(*$2);
      delete $2;
    }
    ;

expression_list:
    expression alias_stmt
    {
      $$ = new std::vector<std::unique_ptr<Expression>>;
      if ($2) {
        $1->set_alias(std::string($2));
        free($2);
      }
      $$->emplace_back($1);
    }
    | expression alias_stmt COMMA expression_list
    {
      if ($4 != nullptr) {
        $$ = $4;
      } else {
        $$ = new std::vector<std::unique_ptr<Expression>>;
      }
      if ($2) {
        $1->set_alias(std::string($2));
        free($2);
      }
      $$->emplace($$->begin(), $1);
    }
    ;
expression:
    value {
      cout << "value_expr\n";
      $$ = new ValueExpr(*$1);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | rel_attr {
      cout << "field_expr\n";
      RelAttrSqlNode *node = $1;
      $$ = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      $$->set_name(token_name(sql_string, &@$));
      delete $1;
    }
    | '*' {
      $$ = new StarExpr();
    }
    | expression '+' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::ADD, $1, $3, sql_string, &@$);
    }
    | expression '-' expression {
      cout << "minus\n";
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::SUB, $1, $3, sql_string, &@$);
    }
    | expression '*' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::MUL, $1, $3, sql_string, &@$);
    }
    | expression '/' expression {
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::DIV, $1, $3, sql_string, &@$);
    }
    | LBRACE expression RBRACE {
      $$ = $2;
      $$->set_name(token_name(sql_string, &@$));
    }
    | '-' expression %prec UMINUS {
      cout << "negative\n";
      $$ = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, $2, nullptr, sql_string, &@$);
    }
    
    | aggr_func_expr {
      $$ = $1;
    }
    | L2_DISTANCE LBRACE expression COMMA expression RBRACE {
        $$ = create_arithmetic_expression(ArithmeticExpr::Type::L2_DISTANCE, $3, $5, sql_string, &@$);
    }
    | INNER_PRODUCT LBRACE expression COMMA expression RBRACE {
        $$ = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, $3, $5, sql_string, &@$);
    }
    | COSINE_DISTANCE LBRACE expression COMMA expression RBRACE {
        $$ = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_DISTANCE, $3, $5, sql_string, &@$);
    }
    // your code here
    // | aggr_func_expr {
    //   $$ = $1;
    // }
    ;

// rules related to aggregation function
aggr_func_expr:
  ID LBRACE expression RBRACE {
    $$ = create_aggregate_expression($1, $3, sql_string, &@$);
    free($1);
  }
  | ID LBRACE RBRACE {
    free($1);
    YYERROR;
  }
  | ID LBRACE expression_list RBRACE {
    delete $3;
    free($1);
    YYERROR;
  }
  ;

rel_attr:
    ID {
      $$ = new RelAttrSqlNode;
      $$->attribute_name = $1;
      printf("attr_name:%s\n",$1);
      free($1);
    }
    | ID DOT ID {
      $$ = new RelAttrSqlNode;
      $$->relation_name  = $1;
      $$->attribute_name = $3;
      free($1);
      free($3);
    }
    ;

relation:
    ID {
      $$ = $1;
    }
    ;
rel_list:
  /* empty */ {
    $$ = nullptr;
  }
  | COMMA relation alias_stmt rel_list {
    $$ = ($4 != nullptr ? $4 : new std::vector<rel_info>());
  
    rel_info r;
    r.relation_name = string( $2);
    printf("rel name:%s.\n", $2);
    if ($3) {
      r.relation_alias = std::string($3);
      free($3);
    }
    $$->push_back(std::move(r));
    free($2);
  }
  | INNER JOIN relation alias_stmt on_stmt rel_list {
    $$ = ($6 != nullptr ? $6 : new std::vector<rel_info>());
    rel_info r;
    r.relation_name = $3;
    free($3);
    if ($4) {
      r.relation_alias = std::string($4);
      free($4);
    }
    if ($5) {
      r.on_conditions = $5;
    }
    $$->insert($$->begin(), std::move(r));
  }
  ;

on_stmt:
  /* empty */ {
    // cross product
    $$ = nullptr;
  }
  | ON condition_list {
    $$ = $2;
  }
  ;

where:
    /* empty */
    {
      $$ = nullptr;
    }
    | WHERE condition_list {
      $$ = $2;  
    }
    ;
condition_list:
    /* empty */
    {
      $$ = nullptr;
    }
    | condition {
      $$ = new std::vector<Expression*>;
      $$->emplace_back($1);
      // delete $1;
    }
    | condition AND condition_list {
      $$ = $3;
      $$->emplace_back($1);
      // delete $1;
    }
    ;
condition:
    expression comp_op expression {
      std::unique_ptr<Expression> left($1);
      std::unique_ptr<Expression> right($3);
      $$ = new ComparisonExpr($2, std::move(left), std::move(right));
    }
    
    // rel_attr comp_op value
    // {
    //   $$ = new ConditionSqlNode;
    //   $$->left_is_attr = 1;
    //   $$->left_attr = *$1;
    //   $$->right_is_attr = 0;
    //   $$->right_value = *$3;
    //   $$->comp = $2;

    //   delete $1;
    //   delete $3;
    // }
    // | value comp_op value 
    // {
    //   $$ = new ConditionSqlNode;
    //   $$->left_is_attr = 0;
    //   $$->left_value = *$1;
    //   $$->right_is_attr = 0;
    //   $$->right_value = *$3;
    //   $$->comp = $2;

    //   delete $1;
    //   delete $3;
    // }
    // | rel_attr comp_op rel_attr
    // {
    //   $$ = new ConditionSqlNode;
    //   $$->left_is_attr = 1;
    //   $$->left_attr = *$1;
    //   $$->right_is_attr = 1;
    //   $$->right_attr = *$3;
    //   $$->comp = $2;

    //   delete $1;
    //   delete $3;
    // }
    // | value comp_op rel_attr
    // {
    //   $$ = new ConditionSqlNode;
    //   $$->left_is_attr = 0;
    //   $$->left_value = *$1;
    //   $$->right_is_attr = 1;
    //   $$->right_attr = *$3;
    //   $$->comp = $2;

    //   delete $1;
    //   delete $3;
    // }
    ;

comp_op:
      EQ { $$ = EQUAL_TO; }
    | LT { $$ = LESS_THAN; }
    | GT { $$ = GREAT_THAN; }
    | LE { $$ = LESS_EQUAL; }
    | GE { $$ = GREAT_EQUAL; }
    | NE { $$ = NOT_EQUAL; }
    | LIKE { $$ = LK;}
    | NOT LIKE { $$ = NOT_LK;}
    ;

// your code here
group_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | GROUP BY rel_attrs {
      $$ = $3;
    }
    ;

rel_attrs:
  rel_attr {
    // std::vector<std::unique_ptr<Expression>> *
    auto field = new UnboundFieldExpr($1->relation_name,$1->attribute_name);
    $$ = new std::vector<std::unique_ptr<Expression>>();
    $$->emplace_back(field);
  }
  | rel_attr COMMA rel_attrs {
    $$ = $3;
    auto field = new UnboundFieldExpr($1->relation_name,$1->attribute_name);
    $$->emplace_back(field);
    delete $1;
  }
  ;
// having:
//     ;


order_by:
    /* empty */
    {
      $$ = nullptr;
    }
    | ORDER BY order_by_seq {
      $$ = $3;
    }
    ;
order_by_seq:
    ID asc_stmt {
      $$ = new vector<order_by>;
      order_by seq;
      seq.attr_name = $1;
      free($1);
      seq.asc = *($2);
      delete $2;
      $$->emplace_back(seq);
    }
    | ID asc_stmt COMMA order_by_seq {
      $$ = $4;
      order_by seq;
      seq.attr_name = $1;
      free($1);
      seq.asc = *($2);
      delete $2;
      $$->emplace_back(seq);
    }
    ;

asc_stmt:
  /* empty */
  {
    // default option is asc
    $$ = new bool(true);
  }
  | ASC {
    $$ = new bool(true);
  }
  | DESC {
    $$ = new bool(false);
  };

load_data_stmt:
    LOAD DATA INFILE SSS INTO TABLE ID 
    {
      char *tmp_file_name = common::substr($4, 1, strlen($4) - 2);
      
      $$ = new ParsedSqlNode(SCF_LOAD_DATA);
      $$->load_data.relation_name = $7;
      $$->load_data.file_name = tmp_file_name;
      free($7);
      free(tmp_file_name);
    }
    ;

explain_stmt:
    EXPLAIN command_wrapper
    {
      $$ = new ParsedSqlNode(SCF_EXPLAIN);
      $$->explain.sql_node = std::unique_ptr<ParsedSqlNode>($2);
    }
    ;

set_variable_stmt:
    SET ID EQ value
    {
      $$ = new ParsedSqlNode(SCF_SET_VARIABLE);
      $$->set_variable.name  = $2;
      $$->set_variable.value = *$4;
      free($2);
      delete $4;
    }
    ;

opt_semicolon: /*empty*/
    | SEMICOLON
    ;
%%
//_____________________________________________________________________
extern void scan_string(const char *str, yyscan_t scanner);

int sql_parse(const char *s, ParsedSqlResult *sql_result) {
  yyscan_t scanner;
  yylex_init(&scanner);
  scan_string(s, scanner);
  int result = yyparse(s, sql_result, scanner);
  yylex_destroy(scanner);
  return result;
}
