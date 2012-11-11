/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : /home/psi/Dropbox/src/chisa/src/chisa/donut/parser/Donut.g
 *     -                            On : 2012-11-11 17:56:01
 *     -                 for the lexer : DonutLexerLexer
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The lexer 
DonutLexer

has the callable functions (rules) shown below,
 * which will invoke the code for the associated rule in the source grammar
 * assuming that the input stream is pointing to a token/text stream that could begin
 * this rule.
 *
 * For instance if you call the first (topmost) rule in a parser grammar, you will
 * get the results of a full parse, but calling a rule half way through the grammar will
 * allow you to pass part of a full token stream to the parser, such as for syntax checking
 * in editors and so on.
 *
 * The parser entry points are called indirectly (by function pointer to function) via
 * a parser context typedef pDonutLexer, which is returned from a call to DonutLexerNew().
 *
 * As this is a generated lexer, it is unlikely you will call it 'manually'. However
 * the methods are provided anyway.
 *
 * The methods in pDonutLexer are  as follows:
 *
 *  - 
 void
      pDonutLexer->T__53(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__54(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__55(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__56(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__57(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__58(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__59(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__60(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__61(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__62(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__63(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__64(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__65(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__66(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__67(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__68(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__69(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__70(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__71(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__72(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__73(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__74(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__75(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__76(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__77(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__78(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__79(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__80(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__81(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__82(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__83(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__84(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__85(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__86(pDonutLexer)
 *  - 
 void
      pDonutLexer->T__87(pDonutLexer)
 *  - 
 void
      pDonutLexer->IDENT(pDonutLexer)
 *  - 
 void
      pDonutLexer->LETTER(pDonutLexer)
 *  - 
 void
      pDonutLexer->STRING_SINGLE(pDonutLexer)
 *  - 
 void
      pDonutLexer->STRING_SINGLE_ELEMENT(pDonutLexer)
 *  - 
 void
      pDonutLexer->STRING_DOUBLE(pDonutLexer)
 *  - 
 void
      pDonutLexer->STRING_DOUBLE_ELEMENT(pDonutLexer)
 *  - 
 void
      pDonutLexer->ESC_SEQ(pDonutLexer)
 *  - 
 void
      pDonutLexer->HEX_LITERAL(pDonutLexer)
 *  - 
 void
      pDonutLexer->OCT_LITERAL(pDonutLexer)
 *  - 
 void
      pDonutLexer->INT_LITERAL(pDonutLexer)
 *  - 
 void
      pDonutLexer->FLOAT_LITERAL(pDonutLexer)
 *  - 
 void
      pDonutLexer->DIGIT(pDonutLexer)
 *  - 
 void
      pDonutLexer->NONZERO_DIGIT(pDonutLexer)
 *  - 
 void
      pDonutLexer->EXPONENT(pDonutLexer)
 *  - 
 void
      pDonutLexer->HEX_DIGIT(pDonutLexer)
 *  - 
 void
      pDonutLexer->OCT_DIGIT(pDonutLexer)
 *  - 
 void
      pDonutLexer->COMMENT(pDonutLexer)
 *  - 
 void
      pDonutLexer->WS(pDonutLexer)
 *  - 
 void
      pDonutLexer->Tokens(pDonutLexer)
 *
 * The return type for any particular rule is of course determined by the source
 * grammar file.
 */
// [The "BSD license"]
// Copyright (c) 2005-2009 Jim Idle, Temporal Wave LLC
// http://www.temporal-wave.com
// http://www.linkedin.com/in/jimidle
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//    derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef	_DonutLexer_H
#define _DonutLexer_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct DonutLexer_Ctx_struct DonutLexer, * pDonutLexer;



#ifdef	ANTLR3_WINDOWS
// Disable: Unreferenced parameter,							- Rules with parameters that are not used
//          constant conditional,							- ANTLR realizes that a prediction is always true (synpred usually)
//          initialized but unused variable					- tree rewrite variables declared but not needed
//          Unreferenced local variable						- lexer rule declares but does not always use _type
//          potentially unitialized variable used			- retval always returned from a rule
//			unreferenced local function has been removed	- susually getTokenNames or freeScope, they can go without warnigns
//
// These are only really displayed at warning level /W4 but that is the code ideal I am aiming at
// and the codegen must generate some of these warnings by necessity, apart from 4100, which is
// usually generated when a parser rule is given a parameter that it does not use. Mostly though
// this is a matter of orthogonality hence I disable that one.
//
#pragma warning( disable : 4100 )
#pragma warning( disable : 4101 )
#pragma warning( disable : 4127 )
#pragma warning( disable : 4189 )
#pragma warning( disable : 4505 )
#pragma warning( disable : 4701 )
#endif

/** Context tracking structure for 
DonutLexer

 */
struct DonutLexer_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_LEXER    pLexer;

     void
     (*mT__53)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__54)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__55)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__56)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__57)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__58)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__59)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__60)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__61)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__62)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__63)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__64)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__65)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__66)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__67)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__68)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__69)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__70)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__71)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__72)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__73)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__74)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__75)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__76)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__77)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__78)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__79)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__80)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__81)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__82)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__83)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__84)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__85)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__86)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mT__87)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mIDENT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mLETTER)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mSTRING_SINGLE)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mSTRING_SINGLE_ELEMENT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mSTRING_DOUBLE)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mSTRING_DOUBLE_ELEMENT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mESC_SEQ)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mHEX_LITERAL)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mOCT_LITERAL)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mINT_LITERAL)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mFLOAT_LITERAL)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mDIGIT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mNONZERO_DIGIT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mEXPONENT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mHEX_DIGIT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mOCT_DIGIT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mCOMMENT)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mWS)	(struct DonutLexer_Ctx_struct * ctx);

     void
     (*mTokens)	(struct DonutLexer_Ctx_struct * ctx);
    const char * (*getGrammarFileName)();
    void            (*reset)  (struct DonutLexer_Ctx_struct * ctx);
    void	    (*free)   (struct DonutLexer_Ctx_struct * ctx);
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pDonutLexer DonutLexerNew         (
pANTLR3_INPUT_STREAM
 instream);
ANTLR3_API pDonutLexer DonutLexerNewSSD      (
pANTLR3_INPUT_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
lexer
 will work with.
 * \{
 *
 * Antlr will define EOF, but we can't use that as it it is too common in
 * in C header files and that would be confusing. There is no way to filter this out at the moment
 * so we just undef it here for now. That isn't the value we get back from C recognizers
 * anyway. We are looking for ANTLR3_TOKEN_EOF.
 */
#ifdef	EOF
#undef	EOF
#endif
#ifdef	Tokens
#undef	Tokens
#endif
#define EOF      -1
#define T__53      53
#define T__54      54
#define T__55      55
#define T__56      56
#define T__57      57
#define T__58      58
#define T__59      59
#define T__60      60
#define T__61      61
#define T__62      62
#define T__63      63
#define T__64      64
#define T__65      65
#define T__66      66
#define T__67      67
#define T__68      68
#define T__69      69
#define T__70      70
#define T__71      71
#define T__72      72
#define T__73      73
#define T__74      74
#define T__75      75
#define T__76      76
#define T__77      77
#define T__78      78
#define T__79      79
#define T__80      80
#define T__81      81
#define T__82      82
#define T__83      83
#define T__84      84
#define T__85      85
#define T__86      86
#define T__87      87
#define ADD      4
#define AND      5
#define APPLY      6
#define ARGS      7
#define ARRAY      8
#define ASSIGN      9
#define ASSIGN_OP      10
#define CEQ      11
#define CGE      12
#define CGT      13
#define CLE      14
#define CLOS      15
#define CLT      16
#define CNE      17
#define COMMENT      18
#define CONT      19
#define DIGIT      20
#define DIV      21
#define DOT      22
#define ESC_SEQ      23
#define EXPONENT      24
#define FLOAT_LITERAL      25
#define HEX_DIGIT      26
#define HEX_LITERAL      27
#define IDENT      28
#define IDX      29
#define INT_LITERAL      30
#define LETTER      31
#define MINUS      32
#define MOD      33
#define MUL      34
#define NONZERO_DIGIT      35
#define NOT      36
#define OBJECT      37
#define OCT_DIGIT      38
#define OCT_LITERAL      39
#define OR      40
#define PAIR      41
#define PLUS      42
#define POST_OP      43
#define PRE_OP      44
#define SCOPE      45
#define STRING_DOUBLE      46
#define STRING_DOUBLE_ELEMENT      47
#define STRING_SINGLE      48
#define STRING_SINGLE_ELEMENT      49
#define SUB      50
#define VARS      51
#define WS      52
#ifdef	EOF
#undef	EOF
#define	EOF	ANTLR3_TOKEN_EOF
#endif

#ifndef TOKENSOURCE
#define TOKENSOURCE(lxr) lxr->pLexer->rec->state->tokSource
#endif

/* End of token definitions for DonutLexer
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */