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

/* Substitute the type names.  */
#define YYSTYPE         SMT2STYPE
/* Substitute the variable and function names.  */
#define yyparse         smt2parse
#define yylex           smt2lex
#define yyerror         smt2error
#define yydebug         smt2debug
#define yynerrs         smt2nerrs

#define yylval          smt2lval
#define yychar          smt2char

/* Copy the first part of user declarations.  */
#line 6 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:339  */

  /********************************************************************
   * AUTHORS:  Trevor Hansen
   *
   * BEGIN DATE: May, 2010
   *
   * This file is modified version of the STP's smtlib.y file. Please
   * see CVCL license below
  ********************************************************************/

  /********************************************************************
   * AUTHORS: Vijay Ganesh, Trevor Hansen
   *
   * BEGIN DATE: July, 2006
   *
   * This file is modified version of the CVCL's smtlib.y file. Please
   * see CVCL license below
  ********************************************************************/


  /********************************************************************
   *
   * \file smtlib.y
   *
   * Author: Sergey Berezin, Clark Barrett
   *
   * Created: Apr 30 2005
   *
   * <hr>
   * Copyright (C) 2004 by the Board of Trustees of Leland Stanford
   * Junior University and by New York University.
   *
   * License to use, copy, modify, sell and/or distribute this software
   * and its documentation for any purpose is hereby granted without
   * royalty, subject to the terms and conditions defined in the \ref
   * LICENSE file provided with this distribution.  In particular:
   *
   * - The above copyright notice and this permission notice must appear
   * in all copies of the software and related documentation.
   *
   * - THE SOFTWARE IS PROVIDED "AS-IS", WITHOUT ANY WARRANTIES,
   * EXPRESSED OR IMPLIED.  USE IT AT YOUR OWN RISK.
   *
   * <hr>
  ********************************************************************/

#include "stp/cpp_interface.h"
#include "stp/Parser/LetMgr.h"
#include "stp/Parser/parser.h"
#include "parsesmt2.tab.h"
#include "smt2_flex_header.h"

  using std::cout;
  using std::cerr;
  using std::endl;

  using stp::SYMBOL;       //!< Named expression (or variable), i.e. created via 'vc_varExpr'.
  using stp::BVNOT;        //!< Bitvector bitwise-not
  using stp::BVCONCAT;     //!< Bitvector concatenation
  using stp::BVOR;         //!< Bitvector bitwise-or
  using stp::BVAND;        //!< Bitvector bitwise-and
  using stp::BVXOR;        //!< Bitvector bitwise-xor
  using stp::BVNAND;       //!< Bitvector bitwise not-and; OR nand (TODO: does this still exist?)
  using stp::BVNOR;        //!< Bitvector bitwise not-or; OR nor (TODO: does this still exist?)
  using stp::BVXNOR;       //!< Bitvector bitwise not-xor; OR xnor (TODO: does this still exist?)
  using stp::BVEXTRACT;    //!< Bitvector extraction, i.e. via 'vc_bvExtract'.
  using stp::BVLEFTSHIFT;  //!< Bitvector left-shift
  using stp::BVRIGHTSHIFT; //!< Bitvector right-right
  using stp::BVSRSHIFT;    //!< Bitvector signed right-shift
  using stp::BVPLUS;       //!< Bitvector addition
  using stp::BVSUB;        //!< Bitvector subtraction
  using stp::BVUMINUS;     //!< Bitvector unary minus; OR negate expression
  using stp::BVMULT;       //!< Bitvector multiplication
  using stp::BVDIV;        //!< Bitvector division
  using stp::BVMOD;        //!< Bitvector modulo operation
  using stp::SBVDIV;       //!< Signed bitvector division
  using stp::SBVREM;       //!< Signed bitvector remainder
  using stp::SBVMOD;       //!< Signed bitvector modulo operation
  using stp::BVSX;         //!< Bitvector signed extend
  using stp::BVZX;         //!< Bitvector zero extend
  using stp::ITE;          //!< If-then-else
  using stp::BOOLEXTRACT;  //!< Bitvector boolean extraction
  using stp::BVLT;         //!< Bitvector less-than
  using stp::BVLE;         //!< Bitvector less-equals
  using stp::BVGT;         //!< Bitvector greater-than
  using stp::BVGE;         //!< Bitvector greater-equals
  using stp::BVSLT;        //!< Signed bitvector less-than
  using stp::BVSLE;        //!< Signed bitvector less-equals
  using stp::BVSGT;        //!< Signed bitvector greater-than
  using stp::BVSGE;        //!< Signed bitvector greater-equals
  using stp::EQ;           //!< Equality comparator
  using stp::FALSE;        //!< Constant false boolean expression
  using stp::TRUE;         //!< Constant true boolean expression
  using stp::NOT;          //!< Logical-not boolean expression
  using stp::AND;          //!< Logical-and boolean expression
  using stp::OR;           //!< Logical-or boolean expression
  using stp::NAND;         //!< Logical-not-and boolean expression (TODO: Does this still exist?)
  using stp::NOR;          //!< Logical-not-or boolean expression (TODO: Does this still exist?)
  using stp::XOR;          //!< Logical-xor (either-or) boolean expression
  using stp::IFF;          //!< If-and-only-if boolean expression
  using stp::IMPLIES;      //!< Implication boolean expression
  using stp::PARAMBOOL;    //!< Parameterized boolean expression
  using stp::READ;         //!< Array read expression
  using stp::WRITE;        //!< Array write expression
  using stp::ARRAY;        //!< Array creation expression
  using stp::BITVECTOR;    //!< Bitvector creation expression
  using stp::BOOLEAN;      //!< Boolean creation expression

  using stp::UNDEFINED;    //!< An undefined expression.
  using stp::SYMBOL;       //!< Named expression (or variable), i.e. created via 'vc_varExpr'.
  using stp::BVCONST;      //!< Bitvector constant expression, i.e. created via 'vc_bvConstExprFromInt'.
  using stp::BVNOT;        //!< Bitvector bitwise-not
  using stp::BVCONCAT;     //!< Bitvector concatenation
  using stp::BVOR;         //!< Bitvector bitwise-or
  using stp::BVAND;        //!< Bitvector bitwise-and
  using stp::BVXOR;        //!< Bitvector bitwise-xor
  using stp::BVNAND;       //!< Bitvector bitwise not-and; OR nand (TODO: does this still exist?)
  using stp::BVNOR;        //!< Bitvector bitwise not-or; OR nor (TODO: does this still exist?)
  using stp::BVXNOR;       //!< Bitvector bitwise not-xor; OR xnor (TODO: does this still exist?)
  using stp::BVEXTRACT;    //!< Bitvector extraction, i.e. via 'vc_bvExtract'.
  using stp::BVLEFTSHIFT;  //!< Bitvector left-shift
  using stp::BVRIGHTSHIFT; //!< Bitvector right-right
  using stp::BVSRSHIFT;    //!< Bitvector signed right-shift
  using stp::BVPLUS;       //!< Bitvector addition
  using stp::BVSUB;        //!< Bitvector subtraction
  using stp::BVUMINUS;     //!< Bitvector unary minus; OR negate expression
  using stp::BVMULT;       //!< Bitvector multiplication
  using stp::BVDIV;        //!< Bitvector division
  using stp::BVMOD;        //!< Bitvector modulo operation
  using stp::SBVDIV;       //!< Signed bitvector division
  using stp::SBVREM;       //!< Signed bitvector remainder
  using stp::SBVMOD;       //!< Signed bitvector modulo operation
  using stp::BVSX;         //!< Bitvector signed extend
  using stp::BVZX;         //!< Bitvector zero extend
  using stp::ITE;          //!< If-then-else
  using stp::BOOLEXTRACT;  //!< Bitvector boolean extraction
  using stp::BVLT;         //!< Bitvector less-than
  using stp::BVLE;         //!< Bitvector less-equals
  using stp::BVGT;         //!< Bitvector greater-than
  using stp::BVGE;         //!< Bitvector greater-equals
  using stp::BVSLT;        //!< Signed bitvector less-than
  using stp::BVSLE;        //!< Signed bitvector less-equals
  using stp::BVSGT;        //!< Signed bitvector greater-than
  using stp::BVSGE;        //!< Signed bitvector greater-equals
  using stp::EQ;           //!< Equality comparator
  using stp::FALSE;        //!< Constant false boolean expression
  using stp::TRUE;         //!< Constant true boolean expression
  using stp::NOT;          //!< Logical-not boolean expression
  using stp::AND;          //!< Logical-and boolean expression
  using stp::OR;           //!< Logical-or boolean expression
  using stp::NAND;         //!< Logical-not-and boolean expression (TODO: Does this still exist?)
  using stp::NOR;          //!< Logical-not-or boolean expression (TODO: Does this still exist?)
  using stp::XOR;          //!< Logical-xor (either-or) boolean expression
  using stp::IFF;          //!< If-and-only-if boolean expression
  using stp::IMPLIES;      //!< Implication boolean expression
  using stp::PARAMBOOL;    //!< Parameterized boolean expression
  using stp::READ;         //!< Array read expression
  using stp::WRITE;        //!< Array write expression
  using stp::ARRAY;        //!< Array creation expression
  using stp::BITVECTOR;    //!< Bitvector creation expression
  using stp::BOOLEAN;      //!< Boolean creation expression

  using stp::NOT_DECLARED;
  using stp::TO_BE_SATISFIABLE;
  using stp::TO_BE_UNSATISFIABLE;
  using stp::TO_BE_UNKNOWN;

  using stp::BOOLEAN_TYPE;
  using stp::BITVECTOR_TYPE;
  using stp::ARRAY_TYPE;
  using stp::UNKNOWN_TYPE;

  using stp::SOLVER_INVALID;
  using stp::SOLVER_VALID;
  using stp::SOLVER_UNDECIDED;
  using stp::SOLVER_TIMEOUT;
  using stp::SOLVER_ERROR;
  using stp::SOLVER_UNSATISFIABLE;
  using stp::SOLVER_SATISFIABLE;

  extern char* smt2text;
  extern int smt2lineno;

  int yyerror(const char *s) {
    cout << "(error \"syntax error: line " << smt2lineno << " " << s << "  token: " << smt2text << "\")" << endl;
    return 1;
  }


#define YYLTYPE_IS_TRIVIAL 1
#define YYMAXDEPTH 104857600
#define YYERROR_VERBOSE 1
#define YY_EXIT_FAILURE -1


#line 271 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:339  */

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

/* In a future release of Bison, this section will be replaced
   by #include "parsesmt2.tab.h".  */
#ifndef YY_SMT2_HOME_YUE_WORK_STP_BUILD_LIB_PARSER_PARSESMT2_TAB_H_INCLUDED
# define YY_SMT2_HOME_YUE_WORK_STP_BUILD_LIB_PARSER_PARSESMT2_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef SMT2DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define SMT2DEBUG 1
#  else
#   define SMT2DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define SMT2DEBUG 1
# endif /* ! defined YYDEBUG */
#endif  /* ! defined SMT2DEBUG */
#if SMT2DEBUG
extern int smt2debug;
#endif

/* Token type.  */
#ifndef SMT2TOKENTYPE
# define SMT2TOKENTYPE
  enum smt2tokentype
  {
    END = 0,
    NUMERAL_TOK = 258,
    BVCONST_DECIMAL_TOK = 259,
    BVCONST_BINARY_TOK = 260,
    BVCONST_HEXIDECIMAL_TOK = 261,
    DECIMAL_TOK = 262,
    FORMID_TOK = 263,
    TERMID_TOK = 264,
    STRING_TOK = 265,
    BITVECTOR_FUNCTIONID_TOK = 266,
    BOOLEAN_FUNCTIONID_TOK = 267,
    SOURCE_TOK = 268,
    CATEGORY_TOK = 269,
    DIFFICULTY_TOK = 270,
    VERSION_TOK = 271,
    STATUS_TOK = 272,
    LICENSE_TOK = 273,
    UNDERSCORE_TOK = 274,
    LPAREN_TOK = 275,
    RPAREN_TOK = 276,
    EXCLAIMATION_MARK_TOK = 277,
    NAMED_ATTRIBUTE_TOK = 278,
    BVLEFTSHIFT_1_TOK = 279,
    BVRIGHTSHIFT_1_TOK = 280,
    BVARITHRIGHTSHIFT_TOK = 281,
    BVPLUS_TOK = 282,
    BVSUB_TOK = 283,
    BVNOT_TOK = 284,
    BVMULT_TOK = 285,
    BVDIV_TOK = 286,
    SBVDIV_TOK = 287,
    BVMOD_TOK = 288,
    SBVREM_TOK = 289,
    SBVMOD_TOK = 290,
    BVNEG_TOK = 291,
    BVAND_TOK = 292,
    BVOR_TOK = 293,
    BVXOR_TOK = 294,
    BVNAND_TOK = 295,
    BVNOR_TOK = 296,
    BVXNOR_TOK = 297,
    BVCONCAT_TOK = 298,
    BVLT_TOK = 299,
    BVGT_TOK = 300,
    BVLE_TOK = 301,
    BVGE_TOK = 302,
    BVSLT_TOK = 303,
    BVSGT_TOK = 304,
    BVSLE_TOK = 305,
    BVSGE_TOK = 306,
    BVSX_TOK = 307,
    BVEXTRACT_TOK = 308,
    BVZX_TOK = 309,
    BVROTATE_RIGHT_TOK = 310,
    BVROTATE_LEFT_TOK = 311,
    BVREPEAT_TOK = 312,
    BVCOMP_TOK = 313,
    BITVEC_TOK = 314,
    ARRAY_TOK = 315,
    BOOL_TOK = 316,
    TRUE_TOK = 317,
    FALSE_TOK = 318,
    NOT_TOK = 319,
    AND_TOK = 320,
    OR_TOK = 321,
    XOR_TOK = 322,
    ITE_TOK = 323,
    EQ_TOK = 324,
    IMPLIES_TOK = 325,
    DISTINCT_TOK = 326,
    LET_TOK = 327,
    COLON_TOK = 328,
    ASSERT_TOK = 329,
    CHECK_SAT_TOK = 330,
    CHECK_SAT_ASSUMING_TOK = 331,
    DECLARE_CONST_TOK = 332,
    DECLARE_FUNCTION_TOK = 333,
    DECLARE_SORT_TOK = 334,
    DEFINE_FUNCTION_TOK = 335,
    DECLARE_FUN_REC_TOK = 336,
    DECLARE_FUNS_REC_TOK = 337,
    DEFINE_SORT_TOK = 338,
    ECHO_TOK = 339,
    EXIT_TOK = 340,
    GET_ASSERTIONS_TOK = 341,
    GET_ASSIGNMENT_TOK = 342,
    GET_INFO_TOK = 343,
    GET_MODEL_TOK = 344,
    GET_OPTION_TOK = 345,
    GET_PROOF_TOK = 346,
    GET_UNSAT_ASSUMPTION_TOK = 347,
    GET_UNSAT_CORE_TOK = 348,
    GET_VALUE_TOK = 349,
    POP_TOK = 350,
    PUSH_TOK = 351,
    RESET_TOK = 352,
    RESET_ASSERTIONS_TOK = 353,
    NOTES_TOK = 354,
    LOGIC_TOK = 355,
    SET_OPTION_TOK = 356,
    SELECT_TOK = 357,
    STORE_TOK = 358
  };
#endif

/* Value type.  */
#if ! defined SMT2STYPE && ! defined SMT2STYPE_IS_DECLARED

union SMT2STYPE
{
#line 202 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:355  */

  unsigned uintval; /* for numerals in types. */

  //ASTNode,ASTVec
  stp::ASTNode *node;
  stp::ASTVec *vec;

  std::string *str;

#line 434 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:355  */
};

typedef union SMT2STYPE SMT2STYPE;
# define SMT2STYPE_IS_TRIVIAL 1
# define SMT2STYPE_IS_DECLARED 1
#endif


extern SMT2STYPE smt2lval;

int smt2parse (void);

#endif /* !YY_SMT2_HOME_YUE_WORK_STP_BUILD_LIB_PARSER_PARSESMT2_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 451 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:358  */

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
         || (defined SMT2STYPE_IS_TRIVIAL && SMT2STYPE_IS_TRIVIAL)))

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
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   939

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  104
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  370

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   358

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103
};

#if SMT2DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   349,   349,   357,   358,   363,   370,   375,   380,   385,
     390,   395,   402,   409,   414,   420,   427,   433,   439,   446,
     453,   459,   470,   475,   478,   484,   495,   501,   510,   530,
     543,   552,   568,   575,   609,   626,   628,   630,   632,   634,
     636,   642,   652,   660,   684,   693,   702,   711,   723,   732,
     743,   749,   755,   760,   767,   794,   818,   825,   832,   839,
     846,   853,   860,   867,   874,   878,   883,   889,   896,   901,
     906,   912,   919,   918,   927,   933,   939,   963,   964,   967,
     981,   999,  1009,  1020,  1025,  1029,  1042,  1056,  1072,  1080,
    1089,  1097,  1105,  1113,  1121,  1129,  1137,  1145,  1163,  1174,
    1182,  1191,  1199,  1208,  1217,  1226,  1234,  1242,  1250,  1258,
    1267,  1276,  1285,  1308,  1331,  1347,  1353,  1360,  1367,  1377,
    1387,  1406,  1405
};
#endif

#if SMT2DEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "NUMERAL_TOK",
  "BVCONST_DECIMAL_TOK", "BVCONST_BINARY_TOK", "BVCONST_HEXIDECIMAL_TOK",
  "DECIMAL_TOK", "FORMID_TOK", "TERMID_TOK", "STRING_TOK",
  "BITVECTOR_FUNCTIONID_TOK", "BOOLEAN_FUNCTIONID_TOK", "SOURCE_TOK",
  "CATEGORY_TOK", "DIFFICULTY_TOK", "VERSION_TOK", "STATUS_TOK",
  "LICENSE_TOK", "UNDERSCORE_TOK", "LPAREN_TOK", "RPAREN_TOK",
  "EXCLAIMATION_MARK_TOK", "NAMED_ATTRIBUTE_TOK", "BVLEFTSHIFT_1_TOK",
  "BVRIGHTSHIFT_1_TOK", "BVARITHRIGHTSHIFT_TOK", "BVPLUS_TOK", "BVSUB_TOK",
  "BVNOT_TOK", "BVMULT_TOK", "BVDIV_TOK", "SBVDIV_TOK", "BVMOD_TOK",
  "SBVREM_TOK", "SBVMOD_TOK", "BVNEG_TOK", "BVAND_TOK", "BVOR_TOK",
  "BVXOR_TOK", "BVNAND_TOK", "BVNOR_TOK", "BVXNOR_TOK", "BVCONCAT_TOK",
  "BVLT_TOK", "BVGT_TOK", "BVLE_TOK", "BVGE_TOK", "BVSLT_TOK", "BVSGT_TOK",
  "BVSLE_TOK", "BVSGE_TOK", "BVSX_TOK", "BVEXTRACT_TOK", "BVZX_TOK",
  "BVROTATE_RIGHT_TOK", "BVROTATE_LEFT_TOK", "BVREPEAT_TOK", "BVCOMP_TOK",
  "BITVEC_TOK", "ARRAY_TOK", "BOOL_TOK", "TRUE_TOK", "FALSE_TOK",
  "NOT_TOK", "AND_TOK", "OR_TOK", "XOR_TOK", "ITE_TOK", "EQ_TOK",
  "IMPLIES_TOK", "DISTINCT_TOK", "LET_TOK", "COLON_TOK", "ASSERT_TOK",
  "CHECK_SAT_TOK", "CHECK_SAT_ASSUMING_TOK", "DECLARE_CONST_TOK",
  "DECLARE_FUNCTION_TOK", "DECLARE_SORT_TOK", "DEFINE_FUNCTION_TOK",
  "DECLARE_FUN_REC_TOK", "DECLARE_FUNS_REC_TOK", "DEFINE_SORT_TOK",
  "ECHO_TOK", "EXIT_TOK", "GET_ASSERTIONS_TOK", "GET_ASSIGNMENT_TOK",
  "GET_INFO_TOK", "GET_MODEL_TOK", "GET_OPTION_TOK", "GET_PROOF_TOK",
  "GET_UNSAT_ASSUMPTION_TOK", "GET_UNSAT_CORE_TOK", "GET_VALUE_TOK",
  "POP_TOK", "PUSH_TOK", "RESET_TOK", "RESET_ASSERTIONS_TOK", "NOTES_TOK",
  "LOGIC_TOK", "SET_OPTION_TOK", "SELECT_TOK", "STORE_TOK", "$accept",
  "cmd", "commands", "cmdi", "function_param", "function_params",
  "function_def", "status", "attribute", "var_decl", "an_mixed",
  "an_formulas", "an_formula", "$@1", "lets", "let", "an_terms", "an_term",
  "$@2", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358
};
# endif

#define YYPACT_NINF -262

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-262)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -4,   194,    34,    15,   149,  -262,    21,    22,    58,    67,
      76,  -262,  -262,    77,    95,    96,  -262,    -6,    91,    30,
      83,  -262,  -262,   194,  -262,  -262,   867,  -262,  -262,  -262,
     825,   825,    86,  -262,    87,  -262,  -262,   675,  -262,  -262,
    -262,  -262,  -262,  -262,   100,  -262,    10,  -262,   101,  -262,
      92,   675,   149,   825,   825,   825,   825,   825,   825,   825,
     825,   149,   149,   149,   149,   149,   675,   149,   675,    94,
      99,  -262,  -262,  -262,  -262,   137,   725,   825,   825,   825,
     825,   825,   825,   825,   825,   825,   825,   825,   825,   825,
     825,   825,   825,   825,   825,   825,   825,   825,   149,   825,
     825,   118,   121,   124,     1,   355,   435,  -262,  -262,  -262,
    -262,  -262,  -262,     9,  -262,   515,   125,   825,   825,   825,
     825,   825,   825,   825,   825,   133,    88,  -262,   132,   149,
     149,   149,   825,   149,   135,   775,  -262,  -262,  -262,   155,
     675,    27,   825,   139,   141,   825,   825,   825,   825,   825,
    -262,   825,   825,   825,   825,   825,   825,  -262,   825,   825,
     825,   825,   825,   825,   825,   825,   825,   825,   825,  -262,
    -262,   -18,   150,   -17,  -262,    19,   675,   149,   143,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,   154,   144,   145,   146,
     147,   151,   152,   153,   156,  -262,  -262,  -262,  -262,   157,
     149,   159,   160,   161,  -262,  -262,  -262,   163,  -262,   595,
     167,   168,   173,   189,   190,   193,   176,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
    -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,   825,  -262,
     825,   -15,  -262,   180,    13,   149,    17,  -262,   675,  -262,
     181,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,  -262,
     182,  -262,  -262,  -262,   191,   183,   163,  -262,   184,   203,
     186,   188,   192,   195,   204,   163,  -262,  -262,   158,   199,
     196,   164,   200,  -262,    14,   149,  -262,  -262,   675,   149,
    -262,   825,   201,   825,   825,   825,   825,   205,   206,   221,
     211,   166,   228,   213,   174,   214,  -262,   215,   216,   218,
    -262,   825,  -262,  -262,  -262,  -262,  -262,   825,   219,   185,
     232,   220,   187,   239,   224,  -262,  -262,  -262,  -262,   226,
    -262,   242,   227,   825,   247,   234,   208,  -262,   238,   241,
    -262,   252,   825,   257,   255,  -262,   256,  -262,   259,   258,
     263,   264,   233,   237,   266,   283,   294,   243,   277,   280,
     301,   284,   285,   286,  -262,   825,   287,  -262,   825,  -262
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     6,     0,     0,     0,     0,
       0,    12,    13,     0,     0,     0,    20,     0,     0,     0,
       0,     1,     2,     0,    52,    75,     0,    50,    51,     5,
       0,     0,     0,     9,     0,    10,    11,     0,    19,    18,
      35,    36,    37,    38,     0,    40,    24,    21,     0,     4,
       0,    75,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   117,   116,    83,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,    45,    34,
      39,    23,    22,     0,     3,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    48,     0,     0,
       0,     0,     0,     0,     0,     0,    81,    72,    64,     0,
     119,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      92,     0,     0,     0,     0,     0,     0,    93,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     7,
       8,     0,     0,     0,    26,     0,     0,     0,     0,    14,
      46,    47,    15,    17,    16,    74,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    68,    49,    69,     0,
       0,     0,     0,     0,    55,    54,    82,     0,   115,     0,
       0,     0,     0,     0,     0,     0,     0,   121,    84,   109,
     110,   111,   100,    99,   101,   102,   104,   103,   105,   106,
      94,    95,    96,   107,   108,    97,    91,    98,     0,    85,
       0,     0,    42,     0,     0,     0,     0,    27,     0,    72,
       0,    60,    62,    61,    63,    56,    58,    57,    59,    70,
       0,    71,    53,    66,     0,     0,    78,   118,     0,     0,
       0,     0,     0,     0,     0,     0,    90,    86,     0,     0,
       0,     0,     0,    30,     0,     0,    76,    67,     0,     0,
      77,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    29,     0,     0,     0,
      89,     0,    88,   113,   112,   114,   120,     0,     0,     0,
       0,     0,     0,     0,     0,    79,    80,    73,    87,     0,
      41,     0,     0,     0,     0,     0,     0,   122,     0,     0,
      31,     0,     0,     0,     0,    25,     0,    28,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    43,     0,     0,    33,     0,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -262,  -262,  -262,   288,   134,  -262,  -262,  -262,  -262,  -262,
     -45,   -50,   123,  -262,  -261,  -262,  -262,   -30,  -262
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    20,   174,   175,    35,   110,    46,    33,
     106,   126,   107,   207,   265,   266,   135,   108,   275
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     101,   102,   241,   244,   278,   290,   115,    40,    41,    42,
      43,    44,    45,   128,   298,    22,     1,   111,   134,   182,
     112,   172,   173,   117,   118,   119,   120,   121,   122,   123,
     124,   139,   281,   304,    21,    23,   132,   284,   136,   172,
     246,    30,    31,   242,   245,   279,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   165,    32,   167,
     168,   183,   184,   282,   305,   144,   181,    34,   285,   210,
     211,   212,   213,   214,   215,   181,    36,   187,   188,   189,
     190,   191,   192,   193,   194,   209,    24,    37,    38,    39,
      25,    47,   202,    48,    49,   206,   103,   104,    26,   196,
     109,   113,   216,   114,   137,   219,   220,   221,   222,   223,
     138,   224,   225,   226,   227,   228,   229,    29,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   240,   169,
      24,   139,   170,    24,    25,   171,   216,    25,   186,    70,
      27,    28,    26,   198,   195,    26,   204,    24,   208,   217,
     243,    25,   218,   249,   250,   251,   252,   253,   254,    26,
     268,   269,   255,   256,   257,   116,   270,   258,   259,   181,
     261,   262,   263,   264,   125,   127,   127,   129,   130,   131,
     133,   127,   271,   272,    27,    28,   273,    27,    28,   274,
     280,   288,   286,   287,   289,   291,   292,   293,   276,   294,
     277,    27,    28,   295,   297,   301,   296,   299,   238,   300,
     303,   166,   311,   302,   318,   320,   316,   317,    70,   180,
     319,   321,   322,   323,   324,   332,   325,   326,   180,   327,
     330,   333,   335,   336,   331,   338,   334,   337,   339,   197,
     341,   197,   199,   200,   201,   342,   203,   197,   308,   344,
     348,   310,   345,   312,   313,   314,   315,   343,     4,     5,
       6,     7,     8,   346,     9,   349,   350,   352,    10,    11,
     351,   328,   353,    12,   354,   357,   358,   329,    13,    14,
      15,    16,   355,    17,    18,    19,   356,   359,   361,   116,
     248,   362,   360,   340,   363,   364,   365,   366,   368,   247,
       0,    50,   347,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   260,     0,     0,     0,     0,     0,     0,
       0,     0,   180,     0,     0,   367,     0,     0,   369,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,     0,    24,    73,     0,   140,    51,   283,     0,
       0,   200,     0,     0,   141,   105,     0,   176,     0,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,    53,
      54,    55,    56,    57,    58,    59,    60,     0,   306,     0,
       0,   307,   309,    97,     0,     0,     0,    27,    28,    61,
      62,    63,    64,   177,    66,    67,    68,   178,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,     0,    24,    73,     0,    74,    25,     0,     0,
       0,     0,     0,     0,    75,   105,   179,    99,   100,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    97,     0,     0,     0,    27,    28,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,     0,    24,    73,     0,    74,    25,     0,     0,
       0,     0,     0,     0,    75,   105,   185,    99,   100,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    97,     0,     0,     0,    27,    28,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,     0,    24,    73,     0,    74,    25,     0,     0,
       0,     0,     0,     0,    75,   105,   267,    99,   100,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    97,     0,     0,     0,    27,    28,     0,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,     0,    24,    73,     0,    74,    25,     0,     0,
       0,     0,     0,     0,    75,   105,     0,    99,   100,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,    72,     0,    97,    73,     0,   140,    27,    28,     0,
       0,     0,     0,    98,   141,    76,     0,   142,     0,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,    99,   100,     0,
      71,    72,     0,    97,    73,     0,    74,     0,     0,     0,
       0,     0,     0,    98,    75,    76,   205,   143,     0,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,    99,   100,     0,
      71,    72,     0,    97,    73,     0,    74,     0,     0,     0,
       0,     0,     0,    98,    75,    76,     0,     0,     0,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,    96,     0,
       0,     0,     0,     0,     0,    24,     0,    99,   100,    51,
       0,     0,     0,    97,     0,     0,     0,    26,     0,    52,
       0,     0,     0,    98,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    53,    54,    55,    56,    57,    58,    59,    60,     0,
       0,     0,     0,     0,     0,     0,     0,    99,   100,    27,
      28,    61,    62,    63,    64,    65,    66,    67,    68,    69
};

static const yytype_int16 yycheck[] =
{
      30,    31,    20,    20,    19,   266,    51,    13,    14,    15,
      16,    17,    18,    63,   275,     0,    20,     7,    68,    10,
      10,    20,    21,    53,    54,    55,    56,    57,    58,    59,
      60,     4,    19,    19,     0,    20,    66,    20,    68,    20,
      21,    20,    20,    61,    61,    60,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    10,    99,
     100,    62,    63,    60,    60,   105,   106,    10,    61,    52,
      53,    54,    55,    56,    57,   115,    10,   117,   118,   119,
     120,   121,   122,   123,   124,   140,     8,    20,     3,     3,
      12,    10,   132,    73,    21,   135,    20,    20,    20,    21,
      10,    10,   142,    21,    20,   145,   146,   147,   148,   149,
      21,   151,   152,   153,   154,   155,   156,     4,   158,   159,
     160,   161,   162,   163,   164,   165,   166,   167,   168,    21,
       8,     4,    21,     8,    12,    21,   176,    12,    23,    26,
      62,    63,    20,    21,    21,    20,    21,     8,     3,    20,
      10,    12,    21,    20,    10,    21,    21,    21,    21,    20,
       3,     3,    21,    21,    21,    52,     3,    21,    21,   209,
      21,    21,    21,    20,    61,    62,    63,    64,    65,    66,
      67,    68,     3,     3,    62,    63,     3,    62,    63,    23,
      20,    10,    21,    21,    21,    21,     3,    21,   238,    21,
     240,    62,    63,    21,    10,    19,    21,    59,   248,    20,
      20,    98,    21,    59,     3,    59,    21,    21,   105,   106,
      19,     3,    19,    59,    20,     3,    21,    21,   115,    21,
      21,    21,     3,    19,    59,     3,    59,    21,    21,   126,
       3,   128,   129,   130,   131,    21,   133,   134,   288,    21,
       3,   291,    21,   293,   294,   295,   296,    59,    74,    75,
      76,    77,    78,    21,    80,    20,    20,    19,    84,    85,
      21,   311,    19,    89,    20,    19,     3,   317,    94,    95,
      96,    97,    59,    99,   100,   101,    59,     3,    21,   176,
     177,    21,    59,   333,     3,    21,    21,    21,    21,   175,
      -1,    23,   342,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   200,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   209,    -1,    -1,   365,    -1,    -1,   368,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,    -1,     8,     9,    -1,    11,    12,   245,    -1,
      -1,   248,    -1,    -1,    19,    20,    -1,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    -1,   285,    -1,
      -1,   288,   289,    58,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,    -1,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,   102,   103,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,    -1,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,   102,   103,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,    -1,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    21,   102,   103,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,    -1,     8,     9,    -1,    11,    12,    -1,    -1,
      -1,    -1,    -1,    -1,    19,    20,    -1,   102,   103,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,     6,    -1,    58,     9,    -1,    11,    62,    63,    -1,
      -1,    -1,    -1,    68,    19,    20,    -1,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,    -1,
       5,     6,    -1,    58,     9,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    19,    20,    21,    72,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,    -1,
       5,     6,    -1,    58,     9,    -1,    11,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    19,    20,    -1,    -1,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,     8,    -1,   102,   103,    12,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    20,    -1,    22,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   102,   103,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    20,   105,   106,    74,    75,    76,    77,    78,    80,
      84,    85,    89,    94,    95,    96,    97,    99,   100,   101,
     107,     0,     0,    20,     8,    12,    20,    62,    63,   116,
      20,    20,    10,   113,    10,   110,    10,    20,     3,     3,
      13,    14,    15,    16,    17,    18,   112,    10,    73,    21,
     107,    12,    22,    44,    45,    46,    47,    48,    49,    50,
      51,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     116,     5,     6,     9,    11,    19,    20,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    58,    68,   102,
     103,   121,   121,    20,    20,    20,   114,   116,   121,    10,
     111,     7,    10,    10,    21,   114,   116,   121,   121,   121,
     121,   121,   121,   121,   121,   116,   115,   116,   115,   116,
     116,   116,   121,   116,   115,   120,   121,    20,    21,     4,
      11,    19,    22,    72,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   116,   121,   121,    21,
      21,    21,    20,    21,   108,   109,    22,    68,    72,    21,
     116,   121,    10,    62,    63,    21,    23,   121,   121,   121,
     121,   121,   121,   121,   121,    21,    21,   116,    21,   116,
     116,   116,   121,   116,    21,    21,   121,   117,     3,   114,
      52,    53,    54,    55,    56,    57,   121,    20,    21,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,    20,    61,    10,    20,    61,    21,   108,   116,    20,
      10,    21,    21,    21,    21,    21,    21,    21,    21,    21,
     116,    21,    21,    21,    20,   118,   119,    21,     3,     3,
       3,     3,     3,     3,    23,   122,   121,   121,    19,    60,
      20,    19,    60,   116,    20,    61,    21,    21,    10,    21,
     118,    21,     3,    21,    21,    21,    21,    10,   118,    59,
      20,    19,    59,    20,    19,    60,   116,   116,   121,   116,
     121,    21,   121,   121,   121,   121,    21,    21,     3,    19,
      59,     3,    19,    59,    20,    21,    21,    21,   121,   121,
      21,    59,     3,    21,    59,     3,    19,    21,     3,    21,
     121,     3,    21,    59,    21,    21,    21,   121,     3,    20,
      20,    21,    19,    19,    20,    59,    59,    19,     3,     3,
      59,    21,    21,     3,    21,    21,    21,   121,    21,   121
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   104,   105,   106,   106,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   108,   109,   109,   110,   110,
     110,   110,   110,   110,   111,   112,   112,   112,   112,   112,
     112,   113,   113,   113,   114,   114,   114,   114,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   117,   116,   116,   116,   116,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   121
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     4,     3,     2,     1,     4,     4,     2,
       2,     2,     1,     1,     4,     4,     4,     4,     2,     2,
       1,     2,     3,     3,     2,     8,     1,     2,    10,     6,
       5,     9,    18,    17,     1,     1,     1,     1,     1,     2,
       1,     8,     4,    16,     1,     1,     2,     2,     1,     2,
       1,     1,     1,     5,     4,     4,     5,     5,     5,     5,
       5,     5,     5,     5,     3,     4,     5,     6,     4,     4,
       5,     5,     0,     8,     4,     1,     6,     2,     1,     4,
       4,     1,     2,     1,     3,     3,     4,     7,     6,     6,
       4,     3,     2,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     6,     6,     6,     3,     1,     1,     4,     1,
       6,     0,     8
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
#if SMT2DEBUG

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
#else /* !SMT2DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !SMT2DEBUG */


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
#line 350 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
       stp::GlobalParserInterface->cleanUp();
       YYACCEPT;
}
#line 1898 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 359 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 1904 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 364 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      stp::GlobalParserInterface->AddAssert(*(yyvsp[0].node));
      stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
      stp::GlobalParserInterface->success();
    }
#line 1914 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 371 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      stp::GlobalParserInterface->checkSat(stp::GlobalParserInterface->getAssertVector());
    }
#line 1922 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 376 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      stp::GlobalParserInterface->unsupported();
    }
#line 1930 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 381 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      stp::GlobalParserInterface->unsupported();
    }
#line 1938 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 386 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      stp::GlobalParserInterface->success();
    }
#line 1946 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 391 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      stp::GlobalParserInterface->success();
    }
#line 1954 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 396 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      std::cout << "\"" << *(yyvsp[0].str)  << "\"" << endl;
      delete (yyvsp[0].str);
      stp::GlobalParserInterface->success();
    }
#line 1964 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 403 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
       stp::GlobalParserInterface->cleanUp();
       stp::GlobalParserInterface->success();
       YYACCEPT;
    }
#line 1974 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 410 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
       stp::GlobalParserInterface->getModel();
    }
#line 1982 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 415 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      stp::GlobalParserInterface->getValue(*(yyvsp[-1].vec));
      delete (yyvsp[-1].vec);
    }
#line 1991 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 421 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
       stp::GlobalParserInterface->setOption(*(yyvsp[-1].str),*(yyvsp[0].str));
       delete (yyvsp[-1].str);
       delete (yyvsp[0].str);
    }
#line 2001 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 428 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
       stp::GlobalParserInterface->setOption(*(yyvsp[-1].str),"false");
       delete (yyvsp[-1].str);
    }
#line 2010 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 434 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
       stp::GlobalParserInterface->setOption(*(yyvsp[-1].str),"true");
       delete (yyvsp[-1].str);
    }
#line 2019 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 440 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
        for (unsigned i=0; i < (yyvsp[0].uintval);i++)
            stp::GlobalParserInterface->push();
        stp::GlobalParserInterface->success();
    }
#line 2029 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 447 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
        for (unsigned i=0; i < (yyvsp[0].uintval);i++)
            stp::GlobalParserInterface->pop();
        stp::GlobalParserInterface->success();
    }
#line 2039 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 454 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
       stp::GlobalParserInterface->reset();
       stp::GlobalParserInterface->success();
    }
#line 2048 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 460 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      if (!(0 == strcmp((yyvsp[0].str)->c_str(),"QF_BV") ||
            0 == strcmp((yyvsp[0].str)->c_str(),"QF_ABV") ||
            0 == strcmp((yyvsp[0].str)->c_str(),"QF_AUFBV"))) {
        yyerror("Wrong input logic");
      }
      stp::GlobalParserInterface->success();
      delete (yyvsp[0].str);
    }
#line 2062 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 471 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
      delete (yyvsp[0].str);
    }
#line 2070 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 476 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2076 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 479 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2082 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 485 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = new ASTNode(stp::GlobalParserInterface->LookupOrCreateSymbol((yyvsp[-6].str)->c_str()));
  stp::GlobalParserInterface->addSymbol(*(yyval.node));
  (yyval.node)->SetIndexWidth(0);
  (yyval.node)->SetValueWidth((yyvsp[-2].uintval));
  delete (yyvsp[-6].str);
}
#line 2094 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 496 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.vec) = new ASTVec;
  (yyval.vec)->push_back(*(yyvsp[0].node));
  delete (yyvsp[0].node);
}
#line 2104 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 502 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.vec) = (yyvsp[-1].vec);
  (yyval.vec)->push_back(*(yyvsp[0].node));
  delete (yyvsp[0].node);
}
#line 2114 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 511 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  if ((yyvsp[0].node)->GetValueWidth() != (yyvsp[-2].uintval))
  {
    char msg [100];
    sprintf(msg, "Different bit-widths specified: %d %d", (yyvsp[0].node)->GetValueWidth(), (yyvsp[-2].uintval));
    yyerror(msg);
  }

  stp::GlobalParserInterface->storeFunction(*(yyvsp[-9].str), *(yyvsp[-7].vec), *(yyvsp[0].node));

  // Next time the variable is used, we want it to be fresh.
  for (size_t i = 0; i < (yyvsp[-7].vec)->size(); i++)
    stp::GlobalParserInterface->removeSymbol((*(yyvsp[-7].vec))[i]);

  delete (yyvsp[-9].str);
  delete (yyvsp[-7].vec);
  delete (yyvsp[0].node);
}
#line 2137 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 531 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  stp::GlobalParserInterface->storeFunction(*(yyvsp[-5].str), *(yyvsp[-3].vec), *(yyvsp[0].node));

  // Next time the variable is used, we want it to be fresh.
  for (size_t i = 0; i < (yyvsp[-3].vec)->size(); i++)
   stp::GlobalParserInterface->removeSymbol((*(yyvsp[-3].vec))[i]);

  delete (yyvsp[-5].str);
  delete (yyvsp[-3].vec);
  delete (yyvsp[0].node);
}
#line 2153 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 544 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTVec empty;
  stp::GlobalParserInterface->storeFunction(*(yyvsp[-4].str), empty, *(yyvsp[0].node));

  delete (yyvsp[-4].str);
  delete (yyvsp[0].node);
}
#line 2165 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 553 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  if ((yyvsp[0].node)->GetValueWidth() != (yyvsp[-2].uintval))
  {
    char msg [100];
    sprintf(msg, "Different bit-widths specified: %d %d", (yyvsp[0].node)->GetValueWidth(), (yyvsp[-2].uintval));
    yyerror(msg);
  }

  ASTVec empty;
  stp::GlobalParserInterface->storeFunction(*(yyvsp[-8].str),empty, *(yyvsp[0].node));

  delete (yyvsp[-8].str);
  delete (yyvsp[0].node);
}
#line 2184 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 569 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  stp::GlobalParserInterface->unsupported();
  delete (yyvsp[-17].str);
  delete (yyvsp[0].node);
}
#line 2194 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 576 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  stp::GlobalParserInterface->unsupported();
  delete (yyvsp[-16].str);
  delete (yyvsp[0].node);

#if 0
  ASTNode s = stp::GlobalParserInterface->LookupOrCreateSymbol((yyvsp[-16].str)->c_str());
  stp::GlobalParserInterface->addSymbol(s);
  unsigned int index_len = (yyvsp[-8].uintval);
  unsigned int value_len = (yyvsp[-3].uintval);
  if(index_len > 0) {
    s.SetIndexWidth((yyvsp[-8].uintval));
  }
  else {
    FatalError("Fatal Error: parsing: BITVECTORS must be of positive length: \n");
  }

  if(value_len > 0) {
    s.SetValueWidth((yyvsp[-3].uintval));
  }
  else {
    FatalError("Fatal Error: parsing: BITVECTORS must be of positive length: \n");
  }

  ASTVec empty;
  stp::GlobalParserInterface->storeFunction(*(yyvsp[-16].str),empty, *(yyvsp[0].node));
#endif

}
#line 2228 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 609 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {

  std::transform((yyvsp[0].str)->begin(), (yyvsp[0].str)->end(), (yyvsp[0].str)->begin(), ::tolower);
  if (0 == strcmp((yyvsp[0].str)->c_str(), "sat"))
      stp::input_status = TO_BE_SATISFIABLE;
  else if (0 == strcmp((yyvsp[0].str)->c_str(), "unsat"))
    stp::input_status = TO_BE_UNSATISFIABLE;
  else if (0 == strcmp((yyvsp[0].str)->c_str(), "unknown"))
      stp::input_status = TO_BE_UNKNOWN;
  else
      yyerror((yyvsp[0].str)->c_str());
  delete (yyvsp[0].str);
  (yyval.node) = NULL;
}
#line 2247 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 627 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2253 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 629 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2259 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 631 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2265 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 633 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2271 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 635 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2277 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 643 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode s = stp::GlobalParserInterface->LookupOrCreateSymbol((yyvsp[-7].str)->c_str());
  stp::GlobalParserInterface->addSymbol(s);
  //Sort_symbs has the indexwidth/valuewidth. Set those fields in
  //var
  s.SetIndexWidth(0);
  s.SetValueWidth((yyvsp[-1].uintval));
  delete (yyvsp[-7].str);
}
#line 2291 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 653 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode s = stp::GlobalParserInterface->LookupOrCreateSymbol((yyvsp[-3].str)->c_str());
  s.SetIndexWidth(0);
  s.SetValueWidth(0);
  stp::GlobalParserInterface->addSymbol(s);
  delete (yyvsp[-3].str);
}
#line 2303 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 661 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode s = stp::GlobalParserInterface->LookupOrCreateSymbol((yyvsp[-15].str)->c_str());
  stp::GlobalParserInterface->addSymbol(s);
  unsigned int index_len = (yyvsp[-7].uintval);
  unsigned int value_len = (yyvsp[-2].uintval);
  if(index_len > 0) {
    s.SetIndexWidth((yyvsp[-7].uintval));
  }
  else {
    stp::FatalError("Fatal Error: parsing: BITVECTORS must be of positive length: \n");
  }

  if(value_len > 0) {
    s.SetValueWidth((yyvsp[-2].uintval));
  }
  else {
    stp::FatalError("Fatal Error: parsing: BITVECTORS must be of positive length: \n");
  }
  delete (yyvsp[-15].str);
}
#line 2328 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 685 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.vec) = new ASTVec;
  if ((yyvsp[0].node) != NULL) {
    (yyval.vec)->push_back(*(yyvsp[0].node));
    stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
  }
}
#line 2340 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 694 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.vec) = new ASTVec;
  if ((yyvsp[0].node) != NULL) {
    (yyval.vec)->push_back(*(yyvsp[0].node));
    stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
  }
}
#line 2352 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 703 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  if ((yyvsp[-1].vec) != NULL && (yyvsp[0].node) != NULL) {
    (yyvsp[-1].vec)->push_back(*(yyvsp[0].node));
    (yyval.vec) = (yyvsp[-1].vec);
    stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
  }
}
#line 2364 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 712 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  if ((yyvsp[-1].vec) != NULL && (yyvsp[0].node) != NULL) {
    (yyvsp[-1].vec)->push_back(*(yyvsp[0].node));
    (yyval.vec) = (yyvsp[-1].vec);
    stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
  }
}
#line 2376 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 724 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.vec) = new ASTVec;
  if ((yyvsp[0].node) != NULL) {
    (yyval.vec)->push_back(*(yyvsp[0].node));
    stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
  }
}
#line 2388 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 733 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  if ((yyvsp[-1].vec) != NULL && (yyvsp[0].node) != NULL) {
    (yyvsp[-1].vec)->push_back(*(yyvsp[0].node));
    (yyval.vec) = (yyvsp[-1].vec);
    stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
  }
}
#line 2400 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 744 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateNode(TRUE));
  assert(0 == (yyval.node)->GetIndexWidth());
  assert(0 == (yyval.node)->GetValueWidth());
}
#line 2410 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 750 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateNode(FALSE));
  assert(0 == (yyval.node)->GetIndexWidth());
  assert(0 == (yyval.node)->GetValueWidth());
}
#line 2420 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 756 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(*(yyvsp[0].node));
  stp::GlobalParserInterface->deleteNode((yyvsp[0].node));
}
#line 2429 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 761 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(EQ,*(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode((yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode((yyvsp[-1].node));
}
#line 2440 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 768 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  using namespace stp;

  ASTVec terms = *(yyvsp[-1].vec);
  ASTVec forms;

  for(ASTVec::const_iterator it=terms.begin(),itend=terms.end();
      it!=itend; it++)
  {
    for(ASTVec::const_iterator it2=it+1; it2!=itend; it2++) {
      ASTNode n =
        stp::GlobalParserInterface->nf->CreateNode(NOT, stp::GlobalParserInterface->CreateNode(EQ, *it, *it2));

      forms.push_back(n);
    }
  }

  if(forms.size() == 0)
    FatalError("empty distinct");

  (yyval.node) = (forms.size() == 1) ?
    stp::GlobalParserInterface->newNode(forms[0]) :
    stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateNode(AND, forms));

  delete (yyvsp[-1].vec);
}
#line 2471 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 795 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  using namespace stp;

  ASTVec terms = *(yyvsp[-1].vec);
  ASTVec forms;

  for(ASTVec::const_iterator it=terms.begin(),itend=terms.end();
      it!=itend; it++) {
    for(ASTVec::const_iterator it2=it+1; it2!=itend; it2++) {
      ASTNode n = (stp::GlobalParserInterface->nf->CreateNode(NOT, stp::GlobalParserInterface->CreateNode(IFF, *it, *it2)));
      forms.push_back(n);
    }
  }

  if(forms.size() == 0)
    FatalError("empty distinct");

  (yyval.node) = (forms.size() == 1) ?
    stp::GlobalParserInterface->newNode(forms[0]) :
    stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateNode(AND, forms));

  delete (yyvsp[-1].vec);
}
#line 2499 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 819 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVSLT, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode((yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode((yyvsp[-1].node));
}
#line 2510 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 826 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVSLE, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2521 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 833 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVSGT, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2532 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 840 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVSGE, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2543 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 847 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVLT, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2554 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 854 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVLE, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2565 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 861 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVGT, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2576 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 868 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(BVGE, *(yyvsp[-2].node), *(yyvsp[-1].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2587 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 875 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = (yyvsp[-1].node);
}
#line 2595 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 879 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateNode(NOT, *(yyvsp[-1].node)));
    stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2604 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 884 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(IMPLIES, *(yyvsp[-2].node), *(yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2614 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 890 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateNode(ITE, *(yyvsp[-3].node), *(yyvsp[-2].node), *(yyvsp[-1].node)));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-3].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2625 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 897 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateNode(AND, *(yyvsp[-1].vec)));
  delete (yyvsp[-1].vec);
}
#line 2634 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 902 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateNode(OR, *(yyvsp[-1].vec)));
  delete (yyvsp[-1].vec);
}
#line 2643 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 907 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(XOR, *(yyvsp[-2].node), *(yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2653 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 913 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(IFF, *(yyvsp[-2].node), *(yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2663 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 919 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
    stp::GlobalParserInterface->letMgr->push();  // TODO this isn't going to clear properly if it's an_term later.
  }
#line 2671 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 923 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
    stp::GlobalParserInterface->letMgr->pop();
  }
#line 2680 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 928 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->applyFunction(*(yyvsp[-2].str),*(yyvsp[-1].vec)));
  delete (yyvsp[-2].str);
  delete (yyvsp[-1].vec);
}
#line 2690 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 934 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTVec empty;
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->applyFunction(*(yyvsp[0].str),empty));
  delete (yyvsp[0].str);
}
#line 2700 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 940 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  /*
    This implements (! <an_formula> :named foo)
    "foo" is created as a symbol that can be refered to by later commands.
  */

  // TODO, will fail if name is already defined?
  ASTNode s(stp::GlobalParserInterface->LookupOrCreateSymbol((yyvsp[-1].str)->c_str()));
  s.SetIndexWidth((yyvsp[-3].node)->GetIndexWidth());
  s.SetValueWidth((yyvsp[-3].node)->GetValueWidth());

  stp::GlobalParserInterface->addSymbol(s);

  ASTNode n = stp::GlobalParserInterface->CreateNode(IFF,s, *(yyvsp[-3].node));

  stp::GlobalParserInterface->AddAssert(n);

  delete (yyvsp[-1].str);

  (yyval.node) = (yyvsp[-3].node);
}
#line 2726 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 965 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {}
#line 2732 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 968 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  //populate the hashtable from LET-var -->
  //LET-exprs and then process them:
  //
  //1. ensure that LET variables do not clash
  //1. with declared variables.
  //
  //2. Ensure that LET variables are not
  //2. defined more than once
  stp::GlobalParserInterface->letMgr->LetExprMgr(*(yyvsp[-2].str),*(yyvsp[-1].node));
  delete (yyvsp[-2].str);
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
}
#line 2750 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 982 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  //populate the hashtable from LET-var -->
  //LET-exprs and then process them:
  //
  //1. ensure that LET variables do not clash
  //1. with declared variables.
  //
  //2. Ensure that LET variables are not
  //2. defined more than once
  stp::GlobalParserInterface->letMgr->LetExprMgr(*(yyvsp[-2].str),*(yyvsp[-1].node));
  delete (yyvsp[-2].str);
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));

}
#line 2769 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 1000 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.vec) = new ASTVec;
  if ((yyvsp[0].node) != NULL) {
    (yyval.vec)->push_back(*(yyvsp[0].node));
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));

  }
}
#line 2782 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 1010 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  if ((yyvsp[-1].vec) != NULL && (yyvsp[0].node) != NULL) {
    (yyvsp[-1].vec)->push_back(*(yyvsp[0].node));
    (yyval.vec) = (yyvsp[-1].vec);
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
  }
}
#line 2794 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 1021 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode((*(yyvsp[0].node)));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2803 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 1026 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = (yyvsp[-1].node);
}
#line 2811 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 1030 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  //ARRAY READ
  // valuewidth is same as array, indexwidth is 0.
  ASTNode array = *(yyvsp[-1].node);
  ASTNode index = *(yyvsp[0].node);
  unsigned int width = array.GetValueWidth();
  ASTNode * n =
    stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(READ, width, array, index));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2828 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 1043 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  //ARRAY WRITE
  unsigned int width = (yyvsp[0].node)->GetValueWidth();
  ASTNode array = *(yyvsp[-2].node);
  ASTNode index = *(yyvsp[-1].node);
  ASTNode writeval = *(yyvsp[0].node);
  ASTNode write_term = stp::GlobalParserInterface->nf->CreateArrayTerm(WRITE,(yyvsp[-2].node)->GetIndexWidth(),width,array,index,writeval);
  ASTNode * n = stp::GlobalParserInterface->newNode(write_term);
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2846 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1057 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  int width = (yyvsp[-3].uintval) - (yyvsp[-2].uintval) + 1;
  if (width < 0)
    yyerror("Negative width in extract");

  if((unsigned)(yyvsp[-3].uintval) >= (yyvsp[0].node)->GetValueWidth())
    yyerror("Parsing: Wrong width in BVEXTRACT\n");

  ASTNode hi  =  stp::GlobalParserInterface->CreateBVConst(32, (yyvsp[-3].uintval));
  ASTNode low =  stp::GlobalParserInterface->CreateBVConst(32, (yyvsp[-2].uintval));
  ASTNode output = stp::GlobalParserInterface->nf->CreateTerm(BVEXTRACT, width, *(yyvsp[0].node),hi,low);
  ASTNode * n = stp::GlobalParserInterface->newNode(output);
  (yyval.node) = n;
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2866 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1073 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned w = (yyvsp[0].node)->GetValueWidth() + (yyvsp[-2].uintval);
  ASTNode width = stp::GlobalParserInterface->CreateBVConst(32,w);
  ASTNode *n =  stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVZX,w,*(yyvsp[0].node),width));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2878 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1081 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned w = (yyvsp[0].node)->GetValueWidth() + (yyvsp[-2].uintval);
  ASTNode width = stp::GlobalParserInterface->CreateBVConst(32,w);
  ASTNode *n =  stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVSX,w,*(yyvsp[0].node),width));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2890 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1090 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  const unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateArrayTerm(ITE,(yyvsp[0].node)->GetIndexWidth(), width,*(yyvsp[-2].node), *(yyvsp[-1].node), *(yyvsp[0].node)));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-2].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2902 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1098 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  const unsigned int width = (yyvsp[-1].node)->GetValueWidth() + (yyvsp[0].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVCONCAT, width, *(yyvsp[-1].node), *(yyvsp[0].node)));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2914 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1106 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  //this is the BVNEG (term) in the CVCL language
  unsigned int width = (yyvsp[0].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVNOT, width, *(yyvsp[0].node)));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2926 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1114 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  //this is the BVUMINUS term in CVCL langauge
  unsigned width = (yyvsp[0].node)->GetValueWidth();
  ASTNode * n =  stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVUMINUS,width,*(yyvsp[0].node)));
  (yyval.node) = n;
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2938 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1122 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVAND, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;
    stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2950 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1130 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVOR, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;
    stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2962 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1138 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVXOR, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;
    stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2974 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1146 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
//   (bvxnor s t) abbreviates (bvor (bvand s t) (bvand (bvnot s) (bvnot t)))
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(
  stp::GlobalParserInterface->nf->CreateTerm( BVOR, width,
    stp::GlobalParserInterface->nf->CreateTerm(BVAND, width, *(yyvsp[-1].node), *(yyvsp[0].node)),
      stp::GlobalParserInterface->nf->CreateTerm(BVAND, width,
        stp::GlobalParserInterface->nf->CreateTerm(BVNOT, width, *(yyvsp[-1].node)),
        stp::GlobalParserInterface->nf->CreateTerm(BVNOT, width, *(yyvsp[0].node))
      )
    )
  );

  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 2996 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1164 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode * n = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(ITE, 1,
  stp::GlobalParserInterface->nf->CreateNode(EQ, *(yyvsp[-1].node), *(yyvsp[0].node)),
  stp::GlobalParserInterface->CreateOneConst(1),
  stp::GlobalParserInterface->CreateZeroConst(1)));

  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3011 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1175 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  const unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVSUB, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3023 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1183 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  const unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVPLUS, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));

}
#line 3036 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1192 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  const unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVMULT, width, *(yyvsp[-1].node), *(yyvsp[0].node)));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3048 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1200 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVDIV, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;

  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3061 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1209 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVMOD, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;

  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3074 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1218 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(SBVDIV, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;

  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3087 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1227 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(SBVREM, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3099 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1235 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(SBVMOD, width, *(yyvsp[-1].node), *(yyvsp[0].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3111 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1243 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVNOT, width, stp::GlobalParserInterface->nf->CreateTerm(BVAND, width, *(yyvsp[-1].node), *(yyvsp[0].node))));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3123 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1251 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned int width = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVNOT, width, stp::GlobalParserInterface->nf->CreateTerm(BVOR, width, *(yyvsp[-1].node), *(yyvsp[0].node))));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3135 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1259 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  // shifting left by who know how much?
  unsigned int w = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVLEFTSHIFT,w,*(yyvsp[-1].node),*(yyvsp[0].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3148 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1268 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  // shifting right by who know how much?
  unsigned int w = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVRIGHTSHIFT,w,*(yyvsp[-1].node),*(yyvsp[0].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3161 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1277 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  // shifting arithmetic right by who know how much?
  unsigned int w = (yyvsp[-1].node)->GetValueWidth();
  ASTNode * n = stp::GlobalParserInterface->newNode(BVSRSHIFT,w,*(yyvsp[-1].node),*(yyvsp[0].node));
  (yyval.node) = n;
  stp::GlobalParserInterface->deleteNode( (yyvsp[-1].node));
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3174 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1286 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode *n;
  unsigned width = (yyvsp[0].node)->GetValueWidth();
  unsigned rotate = (yyvsp[-2].uintval) % width;
  if (0 == rotate)
  {
      n = (yyvsp[0].node);
  }
  else
  {
    ASTNode high = stp::GlobalParserInterface->CreateBVConst(32,width-1);
    ASTNode zero = stp::GlobalParserInterface->CreateBVConst(32,0);
    ASTNode cut = stp::GlobalParserInterface->CreateBVConst(32,width-rotate);
    ASTNode cutMinusOne = stp::GlobalParserInterface->CreateBVConst(32,width-rotate-1);

    ASTNode top =  stp::GlobalParserInterface->nf->CreateTerm(BVEXTRACT,rotate,*(yyvsp[0].node),high, cut);
    ASTNode bottom =  stp::GlobalParserInterface->nf->CreateTerm(BVEXTRACT,width-rotate,*(yyvsp[0].node),cutMinusOne,zero);
    n =  stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVCONCAT,width,bottom,top));
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
  }
  (yyval.node) = n;
}
#line 3201 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1309 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTNode *n;
  unsigned width = (yyvsp[0].node)->GetValueWidth();
  unsigned rotate = (yyvsp[-2].uintval) % width;
  if (0 == rotate)
  {
      n = (yyvsp[0].node);
  }
  else
  {
    ASTNode high = stp::GlobalParserInterface->CreateBVConst(32,width-1);
    ASTNode zero = stp::GlobalParserInterface->CreateBVConst(32,0);
    ASTNode cut = stp::GlobalParserInterface->CreateBVConst(32,rotate);
    ASTNode cutMinusOne = stp::GlobalParserInterface->CreateBVConst(32,rotate-1);

    ASTNode bottom =  stp::GlobalParserInterface->nf->CreateTerm(BVEXTRACT,rotate,*(yyvsp[0].node),cutMinusOne, zero);
    ASTNode top =  stp::GlobalParserInterface->nf->CreateTerm(BVEXTRACT,width-rotate,*(yyvsp[0].node),high,cut);
    n =  stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->nf->CreateTerm(BVCONCAT,width,bottom,top));
    stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
  }
  (yyval.node) = n;
}
#line 3228 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1332 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned count = (yyvsp[-2].uintval);
  if (count < 1)
      stp::FatalError("One or more repeats please");

  unsigned w = (yyvsp[0].node)->GetValueWidth();
  ASTNode n =  *(yyvsp[0].node);

  for (unsigned i =1; i < count; i++)
  {
        n = stp::GlobalParserInterface->nf->CreateTerm(BVCONCAT,w*(i+1),n,*(yyvsp[0].node));
  }
  (yyval.node) = stp::GlobalParserInterface->newNode(n);
  stp::GlobalParserInterface->deleteNode( (yyvsp[0].node));
}
#line 3248 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 1348 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateBVConst(*(yyvsp[-1].str), 10, (yyvsp[0].uintval)));
  (yyval.node)->SetValueWidth((yyvsp[0].uintval));
  delete (yyvsp[-1].str);
}
#line 3258 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 1354 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned width = (yyvsp[0].str)->length()*4;
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateBVConst(*(yyvsp[0].str), 16, width));
  (yyval.node)->SetValueWidth(width);
  delete (yyvsp[0].str);
}
#line 3269 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1361 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  unsigned width = (yyvsp[0].str)->length();
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->CreateBVConst(*(yyvsp[0].str), 2, width));
  (yyval.node)->SetValueWidth(width);
  delete (yyvsp[0].str);
}
#line 3280 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1368 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->applyFunction(*(yyvsp[-2].str),*(yyvsp[-1].vec)));

  if ((yyval.node)->GetType() != BITVECTOR_TYPE)
      yyerror("Must be bitvector type");

  delete (yyvsp[-2].str);
  delete (yyvsp[-1].vec);
}
#line 3294 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1378 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  ASTVec empty;
  (yyval.node) = stp::GlobalParserInterface->newNode(stp::GlobalParserInterface->applyFunction(*(yyvsp[0].str),empty));

  if ((yyval.node)->GetType() != BITVECTOR_TYPE)
    yyerror("Must be bitvector type");

  delete (yyvsp[0].str);
}
#line 3308 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1388 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
  /* This implements (! <an_term> :named foo) */

  ASTNode s(stp::GlobalParserInterface->LookupOrCreateSymbol((yyvsp[-1].str)->c_str()));
  delete (yyvsp[-1].str);

  s.SetIndexWidth((yyvsp[-3].node)->GetIndexWidth());
  s.SetValueWidth((yyvsp[-3].node)->GetValueWidth());

  stp::GlobalParserInterface->addSymbol(s);

  ASTNode n = stp::GlobalParserInterface->CreateNode(EQ,s, *(yyvsp[-3].node));

  stp::GlobalParserInterface->AddAssert(n);

  (yyval.node) = (yyvsp[-3].node);
}
#line 3330 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 1406 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
    stp::GlobalParserInterface->letMgr->push();
  }
#line 3338 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1410 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1646  */
    {
    (yyval.node) = (yyvsp[-1].node);
    stp::GlobalParserInterface->letMgr->pop();
  }
#line 3347 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
    break;


#line 3351 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.c" /* yacc.c:1646  */
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
#line 1417 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1906  */


namespace stp {
  int SMT2Parse() {
    return smt2parse();
  }
}
