/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 2 "yacc_sql.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
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

static int and_flag  = 1;

#line 127 "yacc_sql.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "yacc_sql.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_SEMICOLON = 3,                  /* SEMICOLON  */
  YYSYMBOL_BY = 4,                         /* BY  */
  YYSYMBOL_CREATE = 5,                     /* CREATE  */
  YYSYMBOL_DROP = 6,                       /* DROP  */
  YYSYMBOL_GROUP = 7,                      /* GROUP  */
  YYSYMBOL_TABLE = 8,                      /* TABLE  */
  YYSYMBOL_TABLES = 9,                     /* TABLES  */
  YYSYMBOL_INDEX = 10,                     /* INDEX  */
  YYSYMBOL_HAVING = 11,                    /* HAVING  */
  YYSYMBOL_CALC = 12,                      /* CALC  */
  YYSYMBOL_null = 13,                      /* null  */
  YYSYMBOL_SELECT = 14,                    /* SELECT  */
  YYSYMBOL_ASC = 15,                       /* ASC  */
  YYSYMBOL_ORDER = 16,                     /* ORDER  */
  YYSYMBOL_DESC = 17,                      /* DESC  */
  YYSYMBOL_SHOW = 18,                      /* SHOW  */
  YYSYMBOL_SYNC = 19,                      /* SYNC  */
  YYSYMBOL_INSERT = 20,                    /* INSERT  */
  YYSYMBOL_IS = 21,                        /* IS  */
  YYSYMBOL_AS = 22,                        /* AS  */
  YYSYMBOL_DELETE = 23,                    /* DELETE  */
  YYSYMBOL_UPDATE = 24,                    /* UPDATE  */
  YYSYMBOL_UNIQUE = 25,                    /* UNIQUE  */
  YYSYMBOL_LBRACE = 26,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 27,                    /* RBRACE  */
  YYSYMBOL_COMMA = 28,                     /* COMMA  */
  YYSYMBOL_INNER = 29,                     /* INNER  */
  YYSYMBOL_JOIN = 30,                      /* JOIN  */
  YYSYMBOL_TRX_BEGIN = 31,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 32,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 33,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 34,                     /* INT_T  */
  YYSYMBOL_STRING_T = 35,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 36,                   /* FLOAT_T  */
  YYSYMBOL_IN = 37,                        /* IN  */
  YYSYMBOL_EXISTS = 38,                    /* EXISTS  */
  YYSYMBOL_DATE_T = 39,                    /* DATE_T  */
  YYSYMBOL_LIKE = 40,                      /* LIKE  */
  YYSYMBOL_NOT = 41,                       /* NOT  */
  YYSYMBOL_VECTOR_T = 42,                  /* VECTOR_T  */
  YYSYMBOL_HELP = 43,                      /* HELP  */
  YYSYMBOL_EXIT = 44,                      /* EXIT  */
  YYSYMBOL_DOT = 45,                       /* DOT  */
  YYSYMBOL_INTO = 46,                      /* INTO  */
  YYSYMBOL_VALUES = 47,                    /* VALUES  */
  YYSYMBOL_FROM = 48,                      /* FROM  */
  YYSYMBOL_WHERE = 49,                     /* WHERE  */
  YYSYMBOL_AND = 50,                       /* AND  */
  YYSYMBOL_SET = 51,                       /* SET  */
  YYSYMBOL_ON = 52,                        /* ON  */
  YYSYMBOL_LOAD = 53,                      /* LOAD  */
  YYSYMBOL_DATA = 54,                      /* DATA  */
  YYSYMBOL_TEXT_T = 55,                    /* TEXT_T  */
  YYSYMBOL_INFILE = 56,                    /* INFILE  */
  YYSYMBOL_VIEW = 57,                      /* VIEW  */
  YYSYMBOL_EXPLAIN = 58,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 59,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 60,                    /* FORMAT  */
  YYSYMBOL_EQ = 61,                        /* EQ  */
  YYSYMBOL_LT = 62,                        /* LT  */
  YYSYMBOL_GT = 63,                        /* GT  */
  YYSYMBOL_LE = 64,                        /* LE  */
  YYSYMBOL_GE = 65,                        /* GE  */
  YYSYMBOL_WITH_T = 66,                    /* WITH_T  */
  YYSYMBOL_TYPE_T = 67,                    /* TYPE_T  */
  YYSYMBOL_IVFFLAT = 68,                   /* IVFFLAT  */
  YYSYMBOL_DISTANCE_T = 69,                /* DISTANCE_T  */
  YYSYMBOL_LISTS_T = 70,                   /* LISTS_T  */
  YYSYMBOL_PROBES_T = 71,                  /* PROBES_T  */
  YYSYMBOL_NE = 72,                        /* NE  */
  YYSYMBOL_OR = 73,                        /* OR  */
  YYSYMBOL_L2_DISTANCE = 74,               /* L2_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 75,             /* INNER_PRODUCT  */
  YYSYMBOL_COSINE_DISTANCE = 76,           /* COSINE_DISTANCE  */
  YYSYMBOL_LIMIT_T = 77,                   /* LIMIT_T  */
  YYSYMBOL_NUMBER = 78,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 79,                     /* FLOAT  */
  YYSYMBOL_ID = 80,                        /* ID  */
  YYSYMBOL_SSS = 81,                       /* SSS  */
  YYSYMBOL_VECTOR_DATA = 82,               /* VECTOR_DATA  */
  YYSYMBOL_83_ = 83,                       /* '+'  */
  YYSYMBOL_84_ = 84,                       /* '-'  */
  YYSYMBOL_85_ = 85,                       /* '*'  */
  YYSYMBOL_86_ = 86,                       /* '/'  */
  YYSYMBOL_UMINUS = 87,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 88,                  /* $accept  */
  YYSYMBOL_commands = 89,                  /* commands  */
  YYSYMBOL_command_wrapper = 90,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 91,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 92,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 93,                 /* sync_stmt  */
  YYSYMBOL_alias_stmt = 94,                /* alias_stmt  */
  YYSYMBOL_begin_stmt = 95,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 96,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 97,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 98,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 99,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 100,          /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 101,        /* create_index_stmt  */
  YYSYMBOL_create_vector_index_stmt = 102, /* create_vector_index_stmt  */
  YYSYMBOL_vi_arg_list = 103,              /* vi_arg_list  */
  YYSYMBOL_distance_type = 104,            /* distance_type  */
  YYSYMBOL_vi_arg = 105,                   /* vi_arg  */
  YYSYMBOL_unique_stmt = 106,              /* unique_stmt  */
  YYSYMBOL_attr_list = 107,                /* attr_list  */
  YYSYMBOL_drop_index_stmt = 108,          /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 109,        /* create_table_stmt  */
  YYSYMBOL_create_select_stmt = 110,       /* create_select_stmt  */
  YYSYMBOL_create_view_stmt = 111,         /* create_view_stmt  */
  YYSYMBOL_as_stmt = 112,                  /* as_stmt  */
  YYSYMBOL_attr_def_list = 113,            /* attr_def_list  */
  YYSYMBOL_attr_def = 114,                 /* attr_def  */
  YYSYMBOL_null_def = 115,                 /* null_def  */
  YYSYMBOL_number = 116,                   /* number  */
  YYSYMBOL_type = 117,                     /* type  */
  YYSYMBOL_insert_stmt = 118,              /* insert_stmt  */
  YYSYMBOL_value_list = 119,               /* value_list  */
  YYSYMBOL_insert_val = 120,               /* insert_val  */
  YYSYMBOL_const_value_list_expr = 121,    /* const_value_list_expr  */
  YYSYMBOL_const_value_list = 122,         /* const_value_list  */
  YYSYMBOL_value = 123,                    /* value  */
  YYSYMBOL_storage_format = 124,           /* storage_format  */
  YYSYMBOL_delete_stmt = 125,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 126,              /* update_stmt  */
  YYSYMBOL_assignment_list = 127,          /* assignment_list  */
  YYSYMBOL_assignment = 128,               /* assignment  */
  YYSYMBOL_select_stmt = 129,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 130,                /* calc_stmt  */
  YYSYMBOL_expression_list = 131,          /* expression_list  */
  YYSYMBOL_expression = 132,               /* expression  */
  YYSYMBOL_aggr_func_expr = 133,           /* aggr_func_expr  */
  YYSYMBOL_rel_attr = 134,                 /* rel_attr  */
  YYSYMBOL_relation = 135,                 /* relation  */
  YYSYMBOL_limit_opt = 136,                /* limit_opt  */
  YYSYMBOL_rel_list = 137,                 /* rel_list  */
  YYSYMBOL_on_stmt = 138,                  /* on_stmt  */
  YYSYMBOL_where = 139,                    /* where  */
  YYSYMBOL_condition_list = 140,           /* condition_list  */
  YYSYMBOL_and_clause = 141,               /* and_clause  */
  YYSYMBOL_condition = 142,                /* condition  */
  YYSYMBOL_null_condition = 143,           /* null_condition  */
  YYSYMBOL_comp_op = 144,                  /* comp_op  */
  YYSYMBOL_group_by = 145,                 /* group_by  */
  YYSYMBOL_rel_attrs = 146,                /* rel_attrs  */
  YYSYMBOL_having_stmt = 147,              /* having_stmt  */
  YYSYMBOL_order_by = 148,                 /* order_by  */
  YYSYMBOL_order_list = 149,               /* order_list  */
  YYSYMBOL_load_data_stmt = 150,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 151,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 152,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 153             /* opt_semicolon  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  76
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   475

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  66
/* YYNRULES -- Number of rules.  */
#define YYNRULES  188
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  374

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   338


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,    85,    83,     2,    84,     2,    86,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    87
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   261,   261,   269,   270,   271,   272,   273,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   289,   290,   291,   295,   301,   306,   312,
     315,   320,   326,   332,   338,   344,   351,   357,   365,   387,
     418,   422,   432,   435,   438,   444,   451,   457,   462,   471,
     474,   479,   482,   493,   503,   526,   534,   554,   563,   566,
     572,   575,   588,   601,   613,   616,   619,   623,   626,   627,
     628,   629,   630,   631,   634,   653,   656,   667,   670,   678,
     685,   691,   696,   702,   706,   710,   716,   740,   743,   750,
     761,   776,   780,   786,   793,   801,   811,   857,   866,   879,
     894,   900,   907,   911,   914,   918,   921,   924,   928,   933,
     936,   939,   942,   953,   957,   961,   969,   975,   982,   991,
     997,   998,  1001,  1004,  1017,  1035,  1039,  1046,  1049,  1055,
    1058,  1063,  1071,  1074,  1079,  1085,  1090,  1095,  1101,  1106,
    1111,  1116,  1121,  1127,  1134,  1141,  1150,  1157,  1165,  1172,
    1198,  1199,  1200,  1201,  1202,  1203,  1204,  1205,  1206,  1207,
    1208,  1209,  1210,  1211,  1217,  1220,  1226,  1232,  1240,  1243,
    1281,  1284,  1289,  1299,  1309,  1328,  1347,  1366,  1385,  1404,
    1423,  1433,  1443,  1454,  1480,  1493,  1501,  1511,  1512
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "SEMICOLON", "BY",
  "CREATE", "DROP", "GROUP", "TABLE", "TABLES", "INDEX", "HAVING", "CALC",
  "null", "SELECT", "ASC", "ORDER", "DESC", "SHOW", "SYNC", "INSERT", "IS",
  "AS", "DELETE", "UPDATE", "UNIQUE", "LBRACE", "RBRACE", "COMMA", "INNER",
  "JOIN", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK", "INT_T", "STRING_T",
  "FLOAT_T", "IN", "EXISTS", "DATE_T", "LIKE", "NOT", "VECTOR_T", "HELP",
  "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET", "ON",
  "LOAD", "DATA", "TEXT_T", "INFILE", "VIEW", "EXPLAIN", "STORAGE",
  "FORMAT", "EQ", "LT", "GT", "LE", "GE", "WITH_T", "TYPE_T", "IVFFLAT",
  "DISTANCE_T", "LISTS_T", "PROBES_T", "NE", "OR", "L2_DISTANCE",
  "INNER_PRODUCT", "COSINE_DISTANCE", "LIMIT_T", "NUMBER", "FLOAT", "ID",
  "SSS", "VECTOR_DATA", "'+'", "'-'", "'*'", "'/'", "UMINUS", "$accept",
  "commands", "command_wrapper", "exit_stmt", "help_stmt", "sync_stmt",
  "alias_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "create_vector_index_stmt", "vi_arg_list",
  "distance_type", "vi_arg", "unique_stmt", "attr_list", "drop_index_stmt",
  "create_table_stmt", "create_select_stmt", "create_view_stmt", "as_stmt",
  "attr_def_list", "attr_def", "null_def", "number", "type", "insert_stmt",
  "value_list", "insert_val", "const_value_list_expr", "const_value_list",
  "value", "storage_format", "delete_stmt", "update_stmt",
  "assignment_list", "assignment", "select_stmt", "calc_stmt",
  "expression_list", "expression", "aggr_func_expr", "rel_attr",
  "relation", "limit_opt", "rel_list", "on_stmt", "where",
  "condition_list", "and_clause", "condition", "null_condition", "comp_op",
  "group_by", "rel_attrs", "having_stmt", "order_by", "order_list",
  "load_data_stmt", "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-306)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-82)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     348,     2,    24,   232,   232,   -55,    26,  -306,    -1,    -7,
     -30,  -306,  -306,  -306,  -306,  -306,   -25,    15,   348,    62,
      72,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,    10,  -306,    68,    19,    92,    27,
      41,   232,   114,   118,   129,  -306,  -306,    -5,  -306,  -306,
     232,  -306,  -306,  -306,    79,  -306,  -306,    70,  -306,  -306,
      57,    80,   125,   120,   130,  -306,  -306,  -306,  -306,    11,
     119,   187,   138,  -306,   179,   153,   232,   232,   232,   250,
     -56,  -306,   154,  -306,   232,   232,   232,   232,   207,   162,
     199,   203,   175,   123,   180,  -306,   186,   264,   220,   264,
     227,   216,  -306,    85,   266,   273,  -306,   265,   -13,  -306,
    -306,  -306,    39,    39,  -306,  -306,   232,  -306,     1,   283,
      30,  -306,   254,   203,   291,  -306,   277,   361,   299,  -306,
     260,  -306,   275,  -306,   232,   232,   232,  -306,  -306,  -306,
     102,    -2,   349,   189,   349,   219,  -306,   -31,  -306,    38,
    -306,   175,   325,  -306,  -306,  -306,  -306,  -306,  -306,    13,
     186,   337,   343,   347,   214,   258,   262,   162,   344,   203,
    -306,   123,   350,  -306,   334,  -306,  -306,  -306,   111,  -306,
    -306,  -306,  -306,  -306,  -306,   109,   355,   139,   356,   132,
     148,  -306,  -306,    30,  -306,   264,  -306,  -306,   296,  -306,
     306,   364,  -306,   299,     6,   305,   308,  -306,  -306,  -306,
       1,   162,   386,  -306,    -2,   367,  -306,  -306,  -306,  -306,
    -306,   189,  -306,   253,  -306,   123,   349,  -306,   189,   253,
    -306,   189,  -306,   253,  -306,   371,  -306,  -306,   375,  -306,
    -306,   345,   264,  -306,   377,   379,   102,     1,   404,   398,
     350,  -306,   388,  -306,   389,   169,   391,   392,  -306,    17,
     359,  -306,   357,   342,   397,  -306,   373,   346,    30,   411,
    -306,  -306,  -306,   189,  -306,   253,  -306,  -306,  -306,   351,
     402,   379,  -306,    30,   102,   384,   405,  -306,  -306,   426,
     358,   407,  -306,   251,  -306,  -306,  -306,   346,   145,   354,
    -306,  -306,   376,   378,   380,   381,   409,   410,  -306,   414,
     417,   418,    21,  -306,  -306,   382,   212,   368,   369,  -306,
     251,   -19,   213,   281,   420,   421,   145,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,   423,   424,   425,   427,   428,
     429,   145,   145,  -306,   346,   363,   346,   372,   346,   383,
    -306,  -306,   431,   432,   433,   434,   435,   436,  -306,  -306,
    -306,  -306,  -306,  -306
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    49,     0,     0,     0,     0,     0,    28,     0,     0,
       0,    32,    33,    34,    27,    26,     0,     0,     0,     0,
     187,    25,    24,    15,    16,    19,    20,     9,    10,    11,
      12,    13,    14,     8,    17,    18,     5,     7,     6,     4,
       3,    21,    22,    23,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    83,    84,   116,    85,    86,
       0,   102,   100,    97,    29,   109,   101,     0,    37,    36,
       0,     0,     0,     0,     0,   185,     1,   188,     2,    58,
       0,    58,     0,    35,     0,     0,     0,     0,     0,     0,
       0,   108,     0,    30,     0,     0,     0,     0,    98,     0,
       0,   127,     0,     0,     0,    59,     0,     0,     0,     0,
       0,     0,   107,     0,     0,     0,   114,     0,    29,   117,
     118,    31,   103,   104,   105,   106,     0,   119,    29,     0,
     129,    89,     0,   127,    91,   186,     0,     0,    60,    55,
       0,    57,     0,    53,     0,     0,     0,   115,   113,    99,
     122,     0,     0,     0,     0,     0,   128,   130,   142,     0,
      90,     0,     0,    68,    69,    70,    71,    72,    73,    64,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   127,
      79,     0,    75,    77,   159,   160,   162,   156,     0,   150,
     151,   152,   153,   154,   155,     0,     0,   100,     0,     0,
       0,   132,   133,   129,    94,     0,    93,    92,     0,    65,
       0,     0,    63,    60,    87,     0,     0,   110,   111,   112,
      29,     0,   164,    78,     0,     0,   158,   161,   163,   157,
     145,     0,   148,   144,    80,     0,     0,   149,     0,   138,
     143,     0,   137,   134,   131,     0,   184,    67,     0,    66,
      61,     0,     0,    54,     0,    51,   122,    29,     0,   168,
      75,    74,     0,    82,    81,     0,     0,     0,    95,    64,
       0,    56,     0,     0,     0,   123,   125,     0,   129,   170,
      76,   147,   146,     0,   139,   136,   140,   135,    62,     0,
       0,    51,    38,   129,   122,   116,   166,   165,   169,     0,
     121,     0,    88,     0,    52,   126,   124,     0,     0,     0,
      96,   141,     0,     0,     0,     0,     0,    40,   167,     0,
       0,     0,   172,   171,   120,     0,     0,     0,     0,    39,
       0,     0,     0,     0,   180,   182,     0,    46,    42,    44,
      43,    45,    47,    48,    41,     0,     0,     0,     0,     0,
       0,     0,     0,   173,     0,     0,     0,     0,     0,     0,
     181,   183,     0,     0,     0,     0,     0,     0,   177,   174,
     178,   175,   179,   176
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -306,  -306,   446,  -306,  -306,  -306,  -125,  -306,  -306,  -306,
    -306,  -306,  -306,  -306,  -306,   136,  -306,  -306,  -306,   176,
    -306,  -306,  -306,  -306,   -76,   255,   300,   200,  -306,  -306,
    -306,   211,   248,  -178,   238,   -85,  -306,  -306,  -306,   313,
    -306,  -105,  -306,     8,    -3,  -306,  -179,  -161,  -306,  -241,
    -306,  -127,  -190,  -306,  -306,  -306,  -147,  -306,   168,  -306,
    -306,  -305,  -306,  -306,  -306,  -306
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    98,    24,    25,    26,
      27,    28,    29,    30,    31,   316,   341,   317,    48,   274,
      32,    33,    34,    35,   107,   171,   138,   212,   248,   169,
      36,   225,   182,   154,   196,    62,   253,    37,    38,   133,
     134,    39,    40,    63,    85,    65,    66,   128,   310,   179,
     294,   131,   156,   203,   157,   158,   195,   259,   297,   279,
     300,   323,    41,    42,    43,    78
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      64,    64,   139,   150,   141,   109,   160,   199,   200,    92,
      44,   180,    67,   244,   148,   275,   220,   232,   135,   201,
     -58,    89,   242,    92,   119,    68,   209,    45,   105,   120,
     209,   353,    49,   105,    50,    69,   334,   106,   335,   210,
      90,    71,   202,   152,    46,    70,   360,   361,   198,   336,
      72,   204,   222,   306,   211,    73,   153,    91,   211,    47,
     257,   295,    76,   345,   205,   251,   183,    93,   197,    74,
      94,    95,    96,    97,   206,    77,    55,    56,    80,    58,
      59,    93,   181,   113,   114,   115,   118,   284,   298,   265,
      79,   122,   123,   124,   125,   256,   223,   117,   296,    81,
     245,    92,    82,   305,    52,    53,    54,    83,    55,    56,
      57,    58,    59,   144,    60,    61,    55,    56,    99,    58,
      59,    84,   230,    64,    96,    97,   262,   155,   296,   322,
     177,   178,   276,   266,   149,   231,   267,   100,   252,   183,
      86,   174,   175,   176,    87,   237,   197,   271,   227,   228,
     264,   229,   346,   348,   350,    88,   197,   322,   238,    93,
     101,   240,    94,    95,    96,    97,   -81,   235,    94,    95,
      96,    97,   322,   322,   241,   362,   102,   364,   301,   366,
     112,   103,   282,    52,    53,    54,   104,    55,    56,    57,
      58,    59,   233,    60,    61,   283,   239,   243,   197,   108,
     155,    55,    56,     4,    58,    59,    52,    53,    54,   105,
      55,    56,    57,    58,    59,    51,    60,    61,   110,   319,
     320,   321,    52,    53,    54,   295,    55,    56,    57,    58,
      59,   111,    60,    61,   121,   126,    94,    95,    96,    97,
     184,   217,   127,    52,    53,    54,   129,    55,    56,    57,
      58,    59,   130,    60,    61,   132,   185,   186,    51,   187,
     188,   136,   285,    52,    53,    54,   137,    55,    56,    57,
      58,    59,   140,    60,    61,   155,    51,   116,     4,   142,
     189,   190,   191,   192,   193,   218,   338,   339,   340,   219,
     155,   194,   147,   295,   145,   347,   143,    94,    95,    96,
      97,   146,    94,    95,    96,    97,    52,    53,    54,   151,
      55,    56,    57,    58,    59,   159,    60,    61,   312,   161,
     313,   314,   315,   162,    52,    53,    54,   170,    55,    56,
      57,    58,    59,   208,    60,    61,    94,    95,    96,    97,
     172,    94,    95,    96,    97,    94,    95,    96,    97,    94,
      95,    96,    97,     1,     2,   173,    94,    95,    96,    97,
       3,   295,     4,   349,   214,     5,     6,     7,     8,   215,
     184,     9,    10,   216,   221,   226,   246,   249,   224,    11,
      12,    13,   234,   236,   247,   254,   185,   186,   255,   187,
     188,    14,    15,   258,   261,   163,   164,   165,   268,    16,
     166,    17,   269,   167,   272,   270,    18,   273,   277,   278,
     189,   190,   191,   192,   193,   281,   168,   235,   286,   287,
     289,   194,   291,   290,   292,   293,   295,   299,   303,    90,
     308,   302,   324,   307,   311,   309,   329,   325,   330,   326,
     331,   327,   328,   332,   333,   363,   342,   343,   351,   352,
     337,   354,   355,   356,   365,   357,   358,   359,   368,   369,
     370,   371,   372,   373,    75,   367,   344,   304,   250,   288,
     213,   280,   260,   263,   207,   318
};

static const yytype_int16 yycheck[] =
{
       3,     4,   107,   128,   109,    81,   133,   154,   155,    22,
       8,    13,     4,   203,    27,   256,   177,   195,   103,    50,
      14,    26,   200,    22,    80,    80,    13,    25,    22,    85,
      13,   336,     8,    22,    10,     9,    15,    26,    17,    26,
      45,    48,    73,    13,    42,    46,   351,   352,   153,    28,
      80,    13,   179,   294,    41,    80,    26,    60,    41,    57,
     221,    80,     0,    82,    26,    59,   151,    80,   153,    54,
      83,    84,    85,    86,   159,     3,    78,    79,    10,    81,
      82,    80,    84,    86,    87,    88,    89,   265,   278,   236,
      80,    94,    95,    96,    97,   220,   181,    89,   277,    80,
     205,    22,    10,   293,    74,    75,    76,    80,    78,    79,
      80,    81,    82,    28,    84,    85,    78,    79,    48,    81,
      82,    80,    13,   126,    85,    86,   231,   130,   307,   308,
      28,    29,   257,   238,   126,    26,   241,    80,   214,   224,
      26,   144,   145,   146,    26,    13,   231,   252,    37,    38,
     235,    40,   331,   332,   333,    26,   241,   336,    26,    80,
      80,    13,    83,    84,    85,    86,    27,    28,    83,    84,
      85,    86,   351,   352,    26,   354,    51,   356,   283,   358,
      27,    61,    13,    74,    75,    76,    56,    78,    79,    80,
      81,    82,   195,    84,    85,    26,   199,   200,   283,    80,
     203,    78,    79,    14,    81,    82,    74,    75,    76,    22,
      78,    79,    80,    81,    82,    26,    84,    85,    80,    74,
      75,    76,    74,    75,    76,    80,    78,    79,    80,    81,
      82,    52,    84,    85,    80,    28,    83,    84,    85,    86,
      21,    27,    80,    74,    75,    76,    47,    78,    79,    80,
      81,    82,    49,    84,    85,    80,    37,    38,    26,    40,
      41,    81,   265,    74,    75,    76,    80,    78,    79,    80,
      81,    82,    52,    84,    85,   278,    26,    27,    14,    52,
      61,    62,    63,    64,    65,    27,    74,    75,    76,    27,
     293,    72,    27,    80,    28,    82,    80,    83,    84,    85,
      86,    28,    83,    84,    85,    86,    74,    75,    76,    26,
      78,    79,    80,    81,    82,    61,    84,    85,    67,    28,
      69,    70,    71,    46,    74,    75,    76,    28,    78,    79,
      80,    81,    82,     8,    84,    85,    83,    84,    85,    86,
      80,    83,    84,    85,    86,    83,    84,    85,    86,    83,
      84,    85,    86,     5,     6,    80,    83,    84,    85,    86,
      12,    80,    14,    82,    27,    17,    18,    19,    20,    26,
      21,    23,    24,    26,    30,    41,    80,    13,    28,    31,
      32,    33,    27,    27,    78,    80,    37,    38,    80,    40,
      41,    43,    44,     7,    27,    34,    35,    36,    27,    51,
      39,    53,    27,    42,    27,    60,    58,    28,     4,    11,
      61,    62,    63,    64,    65,    27,    55,    28,    27,    27,
      61,    72,    80,    66,    27,    52,    80,    16,    26,    45,
       4,    80,    78,    28,    27,    77,    27,    61,    28,    61,
      26,    61,    61,    26,    26,    82,    78,    78,    28,    28,
      68,    28,    28,    28,    82,    28,    28,    28,    27,    27,
      27,    27,    27,    27,    18,    82,   330,   291,   213,   269,
     170,   260,   224,   235,   161,   307
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    14,    17,    18,    19,    20,    23,
      24,    31,    32,    33,    43,    44,    51,    53,    58,    89,
      90,    91,    92,    93,    95,    96,    97,    98,    99,   100,
     101,   102,   108,   109,   110,   111,   118,   125,   126,   129,
     130,   150,   151,   152,     8,    25,    42,    57,   106,     8,
      10,    26,    74,    75,    76,    78,    79,    80,    81,    82,
      84,    85,   123,   131,   132,   133,   134,   131,    80,     9,
      46,    48,    80,    80,    54,    90,     0,     3,   153,    80,
      10,    80,    10,    80,    80,   132,    26,    26,    26,    26,
      45,   132,    22,    80,    83,    84,    85,    86,    94,    48,
      80,    80,    51,    61,    56,    22,    26,   112,    80,   112,
      80,    52,    27,   132,   132,   132,    27,   131,   132,    80,
      85,    80,   132,   132,   132,   132,    28,    80,   135,    47,
      49,   139,    80,   127,   128,   123,    81,    80,   114,   129,
      52,   129,    52,    80,    28,    28,    28,    27,    27,   131,
      94,    26,    13,    26,   121,   132,   140,   142,   143,    61,
     139,    28,    46,    34,    35,    36,    39,    42,    55,   117,
      28,   113,    80,    80,   132,   132,   132,    28,    29,   137,
      13,    84,   120,   123,    21,    37,    38,    40,    41,    61,
      62,    63,    64,    65,    72,   144,   122,   123,   129,   144,
     144,    50,    73,   141,    13,    26,   123,   127,     8,    13,
      26,    41,   115,   114,    27,    26,    26,    27,    27,    27,
     135,    30,   139,   123,    28,   119,    41,    37,    38,    40,
      13,    26,   121,   132,    27,    28,    27,    13,    26,   132,
      13,    26,   121,   132,   140,   129,    80,    78,   116,    13,
     113,    59,   112,   124,    80,    80,    94,   135,     7,   145,
     120,    27,   129,   122,   123,   144,   129,   129,    27,    27,
      60,   129,    27,    28,   107,   137,    94,     4,    11,   147,
     119,    27,    13,    26,   121,   132,    27,    27,   115,    61,
      66,    80,    27,    52,   138,    80,   134,   146,   140,    16,
     148,   129,    80,    26,   107,   140,   137,    28,     4,    77,
     136,    27,    67,    69,    70,    71,   103,   105,   146,    74,
      75,    76,   134,   149,    78,    61,    61,    61,    61,    27,
      28,    26,    26,    26,    15,    17,    28,    68,    74,    75,
      76,   104,    78,    78,   103,    82,   134,    82,   134,    82,
     134,    28,    28,   149,    28,    28,    28,    28,    28,    28,
     149,   149,   134,    82,   134,    82,   134,    82,    27,    27,
      27,    27,    27,    27
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    91,    92,    93,    94,
      94,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   103,   104,   104,   104,   105,   105,   105,   105,   106,
     106,   107,   107,   108,   109,   110,   110,   111,   112,   112,
     113,   113,   114,   114,   115,   115,   115,   116,   117,   117,
     117,   117,   117,   117,   118,   119,   119,   120,   120,   120,
     121,   122,   122,   123,   123,   123,   123,   124,   124,   125,
     126,   127,   127,   128,   128,   128,   129,   130,   131,   131,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   133,   133,   133,   134,   134,   134,   135,
     136,   136,   137,   137,   137,   138,   138,   139,   139,   140,
     140,   140,   141,   141,   142,   142,   142,   142,   142,   142,
     142,   142,   142,   143,   143,   143,   143,   143,   143,   143,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,   144,   145,   145,   146,   146,   147,   147,
     148,   148,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   150,   151,   152,   153,   153
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     2,     1,     1,     1,     3,     2,     2,    10,    13,
       1,     3,     1,     1,     1,     3,     3,     3,     3,     0,
       1,     0,     3,     5,     8,     5,     9,     5,     0,     1,
       0,     3,     6,     3,     0,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     8,     0,     3,     1,     2,     1,
       3,     1,     3,     1,     1,     1,     1,     0,     4,     4,
       5,     1,     3,     3,     3,     5,    11,     2,     2,     4,
       1,     1,     1,     3,     3,     3,     3,     3,     2,     1,
       6,     6,     6,     4,     3,     4,     1,     3,     3,     1,
       2,     0,     0,     4,     6,     0,     2,     0,     2,     0,
       1,     3,     1,     1,     3,     5,     5,     3,     3,     5,
       5,     7,     1,     3,     3,     3,     5,     5,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     1,
       1,     2,     1,     2,     0,     3,     1,     3,     0,     2,
       0,     3,     1,     3,     6,     6,     6,     6,     6,     6,
       2,     4,     2,     4,     7,     2,     4,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (&yylloc, sql_string, sql_result, scanner, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location, sql_string, sql_result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp, sql_string, sql_result, scanner);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]), sql_string, sql_result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, sql_string, sql_result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  YY_USE (sql_string);
  YY_USE (sql_result);
  YY_USE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (const char * sql_string, ParsedSqlResult * sql_result, void * scanner)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex (&yylval, &yylloc, scanner);
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* commands: command_wrapper opt_semicolon  */
#line 262 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1961 "yacc_sql.cpp"
    break;

  case 26: /* exit_stmt: EXIT  */
#line 295 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1970 "yacc_sql.cpp"
    break;

  case 27: /* help_stmt: HELP  */
#line 301 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1978 "yacc_sql.cpp"
    break;

  case 28: /* sync_stmt: SYNC  */
#line 306 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1986 "yacc_sql.cpp"
    break;

  case 29: /* alias_stmt: %empty  */
#line 312 "yacc_sql.y"
  {
    (yyval.string) = nullptr;
  }
#line 1994 "yacc_sql.cpp"
    break;

  case 30: /* alias_stmt: ID  */
#line 316 "yacc_sql.y"
  {
    // printf("alias:%s\n", $1);
    (yyval.string) = (yyvsp[0].string);
  }
#line 2003 "yacc_sql.cpp"
    break;

  case 31: /* alias_stmt: AS ID  */
#line 320 "yacc_sql.y"
          {
    (yyval.string) = (yyvsp[0].string);
    // printf("alias:%s\n", $2);
  }
#line 2012 "yacc_sql.cpp"
    break;

  case 32: /* begin_stmt: TRX_BEGIN  */
#line 326 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 2020 "yacc_sql.cpp"
    break;

  case 33: /* commit_stmt: TRX_COMMIT  */
#line 332 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 2028 "yacc_sql.cpp"
    break;

  case 34: /* rollback_stmt: TRX_ROLLBACK  */
#line 338 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 2036 "yacc_sql.cpp"
    break;

  case 35: /* drop_table_stmt: DROP TABLE ID  */
#line 344 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2046 "yacc_sql.cpp"
    break;

  case 36: /* show_tables_stmt: SHOW TABLES  */
#line 351 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 2054 "yacc_sql.cpp"
    break;

  case 37: /* desc_table_stmt: DESC ID  */
#line 357 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2064 "yacc_sql.cpp"
    break;

  case 38: /* create_index_stmt: CREATE unique_stmt INDEX ID ON ID LBRACE ID attr_list RBRACE  */
#line 366 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_INDEX);
      CreateIndexSqlNode &create_index = (yyval.sql_node)->create_index;
      create_index.index_name = (yyvsp[-6].string);
      create_index.unique = (yyvsp[-8].boolean);
      create_index.relation_name = (yyvsp[-4].string);
      if ((yyvsp[-1].relation_list) != nullptr) {
        create_index.attribute_names.swap(*(yyvsp[-1].relation_list));
        delete (yyvsp[-1].relation_list);  
      }
      create_index.attribute_names.emplace_back((yyvsp[-2].string));
      std::reverse(create_index.attribute_names.begin(), create_index.attribute_names.end());
      free((yyvsp[-6].string));
      free((yyvsp[-4].string));
      free((yyvsp[-2].string));
    }
#line 2085 "yacc_sql.cpp"
    break;

  case 39: /* create_vector_index_stmt: CREATE VECTOR_T INDEX ID ON ID LBRACE ID RBRACE WITH_T LBRACE vi_arg_list RBRACE  */
#line 388 "yacc_sql.y"
  {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VECTOR_INDEX);
    CreateVectorIndexSqlNode &idx = (yyval.sql_node)->create_vector_index;
    idx.index_name = (yyvsp[-9].string);
    idx.relation_name = (yyvsp[-7].string);
    idx.attribute_name = (yyvsp[-5].string);
    idx.args = (yyvsp[-1].str_2_str);
    free((yyvsp[-9].string));
    free((yyvsp[-7].string));
    free((yyvsp[-5].string));
  }
#line 2101 "yacc_sql.cpp"
    break;

  case 40: /* vi_arg_list: vi_arg  */
#line 418 "yacc_sql.y"
         {
    // printf("hello\n");
    (yyval.str_2_str) = (yyvsp[0].str_2_str);
  }
#line 2110 "yacc_sql.cpp"
    break;

  case 41: /* vi_arg_list: vi_arg COMMA vi_arg_list  */
#line 422 "yacc_sql.y"
                             {
    (yyval.str_2_str) = (yyvsp[0].str_2_str);
    for (auto &pr : *((yyvsp[-2].str_2_str))) {
      (yyval.str_2_str)->insert({pr.first, pr.second});
    }
    delete (yyvsp[-2].str_2_str);
  }
#line 2122 "yacc_sql.cpp"
    break;

  case 42: /* distance_type: L2_DISTANCE  */
#line 432 "yacc_sql.y"
              {
    (yyval.number) = 1;
  }
#line 2130 "yacc_sql.cpp"
    break;

  case 43: /* distance_type: COSINE_DISTANCE  */
#line 435 "yacc_sql.y"
                   {
    (yyval.number) = 2;
  }
#line 2138 "yacc_sql.cpp"
    break;

  case 44: /* distance_type: INNER_PRODUCT  */
#line 438 "yacc_sql.y"
                  {
    (yyval.number) = 3;
  }
#line 2146 "yacc_sql.cpp"
    break;

  case 45: /* vi_arg: DISTANCE_T EQ distance_type  */
#line 444 "yacc_sql.y"
                              {
    // printf("distance\n");
    string val = ((yyvsp[0].number) == 1 ? "l2" : ((yyvsp[0].number) == 2 ? "cosine" : "inner"));
    (yyval.str_2_str) = new std::unordered_map<string, string>;
    (yyval.str_2_str)->insert({string("distance"), val});
    // delete $3;
  }
#line 2158 "yacc_sql.cpp"
    break;

  case 46: /* vi_arg: TYPE_T EQ IVFFLAT  */
#line 451 "yacc_sql.y"
                      {
    // printf("type\n");
    (yyval.str_2_str) = new std::unordered_map<string, string>;
    (yyval.str_2_str)->insert({string("type"), string("ivfflat")});
    
  }
#line 2169 "yacc_sql.cpp"
    break;

  case 47: /* vi_arg: LISTS_T EQ NUMBER  */
#line 457 "yacc_sql.y"
                      {
    // printf("list\n");
    (yyval.str_2_str) = new std::unordered_map<string, string>;
    (yyval.str_2_str)->insert({string("lists"), std::to_string((yyvsp[0].number))});
  }
#line 2179 "yacc_sql.cpp"
    break;

  case 48: /* vi_arg: PROBES_T EQ NUMBER  */
#line 462 "yacc_sql.y"
                       {
    // printf("probes\n");
    (yyval.str_2_str) = new std::unordered_map<string, string>;
    (yyval.str_2_str)->insert({string("probes"), std::to_string((yyvsp[0].number))});
  }
#line 2189 "yacc_sql.cpp"
    break;

  case 49: /* unique_stmt: %empty  */
#line 471 "yacc_sql.y"
  {
    (yyval.boolean) = false;
  }
#line 2197 "yacc_sql.cpp"
    break;

  case 50: /* unique_stmt: UNIQUE  */
#line 474 "yacc_sql.y"
           {
    (yyval.boolean) = true;
  }
#line 2205 "yacc_sql.cpp"
    break;

  case 51: /* attr_list: %empty  */
#line 479 "yacc_sql.y"
  {
    (yyval.relation_list) = nullptr;
  }
#line 2213 "yacc_sql.cpp"
    break;

  case 52: /* attr_list: COMMA ID attr_list  */
#line 482 "yacc_sql.y"
                       {
    if ((yyvsp[0].relation_list) != nullptr) {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    } else {
      (yyval.relation_list) = new vector<std::string>;
    }
    (yyval.relation_list)->emplace_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 2227 "yacc_sql.cpp"
    break;

  case 53: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 494 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2239 "yacc_sql.cpp"
    break;

  case 54: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 504 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE);
      CreateTableSqlNode &create_table = (yyval.sql_node)->create_table;
      create_table.relation_name = (yyvsp[-5].string);
      free((yyvsp[-5].string));

      std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-2].attr_infos);

      if (src_attrs != nullptr) {
        create_table.attr_infos.swap(*src_attrs);
        delete src_attrs;
      }
      create_table.attr_infos.emplace_back(*(yyvsp[-3].attr_info));
      std::reverse(create_table.attr_infos.begin(), create_table.attr_infos.end());
      delete (yyvsp[-3].attr_info);
      if ((yyvsp[0].string) != nullptr) {
        create_table.storage_format = (yyvsp[0].string);
        free((yyvsp[0].string));
      }
    }
#line 2264 "yacc_sql.cpp"
    break;

  case 55: /* create_select_stmt: CREATE TABLE ID as_stmt select_stmt  */
#line 526 "yacc_sql.y"
                                        {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
    auto &table = (yyval.sql_node)->create_table_select;
    table.relation_name =string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    table.has_schema = false;
    table.query = (yyvsp[0].sql_node);
  }
#line 2277 "yacc_sql.cpp"
    break;

  case 56: /* create_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_stmt select_stmt  */
#line 534 "yacc_sql.y"
                                                                             {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
    auto &table = (yyval.sql_node)->create_table_select;
    table.relation_name =string((yyvsp[-6].string));
    free((yyvsp[-6].string));
    table.has_schema = true;

    std::vector<AttrInfoSqlNode> *src_attrs = (yyvsp[-3].attr_infos);

    if (src_attrs != nullptr) {
      table.attr_infos.swap(*src_attrs);
      delete src_attrs;
    }
    table.attr_infos.emplace_back(*(yyvsp[-4].attr_info));
    delete (yyvsp[-4].attr_info);
    std::reverse(table.attr_infos.begin(), table.attr_infos.end());
    table.query = (yyvsp[0].sql_node);
  }
#line 2300 "yacc_sql.cpp"
    break;

  case 57: /* create_view_stmt: CREATE VIEW ID as_stmt select_stmt  */
#line 554 "yacc_sql.y"
                                       {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
    auto &view = (yyval.sql_node)->create_view;
    view.view_name =string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    view.query = (yyvsp[0].sql_node);
  }
#line 2312 "yacc_sql.cpp"
    break;

  case 58: /* as_stmt: %empty  */
#line 563 "yacc_sql.y"
  {
    (yyval.boolean) = false;
  }
#line 2320 "yacc_sql.cpp"
    break;

  case 59: /* as_stmt: AS  */
#line 566 "yacc_sql.y"
       {
    (yyval.boolean) = true;
  }
#line 2328 "yacc_sql.cpp"
    break;

  case 60: /* attr_def_list: %empty  */
#line 572 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2336 "yacc_sql.cpp"
    break;

  case 61: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 576 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2350 "yacc_sql.cpp"
    break;

  case 62: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 589 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-4].number);
      (yyval.attr_info)->name = (yyvsp[-5].string);
      if ((yyval.attr_info)->type == AttrType::VECTORS) {  // 检查类型是否为 vector_type
          (yyval.attr_info)->length = 4 * (yyvsp[-2].number);
      } else {
          (yyval.attr_info)->length = (yyvsp[-2].number);
      }
      free((yyvsp[-5].string));
      (yyval.attr_info)->nullable = ((yyvsp[0].number) == 1);
    }
#line 2367 "yacc_sql.cpp"
    break;

  case 63: /* attr_def: ID type null_def  */
#line 602 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-2].string));
      (yyval.attr_info)->nullable = ((yyvsp[0].number) == 1);
    }
#line 2380 "yacc_sql.cpp"
    break;

  case 64: /* null_def: %empty  */
#line 613 "yacc_sql.y"
  { // 默認是可以爲null的
    (yyval.number) = 1;
  }
#line 2388 "yacc_sql.cpp"
    break;

  case 65: /* null_def: null  */
#line 616 "yacc_sql.y"
         {
    (yyval.number) = 1;
  }
#line 2396 "yacc_sql.cpp"
    break;

  case 66: /* null_def: NOT null  */
#line 619 "yacc_sql.y"
             {
    (yyval.number) = 0;
  }
#line 2404 "yacc_sql.cpp"
    break;

  case 67: /* number: NUMBER  */
#line 623 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2410 "yacc_sql.cpp"
    break;

  case 68: /* type: INT_T  */
#line 626 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2416 "yacc_sql.cpp"
    break;

  case 69: /* type: STRING_T  */
#line 627 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2422 "yacc_sql.cpp"
    break;

  case 70: /* type: FLOAT_T  */
#line 628 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2428 "yacc_sql.cpp"
    break;

  case 71: /* type: DATE_T  */
#line 629 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2434 "yacc_sql.cpp"
    break;

  case 72: /* type: VECTOR_T  */
#line 630 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2440 "yacc_sql.cpp"
    break;

  case 73: /* type: TEXT_T  */
#line 631 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2446 "yacc_sql.cpp"
    break;

  case 74: /* insert_stmt: INSERT INTO ID VALUES LBRACE insert_val value_list RBRACE  */
#line 635 "yacc_sql.y"
  {
    (yyval.sql_node) = new ParsedSqlNode(SCF_INSERT);
    (yyval.sql_node)->insertion.relation_name = (yyvsp[-5].string);
    if ((yyvsp[-1].value_list) != nullptr) {
      (yyval.sql_node)->insertion.values.swap(*(yyvsp[-1].value_list));
      delete (yyvsp[-1].value_list);
    }
    (yyval.sql_node)->insertion.values.emplace_back(*(yyvsp[-2].value));
    std::reverse((yyval.sql_node)->insertion.values.begin(), (yyval.sql_node)->insertion.values.end());
    delete (yyvsp[-2].value);
    free((yyvsp[-5].string));
  }
#line 2463 "yacc_sql.cpp"
    break;

  case 75: /* value_list: %empty  */
#line 653 "yacc_sql.y"
  {
    (yyval.value_list) = nullptr;
  }
#line 2471 "yacc_sql.cpp"
    break;

  case 76: /* value_list: COMMA insert_val value_list  */
#line 656 "yacc_sql.y"
                                 { 
    if ((yyvsp[0].value_list) != nullptr) {
      (yyval.value_list) = (yyvsp[0].value_list);
    } else {
      (yyval.value_list) = new std::vector<Value>;
    }
    (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
    delete (yyvsp[-1].value);
  }
#line 2485 "yacc_sql.cpp"
    break;

  case 77: /* insert_val: value  */
#line 667 "yacc_sql.y"
         {
    (yyval.value) = (yyvsp[0].value);
  }
#line 2493 "yacc_sql.cpp"
    break;

  case 78: /* insert_val: '-' value  */
#line 670 "yacc_sql.y"
              {
    (yyval.value) = (yyvsp[0].value);
    if ((yyval.value)->attr_type() == AttrType::INTS) {
      (yyval.value)->set_int((yyval.value)->get_int() *(-1));
    } else if ((yyval.value)->attr_type() == AttrType::FLOATS) {
      (yyval.value)->set_float((yyval.value)->get_float() *(-1));
    }
  }
#line 2506 "yacc_sql.cpp"
    break;

  case 79: /* insert_val: null  */
#line 678 "yacc_sql.y"
         {
    (yyval.value) = new Value;
    (yyval.value)->set_null();
  }
#line 2515 "yacc_sql.cpp"
    break;

  case 80: /* const_value_list_expr: LBRACE const_value_list RBRACE  */
#line 685 "yacc_sql.y"
                                 {
    (yyval.expression) = new ConstantValueListExpr((yyvsp[-1].const_value_list_type));
    delete (yyvsp[-1].const_value_list_type);
  }
#line 2524 "yacc_sql.cpp"
    break;

  case 81: /* const_value_list: value  */
#line 691 "yacc_sql.y"
        {
    ////cout << $1->get_int() << endl;
    (yyval.const_value_list_type) = new vector<Value*>();
    (yyval.const_value_list_type)->emplace_back((yyvsp[0].value));
  }
#line 2534 "yacc_sql.cpp"
    break;

  case 82: /* const_value_list: value COMMA const_value_list  */
#line 696 "yacc_sql.y"
                                 {
    (yyval.const_value_list_type) = (yyvsp[0].const_value_list_type);
    (yyval.const_value_list_type)->emplace_back((yyvsp[-2].value));
  }
#line 2543 "yacc_sql.cpp"
    break;

  case 83: /* value: NUMBER  */
#line 702 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2552 "yacc_sql.cpp"
    break;

  case 84: /* value: FLOAT  */
#line 706 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 85: /* value: SSS  */
#line 710 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2572 "yacc_sql.cpp"
    break;

  case 86: /* value: VECTOR_DATA  */
#line 716 "yacc_sql.y"
                  {
      // 这里我们已经在词法分析阶段解析并获得了 std::vector<float> 指针
      Value *value = new Value();

      // 设置 vector 数据，假设 $1 是 std::vector<float> 指针
      if ((yyvsp[0].vector) != nullptr) {
          // 获取底层的 float* 数组指针以及元素个数
          float* vector_data = (yyvsp[0].vector)->data();      // 获取底层的 float* 指针
          size_t vector_size = (yyvsp[0].vector)->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          value->set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete (yyvsp[0].vector);
      } else {
          // yyerror(&@$, NULL, sql_result, scanner, "vector data invalid", SCF_VECTOR);
          YYABORT;  // 停止解析
      }

      (yyval.value) = value;  // 将结果赋值给解析树
    }
#line 2599 "yacc_sql.cpp"
    break;

  case 87: /* storage_format: %empty  */
#line 740 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2607 "yacc_sql.cpp"
    break;

  case 88: /* storage_format: STORAGE FORMAT EQ ID  */
#line 744 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2615 "yacc_sql.cpp"
    break;

  case 89: /* delete_stmt: DELETE FROM ID where  */
#line 751 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2628 "yacc_sql.cpp"
    break;

  case 90: /* update_stmt: UPDATE ID SET assignment_list where  */
#line 762 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_UPDATE);
      (yyval.sql_node)->update.relation_name = (yyvsp[-3].string);
      std::reverse((yyvsp[-1].assignment_ptr_list)->begin(),(yyvsp[-1].assignment_ptr_list)->end());
      (yyval.sql_node)->update.assignments = (yyvsp[-1].assignment_ptr_list);
      // TODO 
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->update.conditions= (yyvsp[0].condition_list);
      }
      free((yyvsp[-3].string));
    }
#line 2644 "yacc_sql.cpp"
    break;

  case 91: /* assignment_list: assignment  */
#line 776 "yacc_sql.y"
             {
    (yyval.assignment_ptr_list) = new vector<Assignment*>();
    (yyval.assignment_ptr_list)->emplace_back((yyvsp[0].assignment_ptr));
  }
#line 2653 "yacc_sql.cpp"
    break;

  case 92: /* assignment_list: assignment COMMA assignment_list  */
#line 780 "yacc_sql.y"
                                     {
    (yyval.assignment_ptr_list) = (yyvsp[0].assignment_ptr_list);
    (yyval.assignment_ptr_list)->emplace_back((yyvsp[-2].assignment_ptr));
  }
#line 2662 "yacc_sql.cpp"
    break;

  case 93: /* assignment: ID EQ value  */
#line 786 "yacc_sql.y"
              {
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    (yyval.assignment_ptr)->right_hand_side = new ValueExpr(*(yyvsp[0].value));
    delete (yyvsp[0].value);
  }
#line 2674 "yacc_sql.cpp"
    break;

  case 94: /* assignment: ID EQ null  */
#line 793 "yacc_sql.y"
               {
    Value v;
    v.set_null();
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    (yyval.assignment_ptr)->right_hand_side = new ValueExpr(v);
  }
#line 2687 "yacc_sql.cpp"
    break;

  case 95: /* assignment: ID EQ LBRACE select_stmt RBRACE  */
#line 801 "yacc_sql.y"
                                   {
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-4].string));
    free((yyvsp[-4].string));
    (yyval.assignment_ptr)->right_hand_side = new SubQueryExpr((yyvsp[-1].sql_node));
  }
#line 2698 "yacc_sql.cpp"
    break;

  case 96: /* select_stmt: SELECT expression_list FROM relation alias_stmt rel_list where group_by having_stmt order_by limit_opt  */
#line 812 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      auto &selection = (yyval.sql_node)->selection;
      // select
      selection.limit = (yyvsp[0].number);
      if ((yyvsp[-9].expression_list) != nullptr) {
        selection.expressions.swap(*(yyvsp[-9].expression_list));
        delete (yyvsp[-9].expression_list);
      }
      // from
      
      auto r = new rel_info;
      r->relation_name = (yyvsp[-7].string);
      if ((yyvsp[-6].string)) {
        r->relation_alias = (yyvsp[-6].string);
        free((yyvsp[-6].string));
      }
      selection.relations.emplace_back(r);
      if ((yyvsp[-5].rel_list_type) != nullptr) {
        for(auto iter = (yyvsp[-5].rel_list_type)->rbegin(); iter != (yyvsp[-5].rel_list_type)->rend(); ++iter) {
          selection.relations.emplace_back(*iter);
          (*iter) = nullptr;
        }
        // // printf("size:%ld.%s\n",selection.relations.size(),selection.relations[0].relation_name.c_str());
      }
      free((yyvsp[-7].string));
      // // printf("and flag:%d\n", and_flag);
      selection.and_flag = and_flag;
      // where 
      if ((yyvsp[-4].condition_list) != nullptr) {
        selection.conditions = (yyvsp[-4].condition_list);
      }
    
      if ((yyvsp[-3].expression_list) != nullptr) {
        selection.group_by = (yyvsp[-3].expression_list);
      }
      if ((yyvsp[-2].condition_list) != nullptr) {
        selection.having = (yyvsp[-2].condition_list);
      }
      if ((yyvsp[-1].order_by_list) != nullptr) {
        selection.order_by = (yyvsp[-1].order_by_list);
      }
    }
#line 2746 "yacc_sql.cpp"
    break;

  case 97: /* calc_stmt: CALC expression_list  */
#line 858 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2756 "yacc_sql.cpp"
    break;

  case 98: /* expression_list: expression alias_stmt  */
#line 867 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if ((yyvsp[0].string)) {
        if ((yyvsp[-1].expression)->type() == ExprType::STAR ) {
          YYERROR;
        }
        (yyvsp[-1].expression)->set_alias(std::string((yyvsp[0].string)));
        // printf("alias:%s\n", $2);
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 99: /* expression_list: expression alias_stmt COMMA expression_list  */
#line 880 "yacc_sql.y"
    {
      if ((yyvsp[0].expression_list) != nullptr) {
        (yyval.expression_list) = (yyvsp[0].expression_list);
      } else {
        (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      }
      if ((yyvsp[-2].string)) {
        (yyvsp[-3].expression)->set_alias(std::string((yyvsp[-2].string)));
        free((yyvsp[-2].string));
      }
      (yyval.expression_list)->emplace((yyval.expression_list)->begin(), (yyvsp[-3].expression));
    }
#line 2790 "yacc_sql.cpp"
    break;

  case 100: /* expression: value  */
#line 894 "yacc_sql.y"
          {
      //cout << "value_expr\n";
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2801 "yacc_sql.cpp"
    break;

  case 101: /* expression: rel_attr  */
#line 900 "yacc_sql.y"
               {
      //cout << "field_expr\n";
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2813 "yacc_sql.cpp"
    break;

  case 102: /* expression: '*'  */
#line 907 "yacc_sql.y"
          {
      // printf("star expression\n");
      (yyval.expression) = new StarExpr();
    }
#line 2822 "yacc_sql.cpp"
    break;

  case 103: /* expression: expression '+' expression  */
#line 911 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2830 "yacc_sql.cpp"
    break;

  case 104: /* expression: expression '-' expression  */
#line 914 "yacc_sql.y"
                                {
      //cout << "minus\n";
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2839 "yacc_sql.cpp"
    break;

  case 105: /* expression: expression '*' expression  */
#line 918 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2847 "yacc_sql.cpp"
    break;

  case 106: /* expression: expression '/' expression  */
#line 921 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2855 "yacc_sql.cpp"
    break;

  case 107: /* expression: LBRACE expression RBRACE  */
#line 924 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 108: /* expression: '-' expression  */
#line 928 "yacc_sql.y"
                                  {
      //cout << "negative\n";
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2873 "yacc_sql.cpp"
    break;

  case 109: /* expression: aggr_func_expr  */
#line 933 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 110: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 936 "yacc_sql.y"
                                                            {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2889 "yacc_sql.cpp"
    break;

  case 111: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 939 "yacc_sql.y"
                                                              {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2897 "yacc_sql.cpp"
    break;

  case 112: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 942 "yacc_sql.y"
                                                                {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2905 "yacc_sql.cpp"
    break;

  case 113: /* aggr_func_expr: ID LBRACE expression RBRACE  */
#line 953 "yacc_sql.y"
                              {
    (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression), sql_string, &(yyloc));
    free((yyvsp[-3].string));
  }
#line 2914 "yacc_sql.cpp"
    break;

  case 114: /* aggr_func_expr: ID LBRACE RBRACE  */
#line 957 "yacc_sql.y"
                     {
    free((yyvsp[-2].string));
    YYERROR;
  }
#line 2923 "yacc_sql.cpp"
    break;

  case 115: /* aggr_func_expr: ID LBRACE expression_list RBRACE  */
#line 961 "yacc_sql.y"
                                     {
    delete (yyvsp[-1].expression_list);
    free((yyvsp[-3].string));
    YYERROR;
  }
#line 2933 "yacc_sql.cpp"
    break;

  case 116: /* rel_attr: ID  */
#line 969 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      // printf("attr_name:%s\n",$1);
      free((yyvsp[0].string));
    }
#line 2944 "yacc_sql.cpp"
    break;

  case 117: /* rel_attr: ID DOT ID  */
#line 975 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2956 "yacc_sql.cpp"
    break;

  case 118: /* rel_attr: ID DOT '*'  */
#line 982 "yacc_sql.y"
                 {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = "*";
      free((yyvsp[-2].string));
    }
#line 2967 "yacc_sql.cpp"
    break;

  case 119: /* relation: ID  */
#line 991 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
      // printf("relation:%s\n",$1);
    }
#line 2976 "yacc_sql.cpp"
    break;

  case 120: /* limit_opt: LIMIT_T NUMBER  */
#line 997 "yacc_sql.y"
                      { (yyval.number) = (yyvsp[0].number); }
#line 2982 "yacc_sql.cpp"
    break;

  case 121: /* limit_opt: %empty  */
#line 998 "yacc_sql.y"
                      { (yyval.number) = -1; }
#line 2988 "yacc_sql.cpp"
    break;

  case 122: /* rel_list: %empty  */
#line 1001 "yacc_sql.y"
              {
    (yyval.rel_list_type) = nullptr;
  }
#line 2996 "yacc_sql.cpp"
    break;

  case 123: /* rel_list: COMMA relation alias_stmt rel_list  */
#line 1004 "yacc_sql.y"
                                       {
    (yyval.rel_list_type) = ((yyvsp[0].rel_list_type) != nullptr ? (yyvsp[0].rel_list_type) : new std::vector<rel_info*>());
  
    auto r = new rel_info;
    r->relation_name = string( (yyvsp[-2].string));
    // printf("rel name:%s.\n", $2);
    if ((yyvsp[-1].string)) {
      r->relation_alias = std::string((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
    (yyval.rel_list_type)->emplace_back(r);
    free((yyvsp[-2].string));
  }
#line 3014 "yacc_sql.cpp"
    break;

  case 124: /* rel_list: INNER JOIN relation alias_stmt on_stmt rel_list  */
#line 1017 "yacc_sql.y"
                                                    {
    (yyval.rel_list_type) = ((yyvsp[0].rel_list_type) != nullptr ? (yyvsp[0].rel_list_type) : new std::vector<rel_info*>());
    auto r = new rel_info;
    r->relation_name = (yyvsp[-3].string);
    free((yyvsp[-3].string));
    if ((yyvsp[-2].string)) {
      r->relation_alias = std::string((yyvsp[-2].string));
      free((yyvsp[-2].string));
    }
    if ((yyvsp[-1].condition_list)) {
      // printf("has on conditions\n");
      r->on_conditions = (yyvsp[-1].condition_list);
    }
    (yyval.rel_list_type)->emplace_back(r);
  }
#line 3034 "yacc_sql.cpp"
    break;

  case 125: /* on_stmt: %empty  */
#line 1035 "yacc_sql.y"
              {
    // cross product
    (yyval.condition_list) = nullptr;
  }
#line 3043 "yacc_sql.cpp"
    break;

  case 126: /* on_stmt: ON condition_list  */
#line 1039 "yacc_sql.y"
                      {
    (yyval.condition_list) = (yyvsp[0].condition_list);
  }
#line 3051 "yacc_sql.cpp"
    break;

  case 127: /* where: %empty  */
#line 1046 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3059 "yacc_sql.cpp"
    break;

  case 128: /* where: WHERE condition_list  */
#line 1049 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 3067 "yacc_sql.cpp"
    break;

  case 129: /* condition_list: %empty  */
#line 1055 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 130: /* condition_list: condition  */
#line 1058 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<Expression*>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
      // delete $1;
    }
#line 3085 "yacc_sql.cpp"
    break;

  case 131: /* condition_list: condition and_clause condition_list  */
#line 1063 "yacc_sql.y"
                                          {
      //TODO
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
      // delete $1;
    }
#line 3096 "yacc_sql.cpp"
    break;

  case 132: /* and_clause: AND  */
#line 1071 "yacc_sql.y"
      {
    (yyval.boolean) = true;
  }
#line 3104 "yacc_sql.cpp"
    break;

  case 133: /* and_clause: OR  */
#line 1074 "yacc_sql.y"
       {
    (yyval.boolean) = false;
    and_flag = 0;
  }
#line 3113 "yacc_sql.cpp"
    break;

  case 134: /* condition: expression comp_op expression  */
#line 1079 "yacc_sql.y"
                                  {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3123 "yacc_sql.cpp"
    break;

  case 135: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 1085 "yacc_sql.y"
                                                 {
      std::unique_ptr<Expression> left((yyvsp[-4].expression));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 3133 "yacc_sql.cpp"
    break;

  case 136: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 1090 "yacc_sql.y"
                                                   {
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-3].sql_node)));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3143 "yacc_sql.cpp"
    break;

  case 137: /* condition: expression comp_op const_value_list_expr  */
#line 1095 "yacc_sql.y"
                                               {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));

      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3154 "yacc_sql.cpp"
    break;

  case 138: /* condition: const_value_list_expr comp_op expression  */
#line 1101 "yacc_sql.y"
                                               {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3164 "yacc_sql.cpp"
    break;

  case 139: /* condition: LBRACE select_stmt RBRACE comp_op const_value_list_expr  */
#line 1106 "yacc_sql.y"
                                                              {
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-3].sql_node)));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3174 "yacc_sql.cpp"
    break;

  case 140: /* condition: const_value_list_expr comp_op LBRACE select_stmt RBRACE  */
#line 1111 "yacc_sql.y"
                                                              {
      std::unique_ptr<Expression> left((yyvsp[-4].expression));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 3184 "yacc_sql.cpp"
    break;

  case 141: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 1116 "yacc_sql.y"
                                                                  {
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-5].sql_node)));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 3194 "yacc_sql.cpp"
    break;

  case 142: /* condition: null_condition  */
#line 1121 "yacc_sql.y"
                     {
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 3202 "yacc_sql.cpp"
    break;

  case 143: /* null_condition: expression comp_op null  */
#line 1127 "yacc_sql.y"
                          {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value v;
      v.set_null();
      std::unique_ptr<Expression> right(new ValueExpr(v));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3214 "yacc_sql.cpp"
    break;

  case 144: /* null_condition: null comp_op expression  */
#line 1134 "yacc_sql.y"
                              {
      Value v;
      v.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3226 "yacc_sql.cpp"
    break;

  case 145: /* null_condition: null comp_op null  */
#line 1141 "yacc_sql.y"
                        {
      Value v;
      v.set_null();
      Value v2;
      v2.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v));
      std::unique_ptr<Expression> right(new ValueExpr(v2));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3240 "yacc_sql.cpp"
    break;

  case 146: /* null_condition: LBRACE select_stmt RBRACE comp_op null  */
#line 1150 "yacc_sql.y"
                                             {
      Value v2;
      v2.set_null();
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-3].sql_node)));
      std::unique_ptr<Expression> right(new ValueExpr(v2));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3252 "yacc_sql.cpp"
    break;

  case 147: /* null_condition: null comp_op LBRACE select_stmt RBRACE  */
#line 1157 "yacc_sql.y"
                                             {
      Value v1;
      v1.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v1));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 3264 "yacc_sql.cpp"
    break;

  case 148: /* null_condition: null comp_op const_value_list_expr  */
#line 1165 "yacc_sql.y"
                                         {
      Value v1;
      v1.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v1));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3276 "yacc_sql.cpp"
    break;

  case 149: /* null_condition: const_value_list_expr comp_op null  */
#line 1172 "yacc_sql.y"
                                         {
      Value v2;
      v2.set_null();
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right(new ValueExpr(v2));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3288 "yacc_sql.cpp"
    break;

  case 150: /* comp_op: EQ  */
#line 1198 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3294 "yacc_sql.cpp"
    break;

  case 151: /* comp_op: LT  */
#line 1199 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3300 "yacc_sql.cpp"
    break;

  case 152: /* comp_op: GT  */
#line 1200 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3306 "yacc_sql.cpp"
    break;

  case 153: /* comp_op: LE  */
#line 1201 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3312 "yacc_sql.cpp"
    break;

  case 154: /* comp_op: GE  */
#line 1202 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3318 "yacc_sql.cpp"
    break;

  case 155: /* comp_op: NE  */
#line 1203 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3324 "yacc_sql.cpp"
    break;

  case 156: /* comp_op: LIKE  */
#line 1204 "yacc_sql.y"
           { (yyval.comp) = LK;}
#line 3330 "yacc_sql.cpp"
    break;

  case 157: /* comp_op: NOT LIKE  */
#line 1205 "yacc_sql.y"
               { (yyval.comp) = NOT_LK;}
#line 3336 "yacc_sql.cpp"
    break;

  case 158: /* comp_op: IS NOT  */
#line 1206 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_NULL;}
#line 3342 "yacc_sql.cpp"
    break;

  case 159: /* comp_op: IS  */
#line 1207 "yacc_sql.y"
          { (yyval.comp) = IS_NULL;}
#line 3348 "yacc_sql.cpp"
    break;

  case 160: /* comp_op: IN  */
#line 1208 "yacc_sql.y"
          { (yyval.comp) = IN_OP;}
#line 3354 "yacc_sql.cpp"
    break;

  case 161: /* comp_op: NOT IN  */
#line 1209 "yacc_sql.y"
              { (yyval.comp) = NOT_IN;}
#line 3360 "yacc_sql.cpp"
    break;

  case 162: /* comp_op: EXISTS  */
#line 1210 "yacc_sql.y"
              { (yyval.comp) = EXISTS_OP;}
#line 3366 "yacc_sql.cpp"
    break;

  case 163: /* comp_op: NOT EXISTS  */
#line 1211 "yacc_sql.y"
                  { (yyval.comp) = NOT_EXISTS;}
#line 3372 "yacc_sql.cpp"
    break;

  case 164: /* group_by: %empty  */
#line 1217 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3380 "yacc_sql.cpp"
    break;

  case 165: /* group_by: GROUP BY rel_attrs  */
#line 1220 "yacc_sql.y"
                         {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3388 "yacc_sql.cpp"
    break;

  case 166: /* rel_attrs: rel_attr  */
#line 1226 "yacc_sql.y"
           {
    // std::vector<std::unique_ptr<Expression>> *
    auto field = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name);
    (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>();
    (yyval.expression_list)->emplace_back(field);
  }
#line 3399 "yacc_sql.cpp"
    break;

  case 167: /* rel_attrs: rel_attr COMMA rel_attrs  */
#line 1232 "yacc_sql.y"
                             {
    (yyval.expression_list) = (yyvsp[0].expression_list);
    auto field = new UnboundFieldExpr((yyvsp[-2].rel_attr)->relation_name,(yyvsp[-2].rel_attr)->attribute_name);
    (yyval.expression_list)->emplace_back(field);
    delete (yyvsp[-2].rel_attr);
  }
#line 3410 "yacc_sql.cpp"
    break;

  case 168: /* having_stmt: %empty  */
#line 1240 "yacc_sql.y"
                {
      (yyval.condition_list) = nullptr;
    }
#line 3418 "yacc_sql.cpp"
    break;

  case 169: /* having_stmt: HAVING condition_list  */
#line 1243 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3426 "yacc_sql.cpp"
    break;

  case 170: /* order_by: %empty  */
#line 1281 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3434 "yacc_sql.cpp"
    break;

  case 171: /* order_by: ORDER BY order_list  */
#line 1284 "yacc_sql.y"
                          {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3442 "yacc_sql.cpp"
    break;

  case 172: /* order_list: rel_attr  */
#line 1289 "yacc_sql.y"
           {
    //std:://cout << "[1]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[0].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[0].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[0].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3457 "yacc_sql.cpp"
    break;

  case 173: /* order_list: rel_attr COMMA order_list  */
#line 1299 "yacc_sql.y"
                              {
    //std:://cout << "[2]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-2].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-2].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-2].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3472 "yacc_sql.cpp"
    break;

  case 174: /* order_list: L2_DISTANCE LBRACE rel_attr COMMA VECTOR_DATA RBRACE  */
#line 1309 "yacc_sql.y"
                                                         {
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = true;
    float* vector_data = (yyvsp[-1].vector)->data();      // 获取底层的 float* 指针
          size_t vector_size = (yyvsp[-1].vector)->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          node.base_vector.set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete (yyvsp[-1].vector);
    node.distance_type = 1;
    delete (yyvsp[-3].rel_attr);

    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3496 "yacc_sql.cpp"
    break;

  case 175: /* order_list: INNER_PRODUCT LBRACE rel_attr COMMA VECTOR_DATA RBRACE  */
#line 1328 "yacc_sql.y"
                                                           {
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = true;
    float* vector_data = (yyvsp[-1].vector)->data();      // 获取底层的 float* 指针
          size_t vector_size = (yyvsp[-1].vector)->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          node.base_vector.set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete (yyvsp[-1].vector);
    node.distance_type = 2;
    delete (yyvsp[-3].rel_attr);

    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3520 "yacc_sql.cpp"
    break;

  case 176: /* order_list: COSINE_DISTANCE LBRACE rel_attr COMMA VECTOR_DATA RBRACE  */
#line 1347 "yacc_sql.y"
                                                             {
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = true;
    float* vector_data = (yyvsp[-1].vector)->data();      // 获取底层的 float* 指针
          size_t vector_size = (yyvsp[-1].vector)->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          node.base_vector.set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete (yyvsp[-1].vector);
    node.distance_type = 3;
    delete (yyvsp[-3].rel_attr);

    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3544 "yacc_sql.cpp"
    break;

  case 177: /* order_list: L2_DISTANCE LBRACE VECTOR_DATA COMMA rel_attr RBRACE  */
#line 1366 "yacc_sql.y"
                                                         {
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = true;
    float* vector_data = (yyvsp[-3].vector)->data();      // 获取底层的 float* 指针
          size_t vector_size = (yyvsp[-3].vector)->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          node.base_vector.set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete (yyvsp[-3].vector);
    node.distance_type = 1;
    delete (yyvsp[-1].rel_attr);

    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3568 "yacc_sql.cpp"
    break;

  case 178: /* order_list: INNER_PRODUCT LBRACE VECTOR_DATA COMMA rel_attr RBRACE  */
#line 1385 "yacc_sql.y"
                                                           {
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = true;
    float* vector_data = (yyvsp[-3].vector)->data();      // 获取底层的 float* 指针
          size_t vector_size = (yyvsp[-3].vector)->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          node.base_vector.set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete (yyvsp[-3].vector);
    node.distance_type = 2;
    delete (yyvsp[-1].rel_attr);

    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3592 "yacc_sql.cpp"
    break;

  case 179: /* order_list: COSINE_DISTANCE LBRACE VECTOR_DATA COMMA rel_attr RBRACE  */
#line 1404 "yacc_sql.y"
                                                             {
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = true;
    float* vector_data = (yyvsp[-3].vector)->data();      // 获取底层的 float* 指针
          size_t vector_size = (yyvsp[-3].vector)->size();      // 获取元素个数

          // 将 float* 数组指针和大小传递给 set_vector
          node.base_vector.set_vector(vector_data, vector_size * sizeof(float));

          // 释放 std::vector<float> 指针的内存
          delete (yyvsp[-3].vector);
    node.distance_type = 3;
    delete (yyvsp[-1].rel_attr);

    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3616 "yacc_sql.cpp"
    break;

  case 180: /* order_list: rel_attr ASC  */
#line 1423 "yacc_sql.y"
                 {
    //std:://cout << "[3]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3631 "yacc_sql.cpp"
    break;

  case 181: /* order_list: rel_attr ASC COMMA order_list  */
#line 1433 "yacc_sql.y"
                                  {
    //std:://cout << "[4]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-3].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3646 "yacc_sql.cpp"
    break;

  case 182: /* order_list: rel_attr DESC  */
#line 1443 "yacc_sql.y"
                  {
    //std:://cout << "[5]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = false;
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
    // std::cout << (*$$)[0].attribute_name << '\n';
  }
#line 3662 "yacc_sql.cpp"
    break;

  case 183: /* order_list: rel_attr DESC COMMA order_list  */
#line 1454 "yacc_sql.y"
                                   {
    //std:://cout << "[6]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = false;
    delete (yyvsp[-3].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3677 "yacc_sql.cpp"
    break;

  case 184: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1481 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3691 "yacc_sql.cpp"
    break;

  case 185: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1494 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3700 "yacc_sql.cpp"
    break;

  case 186: /* set_variable_stmt: SET ID EQ value  */
#line 1502 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3712 "yacc_sql.cpp"
    break;


#line 3716 "yacc_sql.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (&yylloc, sql_string, sql_result, scanner, yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (&yylloc, sql_string, sql_result, scanner, YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc, sql_string, sql_result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp, sql_string, sql_result, scanner);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 1514 "yacc_sql.y"

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
