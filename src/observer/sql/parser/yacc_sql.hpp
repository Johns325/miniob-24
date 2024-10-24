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
    CALC = 266,                    /* CALC  */
    null = 267,                    /* null  */
    SELECT = 268,                  /* SELECT  */
    ALIAS = 269,                   /* ALIAS  */
    ASC = 270,                     /* ASC  */
    ORDER = 271,                   /* ORDER  */
    DESC = 272,                    /* DESC  */
    SHOW = 273,                    /* SHOW  */
    SYNC = 274,                    /* SYNC  */
    INSERT = 275,                  /* INSERT  */
    IS = 276,                      /* IS  */
    DELETE = 277,                  /* DELETE  */
    UPDATE = 278,                  /* UPDATE  */
    UNIQUE = 279,                  /* UNIQUE  */
    LBRACE = 280,                  /* LBRACE  */
    RBRACE = 281,                  /* RBRACE  */
    COMMA = 282,                   /* COMMA  */
    INNER = 283,                   /* INNER  */
    JOIN = 284,                    /* JOIN  */
    TRX_BEGIN = 285,               /* TRX_BEGIN  */
    TRX_COMMIT = 286,              /* TRX_COMMIT  */
    TRX_ROLLBACK = 287,            /* TRX_ROLLBACK  */
    INT_T = 288,                   /* INT_T  */
    STRING_T = 289,                /* STRING_T  */
    FLOAT_T = 290,                 /* FLOAT_T  */
    DATE_T = 291,                  /* DATE_T  */
    LIKE = 292,                    /* LIKE  */
    NOT = 293,                     /* NOT  */
    VECTOR_T = 294,                /* VECTOR_T  */
    HELP = 295,                    /* HELP  */
    EXIT = 296,                    /* EXIT  */
    DOT = 297,                     /* DOT  */
    INTO = 298,                    /* INTO  */
    VALUES = 299,                  /* VALUES  */
    FROM = 300,                    /* FROM  */
    WHERE = 301,                   /* WHERE  */
    AND = 302,                     /* AND  */
    SET = 303,                     /* SET  */
    ON = 304,                      /* ON  */
    LOAD = 305,                    /* LOAD  */
    DATA = 306,                    /* DATA  */
    INFILE = 307,                  /* INFILE  */
    EXPLAIN = 308,                 /* EXPLAIN  */
    STORAGE = 309,                 /* STORAGE  */
    FORMAT = 310,                  /* FORMAT  */
    EQ = 311,                      /* EQ  */
    LT = 312,                      /* LT  */
    GT = 313,                      /* GT  */
    LE = 314,                      /* LE  */
    GE = 315,                      /* GE  */
    NE = 316,                      /* NE  */
    L2_DISTANCE = 317,             /* L2_DISTANCE  */
    INNER_PRODUCT = 318,           /* INNER_PRODUCT  */
    COSINE_DISTANCE = 319,         /* COSINE_DISTANCE  */
    NUMBER = 320,                  /* NUMBER  */
    FLOAT = 321,                   /* FLOAT  */
    ID = 322,                      /* ID  */
    SSS = 323,                     /* SSS  */
    VECTOR_DATA = 324,             /* VECTOR_DATA  */
    UMINUS = 325                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 132 "yacc_sql.y"

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

#line 158 "yacc_sql.hpp"

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
