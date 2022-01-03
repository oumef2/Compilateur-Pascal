#include "Lexer.c"

const char* fileName = "program.pascal";

int main(){

    program = fopen(fileName, "r");
    NextChar();
    getToken();
    do{
        printf("%s_TOKEN\n", currentToken.name);
        getToken();
    }while(strcmp(currentToken.name,"EOF"));
    return 1;
} 