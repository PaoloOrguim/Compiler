%{
#include "lexical_value.h"
#include "asd.h"
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>    /* malloc, exit */
#include <string.h>    /* strdup */
int get_line_number(void);

void set_yylval(int token_type, char* value){
    valor_t *v = malloc(sizeof(valor_t));
    if (!v) {
        fprintf(stderr, "Erro de memória em set_yylval\n");
        exit(1);
    }
    v->line_number = yylineno;
    v->token_type  = token_type;
    v->token_val   = strdup(value);
    if (!v->token_val) {
        fprintf(stderr, "Erro de memória em strdup\n");
        //free(v);
        exit(1);
    }
    yylval.lex_val = v;
}
%}

%option noinput nounput
%option noyywrap
%option yylineno

%{
/* * * * * * * * * * * *
 * * * DEFINICOES * * *
 * * * * * * * * * * * */
%}

DIGITO      [0-9]
LETRA       [a-z_]
ID          {LETRA}({LETRA}|{DIGITO})*
FLOAT       ({DIGITO}+)?\.{DIGITO}+
INT         {DIGITO}+

%%

%{
/* * * * * * * * * 
 * * * REGRAS * * *
 * * * * * * * * */
%}

%{
/*paalvras reservadas, entre aspas para indicar correspondecia exata*/
%}

"as"            { return TK_PR_AS; }
"declare"       { return TK_PR_DECLARE; }
"else"          { return TK_PR_ELSE; }
"float"         { return TK_PR_FLOAT; }
"if"            { return TK_PR_IF; }
"int"           { return TK_PR_INT; }
"is"            { return TK_PR_IS; }
"return"        { return TK_PR_RETURN; }
"returns"       { return TK_PR_RETURNS; }
"while"         { return TK_PR_WHILE; }
"with"          { return TK_PR_WITH; }

%{
/* operadores compostos*/
%}

"<="            { return TK_OC_LE; }
">="            { return TK_OC_GE; }
"=="            { return TK_OC_EQ; }
"!="            { return TK_OC_NE; }

{FLOAT}         {
                    valor_t* aux = NULL;
                    aux = (valor_t*)malloc(sizeof(valor_t));
                    aux->token_type = TK_LI_FLOAT;
                    aux->line_number = get_line_number();
                    aux->token_val = strdup(yytext);
                    yylval.lex_val = aux;
                    return TK_LI_FLOAT;
                }

{INT}           {
                    valor_t* aux = NULL;
                    aux = (valor_t*)malloc(sizeof(valor_t));
                    aux->token_type = TK_LI_INT;
                    aux->line_number = get_line_number();
                    aux->token_val = strdup(yytext);
                    yylval.lex_val = aux;
                    return TK_LI_INT;
                }

{ID}            {
                    valor_t* aux = NULL;
                    aux = (valor_t*)malloc(sizeof(valor_t));
                    aux->token_type = TK_ID;
                    aux->line_number = get_line_number();
                    aux->token_val = strdup(yytext);
                    yylval.lex_val = aux;
                    return TK_ID;
                }

%{
/* Classe de caracteres especiais*/
%}

[!*/%+\-<>\[\]()=,;&|]   { return yytext[0]; }

%{
/* Ignorar comentarios que comecam por "//" e estao concatenados com qualquer coisa ate o fim da linha "."*/
%}

"//".*     

%{
/* Ignorar espacos vazios*/
%}     

[ \t\r]+        

\n    

%{
/* Qualquer coisa que nao se encaixa no resto retorna um token de erro. */
%}          

.               { return TK_ER; }

%%


/* * * * * * * * * 
 * * * CODIGO * * *
 * * * * * * * * */


/* Funcao autoexplicativa */
int get_line_number(void) {
    return yylineno;
}
