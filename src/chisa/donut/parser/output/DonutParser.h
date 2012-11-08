/** \file
 *  This C header file was generated by $ANTLR version 3.4
 *
 *     -  From the grammar source file : /home/psi/Dropbox/src/chisa/src/chisa/donut/parser/Donut.g
 *     -                            On : 2012-11-08 22:26:29
 *     -                for the parser : DonutParserParser
 *
 * Editing it, at least manually, is not wise.
 *
 * C language generator and runtime by Jim Idle, jimi|hereisanat|idle|dotgoeshere|ws.
 *
 *
 * The parser 
DonutParser

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
 * a parser context typedef pDonutParser, which is returned from a call to DonutParserNew().
 *
 * The methods in pDonutParser are  as follows:
 *
 *  - 
 DonutParser_source_return
      pDonutParser->source(pDonutParser)
 *  - 
 DonutParser_program_return
      pDonutParser->program(pDonutParser)
 *  - 
 DonutParser_exprlist_return
      pDonutParser->exprlist(pDonutParser)
 *  - 
 DonutParser_expr_return
      pDonutParser->expr(pDonutParser)
 *  - 
 DonutParser_expr6_return
      pDonutParser->expr6(pDonutParser)
 *  - 
 DonutParser_expr5_return
      pDonutParser->expr5(pDonutParser)
 *  - 
 DonutParser_expr4_return
      pDonutParser->expr4(pDonutParser)
 *  - 
 DonutParser_expr3_return
      pDonutParser->expr3(pDonutParser)
 *  - 
 DonutParser_expr2_return
      pDonutParser->expr2(pDonutParser)
 *  - 
 DonutParser_expr1_return
      pDonutParser->expr1(pDonutParser)
 *  - 
 DonutParser_term_return
      pDonutParser->term(pDonutParser)
 *  - 
 DonutParser_postfix_return
      pDonutParser->postfix(pDonutParser)
 *  - 
 DonutParser_primary_return
      pDonutParser->primary(pDonutParser)
 *  - 
 DonutParser_name_return
      pDonutParser->name(pDonutParser)
 *  - 
 DonutParser_varlist_return
      pDonutParser->varlist(pDonutParser)
 *  - 
 DonutParser_arglist_return
      pDonutParser->arglist(pDonutParser)
 *  - 
 DonutParser_array_return
      pDonutParser->array(pDonutParser)
 *  - 
 DonutParser_exprlist_for_literal_return
      pDonutParser->exprlist_for_literal(pDonutParser)
 *  - 
 DonutParser_object_return
      pDonutParser->object(pDonutParser)
 *  - 
 DonutParser_object_pair_return
      pDonutParser->object_pair(pDonutParser)
 *  - 
 DonutParser_literal_return
      pDonutParser->literal(pDonutParser)
 *  - 
 DonutParser_boolean_literal_return
      pDonutParser->boolean_literal(pDonutParser)
 *  - 
 DonutParser_numeric_literal_return
      pDonutParser->numeric_literal(pDonutParser)
 *  - 
 DonutParser_string_literal_return
      pDonutParser->string_literal(pDonutParser)
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

#ifndef	_DonutParser_H
#define _DonutParser_H
/* =============================================================================
 * Standard antlr3 C runtime definitions
 */
#include    <antlr3.h>

/* End of standard antlr 3 runtime definitions
 * =============================================================================
 */

#undef __cplusplus
#undef LT


#ifdef __cplusplus
extern "C" {
#endif

// Forward declare the context typedef so that we can use it before it is
// properly defined. Delegators and delegates (from import statements) are
// interdependent and their context structures contain pointers to each other
// C only allows such things to be declared if you pre-declare the typedef.
//
typedef struct DonutParser_Ctx_struct DonutParser, * pDonutParser;



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
typedef struct DonutParser_source_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_source_return;



typedef struct DonutParser_program_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_program_return;



typedef struct DonutParser_exprlist_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_exprlist_return;



typedef struct DonutParser_expr_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_expr_return;



typedef struct DonutParser_expr6_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_expr6_return;



typedef struct DonutParser_expr5_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_expr5_return;



typedef struct DonutParser_expr4_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_expr4_return;



typedef struct DonutParser_expr3_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_expr3_return;



typedef struct DonutParser_expr2_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_expr2_return;



typedef struct DonutParser_expr1_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_expr1_return;



typedef struct DonutParser_term_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_term_return;



typedef struct DonutParser_postfix_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_postfix_return;



typedef struct DonutParser_primary_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_primary_return;



typedef struct DonutParser_name_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_name_return;



typedef struct DonutParser_varlist_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_varlist_return;



typedef struct DonutParser_arglist_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_arglist_return;



typedef struct DonutParser_array_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_array_return;



typedef struct DonutParser_exprlist_for_literal_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_exprlist_for_literal_return;



typedef struct DonutParser_object_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_object_return;



typedef struct DonutParser_object_pair_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_object_pair_return;



typedef struct DonutParser_literal_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_literal_return;



typedef struct DonutParser_boolean_literal_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_boolean_literal_return;



typedef struct DonutParser_numeric_literal_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_numeric_literal_return;



typedef struct DonutParser_string_literal_return_struct
{
    /** Generic return elements for ANTLR3 rules that are not in tree parsers or returning trees
     */
    pANTLR3_COMMON_TOKEN    start;
    pANTLR3_COMMON_TOKEN    stop;
    pANTLR3_BASE_TREE	tree;

}
    DonutParser_string_literal_return;




/** Context tracking structure for 
DonutParser

 */
struct DonutParser_Ctx_struct
{
    /** Built in ANTLR3 context tracker contains all the generic elements
     *  required for context tracking.
     */
    pANTLR3_PARSER   pParser;

     DonutParser_source_return
     (*source)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_program_return
     (*program)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_exprlist_return
     (*exprlist)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_expr_return
     (*expr)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_expr6_return
     (*expr6)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_expr5_return
     (*expr5)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_expr4_return
     (*expr4)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_expr3_return
     (*expr3)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_expr2_return
     (*expr2)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_expr1_return
     (*expr1)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_term_return
     (*term)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_postfix_return
     (*postfix)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_primary_return
     (*primary)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_name_return
     (*name)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_varlist_return
     (*varlist)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_arglist_return
     (*arglist)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_array_return
     (*array)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_exprlist_for_literal_return
     (*exprlist_for_literal)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_object_return
     (*object)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_object_pair_return
     (*object_pair)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_literal_return
     (*literal)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_boolean_literal_return
     (*boolean_literal)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_numeric_literal_return
     (*numeric_literal)	(struct DonutParser_Ctx_struct * ctx);

     DonutParser_string_literal_return
     (*string_literal)	(struct DonutParser_Ctx_struct * ctx);
    // Delegated rules

    const char * (*getGrammarFileName)();
    void            (*reset)  (struct DonutParser_Ctx_struct * ctx);
    void	    (*free)   (struct DonutParser_Ctx_struct * ctx);
/* @headerFile.members() */
pANTLR3_BASE_TREE_ADAPTOR	adaptor;
pANTLR3_VECTOR_FACTORY		vectors;
/* End @headerFile.members() */
};

// Function protoypes for the constructor functions that external translation units
// such as delegators and delegates may wish to call.
//
ANTLR3_API pDonutParser DonutParserNew         (
pANTLR3_COMMON_TOKEN_STREAM
 instream);
ANTLR3_API pDonutParser DonutParserNewSSD      (
pANTLR3_COMMON_TOKEN_STREAM
 instream, pANTLR3_RECOGNIZER_SHARED_STATE state);

/** Symbolic definitions of all the tokens that the 
parser
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

/* End of token definitions for DonutParser
 * =============================================================================
 */
/** } */

#ifdef __cplusplus
}
#endif

#endif

/* END - Note:Keep extra line feed to satisfy UNIX systems */
