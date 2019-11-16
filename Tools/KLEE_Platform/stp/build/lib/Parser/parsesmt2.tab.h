/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 202 "/home/yue/Work/stp/lib/Parser/smt2.y" /* yacc.c:1909  */

  unsigned uintval; /* for numerals in types. */

  //ASTNode,ASTVec
  stp::ASTNode *node;
  stp::ASTVec *vec;

  std::string *str;

#line 177 "/home/yue/Work/stp/build/lib/Parser/parsesmt2.tab.h" /* yacc.c:1909  */
};

typedef union SMT2STYPE SMT2STYPE;
# define SMT2STYPE_IS_TRIVIAL 1
# define SMT2STYPE_IS_DECLARED 1
#endif


extern SMT2STYPE smt2lval;

int smt2parse (void);

#endif /* !YY_SMT2_HOME_YUE_WORK_STP_BUILD_LIB_PARSER_PARSESMT2_TAB_H_INCLUDED  */
