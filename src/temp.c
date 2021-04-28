#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum e {ERROR = 0,PLUS = 1,STAR = 2,NUMBER = 3,LP = 4,RP = 5,END = 6,ID = 7, PRINT = 8, EQL = 9, RET=10}TOKEN;

int num; char ch = ' ';
TOKEN token;
int rst;
int array[32];
int term();
int factor();
int expr();
int idx;
TOKEN get_next_token() {
	 char string[32];
	 int i = 0;
	while((ch == ' ') || (ch == '\t')) ch=getchar(); 
	if (ch == '+') {ch = getchar(); return(PLUS);}
	if (ch == '*') {ch = getchar(); return(STAR);}
	if (ch == '(') {ch = getchar(); return(LP);}
	if (ch == ')') {ch = getchar(); return(RP);}
	if (ch == '\n'){return(RET);}
	if (ch == EOF) {ch = getchar(); return(END);}
	if (ch == '=') {ch = getchar(); return(EQL);}
	if((ch>='0') && (ch <='9')) {
		num = 0;
		do {
			num = num * 10 + ch - '0'; 
			ch = getchar();}
		while((ch>='0')&&(ch<='9'));
		return(NUMBER);}
	if((ch>='a')&&(ch<='z')){
		do {
			string[i++] = ch; ch=getchar();}
		while((ch>='a')&& (ch <= 'z'));
		string[i]=0;
		if(strcmp(string,"print") == 0) { return (PRINT);}
		if(strlen(string)==1) {idx=string[0]-'a'; return(ID);}
		return(ERROR);
	}
	else {return(ERROR);}
	
}
void statement() {
	if(token == ID) {
		token = get_next_token();
		if(token == EQL) {
			token = get_next_token();
			if(token == ERROR){
				printf("ERROR\n");
			}
			else{
				array[idx] = expr();
				token = get_next_token();
				if (token != RET) {
					token = ERROR;
					printf("ERROR\n");
				}
			}
		}
		else {
			printf("ERROR\n");
		}
	}
	else if (token == PRINT) {
		token = get_next_token();
		if (token == ERROR) {
			printf("ERROR\n");
		}
		else {
			printf("%d\n",expr());
			token = get_next_token();
			if(token != RET){
				printf("ERROR\n");
			}
		}
	}
	else {
		printf("ERROR\n");
	}
}
int expr() {
	int r; 
	r = term();
	while(token == PLUS) {
	token = get_next_token();
		if(token == ERROR) {
			printf("ERROR\n");
		}
		r = r + term();
	}
	return r;
}
int term () {
	int r;
	r = factor();
	while(token == STAR) {
	token = get_next_token();
		if(token == ERROR){
			printf("ERROR\n");
		}
		r = r * factor();
	}
	return r;
}
int factor() {
	int r;
	if(token == NUMBER){
		r = num;
		token = get_next_token();
	}
	else if(token == ID) {
		r = array[idx];
		token = get_next_token();
	}
	else if(token == LP) {
		token = get_next_token();
		if(token == ERROR){
			printf("ERROR\n");
		}
		else {
			r = expr();
		}
		if(token == RP) {
			token = get_next_token();
			if(token == ERROR){
				printf("ERROR\n");
			}
		}
		else {
			printf("ERROR\n");
		}
	}
	else {
		printf("ERROR\n");
	}
	return r;
}
int main () {
	while(1){
		ch = getchar();
		token = get_next_token();
		statement();
	}	
}
