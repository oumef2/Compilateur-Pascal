#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <string.h>
#include <ctype.h>

typedef struct{
    char name[20];
    char value[20];
} Token;

const char* keyword_list[]= {"PROGRAM_TOKEN", "BEGIN_TOKEN", "END_TOKEN", "CONST_TOKEN" ,
							 "VAR_TOKEN", "IF_TOKEN", "THEN_TOKEN", "WHILE_TOKEN", "DO_TOKEN", 
							 "READ_TOKEN", "WRITE_TOKEN"};

const char* keyword_symb[]= {"PROGRAM", "BEGIN", "END", "CONST" , "VAR", "IF", "THEN", "WHILE", 
							"DO", "READ", "WRITE"};

const char* specialTokens_list[] = { "PV_TOKEN",  "PT_TOKEN",  "PLUS_TOKEN", "MOINS_TOKEN", 
							"MULT_TOKEN", "DIV_TOKEN", "VIR_TOKEN",  "EG_TOKEN", "AFF_TOKEN", 
							"INF_TOKEN",  "INFEG_TOKEN", "SUP_TOKEN", "SUPEG_TOKEN", "DIFF_TOKEN", 
							"PO_TOKEN",  "PF_TOKEN"};

const char* specialTokens_symb[] = {";",    ".",    "+",    "-",     "*",    "/",   "," ,   "=",  
							":=",  "<",    "<=",    ">",    ">=",  "<>",     "(",   ")"};


FILE* program;
Token currentToken;
char currentChar;
char tmpChar;
void get_token(){
	
    // Clear Token
	memset(currentToken.name, '\0', 20);
    memset(currentToken.value, '\0', 20);
	// Ignore Whitespaces and Newlines and Comments
    // Ignore blank space, tabulation, newline
    while( currentChar == ' ' || currentChar == '\t' || 
    	currentChar == '\n' || currentChar == '{'){
        tmpChar = currentChar ;
    	currentChar=getc(program);
    	// Ignore Comments
    	if( tmpChar == '{'){
    		//currentChar=getc(program);
        	if((currentChar == '*')){
        	    while((currentChar=getc(program)) != '*');
        	    currentChar=getc(program);
        	    if(currentChar != '}'){
        			printf("Error in comment, close brace");
    				exit(1);
    			}
                currentChar=getc(program);
        	}
        	else{
        		printf("Error in comment, open brace");
    			exit(1);
        	}
    	}
	}
	if(currentChar == EOF){ 
		strcpy(currentToken.name, "EOF_TOKEN");
	}
	else if(isdigit(currentChar)){
		char num[12];
		int i = 0;
    	num[0] = currentChar;
   		while( ++i < 12 && isdigit(num[i] = currentChar=getc(program)));
    	if(i >= 12){
    		printf("Number has several digit");
    		exit(1);
    	} 
        if (isalpha(currentChar)){
            printf("Word starts with a digit");
            exit(1);
        }
    	num[i] = '\0';
		strcpy(currentToken.name, "NUM_TOKEN");
    	strcpy(currentToken.value, num);
    }
    else if(isalpha(currentChar)){
    	char word[20];
    	int i = 0, j = 0;
		word[0] = toupper(currentChar);
    	while( ++i < 20 && (isalnum( word[i] = currentChar = toupper(currentChar=getc(program)) ) || word[i] == '_' ));
    	if(i == 20){
    		printf("there is many characters in this word");
    		exit(1);
		}
    	word[i] = '\0';	
    	// Verify this word match a keyword in the list of keywords
    	for (j=0; j<11; j++){
    		if(strcmp(word , keyword_symb[j]) == 0){
    			strcpy(currentToken.name, keyword_list[j]);
        		strcpy(currentToken.value, word);
    			break;
			}
    	}
    	if(j==11){
			strcpy(currentToken.name, "ID_TOKEN"); 
    		strcpy(currentToken.value, word);
    	}
    }
    else {
    	char op[3];
		memset(op,'\0',sizeof(op));
    	op[0] = currentChar;
    	if (currentChar == ':' || currentChar == '>'){
			currentChar = getc(program);
			if (currentChar == '='){
    			op[1] = '=';
    			currentChar = getc(program);
			}
    		else
    			op[1] = '\0';
		}
    	else if(currentChar == '<' ){
    		currentChar = getc(program);
			if (currentChar == '>'){
    			op[1] = '>';
    			currentChar = getc(program);
    		}
    		else
				op[1] = '\0';
    	}
    	else {
    		op[1] = '\0';
    		currentChar = getc(program);
    	}
    	//while( (cmp = strcmp(op, specialTokens_symb[i++]) != 0) && i < 16);
    	int i;
    	for (i=0; i<16;i++){
    		if(strcmp(op, specialTokens_symb[i]) == 0){
				strcpy(currentToken.name, specialTokens_list[i]); 
				strcpy(currentToken.value, op);
				break;
			}
    	}
    	if(i==16){
    		printf("invalid token");
            exit(1);
        }
	}
	printf("%s\n", currentToken.name);
} 