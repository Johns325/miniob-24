/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_YACC_SQL_HPP_INCLUDED
# define YY_YY_YACC_SQL_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    SEMICOLON = 258,               /* SEMICOLON  */
    BY = 259,                      /* BY  */
    CREATE = 260,                  /* CREATE  */
    DROP = 261,                    /* DROP  */
    GROUP = 262,                   /* GROUP  */
    TABLE = 263,                   /* TABLE  */
    TABLES = 264,                  /* TABLES  */
    INDEX = 265,                   /* INDEX  */
    HAVING = 266,                  /* HAVING  */
    CALC = 267,                    /* CALC  */
    null = 268,                    /* null  */
    SELECT = 269,                  /* SELECT  */
    ALIAS = 270,                   /* ALIAS  */
    ASC = 271,                     /* ASC  */
    ORDER = 272,                   /* ORDER  */
    DESC = 273,                    /* DESC  */
    SHOW = 274,                    /* SHOW  */
    SYNC = 275,                    /* SYNC  */
    INSERT = 276,                  /* INSERT  */
    IS = 277,                      /* IS  */
    AS = 278,                      /* AS  */
    DELETE = 279,                  /* DELETE  */
    UPDATE = 280,                  /* UPDATE  */
    UNIQUE = 281,                  /* UNIQUE  */
    LBRACE = 282,                  /* LBRACE  */
    RBRACE = 283,                  /* RBRACE  */
    COMMA = 284,                   /* COMMA  */
    INNER = 285,                   /* INNER  */
    JOIN = 286,                    /* JOIN  */
    TRX_BEGIN = 287,               /* TRX_BEGIN  */
    TRX_COMMIT = 288,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 289,            /* TRX_ROLLBACK  */
    INT_T = 290,                   /* INT_T  */
    STRING_T = 291,                /* STRING_T  */
    FLOAT_T = 292,                 /* FLOAT_T  */
    IN = 293,                      /* IN  */
    EXISTS = 294,                  /* EXISTS  */
    DATE_T = 295,                  /* DATE_T  */
    LIKE = 296,                    /* LIKE  */
    NOT = 297,                     /* NOT  */
    VECTOR_T = 298,                /* VECTOR_T  */
    HELP = 299,                    /* HELP  */
    EXIT = 300,                    /* EXIT  */
    DOT = 301,                     /* DOT  */
    INTO = 302,                    /* INTO  */
    VALUES = 303,                  /* VALUES  */
    FROM = 304,                    /* FROM  */
    WHERE = 305,                   /* WHERE  */
    AND = 306,                     /* AND  */
    SET = 307,                     /* SET  */
    ON = 308,                      /* ON  */
    LOAD = 309,                    /* LOAD  */
    DATA = 310,                    /* DATA  */
    TEXT_T = 311,                  /* TEXT_T  */
    INFILE = 312,                  /* INFILE  */
    VIEW = 313,                    /* VIEW  */
    EXPLAIN = 314,                 /* EXPLAIN  */
    STORAGE = 315,                 /* STORAGE  */
    FORMAT = 316,                  /* FORMAT  */
    EQ = 317,                      /* EQ  */
    LT = 318,                      /* LT  */
    GT = 319,                      /* GT  */
    LE = 320,                      /* LE  */
    GE = 321,                      /* GE  */
    NE = 322,                      /* NE  */
    L2_DISTANCE = 323,             /* L2_DISTANCE  */
    INNER_PRODUCT = 324,           /* INNER_PRODUCT  */
    COSINE_DISTANCE = 325,         /* COSINE_DISTANCE  */
    NUMBER = 326,                  /* NUMBER  */
    FLOAT = 327,                   /* FLOAT  */
    ID = 328,                      /* ID  */
    SSS = 329,                     /* SSS  */
    VECTOR_DATA = 330,             /* VECTOR_DATA  */
    UMINUS = 331                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 138 "yacc_sql.y"

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
  std::vector<rel_info*>*                     rel_list_type;
  std::vector<OrderBySqlNode>*               order_by_list;
  Assignment *                               assignment_ptr;
  std::vector<Assignment*>*                  assignment_ptr_list;
  std::vector<Value*>*                       const_value_list_type;

#line 168 "yacc_sql.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif




int yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner);


#endif /* !YY_YY_YACC_SQL_HPP_INCLUDED  */
