#include "Lexical.c"

void Program();
void Block();
void Consts();
void Vars();
void Insts();
void Inst();
void Affec();
void Expr();
void Si();
void Tantque();
void Ecrire();
void Lire();
void Cond();
void Relop();
void Term();
int Addop();
void Fact();
int Mulop();


void Program(){
    if(strcmp(currentToken.name,"PROGRAM_TOKEN")!=0){
    	printf("sytax error: PROGRAM_TOKEN not declared  %s\n",currentToken.name);
    	exit(1);
    }
    get_token();
    if(strcmp(currentToken.name,"ID_TOKEN")!=0){
    	printf("Syntax error: program name not declared  %s\n",currentToken.name);
    	exit(1);
    }
    get_token();
    if(strcmp(currentToken.name,"PV_TOKEN")!=0){
    	printf("Syntax error: program not declared  %s\n",currentToken.name);
    	exit(1);
    }
    Block();
    get_token();
    if(strcmp(currentToken.name,"PT_TOKEN")!=0){
    	printf("Syntax error: (.) didn't end the program  %s\n",currentToken.name);
    	exit(1);
    }    
}
void Block(){
	get_token();
	while (strcmp(currentToken.name,"BEGIN_TOKEN")!=0){
		printf("block: %s\n",currentToken.name);
		if (strcmp(currentToken.name,"CONST_TOKEN")==0)
			Consts();
		else if(strcmp(currentToken.name,"VAR_TOKEN")==0)
			Vars();	
		else 
			exit(1);
	}
	if (strcmp(currentToken.name,"BEGIN_TOKEN")==0)
		Insts();
}
void Consts(){
	get_token();
	while(strcmp(currentToken.name,"ID_TOKEN")==0){
		get_token();
		if(strcmp(currentToken.name,"EG_TOKEN")!=0){
    		printf("Syntax error: constant not declared  %s\n",currentToken.name);
    		exit(1);
    	}
    	get_token();
    	if(strcmp(currentToken.name,"NUM_TOKEN")!=0){
    		printf("Syntax error: constant not declared  %s\n",currentToken.name);
    		exit(1);
    	}
    	get_token();
    	if(strcmp(currentToken.name,"PV_TOKEN")!=0){
    		printf("Syntax error: constant not declared  %s\n",currentToken.name);
    		exit(1);
    	}
    	get_token();
	}
}
void Vars(){
	get_token();
	while(strcmp(currentToken.name,"ID_TOKEN")==0){
		get_token();
		if(strcmp(currentToken.name,"PV_TOKEN")==0){
			get_token();
			break;
		}
		else if(strcmp(currentToken.name,"VIR_TOKEN")==0){
			get_token();
			if(strcmp(currentToken.name,"ID_TOKEN")!=0){
				printf("Syntax error: variable not declared");
				exit(1);
			}
			continue;
		}
		else{
    		printf("Syntax error: (.) didn't end the program");
    		exit(1);
    	}
	}
}
void Insts(){
	//starting with BIGIN
	while(strcmp(currentToken.name,"END_TOKEN")!=0){
		Inst();
	}
	if(strcmp(currentToken.name,"END_TOKEN")==0)
		return;
}
void Inst(){
	get_token();
	if(strcmp(currentToken.name,"BEGIN_TOKEN")==0)
		Insts();
	else if(strcmp(currentToken.name,"ID_TOKEN")==0){
		Affec();
		if(strcmp(currentToken.name,"PV_TOKEN")!=0){
    		printf("Syntax error: inst doesn't end with ;  %s\n",currentToken.name);
    		exit(1);
    	}
	}
	else if(strcmp(currentToken.name,"IF_TOKEN")==0)
		Si();
	else if(strcmp(currentToken.name,"WHILE_TOKEN")==0)
		Tantque();
	else if(strcmp(currentToken.name,"WRITE_TOKEN")==0){
		Ecrire();
		if(strcmp(currentToken.name,"PV_TOKEN")!=0){
    		printf("Syntax error: inst doesn't end with ;  %s\n",currentToken.name);
    		exit(1);
    	}
	}
	else if(strcmp(currentToken.name,"READ_TOKEN")==0){
		Lire();
		if(strcmp(currentToken.name,"PV_TOKEN")!=0){
    		printf("Syntax error: inst doesn't end with ;  %s\n",currentToken.name);
    		exit(1);
    	}
	}
	else 
		return;
}
//read next
void Affec(){
	get_token();
	if(strcmp(currentToken.name,"AFF_TOKEN")!=0){
    	printf("Syntax error: affectation error ;  %s\n",currentToken.name);
    	exit(1);
   	}
   	get_token();
   	Expr();
}
//reads next
void Si(){
	Cond();
	if(strcmp(currentToken.name,"THEN_TOKEN")!=0){
		printf("Syntax error: if condition ;  %s\n",currentToken.name);
   		exit(1);
    }
    Inst();
    get_token();
}
//reads next
void Tantque(){
	Cond();
	if(strcmp(currentToken.name,"DO_TOKEN")!=0){
    		printf("Syntax error: unfinished while lood  %s\n",currentToken.name);
    		exit(1);
    	}
    Inst();
    get_token();
}
//reads next 
void Ecrire(){
	get_token();
	if(strcmp(currentToken.name,"PO_TOKEN")!=0){
    	printf("Syntax error: function write  %s\n",currentToken.name);
    	exit(1);
    }
    do{
    	get_token();
    	Expr();
	}while(strcmp(currentToken.name,"VIR_TOKEN")==0);
    if(strcmp(currentToken.name,"PF_TOKEN")!=0){
    	printf("Syntax error: function write  %s\n",currentToken.name);
    	exit(1);
    }
    get_token();
}
//reads next
void Lire(){
	get_token();
	if(strcmp(currentToken.name,"PO_TOKEN")!=0){
    	printf("Syntax error: function read  %s\n",currentToken.name);
    	exit(1);
    }

    do{
    	get_token();
    	if(strcmp(currentToken.name,"ID_TOKEN")!=0){
    		printf("Syntax error: function read  %s\n",currentToken.name);
    		exit(1);
    	}
    	get_token();
	}while(strcmp(currentToken.name,"VIR_TOKEN")==0);
    if(strcmp(currentToken.name,"PF_TOKEN")!=0){
    	printf("Syntax error: function read  %s\n",currentToken.name);
    	exit(1);
    }
    get_token();
}
void Expr(){
	do{
		Term();
	}while(Addop());
}
void Cond(){
	get_token();
	Expr();
	Relop();
	get_token();
	Expr();
}
void Relop(){
	if(strcmp(currentToken.name,"EG_TOKEN")==0)
		return;
	else if(strcmp(currentToken.name,"DIFF_TOKEN")==0)
		return;
	else if(strcmp(currentToken.name,"INF_TOKEN")==0)
		return;
	else if(strcmp(currentToken.name,"SUP_TOKEN")==0)
		return;
	else if(strcmp(currentToken.name,"INFEG_TOKEN")==0)
		return;
	else if(strcmp(currentToken.name,"SUPEG_TOKEN")==0)
		return;
	else {
		printf("Syntax error: invalid condition");
		exit(1);
	}
}
void Term(){
	do{
		Fact();
	}while(Mulop());
}
int Addop(){
	if(strcmp(currentToken.name,"PLUS_TOKEN")==0){
    	get_token();
    	return 1;
	}
    else if (strcmp(currentToken.name,"MOINS_TOKEN")==0){
    	get_token();
    	return 1;
    }
    else 
    	return 0;
}
void Fact(){
	if(strcmp(currentToken.name,"ID_TOKEN")==0)
		return;
	else if(strcmp(currentToken.name,"NUM_TOKEN")==0)
		return;
	else 
		Expr();	
}
int Mulop(){
	get_token();
	if(strcmp(currentToken.name,"MULT_TOKEN")==0){
		get_token();
    	return(1);
	}
    else if (strcmp(currentToken.name,"DIV_TOKEN")==0){
    	get_token();
    	return 1;
    }
    else 
    	return 0;
}

void main(){
	program = fopen("C:\\Users\\HP\\Desktop\\compila TP\\program.pascal", "r");
    currentChar=getc(program);
    get_token();
   	Program();
   	get_token();
    if(strcmp(currentToken.name,"EOF_TOKEN")==0)
    	printf("no syntax errors");
}