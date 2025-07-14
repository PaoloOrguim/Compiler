#include "errors.h"
#include <stdio.h>
#include <stdlib.h>

void semantic_error(int code, const char *msg, int line_number) {
    fprintf(stderr, "Erro semântico na linha %d: %s\n", line_number, msg);
    exit(code);
}