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
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "asd.h"
    #include "lexical_value.h"    /* struct valor_t */
    #include "tables.h"          /* entries, table and stack related code */
    #include "../headers/errors.h"          /* error codes */

    #define PLACEHOLDER 0

    #define MAX_PARAMS 32 // Defina um limite razoável para o número de parâmetros
    struct param_info temp_params[MAX_PARAMS];
    int temp_param_count = 0;

    extern asd_tree_t *arvore;  /* raiz da AST */

    struct table_stack *stack = NULL; // Pilha de tabelas
    int variable_type = 0; // Tipo da variavel
    int function_type = 0; // Tipo da funcao

    extern int yylex(void);     /* corrigir erro zoado*/

    int get_line_number(void);

    void yyerror (const char *mensagem);

#line 99 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_TK_PR_AS = 3,                   /* TK_PR_AS  */
  YYSYMBOL_TK_PR_DECLARE = 4,              /* TK_PR_DECLARE  */
  YYSYMBOL_TK_PR_ELSE = 5,                 /* TK_PR_ELSE  */
  YYSYMBOL_TK_PR_FLOAT = 6,                /* TK_PR_FLOAT  */
  YYSYMBOL_TK_PR_IF = 7,                   /* TK_PR_IF  */
  YYSYMBOL_TK_PR_INT = 8,                  /* TK_PR_INT  */
  YYSYMBOL_TK_PR_IS = 9,                   /* TK_PR_IS  */
  YYSYMBOL_TK_PR_RETURN = 10,              /* TK_PR_RETURN  */
  YYSYMBOL_TK_PR_RETURNS = 11,             /* TK_PR_RETURNS  */
  YYSYMBOL_TK_PR_WHILE = 12,               /* TK_PR_WHILE  */
  YYSYMBOL_TK_PR_WITH = 13,                /* TK_PR_WITH  */
  YYSYMBOL_TK_OC_LE = 14,                  /* TK_OC_LE  */
  YYSYMBOL_TK_OC_GE = 15,                  /* TK_OC_GE  */
  YYSYMBOL_TK_OC_EQ = 16,                  /* TK_OC_EQ  */
  YYSYMBOL_TK_OC_NE = 17,                  /* TK_OC_NE  */
  YYSYMBOL_TK_ID = 18,                     /* TK_ID  */
  YYSYMBOL_TK_LI_INT = 19,                 /* TK_LI_INT  */
  YYSYMBOL_TK_LI_FLOAT = 20,               /* TK_LI_FLOAT  */
  YYSYMBOL_TK_ER = 21,                     /* TK_ER  */
  YYSYMBOL_22_ = 22,                       /* ';'  */
  YYSYMBOL_23_ = 23,                       /* ','  */
  YYSYMBOL_24_ = 24,                       /* '['  */
  YYSYMBOL_25_ = 25,                       /* ']'  */
  YYSYMBOL_26_ = 26,                       /* '('  */
  YYSYMBOL_27_ = 27,                       /* ')'  */
  YYSYMBOL_28_ = 28,                       /* '|'  */
  YYSYMBOL_29_ = 29,                       /* '&'  */
  YYSYMBOL_30_ = 30,                       /* '<'  */
  YYSYMBOL_31_ = 31,                       /* '>'  */
  YYSYMBOL_32_ = 32,                       /* '+'  */
  YYSYMBOL_33_ = 33,                       /* '-'  */
  YYSYMBOL_34_ = 34,                       /* '*'  */
  YYSYMBOL_35_ = 35,                       /* '/'  */
  YYSYMBOL_36_ = 36,                       /* '%'  */
  YYSYMBOL_37_ = 37,                       /* '!'  */
  YYSYMBOL_YYACCEPT = 38,                  /* $accept  */
  YYSYMBOL_programa = 39,                  /* programa  */
  YYSYMBOL_lista = 40,                     /* lista  */
  YYSYMBOL_elemento = 41,                  /* elemento  */
  YYSYMBOL_def_func = 42,                  /* def_func  */
  YYSYMBOL_decl_var_global = 43,           /* decl_var_global  */
  YYSYMBOL_header = 44,                    /* header  */
  YYSYMBOL_header_head = 45,               /* header_head  */
  YYSYMBOL_tipo = 46,                      /* tipo  */
  YYSYMBOL_tipo_funcao = 47,               /* tipo_funcao  */
  YYSYMBOL_pre_param_list = 48,            /* pre_param_list  */
  YYSYMBOL_param_list = 49,                /* param_list  */
  YYSYMBOL_parameter = 50,                 /* parameter  */
  YYSYMBOL_body = 51,                      /* body  */
  YYSYMBOL_command_block = 52,             /* command_block  */
  YYSYMBOL_simple_command_list = 53,       /* simple_command_list  */
  YYSYMBOL_simple_command = 54,            /* simple_command  */
  YYSYMBOL_init = 55,                      /* init  */
  YYSYMBOL_decl_var = 56,                  /* decl_var  */
  YYSYMBOL_attribution = 57,               /* attribution  */
  YYSYMBOL_call_func = 58,                 /* call_func  */
  YYSYMBOL_arg_list = 59,                  /* arg_list  */
  YYSYMBOL_return_command = 60,            /* return_command  */
  YYSYMBOL_flow_ctrl = 61,                 /* flow_ctrl  */
  YYSYMBOL_conditional = 62,               /* conditional  */
  YYSYMBOL_while = 63,                     /* while  */
  YYSYMBOL_expressao = 64,                 /* expressao  */
  YYSYMBOL_n7 = 65,                        /* n7  */
  YYSYMBOL_n6 = 66,                        /* n6  */
  YYSYMBOL_n5 = 67,                        /* n5  */
  YYSYMBOL_n4 = 68,                        /* n4  */
  YYSYMBOL_n3 = 69,                        /* n3  */
  YYSYMBOL_n2 = 70,                        /* n2  */
  YYSYMBOL_n1 = 71,                        /* n1  */
  YYSYMBOL_n0 = 72,                        /* n0  */
  YYSYMBOL_push_table = 73,                /* push_table  */
  YYSYMBOL_pop_table = 74                  /* pop_table  */
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
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   121

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  38
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   276


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
       2,     2,     2,    37,     2,     2,     2,    36,    29,     2,
      26,    27,    34,    32,    23,    33,     2,    35,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    22,
      30,     2,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    24,     2,    25,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    28,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    51,    51,    52,    56,    57,    70,    71,    75,    85,
     118,   140,   153,   183,   184,   188,   189,   193,   200,   201,
     213,   243,   247,   251,   252,   265,   266,   267,   268,   269,
     270,   274,   280,   286,   290,   327,   361,   466,   510,   511,
     520,   537,   538,   542,   552,   574,   586,   590,   601,   605,
     616,   620,   631,   640,   644,   655,   664,   673,   682,   686,
     697,   706,   710,   720,   729,   738,   742,   743,   744,   745,
     749,   765,   772,   779,   780,   783,   791
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
  "\"end of file\"", "error", "\"invalid token\"", "TK_PR_AS",
  "TK_PR_DECLARE", "TK_PR_ELSE", "TK_PR_FLOAT", "TK_PR_IF", "TK_PR_INT",
  "TK_PR_IS", "TK_PR_RETURN", "TK_PR_RETURNS", "TK_PR_WHILE", "TK_PR_WITH",
  "TK_OC_LE", "TK_OC_GE", "TK_OC_EQ", "TK_OC_NE", "TK_ID", "TK_LI_INT",
  "TK_LI_FLOAT", "TK_ER", "';'", "','", "'['", "']'", "'('", "')'", "'|'",
  "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "$accept",
  "programa", "lista", "elemento", "def_func", "decl_var_global", "header",
  "header_head", "tipo", "tipo_funcao", "pre_param_list", "param_list",
  "parameter", "body", "command_block", "simple_command_list",
  "simple_command", "init", "decl_var", "attribution", "call_func",
  "arg_list", "return_command", "flow_ctrl", "conditional", "while",
  "expressao", "n7", "n6", "n5", "n4", "n3", "n2", "n1", "n0",
  "push_table", "pop_table", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-60)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      10,    72,     8,   -60,    55,    63,   -60,    52,   -60,   -60,
      67,   -60,    74,    12,    56,     8,    57,    66,    43,   -60,
     -60,   -60,   -60,   -60,   -60,   -60,   -60,    62,   -60,   -60,
     -60,   -60,     1,   -60,    79,   -60,    60,    68,    58,    -4,
      59,    -5,   -60,   -60,     1,   -60,   -60,   -60,   -60,   -60,
     -60,   -60,    43,    62,    84,    -4,    64,   -60,   -60,    -4,
      -4,    -4,    -4,   -60,    85,    61,    65,    44,    17,    32,
       0,   -60,   -60,    -4,    -4,    26,    70,   -60,   -60,   -60,
      43,    69,    71,   -60,   -60,   -60,    43,    -4,    -4,    -4,
      -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,    -4,
      73,   -60,   -60,    75,    76,   -60,    80,    57,   -60,   -60,
      65,    44,    17,    17,    32,    32,    32,    32,     0,     0,
     -60,   -60,   -60,    57,   -60,    -4,    47,   -60,    87,   -60,
     -60,   -60,   -60,    57,   -60
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      75,     0,     0,     1,     0,     0,    76,     4,     6,     7,
       0,    75,     0,     0,     0,     0,     0,    11,     0,    15,
      16,    12,     3,     5,    75,    76,    21,     0,    10,    13,
      14,     9,    23,     8,     0,    17,    18,     0,     0,     0,
       0,     0,    25,    76,    23,    26,    27,    28,    29,    30,
      41,    42,     0,     0,     0,     0,    70,    71,    72,     0,
       0,     0,     0,    73,     0,    46,    48,    50,    53,    58,
      61,    65,    69,     0,     0,     0,     0,    24,    20,    19,
       0,     0,     0,    66,    67,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    37,     0,    38,    22,    33,     0,    74,    40,
      47,    49,    51,    52,    56,    57,    54,    55,    59,    60,
      62,    63,    64,     0,    36,     0,     0,    34,    43,    45,
      39,    31,    32,     0,    44
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -60,   -60,    82,   -60,   -60,   -60,   -60,   -60,   -43,   -60,
     -60,    48,   -60,   -60,   -16,    77,   -60,   -60,   -60,   -60,
      18,   -22,   -60,   -60,   -60,   -60,   -32,   -60,    19,    16,
     -21,   -37,   -25,   -59,   -60,     6,   -19
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     1,     6,     7,     8,     9,    10,    11,    31,    21,
      28,    35,    36,    25,    42,    43,    44,   127,    45,    46,
      63,   103,    48,    49,    50,    51,   104,    65,    66,    67,
      68,    69,    70,    71,    72,     2,    14
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      26,    83,    84,    85,    74,    37,    33,    64,    38,    78,
      -2,    39,     4,    40,    56,    57,    58,    17,    19,    41,
      20,    75,    59,    81,    76,    24,     5,    82,    60,    61,
      32,    91,    92,    62,    97,    98,    99,   106,   120,   121,
     122,   100,   101,   109,    56,    57,    58,    93,    94,    29,
      47,    30,    59,   102,   114,   115,   116,   117,    60,    61,
      89,    90,    47,    62,    95,    96,   131,   132,   112,   113,
     118,   119,     3,    12,    13,    15,    16,    18,    22,    27,
      34,    24,    52,    53,    55,    73,    54,    80,    86,    87,
      75,   128,   133,   126,    88,   105,   107,    23,   108,   125,
     123,    79,   124,   130,   111,     0,   110,   129,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   134,     0,     0,
       0,    77
};

static const yytype_int16 yycheck[] =
{
      16,    60,    61,    62,     9,     4,    25,    39,     7,    52,
       0,    10,     4,    12,    18,    19,    20,    11,     6,    18,
       8,    26,    26,    55,    43,    24,    18,    59,    32,    33,
      24,    14,    15,    37,    34,    35,    36,    80,    97,    98,
      99,    73,    74,    86,    18,    19,    20,    30,    31,     6,
      32,     8,    26,    27,    91,    92,    93,    94,    32,    33,
      16,    17,    44,    37,    32,    33,    19,    20,    89,    90,
      95,    96,     0,    18,    11,    23,     9,     3,    22,    13,
      18,    24,     3,    23,    26,    26,    18,     3,     3,    28,
      26,   107,     5,    13,    29,    25,    27,    15,    27,    23,
      27,    53,    27,   125,    88,    -1,    87,   123,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   133,    -1,    -1,
      -1,    44
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    39,    73,     0,     4,    18,    40,    41,    42,    43,
      44,    45,    18,    11,    74,    23,     9,    73,     3,     6,
       8,    47,    22,    40,    24,    51,    52,    13,    48,     6,
       8,    46,    73,    74,    18,    49,    50,     4,     7,    10,
      12,    18,    52,    53,    54,    56,    57,    58,    60,    61,
      62,    63,     3,    23,    18,    26,    18,    19,    20,    26,
      32,    33,    37,    58,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    26,     9,    26,    74,    53,    46,    49,
       3,    64,    64,    71,    71,    71,     3,    28,    29,    16,
      17,    14,    15,    30,    31,    32,    33,    34,    35,    36,
      64,    64,    27,    59,    64,    25,    46,    27,    27,    46,
      66,    67,    68,    68,    69,    69,    69,    69,    70,    70,
      71,    71,    71,    27,    27,    23,    13,    55,    52,    52,
      59,    19,    20,     5,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    38,    39,    39,    40,    40,    41,    41,    42,    43,
      44,    44,    45,    46,    46,    47,    47,    48,    49,    49,
      50,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      54,    55,    55,    55,    56,    57,    58,    58,    59,    59,
      60,    61,    61,    62,    62,    63,    64,    65,    65,    66,
      66,    67,    67,    67,    68,    68,    68,    68,    68,    69,
      69,    69,    70,    70,    70,    70,    71,    71,    71,    71,
      72,    72,    72,    72,    72,    73,    74
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     4,     1,     3,     1,     1,     4,     4,
       3,     2,     3,     1,     1,     1,     1,     2,     1,     3,
       3,     1,     5,     0,     2,     1,     1,     1,     1,     1,
       1,     2,     2,     0,     5,     3,     4,     3,     1,     3,
       4,     1,     1,     5,     7,     5,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     2,     2,     2,     1,
       1,     1,     1,     1,     3,     0,     0
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
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
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

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

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

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
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
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
      yychar = yylex ();
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


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: %empty  */
#line 51 "src/parser.y"
                                                                { (yyval.no_ast) = NULL; arvore = (yyval.no_ast); }
#line 1519 "parser.tab.c"
    break;

  case 3: /* programa: push_table lista pop_table ';'  */
#line 52 "src/parser.y"
                                                                  { (yyval.no_ast) = (yyvsp[-2].no_ast); arvore = (yyval.no_ast); }
#line 1525 "parser.tab.c"
    break;

  case 4: /* lista: elemento  */
#line 56 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1531 "parser.tab.c"
    break;

  case 5: /* lista: elemento ',' lista  */
#line 57 "src/parser.y"
                                            {
                                                if ((yyvsp[-2].no_ast) == NULL){
                                                    (yyval.no_ast) = (yyvsp[0].no_ast);
                                                } else if((yyvsp[0].no_ast) == NULL){
                                                    (yyval.no_ast) = (yyvsp[-2].no_ast);
                                                } else{
                                                    (yyval.no_ast) = (yyvsp[-2].no_ast);
                                                    asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                                }
                                            }
#line 1546 "parser.tab.c"
    break;

  case 6: /* elemento: def_func  */
#line 70 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1552 "parser.tab.c"
    break;

  case 7: /* elemento: decl_var_global  */
#line 71 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1558 "parser.tab.c"
    break;

  case 8: /* def_func: header TK_PR_IS body pop_table  */
#line 75 "src/parser.y"
                                       { // No com a label do header. Body vira filho
                                                    (yyval.no_ast) = asd_new((yyvsp[-3].no_ast)->label, variable_type);
                                                    if ((yyvsp[-1].no_ast) != NULL){
                                                        asd_add_child((yyval.no_ast), (yyvsp[-1].no_ast));
                                                    }
                                                    asd_free((yyvsp[-3].no_ast));
                                                }
#line 1570 "parser.tab.c"
    break;

  case 9: /* decl_var_global: TK_PR_DECLARE TK_ID TK_PR_AS tipo  */
#line 85 "src/parser.y"
                                            {   
                                                // Verificar se a variavel ja foi declarada
                                                // Se sim, erro de variavel ja declarada
                                                // Se nao, criar variavel e adicionar na tabela
                                                char *name = (yyvsp[-2].lex_val)->token_val;
                                                if(search_entry(stack->top, name) != NULL){
                                                    semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                } else{
                                                    valor_t v;
                                                    v.line_number = get_line_number();
                                                    v.token_type = TK_ID;
                                                    v.token_val = strdup(name);
                                                    struct entry e = create_entry(
                                                        get_line_number(),
                                                        NATURE_VAR,
                                                        variable_type,
                                                        v,
                                                        0,
                                                        NULL
                                                    );
                                                    add_entry(stack->top, &e);
                                                    free(v.token_val);
                                                }
                                                // Pra variavel global cabeca fica nula e libera TK_ID
                                                (yyval.no_ast) = NULL;
                                                if ((yyvsp[-2].lex_val)){
                                                    free((yyvsp[-2].lex_val)->token_val);
                                                    free((yyvsp[-2].lex_val));
                                                }
                                            }
#line 1605 "parser.tab.c"
    break;

  case 10: /* header: header_head push_table pre_param_list  */
#line 118 "src/parser.y"
                                            {    // Nova pre_param_list para facilitar
                                                char *fname = (yyvsp[-2].no_ast)->label; // O label do no AST de header_head é o nome da função
                                                struct entry *func_entry = search_entry_in_stack(stack, fname);
                                                if (func_entry != NULL && func_entry->nature == NATURE_FUNC) {
                                                    func_entry->num_params = temp_param_count;
                                                    if (temp_param_count > 0) {
                                                        // Aloca memoria para os parametros na entrada da tabela de simbolos
                                                        func_entry->params = malloc(temp_param_count * sizeof(struct param_info));
                                                        if (func_entry->params == NULL) {
                                                            fprintf(stderr, "Erro ao alocar memoria para params da funcao na tabela de simbolos\n");
                                                            exit(1);
                                                        }
                                                        // Copia os parametros da lista temporaria para a entrada da tabela
                                                        memcpy(func_entry->params, temp_params, temp_param_count * sizeof(struct param_info));
                                                    } else {
                                                        func_entry->params = NULL; // Garante que é NULL se não houver parâmetros
                                                    }
                                                }
                                                (yyval.no_ast) = (yyvsp[-2].no_ast);
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast)); // Adiciona a lista de parâmetros à AST da função
                                                temp_param_count = 0; // **RESETA O CONTADOR DE PARAMETROS APÓS USAR**
                                            }
#line 1632 "parser.tab.c"
    break;

  case 11: /* header: header_head push_table  */
#line 140 "src/parser.y"
                                            {
                                                char *fname = (yyvsp[-1].no_ast)->label;
                                                struct entry *func_entry = search_entry_in_stack(stack, fname);
                                                if (func_entry != NULL && func_entry->nature == NATURE_FUNC) {
                                                    func_entry->num_params = 0;
                                                    func_entry->params = NULL; // Não há parâmetros
                                                }
                                                (yyval.no_ast) = (yyvsp[-1].no_ast);
                                                temp_param_count = 0; // **RESETA O CONTADOR DE PARAMETROS APÓS USAR**
                                            }
#line 1647 "parser.tab.c"
    break;

  case 12: /* header_head: TK_ID TK_PR_RETURNS tipo_funcao  */
#line 153 "src/parser.y"
                                                   {
                                                char *fname = (yyvsp[-2].lex_val)->token_val;
                                                if (search_entry(stack->top, fname) != NULL){
                                                    semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                } else{
                                                    valor_t v;
                                                    v.line_number = get_line_number();
                                                    v.token_type = TK_ID;
                                                    v.token_val = strdup(fname);
                                                    struct entry e = create_entry(
                                                        get_line_number(),
                                                        NATURE_FUNC,
                                                        function_type,
                                                        v,
                                                        0,
                                                        NULL
                                                    );
                                                    add_entry(stack->top, &e);
                                                    free(v.token_val);
                                                }
                                                (yyval.no_ast) = asd_new((yyvsp[-2].lex_val)->token_val, variable_type);
                                                if((yyvsp[-2].lex_val)){
                                                    free((yyvsp[-2].lex_val)->token_val);
                                                    free((yyvsp[-2].lex_val));
                                                }
                                                temp_param_count = 0; // **RESETA O CONTADOR DE PARAMETROS AQUI!**
                                            }
#line 1679 "parser.tab.c"
    break;

  case 13: /* tipo: TK_PR_FLOAT  */
#line 183 "src/parser.y"
                                            { (yyval.no_ast) = NULL; variable_type = TYPE_FLOAT; }
#line 1685 "parser.tab.c"
    break;

  case 14: /* tipo: TK_PR_INT  */
#line 184 "src/parser.y"
                                            { (yyval.no_ast) = NULL; variable_type = TYPE_INT; }
#line 1691 "parser.tab.c"
    break;

  case 15: /* tipo_funcao: TK_PR_FLOAT  */
#line 188 "src/parser.y"
                                            { (yyval.no_ast) = NULL; function_type = TYPE_FLOAT; }
#line 1697 "parser.tab.c"
    break;

  case 16: /* tipo_funcao: TK_PR_INT  */
#line 189 "src/parser.y"
                                            { (yyval.no_ast) = NULL; function_type = TYPE_INT; }
#line 1703 "parser.tab.c"
    break;

  case 17: /* pre_param_list: TK_PR_WITH param_list  */
#line 193 "src/parser.y"
                                            { 
                                                if((yyvsp[0].no_ast) != NULL){
                                                    (yyval.no_ast) = (yyvsp[0].no_ast);
                                                }
                                            }
#line 1713 "parser.tab.c"
    break;

  case 18: /* param_list: parameter  */
#line 200 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1719 "parser.tab.c"
    break;

  case 19: /* param_list: parameter ',' param_list  */
#line 201 "src/parser.y"
                                            { 
                                                if((yyvsp[0].no_ast)==NULL)
                                                {
                                                    (yyval.no_ast)=(yyvsp[-2].no_ast);
                                                }else{
                                                    (yyval.no_ast) = (yyvsp[-2].no_ast);
                                                    asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                                }
                                            }
#line 1733 "parser.tab.c"
    break;

  case 20: /* parameter: TK_ID TK_PR_AS tipo  */
#line 213 "src/parser.y"
                                            {
                                                char *pname = (yyvsp[-2].lex_val)->token_val;
                                                if(search_entry(stack->top, pname) != NULL){
                                                    semantic_error(ERR_DECLARED, "Dois parametros com o mesmo nome.", get_line_number());
                                                }
                                                valor_t v;
                                                v.line_number = get_line_number();
                                                v.token_type = TK_ID;
                                                v.token_val = strdup(pname);
                                                struct entry e = create_entry(
                                                    get_line_number(),
                                                    NATURE_VAR,
                                                    variable_type,
                                                    v,
                                                    0,
                                                    NULL
                                                );
                                                add_entry(stack->top, &e);
                                                free(v.token_val);


                                                (yyval.no_ast) = asd_new((yyvsp[-2].lex_val)->token_val, variable_type);
                                                if((yyvsp[-2].lex_val)){
                                                    free((yyvsp[-2].lex_val)->token_val);
                                                    free((yyvsp[-2].lex_val));
                                                }
                                            }
#line 1765 "parser.tab.c"
    break;

  case 21: /* body: command_block  */
#line 243 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1771 "parser.tab.c"
    break;

  case 22: /* command_block: '[' push_table simple_command_list pop_table ']'  */
#line 247 "src/parser.y"
                                                                 { (yyval.no_ast) = (yyvsp[-2].no_ast); }
#line 1777 "parser.tab.c"
    break;

  case 23: /* simple_command_list: %empty  */
#line 251 "src/parser.y"
                                             { (yyval.no_ast) = NULL; }
#line 1783 "parser.tab.c"
    break;

  case 24: /* simple_command_list: simple_command simple_command_list  */
#line 252 "src/parser.y"
                                            { // Logica para cabeca e simple_command_list virar filho
                                                if((yyvsp[-1].no_ast) == NULL){
                                                    (yyval.no_ast) = (yyvsp[0].no_ast);
                                                }else if((yyvsp[0].no_ast) == NULL){
                                                    (yyval.no_ast) = (yyvsp[-1].no_ast);
                                                }else{
                                                    (yyval.no_ast) = (yyvsp[-1].no_ast);
                                                    asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                                }
                                            }
#line 1798 "parser.tab.c"
    break;

  case 25: /* simple_command: command_block  */
#line 265 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1804 "parser.tab.c"
    break;

  case 26: /* simple_command: decl_var  */
#line 266 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1810 "parser.tab.c"
    break;

  case 27: /* simple_command: attribution  */
#line 267 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1816 "parser.tab.c"
    break;

  case 28: /* simple_command: call_func  */
#line 268 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1822 "parser.tab.c"
    break;

  case 29: /* simple_command: return_command  */
#line 269 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1828 "parser.tab.c"
    break;

  case 30: /* simple_command: flow_ctrl  */
#line 270 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 1834 "parser.tab.c"
    break;

  case 31: /* init: TK_PR_WITH TK_LI_INT  */
#line 274 "src/parser.y"
                                        {  (yyval.no_ast) = asd_new((yyvsp[0].lex_val)->token_val, TYPE_INT);
                                            if ((yyvsp[0].lex_val)){
                                                free((yyvsp[0].lex_val)->token_val);
                                                free((yyvsp[0].lex_val));
                                            }
                                        }
#line 1845 "parser.tab.c"
    break;

  case 32: /* init: TK_PR_WITH TK_LI_FLOAT  */
#line 280 "src/parser.y"
                                        {  (yyval.no_ast) = asd_new((yyvsp[0].lex_val)->token_val, TYPE_FLOAT);
                                            if ((yyvsp[0].lex_val)){
                                                free((yyvsp[0].lex_val)->token_val);
                                                free((yyvsp[0].lex_val));
                                            }
                                        }
#line 1856 "parser.tab.c"
    break;

  case 33: /* init: %empty  */
#line 286 "src/parser.y"
                                       { (yyval.no_ast) = NULL;}
#line 1862 "parser.tab.c"
    break;

  case 34: /* decl_var: TK_PR_DECLARE TK_ID TK_PR_AS tipo init  */
#line 290 "src/parser.y"
                                             {
                                                char *varname = (yyvsp[-3].lex_val)->token_val;
                                                // Verificar se a variavel ja foi declarada no escopo atual
                                                if(search_entry(stack->top, varname) != NULL){
                                                    semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                }
                                                if ((yyvsp[0].no_ast) != NULL && variable_type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo de variavel diferente do tipo da inicializacao", get_line_number());
                                                }
                                                valor_t v;
                                                v.line_number = get_line_number();
                                                v.token_type = TK_ID;
                                                v.token_val = strdup(varname);
                                                struct entry e = create_entry(
                                                    get_line_number(),
                                                    NATURE_VAR,
                                                    variable_type,
                                                    v,
                                                    0,
                                                    NULL
                                                );
                                                add_entry(stack->top, &e);
                                                free(v.token_val);
                                                

                                                if((yyvsp[0].no_ast) != NULL)  //se tiver inicializacao cria no e da os filhos com o valor do ID e da init
                                                {
                                                    (yyval.no_ast) = asd_new("with", variable_type);
                                                    asd_add_child((yyval.no_ast), asd_new((yyvsp[-3].lex_val)->token_val, variable_type));
                                                    asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                                }
                                                else{ (yyval.no_ast) = NULL;}
                                                if((yyvsp[-3].lex_val)){ free((yyvsp[-3].lex_val)->token_val); free((yyvsp[-3].lex_val));}
                                            }
#line 1901 "parser.tab.c"
    break;

  case 35: /* attribution: TK_ID TK_PR_IS expressao  */
#line 327 "src/parser.y"
                                            {   
                                                // Verificar se a variavel foi declarada em algum escopo
                                                char *varname = (yyvsp[-2].lex_val)->token_val;
                                                struct entry *e = search_entry_in_stack(stack, varname);
                                                // Por algum motivo get_line_number() nao funciona aqui
                                                // Ele devolve o numero da linha do erro + 1
                                                // ???? Sor, se o senhor ver isso e quiser deixar nos comentarios do trabalho
                                                // por que na atribuição ele da o numero da linha do erro + 1
                                                // mas nas outras produções ele da o numero certo a gente ficaria grato
                                                // É como se o yylineno identificasse o /n antes de chegar nesse bloco de código
                                                // sendo que nas outras produções ele identifica o /n depois, pelo que parece ao menos
                                                // O certo deveria ser pegar o $x->line_number quando possível em vez de get_line_number()?
                                                if(e == NULL){
                                                    semantic_error(ERR_UNDECLARED, "Identificador nao declarado", (yyvsp[-2].lex_val)->line_number);
                                                }
                                                if(e->nature == NATURE_FUNC){
                                                    semantic_error(ERR_FUNCTION, "Tentativa de fazer atribuicao em funcao", (yyvsp[-2].lex_val)->line_number);
                                                }
                                                if (e->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo de variavel diferente do tipo da atribuicao", (yyvsp[-2].lex_val)->line_number);
                                                }

                                                // Atribuitcao no is com filhos do valor do TK_ID e a expressao
                                                (yyval.no_ast) = asd_new("is", e->type);
                                                asd_add_child((yyval.no_ast), asd_new((yyvsp[-2].lex_val)->token_val, variable_type));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                                if((yyvsp[-2].lex_val)){
                                                    free((yyvsp[-2].lex_val)->token_val);
                                                    free((yyvsp[-2].lex_val));
                                                }
                                            }
#line 1937 "parser.tab.c"
    break;

  case 36: /* call_func: TK_ID '(' arg_list ')'  */
#line 361 "src/parser.y"
                                        {
                                        char *fname = (yyvsp[-3].lex_val)->token_val;
                                        struct entry *func_entry = search_entry_in_stack(stack, fname);

                                        // Placeholder for the AST node for the call, to be created even on errors
                                        asd_tree_t *call_node = NULL;

                                        if (func_entry == NULL) {
                                            semantic_error(ERR_UNDECLARED, "Identificador nao declarado", (yyvsp[-3].lex_val)->line_number);
                                        } else if (func_entry->nature == NATURE_VAR) {
                                            semantic_error(ERR_VARIABLE, "Erro: variavel sendo usada como funcao", (yyvsp[-3].lex_val)->line_number);
                                        } else { // It's a declared function, now check arguments
                                            int declared_param_count = func_entry->num_params;
                                            asd_tree_t *first_arg_node = (yyvsp[-1].no_ast); // This is the AST node representing the first argument (or the list head)

                                            int actual_arg_count = 0;

                                            if (first_arg_node != NULL) { // Check if there's at least one argument parsed
                                                actual_arg_count = 1; // Count the first argument
                                                // Perform type check for the first argument
                                                if (actual_arg_count <= declared_param_count && func_entry->params != NULL) {
                                                    if (first_arg_node->type != func_entry->params[actual_arg_count - 1].type) {
                                                        semantic_error(ERR_WRONG_TYPE_ARGS, "Tipo de argumento incompativel na chamada da funcao", (yyvsp[-3].lex_val)->line_number);
                                                    }
                                                }

                                                // Iterate through the children (subsequent arguments)
                                                // **CRITICAL: Add a null check for first_arg_node before accessing number_of_children**
                                                // Although you already have `if (first_arg_node != NULL)`, this internal loop should be careful.
                                                // The error trace points to line 276, which is `asd_tree_t *first_arg_node = $3;`.
                                                // This suggests $3 itself might be NULL. The check `if (first_arg_node != NULL)` happens *after* assignment.
                                                // The problem might be in the first_arg_node->children[i] or first_arg_node->number_of_children if first_arg_node is indeed NULL.
                                                // This `for` loop will only execute if `first_arg_node` is not null, so the issue is probably
                                                // when `first_arg_node` is indeed null, and then `actual_arg_count` remains 0,
                                                // leading to `ERR_MISSING_ARGS` if `declared_param_count > 0`.
                                                // Let's assume the SEGV points to the line where `first_arg_node` is *used* when it's null,
                                                // not necessarily its assignment.
                                                
                                                // The most likely culprit is the `for` loop if `first_arg_node` is NULL.
                                                // The previous check `if (first_arg_node != NULL)` should handle it.
                                                // Let's re-evaluate the flow for the `arg_list` rule.
                                                // If `arg_list` can return NULL when it's expected to be a valid AST node.

                                                // Assuming $3 is properly handled by the grammar, the issue may be if `number_of_children` is garbage
                                                // if `asd_new` failed or a node was corrupted. But AddressSanitizer points to `0x18`, which
                                                // strongly suggests `NULL + offset`.

                                                // Re-confirming: the only way `first_arg_node->number_of_children` leads to 0x18
                                                // is if `first_arg_node` is NULL. The `if (first_arg_node != NULL)` check should prevent this.
                                                // IS IT POSSIBLE that `first_arg_node` itself is not fully constructed or partially corrupted?
                                                // Or is the error message `src/parser.y:276` misleading and it's actually in the loop *after* the if statement?

                                                // Let's make the loop even safer:
                                                if (first_arg_node->number_of_children > 0) { // Check before iterating through children
                                                    for (int i = 0; i < first_arg_node->number_of_children; i++) {
                                                        asd_tree_t *current_arg_node = first_arg_node->children[i];
                                                        if (current_arg_node == NULL) { // Extra check for null children
                                                            semantic_error(ERR_WRONG_TYPE_ARGS, "Argumento nulo inesperado na chamada da funcao", (yyvsp[-3].lex_val)->line_number);
                                                            break;
                                                        }
                                                        actual_arg_count++;

                                                        if (actual_arg_count > declared_param_count) {
                                                            semantic_error(ERR_EXCESS_ARGS, "Numero excessivo de argumentos na chamada da funcao", (yyvsp[-3].lex_val)->line_number);
                                                            break;
                                                        }
                                                        if (func_entry->params != NULL && (actual_arg_count - 1) < declared_param_count) {
                                                            if (current_arg_node->type != func_entry->params[actual_arg_count - 1].type) {
                                                                semantic_error(ERR_WRONG_TYPE_ARGS, "Tipo de argumento incompativel na chamada da funcao", (yyvsp[-3].lex_val)->line_number);
                                                            }
                                                        }
                                                    }
                                                }
                                            }

                                            // Check for missing arguments
                                            if (actual_arg_count < declared_param_count) {
                                                semantic_error(ERR_MISSING_ARGS, "Numero insuficiente de argumentos na chamada da funcao", (yyvsp[-3].lex_val)->line_number);
                                            }

                                            // Create the AST node for the function call
                                            char *nome_da_funcao = malloc(strlen((yyvsp[-3].lex_val)->token_val) + 6);
                                            if (nome_da_funcao != NULL) { // Safety check for malloc
                                                sprintf(nome_da_funcao, "call %s", (yyvsp[-3].lex_val)->token_val);
                                                call_node = asd_new(nome_da_funcao, func_entry->type);
                                                free(nome_da_funcao);
                                            } else {
                                                fprintf(stderr, "Erro de alocacao de memoria para nome da funcao.\n");
                                                call_node = asd_new("call_error", variable_type); // Fallback
                                            }
                                        }

                                        // Attach arguments to the function call node, if it exists
                                        if (call_node != NULL && (yyvsp[-1].no_ast) != NULL) {
                                            asd_add_child(call_node, (yyvsp[-1].no_ast));
                                        }

                                        (yyval.no_ast) = call_node; // Assign the created node to $$
                                        
                                        // Free the lexical value for TK_ID
                                        if ((yyvsp[-3].lex_val)) {
                                            free((yyvsp[-3].lex_val)->token_val);
                                            free((yyvsp[-3].lex_val));
                                        }
                                    }
#line 2047 "parser.tab.c"
    break;

  case 37: /* call_func: TK_ID '(' ')'  */
#line 466 "src/parser.y"
                                        {
                                        // ... (this rule also needs to be reviewed for similar null pointer risks)
                                        // The proposed code for this rule seems less prone to this specific SEGV
                                        // because it doesn't iterate over children.
                                        char *fname = (yyvsp[-2].lex_val)->token_val;
                                        struct entry *func_entry = search_entry_in_stack(stack, fname);
                                        asd_tree_t *call_node_empty = NULL; // New node for this rule

                                        if (func_entry == NULL) {
                                            semantic_error(ERR_UNDECLARED, "Identificador nao declarado", (yyvsp[-2].lex_val)->line_number);
                                            call_node_empty = asd_new("call", variable_type);
                                        } else if (func_entry->nature == NATURE_VAR) {
                                            semantic_error(ERR_VARIABLE, "Erro: variavel sendo usada como funcao", (yyvsp[-2].lex_val)->line_number);
                                            call_node_empty = asd_new("call", variable_type);
                                        } else {
                                            int declared_param_count = func_entry->num_params;
                                            if (declared_param_count > 0) {
                                                semantic_error(ERR_MISSING_ARGS, "Numero insuficiente de argumentos na chamada da funcao (esperado mais de 0, recebido 0)", (yyvsp[-2].lex_val)->line_number);
                                            }

                                            char *nome_da_funcao = malloc(strlen((yyvsp[-2].lex_val)->token_val) + 6);
                                            if (nome_da_funcao != NULL) { // Safety check for malloc
                                                sprintf(nome_da_funcao, "call %s", (yyvsp[-2].lex_val)->token_val);
                                                call_node_empty = asd_new(nome_da_funcao, func_entry->type);
                                                free(nome_da_funcao);
                                            } else {
                                                fprintf(stderr, "Erro de alocacao de memoria para nome da funcao (vazio).\n");
                                                call_node_empty = asd_new("call_error", variable_type); // Fallback
                                            }
                                        }
                                        (yyval.no_ast) = call_node_empty; // Assign the created node
                                        if ((yyvsp[-2].lex_val)) {
                                            free((yyvsp[-2].lex_val)->token_val);
                                            free((yyvsp[-2].lex_val));
                                        }
                                    }
#line 2088 "parser.tab.c"
    break;

  case 38: /* arg_list: expressao  */
#line 510 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2094 "parser.tab.c"
    break;

  case 39: /* arg_list: expressao ',' arg_list  */
#line 511 "src/parser.y"
                                            {
                                                 // Adiciona a nova expressão como filho da arg_list existente
                                                asd_tree_t *current_list_head = (yyvsp[-2].no_ast);
                                                asd_add_child(current_list_head, (yyvsp[0].no_ast)); // $3 é a nova expressao
                                                (yyval.no_ast) = current_list_head;
                                            }
#line 2105 "parser.tab.c"
    break;

  case 40: /* return_command: TK_PR_RETURN expressao TK_PR_AS tipo  */
#line 520 "src/parser.y"
                                            {   
                                                // Verificar se a funcao e o retorno tem o mesmo tipo
                                                if (function_type != variable_type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo de retorno diferente do tipo da funcao", get_line_number());
                                                }
                                                // Verificar se a funcao e a expressao tem o mesmo tipo
                                                if (function_type != (yyvsp[-2].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Tipo expressao retornada diferente do tipo da funcao", get_line_number());
                                                }
        
                                                //No return cujo filho e a expressao
                                                (yyval.no_ast) = asd_new("return", function_type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                            }
#line 2124 "parser.tab.c"
    break;

  case 41: /* flow_ctrl: conditional  */
#line 537 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2130 "parser.tab.c"
    break;

  case 42: /* flow_ctrl: while  */
#line 538 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2136 "parser.tab.c"
    break;

  case 43: /* conditional: TK_PR_IF '(' expressao ')' command_block  */
#line 542 "src/parser.y"
                                                                            {   // Sem else
                                                                                (yyval.no_ast) = asd_new("if", (yyvsp[-2].no_ast)->type);
                                                                                if((yyvsp[-2].no_ast)!=NULL){
                                                                                    asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                                                }
                                                                                if((yyvsp[0].no_ast) != NULL){
                                                                                    asd_add_child((yyval.no_ast), (yyvsp[0].no_ast)); 
                                                                                }
                                                                                //if ($6) asd_add_child($$, $6);
                                                                            }
#line 2151 "parser.tab.c"
    break;

  case 44: /* conditional: TK_PR_IF '(' expressao ')' command_block TK_PR_ELSE command_block  */
#line 552 "src/parser.y"
                                                                            {   
                                                                                // Tipo dos dois blocos deve ser igual
                                                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                                                    semantic_error(ERR_WRONG_TYPE, "Erro: tipo do bloco 'if' diferente do bloco 'else'", get_line_number());
                                                                                }
        
        
        
                                                                                // Com else command_block vira filho
                                                                                (yyval.no_ast) = asd_new("if", (yyvsp[-4].no_ast)->type);
                                                                                if((yyvsp[-4].no_ast)!=NULL){
                                                                                    asd_add_child((yyval.no_ast), (yyvsp[-4].no_ast));
                                                                                }
                                                                                if((yyvsp[-2].no_ast) != NULL){
                                                                                    asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast)); 
                                                                                }
                                                                                if ((yyvsp[0].no_ast) != NULL) asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                                                            }
#line 2175 "parser.tab.c"
    break;

  case 45: /* while: TK_PR_WHILE '(' expressao ')' command_block  */
#line 574 "src/parser.y"
                                                                {
                                                                    (yyval.no_ast) = asd_new("while", (yyvsp[-2].no_ast)->type);
                                                                    if((yyvsp[-2].no_ast)!=NULL){
                                                                        asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                                    }
                                                                    if((yyvsp[0].no_ast) != NULL){
                                                                        asd_add_child((yyval.no_ast), (yyvsp[0].no_ast)); 
                                                                    }
                                                                }
#line 2189 "parser.tab.c"
    break;

  case 46: /* expressao: n7  */
#line 586 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2195 "parser.tab.c"
    break;

  case 47: /* n7: n7 '|' n6  */
#line 590 "src/parser.y"
                                            {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: operacao '|' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("|", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2211 "parser.tab.c"
    break;

  case 48: /* n7: n6  */
#line 601 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2217 "parser.tab.c"
    break;

  case 49: /* n6: n6 '&' n5  */
#line 605 "src/parser.y"
                                            {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: operacao '&' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("&", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2233 "parser.tab.c"
    break;

  case 50: /* n6: n5  */
#line 616 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2239 "parser.tab.c"
    break;

  case 51: /* n5: n5 TK_OC_EQ n4  */
#line 620 "src/parser.y"
                                            {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '==' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("==", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2255 "parser.tab.c"
    break;

  case 52: /* n5: n5 TK_OC_NE n4  */
#line 631 "src/parser.y"
                                            {   
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '!=' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("!=", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2269 "parser.tab.c"
    break;

  case 53: /* n5: n4  */
#line 640 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2275 "parser.tab.c"
    break;

  case 54: /* n4: n4 '<' n3  */
#line 644 "src/parser.y"
                                            {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '<' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("<", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2291 "parser.tab.c"
    break;

  case 55: /* n4: n4 '>' n3  */
#line 655 "src/parser.y"
                                            {   
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '>' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new(">", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2305 "parser.tab.c"
    break;

  case 56: /* n4: n4 TK_OC_LE n3  */
#line 664 "src/parser.y"
                                            {   
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '<=' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("<=", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2319 "parser.tab.c"
    break;

  case 57: /* n4: n4 TK_OC_GE n3  */
#line 673 "src/parser.y"
                                            {   
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '>=' entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new(">=", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2333 "parser.tab.c"
    break;

  case 58: /* n4: n3  */
#line 682 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2339 "parser.tab.c"
    break;

  case 59: /* n3: n3 '+' n2  */
#line 686 "src/parser.y"
                                            {   
                                                // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: soma entre tipos incompativeis", get_line_number());
                                                }

                                                (yyval.no_ast) = asd_new("+", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2355 "parser.tab.c"
    break;

  case 60: /* n3: n3 '-' n2  */
#line 697 "src/parser.y"
                                            {   
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: subtracao entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("-", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2369 "parser.tab.c"
    break;

  case 61: /* n3: n2  */
#line 706 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2375 "parser.tab.c"
    break;

  case 62: /* n2: n2 '*' n1  */
#line 710 "src/parser.y"
                                            {   // Verifica se os tipos sao iguais
                                                // Se forem diferentes, ERR_WRONG_TYPE
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: multiplicacao entre tipos incompativeis", get_line_number());
                                                }

                                                (yyval.no_ast) = asd_new("*", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2390 "parser.tab.c"
    break;

  case 63: /* n2: n2 '/' n1  */
#line 720 "src/parser.y"
                                            {   
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: divisao entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("/", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2404 "parser.tab.c"
    break;

  case 64: /* n2: n2 '%' n1  */
#line 729 "src/parser.y"
                                            {   
                                                if((yyvsp[-2].no_ast)->type != (yyvsp[0].no_ast)->type){
                                                    semantic_error(ERR_WRONG_TYPE, "Erro: modulo entre tipos incompativeis", get_line_number());
                                                }
        
                                                (yyval.no_ast) = asd_new("%", (yyvsp[-2].no_ast)->type);
                                                asd_add_child((yyval.no_ast), (yyvsp[-2].no_ast));
                                                asd_add_child((yyval.no_ast), (yyvsp[0].no_ast));
                                            }
#line 2418 "parser.tab.c"
    break;

  case 65: /* n2: n1  */
#line 738 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2424 "parser.tab.c"
    break;

  case 66: /* n1: '+' n1  */
#line 742 "src/parser.y"
                                            { (yyval.no_ast) = asd_new("+", (yyvsp[0].no_ast)->type); asd_add_child((yyval.no_ast), (yyvsp[0].no_ast)); }
#line 2430 "parser.tab.c"
    break;

  case 67: /* n1: '-' n1  */
#line 743 "src/parser.y"
                                            { (yyval.no_ast) = asd_new("-", (yyvsp[0].no_ast)->type); asd_add_child((yyval.no_ast), (yyvsp[0].no_ast)); }
#line 2436 "parser.tab.c"
    break;

  case 68: /* n1: '!' n1  */
#line 744 "src/parser.y"
                                            { (yyval.no_ast) = asd_new("!", (yyvsp[0].no_ast)->type); asd_add_child((yyval.no_ast), (yyvsp[0].no_ast)); }
#line 2442 "parser.tab.c"
    break;

  case 69: /* n1: n0  */
#line 745 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2448 "parser.tab.c"
    break;

  case 70: /* n0: TK_ID  */
#line 749 "src/parser.y"
                                            {
                                                // Verificar se a variavel foi declarada em algum escopo
                                                char *varname = (yyvsp[0].lex_val)->token_val;
                                                struct entry *e = search_entry_in_stack(stack, varname);
                                                if (e == NULL){
                                                    semantic_error(ERR_UNDECLARED, "Identificador nao declarado", (yyvsp[0].lex_val)->line_number);
                                                }
                                                if (e->nature == NATURE_FUNC){
                                                    semantic_error(ERR_FUNCTION, "Erro: funcao sendo usada como variavel", (yyvsp[0].lex_val)->line_number);
                                                }
                                                (yyval.no_ast) = asd_new((yyvsp[0].lex_val)->token_val, e->type);
                                                if((yyvsp[0].lex_val)){
                                                    free((yyvsp[0].lex_val)->token_val); 
                                                    free((yyvsp[0].lex_val));
                                                }
                                            }
#line 2469 "parser.tab.c"
    break;

  case 71: /* n0: TK_LI_INT  */
#line 765 "src/parser.y"
                                            {
                                                (yyval.no_ast) = asd_new((yyvsp[0].lex_val)->token_val, TYPE_INT);
                                                if((yyvsp[0].lex_val)){
                                                    free((yyvsp[0].lex_val)->token_val); 
                                                    free((yyvsp[0].lex_val));
                                                }
                                            }
#line 2481 "parser.tab.c"
    break;

  case 72: /* n0: TK_LI_FLOAT  */
#line 772 "src/parser.y"
                                            {
                                                (yyval.no_ast) = asd_new((yyvsp[0].lex_val)->token_val, TYPE_FLOAT);
                                                if((yyvsp[0].lex_val)){
                                                    free((yyvsp[0].lex_val)->token_val); 
                                                    free((yyvsp[0].lex_val));
                                                }
                                            }
#line 2493 "parser.tab.c"
    break;

  case 73: /* n0: call_func  */
#line 779 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[0].no_ast); }
#line 2499 "parser.tab.c"
    break;

  case 74: /* n0: '(' expressao ')'  */
#line 780 "src/parser.y"
                                            { (yyval.no_ast) = (yyvsp[-1].no_ast); }
#line 2505 "parser.tab.c"
    break;

  case 75: /* push_table: %empty  */
#line 783 "src/parser.y"
                                               {
                                                // Criar tabela
                                                struct table *table = create_table();
                                                // Colocar tabela na pilha
                                                push_table_stack(&stack, table);
                                                (yyval.no_ast) = NULL;
                                            }
#line 2517 "parser.tab.c"
    break;

  case 76: /* pop_table: %empty  */
#line 791 "src/parser.y"
                                           {
                                                // Tirar tabela do topo da pilha
                                                pop_table_stack(&stack);
                                                (yyval.no_ast) = NULL;
                                            }
#line 2527 "parser.tab.c"
    break;


#line 2531 "parser.tab.c"

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
          = {yyssp, yytoken};
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
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

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
                      yytoken, &yylval);
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


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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
  yyerror (YY_("memory exhausted"));
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
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
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

#line 797 "src/parser.y"


void yyerror(const char *msg) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", get_line_number(), msg);
}
