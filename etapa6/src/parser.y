%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "asd.h"
    #include "lexical_value.h"     /* struct valor_t */
    #include "tables.h"            /* entries, table and stack related code */
    #include "../headers/errors.h" /* error codes */
    #include "iloc.h"              // Include iloc.h

    #define PLACEHOLDER 0

    extern asd_tree_t *arvore;   /* raiz da AST */

    extern struct table *global_scope; // Variável externa para o escopo global (Etapa 6)

    struct table_stack *stack = NULL; // Pilha de tabelas
    int variable_type = 0; // Tipo da variavel
    int function_type = 0; // Tipo da funcao
    static struct entry *current_func_entry_for_params = NULL;
    int arg_list_count = 0; // Contador de argumentos da funcao sendo chamada
    int temp_params[128] = {0};

    extern int yylex(void);      /* corrigir erro zoado*/

    int get_line_number(void);

    void yyerror (const char *mensagem);
%}

%define parse.error verbose

%union {
  valor_t    *lex_val;  /* para TK_ID e literais */
  asd_tree_t *no_ast;      /* para os nós da AST */
}

%token TK_PR_AS TK_PR_DECLARE TK_PR_ELSE TK_PR_FLOAT TK_PR_IF TK_PR_INT TK_PR_IS TK_PR_RETURN
%token TK_PR_RETURNS TK_PR_WHILE TK_PR_WITH TK_OC_LE TK_OC_GE TK_OC_EQ TK_OC_NE
%token <lex_val> TK_ID TK_LI_INT TK_LI_FLOAT
%token TK_ER

%type<no_ast> programa lista elemento def_func decl_var_global header tipo header_head
%type<no_ast> pre_param_list param_list parameter body command_block simple_command_list simple_command
%type<no_ast> init decl_var attribution call_func arg_list return_command
%type<no_ast> flow_ctrl conditional while expressao
%type<no_ast> n7 n6 n5 n4 n3 n2 n1 n0
%type<no_ast> push_table pop_table tipo_funcao

%%

programa
    : /*vazio*/                                     { $$ = NULL; arvore = $$; }
    | push_table lista pop_table ';'                { $$ = $2; arvore = $$; }
    ;

lista
    : elemento                                      { $$ = $1; }
    | elemento ',' lista                            {
                                                        if ($1 == NULL){ $$ = $3; }
                                                        else if($3 == NULL){ $$ = $1; }
                                                        else {
                                                            $$ = $1;
                                                            asd_add_child($$, $3);
                                                            if ($$->code && $3->code) {
                                                                iloc_list_concat($$->code, $3->code);
                                                                $3->code = NULL; // FIX: Transfer ownership
                                                            }
                                                        }
                                                    }
    ;

elemento
    : def_func                                      { $$ = $1; }
    | decl_var_global                               { $$ = $1; }
    ;

def_func
    : header TK_PR_IS body pop_table                {
                                                        $$ = asd_new($1->label, function_type);
                                                        $$->code = $1->code;
                                                        $1->code = NULL;

                                                        if ($3 != NULL){
                                                            asd_add_child($$, $3);
                                                            if ($3->code) {
                                                                iloc_list_concat($$->code, $3->code);
                                                                $3->code = NULL; // FIX: Transfer ownership
                                                            }
                                                        }
                                                        asd_free($1);
                                                    }
    ;

decl_var_global
    : TK_PR_DECLARE TK_ID TK_PR_AS tipo             {
                                                        char *name = $2->token_val;
                                                        if(search_entry(stack->top, name) != NULL){
                                                            semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                        } else{
                                                            int var_offset = stack->top->current_offset;
                                                            stack->top->current_offset += 4;

                                                            valor_t v;
                                                            v.line_number = get_line_number();
                                                            v.token_type = TK_ID;
                                                            v.token_val = strdup(name);
                                                            struct entry e = create_entry( get_line_number(), var_offset, 1, NATURE_VAR, variable_type, v, 0, NULL );
                                                            add_entry(stack->top, &e);
                                                            free(v.token_val);
                                                        }
                                                        $$ = NULL;
                                                        if ($2){ free($2->token_val); free($2); }
                                                    }
    ;

header
    : header_head push_table pre_param_list         {
                                                        $$ = $1;
                                                        if ($3 != NULL) {
                                                           asd_add_child($$, $3);
                                                        }
                                                    }
    | header_head push_table                        { $$ = $1; }
    ;

header_head
    : TK_ID TK_PR_RETURNS tipo_funcao               {
                                                        char *fname = $1->token_val;
                                                        if (search_entry(stack->top, fname) != NULL){
                                                            semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", get_line_number());
                                                        } else{
                                                            valor_t v;
                                                            v.line_number = get_line_number();
                                                            v.token_type = TK_ID;
                                                            v.token_val = strdup(fname);
                                                            struct entry e = create_entry( get_line_number(), 0, 0, NATURE_FUNC, function_type, v, 0, NULL );
                                                            add_entry(stack->top, &e);
                                                            free(v.token_val);
                                                        }
                                                        current_func_entry_for_params = search_entry(stack->top, fname);
                                                        $$ = asd_new($1->token_val, function_type);
                                                        $$->code = iloc_list_new();
                                                        char *func_label;
                                                        asprintf(&func_label, "%s", fname);
                                                        iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, func_label, "Function entry"));
                                                        free(func_label);

                                                        if($1){ free($1->token_val); free($1); }
                                                    }
    ;

tipo
    : TK_PR_FLOAT                                   { $$ = NULL; variable_type = TYPE_FLOAT; }
    | TK_PR_INT                                     { $$ = NULL; variable_type = TYPE_INT; }
    ;

tipo_funcao
    : TK_PR_FLOAT                                   { $$ = NULL; function_type = TYPE_FLOAT; }
    | TK_PR_INT                                     { $$ = NULL; function_type = TYPE_INT; }
    ;

pre_param_list
    : TK_PR_WITH param_list                         { $$ = $2; }
    ;

param_list
    : parameter                                     { $$ = $1; }
    | parameter ',' param_list                      { $$ = $1; asd_add_child($$, $3); }
    ;

parameter
    : TK_ID TK_PR_AS tipo                           {
                                                        char *pname = $1->token_val;
                                                        if(search_entry(stack->top, pname) != NULL){
                                                            semantic_error(ERR_DECLARED, "Dois parametros com o mesmo nome.", get_line_number());
                                                        }
                                                        int param_offset = stack->top->current_offset;
                                                        stack->top->current_offset += 4;

                                                        valor_t v;
                                                        v.line_number = get_line_number();
                                                        v.token_type = TK_ID;
                                                        v.token_val = strdup(pname);
                                                        struct entry e = create_entry( get_line_number(), param_offset, 0, NATURE_VAR, variable_type, v, 0, NULL );
                                                        add_entry(stack->top, &e);
                                                        free(v.token_val);

                                                        struct entry *fe = current_func_entry_for_params;
                                                        fe->num_params++;
                                                        fe->params = realloc(fe->params, fe->num_params * sizeof *fe->params);
                                                        if (!fe->params) exit(1);
                                                        fe->params[ fe->num_params - 1 ].type = variable_type;

                                                        $$ = asd_new($1->token_val, variable_type);
                                                        
                                                        if($1){ free($1->token_val); free($1); }
                                                    }
    ;

body
    : command_block                                 { $$ = $1; }
    ;

command_block
    : '[' simple_command_list ']'                   { $$ = $2; }
    ;

simple_command_list
    : /*nothingness*/                               { $$ = NULL; }
    | simple_command simple_command_list            {
                                                        if($1 == NULL){ $$ = $2; }
                                                        else if($2 == NULL){ $$ = $1; }
                                                        else {
                                                            $$ = $1;
                                                            asd_add_child($$, $2);
                                                            if ($$->code && $2->code) {
                                                                iloc_list_concat($$->code, $2->code);
                                                                $2->code = NULL; // FIX: Transfer ownership
                                                            }
                                                        }
                                                    }
    ;

simple_command
    : push_table command_block pop_table            { $$ = $2; }
    | decl_var                                      { $$ = $1; }
    | attribution                                   { $$ = $1; }
    | call_func                                     { $$ = $1; }
    | return_command                                { $$ = $1; }
    | flow_ctrl                                     { $$ = $1; }
    ;

init
    : TK_PR_WITH TK_LI_INT                          {
                                                        $$ = asd_new($2->token_val, TYPE_INT);
                                                        $$->code = iloc_list_new();
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_op_t *load_const_op = iloc_op_new("loadI", iloc_operand_new_const(atoi($2->token_val)), NULL, iloc_operand_new_reg($$->temp), NULL, NULL, "Load integer literal");
                                                        iloc_list_add($$->code, load_const_op);
                                                        if ($2){ free($2->token_val); free($2); }
                                                    }
    | TK_PR_WITH TK_LI_FLOAT                        {
                                                        $$ = asd_new($2->token_val, TYPE_FLOAT);
                                                        $$->code = iloc_list_new();
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_op_t *load_const_op = iloc_op_new("loadI", iloc_operand_new_const((int)atof($2->token_val)), NULL, iloc_operand_new_reg($$->temp), NULL, NULL, "Load float literal");
                                                        iloc_list_add($$->code, load_const_op);
                                                        if ($2){ free($2->token_val); free($2); }
                                                    }
    | /*nada*/                                      { $$ = NULL;}
    ;

decl_var
    : TK_PR_DECLARE TK_ID TK_PR_AS tipo init        {
                                                        char *varname = $2->token_val;
                                                        if(search_entry(stack->top, varname) != NULL){
                                                            semantic_error(ERR_DECLARED, "Identificador ja declarado neste escopo", $2->line_number);
                                                        }
                                                        if ($5 != NULL && variable_type != $5->type){
                                                            semantic_error(ERR_WRONG_TYPE, "Tipo de variavel diferente do tipo da inicializacao", get_line_number());
                                                        }

                                                        int var_offset = stack->top->current_offset;
                                                        stack->top->current_offset += 4;

                                                        valor_t v;
                                                        v.line_number = $2->line_number;
                                                        v.token_type = TK_ID;
                                                        v.token_val = strdup(varname);
                                                        struct entry e = create_entry( $2->line_number, var_offset, 0, NATURE_VAR, variable_type, v, 0, NULL );
                                                        add_entry(stack->top, &e);
                                                        free(v.token_val);

                                                        if($5 != NULL) {
                                                            $$ = asd_new("with", variable_type);
                                                            asd_add_child($$, asd_new(varname, variable_type));
                                                            asd_add_child($$, $5);
                                                            $$->code = $5->code;
                                                            $5->code = NULL;
                                                            char *store_comment;
                                                            asprintf(&store_comment, "Store initial value for %s", varname);
                                                            iloc_op_t *store_op = iloc_op_new("storeAI", iloc_operand_new_reg($5->temp), NULL, iloc_operand_new_reg("rfp"), iloc_operand_new_const(var_offset), NULL, store_comment);
                                                            iloc_list_add($$->code, store_op);
                                                            free(store_comment);
                                                            free($5->temp);
                                                            $5->temp = NULL;
                                                        } else {
                                                            $$ = NULL;
                                                        }

                                                        if($2){ free($2->token_val); free($2);}
                                                    }
    ;

attribution
    : TK_ID TK_PR_IS expressao                      {
                                                        char *varname = $1->token_val;
                                                        struct entry *e = search_entry_in_stack(stack, varname);
                                                        if(e == NULL){ semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number); }
                                                        if(e->nature == NATURE_FUNC){ semantic_error(ERR_FUNCTION, "Tentativa de fazer atribuicao em funcao", $1->line_number); }
                                                        if (e->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Tipo de variavel diferente do tipo da atribuicao", $1->line_number); }

                                                        $$ = asd_new("is", e->type);
                                                        asd_add_child($$, asd_new($1->token_val, e->type));
                                                        asd_add_child($$, $3);

                                                        const char* base_reg = (e->is_global) ? "rbss" : "rfp";
                                                        $$->code = $3->code;
                                                        $3->code = NULL;
                                                        char *store_comment;
                                                        asprintf(&store_comment, "Store value for %s", varname);
                                                        iloc_op_t *store_op = iloc_op_new("storeAI", iloc_operand_new_reg($3->temp), NULL, iloc_operand_new_reg(base_reg), iloc_operand_new_const(e->offset), NULL, store_comment);
                                                        iloc_list_add($$->code, store_op);
                                                        free(store_comment);
                                                        free($3->temp);
                                                        $3->temp = NULL;

                                                        if($1){ free($1->token_val); free($1); }
                                                    }
    ;

call_func
    : TK_ID '(' arg_list ')'                        {
                                                        char *fname = $1->token_val;
                                                        struct entry *e = search_entry_in_stack(stack, fname);
                                                        if(e == NULL){ semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number); }
                                                        if(e->nature == NATURE_VAR){ semantic_error(ERR_VARIABLE, "Erro: variavel sendo usada como funcao", $1->line_number); }
                                                        if (e->num_params < arg_list_count){ semantic_error(ERR_EXCESS_ARGS, "Erro: chamada de funcao com excesso de parametros.", $1->line_number); }
                                                        if (e->num_params > arg_list_count){ semantic_error(ERR_MISSING_ARGS, "Erro: chamada de funcao faltando parametros.", $1->line_number); }
                                                        for (int i = 0; i < e->num_params; i++) {
                                                            if (e->params[i].type != temp_params[e->num_params - i - 1]) {
                                                                semantic_error(ERR_WRONG_TYPE_ARGS, "Erro: tipo de parametro passado diferente do tipo do parametro da funcao", $1->line_number);
                                                            }
                                                        }
                                                        for (int i = 0; i < 32; i++) { temp_params[i] = 0; }
                                                        arg_list_count = 0;

                                                        char *nome_da_funcao;
                                                        asprintf(&nome_da_funcao, "call %s", $1->token_val);
                                                        $$ = asd_new(nome_da_funcao, e->type);
                                                        free(nome_da_funcao);
                                                        asd_add_child($$, $3);

                                                        $$->code = $3->code;
                                                        $3->code = NULL;
                                                        iloc_op_t *call_op = iloc_op_new("jumpI", NULL, NULL, iloc_operand_new_label(fname), NULL, NULL, "Call function");
                                                        iloc_list_add($$->code, call_op);
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_op_t *mov_ret_op = iloc_op_new("i2i", iloc_operand_new_reg("r_ret"), NULL, iloc_operand_new_reg($$->temp), NULL, NULL, "Move return value to temp");
                                                        iloc_list_add($$->code, mov_ret_op);

                                                        if($1){ free($1->token_val); free($1); };
                                                    }
    | TK_ID '(' ')'                                 {
                                                        char *fname = $1->token_val;
                                                        struct entry *e = search_entry_in_stack(stack, fname);
                                                        if(e == NULL){ semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number); }
                                                        if(e->nature == NATURE_VAR){ semantic_error(ERR_VARIABLE, "Erro: variavel sendo usada como funcao", $1->line_number); }
                                                        if (e->num_params > 0){ semantic_error(ERR_MISSING_ARGS, "Erro: chamada de funcao faltando parametros", $1->line_number); }
                                                        
                                                        char *nome_da_funcao;
                                                        asprintf(&nome_da_funcao, "call %s", $1->token_val);
                                                        $$ = asd_new(nome_da_funcao, e->type);
                                                        free(nome_da_funcao);

                                                        $$->code = iloc_list_new();
                                                        iloc_op_t *call_op = iloc_op_new("jumpI", NULL, NULL, iloc_operand_new_label(fname), NULL, NULL, "Call function");
                                                        iloc_list_add($$->code, call_op);
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_op_t *mov_ret_op = iloc_op_new("i2i", iloc_operand_new_reg("r_ret"), NULL, iloc_operand_new_reg($$->temp), NULL, NULL, "Move return value to temp");
                                                        iloc_list_add($$->code, mov_ret_op);

                                                        if($1){ free($1->token_val); free($1); };
                                                    }
    ;

arg_list
    : expressao                                     {
                                                        temp_params[arg_list_count] = $1->type;
                                                        arg_list_count++;
                                                        $$ = $1;
                                                    }
    | expressao ',' arg_list                        {
                                                        temp_params[arg_list_count] = $1->type;
                                                        arg_list_count++;
                                                        $$ = $1;
                                                        asd_add_child($$, $3);
                                                        if($$->code && $3->code) {
                                                            iloc_list_concat($$->code, $3->code);
                                                            $3->code = NULL; // FIX: Transfer ownership
                                                        }
                                                    }
    ;

return_command
    : TK_PR_RETURN expressao TK_PR_AS tipo          {
                                                        if (function_type != variable_type){ semantic_error(ERR_WRONG_TYPE, "Tipo de retorno diferente do tipo da funcao", get_line_number()); }
                                                        if (function_type != $2->type){ semantic_error(ERR_WRONG_TYPE, "Tipo expressao retornada diferente do tipo da funcao", get_line_number()); }
                                                        
                                                        $$ = asd_new("return", function_type);
                                                        asd_add_child($$, $2);
                                                        $$->code = $2->code;
                                                        $2->code = NULL;
                                                        iloc_op_t *ret_op = iloc_op_new("i2i", iloc_operand_new_reg($2->temp), NULL, iloc_operand_new_reg("r_ret"), NULL, NULL, "Set return value");
                                                        iloc_list_add($$->code, ret_op);
                                                        free($2->temp);
                                                        $2->temp = NULL;
                                                    }
    ;

flow_ctrl
    : conditional                                   { $$ = $1; }
    | while                                         { $$ = $1; }
    ;

conditional
    : TK_PR_IF '(' expressao ')' push_table command_block pop_table         {
                                                                                $$ = asd_new("if", $3->type);
                                                                                asd_add_child($$, $3);
                                                                                if($6 != NULL){ asd_add_child($$, $6); }

                                                                                char *label_if_body = iloc_new_label();
                                                                                char *label_end_if = iloc_new_label();
                                                                                
                                                                                $$->code = $3->code;
                                                                                $3->code = NULL;
                                                                                iloc_op_t *cbr_op = iloc_op_new("cbr", iloc_operand_new_reg($3->temp), NULL, iloc_operand_new_label(label_if_body), iloc_operand_new_label(label_end_if), NULL, "Conditional branch (if)");
                                                                                iloc_list_add($$->code, cbr_op);
                                                                                free($3->temp);
                                                                                $3->temp = NULL;

                                                                                iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_if_body, "If block start"));
                                                                                if ($6 != NULL && $6->code) { 
                                                                                    iloc_list_concat($$->code, $6->code); 
                                                                                    $6->code = NULL; // FIX: Transfer ownership
                                                                                }
                                                                                iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_end_if, "End if label"));

                                                                                free(label_if_body); free(label_end_if);
                                                                            }
    | TK_PR_IF '(' expressao ')' push_table command_block pop_table TK_PR_ELSE push_table command_block pop_table {
                                                                                                                    if($6 != NULL && $10 != NULL && $6->type != $10->type){
                                                                                                                        semantic_error(ERR_WRONG_TYPE, "Erro: tipo do bloco 'if' diferente do bloco 'else'", get_line_number());
                                                                                                                    }
                                                                                                                    $$ = asd_new("if", $3->type);
                                                                                                                    asd_add_child($$, $3);
                                                                                                                    if($6 != NULL) { asd_add_child($$, $6); }
                                                                                                                    if ($10 != NULL) { asd_add_child($$, $10); }

                                                                                                                    char *label_if_body = iloc_new_label();
                                                                                                                    char *label_else_body = iloc_new_label();
                                                                                                                    char *label_end_if = iloc_new_label();

                                                                                                                    $$->code = $3->code;
                                                                                                                    $3->code = NULL;
                                                                                                                    iloc_op_t *cbr_op = iloc_op_new("cbr", iloc_operand_new_reg($3->temp), NULL, iloc_operand_new_label(label_if_body), iloc_operand_new_label(label_else_body), NULL, "Conditional branch (if-else)");
                                                                                                                    iloc_list_add($$->code, cbr_op);
                                                                                                                    free($3->temp);
                                                                                                                    $3->temp = NULL;

                                                                                                                    iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_if_body, "If block start"));
                                                                                                                    if ($6 != NULL && $6->code) { 
                                                                                                                        iloc_list_concat($$->code, $6->code); 
                                                                                                                        $6->code = NULL; // FIX: Transfer ownership
                                                                                                                    }
                                                                                                                    iloc_list_add($$->code, iloc_op_new("jumpI", NULL, NULL, iloc_operand_new_label(label_end_if), NULL, NULL, "Jump to end of if-else"));
                                                                                                                    
                                                                                                                    iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_else_body, "Else block start"));
                                                                                                                    if ($10 != NULL && $10->code) { 
                                                                                                                        iloc_list_concat($$->code, $10->code); 
                                                                                                                        $10->code = NULL; // FIX: Transfer ownership
                                                                                                                    }
                                                                                                                    iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_end_if, "End if-else label"));
                                                                                                                    
                                                                                                                    free(label_if_body); free(label_else_body); free(label_end_if);
                                                                                                                }
    ;

while
    : TK_PR_WHILE '(' expressao ')' push_table command_block pop_table      {
                                                                                $$ = asd_new("while", $3->type);
                                                                                asd_add_child($$, $3);
                                                                                if($6 != NULL) { asd_add_child($$, $6); }

                                                                                char *label_loop_start = iloc_new_label();
                                                                                char *label_loop_body = iloc_new_label();
                                                                                char *label_loop_end = iloc_new_label();
                                                                                
                                                                                $$->code = iloc_list_new();
                                                                                iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_loop_start, "While loop start"));
                                                                                iloc_list_concat($$->code, $3->code);
                                                                                $3->code = NULL;
                                                                                iloc_op_t *cbr_op = iloc_op_new("cbr", iloc_operand_new_reg($3->temp), NULL, iloc_operand_new_label(label_loop_body), iloc_operand_new_label(label_loop_end), NULL, "Conditional branch (while)");
                                                                                iloc_list_add($$->code, cbr_op);
                                                                                free($3->temp);
                                                                                $3->temp = NULL;

                                                                                iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_loop_body, "While body start"));
                                                                                if ($6 != NULL && $6->code) { 
                                                                                    iloc_list_concat($$->code, $6->code);
                                                                                    $6->code = NULL; // FIX: Transfer ownership
                                                                                }
                                                                                iloc_list_add($$->code, iloc_op_new("jumpI", NULL, NULL, iloc_operand_new_label(label_loop_start), NULL, NULL, "Jump to loop start"));
                                                                                iloc_list_add($$->code, iloc_op_new("nop", NULL, NULL, NULL, NULL, label_loop_end, "While loop end"));
                                                                                
                                                                                free(label_loop_start); free(label_loop_body); free(label_loop_end);
                                                                            }
    ;

expressao
    : n7                                            { $$ = $1; }
    ;

n7
    : n7 '|' n6                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: operacao '|' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("|", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("or", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "OR"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n6                                            { $$ = $1; }
    ;

n6
    : n6 '&' n5                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: operacao '&' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("&", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("and", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "AND"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n5                                            { $$ = $1; }
    ;

n5
    : n5 TK_OC_EQ n4                                {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '==' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("==", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("cmp_EQ", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "EQ Cmp"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n5 TK_OC_NE n4                                {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '!=' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("!=", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("cmp_NE", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "NE Cmp"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n4                                            { $$ = $1; }
    ;

n4
    : n4 '<' n3                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '<' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("<", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("cmp_LT", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "LT Cmp"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n4 '>' n3                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '>' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new(">", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("cmp_GT", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "GT Cmp"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n4 TK_OC_LE n3                                {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '<=' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("<=", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("cmp_LE", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "LE Cmp"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n4 TK_OC_GE n3                                {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: comparacao '>=' entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new(">=", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("cmp_GE", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "GE Cmp"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n3                                            { $$ = $1; }
    ;

n3
    : n3 '+' n2                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: soma entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("+", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("add", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "Addition"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n3 '-' n2                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: subtracao entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("-", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("sub", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "Subtraction"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n2                                            { $$ = $1; }
    ;

n2
    : n2 '*' n1                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: multiplicacao entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("*", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("mult", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "Multiplication"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n2 '/' n1                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: divisao entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("/", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("div", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "Division"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n2 '%' n1                                     {
                                                        if($1->type != $3->type){ semantic_error(ERR_WRONG_TYPE, "Erro: modulo entre tipos incompativeis", get_line_number()); }
                                                        $$ = asd_new("%", $1->type); asd_add_child($$, $1); asd_add_child($$, $3);
                                                        $$->code = $1->code; $1->code = NULL; iloc_list_concat($$->code, $3->code); $3->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("rem", iloc_operand_new_reg($1->temp), iloc_operand_new_reg($3->temp), iloc_operand_new_reg($$->temp), NULL, NULL, "Modulo"));
                                                        free($1->temp); $1->temp = NULL;
                                                        free($3->temp); $3->temp = NULL;
                                                    }
    | n1                                            { $$ = $1; }
    ;

n1
    : '+' n1                                        { 
                                                        $$ = asd_new("+", $2->type); asd_add_child($$, $2); 
                                                        $$->code = $2->code; $2->code = NULL; 
                                                        $$->temp = $2->temp; $2->temp = NULL; 
                                                    }
    | '-' n1                                        {
                                                        $$ = asd_new("-", $2->type); asd_add_child($$, $2);
                                                        $$->code = $2->code; $2->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("rsubI", iloc_operand_new_reg($2->temp), iloc_operand_new_const(0), iloc_operand_new_reg($$->temp), NULL, NULL, "Unary minus"));
                                                        free($2->temp);
                                                        $2->temp = NULL;
                                                    }
    | '!' n1                                        {
                                                        $$ = asd_new("!", $2->type); asd_add_child($$, $2);
                                                        $$->code = $2->code; $2->code = NULL;
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_list_add($$->code, iloc_op_new("xorI", iloc_operand_new_reg($2->temp), iloc_operand_new_const(1), iloc_operand_new_reg($$->temp), NULL, NULL, "Logical NOT"));
                                                        free($2->temp);
                                                        $2->temp = NULL;
                                                    }
    | n0                                            { $$ = $1; }
    ;

n0
    : TK_ID                                         {
                                                        char *varname = $1->token_val;
                                                        struct entry *e = search_entry_in_stack(stack, varname);
                                                        if (e == NULL){ semantic_error(ERR_UNDECLARED, "Identificador nao declarado", $1->line_number); }
                                                        if (e->nature == NATURE_FUNC){ semantic_error(ERR_FUNCTION, "Erro: funcao sendo usada como variavel", $1->line_number); }
                                                        
                                                        $$ = asd_new($1->token_val, e->type);
                                                        $$->code = iloc_list_new();
                                                        $$->temp = iloc_new_reg_temp();
                                                        const char* base_reg = (e->is_global) ? "rbss" : "rfp";
                                                        char *load_comment;
                                                        asprintf(&load_comment, "Load value of %s", varname);
                                                        iloc_op_t *load_op = iloc_op_new("loadAI", iloc_operand_new_reg(base_reg), iloc_operand_new_const(e->offset), iloc_operand_new_reg($$->temp), NULL, NULL, load_comment);
                                                        iloc_list_add($$->code, load_op);
                                                        free(load_comment);

                                                        if($1){ free($1->token_val); free($1); }
                                                    }
    | TK_LI_INT                                     {
                                                        $$ = asd_new($1->token_val, TYPE_INT);
                                                        $$->code = iloc_list_new();
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_op_t *load_const_op = iloc_op_new("loadI", iloc_operand_new_const(atoi($1->token_val)), NULL, iloc_operand_new_reg($$->temp), NULL, NULL, "Load integer literal");
                                                        iloc_list_add($$->code, load_const_op);
                                                        if($1){ free($1->token_val); free($1); }
                                                    }
    | TK_LI_FLOAT                                   {
                                                        $$ = asd_new($1->token_val, TYPE_FLOAT);
                                                        $$->code = iloc_list_new();
                                                        $$->temp = iloc_new_reg_temp();
                                                        iloc_op_t *load_const_op = iloc_op_new("loadI", iloc_operand_new_const((int)atof($1->token_val)), NULL, iloc_operand_new_reg($$->temp), NULL, NULL, "Load float literal (as int)");
                                                        iloc_list_add($$->code, load_const_op);
                                                        if($1){ free($1->token_val); free($1); }
                                                    }
    | call_func                                     { $$ = $1; }
    | '(' expressao ')'                             { $$ = $2; }
    ;

push_table:                                         {
                                                        struct table *table = create_table();
                                                        push_table_stack(&stack, table);

                                                        // FIX: Capture global scope (Etapa 6)
                                                        if (global_scope == NULL) {
                                                            global_scope = stack->top;
                                                        }

                                                        $$ = NULL;
                                                    }

pop_table:                                          {
                                                        pop_table_stack(&stack);
                                                        $$ = NULL;
                                                    }

%%

void yyerror(const char *msg) {
    fprintf(stderr, "Erro sintático na linha %d: %s\n", get_line_number(), msg);
}
