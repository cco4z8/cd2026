#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 為了不違反只能 include 三個標頭檔的規定，自行實作字元判斷函式
int is_space(int c) {
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

int is_alpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int is_digit(int c) {
    return (c >= '0' && c <= '9');
}

int is_alnum(int c) {
    return is_alpha(c) || is_digit(c);
}

int main() {
    int c;
    char buffer[256];
    int buf_idx = 0;

    // 讀取 stdin，直到檔案結束
    while ((c = getchar()) != EOF) {
        // 忽略 Whitespace
        if (is_space(c)) {
            continue;
        }

        buf_idx = 0;
        buffer[0] = '\0';

        // 判斷 ID 或是 Keywords
        if (is_alpha(c)) {
            buffer[buf_idx++] = c;
            while ((c = getchar()) != EOF && (is_alnum(c) || c == '_')) {
                buffer[buf_idx++] = c;
            }
            buffer[buf_idx] = '\0';
            
            if (c != EOF) {
                ungetc(c, stdin); // 退回多讀的一個字元
            }

            // 辨識 Keywords
            if (strcmp(buffer, "int") == 0) {
                printf("%s: TYPE_TOKEN\n", buffer);
            } else if (strcmp(buffer, "main") == 0) {
                printf("%s: MAIN_TOKEN\n", buffer);
            } else if (strcmp(buffer, "if") == 0) {
                printf("%s: IF_TOKEN\n", buffer);
            } else if (strcmp(buffer, "else") == 0) {
                printf("%s: ELSE_TOKEN\n", buffer);
            } else if (strcmp(buffer, "while") == 0) {
                printf("%s: WHILE_TOKEN\n", buffer);
            } else {
                // 否則就是一般 ID
                printf("%s: ID_TOKEN\n", buffer);
            }
        } 
        // 判斷 Number (只有 int)
        else if (is_digit(c)) {
            buffer[buf_idx++] = c;
            while ((c = getchar()) != EOF && is_digit(c)) {
                buffer[buf_idx++] = c;
            }
            buffer[buf_idx] = '\0';
            
            if (c != EOF) {
                ungetc(c, stdin);
            }
            printf("%s: LITERAL_TOKEN\n", buffer);
        } 
        // 判斷 Relop 與其他符號
        else {
            if (c == '=') {
                int next_c = getchar();
                if (next_c == '=') {
                    printf("==: EQUAL_TOKEN\n");
                } else {
                    if (next_c != EOF) ungetc(next_c, stdin);
                    printf("=: ASSIGN_TOKEN\n");
                }
            } else if (c == '>') {
                int next_c = getchar();
                if (next_c == '=') {
                    printf(">=: GREATEREQUAL_TOKEN\n");
                } else {
                    if (next_c != EOF) ungetc(next_c, stdin);
                    printf(">: GREATER_TOKEN\n");
                }
            } else if (c == '<') {
                int next_c = getchar();
                if (next_c == '=') {
                    printf("<=: LESSEQUAL_TOKEN\n");
                } else {
                    if (next_c != EOF) ungetc(next_c, stdin);
                    printf("<: LESS_TOKEN\n");
                }
            } else if (c == '+') {
                printf("+: PLUS_TOKEN\n");
            } else if (c == '-') {
                printf("-: MINUS_TOKEN\n");
            } else if (c == '(') {
                printf("(: LEFTPAREN_TOKEN\n");
            } else if (c == ')') {
                // 這裡刻意配合簡報拼字錯誤 (REFT)
                printf("): REFTPAREN_TOKEN\n"); 
            } else if (c == '{') {
                printf("{: LEFTBRACE_TOKEN\n");
            } else if (c == '}') {
                // 這裡刻意配合簡報拼字錯誤 (REFT)
                printf("}: REFTBRACE_TOKEN\n"); 
            } else if (c == ';') {
                printf(";: SEMICOLON_TOKEN\n");
            } else {
                // 若有其他未定義字元，直接忽略或可在此處處理
            }
        }
    }

    return 0;
}