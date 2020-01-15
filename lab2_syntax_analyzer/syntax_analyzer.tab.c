/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "syntax_analyzer.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./common/common.h"
#include "./syntax_tree/SyntaxTree.h"


#include "./lab1_lexical_analyzer/lexical_analyzer.h"

/*
%code requires{
	#include "./syntax_tree/SyntaxTree.h"
}*/

// external functions from lex
extern int yylex();
extern int yyparse();
extern int yyrestart();
extern FILE * yyin;
//extern YYSTYPE yylval;

// external variables from lexical_analyzer module
extern int lines;
extern int pos_start;
extern int pos_end;
extern char * yytext;
//int tempo_value; no need to get the return value

// Global syntax tree.

struct _SyntaxTree * gt;
//SyntaxTree *gt;
struct _SyntaxTreeNode *tempo;
//SyntaxTreeNode *tempo;

void yyerror(const char * s);

#line 106 "syntax_analyzer.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ERROR = 258,
    ADD = 259,
    SUB = 260,
    MUL = 261,
    DIV = 262,
    LT = 263,
    LTE = 264,
    GT = 265,
    GTE = 266,
    EQ = 267,
    NEQ = 268,
    ASSIGN = 269,
    SEMICOLON = 270,
    COMMA = 271,
    LPARENTHESE = 272,
    RPARENTHESE = 273,
    LBRACKET = 274,
    RBRACKET = 275,
    LBRACE = 276,
    RBRACE = 277,
    ELSE = 278,
    IF = 279,
    INT = 280,
    RETURN = 281,
    VOID = 282,
    WHILE = 283,
    ARRAY = 284,
    EOL = 285,
    COMMENT = 286,
    BLANK = 287,
    LETTER = 288,
    IDENTIFIER = 289,
    NUMBER = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 41 "syntax_analyzer.y" /* yacc.c:355  */

    int num;
    char name[100];
    struct _SyntaxTreeNode *node;
    //SyntaxTreeNode *node;
/********** TODO: Fill in this union structure *********/

#line 187 "syntax_analyzer.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 204 "syntax_analyzer.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   101

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  101

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      35
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   104,   104,   113,   121,   127,   132,   138,   146,   163,
     171,   176,   197,   203,   208,   220,   226,   238,   250,   264,
     272,   277,   285,   290,   295,   300,   305,   310,   315,   323,
     328,   345,   368,   385,   393,   401,   412,   417,   423,   437,
     448,   453,   458,   463,   468,   473,   478,   483,   494,   499,
     504,   509,   520,   525,   530,   535,   546,   551,   556,   561,
     575,   580,   585,   596
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ERROR", "ADD", "SUB", "MUL", "DIV",
  "LT", "LTE", "GT", "GTE", "EQ", "NEQ", "ASSIGN", "SEMICOLON", "COMMA",
  "LPARENTHESE", "RPARENTHESE", "LBRACKET", "RBRACKET", "LBRACE", "RBRACE",
  "ELSE", "IF", "INT", "RETURN", "VOID", "WHILE", "ARRAY", "EOL",
  "COMMENT", "BLANK", "LETTER", "IDENTIFIER", "NUMBER", "$accept",
  "program", "declaration-list", "declaration", "var-declaration",
  "type-specifier", "fun-declaration", "params", "params-list", "param",
  "compound-stmt", "local-declarations", "statement-list", "statement",
  "experssion-stmt", "selection-stmt", "iteration-stmt", "return-stmt",
  "expression", "var", "simple-expression", "relop", "additive-expression",
  "addop", "term", "mulop", "factor", "call", "args", "arg-list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290
};
# endif

#define YYPACT_NINF -86

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-86)))

#define YYTABLE_NINF -14

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -23,   -86,   -86,     9,   -23,   -86,   -86,   -11,   -86,   -86,
     -86,    -7,   -86,    16,    -3,    19,    11,    31,    38,   -86,
      51,    43,    52,   -23,    59,   -86,   -86,   -86,   -86,   -86,
     -23,   -86,    41,    12,    20,   -86,   -16,   -86,    60,    -4,
      61,    33,   -86,   -86,   -86,   -86,   -86,   -86,   -86,    64,
      62,   -86,    55,    50,   -86,   -86,    63,   -16,   -86,    67,
     -16,   -16,   -16,   -86,   -16,   -86,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,   -16,   -16,   -86,   -86,   -16,   -86,    66,
     -86,    68,   -86,    69,    72,    70,   -86,   -86,    65,    50,
     -86,    27,    27,   -86,   -16,   -86,    57,   -86,   -86,    27,
     -86
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     9,    10,     0,     2,     4,     5,     0,     6,     1,
       3,     0,     7,     0,     0,    10,     0,     0,    12,    15,
       0,    16,     0,     0,     0,    17,    20,    11,    14,     8,
      22,    19,     0,     0,     0,    29,     0,    18,     0,     0,
       0,    37,    58,    24,    21,    23,    25,    26,    27,     0,
      56,    36,    40,    48,    52,    57,     0,     0,    33,     0,
       0,    61,     0,    28,     0,    49,    50,    42,    41,    43,
      44,    45,    46,     0,     0,    53,    54,     0,    55,     0,
      34,     0,    63,     0,    60,     0,    35,    56,    39,    47,
      51,     0,     0,    59,     0,    38,    30,    32,    62,     0,
      31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   -86,   -86,    79,    71,    -8,   -86,   -86,   -86,    73,
      75,   -86,   -86,   -85,   -86,   -86,   -86,   -86,   -36,   -57,
     -86,   -86,    18,   -86,    15,   -86,     8,   -86,   -86,   -86
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,     8,    17,    18,    19,
      43,    30,    33,    44,    45,    46,    47,    48,    49,    50,
      51,    73,    52,    74,    53,    77,    54,    55,    83,    84
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      56,    36,     1,    59,     2,    16,    96,    97,    12,     9,
      13,    58,    14,    36,   100,    16,    87,    87,    41,    42,
      87,    79,    32,    11,    81,    82,    85,    35,    86,    36,
      41,    42,    20,    26,    37,    12,    38,   -13,    39,    14,
      40,     1,    35,    15,    36,    21,    41,    42,    26,    22,
      61,    38,    62,    39,    23,    40,    75,    76,    98,    65,
      66,    41,    42,    67,    68,    69,    70,    71,    72,    65,
      66,    24,    25,    26,    29,    34,    64,    57,    60,    63,
      99,    78,    80,    10,    91,    90,    92,    93,    94,    89,
      95,    88,     0,     0,     0,     0,    28,    27,     0,     0,
       0,    31
};

static const yytype_int8 yycheck[] =
{
      36,    17,    25,    39,    27,    13,    91,    92,    15,     0,
      17,    15,    19,    17,    99,    23,    73,    74,    34,    35,
      77,    57,    30,    34,    60,    61,    62,    15,    64,    17,
      34,    35,    35,    21,    22,    15,    24,    18,    26,    19,
      28,    25,    15,    27,    17,    34,    34,    35,    21,    18,
      17,    24,    19,    26,    16,    28,     6,     7,    94,     4,
       5,    34,    35,     8,     9,    10,    11,    12,    13,     4,
       5,    20,    29,    21,    15,    34,    14,    17,    17,    15,
      23,    18,    15,     4,    18,    77,    18,    18,    16,    74,
      20,    73,    -1,    -1,    -1,    -1,    23,    22,    -1,    -1,
      -1,    30
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    27,    37,    38,    39,    40,    41,    42,     0,
      39,    34,    15,    17,    19,    27,    41,    43,    44,    45,
      35,    34,    18,    16,    20,    29,    21,    46,    45,    15,
      47,    40,    41,    48,    34,    15,    17,    22,    24,    26,
      28,    34,    35,    46,    49,    50,    51,    52,    53,    54,
      55,    56,    58,    60,    62,    63,    54,    17,    15,    54,
      17,    17,    19,    15,    14,     4,     5,     8,     9,    10,
      11,    12,    13,    57,    59,     6,     7,    61,    18,    54,
      15,    54,    54,    64,    65,    54,    54,    55,    58,    60,
      62,    18,    18,    18,    16,    20,    49,    49,    54,    23,
      49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    36,    37,    38,    38,    39,    39,    40,    40,    41,
      41,    42,    43,    43,    44,    44,    45,    45,    46,    47,
      47,    48,    48,    49,    49,    49,    49,    49,    50,    50,
      51,    51,    52,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    57,    57,    57,    58,    58,    59,
      59,    60,    60,    61,    61,    62,    62,    62,    62,    63,
      64,    64,    65,    65
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     6,     1,
       1,     6,     1,     1,     3,     1,     2,     3,     4,     2,
       0,     2,     0,     1,     1,     1,     1,     1,     2,     1,
       5,     7,     5,     2,     3,     3,     1,     1,     4,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 104 "syntax_analyzer.y" /* yacc.c:1646  */
    {
						(yyval.node) = newSyntaxTreeNode("program");
						(yyval.node)->children_num= 0;
						//gt = newSyntaxTree();
						gt->root = (yyval.node);
						(yyvsp[0].node) = newSyntaxTreeNode("declaration-list");
						(yyvsp[0].node)->children_num = 0;
						SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
						}
#line 1365 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 113 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-1].node) = newSyntaxTreeNode("declaration-list");
	(yyvsp[-1].node)->children_num = 0;
	(yyvsp[0].node) = newSyntaxTreeNode("declaration");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1378 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 121 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					(yyvsp[0].node) = newSyntaxTreeNode("declaration");
					(yyvsp[0].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
				}
#line 1388 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 127 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[0].node) = newSyntaxTreeNode("var-declaration");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1398 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 132 "syntax_analyzer.y" /* yacc.c:1646  */
    {
				(yyvsp[0].node) = newSyntaxTreeNode("fun-declaration");
				(yyvsp[0].node)->children_num = 0;
				SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
			}
#line 1408 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 138 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-2].node) = newSyntaxTreeNode("type-specifier");
	(yyvsp[-2].node)->children_num = 0;
	tempo = newSyntaxTreeNode((yyvsp[-1].name));
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1421 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 146 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					(yyvsp[-5].node) = newSyntaxTreeNode("type-specifier");
					(yyvsp[-5].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-5].node));
					tempo = newSyntaxTreeNode((yyvsp[-4].name));
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					tempo = newSyntaxTreeNode("[");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					tempo = newSyntaxTreeNodeFromNum((yyvsp[-2].num));
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					tempo = newSyntaxTreeNode("]");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
				}
#line 1443 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 163 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("int");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	printf("!!Meet int\n");
	printf("Tempo-name:%s\n", tempo->name);
	//printf("Temporary ok\n");
}
#line 1456 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 171 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					tempo = newSyntaxTreeNode("void");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
				}
#line 1466 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 176 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-5].node) = newSyntaxTreeNode("type-specifier");
	(yyvsp[-5].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-5].node));
	tempo = newSyntaxTreeNode((yyvsp[-4].name));
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	tempo = newSyntaxTreeNode("(");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[-2].node) = newSyntaxTreeNode("params");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	tempo = newSyntaxTreeNode(")");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[0].node) = newSyntaxTreeNode("compound-stmt");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
	printf("!!Meet fun-declaration\n");
}
#line 1492 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 197 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[0].node) = newSyntaxTreeNode("params-list");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
	printf("!!Meet params\n");
}
#line 1503 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 203 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					tempo = newSyntaxTreeNode("void");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
				}
#line 1513 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 208 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-2].node) = newSyntaxTreeNode("params-list");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	tempo = newSyntaxTreeNode(",");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[0].node) = newSyntaxTreeNode("param");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
	printf("!!Meet params-list\n");
}
#line 1530 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 220 "syntax_analyzer.y" /* yacc.c:1646  */
    {
				(yyvsp[0].node) = newSyntaxTreeNode("param");
				(yyvsp[0].node)->children_num = 0;
				SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
				printf("!!Meet params-list\n");
			}
#line 1541 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 226 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-1].node) = newSyntaxTreeNode("type-specifier");
	(yyvsp[-1].node)->children_num = 0;
	printf("param-name:%s, %d\n", (yyvsp[-1].node)->name, (yyvsp[-1].node)->children_num);
	printf("INPUT OK\n");
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	printf("ADD OK\n");
	tempo = newSyntaxTreeNode((yyvsp[0].name));
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	printf("!!Meet param1\n");
}
#line 1558 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 238 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					(yyvsp[-2].node) = newSyntaxTreeNode("type-specifier");
					(yyvsp[-2].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
					tempo = newSyntaxTreeNode((yyvsp[-1].name));
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					tempo = newSyntaxTreeNode("[]");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					printf("!!Meet param2\n");
				}
#line 1575 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 250 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("{");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[-2].node) = newSyntaxTreeNode("local-declarations");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	(yyvsp[-1].node) = newSyntaxTreeNode("statement-list");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	tempo = newSyntaxTreeNode("}");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1594 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 264 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-1].node) = newSyntaxTreeNode("local-declarations");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	(yyvsp[0].node) = newSyntaxTreeNode("var-declaration");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1607 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 272 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("epsilon");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1617 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 277 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-1].node) = newSyntaxTreeNode("statement-list");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	(yyvsp[0].node) = newSyntaxTreeNode("statement");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1630 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 285 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("epsilon");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1640 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 290 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[0].node) = newSyntaxTreeNode("experssion-stmt");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1650 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 295 "syntax_analyzer.y" /* yacc.c:1646  */
    {
			(yyvsp[0].node) = newSyntaxTreeNode("compound-stmt");
			(yyvsp[0].node)->children_num = 0;
			SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
		}
#line 1660 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 300 "syntax_analyzer.y" /* yacc.c:1646  */
    {
			(yyvsp[0].node) = newSyntaxTreeNode("selection-stmt");
			(yyvsp[0].node)->children_num = 0;
			SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
		}
#line 1670 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 305 "syntax_analyzer.y" /* yacc.c:1646  */
    {
			(yyvsp[0].node) = newSyntaxTreeNode("iteration-stmt");
			(yyvsp[0].node)->children_num = 0;
			SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
		}
#line 1680 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 310 "syntax_analyzer.y" /* yacc.c:1646  */
    {
			(yyvsp[0].node) = newSyntaxTreeNode("return-stmt");
			(yyvsp[0].node)->children_num = 0;
			SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
		}
#line 1690 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 315 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-1].node) = newSyntaxTreeNode("expression");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	tempo = newSyntaxTreeNode(";");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1703 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 323 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					tempo = newSyntaxTreeNode(";");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
				}
#line 1713 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 328 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("if");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	tempo = newSyntaxTreeNode("(");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[-2].node) = newSyntaxTreeNode("expression");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	tempo = newSyntaxTreeNode(")");	
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[0].node) = newSyntaxTreeNode("statement");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1735 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 345 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					tempo = newSyntaxTreeNode("if");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					tempo = newSyntaxTreeNode("(");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					(yyvsp[-4].node) = newSyntaxTreeNode("expression");
					(yyvsp[-4].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-4].node));
					tempo = newSyntaxTreeNode(")");	
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					(yyvsp[-2].node) = newSyntaxTreeNode("statement");
					(yyvsp[-2].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
					tempo = newSyntaxTreeNode("else");	
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					(yyvsp[0].node) = newSyntaxTreeNode("statement");
					(yyvsp[0].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
				}
#line 1763 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 368 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("while");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	tempo = newSyntaxTreeNode("(");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[-2].node) = newSyntaxTreeNode("expression");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	tempo = newSyntaxTreeNode(")");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[0].node) = newSyntaxTreeNode("statement");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1785 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 385 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("return");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	tempo = newSyntaxTreeNode(";");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1798 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 393 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					tempo = newSyntaxTreeNode("return");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
					(yyvsp[-1].node) = newSyntaxTreeNode("expression");
					(yyvsp[-1].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
				}
#line 1811 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 401 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-2].node) = newSyntaxTreeNode("var");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	tempo = newSyntaxTreeNode("=");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[0].node) = newSyntaxTreeNode("expression");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1827 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 412 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					tempo = newSyntaxTreeNode("simple-expression");
					tempo->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), tempo);
				}
#line 1837 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 417 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode((yyvsp[0].name));
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	printf("!!Meet IDENTIFIER\n");
}
#line 1848 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 423 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode((yyvsp[-3].name));
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
		tempo = newSyntaxTreeNode("[");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
		(yyvsp[-1].node) = newSyntaxTreeNode("expression");
		(yyvsp[-1].node)->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
		tempo = newSyntaxTreeNode("]");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 1867 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 437 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-2].node) = newSyntaxTreeNode("additive-expression");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	(yyvsp[-1].node) = newSyntaxTreeNode("relop");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	(yyvsp[0].node) = newSyntaxTreeNode("additive-expression");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1883 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 448 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					(yyvsp[0].node) = newSyntaxTreeNode("additive-expression");
					(yyvsp[0].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
				}
#line 1893 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 453 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("<=");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1903 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 458 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode("<");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 1913 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 463 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode(">");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 1923 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 468 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode(">=");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 1933 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 473 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode("==");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 1943 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 478 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode("!=");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 1953 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 483 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-2].node) = newSyntaxTreeNode("additive-expression");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	(yyvsp[-1].node) = newSyntaxTreeNode("addop");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	(yyvsp[0].node) = newSyntaxTreeNode("term");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 1969 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 494 "syntax_analyzer.y" /* yacc.c:1646  */
    {
					(yyvsp[0].node) = newSyntaxTreeNode("term");
					(yyvsp[0].node)->children_num = 0;
					SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
				}
#line 1979 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 499 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("+");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 1989 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 504 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode("-");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 1999 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 509 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-2].node) = newSyntaxTreeNode("term");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));	
	(yyvsp[-1].node) = newSyntaxTreeNode("mulop");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	(yyvsp[0].node) = newSyntaxTreeNode("factor");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 2015 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 520 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		(yyvsp[0].node) = newSyntaxTreeNode("factor");
		(yyvsp[0].node)->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
	}
#line 2025 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 525 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("*");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 2035 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 530 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNode("/");
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 2045 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 535 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("(");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[-1].node) = newSyntaxTreeNode("expression");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	tempo = newSyntaxTreeNode(")");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 2061 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 546 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		(yyvsp[0].node) = newSyntaxTreeNode("var");
		(yyvsp[0].node)->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
	}
#line 2071 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 551 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		(yyvsp[0].node) = newSyntaxTreeNode("call");
		(yyvsp[0].node)->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
	}
#line 2081 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 556 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		tempo = newSyntaxTreeNodeFromNum((yyvsp[0].num));
		tempo->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), tempo);
	}
#line 2091 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 561 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode((yyvsp[-3].name));
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	tempo = newSyntaxTreeNode("(");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[-1].node) = newSyntaxTreeNode("args");
	(yyvsp[-1].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-1].node));
	tempo = newSyntaxTreeNode(")");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 2110 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 575 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[0].node) = newSyntaxTreeNode("arg-list");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 2120 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 580 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	tempo = newSyntaxTreeNode("epsilon");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
}
#line 2130 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 585 "syntax_analyzer.y" /* yacc.c:1646  */
    {
	(yyvsp[-2].node) = newSyntaxTreeNode("arg-list");
	(yyvsp[-2].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[-2].node));
	tempo = newSyntaxTreeNode(",");
	tempo->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), tempo);
	(yyvsp[0].node) = newSyntaxTreeNode("expression");
	(yyvsp[0].node)->children_num = 0;
	SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
}
#line 2146 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 596 "syntax_analyzer.y" /* yacc.c:1646  */
    {
		(yyvsp[0].node) = newSyntaxTreeNode("expression");
		(yyvsp[0].node)->children_num = 0;
		SyntaxTreeNode_AddChild((yyval.node), (yyvsp[0].node));
	}
#line 2156 "syntax_analyzer.tab.c" /* yacc.c:1646  */
    break;


#line 2160 "syntax_analyzer.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 601 "syntax_analyzer.y" /* yacc.c:1906  */


void yyerror(const char * s)
{
	// TODO: variables in Lab1 updates only in analyze() function in lexical_analyzer.l
	//       You need to move position updates to show error output below
	//yytext = yyval;
	//printf("ERRORS %s happend at:%d about <%s>\n", s, lines, yytext);
	//printf("tempo message:<%s> %d\n", tempo->name, tempo->children_num);
	fprintf(stderr, "%s:%d %d %d syntax error for %s\n", s, lines,pos_start,pos_end, yytext);
}

/// \brief Syntax analysis from input file to output file
///
/// \param input basename of input file
/// \param output basename of output file
void syntax(const char * input, const char * output)
{
	gt = newSyntaxTree();

	char inputpath[256] = "./testcase/";
	char outputpath[256] = "./syntree/";
	strcat(inputpath, input);
	strcat(outputpath, output);

	if (!(yyin = fopen(inputpath, "r"))) {
		fprintf(stderr, "[ERR] Open input file %s failed.", inputpath);
		exit(1);
	}
	yyrestart(yyin);
	printf("[START]: Syntax analysis start for %s\n", input);
	FILE * fp = fopen(outputpath, "w+");
	if (!fp)	return;

	// yyerror() is invoked when yyparse fail. If you still want to check the return value, it's OK.
	// `while (!feof(yyin))` is not needed here. We only analyze once.
	yyparse();

	printf("[OUTPUT] Printing tree to output file %s\n", outputpath);
	printf("OK now\n");
	printSyntaxTree(fp, gt);
	printf("OK1\n");
	deleteSyntaxTree(gt);
	printf("OK2\n");
	gt = 0;

	fclose(fp);
	printf("[END] Syntax analysis end for %s\n", input);
}

/// \brief starting function for testing syntax module.
///
/// Invoked in test_syntax.c
int syntax_main(int argc, char ** argv)
{
	char filename[10][256];
	char output_file_name[256];
	const char suffix[256] = ".syntax_tree";
	int fn = getAllTestcase(filename);
	//printf("file_count:%d\n", fn);
	for (int i = 0; i < fn; i++) {
			lines = 1;
			int name_len = strstr(filename[i], ".cminus") - filename[i];
			strncpy(output_file_name, filename[i], name_len);
			strcpy(output_file_name+name_len, suffix);
			syntax(filename[i], output_file_name);
	}
	return 0;
}
