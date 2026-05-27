#include <stdio.h>
#include <string.h>

int is_space(int c) {
    return (c == ' ' || c == '\n' || c == '\t' || c == '\r');
}

int is_digit(int c) {
    return (c >= '0' && c <= '9');
}

#define TOKEN_NUM     1
#define TOKEN_PLUS    2
#define TOKEN_LPAREN  3
#define TOKEN_RPAREN  4
#define TOKEN_EOF     5

char input[1000];
int pos = 0;
int token;
char lexeme[256];
int has_error = 0; 

void nextToken() {
    int len = 0;

    while (is_space(input[pos]))
        pos++;

    if (input[pos] == '\0') {
        token = TOKEN_EOF;
        lexeme[0] = '\0';
        return;
    }

    if (is_digit(input[pos])) {
        while (is_digit(input[pos])) {
            lexeme[len++] = input[pos++];
        }
        lexeme[len] = '\0';
        token = TOKEN_NUM;
        return;
    }

    if (input[pos] == '+') {
        pos++;
        token = TOKEN_PLUS;
        return;
    }

    if (input[pos] == '(') {
        pos++;
        token = TOKEN_LPAREN;
        return;
    }

    if (input[pos] == ')') {
        pos++;
        token = TOKEN_RPAREN;
        return;
    }
    
    has_error = 1;
}

void parse_S();
void parse_S_prime();
void parse_E();


void parse_error() {
    if (!has_error) {
        printf("ParseError\n");
        has_error = 1;
    }
}

void parse_S() {
    if (has_error) return;
    
    if (token == TOKEN_NUM || token == TOKEN_LPAREN) {
        printf("S -> E S'\n");
        parse_E();
        parse_S_prime();
    } else {
        parse_error();
    }
}

void parse_S_prime() {
    if (has_error) return;
    
    if (token == TOKEN_PLUS) {
        printf("S' -> + S\n");
        nextToken();
        parse_S();
    } 
    else if (token == TOKEN_RPAREN || token == TOKEN_EOF) {
        return;
    } 
    else {
        parse_error();
    }
}


void parse_E() {
    if (has_error) return;
    
    if (token == TOKEN_NUM) {
        printf("%s\n", lexeme);
        nextToken();
    } 
    else if (token == TOKEN_LPAREN) {
        printf("E -> ( S )\n");
        nextToken();
        parse_S();
        
        if (token != TOKEN_RPAREN) {
            parse_error();
        } else {
            nextToken();
        }
    } 
    else {
        parse_error();
    }
}

int main() {
    
    if (fgets(input, sizeof(input), stdin) != NULL) {

        int len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[len-1] = '\0';
        }
    }

    pos = 0;
    has_error = 0;
    
    nextToken();
    parse_S();

    if (!has_error && token != TOKEN_EOF) {
        parse_error();
    }

    return 0;
}
