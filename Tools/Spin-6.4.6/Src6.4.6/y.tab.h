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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ASSERT = 258,
    PRINT = 259,
    PRINTM = 260,
    PREPROC = 261,
    C_CODE = 262,
    C_DECL = 263,
    C_EXPR = 264,
    C_STATE = 265,
    C_TRACK = 266,
    RUN = 267,
    LEN = 268,
    ENABLED = 269,
    SET_P = 270,
    GET_P = 271,
    EVAL = 272,
    PC_VAL = 273,
    TYPEDEF = 274,
    MTYPE = 275,
    INLINE = 276,
    RETURN = 277,
    LABEL = 278,
    OF = 279,
    GOTO = 280,
    BREAK = 281,
    ELSE = 282,
    SEMI = 283,
    ARROW = 284,
    IF = 285,
    FI = 286,
    DO = 287,
    OD = 288,
    FOR = 289,
    SELECT = 290,
    IN = 291,
    SEP = 292,
    DOTDOT = 293,
    ATOMIC = 294,
    NON_ATOMIC = 295,
    D_STEP = 296,
    UNLESS = 297,
    TIMEOUT = 298,
    NONPROGRESS = 299,
    ACTIVE = 300,
    PROCTYPE = 301,
    D_PROCTYPE = 302,
    HIDDEN = 303,
    SHOW = 304,
    ISLOCAL = 305,
    PRIORITY = 306,
    PROVIDED = 307,
    FULL = 308,
    EMPTY = 309,
    NFULL = 310,
    NEMPTY = 311,
    CONST = 312,
    TYPE = 313,
    XU = 314,
    NAME = 315,
    UNAME = 316,
    PNAME = 317,
    INAME = 318,
    STRING = 319,
    CLAIM = 320,
    TRACE = 321,
    INIT = 322,
    LTL = 323,
    ASGN = 324,
    SND = 325,
    O_SND = 326,
    RCV = 327,
    R_RCV = 328,
    IMPLIES = 329,
    EQUIV = 330,
    OR = 331,
    AND = 332,
    ALWAYS = 333,
    EVENTUALLY = 334,
    UNTIL = 335,
    WEAK_UNTIL = 336,
    RELEASE = 337,
    NEXT = 338,
    EQ = 339,
    NE = 340,
    GT = 341,
    LT = 342,
    GE = 343,
    LE = 344,
    LSHIFT = 345,
    RSHIFT = 346,
    INCR = 347,
    DECR = 348,
    UMIN = 349,
    NEG = 350,
    DOT = 351
  };
#endif
/* Tokens.  */
#define ASSERT 258
#define PRINT 259
#define PRINTM 260
#define PREPROC 261
#define C_CODE 262
#define C_DECL 263
#define C_EXPR 264
#define C_STATE 265
#define C_TRACK 266
#define RUN 267
#define LEN 268
#define ENABLED 269
#define SET_P 270
#define GET_P 271
#define EVAL 272
#define PC_VAL 273
#define TYPEDEF 274
#define MTYPE 275
#define INLINE 276
#define RETURN 277
#define LABEL 278
#define OF 279
#define GOTO 280
#define BREAK 281
#define ELSE 282
#define SEMI 283
#define ARROW 284
#define IF 285
#define FI 286
#define DO 287
#define OD 288
#define FOR 289
#define SELECT 290
#define IN 291
#define SEP 292
#define DOTDOT 293
#define ATOMIC 294
#define NON_ATOMIC 295
#define D_STEP 296
#define UNLESS 297
#define TIMEOUT 298
#define NONPROGRESS 299
#define ACTIVE 300
#define PROCTYPE 301
#define D_PROCTYPE 302
#define HIDDEN 303
#define SHOW 304
#define ISLOCAL 305
#define PRIORITY 306
#define PROVIDED 307
#define FULL 308
#define EMPTY 309
#define NFULL 310
#define NEMPTY 311
#define CONST 312
#define TYPE 313
#define XU 314
#define NAME 315
#define UNAME 316
#define PNAME 317
#define INAME 318
#define STRING 319
#define CLAIM 320
#define TRACE 321
#define INIT 322
#define LTL 323
#define ASGN 324
#define SND 325
#define O_SND 326
#define RCV 327
#define R_RCV 328
#define IMPLIES 329
#define EQUIV 330
#define OR 331
#define AND 332
#define ALWAYS 333
#define EVENTUALLY 334
#define UNTIL 335
#define WEAK_UNTIL 336
#define RELEASE 337
#define NEXT 338
#define EQ 339
#define NE 340
#define GT 341
#define LT 342
#define GE 343
#define LE 344
#define LSHIFT 345
#define RSHIFT 346
#define INCR 347
#define DECR 348
#define UMIN 349
#define NEG 350
#define DOT 351

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
