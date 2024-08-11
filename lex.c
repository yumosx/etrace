#include "xdp.h"

token_t* add_token(vec_t* vec, char* name, token_type t) {
    token_t* tok = malloc(sizeof(*tok));
    tok->name = name;
    tok->type = t;
    
    vec_push(vec, tok);
    return tok;
}

token_type get_keyworld(char* name) {
    if (!strcmp(name, "u8")) {
        return TOKEN_U8; 
    }
    
    if (!strcmp(name, "u16")) {
        return TOKEN_U16;
    }

    return 0;
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

        if (strchr("@=?-", *p)) {
            char* str;
            switch (*p) {
            case '@':
                str = strdup("@");
                add_token(vec, str, TOKEN_AT);
                break;
            case '=':
                str = strdup("=");
                add_token(vec, str, TOKEN_MATCH);
                break;
            case '-':
                p++;
                if (*p == '>') {
                    str = strdup("->");
                    add_token(vec, str, TOKEN_ARROW);
                }
                break;
            case '?':
                str = strdup("?");
                add_token(vec, str, TOKEN_CASE);
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
            
            if (!type) printf("token type not found");
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
    }
    add_token(vec, p, TOKEN_EOF);
    return vec;
}

int main() {
    char* input = "u8@12";
    token_t* tok;
    vec_t* vec;

    vec = scan(input);
    tok = vec->data[1];

    printf("%s\n", tok->name);
    return 0;
}
