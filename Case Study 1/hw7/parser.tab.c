/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"



#include "scanType.h"  
#include "AST.h"
#include "semantic.h"
#include "IOinit.h"
#include "yyerror.h"
#include "codeGeneration.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>  
#include <getopt.h>
#include <iostream>
#include <string>
#include <fstream>

extern int yylex();
extern FILE *yyin;
extern int line;       
extern int numErrors;  
int numWarnings;       
bool isPrintingTreeTypes = false;

//memeory information
bool isPrintingMemoryOffset = false;
bool isPrintingMemorySize;
extern int globalOffset;

bool isOnlyPrintingMemoryInfo; 


static TreeNode* ROOT;

extern SymbolTable symbolTable;


// #define YYERROR_VERBOSE


#line 125 "parser.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    NUMCONST = 259,
    CHARCONST = 260,
    STRINGCONST = 261,
    ASGN = 262,
    ADDASGN = 263,
    SUBASS = 264,
    INC = 265,
    DEC = 266,
    GEQ = 267,
    LEQ = 268,
    NEQ = 269,
    MULASS = 270,
    DIVASS = 271,
    INT = 272,
    IF = 273,
    OR = 274,
    NOT = 275,
    BY = 276,
    ELSE = 277,
    THEN = 278,
    FOR = 279,
    BREAK = 280,
    RETURN = 281,
    BOOL = 282,
    CHAR = 283,
    STATIC = 284,
    AND = 285,
    BEGN = 286,
    FINISH = 287,
    DO = 288,
    WHILE = 289,
    TO = 290,
    BOOLCONST = 291,
    QUESTION = 292,
    LESS = 293,
    GREAT = 294,
    PLUS = 295,
    EQUAL = 296,
    MULT = 297,
    DIV = 298,
    MOD = 299,
    COMMA = 300,
    OBRACKET = 301,
    CBRACKET = 302,
    MINUS = 303,
    COLON = 304,
    SEMICOLON = 305,
    OPAREN = 306,
    CPAREN = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 58 "parser.y"

  ExpType type;           
  TokenData* tokenData; 
  TreeNode* node;        

#line 236 "parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */



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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


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
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   666

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

#define YYUNDEFTOK  2
#define YYMAXUTOK   307


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    82,    82,    86,    87,    90,    91,    92,    96,    97,
      98,   102,   109,   113,   114,   115,   116,   120,   121,   122,
     126,   130,   137,   138,   141,   142,   143,   149,   158,   163,
     164,   165,   166,   169,   170,   175,   176,   177,   178,   182,
     183,   187,   188,   189,   190,   193,   196,   202,   203,   206,
     207,   212,   217,   225,   226,   227,   228,   229,   230,   231,
     234,   239,   243,   248,   256,   257,   260,   261,   262,   265,
     266,   267,   268,   273,   281,   282,   285,   286,   289,   293,
     298,   299,   300,   303,   306,   312,   316,   321,   325,   329,
     333,   337,   343,   348,   350,   355,   360,   361,   362,   363,
     366,   372,   373,   376,   382,   383,   386,   390,   391,   394,
     399,   400,   403,   407,   412,   416,   421,   425,   431,   435,
     436,   439,   443,   449,   453,   454,   457,   461,   465,   471,
     474,   475,   478,   482,   486,   492,   495,   504,   505,   506,
     507,   510,   511,   515,   519,   522,   523,   526,   527,   528,
     530,   534,   539,   545
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "NUMCONST", "CHARCONST",
  "STRINGCONST", "ASGN", "ADDASGN", "SUBASS", "INC", "DEC", "GEQ", "LEQ",
  "NEQ", "MULASS", "DIVASS", "INT", "IF", "OR", "NOT", "BY", "ELSE",
  "THEN", "FOR", "BREAK", "RETURN", "BOOL", "CHAR", "STATIC", "AND",
  "BEGN", "FINISH", "DO", "WHILE", "TO", "BOOLCONST", "QUESTION", "LESS",
  "GREAT", "PLUS", "EQUAL", "MULT", "DIV", "MOD", "COMMA", "OBRACKET",
  "CBRACKET", "MINUS", "COLON", "SEMICOLON", "OPAREN", "CPAREN", "$accept",
  "program", "declarationList", "declaration", "varDeclaration",
  "scopedtypespecificer", "vardeclarationList", "varDeclarationInit",
  "varDeclarationId", "typespec", "funDeclaration", "parameters",
  "parameterList", "parameterTypeList", "parameterIdList", "parameterId",
  "statement", "matched", "unmatched", "expstatement", "statementEnd",
  "compoundstatement", "localdeclaration", "statementList", "iterRange",
  "returnstatement", "breakstatement", "asgnop", "exp", "simpleExp",
  "andExp", "relExp", "unaryRelExp", "operator", "sumExp", "sumop",
  "mulExp", "mulop", "unaryExp", "unaryop", "mutable", "immutable",
  "factor", "call", "args", "argList", "constant", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307
};
# endif

#define YYPACT_NINF (-183)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-147)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     127,   614,    24,  -183,  -183,  -183,    84,   632,  -183,  -183,
     179,  -183,   170,    51,   103,  -183,    56,     9,  -183,  -183,
     236,   120,   134,  -183,   304,   131,   253,  -183,   304,   181,
     256,    64,    70,  -183,  -183,    11,  -183,    55,   140,  -183,
    -183,  -183,   317,  -183,  -183,  -183,  -183,   324,   105,   106,
    -183,  -183,   239,   180,  -183,   549,  -183,  -183,  -183,  -183,
    -183,  -183,   102,   170,  -183,   105,   107,   110,   138,  -183,
      10,    90,   181,   124,  -183,   344,    89,    55,  -183,   154,
     141,   105,   230,   373,   393,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,  -183,   562,   602,  -183,  -183,  -183,   615,    55,
    -183,  -183,   153,   261,  -183,  -183,  -183,  -183,  -183,   163,
     154,   160,  -183,   151,   166,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,   344,  -183,  -183,  -183,   400,    55,   106,    55,
    -183,    55,   -21,    55,   180,    55,  -183,  -183,  -183,  -183,
      94,  -183,  -183,  -183,   413,  -183,   154,  -183,    40,  -183,
     270,   184,   154,  -183,   270,   147,    14,   453,   290,   162,
     109,  -183,   466,  -183,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,   186,   156,  -183,  -183,    20,    21,  -183,   240,
    -183,    38,  -183,   193,   -19,    53,  -183,  -183,   224,   264,
     264,   473,  -183,  -183,   224,   264,   493,   291,   466,  -183,
    -183,   241,  -183,   254,    45,   263,    -2,  -183,  -183,  -183,
      76,    85,   295,    54,   264,   264,   302,   224,   264,   522,
     224,   224,   473,   224,  -183,  -183,  -183,  -183,  -183,  -183,
    -183,  -183,    55,   278,   282,   289,   280,   542,   224,   224,
     224,    55,   105
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,    24,    26,    25,     0,     0,     4,     6,
       0,     5,    16,    20,     0,    15,    17,     0,     1,     3,
      29,    20,     0,    23,     0,     0,     0,     9,     0,    31,
       0,     0,    33,    36,    10,     0,     8,     0,   135,   150,
     151,   153,     0,   152,   134,   133,   132,     0,    19,   101,
     110,   104,   108,   119,   124,     0,   141,   142,   130,   138,
     139,    22,     0,    14,    13,    18,    40,    45,    39,    42,
       0,     0,    30,     0,   144,     0,     0,   111,   109,   140,
       0,    93,   141,     0,     0,   113,   115,   117,   114,   112,
     121,   116,   122,     0,     0,   126,   127,   128,     0,   131,
     129,    21,     0,     0,    32,    75,    28,    37,    35,     0,
       0,     0,   148,     0,   145,    87,    88,    89,    98,    99,
      90,    91,     0,   137,    94,    95,     0,   102,   100,   105,
     103,   107,   106,   120,   118,   125,   123,    46,    43,    41,
      77,    27,   136,   143,     0,    96,    97,    92,     0,    74,
       0,     0,   149,   147,     0,     0,     0,     0,     0,     0,
       0,    73,     0,    67,    76,    47,    48,    69,    49,    70,
      72,    71,     0,     0,    12,    68,    53,     0,    59,     0,
      86,     0,    83,     0,    57,     0,    66,    11,     0,     0,
       0,     0,    85,    84,     0,     0,     0,     0,     0,    54,
      64,    47,    61,    47,     0,     0,     0,    56,    51,    62,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    55,    65,    50,    60,    81,    58,
      52,    63,    80,    78,     0,     0,     0,     0,     0,     0,
       0,    82,    79
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -183,  -183,  -183,   309,  -183,  -183,    -7,   293,  -183,     2,
    -183,   296,  -183,   246,  -183,   223,  -182,  -138,   -37,  -183,
    -183,   -54,  -183,  -183,   111,  -183,  -183,   250,   -41,   -23,
     251,  -183,   -22,  -183,   242,  -183,   244,  -183,   -40,  -183,
     -24,  -183,  -183,  -183,  -183,  -183,  -183
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     6,     7,     8,     9,   149,    14,    15,    16,    30,
      11,    31,    32,    33,    68,    69,   164,   208,   166,   167,
     168,   169,   140,   151,   205,   170,   171,   122,   172,    81,
      49,    50,    51,    93,    52,    94,    53,    98,    54,    55,
      82,    57,    58,    59,   113,   114,    60
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      56,    48,    10,    22,    56,    65,    80,   200,   202,    10,
      29,   104,    72,   165,   194,   100,   106,    83,    56,    90,
      78,   115,   116,   117,   118,   119,     3,    92,     3,   120,
     121,    56,    74,   219,   111,   112,     4,     5,     4,     5,
      83,   105,   188,   189,   190,   115,   116,   117,   118,   119,
     199,   201,   203,   120,   121,   141,   207,     3,   136,    56,
      56,   -34,   130,   -34,   175,    74,   216,     4,     5,    56,
      56,    74,    83,    83,    56,    17,   224,   226,   217,   229,
     230,   145,   234,   235,    18,   147,   195,   223,   192,    74,
     110,   107,    38,    39,    40,    41,    74,    25,   188,   220,
     224,   226,   230,   153,    83,    28,    74,     3,   221,    42,
     181,     3,    38,    39,    40,    41,    70,     4,     5,   183,
      71,     4,     5,   148,    83,    43,    44,    74,     1,    42,
       2,    45,    61,    56,   177,    62,    84,    46,    56,   185,
      47,  -146,   150,   155,     3,    43,    44,   173,    26,   101,
     154,    45,   -44,    27,     4,     5,   102,    46,   209,   182,
      47,   115,   116,   117,   118,   119,    25,    56,   206,   120,
     121,    35,    56,   211,    56,   213,   109,   225,   227,    26,
      20,   231,    21,   103,    36,   156,    75,    38,    39,    40,
      41,    76,    26,   123,   105,    56,   233,   174,    56,   206,
     137,    26,   157,   143,    42,    74,   187,   142,   158,   159,
     160,   144,   180,    56,   242,   105,   161,    23,   162,    24,
      43,    44,    95,    96,    97,   156,    45,    38,    39,    40,
      41,   -38,    46,   -38,   163,    47,   186,   115,   116,   117,
     124,   125,   196,   193,    42,   120,   121,   191,   197,   159,
     160,    85,    86,    87,    63,   105,    13,    66,   198,    67,
      43,    44,   138,   214,    67,   156,    45,    38,    39,    40,
      41,    12,    46,    13,   163,    47,   215,    88,    89,    90,
      91,   -16,   157,    23,    42,    24,    34,    92,   158,   159,
     160,   178,   178,   179,   212,   105,   218,    83,   162,   237,
      43,    44,   222,   228,   238,    37,    45,    38,    39,    40,
      41,   239,    46,   240,   163,    47,    19,   108,    77,    64,
      38,    39,    40,    41,    42,    79,   139,    38,    39,    40,
      41,    73,   126,   236,   128,   132,     0,    42,   134,     0,
      43,    44,     0,     0,    42,   110,    45,    38,    39,    40,
      41,     0,    46,    43,    44,    47,     0,     0,     0,    45,
      43,    44,     0,     0,    42,    46,    45,     0,    47,     0,
       0,     0,    46,     0,   127,    47,    38,    39,    40,    41,
      43,    44,     0,     0,     0,     0,    45,     0,     0,     0,
       0,     0,    46,    42,   129,    47,    38,    39,    40,    41,
       0,   146,     0,    38,    39,    40,    41,     0,     0,    43,
      44,     0,     0,    42,   152,    45,    38,    39,    40,    41,
      42,    46,     0,     0,    47,     0,     0,     0,     0,    43,
      44,     0,     0,    42,     0,    45,    43,    44,     0,     0,
       0,    46,    45,     0,    47,     0,     0,     0,    46,    43,
      44,    47,     0,     0,   176,    45,    38,    39,    40,    41,
       0,    46,     0,     0,    47,     0,     0,   184,     0,    38,
      39,    40,    41,    42,   204,     0,    38,    39,    40,    41,
       0,     0,     0,     0,     0,     0,    42,     0,     0,    43,
      44,     0,     0,    42,   210,    45,    38,    39,    40,    41,
       0,    46,    43,    44,    47,     0,     0,     0,    45,    43,
      44,     0,     0,    42,    46,    45,     0,    47,     0,     0,
       0,    46,     0,   232,    47,    38,    39,    40,    41,    43,
      44,     0,     0,     0,     0,    45,     0,     0,     0,     0,
       0,    46,    42,   241,    47,    38,    39,    40,    41,     0,
      99,     0,    38,    39,    40,    41,     0,     0,    43,    44,
       0,     0,    42,   131,    45,    38,    39,    40,    41,     0,
      46,     0,     0,    47,     0,     0,     0,     0,    43,    44,
       0,     0,     0,     0,    45,    43,    44,     0,     0,     0,
      46,    45,     0,    47,     0,     0,     0,    46,    43,    44,
      47,     0,     0,   133,    45,    38,    39,    40,    41,     0,
      46,     0,     0,    47,    -7,    12,   135,    13,    38,    39,
      40,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    -7,    -2,     1,     0,     2,     0,     0,    43,    44,
       0,    -7,    -7,     0,    45,     0,     0,     0,     0,     3,
      46,    43,    44,    47,     0,     0,     0,    45,     0,     4,
       5,     0,     0,    46,     0,     0,    47
};

static const yytype_int16 yycheck[] =
{
      24,    24,     0,    10,    28,    28,    47,   189,   190,     7,
       1,     1,     1,   151,    33,    55,    70,    19,    42,    40,
      42,     7,     8,     9,    10,    11,    17,    48,    17,    15,
      16,    55,    51,    35,    75,    76,    27,    28,    27,    28,
      19,    31,    22,    23,    23,     7,     8,     9,    10,    11,
     188,   189,   190,    15,    16,   109,   194,    17,    98,    83,
      84,    52,    84,    52,    50,    51,    21,    27,    28,    93,
      94,    51,    19,    19,    98,    51,   214,   215,    33,   217,
     218,   122,   220,   221,     0,   126,    33,    33,    50,    51,
       1,     1,     3,     4,     5,     6,    51,    46,    22,    23,
     238,   239,   240,   144,    19,    49,    51,    17,    23,    20,
       1,    17,     3,     4,     5,     6,    52,    27,    28,   160,
      50,    27,    28,    29,    19,    36,    37,    51,     1,    20,
       3,    42,     1,   157,   157,     4,    30,    48,   162,   162,
      51,    52,   140,   150,    17,    36,    37,   154,    45,    47,
     148,    42,    45,    50,    27,    28,    46,    48,   195,    50,
      51,     7,     8,     9,    10,    11,    46,   191,   191,    15,
      16,    51,   196,   196,   198,   198,    52,   214,   215,    45,
       1,   218,     3,    45,    50,     1,    46,     3,     4,     5,
       6,    51,    45,    52,    31,   219,   219,    50,   222,   222,
      47,    45,    18,    52,    20,    51,    50,    47,    24,    25,
      26,    45,    50,   237,   237,    31,    32,    47,    34,    49,
      36,    37,    42,    43,    44,     1,    42,     3,     4,     5,
       6,    50,    48,    52,    50,    51,    50,     7,     8,     9,
      10,    11,    18,    50,    20,    15,    16,     7,    24,    25,
      26,    12,    13,    14,     1,    31,     3,     1,    34,     3,
      36,    37,     1,    22,     3,     1,    42,     3,     4,     5,
       6,     1,    48,     3,    50,    51,    22,    38,    39,    40,
      41,    45,    18,    47,    20,    49,    50,    48,    24,    25,
      26,     1,     1,     3,     3,    31,    33,    19,    34,    21,
      36,    37,     7,     1,    22,     1,    42,     3,     4,     5,
       6,    22,    48,    33,    50,    51,     7,    71,     1,    26,
       3,     4,     5,     6,    20,     1,   103,     3,     4,     5,
       6,    35,    82,   222,    83,    93,    -1,    20,    94,    -1,
      36,    37,    -1,    -1,    20,     1,    42,     3,     4,     5,
       6,    -1,    48,    36,    37,    51,    -1,    -1,    -1,    42,
      36,    37,    -1,    -1,    20,    48,    42,    -1,    51,    -1,
      -1,    -1,    48,    -1,     1,    51,     3,     4,     5,     6,
      36,    37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    48,    20,     1,    51,     3,     4,     5,     6,
      -1,     1,    -1,     3,     4,     5,     6,    -1,    -1,    36,
      37,    -1,    -1,    20,     1,    42,     3,     4,     5,     6,
      20,    48,    -1,    -1,    51,    -1,    -1,    -1,    -1,    36,
      37,    -1,    -1,    20,    -1,    42,    36,    37,    -1,    -1,
      -1,    48,    42,    -1,    51,    -1,    -1,    -1,    48,    36,
      37,    51,    -1,    -1,     1,    42,     3,     4,     5,     6,
      -1,    48,    -1,    -1,    51,    -1,    -1,     1,    -1,     3,
       4,     5,     6,    20,     1,    -1,     3,     4,     5,     6,
      -1,    -1,    -1,    -1,    -1,    -1,    20,    -1,    -1,    36,
      37,    -1,    -1,    20,     1,    42,     3,     4,     5,     6,
      -1,    48,    36,    37,    51,    -1,    -1,    -1,    42,    36,
      37,    -1,    -1,    20,    48,    42,    -1,    51,    -1,    -1,
      -1,    48,    -1,     1,    51,     3,     4,     5,     6,    36,
      37,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      -1,    48,    20,     1,    51,     3,     4,     5,     6,    -1,
       1,    -1,     3,     4,     5,     6,    -1,    -1,    36,    37,
      -1,    -1,    20,     1,    42,     3,     4,     5,     6,    -1,
      48,    -1,    -1,    51,    -1,    -1,    -1,    -1,    36,    37,
      -1,    -1,    -1,    -1,    42,    36,    37,    -1,    -1,    -1,
      48,    42,    -1,    51,    -1,    -1,    -1,    48,    36,    37,
      51,    -1,    -1,     1,    42,     3,     4,     5,     6,    -1,
      48,    -1,    -1,    51,     0,     1,     1,     3,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    17,     0,     1,    -1,     3,    -1,    -1,    36,    37,
      -1,    27,    28,    -1,    42,    -1,    -1,    -1,    -1,    17,
      48,    36,    37,    51,    -1,    -1,    -1,    42,    -1,    27,
      28,    -1,    -1,    48,    -1,    -1,    51
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    17,    27,    28,    54,    55,    56,    57,
      62,    63,     1,     3,    59,    60,    61,    51,     0,    56,
       1,     3,    59,    47,    49,    46,    45,    50,    49,     1,
      62,    64,    65,    66,    50,    51,    50,     1,     3,     4,
       5,     6,    20,    36,    37,    42,    48,    51,    82,    83,
      84,    85,    87,    89,    91,    92,    93,    94,    95,    96,
      99,     1,     4,     1,    60,    82,     1,     3,    67,    68,
      52,    50,     1,    64,    51,    46,    51,     1,    85,     1,
      81,    82,    93,    19,    30,    12,    13,    14,    38,    39,
      40,    41,    48,    86,    88,    42,    43,    44,    90,     1,
      91,    47,    46,    45,     1,    31,    74,     1,    66,    52,
       1,    81,    81,    97,    98,     7,     8,     9,    10,    11,
      15,    16,    80,    52,    10,    11,    80,     1,    83,     1,
      85,     1,    87,     1,    89,     1,    91,    47,     1,    68,
      75,    74,    47,    52,    45,    81,     1,    81,    29,    58,
      62,    76,     1,    81,    62,    59,     1,    18,    24,    25,
      26,    32,    34,    50,    69,    70,    71,    72,    73,    74,
      78,    79,    81,    59,    50,    50,     1,    82,     1,     3,
      50,     1,    50,    81,     1,    82,    50,    50,    22,    23,
      23,     7,    50,    50,    33,    33,    18,    24,    34,    70,
      69,    70,    69,    70,     1,    77,    82,    70,    70,    71,
       1,    82,     3,    82,    22,    22,    21,    33,    33,    35,
      23,    23,     7,    33,    70,    71,    70,    71,     1,    70,
      70,    71,     1,    82,    70,    70,    77,    21,    22,    22,
      33,     1,    82
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    56,    57,    57,
      57,    58,    58,    59,    59,    59,    59,    60,    60,    60,
      61,    61,    61,    61,    62,    62,    62,    63,    63,    63,
      63,    63,    63,    64,    64,    65,    65,    65,    65,    66,
      66,    67,    67,    67,    67,    68,    68,    69,    69,    70,
      70,    70,    70,    70,    70,    70,    70,    70,    70,    70,
      71,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    73,    73,    74,    75,    75,    76,    76,    77,    77,
      77,    77,    77,    78,    78,    78,    79,    80,    80,    80,
      80,    80,    81,    81,    81,    81,    81,    81,    81,    81,
      82,    82,    82,    83,    83,    83,    84,    84,    84,    85,
      85,    85,    86,    86,    86,    86,    86,    86,    87,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    90,    91,
      91,    91,    92,    92,    92,    93,    93,    94,    94,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      99,    99,    99,    99
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     3,     3,
       3,     4,     3,     3,     3,     1,     1,     1,     3,     3,
       1,     4,     3,     2,     1,     1,     1,     6,     5,     2,
       4,     3,     5,     1,     0,     3,     1,     3,     1,     2,
       2,     3,     1,     3,     1,     1,     3,     1,     1,     1,
       6,     4,     6,     2,     4,     6,     4,     2,     6,     2,
       6,     4,     4,     6,     4,     6,     2,     1,     2,     1,
       1,     1,     1,     4,     2,     0,     2,     0,     3,     5,
       3,     3,     5,     2,     3,     3,     2,     1,     1,     1,
       1,     1,     3,     1,     2,     2,     3,     3,     2,     2,
       3,     1,     3,     3,     1,     3,     3,     3,     1,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     1,     3,     1,     3,     1,     1,     1,     2,
       1,     2,     1,     1,     1,     1,     4,     3,     1,     1,
       2,     1,     1,     4,     2,     1,     0,     3,     1,     3,
       1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
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
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
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
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
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
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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
  case 2:
#line 82 "parser.y"
                                                                 { ROOT = (yyvsp[0].node);}
#line 1680 "parser.tab.c"
    break;

  case 3:
#line 86 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1686 "parser.tab.c"
    break;

  case 4:
#line 87 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1692 "parser.tab.c"
    break;

  case 5:
#line 90 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1698 "parser.tab.c"
    break;

  case 6:
#line 91 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1704 "parser.tab.c"
    break;

  case 7:
#line 92 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 1710 "parser.tab.c"
    break;

  case 8:
#line 96 "parser.y"
                                                              { (yyval.node) = (yyvsp[-1].node); setType((yyval.node), (yyvsp[-2].type)); yyerrok;}
#line 1716 "parser.tab.c"
    break;

  case 9:
#line 97 "parser.y"
                                                              { (yyval.node) = NULL; yyerrok;}
#line 1722 "parser.tab.c"
    break;

  case 10:
#line 98 "parser.y"
                                                              { (yyval.node) = NULL; yyerrok;}
#line 1728 "parser.tab.c"
    break;

  case 11:
#line 102 "parser.y"
                                                                {   
                                                                  (yyval.node) = (yyvsp[-1].node); 
                                                                  (yyval.node)->isStatic = true; 
                                                                  setType((yyval.node), (yyvsp[-2].type));
                                                                  yyerrok;
                                                                }
#line 1739 "parser.tab.c"
    break;

  case 12:
#line 109 "parser.y"
                                                               { (yyval.node) = (yyvsp[-1].node); setType((yyval.node), (yyvsp[-2].type)); yyerrok;}
#line 1745 "parser.tab.c"
    break;

  case 13:
#line 113 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); yyerrok;}
#line 1751 "parser.tab.c"
    break;

  case 14:
#line 114 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 1757 "parser.tab.c"
    break;

  case 15:
#line 115 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1763 "parser.tab.c"
    break;

  case 16:
#line 116 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1769 "parser.tab.c"
    break;

  case 17:
#line 120 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1775 "parser.tab.c"
    break;

  case 18:
#line 121 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-2].node); (yyvsp[-2].node)->child[0] = (yyvsp[0].node);}
#line 1781 "parser.tab.c"
    break;

  case 19:
#line 122 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 1787 "parser.tab.c"
    break;

  case 20:
#line 126 "parser.y"
                                                                 { (yyval.node) = newDeclNode(VarK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                 }
#line 1795 "parser.tab.c"
    break;

  case 21:
#line 130 "parser.y"
                                                                 { (yyval.node) = newDeclNode(VarK, (yyvsp[-3].tokenData));       
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                   (yyval.node)->isArray = true;
                                                                   (yyval.node)->arraySize = (yyvsp[-1].tokenData)->nvalue;
                                                                   (yyval.node)->thisTokenData = (yyvsp[-3].tokenData); 
                                                                   (yyval.node)->expType = UndefinedType;
                                                                 }
#line 1807 "parser.tab.c"
    break;

  case 22:
#line 137 "parser.y"
                                                               { (yyval.node) = NULL;}
#line 1813 "parser.tab.c"
    break;

  case 23:
#line 138 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 1819 "parser.tab.c"
    break;

  case 24:
#line 141 "parser.y"
                                                              { (yyval.type) = Integer; }
#line 1825 "parser.tab.c"
    break;

  case 25:
#line 142 "parser.y"
                                                                 { (yyval.type) = Char; }
#line 1831 "parser.tab.c"
    break;

  case 26:
#line 143 "parser.y"
                                                                 { (yyval.type) = Boolean;}
#line 1837 "parser.tab.c"
    break;

  case 27:
#line 151 "parser.y"
                                                                 { (yyval.node) = newDeclNode(FuncK, (yyvsp[-4].tokenData));     
                                                                   (yyval.node)->attr.name = (yyvsp[-4].tokenData)->tokenstr;
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->expType = (yyvsp[-5].type);
                                                                 }
#line 1848 "parser.tab.c"
    break;

  case 28:
#line 158 "parser.y"
                                                                 { (yyval.node) = newDeclNode(FuncK, (yyvsp[-4].tokenData));   
                                                                   (yyval.node)->attr.name = (yyvsp[-4].tokenData)->tokenstr;
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 1858 "parser.tab.c"
    break;

  case 29:
#line 163 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1864 "parser.tab.c"
    break;

  case 30:
#line 164 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1870 "parser.tab.c"
    break;

  case 31:
#line 165 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1876 "parser.tab.c"
    break;

  case 32:
#line 166 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1882 "parser.tab.c"
    break;

  case 33:
#line 169 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1888 "parser.tab.c"
    break;

  case 34:
#line 170 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 1894 "parser.tab.c"
    break;

  case 35:
#line 175 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1900 "parser.tab.c"
    break;

  case 36:
#line 176 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1906 "parser.tab.c"
    break;

  case 37:
#line 177 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1912 "parser.tab.c"
    break;

  case 38:
#line 178 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1918 "parser.tab.c"
    break;

  case 39:
#line 182 "parser.y"
                                                              { (yyval.node) = (yyvsp[0].node); setType((yyval.node), (yyvsp[-1].type)); }
#line 1924 "parser.tab.c"
    break;

  case 40:
#line 183 "parser.y"
                                                              { (yyval.node) = NULL;}
#line 1930 "parser.tab.c"
    break;

  case 41:
#line 187 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); yyerrok; }
#line 1936 "parser.tab.c"
    break;

  case 42:
#line 188 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1942 "parser.tab.c"
    break;

  case 43:
#line 189 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1948 "parser.tab.c"
    break;

  case 44:
#line 190 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 1954 "parser.tab.c"
    break;

  case 45:
#line 193 "parser.y"
                                                                 { (yyval.node) = newDeclNode(ParamK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr; 
                                                                 }
#line 1962 "parser.tab.c"
    break;

  case 46:
#line 196 "parser.y"
                                                                 { (yyval.node) = newDeclNode(ParamK, (yyvsp[-2].tokenData));
                                                                   (yyval.node)->isArray = true;
                                                                   (yyval.node)->attr.name = (yyvsp[-2].tokenData)->tokenstr; 
                                                                 }
#line 1971 "parser.tab.c"
    break;

  case 47:
#line 202 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1977 "parser.tab.c"
    break;

  case 48:
#line 203 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1983 "parser.tab.c"
    break;

  case 49:
#line 206 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 1989 "parser.tab.c"
    break;

  case 50:
#line 207 "parser.y"
                                                                 { (yyval.node) = newStmtNode(IfK, (yyvsp[-5].tokenData)); 
                                                                   (yyval.node)->child[0] = (yyvsp[-4].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                 }
#line 1999 "parser.tab.c"
    break;

  case 51:
#line 212 "parser.y"
                                                                 { (yyval.node) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                 }
#line 2009 "parser.tab.c"
    break;

  case 52:
#line 217 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ForK, (yyvsp[-5].tokenData));
                                                                   (yyval.node)->child[0] = newDeclNode(VarK, (yyvsp[-4].tokenData));
                                                                   (yyval.node)->child[0]->expType = Integer;
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                   
                                                                 }
#line 2022 "parser.tab.c"
    break;

  case 53:
#line 225 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2028 "parser.tab.c"
    break;

  case 54:
#line 226 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2034 "parser.tab.c"
    break;

  case 55:
#line 227 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2040 "parser.tab.c"
    break;

  case 56:
#line 228 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2046 "parser.tab.c"
    break;

  case 57:
#line 229 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2052 "parser.tab.c"
    break;

  case 58:
#line 230 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2058 "parser.tab.c"
    break;

  case 59:
#line 231 "parser.y"
                                                                { (yyval.node) = NULL; }
#line 2064 "parser.tab.c"
    break;

  case 60:
#line 234 "parser.y"
                                                                 { (yyval.node) = newStmtNode(IfK, (yyvsp[-5].tokenData)); 
                                                                   (yyval.node)->child[0] = (yyvsp[-4].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node); 
                                                                 }
#line 2074 "parser.tab.c"
    break;

  case 61:
#line 239 "parser.y"
                                                                 { (yyval.node) = newStmtNode(IfK, (yyvsp[-3].tokenData));              
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node); 
                                                                 }
#line 2083 "parser.tab.c"
    break;

  case 62:
#line 243 "parser.y"
                                                                 { (yyval.node) = newStmtNode(WhileK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                 }
#line 2093 "parser.tab.c"
    break;

  case 63:
#line 248 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ForK, (yyvsp[-5].tokenData));
                                                                   (yyval.node)->child[0] = newDeclNode(VarK, (yyvsp[-4].tokenData));
                                                                   (yyval.node)->child[0]->expType = Integer;
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                   
                                                                 }
#line 2106 "parser.tab.c"
    break;

  case 64:
#line 256 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2112 "parser.tab.c"
    break;

  case 65:
#line 257 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2118 "parser.tab.c"
    break;

  case 66:
#line 260 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); }
#line 2124 "parser.tab.c"
    break;

  case 67:
#line 261 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2130 "parser.tab.c"
    break;

  case 68:
#line 262 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2136 "parser.tab.c"
    break;

  case 69:
#line 265 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2142 "parser.tab.c"
    break;

  case 70:
#line 266 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2148 "parser.tab.c"
    break;

  case 71:
#line 267 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2154 "parser.tab.c"
    break;

  case 72:
#line 268 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2160 "parser.tab.c"
    break;

  case 73:
#line 273 "parser.y"
                                                                 { (yyval.node) = newStmtNode(CompoundK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-1].node);
                                                                   yyerrok;
                                                                 }
#line 2170 "parser.tab.c"
    break;

  case 74:
#line 281 "parser.y"
                                                              { (yyval.node) = addSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2176 "parser.tab.c"
    break;

  case 75:
#line 282 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2182 "parser.tab.c"
    break;

  case 76:
#line 285 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 2188 "parser.tab.c"
    break;

  case 77:
#line 286 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2194 "parser.tab.c"
    break;

  case 78:
#line 289 "parser.y"
                                                                 { (yyval.node) = newStmtNode(RangeK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2203 "parser.tab.c"
    break;

  case 79:
#line 293 "parser.y"
                                                                 { (yyval.node) = newStmtNode(RangeK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-4].node);
                                                                   (yyval.node)->child[1] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[2] = (yyvsp[0].node);
                                                                 }
#line 2213 "parser.tab.c"
    break;

  case 80:
#line 298 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2219 "parser.tab.c"
    break;

  case 81:
#line 299 "parser.y"
                                                                { (yyval.node) = NULL; yyerrok;}
#line 2225 "parser.tab.c"
    break;

  case 82:
#line 300 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2231 "parser.tab.c"
    break;

  case 83:
#line 303 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ReturnK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                 }
#line 2239 "parser.tab.c"
    break;

  case 84:
#line 306 "parser.y"
                                                                 { (yyval.node) = newStmtNode(ReturnK, (yyvsp[-2].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = (yyvsp[-1].node)->expType;
                                                                   yyerrok;
                                                                 }
#line 2250 "parser.tab.c"
    break;

  case 85:
#line 312 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2256 "parser.tab.c"
    break;

  case 86:
#line 316 "parser.y"
                                                                 { (yyval.node) = newStmtNode(BreakK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                 }
#line 2264 "parser.tab.c"
    break;

  case 87:
#line 321 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2273 "parser.tab.c"
    break;

  case 88:
#line 325 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2282 "parser.tab.c"
    break;

  case 89:
#line 329 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2291 "parser.tab.c"
    break;

  case 90:
#line 333 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2300 "parser.tab.c"
    break;

  case 91:
#line 337 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2309 "parser.tab.c"
    break;

  case 92:
#line 343 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2318 "parser.tab.c"
    break;

  case 93:
#line 348 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2324 "parser.tab.c"
    break;

  case 94:
#line 350 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2334 "parser.tab.c"
    break;

  case 95:
#line 355 "parser.y"
                                                                 { (yyval.node) = newExpNode(AssignK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2344 "parser.tab.c"
    break;

  case 96:
#line 360 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2350 "parser.tab.c"
    break;

  case 97:
#line 361 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2356 "parser.tab.c"
    break;

  case 98:
#line 362 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2362 "parser.tab.c"
    break;

  case 99:
#line 363 "parser.y"
                                                                 { (yyval.node) = NULL; yyerrok;}
#line 2368 "parser.tab.c"
    break;

  case 100:
#line 366 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2379 "parser.tab.c"
    break;

  case 101:
#line 372 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2385 "parser.tab.c"
    break;

  case 102:
#line 373 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2391 "parser.tab.c"
    break;

  case 103:
#line 376 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2402 "parser.tab.c"
    break;

  case 104:
#line 382 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2408 "parser.tab.c"
    break;

  case 105:
#line 383 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2414 "parser.tab.c"
    break;

  case 106:
#line 386 "parser.y"
                                                                    { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2423 "parser.tab.c"
    break;

  case 107:
#line 390 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2429 "parser.tab.c"
    break;

  case 108:
#line 391 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2435 "parser.tab.c"
    break;

  case 109:
#line 394 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-1].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[0].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-1].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2445 "parser.tab.c"
    break;

  case 110:
#line 399 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2451 "parser.tab.c"
    break;

  case 111:
#line 400 "parser.y"
                                                                { (yyval.node) = NULL;}
#line 2457 "parser.tab.c"
    break;

  case 112:
#line 403 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2466 "parser.tab.c"
    break;

  case 113:
#line 407 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2475 "parser.tab.c"
    break;

  case 114:
#line 412 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2484 "parser.tab.c"
    break;

  case 115:
#line 416 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2493 "parser.tab.c"
    break;

  case 116:
#line 421 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2502 "parser.tab.c"
    break;

  case 117:
#line 425 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Boolean;
                                                                 }
#line 2511 "parser.tab.c"
    break;

  case 118:
#line 431 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2520 "parser.tab.c"
    break;

  case 119:
#line 435 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2526 "parser.tab.c"
    break;

  case 120:
#line 436 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2532 "parser.tab.c"
    break;

  case 121:
#line 439 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2541 "parser.tab.c"
    break;

  case 122:
#line 443 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2550 "parser.tab.c"
    break;

  case 123:
#line 449 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[-2].node);
                                                                   (yyval.node)->child[1] = (yyvsp[0].node);
                                                                 }
#line 2559 "parser.tab.c"
    break;

  case 124:
#line 453 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2565 "parser.tab.c"
    break;

  case 125:
#line 454 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2571 "parser.tab.c"
    break;

  case 126:
#line 457 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2580 "parser.tab.c"
    break;

  case 127:
#line 461 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2589 "parser.tab.c"
    break;

  case 128:
#line 465 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2598 "parser.tab.c"
    break;

  case 129:
#line 471 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); 
                                                                   (yyval.node)->child[0] = (yyvsp[0].node);
                                                                 }
#line 2606 "parser.tab.c"
    break;

  case 130:
#line 474 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2612 "parser.tab.c"
    break;

  case 131:
#line 475 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2618 "parser.tab.c"
    break;

  case 132:
#line 478 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2627 "parser.tab.c"
    break;

  case 133:
#line 482 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2636 "parser.tab.c"
    break;

  case 134:
#line 486 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2645 "parser.tab.c"
    break;

  case 135:
#line 492 "parser.y"
                                                                 { (yyval.node) = newExpNode(IdK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;    
                                                                 }
#line 2653 "parser.tab.c"
    break;

  case 136:
#line 495 "parser.y"
                                                                 { (yyval.node) = newExpNode(OpK, (yyvsp[-2].tokenData));  
                                                                  (yyval.node)->child[0] = newExpNode(IdK, (yyvsp[-3].tokenData));
                                                                  (yyval.node)->child[0]->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                  (yyval.node)->child[0]->isArray = true;
                                                                  (yyval.node)->child[1] = (yyvsp[-1].node); 
                                                                  (yyval.node)->attr.name = (yyvsp[-2].tokenData)->tokenstr;
                                                                 }
#line 2665 "parser.tab.c"
    break;

  case 137:
#line 504 "parser.y"
                                                                 { (yyval.node) = (yyvsp[-1].node); yyerrok; }
#line 2671 "parser.tab.c"
    break;

  case 138:
#line 505 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2677 "parser.tab.c"
    break;

  case 139:
#line 506 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2683 "parser.tab.c"
    break;

  case 140:
#line 507 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2689 "parser.tab.c"
    break;

  case 141:
#line 510 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2695 "parser.tab.c"
    break;

  case 142:
#line 511 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2701 "parser.tab.c"
    break;

  case 143:
#line 515 "parser.y"
                                                                 { (yyval.node) = newExpNode(CallK, (yyvsp[-3].tokenData));
                                                                   (yyval.node)->child[0] = (yyvsp[-1].node);
                                                                   (yyval.node)->attr.name = (yyvsp[-3].tokenData)->tokenstr;
                                                                 }
#line 2710 "parser.tab.c"
    break;

  case 144:
#line 519 "parser.y"
                                                               { (yyval.node) = NULL; yyerrok; }
#line 2716 "parser.tab.c"
    break;

  case 145:
#line 522 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2722 "parser.tab.c"
    break;

  case 146:
#line 523 "parser.y"
                                                                 { (yyval.node) = NULL; }
#line 2728 "parser.tab.c"
    break;

  case 147:
#line 526 "parser.y"
                                                                 { (yyval.node) = addSibling((yyvsp[-2].node), (yyvsp[0].node)); yyerrok; }
#line 2734 "parser.tab.c"
    break;

  case 148:
#line 527 "parser.y"
                                                                 { (yyval.node) = (yyvsp[0].node); }
#line 2740 "parser.tab.c"
    break;

  case 149:
#line 528 "parser.y"
                                                                 { (yyval.node) = NULL;}
#line 2746 "parser.tab.c"
    break;

  case 150:
#line 530 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.value = (yyvsp[0].tokenData)->nvalue; 
                                                                   (yyval.node)->expType = Integer;
                                                                 }
#line 2755 "parser.tab.c"
    break;

  case 151:
#line 534 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   (yyval.node)->thisTokenData = (yyvsp[0].tokenData); 
                                                                   (yyval.node)->expType = Char;
                                                                 }
#line 2765 "parser.tab.c"
    break;

  case 152:
#line 539 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.value = (yyvsp[0].tokenData)->nvalue; 
                                                                   (yyval.node)->expType = Boolean;
                                                                   (yyval.node)->attr.name = (yyvsp[0].tokenData)->tokenstr;
                                                                   
                                                                 }
#line 2776 "parser.tab.c"
    break;

  case 153:
#line 545 "parser.y"
                                                                 { (yyval.node) = newExpNode(ConstantK, (yyvsp[0].tokenData));
                                                                   (yyval.node)->attr.string = (yyvsp[0].tokenData)->stringvalue;
                                                                   (yyval.node)->isArray = true;
                                                                   (yyval.node)->expType = CharInt;
                                                                   (yyval.node)->arraySize = (yyvsp[0].tokenData)->strlength;
                                                                 }
#line 2787 "parser.tab.c"
    break;


#line 2791 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

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
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
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
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 552 "parser.y"


extern int yydebug;
int main(int argc, char *argv[])
{
  int compilerFlag = 0;
  bool isPrintingAST = 0;
  numErrors = 0;
  numWarnings = 0;
  bool isGeneratingCode = true;
  int optionNumber; 
  extern int optind; 

  while((compilerFlag = getopt(argc, argv, "dDpPhM")) != -1)
  {

    switch(compilerFlag)
    {

        case 'p':
            {
              isPrintingAST = true;
              isPrintingTreeTypes = false;
              isGeneratingCode = false;
              optionNumber = 0; 
            }
            break;
    
        case 'P':
              {
                isPrintingAST = true;
                isPrintingTreeTypes = true;
                isGeneratingCode = false;
                optionNumber = 1;
              }
              break;

        case 'd':
              {
                yydebug = 1;
              }
              break;           
        
        case 'D':
              {
                symbolTable.debug(1);
              }  
              break;

        case 'M':
              {
                isPrintingAST = true;
                isPrintingTreeTypes = true;
                isPrintingMemoryOffset = true;
                isPrintingMemorySize = true;
                isOnlyPrintingMemoryInfo = true;
                isGeneratingCode = false;
                optionNumber = 1;
              }
              break; 

        case 'h':
              {
                std::cout << "usage: c- [options] [sourcefile]" << std::endl;
                std::cout << "options:" << std::endl;
                std::cout << "-d     - turn on parser debugging" << std::endl;
                std::cout << "-D     - turn on symbol table debugging" << std::endl;
                std::cout << "-h     - print this usage message" << std::endl;
                std::cout << "-p     - print the abstract syntax tree" << std::endl;
                std::cout << "-P     - print the abstract syntax tree plus type information" << std::endl;
                std::cout << "-M     - print the abstract syntax tree plus type information and memory offsets" << std::endl;
              }
              break;

        default:
              {
                exit(1);
              }
    }
  }

  if(isGeneratingCode == true)
  {
    optionNumber = 1;
    isPrintingMemorySize = true;
    isPrintingTreeTypes = true;
    isOnlyPrintingMemoryInfo = false;
  }
  
  
  std::string fileName = argv[argc-1];
  
  if(argc >1 && !(yyin = fopen(fileName.c_str(), "r")))
  {
    // failed to open file
    std::cout << "ERROR(ARGLIST): source file \"" << argv[1] << "\" could not be opened." << std::endl;
    numErrors++;
    std::cout << "Number of warnings: " << numWarnings << std::endl;
    std::cout << "Number of errors: " << numErrors << std::endl;
    exit(1);
  }

  initErrorProcessing(); 

  // remove line 623 before submission. Just For testing
  /* std::cout << "====================================" << std::endl; */
  yyparse();


  if(isPrintingAST && optionNumber == 0 && numErrors == 0 && ROOT != NULL)
  {
    printAST(ROOT, 0, isPrintingTreeTypes);
  }
  else if(optionNumber == 1 && numErrors == 0 && ROOT != NULL)
  {
    initializeIO();
    semanticAnalysis(ROOT, numErrors, numWarnings);

    if(numErrors < 1 && isOnlyPrintingMemoryInfo)
    {  
      printAST(ROOT, 0, isPrintingTreeTypes);
    }
  }

  //code generation
  if(numErrors == 0) // if there are no errors
  {
    
    char* tmOutputFile = (char*)malloc(strlen(argv[optind]) + 1);
    int tmOutputFileLength = strlen(argv[optind]);

    strcpy(tmOutputFile, argv[optind]);
    tmOutputFile[tmOutputFileLength - 2] = 't';
    tmOutputFile[tmOutputFileLength - 1] = 'm';
    
    generateCode(ROOT, tmOutputFile);

  }

  
  // remove line 644 before submission. Just For testing
  /* std::cout << "FILE: " << fileName.substr(fileName.find_last_of("/\\") + 1) << std::endl; */
  if(isPrintingMemoryOffset)
  {
    // print memory offsets
    std:: cout << "Offset for end of global space: " << globalOffset << std::endl;
  }
  std::cout << "Number of warnings: " << numWarnings << std::endl;
  std::cout << "Number of errors: " << numErrors << std::endl;

  return 0;
}
