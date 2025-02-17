#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_IDENT 100

// Definição dos tokens
typedef enum {
    TK_INTEIRO, TK_REAL, TK_IF, TK_ELSE, TK_WHILE, TK_REPEAT, TK_UNTIL,
    TK_READ, TK_WRITE, TK_ASSIGN, TK_ADD, TK_SUB, TK_MUL, TK_DIV,
    TK_LT, TK_GT, TK_LE, TK_GE, TK_EQ, TK_NE, TK_AND, TK_OR,
    TK_LPAREN, TK_RPAREN, TK_LBRACE, TK_RBRACE, TK_SEMICOLON, TK_COMMA,
    TK_IDENTIFIER, TK_NUMBER, TK_EOF
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[MAX_IDENT];
} Token;

// Função auxiliar para verificar palavras-chave
TokenType check_keyword(char *str) {
    if (strcmp(str, "inteiro") == 0) return TK_INTEIRO;
    if (strcmp(str, "real") == 0) return TK_REAL;
    if (strcmp(str, "se") == 0) return TK_IF;
    if (strcmp(str, "senao") == 0) return TK_ELSE;
    if (strcmp(str, "enquanto") == 0) return TK_WHILE;
    if (strcmp(str, "repita") == 0) return TK_REPEAT;
    if (strcmp(str, "ate") == 0) return TK_UNTIL;
    if (strcmp(str, "ler") == 0) return TK_READ;
    if (strcmp(str, "mostrar") == 0) return TK_WRITE;
    return TK_IDENTIFIER;
}

// Função para identificar números
int is_number(char c) {
    return isdigit(c) || c == '.';
}

// Função que realiza a análise léxica
void lex_analyze(char *source) {
    int i = 0;
    char ch;
    Token token;

    while ((ch = source[i]) != '\0') {
        // Ignorar espaços e quebras de linha
        if (isspace(ch)) {
            i++;
            continue;
        }

        // Identificadores e palavras-chave
        if (isalpha(ch)) {
            int j = 0;
            while (isalpha(source[i]) || isdigit(source[i])) {
                token.lexeme[j++] = source[i++];
            }
            token.lexeme[j] = '\0';
            token.type = check_keyword(token.lexeme);
            printf("Token: %d, Lexeme: %s\n", token.type, token.lexeme);
            continue;
        }

        // Números
        if (is_number(ch)) {
            int j = 0;
            while (is_number(source[i])) {
                token.lexeme[j++] = source[i++];
            }
            token.lexeme[j] = '\0';
            token.type = TK_NUMBER;
            printf("Token: NUMBER, Lexeme: %s\n", token.lexeme);
            continue;
        }

        // Operadores e símbolos
        switch (ch) {
            case '+': token.type = TK_ADD; break;
            case '-': token.type = TK_SUB; break;
            case '*': token.type = TK_MUL; break;
            case '/': token.type = TK_DIV; break;
            case '(': token.type = TK_LPAREN; break;
            case ')': token.type = TK_RPAREN; break;
            case '{': token.type = TK_LBRACE; break;
            case '}': token.type = TK_RBRACE; break;
            case ';': token.type = TK_SEMICOLON; break;
            case ',': token.type = TK_COMMA; break;
            case '=':
                if (source[i+1] == '=') { token.type = TK_EQ; i++; }
                else token.type = TK_ASSIGN;
                break;
            case '<':
                if (source[i+1] == '=') { token.type = TK_LE; i++; }
                else token.type = TK_LT;
                break;
            case '>':
                if (source[i+1] == '=') { token.type = TK_GE; i++; }
                else token.type = TK_GT;
                break;
            case '!':
                if (source[i+1] == '=') { token.type = TK_NE; i++; }
                break;
            case '&':
                if (source[i+1] == '&') { token.type = TK_AND; i++; }
                break;
            case '|':
                if (source[i+1] == '|') { token.type = TK_OR; i++; }
                break;
            default:
                printf("Token desconhecido: %c\n", ch);
                i++;
                continue;
        }

        token.lexeme[0] = ch;
        token.lexeme[1] = '\0';
        printf("Token: %d, Lexeme: %s\n", token.type, token.lexeme);
        i++;
    }

    token.type = TK_EOF;
    printf("Token: EOF\n");
}

int main() {
    char code[] = "inteiro a, b; real x; a = 5; b = 10; x = 3.14; se a > b entao mostrar(a);";
    lex_analyze(code);
    return 0;
}
