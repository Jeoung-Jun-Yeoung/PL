#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum {NN = 0,PLUS = 1,STAR = 2,NUMBER = 3,LP = 4,RP = 5,END = 6}token;
// NN은 틀린 토큰
// END는 문자열 끝
char* str;
char s1[500];
int idex = 0;
enum token;

void err () {
	printf("ERROR!\n");
}

void get_next_token () {
	if (token != NN){
		token = -1;
	}
	for (int i = idex; i < strlen(s1); i++){
		if (token == NN){
			break;
		}
		if (token == 3 && isdigit(s1[i]) == 0) {
			idex = i;
			break;
		}
		if (s1[i] == '+') {
			token = PLUS;
			idex = i + 1 ;
			break;
		}
		else if (s1[i] == '*') {
			token = STAR;
			idex = i + 1 ;
			break;
		}
		else if (s1[i] == '(') {
			token = LP;
			idex = i + 1 ;
			break;
		}
		else if (s1[i] == ')') {
			token = RP;
			idex = i + 1 ;
			break;
		}
		else if (isdigit(s1[i]) != 0) {
			token = NUMBER;
		}
		else if (s1[i] == '\n') {
			token = END;
		}
		else if (s1[i] == ' ') {
			continue;
		}
		else {
			token = NN;
			break;
		}
	}
}

void term () {
	factor();
	while(token == STAR) {
		get_next_token();
		if (token == NN) {
			err();
			break;
		}
		factor();
	}
}

void expr () {
	term();
	while(token == PLUS) {
		get_next_token();
		if (token == NN) {
			err();
			break;
		}
		term();
	}
}

void factor () {
	if (token == NUMBER) {
		get_next_token();
		
		if (token == NN) {
			err();
		}
	
	}
	else if (token == LP) {
		get_next_token();
		
		if (token == NN) {
			err();
		} 
		else { 
			expr(); 
		}

		if (token == RP) {
			
			get_next_token();
			
			if (token == NN) {
				err();
			}
		
		}
		else {
			err();
		}
	}
	else { 
		err();
	}
}


int main () {
	fgets(s1,sizeof(s1),stdin);
	get_next_token();
	expr();
	if (token == END) {
		printf("complete");
	}
	else {
		err();
	}
}
