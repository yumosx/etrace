#include "xdp.h"

token_t* add_token(vec_t* vec, char* str, token_type t) {
    token_t* tok = malloc(sizeof(*tok));
    tok->str = str;
    tok->type = t;
    
    vec_push(vec, tok);
    return tok;
}


static kw_t kws[] = {
    {.name="u8",     .type = TOKEN_U8},
    {.name="u16",    .type = TOKEN_U16},
    {.name="const",  .type = TOKEN_CONST},
    {.name="case",   .type = TOKEN_CASE},
    {.name="drop",   .type = TOKEN_DROP},
    {.name="pass",   .type = TOKEN_PASS},
    {.name="end",    .type = TOKEN_END}
};
static int kwlen = _size(kws); 

token_type get_keyworld(char* name) {
    int i;

    for (i = 0; i < kwlen; i++) {
        return kws[i].type;
    }

    return TOKEN_IDENT;
}


vec_t* scan(char* p) {
    vec_t*  vec;
    int i;
   
    vec = vec_new();
    i = 0;
    
    while (*p) {
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (strchr("#=->();", *p)) {
            char* str;
            switch (*p) {
            case '#':
                str = strdup("#");
                add_token(vec, str, TOKEN_MC);
                break;
            case '=':
                str = strdup("=");
                add_token(vec, str, TOKEN_EQ);
                break;
            case '(':
                str = strdup("(");
                add_token(vec, str, TOKEN_LPARN);
                break;
            case ')':
                str = strdup(")");
                add_token(vec, str, TOKEN_RPARN);
                break;
            case ';':
                str = strdup(";");
                add_token(vec, str, TOKEN_SEMICOLON);
                break;
            case '-':
                p++;
                if (*p == '>') {
                    str = strdup("->");
                    add_token(vec, str, TOKEN_ARROW);
                }
                break;
            default:
                break;
            }

            p++;
            i++;
            continue;
        }

        if (isalpha(*p)) {
            int len = 1;
            token_t* tok;
            char* name;
            token_type type;

            while (isalpha(p[len]) || isdigit(p[len])) {
                len++;
            }

            name = strndup(p, len);
            type = get_keyworld(name);
            
            add_token(vec, name, type);  
            i++;
            p += len;
            continue;
        }

        if (isdigit(*p)) {
            int len = 1;
            char* value;
            
            while (isdigit(p[len])) {
                len++;
            }
            value = strndup(p, len);
            add_token(vec, value, TOKEN_NUMBER);
            i++;
            p += len;
            continue;
        }

        error("cannot tokenize: %s", p);    
    }
    add_token(vec, p, TOKEN_EOF);
    return vec;
}

void free_tok(vec_t* toks) {
    token_t* tok;
    int i;    

    for (i = 0; i < toks->len; i++) {
        tok = toks->data[i];
        if (tok && tok->type != TOKEN_EOF) {
            free(tok->str);
            free(tok);
        }
    }

    vec_free(toks);
}


int main() {
    char* input = "#const(a=1) case a=12->pass; end";
    int i;
    token_t* tok;
    vec_t* vec;

    vec = scan(input);

    for (i = 0; i < vec->len; i++) {
        tok = vec->data[i];
        printf("%s\t", tok->str);
        printf("%d\n", tok->type);
    }
    free_tok(vec);
    return 0;
}
