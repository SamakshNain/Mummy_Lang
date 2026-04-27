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
#line 1 "mummy.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern FILE *yyin;
int yylex();
void yyerror(const char *s);

/* ---------- TAC NODE ---------- */
struct node {
    char code[1000][100];
    int size;
    char place[20];
};

/* ---------- HELPERS ---------- */
struct node* newNode() {
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->size = 0;
    return n;
}

void addLine(struct node* n, char* line) {
    strcpy(n->code[n->size++], line);
}

void merge(struct node* a, struct node* b) {
    for(int i=0;i<b->size;i++)
        strcpy(a->code[a->size++], b->code[i]);
}

/* ---------- TEMP & LABEL ---------- */
int tempCount = 0, labelCount = 0;

char* newTemp() {
    char buf[20];
    sprintf(buf,"t%d",tempCount++);
    return strdup(buf);
}

char* newLabel() {
    char buf[20];
    sprintf(buf,"L%d",labelCount++);
    return strdup(buf);
}

/* ---------- GLOBAL TAC ---------- */
char globalCode[1000][100];
int globalSize = 0;

void storeCode(struct node* n) {
    for(int i=0;i<n->size;i++)
        strcpy(globalCode[globalSize++], n->code[i]);
}

void printTAC() {
    printf("\n--- THREE ADDRESS CODE ---\n");
    for(int i=0;i<globalSize;i++)
        printf("%s\n", globalCode[i]);
}

/* ---------- INTERPRETER ---------- */
int vars[100];
char names[100][20];
int varCount = 0;

int getVarIndex(char* name) {
    for(int i=0;i<varCount;i++)
        if(strcmp(names[i],name)==0) return i;

    strcpy(names[varCount],name);
    return varCount++;
}

int getValue(char* x) {
    if(isdigit(x[0])) return atoi(x);
    return vars[getVarIndex(x)];
}

void executeTAC() {
    printf("\n--- OUTPUT ---\n");

    int pc = 0;

    while(pc < globalSize) {
        char a[20], b[20], c[20];

        /* assignment */
        if(sscanf(globalCode[pc], "%s = %s", a, b) == 2 &&
           !strstr(globalCode[pc], "+") &&
           !strstr(globalCode[pc], "-") &&
           !strstr(globalCode[pc], "*") &&
           !strstr(globalCode[pc], "/") &&
           !strstr(globalCode[pc], "<") &&
           !strstr(globalCode[pc], ">") &&
           !strstr(globalCode[pc], "==")) {

            vars[getVarIndex(a)] = getValue(b);
        }

        /* arithmetic */
        else if(sscanf(globalCode[pc], "%s = %s + %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) + getValue(c);

        else if(sscanf(globalCode[pc], "%s = %s - %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) - getValue(c);

        else if(sscanf(globalCode[pc], "%s = %s * %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) * getValue(c);

        else if(sscanf(globalCode[pc], "%s = %s / %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) / getValue(c);

        /* conditions */
        else if(sscanf(globalCode[pc], "%s = %s < %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) < getValue(c);

        else if(sscanf(globalCode[pc], "%s = %s > %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) > getValue(c);

        else if(sscanf(globalCode[pc], "%s = %s == %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) == getValue(c);

        else if(sscanf(globalCode[pc], "%s = %s <= %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) <= getValue(c);

        else if(sscanf(globalCode[pc], "%s = %s >= %s", a,b,c)==3)
            vars[getVarIndex(a)] = getValue(b) >= getValue(c);
        
        else if(sscanf(globalCode[pc], "input %s", a)==1) {
            int idx = getVarIndex(a);
            printf("Enter value for %s: ", a);
            scanf("%d", &vars[idx]);
        }
        /* print */
        else if(sscanf(globalCode[pc], "print %s", a)==1)
            printf("%d\n", getValue(a));

        /* goto */
        else if(sscanf(globalCode[pc], "goto %s", a)==1) {
            char label[20];
            sprintf(label,"%s:",a);
            for(int i=0;i<globalSize;i++) {
                if(strcmp(globalCode[i],label)==0) {
                    pc = i;
                    break;
                }
            }
            continue;
        }

        /* if */
        else if(sscanf(globalCode[pc], "if %s goto %s", a,b)==2) {
            if(getValue(a)) {
                char label[20];
                sprintf(label,"%s:",b);
                for(int i=0;i<globalSize;i++) {
                    if(strcmp(globalCode[i],label)==0) {
                        pc = i;
                        break;
                    }
                }
                continue;
            }
        }

        pc++;
    }
}

#line 244 "mummy.tab.c"

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

#include "mummy.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_MUMMY = 3,                      /* MUMMY  */
  YYSYMBOL_YE_HE = 4,                      /* YE_HE  */
  YYSYMBOL_JAB_TAK = 5,                    /* JAB_TAK  */
  YYSYMBOL_AGAR = 6,                       /* AGAR  */
  YYSYMBOL_NAHI_TO = 7,                    /* NAHI_TO  */
  YYSYMBOL_BOLO = 8,                       /* BOLO  */
  YYSYMBOL_PUCHO = 9,                      /* PUCHO  */
  YYSYMBOL_END = 10,                       /* END  */
  YYSYMBOL_ASSIGN = 11,                    /* ASSIGN  */
  YYSYMBOL_SEMICOLON = 12,                 /* SEMICOLON  */
  YYSYMBOL_PLUS = 13,                      /* PLUS  */
  YYSYMBOL_MINUS = 14,                     /* MINUS  */
  YYSYMBOL_MUL = 15,                       /* MUL  */
  YYSYMBOL_DIV = 16,                       /* DIV  */
  YYSYMBOL_LT = 17,                        /* LT  */
  YYSYMBOL_GT = 18,                        /* GT  */
  YYSYMBOL_EQ = 19,                        /* EQ  */
  YYSYMBOL_LE = 20,                        /* LE  */
  YYSYMBOL_GE = 21,                        /* GE  */
  YYSYMBOL_LPAREN = 22,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 23,                    /* RPAREN  */
  YYSYMBOL_ID = 24,                        /* ID  */
  YYSYMBOL_NUMBER = 25,                    /* NUMBER  */
  YYSYMBOL_YYACCEPT = 26,                  /* $accept  */
  YYSYMBOL_program = 27,                   /* program  */
  YYSYMBOL_stmt_list = 28,                 /* stmt_list  */
  YYSYMBOL_statement = 29,                 /* statement  */
  YYSYMBOL_declare = 30,                   /* declare  */
  YYSYMBOL_print_stmt = 31,                /* print_stmt  */
  YYSYMBOL_input_stmt = 32,                /* input_stmt  */
  YYSYMBOL_expression = 33,                /* expression  */
  YYSYMBOL_relational = 34,                /* relational  */
  YYSYMBOL_additive = 35,                  /* additive  */
  YYSYMBOL_term = 36,                      /* term  */
  YYSYMBOL_factor = 37,                    /* factor  */
  YYSYMBOL_if_stmt = 38,                   /* if_stmt  */
  YYSYMBOL_loop_stmt = 39                  /* loop_stmt  */
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
typedef yytype_int8 yy_state_t;

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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   66

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  26
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  33
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  70

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   280


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
      25
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   189,   189,   193,   194,   198,   199,   200,   201,   202,
     203,   214,   215,   226,   237,   246,   249,   253,   257,   261,
     265,   269,   273,   277,   281,   285,   289,   293,   297,   298,
     299,   304,   316,   335
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "MUMMY", "YE_HE",
  "JAB_TAK", "AGAR", "NAHI_TO", "BOLO", "PUCHO", "END", "ASSIGN",
  "SEMICOLON", "PLUS", "MINUS", "MUL", "DIV", "LT", "GT", "EQ", "LE", "GE",
  "LPAREN", "RPAREN", "ID", "NUMBER", "$accept", "program", "stmt_list",
  "statement", "declare", "print_stmt", "input_stmt", "expression",
  "relational", "additive", "term", "factor", "if_stmt", "loop_stmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-40)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       1,    31,    27,     7,     1,   -40,    -8,    19,    26,    25,
      32,   -40,   -40,   -40,   -40,   -40,    25,   -40,   -40,    -6,
      25,    25,    25,   -40,   -40,    43,   -40,    13,     5,   -40,
      45,    46,    25,   -40,    39,    40,    42,   -40,    25,    25,
      25,    25,    25,    25,    25,    25,    25,   -40,   -40,    49,
       1,     1,   -40,     5,     5,    38,    38,    38,    38,    38,
     -40,   -40,   -40,    -2,    -1,   -40,    59,     1,     0,   -40
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     2,     4,     0,     0,     0,     0,
       0,     5,     6,     7,     8,     9,     0,     1,     3,     0,
       0,     0,     0,    28,    29,     0,    15,    21,    24,    27,
       0,     0,     0,    11,     0,     0,     0,    13,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    10,     0,
       0,     0,    30,    22,    23,    16,    17,    18,    19,    20,
      25,    26,    12,     0,     0,    33,    31,     0,     0,    32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -40,   -40,   -39,    -4,   -40,   -40,   -40,    -3,   -40,     2,
     -24,     8,   -40,   -40
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,    11,    12,    13,    25,    26,    27,
      28,    29,    14,    15
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      18,     1,     1,     1,     1,    32,    33,    17,    65,    66,
      69,    63,    64,    31,    53,    54,    19,    34,    35,    36,
      45,    46,     2,     2,     2,     2,    38,    39,    68,    49,
      40,    41,    42,    43,    44,     6,     7,     8,    16,     9,
      10,    20,    55,    56,    57,    58,    59,    22,    21,    23,
      24,    38,    39,    60,    61,    37,    30,    47,    48,    18,
      18,    62,    50,    51,    18,    52,    67
};

static const yytype_int8 yycheck[] =
{
       4,     3,     3,     3,     3,    11,    12,     0,    10,    10,
      10,    50,    51,    16,    38,    39,    24,    20,    21,    22,
      15,    16,    24,    24,    24,    24,    13,    14,    67,    32,
      17,    18,    19,    20,    21,     4,     5,     6,    11,     8,
       9,    22,    40,    41,    42,    43,    44,    22,    22,    24,
      25,    13,    14,    45,    46,    12,    24,    12,    12,    63,
      64,    12,    23,    23,    68,    23,     7
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    24,    27,    28,    29,     4,     5,     6,     8,
       9,    30,    31,    32,    38,    39,    11,     0,    29,    24,
      22,    22,    22,    24,    25,    33,    34,    35,    36,    37,
      24,    33,    11,    12,    33,    33,    33,    12,    13,    14,
      17,    18,    19,    20,    21,    15,    16,    12,    12,    33,
      23,    23,    23,    36,    36,    35,    35,    35,    35,    35,
      37,    37,    12,    28,    28,    10,    10,     7,    28,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    26,    27,    28,    28,    29,    29,    29,    29,    29,
      29,    30,    30,    31,    32,    33,    34,    34,    34,    34,
      34,    34,    35,    35,    35,    36,    36,    36,    37,    37,
      37,    38,    38,    39
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     2,     2,     2,     2,
       4,     3,     5,     3,     3,     1,     3,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     1,     1,     1,
       3,     6,     9,     6
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
  case 2: /* program: stmt_list  */
#line 189 "mummy.y"
              { storeCode((yyvsp[0].node)); }
#line 1304 "mummy.tab.c"
    break;

  case 3: /* stmt_list: stmt_list statement  */
#line 193 "mummy.y"
                        { merge((yyvsp[-1].node),(yyvsp[0].node)); (yyval.node) = (yyvsp[-1].node); }
#line 1310 "mummy.tab.c"
    break;

  case 4: /* stmt_list: statement  */
#line 194 "mummy.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1316 "mummy.tab.c"
    break;

  case 5: /* statement: MUMMY declare  */
#line 198 "mummy.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1322 "mummy.tab.c"
    break;

  case 6: /* statement: MUMMY print_stmt  */
#line 199 "mummy.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1328 "mummy.tab.c"
    break;

  case 7: /* statement: MUMMY input_stmt  */
#line 200 "mummy.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1334 "mummy.tab.c"
    break;

  case 8: /* statement: MUMMY if_stmt  */
#line 201 "mummy.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1340 "mummy.tab.c"
    break;

  case 9: /* statement: MUMMY loop_stmt  */
#line 202 "mummy.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1346 "mummy.tab.c"
    break;

  case 10: /* statement: ID ASSIGN expression SEMICOLON  */
#line 203 "mummy.y"
                                     {
        (yyval.node) = newNode();
        merge((yyval.node),(yyvsp[-1].node));
        char line[100];
        sprintf(line,"%s = %s",(yyvsp[-3].str),(yyvsp[-1].node)->place);
        addLine((yyval.node),line);
    }
#line 1358 "mummy.tab.c"
    break;

  case 11: /* declare: YE_HE ID SEMICOLON  */
#line 214 "mummy.y"
                       { (yyval.node) = newNode(); }
#line 1364 "mummy.tab.c"
    break;

  case 12: /* declare: YE_HE ID ASSIGN expression SEMICOLON  */
#line 215 "mummy.y"
                                         {
        (yyval.node) = newNode();
        merge((yyval.node),(yyvsp[-1].node));
        char line[100];
        sprintf(line,"%s = %s",(yyvsp[-3].str),(yyvsp[-1].node)->place);
        addLine((yyval.node),line);
    }
#line 1376 "mummy.tab.c"
    break;

  case 13: /* print_stmt: BOLO expression SEMICOLON  */
#line 226 "mummy.y"
                              {
        (yyval.node) = newNode();
        merge((yyval.node),(yyvsp[-1].node));
        char line[100];
        sprintf(line,"print %s",(yyvsp[-1].node)->place);
        addLine((yyval.node),line);
    }
#line 1388 "mummy.tab.c"
    break;

  case 14: /* input_stmt: PUCHO ID SEMICOLON  */
#line 237 "mummy.y"
                       {
        (yyval.node) = newNode();
        char line[100];
        sprintf(line,"input %s",(yyvsp[-1].str));
        addLine((yyval.node),line);
    }
#line 1399 "mummy.tab.c"
    break;

  case 15: /* expression: relational  */
#line 246 "mummy.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1405 "mummy.tab.c"
    break;

  case 16: /* relational: additive LT additive  */
#line 249 "mummy.y"
                         { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s < %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1414 "mummy.tab.c"
    break;

  case 17: /* relational: additive GT additive  */
#line 253 "mummy.y"
                         { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s > %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1423 "mummy.tab.c"
    break;

  case 18: /* relational: additive EQ additive  */
#line 257 "mummy.y"
                         { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s == %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1432 "mummy.tab.c"
    break;

  case 19: /* relational: additive LE additive  */
#line 261 "mummy.y"
                         { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s <= %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1441 "mummy.tab.c"
    break;

  case 20: /* relational: additive GE additive  */
#line 265 "mummy.y"
                         { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s >= %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1450 "mummy.tab.c"
    break;

  case 21: /* relational: additive  */
#line 269 "mummy.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1456 "mummy.tab.c"
    break;

  case 22: /* additive: additive PLUS term  */
#line 273 "mummy.y"
                       { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s + %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1465 "mummy.tab.c"
    break;

  case 23: /* additive: additive MINUS term  */
#line 277 "mummy.y"
                        { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s - %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1474 "mummy.tab.c"
    break;

  case 24: /* additive: term  */
#line 281 "mummy.y"
         { (yyval.node) = (yyvsp[0].node); }
#line 1480 "mummy.tab.c"
    break;

  case 25: /* term: term MUL factor  */
#line 285 "mummy.y"
                    { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s * %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1489 "mummy.tab.c"
    break;

  case 26: /* term: term DIV factor  */
#line 289 "mummy.y"
                    { (yyval.node) = newNode(); merge((yyval.node),(yyvsp[-2].node)); merge((yyval.node),(yyvsp[0].node));
        char* t=newTemp(); char line[100];
        sprintf(line,"%s = %s / %s",t,(yyvsp[-2].node)->place,(yyvsp[0].node)->place);
        addLine((yyval.node),line); strcpy((yyval.node)->place,t); }
#line 1498 "mummy.tab.c"
    break;

  case 27: /* term: factor  */
#line 293 "mummy.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 1504 "mummy.tab.c"
    break;

  case 28: /* factor: ID  */
#line 297 "mummy.y"
       { (yyval.node) = newNode(); strcpy((yyval.node)->place,(yyvsp[0].str)); }
#line 1510 "mummy.tab.c"
    break;

  case 29: /* factor: NUMBER  */
#line 298 "mummy.y"
           { (yyval.node) = newNode(); strcpy((yyval.node)->place,(yyvsp[0].str)); }
#line 1516 "mummy.tab.c"
    break;

  case 30: /* factor: LPAREN expression RPAREN  */
#line 299 "mummy.y"
                             { (yyval.node) = (yyvsp[-1].node); }
#line 1522 "mummy.tab.c"
    break;

  case 31: /* if_stmt: AGAR LPAREN expression RPAREN stmt_list END  */
#line 304 "mummy.y"
                                                {
        (yyval.node) = newNode();
        char *L1=newLabel(), *L2=newLabel();
        merge((yyval.node),(yyvsp[-3].node));
        char l1[100], l2[100];
        sprintf(l1,"if %s goto %s",(yyvsp[-3].node)->place,L1);
        sprintf(l2,"goto %s",L2);
        addLine((yyval.node),l1); addLine((yyval.node),l2);
        char lab1[20]; sprintf(lab1,"%s:",L1); addLine((yyval.node),lab1);
        merge((yyval.node),(yyvsp[-1].node));
        char lab2[20]; sprintf(lab2,"%s:",L2); addLine((yyval.node),lab2);
    }
#line 1539 "mummy.tab.c"
    break;

  case 32: /* if_stmt: AGAR LPAREN expression RPAREN stmt_list END NAHI_TO stmt_list END  */
#line 316 "mummy.y"
                                                                      {
        (yyval.node) = newNode();
        char *L1=newLabel(), *L2=newLabel(), *L3=newLabel();
        merge((yyval.node),(yyvsp[-6].node));
        char l1[100], l2[100];
        sprintf(l1,"if %s goto %s",(yyvsp[-6].node)->place,L1);
        sprintf(l2,"goto %s",L2);
        addLine((yyval.node),l1); addLine((yyval.node),l2);
        char lab1[20]; sprintf(lab1,"%s:",L1); addLine((yyval.node),lab1);
        merge((yyval.node),(yyvsp[-4].node));
        char go[100]; sprintf(go,"goto %s",L3); addLine((yyval.node),go);
        char lab2[20]; sprintf(lab2,"%s:",L2); addLine((yyval.node),lab2);
        merge((yyval.node),(yyvsp[-1].node));
        char lab3[20]; sprintf(lab3,"%s:",L3); addLine((yyval.node),lab3);
    }
#line 1559 "mummy.tab.c"
    break;

  case 33: /* loop_stmt: JAB_TAK LPAREN expression RPAREN stmt_list END  */
#line 335 "mummy.y"
                                                   {
        (yyval.node) = newNode();
        char *L1=newLabel(), *L2=newLabel(), *L3=newLabel();
        char start[20]; sprintf(start,"%s:",L1); addLine((yyval.node),start);
        merge((yyval.node),(yyvsp[-3].node));
        char l1[100], l2[100];
        sprintf(l1,"if %s goto %s",(yyvsp[-3].node)->place,L2);
        sprintf(l2,"goto %s",L3);
        addLine((yyval.node),l1); addLine((yyval.node),l2);
        char body[20]; sprintf(body,"%s:",L2); addLine((yyval.node),body);
        merge((yyval.node),(yyvsp[-1].node));
        char back[100]; sprintf(back,"goto %s",L1); addLine((yyval.node),back);
        char end[20]; sprintf(end,"%s:",L3); addLine((yyval.node),end);
    }
#line 1578 "mummy.tab.c"
    break;


#line 1582 "mummy.tab.c"

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
      yyerror (YY_("syntax error"));
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

  return yyresult;
}

#line 351 "mummy.y"


void yyerror(const char *s) {
    printf("Syntax Error: %s\n", s);
}

int main(int argc, char *argv[]) {
    yyin = fopen(argv[1], "r");

    if (yyparse() == 0) {
        printTAC();
        executeTAC();
    }

    return 0;
}
