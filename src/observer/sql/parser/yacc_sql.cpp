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


#line 125 "yacc_sql.cpp"

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
  YYSYMBOL_ALIAS = 15,                     /* ALIAS  */
  YYSYMBOL_ASC = 16,                       /* ASC  */
  YYSYMBOL_ORDER = 17,                     /* ORDER  */
  YYSYMBOL_DESC = 18,                      /* DESC  */
  YYSYMBOL_SHOW = 19,                      /* SHOW  */
  YYSYMBOL_SYNC = 20,                      /* SYNC  */
  YYSYMBOL_INSERT = 21,                    /* INSERT  */
  YYSYMBOL_IS = 22,                        /* IS  */
  YYSYMBOL_AS = 23,                        /* AS  */
  YYSYMBOL_DELETE = 24,                    /* DELETE  */
  YYSYMBOL_UPDATE = 25,                    /* UPDATE  */
  YYSYMBOL_UNIQUE = 26,                    /* UNIQUE  */
  YYSYMBOL_LBRACE = 27,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 28,                    /* RBRACE  */
  YYSYMBOL_COMMA = 29,                     /* COMMA  */
  YYSYMBOL_INNER = 30,                     /* INNER  */
  YYSYMBOL_JOIN = 31,                      /* JOIN  */
  YYSYMBOL_TRX_BEGIN = 32,                 /* TRX_BEGIN  */
  YYSYMBOL_TRX_COMMIT = 33,                /* TRX_COMMIT  */
  YYSYMBOL_TRX_ROLLBACK = 34,              /* TRX_ROLLBACK  */
  YYSYMBOL_INT_T = 35,                     /* INT_T  */
  YYSYMBOL_STRING_T = 36,                  /* STRING_T  */
  YYSYMBOL_FLOAT_T = 37,                   /* FLOAT_T  */
  YYSYMBOL_IN = 38,                        /* IN  */
  YYSYMBOL_EXISTS = 39,                    /* EXISTS  */
  YYSYMBOL_DATE_T = 40,                    /* DATE_T  */
  YYSYMBOL_LIKE = 41,                      /* LIKE  */
  YYSYMBOL_NOT = 42,                       /* NOT  */
  YYSYMBOL_VECTOR_T = 43,                  /* VECTOR_T  */
  YYSYMBOL_HELP = 44,                      /* HELP  */
  YYSYMBOL_EXIT = 45,                      /* EXIT  */
  YYSYMBOL_DOT = 46,                       /* DOT  */
  YYSYMBOL_INTO = 47,                      /* INTO  */
  YYSYMBOL_VALUES = 48,                    /* VALUES  */
  YYSYMBOL_FROM = 49,                      /* FROM  */
  YYSYMBOL_WHERE = 50,                     /* WHERE  */
  YYSYMBOL_AND = 51,                       /* AND  */
  YYSYMBOL_SET = 52,                       /* SET  */
  YYSYMBOL_ON = 53,                        /* ON  */
  YYSYMBOL_LOAD = 54,                      /* LOAD  */
  YYSYMBOL_DATA = 55,                      /* DATA  */
  YYSYMBOL_TEXT_T = 56,                    /* TEXT_T  */
  YYSYMBOL_INFILE = 57,                    /* INFILE  */
  YYSYMBOL_VIEW = 58,                      /* VIEW  */
  YYSYMBOL_EXPLAIN = 59,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 60,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 61,                    /* FORMAT  */
  YYSYMBOL_EQ = 62,                        /* EQ  */
  YYSYMBOL_LT = 63,                        /* LT  */
  YYSYMBOL_GT = 64,                        /* GT  */
  YYSYMBOL_LE = 65,                        /* LE  */
  YYSYMBOL_GE = 66,                        /* GE  */
  YYSYMBOL_NE = 67,                        /* NE  */
  YYSYMBOL_L2_DISTANCE = 68,               /* L2_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 69,             /* INNER_PRODUCT  */
  YYSYMBOL_COSINE_DISTANCE = 70,           /* COSINE_DISTANCE  */
  YYSYMBOL_NUMBER = 71,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 72,                     /* FLOAT  */
  YYSYMBOL_ID = 73,                        /* ID  */
  YYSYMBOL_SSS = 74,                       /* SSS  */
  YYSYMBOL_VECTOR_DATA = 75,               /* VECTOR_DATA  */
  YYSYMBOL_76_ = 76,                       /* '+'  */
  YYSYMBOL_77_ = 77,                       /* '-'  */
  YYSYMBOL_78_ = 78,                       /* '*'  */
  YYSYMBOL_79_ = 79,                       /* '/'  */
  YYSYMBOL_UMINUS = 80,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 81,                  /* $accept  */
  YYSYMBOL_commands = 82,                  /* commands  */
  YYSYMBOL_command_wrapper = 83,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 84,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 85,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 86,                 /* sync_stmt  */
  YYSYMBOL_alias_stmt = 87,                /* alias_stmt  */
  YYSYMBOL_begin_stmt = 88,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 89,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 90,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 91,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 92,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 93,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 94,         /* create_index_stmt  */
  YYSYMBOL_unique_stmt = 95,               /* unique_stmt  */
  YYSYMBOL_attr_list = 96,                 /* attr_list  */
  YYSYMBOL_drop_index_stmt = 97,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 98,         /* create_table_stmt  */
  YYSYMBOL_create_select_stmt = 99,        /* create_select_stmt  */
  YYSYMBOL_create_view_stmt = 100,         /* create_view_stmt  */
  YYSYMBOL_as_stmt = 101,                  /* as_stmt  */
  YYSYMBOL_attr_def_list = 102,            /* attr_def_list  */
  YYSYMBOL_attr_def = 103,                 /* attr_def  */
  YYSYMBOL_null_def = 104,                 /* null_def  */
  YYSYMBOL_number = 105,                   /* number  */
  YYSYMBOL_type = 106,                     /* type  */
  YYSYMBOL_insert_stmt = 107,              /* insert_stmt  */
  YYSYMBOL_value_list = 108,               /* value_list  */
  YYSYMBOL_insert_val = 109,               /* insert_val  */
  YYSYMBOL_const_value_list_expr = 110,    /* const_value_list_expr  */
  YYSYMBOL_const_value_list = 111,         /* const_value_list  */
  YYSYMBOL_value = 112,                    /* value  */
  YYSYMBOL_storage_format = 113,           /* storage_format  */
  YYSYMBOL_delete_stmt = 114,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 115,              /* update_stmt  */
  YYSYMBOL_assignment_list = 116,          /* assignment_list  */
  YYSYMBOL_assignment = 117,               /* assignment  */
  YYSYMBOL_select_stmt = 118,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 119,                /* calc_stmt  */
  YYSYMBOL_expression_list = 120,          /* expression_list  */
  YYSYMBOL_expression = 121,               /* expression  */
  YYSYMBOL_aggr_func_expr = 122,           /* aggr_func_expr  */
  YYSYMBOL_rel_attr = 123,                 /* rel_attr  */
  YYSYMBOL_relation = 124,                 /* relation  */
  YYSYMBOL_rel_list = 125,                 /* rel_list  */
  YYSYMBOL_on_stmt = 126,                  /* on_stmt  */
  YYSYMBOL_where = 127,                    /* where  */
  YYSYMBOL_condition_list = 128,           /* condition_list  */
  YYSYMBOL_condition = 129,                /* condition  */
  YYSYMBOL_null_condition = 130,           /* null_condition  */
  YYSYMBOL_comp_op = 131,                  /* comp_op  */
  YYSYMBOL_group_by = 132,                 /* group_by  */
  YYSYMBOL_rel_attrs = 133,                /* rel_attrs  */
  YYSYMBOL_having_stmt = 134,              /* having_stmt  */
  YYSYMBOL_order_by = 135,                 /* order_by  */
  YYSYMBOL_order_list = 136,               /* order_list  */
  YYSYMBOL_load_data_stmt = 137,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 138,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 139,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 140             /* opt_semicolon  */
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
#define YYFINAL  74
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   410

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  166
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  307

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   331


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
       2,     2,    78,    76,     2,    77,     2,    79,     2,     2,
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
      75,    80
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   243,   243,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,   264,   265,   266,   267,
     268,   269,   270,   271,   272,   276,   282,   287,   293,   296,
     300,   305,   311,   317,   323,   330,   336,   344,   364,   367,
     372,   375,   386,   396,   419,   427,   447,   456,   459,   465,
     468,   481,   494,   506,   509,   512,   516,   519,   520,   521,
     522,   523,   524,   527,   546,   549,   560,   563,   571,   578,
     584,   589,   595,   599,   603,   609,   633,   636,   643,   654,
     669,   673,   679,   686,   694,   704,   748,   757,   766,   781,
     787,   794,   797,   800,   804,   807,   810,   814,   819,   822,
     825,   828,   839,   843,   847,   855,   861,   871,   876,   879,
     892,   910,   914,   921,   924,   930,   933,   938,   945,   951,
     956,   961,   967,   972,   977,   982,   987,   993,  1000,  1007,
    1016,  1023,  1031,  1038,  1064,  1065,  1066,  1067,  1068,  1069,
    1070,  1071,  1072,  1073,  1074,  1075,  1076,  1077,  1083,  1086,
    1092,  1098,  1106,  1109,  1147,  1150,  1155,  1165,  1175,  1185,
    1195,  1206,  1232,  1245,  1253,  1263,  1264
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
  "null", "SELECT", "ALIAS", "ASC", "ORDER", "DESC", "SHOW", "SYNC",
  "INSERT", "IS", "AS", "DELETE", "UPDATE", "UNIQUE", "LBRACE", "RBRACE",
  "COMMA", "INNER", "JOIN", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "STRING_T", "FLOAT_T", "IN", "EXISTS", "DATE_T", "LIKE", "NOT",
  "VECTOR_T", "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE",
  "AND", "SET", "ON", "LOAD", "DATA", "TEXT_T", "INFILE", "VIEW",
  "EXPLAIN", "STORAGE", "FORMAT", "EQ", "LT", "GT", "LE", "GE", "NE",
  "L2_DISTANCE", "INNER_PRODUCT", "COSINE_DISTANCE", "NUMBER", "FLOAT",
  "ID", "SSS", "VECTOR_DATA", "'+'", "'-'", "'*'", "'/'", "UMINUS",
  "$accept", "commands", "command_wrapper", "exit_stmt", "help_stmt",
  "sync_stmt", "alias_stmt", "begin_stmt", "commit_stmt", "rollback_stmt",
  "drop_table_stmt", "show_tables_stmt", "desc_table_stmt",
  "create_index_stmt", "unique_stmt", "attr_list", "drop_index_stmt",
  "create_table_stmt", "create_select_stmt", "create_view_stmt", "as_stmt",
  "attr_def_list", "attr_def", "null_def", "number", "type", "insert_stmt",
  "value_list", "insert_val", "const_value_list_expr", "const_value_list",
  "value", "storage_format", "delete_stmt", "update_stmt",
  "assignment_list", "assignment", "select_stmt", "calc_stmt",
  "expression_list", "expression", "aggr_func_expr", "rel_attr",
  "relation", "rel_list", "on_stmt", "where", "condition_list",
  "condition", "null_condition", "comp_op", "group_by", "rel_attrs",
  "having_stmt", "order_by", "order_list", "load_data_stmt",
  "explain_stmt", "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-231)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     266,    10,    21,   274,   274,   -53,    18,  -231,   -24,   -15,
     -36,  -231,  -231,  -231,  -231,  -231,   -34,   -14,   266,    44,
      71,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,  -231,
    -231,  -231,  -231,    20,  -231,    23,   101,    47,    54,   274,
     105,   113,   133,  -231,  -231,   -11,  -231,  -231,   274,  -231,
    -231,  -231,    89,  -231,  -231,   114,  -231,  -231,    91,    99,
     124,   120,   127,  -231,  -231,  -231,  -231,    -1,   163,   115,
    -231,   134,   168,   274,   274,   274,   261,   121,  -231,   122,
    -231,   274,   274,   274,   274,   164,   136,   149,   156,   138,
     222,   139,  -231,   141,   201,   201,   171,   154,  -231,   277,
     287,   297,  -231,   202,    69,  -231,  -231,   -32,   -32,  -231,
    -231,   274,  -231,    -2,   214,    -8,  -231,   186,   156,   220,
    -231,   203,   239,   233,  -231,  -231,   192,  -231,   274,   274,
     274,  -231,  -231,  -231,    28,   106,   319,   165,   319,   190,
    -231,   219,  -231,     1,  -231,   138,   273,  -231,  -231,  -231,
    -231,  -231,  -231,    11,   141,   255,   265,   182,   236,   245,
     136,   271,   156,  -231,   222,   275,  -231,   263,  -231,  -231,
    -231,   100,  -231,  -231,  -231,  -231,  -231,  -231,    32,   279,
      97,   280,    81,   130,    -8,  -231,   201,  -231,  -231,   230,
    -231,   238,   304,  -231,   233,    19,   246,  -231,  -231,  -231,
      -2,   136,   320,  -231,   106,   300,  -231,  -231,  -231,  -231,
    -231,   165,  -231,    37,  -231,   222,   319,  -231,   165,    37,
    -231,   165,  -231,    37,  -231,   309,  -231,  -231,   312,  -231,
    -231,   289,   201,  -231,   333,    28,    -2,   363,   357,   275,
    -231,   341,  -231,   342,   148,   344,   349,  -231,    12,   308,
    -231,   305,   351,  -231,   327,   316,    -8,   373,  -231,  -231,
    -231,   165,  -231,    37,  -231,  -231,  -231,   318,   333,  -231,
      -8,    28,   346,   364,  -231,  -231,   390,  -231,   370,  -231,
    -231,  -231,  -231,   316,   316,  -231,  -231,    14,  -231,   371,
     372,   316,   316,   316,  -231,  -231,  -231
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    38,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    31,    32,    33,    26,    25,     0,     0,     0,     0,
     165,    24,    23,    14,    15,    18,    19,     9,    10,    11,
      12,    13,     8,    16,    17,     5,     7,     6,     4,     3,
      20,    21,    22,     0,    39,     0,     0,     0,     0,     0,
       0,     0,     0,    72,    73,   105,    74,    75,     0,    91,
      89,    86,    28,    98,    90,     0,    36,    35,     0,     0,
       0,     0,     0,   163,     1,   166,     2,    47,    47,     0,
      34,     0,     0,     0,     0,     0,     0,     0,    97,     0,
      29,     0,     0,     0,     0,    87,     0,     0,   113,     0,
       0,     0,    48,     0,     0,     0,     0,     0,    96,     0,
       0,     0,   103,     0,    28,   106,    30,    92,    93,    94,
      95,     0,   107,    28,     0,   115,    78,     0,   113,    80,
     164,     0,     0,    49,    44,    46,     0,    42,     0,     0,
       0,   104,   102,    88,   108,     0,     0,     0,     0,     0,
     114,   116,   126,     0,    79,     0,     0,    57,    58,    59,
      60,    61,    62,    53,     0,     0,     0,     0,     0,     0,
       0,     0,   113,    68,     0,    64,    66,   143,   144,   146,
     140,     0,   134,   135,   136,   137,   138,   139,     0,     0,
      89,     0,     0,     0,   115,    83,     0,    82,    81,     0,
      54,     0,     0,    52,    49,    76,     0,    99,   100,   101,
      28,     0,   148,    67,     0,     0,   142,   145,   147,   141,
     129,     0,   132,   128,    69,     0,     0,   133,     0,   122,
     127,     0,   121,   118,   117,     0,   162,    56,     0,    55,
      50,     0,     0,    43,    40,   108,    28,     0,   152,    64,
      63,     0,    71,    70,     0,     0,     0,    84,    53,     0,
      45,     0,     0,   109,   111,     0,   115,   154,    65,   131,
     130,     0,   123,   120,   124,   119,    51,     0,    40,    37,
     115,   108,   105,   150,   149,   153,     0,    85,     0,    77,
      41,   112,   110,     0,     0,   125,   151,   156,   155,   158,
     160,     0,     0,     0,   157,   159,   161
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -231,  -231,   381,  -231,  -231,  -231,  -115,  -231,  -231,  -231,
    -231,  -231,  -231,  -231,  -231,   125,  -231,  -231,  -231,  -231,
     -76,   198,   240,   147,  -231,  -231,  -231,   157,   193,  -176,
     183,   -97,  -231,  -231,  -231,   254,  -231,   -98,  -231,     0,
      -3,  -231,    94,  -159,  -230,  -231,   -88,  -181,  -231,  -231,
    -139,  -231,   117,  -231,  -231,  -132,  -231,  -231,  -231,  -231
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    95,    24,    25,    26,
      27,    28,    29,    30,    46,   262,    31,    32,    33,    34,
     104,   165,   133,   203,   238,   163,    35,   215,   175,   148,
     189,    60,   243,    36,    37,   128,   129,    38,    39,    61,
      82,    63,    64,   123,   172,   281,   126,   150,   151,   152,
     188,   248,   284,   267,   287,   298,    40,    41,    42,    76
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      62,    62,   105,   130,    65,   146,   134,   135,   144,   192,
     193,   210,   222,   234,   195,   263,    86,   232,    43,   147,
      66,    89,   102,    68,   200,   200,   103,    67,   196,    47,
     299,    48,   300,   -47,    69,    87,    44,    70,   201,    71,
     154,    72,   102,   301,    74,   220,    93,    94,   176,   191,
     190,   292,   246,   202,   202,    88,   197,   170,   171,   221,
      50,    51,    52,    53,    54,    55,    56,    57,    45,    58,
      59,    90,    53,    54,    75,    56,    57,   213,   272,   241,
     109,   110,   111,   114,   212,   285,   113,   254,   117,   118,
     119,   120,    89,    77,   227,   245,    78,   142,   235,   291,
      50,    51,    52,    53,    54,    55,    56,    57,   228,    58,
      59,    79,    89,    91,    92,    93,    94,   176,    62,   173,
      80,   143,   149,   251,   190,   -70,   225,    81,   253,   242,
     255,   264,    83,   256,   190,   167,   168,   169,   217,   218,
      84,   219,    90,   230,   260,    91,    92,    93,    94,    50,
      51,    52,    53,    54,    55,    56,    57,   231,    58,    59,
      85,   270,    90,    96,    97,    91,    92,    93,    94,   304,
     305,   306,    98,   288,   190,   271,    99,    53,    54,     4,
      56,    57,   100,   174,   101,   223,   102,   107,   106,   229,
     233,   149,    49,   121,   115,   116,   108,   124,    50,    51,
      52,    53,    54,    55,    56,    57,   125,    58,    59,   122,
     207,   127,   177,   131,   132,     4,    50,    51,    52,    53,
      54,    55,    56,    57,   136,    58,    59,   137,   178,   179,
     141,   180,   181,    50,    51,    52,    53,    54,    55,    56,
      57,   145,    58,    59,    91,    92,    93,    94,   153,   155,
     156,   273,   182,   183,   184,   185,   186,   187,    91,    92,
      93,    94,   164,   149,   208,   166,    91,    92,    93,    94,
     194,     1,     2,   209,   157,   158,   159,   149,     3,   160,
       4,   199,   161,   205,     5,     6,     7,     8,    49,   112,
       9,    10,   206,    53,    54,   162,    56,    57,    11,    12,
      13,    49,   211,   236,   214,   216,   138,   224,   226,   237,
      14,    15,    91,    92,    93,    94,   139,   239,    16,   244,
      17,    91,    92,    93,    94,    18,   140,   247,   250,    50,
      51,    52,    53,    54,    55,    56,    57,   257,    58,    59,
     258,   177,    50,    51,    52,    53,    54,    55,    56,    57,
     259,    58,    59,    91,    92,    93,    94,   178,   179,   283,
     180,   181,   261,    91,    92,    93,    94,   265,   266,   269,
     277,   225,   274,    91,    92,    93,    94,   275,   278,   279,
     280,   182,   183,   184,   185,   186,   187,   283,   297,   282,
     286,   289,    87,   293,   294,   297,   297,   297,   295,    73,
     302,   303,   240,   290,   204,   276,   268,   249,   252,   198,
     296
};

static const yytype_int16 yycheck[] =
{
       3,     4,    78,   100,     4,    13,   104,   105,   123,   148,
     149,   170,   188,   194,    13,   245,    27,   193,     8,    27,
      73,    23,    23,    47,    13,    13,    27,     9,    27,     8,
      16,    10,    18,    14,    49,    46,    26,    73,    27,    73,
     128,    55,    23,    29,     0,    13,    78,    79,   145,   147,
     147,   281,   211,    42,    42,    58,   153,    29,    30,    27,
      68,    69,    70,    71,    72,    73,    74,    75,    58,    77,
      78,    73,    71,    72,     3,    74,    75,   174,   254,    60,
      83,    84,    85,    86,   172,   266,    86,   226,    91,    92,
      93,    94,    23,    73,    13,   210,    73,    28,   196,   280,
      68,    69,    70,    71,    72,    73,    74,    75,    27,    77,
      78,    10,    23,    76,    77,    78,    79,   214,   121,    13,
      73,   121,   125,   221,   221,    28,    29,    73,   225,   205,
     228,   246,    27,   231,   231,   138,   139,   140,    38,    39,
      27,    41,    73,    13,   242,    76,    77,    78,    79,    68,
      69,    70,    71,    72,    73,    74,    75,    27,    77,    78,
      27,    13,    73,    49,    73,    76,    77,    78,    79,   301,
     302,   303,    73,   271,   271,    27,    52,    71,    72,    14,
      74,    75,    62,    77,    57,   188,    23,    53,    73,   192,
     193,   194,    27,    29,    73,    73,    28,    48,    68,    69,
      70,    71,    72,    73,    74,    75,    50,    77,    78,    73,
      28,    73,    22,    74,    73,    14,    68,    69,    70,    71,
      72,    73,    74,    75,    53,    77,    78,    73,    38,    39,
      28,    41,    42,    68,    69,    70,    71,    72,    73,    74,
      75,    27,    77,    78,    76,    77,    78,    79,    62,    29,
      47,   254,    62,    63,    64,    65,    66,    67,    76,    77,
      78,    79,    29,   266,    28,    73,    76,    77,    78,    79,
      51,     5,     6,    28,    35,    36,    37,   280,    12,    40,
      14,     8,    43,    28,    18,    19,    20,    21,    27,    28,
      24,    25,    27,    71,    72,    56,    74,    75,    32,    33,
      34,    27,    31,    73,    29,    42,    29,    28,    28,    71,
      44,    45,    76,    77,    78,    79,    29,    13,    52,    73,
      54,    76,    77,    78,    79,    59,    29,     7,    28,    68,
      69,    70,    71,    72,    73,    74,    75,    28,    77,    78,
      28,    22,    68,    69,    70,    71,    72,    73,    74,    75,
      61,    77,    78,    76,    77,    78,    79,    38,    39,   265,
      41,    42,    29,    76,    77,    78,    79,     4,    11,    28,
      62,    29,    28,    76,    77,    78,    79,    28,    73,    28,
      53,    62,    63,    64,    65,    66,    67,   293,   294,    73,
      17,    73,    46,    29,     4,   301,   302,   303,    28,    18,
      29,    29,   204,   278,   164,   258,   249,   214,   225,   155,
     293
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    14,    18,    19,    20,    21,    24,
      25,    32,    33,    34,    44,    45,    52,    54,    59,    82,
      83,    84,    85,    86,    88,    89,    90,    91,    92,    93,
      94,    97,    98,    99,   100,   107,   114,   115,   118,   119,
     137,   138,   139,     8,    26,    58,    95,     8,    10,    27,
      68,    69,    70,    71,    72,    73,    74,    75,    77,    78,
     112,   120,   121,   122,   123,   120,    73,     9,    47,    49,
      73,    73,    55,    83,     0,     3,   140,    73,    73,    10,
      73,    73,   121,    27,    27,    27,    27,    46,   121,    23,
      73,    76,    77,    78,    79,    87,    49,    73,    73,    52,
      62,    57,    23,    27,   101,   101,    73,    53,    28,   121,
     121,   121,    28,   120,   121,    73,    73,   121,   121,   121,
     121,    29,    73,   124,    48,    50,   127,    73,   116,   117,
     112,    74,    73,   103,   118,   118,    53,    73,    29,    29,
      29,    28,    28,   120,    87,    27,    13,    27,   110,   121,
     128,   129,   130,    62,   127,    29,    47,    35,    36,    37,
      40,    43,    56,   106,    29,   102,    73,   121,   121,   121,
      29,    30,   125,    13,    77,   109,   112,    22,    38,    39,
      41,    42,    62,    63,    64,    65,    66,    67,   131,   111,
     112,   118,   131,   131,    51,    13,    27,   112,   116,     8,
      13,    27,    42,   104,   103,    28,    27,    28,    28,    28,
     124,    31,   127,   112,    29,   108,    42,    38,    39,    41,
      13,    27,   110,   121,    28,    29,    28,    13,    27,   121,
      13,    27,   110,   121,   128,   118,    73,    71,   105,    13,
     102,    60,   101,   113,    73,    87,   124,     7,   132,   109,
      28,   118,   111,   112,   131,   118,   118,    28,    28,    61,
     118,    29,    96,   125,    87,     4,    11,   134,   108,    28,
      13,    27,   110,   121,    28,    28,   104,    62,    73,    28,
      53,   126,    73,   123,   133,   128,    17,   135,   118,    73,
      96,   128,   125,    29,     4,    28,   133,   123,   136,    16,
      18,    29,    29,    29,   136,   136,   136
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    84,    85,    86,    87,    87,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    95,
      96,    96,    97,    98,    99,    99,   100,   101,   101,   102,
     102,   103,   103,   104,   104,   104,   105,   106,   106,   106,
     106,   106,   106,   107,   108,   108,   109,   109,   109,   110,
     111,   111,   112,   112,   112,   112,   113,   113,   114,   115,
     116,   116,   117,   117,   117,   118,   119,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   122,   122,   122,   123,   123,   124,   125,   125,
     125,   126,   126,   127,   127,   128,   128,   128,   129,   129,
     129,   129,   129,   129,   129,   129,   129,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   132,   132,
     133,   133,   134,   134,   135,   135,   136,   136,   136,   136,
     136,   136,   137,   138,   139,   140,   140
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     1,
       2,     1,     1,     1,     3,     2,     2,    10,     0,     1,
       0,     3,     5,     8,     5,     9,     5,     0,     1,     0,
       3,     6,     3,     0,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     8,     0,     3,     1,     2,     1,     3,
       1,     3,     1,     1,     1,     1,     0,     4,     4,     5,
       1,     3,     3,     3,     5,    10,     2,     2,     4,     1,
       1,     1,     3,     3,     3,     3,     3,     2,     1,     6,
       6,     6,     4,     3,     4,     1,     3,     1,     0,     4,
       6,     0,     2,     0,     2,     0,     1,     3,     3,     5,
       5,     3,     3,     5,     5,     7,     1,     3,     3,     3,
       5,     5,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     2,     1,     2,     0,     3,
       1,     3,     0,     2,     0,     3,     1,     3,     2,     4,
       2,     4,     7,     2,     4,     0,     1
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
#line 244 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1903 "yacc_sql.cpp"
    break;

  case 25: /* exit_stmt: EXIT  */
#line 276 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 26: /* help_stmt: HELP  */
#line 282 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1920 "yacc_sql.cpp"
    break;

  case 27: /* sync_stmt: SYNC  */
#line 287 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1928 "yacc_sql.cpp"
    break;

  case 28: /* alias_stmt: %empty  */
#line 293 "yacc_sql.y"
  {
    (yyval.string) = nullptr;
  }
#line 1936 "yacc_sql.cpp"
    break;

  case 29: /* alias_stmt: ID  */
#line 297 "yacc_sql.y"
  {
    (yyval.string) = (yyvsp[0].string);
  }
#line 1944 "yacc_sql.cpp"
    break;

  case 30: /* alias_stmt: AS ID  */
#line 300 "yacc_sql.y"
          {
    (yyval.string) = (yyvsp[0].string);
  }
#line 1952 "yacc_sql.cpp"
    break;

  case 31: /* begin_stmt: TRX_BEGIN  */
#line 305 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1960 "yacc_sql.cpp"
    break;

  case 32: /* commit_stmt: TRX_COMMIT  */
#line 311 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1968 "yacc_sql.cpp"
    break;

  case 33: /* rollback_stmt: TRX_ROLLBACK  */
#line 317 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1976 "yacc_sql.cpp"
    break;

  case 34: /* drop_table_stmt: DROP TABLE ID  */
#line 323 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1986 "yacc_sql.cpp"
    break;

  case 35: /* show_tables_stmt: SHOW TABLES  */
#line 330 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1994 "yacc_sql.cpp"
    break;

  case 36: /* desc_table_stmt: DESC ID  */
#line 336 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 2004 "yacc_sql.cpp"
    break;

  case 37: /* create_index_stmt: CREATE unique_stmt INDEX ID ON ID LBRACE ID attr_list RBRACE  */
#line 345 "yacc_sql.y"
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
#line 2025 "yacc_sql.cpp"
    break;

  case 38: /* unique_stmt: %empty  */
#line 364 "yacc_sql.y"
  {
    (yyval.boolean) = false;
  }
#line 2033 "yacc_sql.cpp"
    break;

  case 39: /* unique_stmt: UNIQUE  */
#line 367 "yacc_sql.y"
           {
    (yyval.boolean) = true;
  }
#line 2041 "yacc_sql.cpp"
    break;

  case 40: /* attr_list: %empty  */
#line 372 "yacc_sql.y"
  {
    (yyval.relation_list) = nullptr;
  }
#line 2049 "yacc_sql.cpp"
    break;

  case 41: /* attr_list: COMMA ID attr_list  */
#line 375 "yacc_sql.y"
                       {
    if ((yyvsp[0].relation_list) != nullptr) {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    } else {
      (yyval.relation_list) = new vector<std::string>;
    }
    (yyval.relation_list)->emplace_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 2063 "yacc_sql.cpp"
    break;

  case 42: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 387 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2075 "yacc_sql.cpp"
    break;

  case 43: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 397 "yacc_sql.y"
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
#line 2100 "yacc_sql.cpp"
    break;

  case 44: /* create_select_stmt: CREATE TABLE ID as_stmt select_stmt  */
#line 419 "yacc_sql.y"
                                        {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_TABLE_SELECT);
    auto &table = (yyval.sql_node)->create_table_select;
    table.relation_name =string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    table.has_schema = false;
    table.query = (yyvsp[0].sql_node);
  }
#line 2113 "yacc_sql.cpp"
    break;

  case 45: /* create_select_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE as_stmt select_stmt  */
#line 427 "yacc_sql.y"
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
#line 2136 "yacc_sql.cpp"
    break;

  case 46: /* create_view_stmt: CREATE VIEW ID as_stmt select_stmt  */
#line 447 "yacc_sql.y"
                                       {
    (yyval.sql_node) = new ParsedSqlNode(SCF_CREATE_VIEW);
    auto &view = (yyval.sql_node)->create_view;
    view.view_name =string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    view.query = (yyvsp[0].sql_node);
  }
#line 2148 "yacc_sql.cpp"
    break;

  case 47: /* as_stmt: %empty  */
#line 456 "yacc_sql.y"
  {
    (yyval.boolean) = false;
  }
#line 2156 "yacc_sql.cpp"
    break;

  case 48: /* as_stmt: AS  */
#line 459 "yacc_sql.y"
       {
    (yyval.boolean) = true;
  }
#line 2164 "yacc_sql.cpp"
    break;

  case 49: /* attr_def_list: %empty  */
#line 465 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2172 "yacc_sql.cpp"
    break;

  case 50: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 469 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2186 "yacc_sql.cpp"
    break;

  case 51: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 482 "yacc_sql.y"
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
#line 2203 "yacc_sql.cpp"
    break;

  case 52: /* attr_def: ID type null_def  */
#line 495 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-2].string));
      (yyval.attr_info)->nullable = ((yyvsp[0].number) == 1);
    }
#line 2216 "yacc_sql.cpp"
    break;

  case 53: /* null_def: %empty  */
#line 506 "yacc_sql.y"
  { // 默認是可以爲null的
    (yyval.number) = 1;
  }
#line 2224 "yacc_sql.cpp"
    break;

  case 54: /* null_def: null  */
#line 509 "yacc_sql.y"
         {
    (yyval.number) = 1;
  }
#line 2232 "yacc_sql.cpp"
    break;

  case 55: /* null_def: NOT null  */
#line 512 "yacc_sql.y"
             {
    (yyval.number) = 0;
  }
#line 2240 "yacc_sql.cpp"
    break;

  case 56: /* number: NUMBER  */
#line 516 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2246 "yacc_sql.cpp"
    break;

  case 57: /* type: INT_T  */
#line 519 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2252 "yacc_sql.cpp"
    break;

  case 58: /* type: STRING_T  */
#line 520 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2258 "yacc_sql.cpp"
    break;

  case 59: /* type: FLOAT_T  */
#line 521 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2264 "yacc_sql.cpp"
    break;

  case 60: /* type: DATE_T  */
#line 522 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2270 "yacc_sql.cpp"
    break;

  case 61: /* type: VECTOR_T  */
#line 523 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2276 "yacc_sql.cpp"
    break;

  case 62: /* type: TEXT_T  */
#line 524 "yacc_sql.y"
                 { (yyval.number) = static_cast<int>(AttrType::TEXTS); }
#line 2282 "yacc_sql.cpp"
    break;

  case 63: /* insert_stmt: INSERT INTO ID VALUES LBRACE insert_val value_list RBRACE  */
#line 528 "yacc_sql.y"
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
#line 2299 "yacc_sql.cpp"
    break;

  case 64: /* value_list: %empty  */
#line 546 "yacc_sql.y"
  {
    (yyval.value_list) = nullptr;
  }
#line 2307 "yacc_sql.cpp"
    break;

  case 65: /* value_list: COMMA insert_val value_list  */
#line 549 "yacc_sql.y"
                                 { 
    if ((yyvsp[0].value_list) != nullptr) {
      (yyval.value_list) = (yyvsp[0].value_list);
    } else {
      (yyval.value_list) = new std::vector<Value>;
    }
    (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
    delete (yyvsp[-1].value);
  }
#line 2321 "yacc_sql.cpp"
    break;

  case 66: /* insert_val: value  */
#line 560 "yacc_sql.y"
         {
    (yyval.value) = (yyvsp[0].value);
  }
#line 2329 "yacc_sql.cpp"
    break;

  case 67: /* insert_val: '-' value  */
#line 563 "yacc_sql.y"
              {
    (yyval.value) = (yyvsp[0].value);
    if ((yyval.value)->attr_type() == AttrType::INTS) {
      (yyval.value)->set_int((yyval.value)->get_int() *(-1));
    } else if ((yyval.value)->attr_type() == AttrType::FLOATS) {
      (yyval.value)->set_float((yyval.value)->get_float() *(-1));
    }
  }
#line 2342 "yacc_sql.cpp"
    break;

  case 68: /* insert_val: null  */
#line 571 "yacc_sql.y"
         {
    (yyval.value) = new Value;
    (yyval.value)->set_null();
  }
#line 2351 "yacc_sql.cpp"
    break;

  case 69: /* const_value_list_expr: LBRACE const_value_list RBRACE  */
#line 578 "yacc_sql.y"
                                 {
    (yyval.expression) = new ConstantValueListExpr((yyvsp[-1].const_value_list_type));
    delete (yyvsp[-1].const_value_list_type);
  }
#line 2360 "yacc_sql.cpp"
    break;

  case 70: /* const_value_list: value  */
#line 584 "yacc_sql.y"
        {
    cout << (yyvsp[0].value)->get_int() << endl;
    (yyval.const_value_list_type) = new vector<Value*>();
    (yyval.const_value_list_type)->emplace_back((yyvsp[0].value));
  }
#line 2370 "yacc_sql.cpp"
    break;

  case 71: /* const_value_list: value COMMA const_value_list  */
#line 589 "yacc_sql.y"
                                 {
    (yyval.const_value_list_type) = (yyvsp[0].const_value_list_type);
    (yyval.const_value_list_type)->emplace_back((yyvsp[-2].value));
  }
#line 2379 "yacc_sql.cpp"
    break;

  case 72: /* value: NUMBER  */
#line 595 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2388 "yacc_sql.cpp"
    break;

  case 73: /* value: FLOAT  */
#line 599 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2397 "yacc_sql.cpp"
    break;

  case 74: /* value: SSS  */
#line 603 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2408 "yacc_sql.cpp"
    break;

  case 75: /* value: VECTOR_DATA  */
#line 609 "yacc_sql.y"
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
#line 2435 "yacc_sql.cpp"
    break;

  case 76: /* storage_format: %empty  */
#line 633 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2443 "yacc_sql.cpp"
    break;

  case 77: /* storage_format: STORAGE FORMAT EQ ID  */
#line 637 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2451 "yacc_sql.cpp"
    break;

  case 78: /* delete_stmt: DELETE FROM ID where  */
#line 644 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2464 "yacc_sql.cpp"
    break;

  case 79: /* update_stmt: UPDATE ID SET assignment_list where  */
#line 655 "yacc_sql.y"
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
#line 2480 "yacc_sql.cpp"
    break;

  case 80: /* assignment_list: assignment  */
#line 669 "yacc_sql.y"
             {
    (yyval.assignment_ptr_list) = new vector<Assignment*>();
    (yyval.assignment_ptr_list)->emplace_back((yyvsp[0].assignment_ptr));
  }
#line 2489 "yacc_sql.cpp"
    break;

  case 81: /* assignment_list: assignment COMMA assignment_list  */
#line 673 "yacc_sql.y"
                                     {
    (yyval.assignment_ptr_list) = (yyvsp[0].assignment_ptr_list);
    (yyval.assignment_ptr_list)->emplace_back((yyvsp[-2].assignment_ptr));
  }
#line 2498 "yacc_sql.cpp"
    break;

  case 82: /* assignment: ID EQ value  */
#line 679 "yacc_sql.y"
              {
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    (yyval.assignment_ptr)->right_hand_side = new ValueExpr(*(yyvsp[0].value));
    delete (yyvsp[0].value);
  }
#line 2510 "yacc_sql.cpp"
    break;

  case 83: /* assignment: ID EQ null  */
#line 686 "yacc_sql.y"
               {
    Value v;
    v.set_null();
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    (yyval.assignment_ptr)->right_hand_side = new ValueExpr(v);
  }
#line 2523 "yacc_sql.cpp"
    break;

  case 84: /* assignment: ID EQ LBRACE select_stmt RBRACE  */
#line 694 "yacc_sql.y"
                                   {
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-4].string));
    free((yyvsp[-4].string));
    (yyval.assignment_ptr)->right_hand_side = new SubQueryExpr((yyvsp[-1].sql_node));
  }
#line 2534 "yacc_sql.cpp"
    break;

  case 85: /* select_stmt: SELECT expression_list FROM relation alias_stmt rel_list where group_by having_stmt order_by  */
#line 705 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SELECT);
      auto &selection = (yyval.sql_node)->selection;
      // select
      if ((yyvsp[-8].expression_list) != nullptr) {
        selection.expressions.swap(*(yyvsp[-8].expression_list));
        delete (yyvsp[-8].expression_list);
      }
      // from
      
      auto r = new rel_info;
      r->relation_name = (yyvsp[-6].string);
      if ((yyvsp[-5].string)) {
        r->relation_alias = (yyvsp[-5].string);
        free((yyvsp[-5].string));
      }
      selection.relations.emplace_back(r);
      if ((yyvsp[-4].rel_list_type) != nullptr) {
        for(auto iter = (yyvsp[-4].rel_list_type)->rbegin(); iter != (yyvsp[-4].rel_list_type)->rend(); ++iter) {
          selection.relations.emplace_back(*iter);
          (*iter) = nullptr;
        }
        // printf("size:%ld.%s\n",selection.relations.size(),selection.relations[0].relation_name.c_str());
      }
      free((yyvsp[-6].string));
      
      // where 
      if ((yyvsp[-3].condition_list) != nullptr) {
        selection.conditions = (yyvsp[-3].condition_list);
      }
    
      if ((yyvsp[-2].expression_list) != nullptr) {
        selection.group_by = (yyvsp[-2].expression_list);
      }
      if ((yyvsp[-1].condition_list) != nullptr) {
        selection.having = (yyvsp[-1].condition_list);
      }
      if ((yyvsp[0].order_by_list) != nullptr) {
        selection.order_by = (yyvsp[0].order_by_list);
      }
    }
#line 2580 "yacc_sql.cpp"
    break;

  case 86: /* calc_stmt: CALC expression_list  */
#line 749 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2590 "yacc_sql.cpp"
    break;

  case 87: /* expression_list: expression alias_stmt  */
#line 758 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if ((yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias(std::string((yyvsp[0].string)));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2603 "yacc_sql.cpp"
    break;

  case 88: /* expression_list: expression alias_stmt COMMA expression_list  */
#line 767 "yacc_sql.y"
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
#line 2620 "yacc_sql.cpp"
    break;

  case 89: /* expression: value  */
#line 781 "yacc_sql.y"
          {
      cout << "value_expr\n";
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2631 "yacc_sql.cpp"
    break;

  case 90: /* expression: rel_attr  */
#line 787 "yacc_sql.y"
               {
      cout << "field_expr\n";
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2643 "yacc_sql.cpp"
    break;

  case 91: /* expression: '*'  */
#line 794 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2651 "yacc_sql.cpp"
    break;

  case 92: /* expression: expression '+' expression  */
#line 797 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2659 "yacc_sql.cpp"
    break;

  case 93: /* expression: expression '-' expression  */
#line 800 "yacc_sql.y"
                                {
      cout << "minus\n";
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2668 "yacc_sql.cpp"
    break;

  case 94: /* expression: expression '*' expression  */
#line 804 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2676 "yacc_sql.cpp"
    break;

  case 95: /* expression: expression '/' expression  */
#line 807 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2684 "yacc_sql.cpp"
    break;

  case 96: /* expression: LBRACE expression RBRACE  */
#line 810 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2693 "yacc_sql.cpp"
    break;

  case 97: /* expression: '-' expression  */
#line 814 "yacc_sql.y"
                                  {
      cout << "negative\n";
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2702 "yacc_sql.cpp"
    break;

  case 98: /* expression: aggr_func_expr  */
#line 819 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2710 "yacc_sql.cpp"
    break;

  case 99: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 822 "yacc_sql.y"
                                                            {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2718 "yacc_sql.cpp"
    break;

  case 100: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 825 "yacc_sql.y"
                                                              {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2726 "yacc_sql.cpp"
    break;

  case 101: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 828 "yacc_sql.y"
                                                                {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2734 "yacc_sql.cpp"
    break;

  case 102: /* aggr_func_expr: ID LBRACE expression RBRACE  */
#line 839 "yacc_sql.y"
                              {
    (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression), sql_string, &(yyloc));
    free((yyvsp[-3].string));
  }
#line 2743 "yacc_sql.cpp"
    break;

  case 103: /* aggr_func_expr: ID LBRACE RBRACE  */
#line 843 "yacc_sql.y"
                     {
    free((yyvsp[-2].string));
    YYERROR;
  }
#line 2752 "yacc_sql.cpp"
    break;

  case 104: /* aggr_func_expr: ID LBRACE expression_list RBRACE  */
#line 847 "yacc_sql.y"
                                     {
    delete (yyvsp[-1].expression_list);
    free((yyvsp[-3].string));
    YYERROR;
  }
#line 2762 "yacc_sql.cpp"
    break;

  case 105: /* rel_attr: ID  */
#line 855 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      printf("attr_name:%s\n",(yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2773 "yacc_sql.cpp"
    break;

  case 106: /* rel_attr: ID DOT ID  */
#line 861 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2785 "yacc_sql.cpp"
    break;

  case 107: /* relation: ID  */
#line 871 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2793 "yacc_sql.cpp"
    break;

  case 108: /* rel_list: %empty  */
#line 876 "yacc_sql.y"
              {
    (yyval.rel_list_type) = nullptr;
  }
#line 2801 "yacc_sql.cpp"
    break;

  case 109: /* rel_list: COMMA relation alias_stmt rel_list  */
#line 879 "yacc_sql.y"
                                       {
    (yyval.rel_list_type) = ((yyvsp[0].rel_list_type) != nullptr ? (yyvsp[0].rel_list_type) : new std::vector<rel_info*>());
  
    auto r = new rel_info;
    r->relation_name = string( (yyvsp[-2].string));
    printf("rel name:%s.\n", (yyvsp[-2].string));
    if ((yyvsp[-1].string)) {
      r->relation_alias = std::string((yyvsp[-1].string));
      free((yyvsp[-1].string));
    }
    (yyval.rel_list_type)->emplace_back(r);
    free((yyvsp[-2].string));
  }
#line 2819 "yacc_sql.cpp"
    break;

  case 110: /* rel_list: INNER JOIN relation alias_stmt on_stmt rel_list  */
#line 892 "yacc_sql.y"
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
      printf("has on conditions\n");
      r->on_conditions = (yyvsp[-1].condition_list);
    }
    (yyval.rel_list_type)->emplace_back(r);
  }
#line 2839 "yacc_sql.cpp"
    break;

  case 111: /* on_stmt: %empty  */
#line 910 "yacc_sql.y"
              {
    // cross product
    (yyval.condition_list) = nullptr;
  }
#line 2848 "yacc_sql.cpp"
    break;

  case 112: /* on_stmt: ON condition_list  */
#line 914 "yacc_sql.y"
                      {
    (yyval.condition_list) = (yyvsp[0].condition_list);
  }
#line 2856 "yacc_sql.cpp"
    break;

  case 113: /* where: %empty  */
#line 921 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2864 "yacc_sql.cpp"
    break;

  case 114: /* where: WHERE condition_list  */
#line 924 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2872 "yacc_sql.cpp"
    break;

  case 115: /* condition_list: %empty  */
#line 930 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2880 "yacc_sql.cpp"
    break;

  case 116: /* condition_list: condition  */
#line 933 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<Expression*>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
      // delete $1;
    }
#line 2890 "yacc_sql.cpp"
    break;

  case 117: /* condition_list: condition AND condition_list  */
#line 938 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
      // delete $1;
    }
#line 2900 "yacc_sql.cpp"
    break;

  case 118: /* condition: expression comp_op expression  */
#line 945 "yacc_sql.y"
                                  {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2910 "yacc_sql.cpp"
    break;

  case 119: /* condition: expression comp_op LBRACE select_stmt RBRACE  */
#line 951 "yacc_sql.y"
                                                 {
      std::unique_ptr<Expression> left((yyvsp[-4].expression));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 2920 "yacc_sql.cpp"
    break;

  case 120: /* condition: LBRACE select_stmt RBRACE comp_op expression  */
#line 956 "yacc_sql.y"
                                                   {
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-3].sql_node)));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2930 "yacc_sql.cpp"
    break;

  case 121: /* condition: expression comp_op const_value_list_expr  */
#line 961 "yacc_sql.y"
                                               {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));

      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2941 "yacc_sql.cpp"
    break;

  case 122: /* condition: const_value_list_expr comp_op expression  */
#line 967 "yacc_sql.y"
                                               {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2951 "yacc_sql.cpp"
    break;

  case 123: /* condition: LBRACE select_stmt RBRACE comp_op const_value_list_expr  */
#line 972 "yacc_sql.y"
                                                              {
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-3].sql_node)));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2961 "yacc_sql.cpp"
    break;

  case 124: /* condition: const_value_list_expr comp_op LBRACE select_stmt RBRACE  */
#line 977 "yacc_sql.y"
                                                              {
      std::unique_ptr<Expression> left((yyvsp[-4].expression));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 2971 "yacc_sql.cpp"
    break;

  case 125: /* condition: LBRACE select_stmt RBRACE comp_op LBRACE select_stmt RBRACE  */
#line 982 "yacc_sql.y"
                                                                  {
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-5].sql_node)));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 2981 "yacc_sql.cpp"
    break;

  case 126: /* condition: null_condition  */
#line 987 "yacc_sql.y"
                     {
      (yyval.condition) = (yyvsp[0].condition);
    }
#line 2989 "yacc_sql.cpp"
    break;

  case 127: /* null_condition: expression comp_op null  */
#line 993 "yacc_sql.y"
                          {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value v;
      v.set_null();
      std::unique_ptr<Expression> right(new ValueExpr(v));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3001 "yacc_sql.cpp"
    break;

  case 128: /* null_condition: null comp_op expression  */
#line 1000 "yacc_sql.y"
                              {
      Value v;
      v.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3013 "yacc_sql.cpp"
    break;

  case 129: /* null_condition: null comp_op null  */
#line 1007 "yacc_sql.y"
                        {
      Value v;
      v.set_null();
      Value v2;
      v2.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v));
      std::unique_ptr<Expression> right(new ValueExpr(v2));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3027 "yacc_sql.cpp"
    break;

  case 130: /* null_condition: LBRACE select_stmt RBRACE comp_op null  */
#line 1016 "yacc_sql.y"
                                             {
      Value v2;
      v2.set_null();
      std::unique_ptr<Expression> left(new SubQueryExpr((yyvsp[-3].sql_node)));
      std::unique_ptr<Expression> right(new ValueExpr(v2));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3039 "yacc_sql.cpp"
    break;

  case 131: /* null_condition: null comp_op LBRACE select_stmt RBRACE  */
#line 1023 "yacc_sql.y"
                                             {
      Value v1;
      v1.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v1));
      std::unique_ptr<Expression> right(new SubQueryExpr((yyvsp[-1].sql_node)));
      (yyval.condition) = new ComparisonExpr((yyvsp[-3].comp), std::move(left), std::move(right));
    }
#line 3051 "yacc_sql.cpp"
    break;

  case 132: /* null_condition: null comp_op const_value_list_expr  */
#line 1031 "yacc_sql.y"
                                         {
      Value v1;
      v1.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v1));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3063 "yacc_sql.cpp"
    break;

  case 133: /* null_condition: const_value_list_expr comp_op null  */
#line 1038 "yacc_sql.y"
                                         {
      Value v2;
      v2.set_null();
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right(new ValueExpr(v2));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 3075 "yacc_sql.cpp"
    break;

  case 134: /* comp_op: EQ  */
#line 1064 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 3081 "yacc_sql.cpp"
    break;

  case 135: /* comp_op: LT  */
#line 1065 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 3087 "yacc_sql.cpp"
    break;

  case 136: /* comp_op: GT  */
#line 1066 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 3093 "yacc_sql.cpp"
    break;

  case 137: /* comp_op: LE  */
#line 1067 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 3099 "yacc_sql.cpp"
    break;

  case 138: /* comp_op: GE  */
#line 1068 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 3105 "yacc_sql.cpp"
    break;

  case 139: /* comp_op: NE  */
#line 1069 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 3111 "yacc_sql.cpp"
    break;

  case 140: /* comp_op: LIKE  */
#line 1070 "yacc_sql.y"
           { (yyval.comp) = LK;}
#line 3117 "yacc_sql.cpp"
    break;

  case 141: /* comp_op: NOT LIKE  */
#line 1071 "yacc_sql.y"
               { (yyval.comp) = NOT_LK;}
#line 3123 "yacc_sql.cpp"
    break;

  case 142: /* comp_op: IS NOT  */
#line 1072 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_NULL;}
#line 3129 "yacc_sql.cpp"
    break;

  case 143: /* comp_op: IS  */
#line 1073 "yacc_sql.y"
          { (yyval.comp) = IS_NULL;}
#line 3135 "yacc_sql.cpp"
    break;

  case 144: /* comp_op: IN  */
#line 1074 "yacc_sql.y"
          { (yyval.comp) = IN_OP;}
#line 3141 "yacc_sql.cpp"
    break;

  case 145: /* comp_op: NOT IN  */
#line 1075 "yacc_sql.y"
              { (yyval.comp) = NOT_IN;}
#line 3147 "yacc_sql.cpp"
    break;

  case 146: /* comp_op: EXISTS  */
#line 1076 "yacc_sql.y"
              { (yyval.comp) = EXISTS_OP;}
#line 3153 "yacc_sql.cpp"
    break;

  case 147: /* comp_op: NOT EXISTS  */
#line 1077 "yacc_sql.y"
                  { (yyval.comp) = NOT_EXISTS;}
#line 3159 "yacc_sql.cpp"
    break;

  case 148: /* group_by: %empty  */
#line 1083 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 3167 "yacc_sql.cpp"
    break;

  case 149: /* group_by: GROUP BY rel_attrs  */
#line 1086 "yacc_sql.y"
                         {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 3175 "yacc_sql.cpp"
    break;

  case 150: /* rel_attrs: rel_attr  */
#line 1092 "yacc_sql.y"
           {
    // std::vector<std::unique_ptr<Expression>> *
    auto field = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name);
    (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>();
    (yyval.expression_list)->emplace_back(field);
  }
#line 3186 "yacc_sql.cpp"
    break;

  case 151: /* rel_attrs: rel_attr COMMA rel_attrs  */
#line 1098 "yacc_sql.y"
                             {
    (yyval.expression_list) = (yyvsp[0].expression_list);
    auto field = new UnboundFieldExpr((yyvsp[-2].rel_attr)->relation_name,(yyvsp[-2].rel_attr)->attribute_name);
    (yyval.expression_list)->emplace_back(field);
    delete (yyvsp[-2].rel_attr);
  }
#line 3197 "yacc_sql.cpp"
    break;

  case 152: /* having_stmt: %empty  */
#line 1106 "yacc_sql.y"
                {
      (yyval.condition_list) = nullptr;
    }
#line 3205 "yacc_sql.cpp"
    break;

  case 153: /* having_stmt: HAVING condition_list  */
#line 1109 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 3213 "yacc_sql.cpp"
    break;

  case 154: /* order_by: %empty  */
#line 1147 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 3221 "yacc_sql.cpp"
    break;

  case 155: /* order_by: ORDER BY order_list  */
#line 1150 "yacc_sql.y"
                          {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 3229 "yacc_sql.cpp"
    break;

  case 156: /* order_list: rel_attr  */
#line 1155 "yacc_sql.y"
           {
    //std::cout << "[1]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[0].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[0].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[0].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3244 "yacc_sql.cpp"
    break;

  case 157: /* order_list: rel_attr COMMA order_list  */
#line 1165 "yacc_sql.y"
                              {
    //std::cout << "[2]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-2].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-2].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-2].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3259 "yacc_sql.cpp"
    break;

  case 158: /* order_list: rel_attr ASC  */
#line 1175 "yacc_sql.y"
                 {
    //std::cout << "[3]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
  }
#line 3274 "yacc_sql.cpp"
    break;

  case 159: /* order_list: rel_attr ASC COMMA order_list  */
#line 1185 "yacc_sql.y"
                                  {
    //std::cout << "[4]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = true;
    delete (yyvsp[-3].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3289 "yacc_sql.cpp"
    break;

  case 160: /* order_list: rel_attr DESC  */
#line 1195 "yacc_sql.y"
                  {
    //std::cout << "[5]\n";
    (yyval.order_by_list) = new vector<OrderBySqlNode>();
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-1].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-1].rel_attr)->attribute_name;
    node.asc = false;
    delete (yyvsp[-1].rel_attr);
    (yyval.order_by_list)->emplace_back(std::move(node));
    std::cout << (*(yyval.order_by_list))[0].attribute_name << '\n';
  }
#line 3305 "yacc_sql.cpp"
    break;

  case 161: /* order_list: rel_attr DESC COMMA order_list  */
#line 1206 "yacc_sql.y"
                                   {
    //std::cout << "[6]\n";
    (yyval.order_by_list) = (yyvsp[0].order_by_list);
    OrderBySqlNode node; 
    node.table_name = (yyvsp[-3].rel_attr)->relation_name;
    node.attribute_name = (yyvsp[-3].rel_attr)->attribute_name;
    node.asc = false;
    delete (yyvsp[-3].rel_attr);
    (yyval.order_by_list)->emplace((yyval.order_by_list)->begin(), std::move(node));
  }
#line 3320 "yacc_sql.cpp"
    break;

  case 162: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1233 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3334 "yacc_sql.cpp"
    break;

  case 163: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1246 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3343 "yacc_sql.cpp"
    break;

  case 164: /* set_variable_stmt: SET ID EQ value  */
#line 1254 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3355 "yacc_sql.cpp"
    break;


#line 3359 "yacc_sql.cpp"

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

#line 1266 "yacc_sql.y"

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
