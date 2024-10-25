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
  YYSYMBOL_DATE_T = 37,                    /* DATE_T  */
  YYSYMBOL_LIKE = 38,                      /* LIKE  */
  YYSYMBOL_NOT = 39,                       /* NOT  */
  YYSYMBOL_VECTOR_T = 40,                  /* VECTOR_T  */
  YYSYMBOL_HELP = 41,                      /* HELP  */
  YYSYMBOL_EXIT = 42,                      /* EXIT  */
  YYSYMBOL_DOT = 43,                       /* DOT  */
  YYSYMBOL_INTO = 44,                      /* INTO  */
  YYSYMBOL_VALUES = 45,                    /* VALUES  */
  YYSYMBOL_FROM = 46,                      /* FROM  */
  YYSYMBOL_WHERE = 47,                     /* WHERE  */
  YYSYMBOL_AND = 48,                       /* AND  */
  YYSYMBOL_SET = 49,                       /* SET  */
  YYSYMBOL_ON = 50,                        /* ON  */
  YYSYMBOL_LOAD = 51,                      /* LOAD  */
  YYSYMBOL_DATA = 52,                      /* DATA  */
  YYSYMBOL_INFILE = 53,                    /* INFILE  */
  YYSYMBOL_EXPLAIN = 54,                   /* EXPLAIN  */
  YYSYMBOL_STORAGE = 55,                   /* STORAGE  */
  YYSYMBOL_FORMAT = 56,                    /* FORMAT  */
  YYSYMBOL_EQ = 57,                        /* EQ  */
  YYSYMBOL_LT = 58,                        /* LT  */
  YYSYMBOL_GT = 59,                        /* GT  */
  YYSYMBOL_LE = 60,                        /* LE  */
  YYSYMBOL_GE = 61,                        /* GE  */
  YYSYMBOL_NE = 62,                        /* NE  */
  YYSYMBOL_L2_DISTANCE = 63,               /* L2_DISTANCE  */
  YYSYMBOL_INNER_PRODUCT = 64,             /* INNER_PRODUCT  */
  YYSYMBOL_COSINE_DISTANCE = 65,           /* COSINE_DISTANCE  */
  YYSYMBOL_NUMBER = 66,                    /* NUMBER  */
  YYSYMBOL_FLOAT = 67,                     /* FLOAT  */
  YYSYMBOL_ID = 68,                        /* ID  */
  YYSYMBOL_SSS = 69,                       /* SSS  */
  YYSYMBOL_VECTOR_DATA = 70,               /* VECTOR_DATA  */
  YYSYMBOL_71_ = 71,                       /* '+'  */
  YYSYMBOL_72_ = 72,                       /* '-'  */
  YYSYMBOL_73_ = 73,                       /* '*'  */
  YYSYMBOL_74_ = 74,                       /* '/'  */
  YYSYMBOL_UMINUS = 75,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 76,                  /* $accept  */
  YYSYMBOL_commands = 77,                  /* commands  */
  YYSYMBOL_command_wrapper = 78,           /* command_wrapper  */
  YYSYMBOL_exit_stmt = 79,                 /* exit_stmt  */
  YYSYMBOL_help_stmt = 80,                 /* help_stmt  */
  YYSYMBOL_sync_stmt = 81,                 /* sync_stmt  */
  YYSYMBOL_alias_stmt = 82,                /* alias_stmt  */
  YYSYMBOL_begin_stmt = 83,                /* begin_stmt  */
  YYSYMBOL_commit_stmt = 84,               /* commit_stmt  */
  YYSYMBOL_rollback_stmt = 85,             /* rollback_stmt  */
  YYSYMBOL_drop_table_stmt = 86,           /* drop_table_stmt  */
  YYSYMBOL_show_tables_stmt = 87,          /* show_tables_stmt  */
  YYSYMBOL_desc_table_stmt = 88,           /* desc_table_stmt  */
  YYSYMBOL_create_index_stmt = 89,         /* create_index_stmt  */
  YYSYMBOL_unique_stmt = 90,               /* unique_stmt  */
  YYSYMBOL_attr_list = 91,                 /* attr_list  */
  YYSYMBOL_drop_index_stmt = 92,           /* drop_index_stmt  */
  YYSYMBOL_create_table_stmt = 93,         /* create_table_stmt  */
  YYSYMBOL_attr_def_list = 94,             /* attr_def_list  */
  YYSYMBOL_attr_def = 95,                  /* attr_def  */
  YYSYMBOL_null_def = 96,                  /* null_def  */
  YYSYMBOL_number = 97,                    /* number  */
  YYSYMBOL_type = 98,                      /* type  */
  YYSYMBOL_insert_stmt = 99,               /* insert_stmt  */
  YYSYMBOL_value_list = 100,               /* value_list  */
  YYSYMBOL_insert_val = 101,               /* insert_val  */
  YYSYMBOL_value = 102,                    /* value  */
  YYSYMBOL_storage_format = 103,           /* storage_format  */
  YYSYMBOL_delete_stmt = 104,              /* delete_stmt  */
  YYSYMBOL_update_stmt = 105,              /* update_stmt  */
  YYSYMBOL_assignment_list = 106,          /* assignment_list  */
  YYSYMBOL_assignment = 107,               /* assignment  */
  YYSYMBOL_select_stmt = 108,              /* select_stmt  */
  YYSYMBOL_calc_stmt = 109,                /* calc_stmt  */
  YYSYMBOL_expression_list = 110,          /* expression_list  */
  YYSYMBOL_expression = 111,               /* expression  */
  YYSYMBOL_aggr_func_expr = 112,           /* aggr_func_expr  */
  YYSYMBOL_rel_attr = 113,                 /* rel_attr  */
  YYSYMBOL_relation = 114,                 /* relation  */
  YYSYMBOL_rel_list = 115,                 /* rel_list  */
  YYSYMBOL_on_stmt = 116,                  /* on_stmt  */
  YYSYMBOL_where = 117,                    /* where  */
  YYSYMBOL_condition_list = 118,           /* condition_list  */
  YYSYMBOL_condition = 119,                /* condition  */
  YYSYMBOL_comp_op = 120,                  /* comp_op  */
  YYSYMBOL_group_by = 121,                 /* group_by  */
  YYSYMBOL_rel_attrs = 122,                /* rel_attrs  */
  YYSYMBOL_having_stmt = 123,              /* having_stmt  */
  YYSYMBOL_order_by = 124,                 /* order_by  */
  YYSYMBOL_order_list = 125,               /* order_list  */
  YYSYMBOL_load_data_stmt = 126,           /* load_data_stmt  */
  YYSYMBOL_explain_stmt = 127,             /* explain_stmt  */
  YYSYMBOL_set_variable_stmt = 128,        /* set_variable_stmt  */
  YYSYMBOL_opt_semicolon = 129             /* opt_semicolon  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  71
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   320

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  76
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  54
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   326


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
       2,     2,    73,    71,     2,    72,     2,    74,     2,     2,
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
      65,    66,    67,    68,    69,    70,    75
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   231,   231,   239,   240,   241,   242,   243,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   255,
     256,   257,   258,   262,   268,   273,   279,   282,   287,   293,
     299,   305,   312,   318,   326,   346,   349,   354,   357,   368,
     378,   402,   405,   418,   431,   443,   446,   449,   453,   456,
     457,   458,   459,   460,   463,   482,   485,   496,   499,   507,
     513,   517,   521,   527,   551,   554,   561,   572,   587,   591,
     597,   604,   616,   660,   669,   678,   693,   699,   706,   709,
     712,   716,   719,   722,   726,   731,   734,   737,   740,   751,
     755,   759,   767,   773,   783,   788,   791,   804,   822,   826,
     833,   836,   842,   845,   850,   857,   862,   869,   876,   937,
     938,   939,   940,   941,   942,   943,   944,   945,   946,   952,
     955,   961,   967,   975,   978,  1016,  1019,  1024,  1034,  1044,
    1054,  1064,  1075,  1101,  1114,  1122,  1132,  1133
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
  "INSERT", "IS", "DELETE", "UPDATE", "UNIQUE", "LBRACE", "RBRACE",
  "COMMA", "INNER", "JOIN", "TRX_BEGIN", "TRX_COMMIT", "TRX_ROLLBACK",
  "INT_T", "STRING_T", "FLOAT_T", "DATE_T", "LIKE", "NOT", "VECTOR_T",
  "HELP", "EXIT", "DOT", "INTO", "VALUES", "FROM", "WHERE", "AND", "SET",
  "ON", "LOAD", "DATA", "INFILE", "EXPLAIN", "STORAGE", "FORMAT", "EQ",
  "LT", "GT", "LE", "GE", "NE", "L2_DISTANCE", "INNER_PRODUCT",
  "COSINE_DISTANCE", "NUMBER", "FLOAT", "ID", "SSS", "VECTOR_DATA", "'+'",
  "'-'", "'*'", "'/'", "UMINUS", "$accept", "commands", "command_wrapper",
  "exit_stmt", "help_stmt", "sync_stmt", "alias_stmt", "begin_stmt",
  "commit_stmt", "rollback_stmt", "drop_table_stmt", "show_tables_stmt",
  "desc_table_stmt", "create_index_stmt", "unique_stmt", "attr_list",
  "drop_index_stmt", "create_table_stmt", "attr_def_list", "attr_def",
  "null_def", "number", "type", "insert_stmt", "value_list", "insert_val",
  "value", "storage_format", "delete_stmt", "update_stmt",
  "assignment_list", "assignment", "select_stmt", "calc_stmt",
  "expression_list", "expression", "aggr_func_expr", "rel_attr",
  "relation", "rel_list", "on_stmt", "where", "condition_list",
  "condition", "comp_op", "group_by", "rel_attrs", "having_stmt",
  "order_by", "order_list", "load_data_stmt", "explain_stmt",
  "set_variable_stmt", "opt_semicolon", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-227)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     153,     4,    28,   163,   163,   -57,    12,  -227,   -12,    -6,
     -26,  -227,  -227,  -227,  -227,  -227,     6,    46,   153,   100,
      98,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,    45,  -227,    96,    54,    55,   163,   104,   114,   131,
    -227,  -227,   -13,  -227,  -227,   163,  -227,  -227,  -227,    -1,
    -227,  -227,    70,  -227,  -227,    56,    92,   119,   118,   143,
    -227,  -227,  -227,  -227,   171,   124,  -227,   149,    72,   163,
     163,   163,   152,   132,  -227,   133,   163,   163,   163,   163,
     177,   138,   164,   167,   155,   121,   165,   182,   205,   188,
    -227,   170,   175,   180,  -227,   230,    -7,  -227,  -227,   -56,
     -56,  -227,  -227,   163,  -227,   243,   233,   -10,  -227,   203,
     167,   239,  -227,   224,   229,   242,   204,  -227,   163,   163,
     163,  -227,  -227,  -227,    17,    48,   223,    90,  -227,   225,
      38,  -227,   155,   263,  -227,  -227,  -227,  -227,  -227,     2,
     182,   247,   249,    82,   139,   166,   138,   246,   167,  -227,
     121,   250,  -227,   238,  -227,   241,  -227,  -227,  -227,  -227,
    -227,  -227,    24,    69,   -10,  -227,  -227,  -227,   218,  -227,
     221,   275,  -227,   242,   234,   222,  -227,  -227,  -227,   243,
     138,   284,  -227,    48,   265,  -227,  -227,  -227,   109,  -227,
     109,  -227,  -227,  -227,   266,  -227,  -227,   240,  -227,   267,
      17,   243,   290,   286,   250,  -227,     9,   244,   231,   271,
    -227,   252,   232,   -10,   287,  -227,  -227,   235,   267,  -227,
     -10,    17,   262,   278,  -227,  -227,   303,  -227,  -227,  -227,
    -227,  -227,   232,   232,  -227,   103,  -227,   280,   281,   232,
     232,   232,  -227,  -227,  -227
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    35,     0,     0,     0,     0,     0,    25,     0,     0,
       0,    28,    29,    30,    24,    23,     0,     0,     0,     0,
     136,    22,    21,    14,    15,    16,    17,     9,    10,    11,
      12,    13,     8,     5,     7,     6,     4,     3,    18,    19,
      20,     0,    36,     0,     0,     0,     0,     0,     0,     0,
      60,    61,    92,    62,    63,     0,    78,    76,    73,    26,
      85,    77,     0,    33,    32,     0,     0,     0,     0,     0,
     134,     1,   137,     2,     0,     0,    31,     0,     0,     0,
       0,     0,     0,     0,    84,     0,     0,     0,     0,     0,
      74,     0,     0,   100,     0,     0,     0,     0,     0,     0,
      83,     0,     0,     0,    90,     0,    26,    93,    27,    79,
      80,    81,    82,     0,    94,    26,     0,   102,    66,     0,
     100,    68,   135,     0,     0,    41,     0,    39,     0,     0,
       0,    91,    89,    75,    95,     0,     0,     0,   101,   103,
       0,    67,     0,     0,    49,    50,    51,    52,    53,    45,
       0,     0,     0,     0,     0,     0,     0,     0,   100,    59,
       0,    55,    57,   118,   115,     0,   109,   110,   111,   112,
     113,   114,     0,     0,   102,    71,    70,    69,     0,    46,
       0,     0,    44,    41,    64,     0,    86,    87,    88,    26,
       0,   119,    58,     0,     0,   117,   116,   108,   107,   106,
     105,   104,   133,    48,     0,    47,    42,     0,    40,    37,
      95,    26,     0,   123,    55,    54,    45,     0,     0,     0,
      96,    98,     0,   102,   125,    56,    43,     0,    37,    34,
     102,    95,    92,   121,   120,   124,     0,    72,    65,    38,
      99,    97,     0,     0,   122,   127,   126,   129,   131,     0,
       0,     0,   128,   130,   132
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -227,  -227,   292,  -227,  -227,  -227,  -108,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,    83,  -227,  -227,   129,   168,
      97,  -227,  -227,  -227,   101,   123,   -91,  -227,  -227,  -227,
     172,  -227,  -227,  -227,    -2,    -3,  -227,  -216,  -151,  -200,
    -227,  -111,  -155,  -227,   183,  -227,    75,  -227,  -227,  -226,
    -227,  -227,  -227,  -227
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    22,    23,    90,    24,    25,    26,
      27,    28,    29,    30,    43,   219,    31,    32,   151,   125,
     182,   204,   149,    33,   194,   161,    57,   208,    34,    35,
     120,   121,    36,    37,    58,   137,    60,    61,   115,   158,
     231,   118,   138,   139,   172,   213,   234,   224,   237,   246,
      38,    39,    40,    73
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    59,    62,   136,   122,   189,   233,   134,    85,   141,
     220,    63,    41,    82,    85,   179,    46,    88,    89,   201,
     132,    64,   179,   252,   253,   254,   233,   245,   180,    42,
      83,   241,    65,   245,   245,   245,    44,   197,    45,   211,
      66,   181,    67,    78,   162,   156,   157,   191,   181,   176,
      46,   175,    84,    47,    48,    49,    50,    51,    52,    53,
      54,   159,    55,    56,    86,    87,    88,    89,   235,   192,
      86,    87,    88,    89,    68,   240,   101,   102,   103,   106,
     105,   210,   199,   109,   110,   111,   112,    47,    48,    49,
      50,    51,    52,    53,    54,    46,    55,    56,    69,   100,
      71,    72,   162,   221,    50,    51,    75,    53,    54,   186,
      59,   133,   163,    74,    50,    51,    91,    53,    54,   247,
     160,   248,    76,    77,    92,   153,   154,   155,   164,   165,
      79,   249,    47,    48,    49,    50,    51,    52,    53,    54,
      80,    55,    56,    86,    87,    88,    89,   166,   167,   168,
     169,   170,   171,    86,    87,    88,    89,    81,     1,     2,
      93,    86,    87,    88,    89,     3,   187,     4,    94,   198,
     200,     5,     6,     7,     8,    95,     9,    10,    46,   104,
      86,    87,    88,    89,    11,    12,    13,    50,    51,    46,
      53,    54,    98,   188,    14,    15,    96,    97,   128,    99,
     107,   108,    16,   129,    17,   113,   114,    18,   130,   116,
      86,    87,    88,    89,   117,    47,    48,    49,    50,    51,
      52,    53,    54,   119,    55,    56,    47,    48,    49,    50,
      51,    52,    53,    54,   123,    55,    56,    86,    87,    88,
      89,    86,    87,    88,    89,   163,    86,    87,    88,    89,
     124,    86,    87,    88,    89,   126,   127,   131,    85,   135,
     140,   164,   165,   144,   145,   146,   147,   142,   143,   148,
     150,   178,   152,   174,   184,   185,   190,   195,   193,   196,
     166,   167,   168,   169,   170,   171,   202,   203,   205,   207,
     209,   212,   215,   216,   222,   218,   217,   223,   229,   228,
     232,   227,   230,   238,   236,    83,   242,   243,   250,   251,
      70,   239,   206,   226,   177,   225,   214,   244,   183,     0,
     173
};

static const yytype_int16 yycheck[] =
{
       3,     4,     4,    13,    95,   156,   222,   115,    15,   120,
     210,    68,     8,    26,    15,    13,    26,    73,    74,   174,
      27,     9,    13,   249,   250,   251,   242,   243,    26,    25,
      43,   231,    44,   249,   250,   251,     8,    13,    10,   190,
      46,    39,    68,    46,   135,    28,    29,   158,    39,   140,
      26,    13,    55,    63,    64,    65,    66,    67,    68,    69,
      70,    13,    72,    73,    71,    72,    73,    74,   223,   160,
      71,    72,    73,    74,    68,   230,    79,    80,    81,    82,
      82,   189,    13,    86,    87,    88,    89,    63,    64,    65,
      66,    67,    68,    69,    70,    26,    72,    73,    52,    27,
       0,     3,   193,   211,    66,    67,    10,    69,    70,    27,
     113,   113,    22,    68,    66,    67,    46,    69,    70,    16,
      72,    18,    68,    68,    68,   128,   129,   130,    38,    39,
      26,    28,    63,    64,    65,    66,    67,    68,    69,    70,
      26,    72,    73,    71,    72,    73,    74,    57,    58,    59,
      60,    61,    62,    71,    72,    73,    74,    26,     5,     6,
      68,    71,    72,    73,    74,    12,    27,    14,    49,   172,
     173,    18,    19,    20,    21,    57,    23,    24,    26,    27,
      71,    72,    73,    74,    31,    32,    33,    66,    67,    26,
      69,    70,    68,    27,    41,    42,    53,    26,    28,    50,
      68,    68,    49,    28,    51,    28,    68,    54,    28,    45,
      71,    72,    73,    74,    47,    63,    64,    65,    66,    67,
      68,    69,    70,    68,    72,    73,    63,    64,    65,    66,
      67,    68,    69,    70,    69,    72,    73,    71,    72,    73,
      74,    71,    72,    73,    74,    22,    71,    72,    73,    74,
      68,    71,    72,    73,    74,    50,    68,    27,    15,    26,
      57,    38,    39,    34,    35,    36,    37,    28,    44,    40,
      28,     8,    68,    48,    27,    26,    30,    39,    28,    38,
      57,    58,    59,    60,    61,    62,    68,    66,    13,    55,
      68,     7,    27,    27,     4,    28,    56,    11,    27,    68,
      68,    57,    50,    68,    17,    43,    28,     4,    28,    28,
      18,   228,   183,   216,   142,   214,   193,   242,   150,    -1,
     137
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     5,     6,    12,    14,    18,    19,    20,    21,    23,
      24,    31,    32,    33,    41,    42,    49,    51,    54,    77,
      78,    79,    80,    81,    83,    84,    85,    86,    87,    88,
      89,    92,    93,    99,   104,   105,   108,   109,   126,   127,
     128,     8,    25,    90,     8,    10,    26,    63,    64,    65,
      66,    67,    68,    69,    70,    72,    73,   102,   110,   111,
     112,   113,   110,    68,     9,    44,    46,    68,    68,    52,
      78,     0,     3,   129,    68,    10,    68,    68,   111,    26,
      26,    26,    26,    43,   111,    15,    71,    72,    73,    74,
      82,    46,    68,    68,    49,    57,    53,    26,    68,    50,
      27,   111,   111,   111,    27,   110,   111,    68,    68,   111,
     111,   111,   111,    28,    68,   114,    45,    47,   117,    68,
     106,   107,   102,    69,    68,    95,    50,    68,    28,    28,
      28,    27,    27,   110,    82,    26,    13,   111,   118,   119,
      57,   117,    28,    44,    34,    35,    36,    37,    40,    98,
      28,    94,    68,   111,   111,   111,    28,    29,   115,    13,
      72,   101,   102,    22,    38,    39,    57,    58,    59,    60,
      61,    62,   120,   120,    48,    13,   102,   106,     8,    13,
      26,    39,    96,    95,    27,    26,    27,    27,    27,   114,
      30,   117,   102,    28,   100,    39,    38,    13,   111,    13,
     111,   118,    68,    66,    97,    13,    94,    55,   103,    68,
      82,   114,     7,   121,   101,    27,    27,    56,    28,    91,
     115,    82,     4,    11,   123,   100,    96,    57,    68,    27,
      50,   116,    68,   113,   122,   118,    17,   124,    68,    91,
     118,   115,    28,     4,   122,   113,   125,    16,    18,    28,
      28,    28,   125,   125,   125
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_uint8 yyr1[] =
{
       0,    76,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    79,    80,    81,    82,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    90,    91,    91,    92,
      93,    94,    94,    95,    95,    96,    96,    96,    97,    98,
      98,    98,    98,    98,    99,   100,   100,   101,   101,   101,
     102,   102,   102,   102,   103,   103,   104,   105,   106,   106,
     107,   107,   108,   109,   110,   110,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   113,   113,   114,   115,   115,   115,   116,   116,
     117,   117,   118,   118,   118,   119,   119,   119,   119,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   122,   122,   123,   123,   124,   124,   125,   125,   125,
     125,   125,   125,   126,   127,   128,   129,   129
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     2,     1,     1,
       1,     3,     2,     2,    10,     0,     1,     0,     3,     5,
       8,     0,     3,     6,     3,     0,     1,     2,     1,     1,
       1,     1,     1,     1,     8,     0,     3,     1,     2,     1,
       1,     1,     1,     1,     0,     4,     4,     5,     1,     3,
       3,     3,    10,     2,     2,     4,     1,     1,     1,     3,
       3,     3,     3,     3,     2,     1,     6,     6,     6,     4,
       3,     4,     1,     3,     1,     0,     4,     6,     0,     2,
       0,     2,     0,     1,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     0,
       3,     1,     3,     0,     2,     0,     3,     1,     3,     2,
       4,     2,     4,     7,     2,     4,     0,     1
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
#line 232 "yacc_sql.y"
  {
    std::unique_ptr<ParsedSqlNode> sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[-1].sql_node));
    sql_result->add_sql_node(std::move(sql_node));
  }
#line 1847 "yacc_sql.cpp"
    break;

  case 23: /* exit_stmt: EXIT  */
#line 262 "yacc_sql.y"
         {
      (void)yynerrs;  // 这么写为了消除yynerrs未使用的告警。如果你有更好的方法欢迎提PR
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXIT);
    }
#line 1856 "yacc_sql.cpp"
    break;

  case 24: /* help_stmt: HELP  */
#line 268 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_HELP);
    }
#line 1864 "yacc_sql.cpp"
    break;

  case 25: /* sync_stmt: SYNC  */
#line 273 "yacc_sql.y"
         {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SYNC);
    }
#line 1872 "yacc_sql.cpp"
    break;

  case 26: /* alias_stmt: %empty  */
#line 279 "yacc_sql.y"
  {
    (yyval.string) = nullptr;
  }
#line 1880 "yacc_sql.cpp"
    break;

  case 27: /* alias_stmt: ALIAS ID  */
#line 282 "yacc_sql.y"
             {
    (yyval.string) = (yyvsp[0].string);
  }
#line 1888 "yacc_sql.cpp"
    break;

  case 28: /* begin_stmt: TRX_BEGIN  */
#line 287 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_BEGIN);
    }
#line 1896 "yacc_sql.cpp"
    break;

  case 29: /* commit_stmt: TRX_COMMIT  */
#line 293 "yacc_sql.y"
               {
      (yyval.sql_node) = new ParsedSqlNode(SCF_COMMIT);
    }
#line 1904 "yacc_sql.cpp"
    break;

  case 30: /* rollback_stmt: TRX_ROLLBACK  */
#line 299 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_ROLLBACK);
    }
#line 1912 "yacc_sql.cpp"
    break;

  case 31: /* drop_table_stmt: DROP TABLE ID  */
#line 305 "yacc_sql.y"
                  {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_TABLE);
      (yyval.sql_node)->drop_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1922 "yacc_sql.cpp"
    break;

  case 32: /* show_tables_stmt: SHOW TABLES  */
#line 312 "yacc_sql.y"
                {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SHOW_TABLES);
    }
#line 1930 "yacc_sql.cpp"
    break;

  case 33: /* desc_table_stmt: DESC ID  */
#line 318 "yacc_sql.y"
             {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DESC_TABLE);
      (yyval.sql_node)->desc_table.relation_name = (yyvsp[0].string);
      free((yyvsp[0].string));
    }
#line 1940 "yacc_sql.cpp"
    break;

  case 34: /* create_index_stmt: CREATE unique_stmt INDEX ID ON ID LBRACE ID attr_list RBRACE  */
#line 327 "yacc_sql.y"
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
#line 1961 "yacc_sql.cpp"
    break;

  case 35: /* unique_stmt: %empty  */
#line 346 "yacc_sql.y"
  {
    (yyval.boolean) = false;
  }
#line 1969 "yacc_sql.cpp"
    break;

  case 36: /* unique_stmt: UNIQUE  */
#line 349 "yacc_sql.y"
           {
    (yyval.boolean) = true;
  }
#line 1977 "yacc_sql.cpp"
    break;

  case 37: /* attr_list: %empty  */
#line 354 "yacc_sql.y"
  {
    (yyval.relation_list) = nullptr;
  }
#line 1985 "yacc_sql.cpp"
    break;

  case 38: /* attr_list: COMMA ID attr_list  */
#line 357 "yacc_sql.y"
                       {
    if ((yyvsp[0].relation_list) != nullptr) {
      (yyval.relation_list) = (yyvsp[0].relation_list);
    } else {
      (yyval.relation_list) = new vector<std::string>;
    }
    (yyval.relation_list)->emplace_back((yyvsp[-1].string));
    free((yyvsp[-1].string));
  }
#line 1999 "yacc_sql.cpp"
    break;

  case 39: /* drop_index_stmt: DROP INDEX ID ON ID  */
#line 369 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DROP_INDEX);
      (yyval.sql_node)->drop_index.index_name = (yyvsp[-2].string);
      (yyval.sql_node)->drop_index.relation_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2011 "yacc_sql.cpp"
    break;

  case 40: /* create_table_stmt: CREATE TABLE ID LBRACE attr_def attr_def_list RBRACE storage_format  */
#line 379 "yacc_sql.y"
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
#line 2036 "yacc_sql.cpp"
    break;

  case 41: /* attr_def_list: %empty  */
#line 402 "yacc_sql.y"
    {
      (yyval.attr_infos) = nullptr;
    }
#line 2044 "yacc_sql.cpp"
    break;

  case 42: /* attr_def_list: COMMA attr_def attr_def_list  */
#line 406 "yacc_sql.y"
    {
      if ((yyvsp[0].attr_infos) != nullptr) {
        (yyval.attr_infos) = (yyvsp[0].attr_infos);
      } else {
        (yyval.attr_infos) = new std::vector<AttrInfoSqlNode>;
      }
      (yyval.attr_infos)->emplace_back(*(yyvsp[-1].attr_info));
      delete (yyvsp[-1].attr_info);
    }
#line 2058 "yacc_sql.cpp"
    break;

  case 43: /* attr_def: ID type LBRACE number RBRACE null_def  */
#line 419 "yacc_sql.y"
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
#line 2075 "yacc_sql.cpp"
    break;

  case 44: /* attr_def: ID type null_def  */
#line 432 "yacc_sql.y"
    {
      (yyval.attr_info) = new AttrInfoSqlNode;
      (yyval.attr_info)->type = (AttrType)(yyvsp[-1].number);
      (yyval.attr_info)->name = (yyvsp[-2].string);
      (yyval.attr_info)->length = 4;
      free((yyvsp[-2].string));
      (yyval.attr_info)->nullable = ((yyvsp[0].number) == 1);
    }
#line 2088 "yacc_sql.cpp"
    break;

  case 45: /* null_def: %empty  */
#line 443 "yacc_sql.y"
  {
    (yyval.number) = 0;
  }
#line 2096 "yacc_sql.cpp"
    break;

  case 46: /* null_def: null  */
#line 446 "yacc_sql.y"
         {
    (yyval.number) = 1;
  }
#line 2104 "yacc_sql.cpp"
    break;

  case 47: /* null_def: NOT null  */
#line 449 "yacc_sql.y"
             {
    (yyval.number) = 0;
  }
#line 2112 "yacc_sql.cpp"
    break;

  case 48: /* number: NUMBER  */
#line 453 "yacc_sql.y"
           {(yyval.number) = (yyvsp[0].number);}
#line 2118 "yacc_sql.cpp"
    break;

  case 49: /* type: INT_T  */
#line 456 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::INTS); }
#line 2124 "yacc_sql.cpp"
    break;

  case 50: /* type: STRING_T  */
#line 457 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::CHARS); }
#line 2130 "yacc_sql.cpp"
    break;

  case 51: /* type: FLOAT_T  */
#line 458 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::FLOATS); }
#line 2136 "yacc_sql.cpp"
    break;

  case 52: /* type: DATE_T  */
#line 459 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::DATES); }
#line 2142 "yacc_sql.cpp"
    break;

  case 53: /* type: VECTOR_T  */
#line 460 "yacc_sql.y"
               { (yyval.number) = static_cast<int>(AttrType::VECTORS); }
#line 2148 "yacc_sql.cpp"
    break;

  case 54: /* insert_stmt: INSERT INTO ID VALUES LBRACE insert_val value_list RBRACE  */
#line 464 "yacc_sql.y"
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
#line 2165 "yacc_sql.cpp"
    break;

  case 55: /* value_list: %empty  */
#line 482 "yacc_sql.y"
    {
      (yyval.value_list) = nullptr;
    }
#line 2173 "yacc_sql.cpp"
    break;

  case 56: /* value_list: COMMA insert_val value_list  */
#line 485 "yacc_sql.y"
                                   { 
      if ((yyvsp[0].value_list) != nullptr) {
        (yyval.value_list) = (yyvsp[0].value_list);
      } else {
        (yyval.value_list) = new std::vector<Value>;
      }
      (yyval.value_list)->emplace_back(*(yyvsp[-1].value));
      delete (yyvsp[-1].value);
    }
#line 2187 "yacc_sql.cpp"
    break;

  case 57: /* insert_val: value  */
#line 496 "yacc_sql.y"
         {
    (yyval.value) = (yyvsp[0].value);
  }
#line 2195 "yacc_sql.cpp"
    break;

  case 58: /* insert_val: '-' value  */
#line 499 "yacc_sql.y"
              {
    (yyval.value) = (yyvsp[0].value);
    if ((yyval.value)->attr_type() == AttrType::INTS) {
      (yyval.value)->set_int((yyval.value)->get_int() *(-1));
    } else if ((yyval.value)->attr_type() == AttrType::FLOATS) {
      (yyval.value)->set_float((yyval.value)->get_float() *(-1));
    }
  }
#line 2208 "yacc_sql.cpp"
    break;

  case 59: /* insert_val: null  */
#line 507 "yacc_sql.y"
         {
    (yyval.value) = new Value;
    (yyval.value)->set_null();
  }
#line 2217 "yacc_sql.cpp"
    break;

  case 60: /* value: NUMBER  */
#line 513 "yacc_sql.y"
           {
      (yyval.value) = new Value((int)(yyvsp[0].number));
      (yyloc) = (yylsp[0]);
    }
#line 2226 "yacc_sql.cpp"
    break;

  case 61: /* value: FLOAT  */
#line 517 "yacc_sql.y"
           {
      (yyval.value) = new Value((float)(yyvsp[0].floats));
      (yyloc) = (yylsp[0]);
    }
#line 2235 "yacc_sql.cpp"
    break;

  case 62: /* value: SSS  */
#line 521 "yacc_sql.y"
         {
      char *tmp = common::substr((yyvsp[0].string),1,strlen((yyvsp[0].string))-2);
      (yyval.value) = new Value(tmp);
      free(tmp);
      free((yyvsp[0].string));
    }
#line 2246 "yacc_sql.cpp"
    break;

  case 63: /* value: VECTOR_DATA  */
#line 527 "yacc_sql.y"
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
#line 2273 "yacc_sql.cpp"
    break;

  case 64: /* storage_format: %empty  */
#line 551 "yacc_sql.y"
    {
      (yyval.string) = nullptr;
    }
#line 2281 "yacc_sql.cpp"
    break;

  case 65: /* storage_format: STORAGE FORMAT EQ ID  */
#line 555 "yacc_sql.y"
    {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2289 "yacc_sql.cpp"
    break;

  case 66: /* delete_stmt: DELETE FROM ID where  */
#line 562 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_DELETE);
      (yyval.sql_node)->deletion.relation_name = (yyvsp[-1].string);
      if ((yyvsp[0].condition_list) != nullptr) {
        (yyval.sql_node)->deletion.conditions = (yyvsp[0].condition_list);
      }
      free((yyvsp[-1].string));
    }
#line 2302 "yacc_sql.cpp"
    break;

  case 67: /* update_stmt: UPDATE ID SET assignment_list where  */
#line 573 "yacc_sql.y"
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
#line 2318 "yacc_sql.cpp"
    break;

  case 68: /* assignment_list: assignment  */
#line 587 "yacc_sql.y"
             {
    (yyval.assignment_ptr_list) = new vector<Assignment*>();
    (yyval.assignment_ptr_list)->emplace_back((yyvsp[0].assignment_ptr));
  }
#line 2327 "yacc_sql.cpp"
    break;

  case 69: /* assignment_list: assignment COMMA assignment_list  */
#line 591 "yacc_sql.y"
                                     {
    (yyval.assignment_ptr_list) = (yyvsp[0].assignment_ptr_list);
    (yyval.assignment_ptr_list)->emplace_back((yyvsp[-2].assignment_ptr));
  }
#line 2336 "yacc_sql.cpp"
    break;

  case 70: /* assignment: ID EQ value  */
#line 597 "yacc_sql.y"
              {
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    (yyval.assignment_ptr)->right_hand_side = new ValueExpr(*(yyvsp[0].value));
    delete (yyvsp[0].value);
  }
#line 2348 "yacc_sql.cpp"
    break;

  case 71: /* assignment: ID EQ null  */
#line 604 "yacc_sql.y"
               {
    Value v;
    v.set_null();
    (yyval.assignment_ptr) = new Assignment;
    (yyval.assignment_ptr)->attr_name = string((yyvsp[-2].string));
    free((yyvsp[-2].string));
    (yyval.assignment_ptr)->right_hand_side = new ValueExpr(v);
  }
#line 2361 "yacc_sql.cpp"
    break;

  case 72: /* select_stmt: SELECT expression_list FROM relation alias_stmt rel_list where group_by having_stmt order_by  */
#line 617 "yacc_sql.y"
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
#line 2407 "yacc_sql.cpp"
    break;

  case 73: /* calc_stmt: CALC expression_list  */
#line 661 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_CALC);
      (yyval.sql_node)->calc.expressions.swap(*(yyvsp[0].expression_list));
      delete (yyvsp[0].expression_list);
    }
#line 2417 "yacc_sql.cpp"
    break;

  case 74: /* expression_list: expression alias_stmt  */
#line 670 "yacc_sql.y"
    {
      (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>;
      if ((yyvsp[0].string)) {
        (yyvsp[-1].expression)->set_alias(std::string((yyvsp[0].string)));
        free((yyvsp[0].string));
      }
      (yyval.expression_list)->emplace_back((yyvsp[-1].expression));
    }
#line 2430 "yacc_sql.cpp"
    break;

  case 75: /* expression_list: expression alias_stmt COMMA expression_list  */
#line 679 "yacc_sql.y"
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
#line 2447 "yacc_sql.cpp"
    break;

  case 76: /* expression: value  */
#line 693 "yacc_sql.y"
          {
      cout << "value_expr\n";
      (yyval.expression) = new ValueExpr(*(yyvsp[0].value));
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].value);
    }
#line 2458 "yacc_sql.cpp"
    break;

  case 77: /* expression: rel_attr  */
#line 699 "yacc_sql.y"
               {
      cout << "field_expr\n";
      RelAttrSqlNode *node = (yyvsp[0].rel_attr);
      (yyval.expression) = new UnboundFieldExpr(node->relation_name, node->attribute_name);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
      delete (yyvsp[0].rel_attr);
    }
#line 2470 "yacc_sql.cpp"
    break;

  case 78: /* expression: '*'  */
#line 706 "yacc_sql.y"
          {
      (yyval.expression) = new StarExpr();
    }
#line 2478 "yacc_sql.cpp"
    break;

  case 79: /* expression: expression '+' expression  */
#line 709 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::ADD, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2486 "yacc_sql.cpp"
    break;

  case 80: /* expression: expression '-' expression  */
#line 712 "yacc_sql.y"
                                {
      cout << "minus\n";
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::SUB, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2495 "yacc_sql.cpp"
    break;

  case 81: /* expression: expression '*' expression  */
#line 716 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::MUL, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2503 "yacc_sql.cpp"
    break;

  case 82: /* expression: expression '/' expression  */
#line 719 "yacc_sql.y"
                                {
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::DIV, (yyvsp[-2].expression), (yyvsp[0].expression), sql_string, &(yyloc));
    }
#line 2511 "yacc_sql.cpp"
    break;

  case 83: /* expression: LBRACE expression RBRACE  */
#line 722 "yacc_sql.y"
                               {
      (yyval.expression) = (yyvsp[-1].expression);
      (yyval.expression)->set_name(token_name(sql_string, &(yyloc)));
    }
#line 2520 "yacc_sql.cpp"
    break;

  case 84: /* expression: '-' expression  */
#line 726 "yacc_sql.y"
                                  {
      cout << "negative\n";
      (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::NEGATIVE, (yyvsp[0].expression), nullptr, sql_string, &(yyloc));
    }
#line 2529 "yacc_sql.cpp"
    break;

  case 85: /* expression: aggr_func_expr  */
#line 731 "yacc_sql.y"
                     {
      (yyval.expression) = (yyvsp[0].expression);
    }
#line 2537 "yacc_sql.cpp"
    break;

  case 86: /* expression: L2_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 734 "yacc_sql.y"
                                                            {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::L2_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2545 "yacc_sql.cpp"
    break;

  case 87: /* expression: INNER_PRODUCT LBRACE expression COMMA expression RBRACE  */
#line 737 "yacc_sql.y"
                                                              {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::INNER_PRODUCT, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2553 "yacc_sql.cpp"
    break;

  case 88: /* expression: COSINE_DISTANCE LBRACE expression COMMA expression RBRACE  */
#line 740 "yacc_sql.y"
                                                                {
        (yyval.expression) = create_arithmetic_expression(ArithmeticExpr::Type::COSINE_DISTANCE, (yyvsp[-3].expression), (yyvsp[-1].expression), sql_string, &(yyloc));
    }
#line 2561 "yacc_sql.cpp"
    break;

  case 89: /* aggr_func_expr: ID LBRACE expression RBRACE  */
#line 751 "yacc_sql.y"
                              {
    (yyval.expression) = create_aggregate_expression((yyvsp[-3].string), (yyvsp[-1].expression), sql_string, &(yyloc));
    free((yyvsp[-3].string));
  }
#line 2570 "yacc_sql.cpp"
    break;

  case 90: /* aggr_func_expr: ID LBRACE RBRACE  */
#line 755 "yacc_sql.y"
                     {
    free((yyvsp[-2].string));
    YYERROR;
  }
#line 2579 "yacc_sql.cpp"
    break;

  case 91: /* aggr_func_expr: ID LBRACE expression_list RBRACE  */
#line 759 "yacc_sql.y"
                                     {
    delete (yyvsp[-1].expression_list);
    free((yyvsp[-3].string));
    YYERROR;
  }
#line 2589 "yacc_sql.cpp"
    break;

  case 92: /* rel_attr: ID  */
#line 767 "yacc_sql.y"
       {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      printf("attr_name:%s\n",(yyvsp[0].string));
      free((yyvsp[0].string));
    }
#line 2600 "yacc_sql.cpp"
    break;

  case 93: /* rel_attr: ID DOT ID  */
#line 773 "yacc_sql.y"
                {
      (yyval.rel_attr) = new RelAttrSqlNode;
      (yyval.rel_attr)->relation_name  = (yyvsp[-2].string);
      (yyval.rel_attr)->attribute_name = (yyvsp[0].string);
      free((yyvsp[-2].string));
      free((yyvsp[0].string));
    }
#line 2612 "yacc_sql.cpp"
    break;

  case 94: /* relation: ID  */
#line 783 "yacc_sql.y"
       {
      (yyval.string) = (yyvsp[0].string);
    }
#line 2620 "yacc_sql.cpp"
    break;

  case 95: /* rel_list: %empty  */
#line 788 "yacc_sql.y"
              {
    (yyval.rel_list_type) = nullptr;
  }
#line 2628 "yacc_sql.cpp"
    break;

  case 96: /* rel_list: COMMA relation alias_stmt rel_list  */
#line 791 "yacc_sql.y"
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
#line 2646 "yacc_sql.cpp"
    break;

  case 97: /* rel_list: INNER JOIN relation alias_stmt on_stmt rel_list  */
#line 804 "yacc_sql.y"
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
#line 2666 "yacc_sql.cpp"
    break;

  case 98: /* on_stmt: %empty  */
#line 822 "yacc_sql.y"
              {
    // cross product
    (yyval.condition_list) = nullptr;
  }
#line 2675 "yacc_sql.cpp"
    break;

  case 99: /* on_stmt: ON condition_list  */
#line 826 "yacc_sql.y"
                      {
    (yyval.condition_list) = (yyvsp[0].condition_list);
  }
#line 2683 "yacc_sql.cpp"
    break;

  case 100: /* where: %empty  */
#line 833 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2691 "yacc_sql.cpp"
    break;

  case 101: /* where: WHERE condition_list  */
#line 836 "yacc_sql.y"
                           {
      (yyval.condition_list) = (yyvsp[0].condition_list);  
    }
#line 2699 "yacc_sql.cpp"
    break;

  case 102: /* condition_list: %empty  */
#line 842 "yacc_sql.y"
    {
      (yyval.condition_list) = nullptr;
    }
#line 2707 "yacc_sql.cpp"
    break;

  case 103: /* condition_list: condition  */
#line 845 "yacc_sql.y"
                {
      (yyval.condition_list) = new std::vector<Expression*>;
      (yyval.condition_list)->emplace_back((yyvsp[0].condition));
      // delete $1;
    }
#line 2717 "yacc_sql.cpp"
    break;

  case 104: /* condition_list: condition AND condition_list  */
#line 850 "yacc_sql.y"
                                   {
      (yyval.condition_list) = (yyvsp[0].condition_list);
      (yyval.condition_list)->emplace_back((yyvsp[-2].condition));
      // delete $1;
    }
#line 2727 "yacc_sql.cpp"
    break;

  case 105: /* condition: expression comp_op expression  */
#line 857 "yacc_sql.y"
                                  {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2737 "yacc_sql.cpp"
    break;

  case 106: /* condition: expression comp_op null  */
#line 862 "yacc_sql.y"
                              {
      std::unique_ptr<Expression> left((yyvsp[-2].expression));
      Value v;
      v.set_null();
      std::unique_ptr<Expression> right(new ValueExpr(v));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2749 "yacc_sql.cpp"
    break;

  case 107: /* condition: null comp_op expression  */
#line 869 "yacc_sql.y"
                              {
      Value v;
      v.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v));
      std::unique_ptr<Expression> right((yyvsp[0].expression));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2761 "yacc_sql.cpp"
    break;

  case 108: /* condition: null comp_op null  */
#line 876 "yacc_sql.y"
                        {
      Value v;
      v.set_null();
      Value v2;
      v2.set_null();
      std::unique_ptr<Expression> left(new ValueExpr(v));
      std::unique_ptr<Expression> right(new ValueExpr(v2));
      (yyval.condition) = new ComparisonExpr((yyvsp[-1].comp), std::move(left), std::move(right));
    }
#line 2775 "yacc_sql.cpp"
    break;

  case 109: /* comp_op: EQ  */
#line 937 "yacc_sql.y"
         { (yyval.comp) = EQUAL_TO; }
#line 2781 "yacc_sql.cpp"
    break;

  case 110: /* comp_op: LT  */
#line 938 "yacc_sql.y"
         { (yyval.comp) = LESS_THAN; }
#line 2787 "yacc_sql.cpp"
    break;

  case 111: /* comp_op: GT  */
#line 939 "yacc_sql.y"
         { (yyval.comp) = GREAT_THAN; }
#line 2793 "yacc_sql.cpp"
    break;

  case 112: /* comp_op: LE  */
#line 940 "yacc_sql.y"
         { (yyval.comp) = LESS_EQUAL; }
#line 2799 "yacc_sql.cpp"
    break;

  case 113: /* comp_op: GE  */
#line 941 "yacc_sql.y"
         { (yyval.comp) = GREAT_EQUAL; }
#line 2805 "yacc_sql.cpp"
    break;

  case 114: /* comp_op: NE  */
#line 942 "yacc_sql.y"
         { (yyval.comp) = NOT_EQUAL; }
#line 2811 "yacc_sql.cpp"
    break;

  case 115: /* comp_op: LIKE  */
#line 943 "yacc_sql.y"
           { (yyval.comp) = LK;}
#line 2817 "yacc_sql.cpp"
    break;

  case 116: /* comp_op: NOT LIKE  */
#line 944 "yacc_sql.y"
               { (yyval.comp) = NOT_LK;}
#line 2823 "yacc_sql.cpp"
    break;

  case 117: /* comp_op: IS NOT  */
#line 945 "yacc_sql.y"
             { (yyval.comp) = IS_NOT_NULL;}
#line 2829 "yacc_sql.cpp"
    break;

  case 118: /* comp_op: IS  */
#line 946 "yacc_sql.y"
          { (yyval.comp) = IS_NULL;}
#line 2835 "yacc_sql.cpp"
    break;

  case 119: /* group_by: %empty  */
#line 952 "yacc_sql.y"
    {
      (yyval.expression_list) = nullptr;
    }
#line 2843 "yacc_sql.cpp"
    break;

  case 120: /* group_by: GROUP BY rel_attrs  */
#line 955 "yacc_sql.y"
                         {
      (yyval.expression_list) = (yyvsp[0].expression_list);
    }
#line 2851 "yacc_sql.cpp"
    break;

  case 121: /* rel_attrs: rel_attr  */
#line 961 "yacc_sql.y"
           {
    // std::vector<std::unique_ptr<Expression>> *
    auto field = new UnboundFieldExpr((yyvsp[0].rel_attr)->relation_name,(yyvsp[0].rel_attr)->attribute_name);
    (yyval.expression_list) = new std::vector<std::unique_ptr<Expression>>();
    (yyval.expression_list)->emplace_back(field);
  }
#line 2862 "yacc_sql.cpp"
    break;

  case 122: /* rel_attrs: rel_attr COMMA rel_attrs  */
#line 967 "yacc_sql.y"
                             {
    (yyval.expression_list) = (yyvsp[0].expression_list);
    auto field = new UnboundFieldExpr((yyvsp[-2].rel_attr)->relation_name,(yyvsp[-2].rel_attr)->attribute_name);
    (yyval.expression_list)->emplace_back(field);
    delete (yyvsp[-2].rel_attr);
  }
#line 2873 "yacc_sql.cpp"
    break;

  case 123: /* having_stmt: %empty  */
#line 975 "yacc_sql.y"
                {
      (yyval.condition_list) = nullptr;
    }
#line 2881 "yacc_sql.cpp"
    break;

  case 124: /* having_stmt: HAVING condition_list  */
#line 978 "yacc_sql.y"
                            {
      (yyval.condition_list) = (yyvsp[0].condition_list);
    }
#line 2889 "yacc_sql.cpp"
    break;

  case 125: /* order_by: %empty  */
#line 1016 "yacc_sql.y"
    {
      (yyval.order_by_list) = nullptr;
    }
#line 2897 "yacc_sql.cpp"
    break;

  case 126: /* order_by: ORDER BY order_list  */
#line 1019 "yacc_sql.y"
                          {
      (yyval.order_by_list) = (yyvsp[0].order_by_list);
    }
#line 2905 "yacc_sql.cpp"
    break;

  case 127: /* order_list: rel_attr  */
#line 1024 "yacc_sql.y"
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
#line 2920 "yacc_sql.cpp"
    break;

  case 128: /* order_list: rel_attr COMMA order_list  */
#line 1034 "yacc_sql.y"
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
#line 2935 "yacc_sql.cpp"
    break;

  case 129: /* order_list: rel_attr ASC  */
#line 1044 "yacc_sql.y"
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
#line 2950 "yacc_sql.cpp"
    break;

  case 130: /* order_list: rel_attr ASC COMMA order_list  */
#line 1054 "yacc_sql.y"
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
#line 2965 "yacc_sql.cpp"
    break;

  case 131: /* order_list: rel_attr DESC  */
#line 1064 "yacc_sql.y"
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
#line 2981 "yacc_sql.cpp"
    break;

  case 132: /* order_list: rel_attr DESC COMMA order_list  */
#line 1075 "yacc_sql.y"
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
#line 2996 "yacc_sql.cpp"
    break;

  case 133: /* load_data_stmt: LOAD DATA INFILE SSS INTO TABLE ID  */
#line 1102 "yacc_sql.y"
    {
      char *tmp_file_name = common::substr((yyvsp[-3].string), 1, strlen((yyvsp[-3].string)) - 2);
      
      (yyval.sql_node) = new ParsedSqlNode(SCF_LOAD_DATA);
      (yyval.sql_node)->load_data.relation_name = (yyvsp[0].string);
      (yyval.sql_node)->load_data.file_name = tmp_file_name;
      free((yyvsp[0].string));
      free(tmp_file_name);
    }
#line 3010 "yacc_sql.cpp"
    break;

  case 134: /* explain_stmt: EXPLAIN command_wrapper  */
#line 1115 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_EXPLAIN);
      (yyval.sql_node)->explain.sql_node = std::unique_ptr<ParsedSqlNode>((yyvsp[0].sql_node));
    }
#line 3019 "yacc_sql.cpp"
    break;

  case 135: /* set_variable_stmt: SET ID EQ value  */
#line 1123 "yacc_sql.y"
    {
      (yyval.sql_node) = new ParsedSqlNode(SCF_SET_VARIABLE);
      (yyval.sql_node)->set_variable.name  = (yyvsp[-2].string);
      (yyval.sql_node)->set_variable.value = *(yyvsp[0].value);
      free((yyvsp[-2].string));
      delete (yyvsp[0].value);
    }
#line 3031 "yacc_sql.cpp"
    break;


#line 3035 "yacc_sql.cpp"

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

#line 1135 "yacc_sql.y"

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
