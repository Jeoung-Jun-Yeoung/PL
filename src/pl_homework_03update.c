#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum {ERR = 0,PLUS = 1,STAR = 2,NUMBER = 3,LP = 4,RP = 5,END = 6,ID = 7, PRINT = 8, EQL = 9, RET = 10}token;

char s1[500];
int idex;
int idx = 0;
enum token;
int num;
int rst = 0;
int array[26];
char testprint[6] = "print ";
char close[4] = "exit";

void get_next_token();
void statement();
int expr();
int term();
int factor();
void err();


void err () {
	printf("ERROR!\n");
}

void get_next_token () {
	char number[5];
	int numberidx=0;
	token = -1;
	for (int i = idex; i < strlen(s1); i++){
		if (token == ERR){
			break;
		}
		if (token == 3 && isdigit(s1[i]) == 0) {
			idex = i;
			rst = atoi(number);
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
		else if (s1[i]  >= 97 && s1[i] <= 122) { 
			if (s1[i] == 'p') {
				if (strncmp(s1,testprint,6) == 0) {
					token = PRINT;
					idex = 6;
					break;
				}
			}
			else if (s1[i] == 'e') {
				if (strncmp(s1,close,4) == 0) {
					token = END;
					idex = 4;
				}
			}
			else {
				token = ID;
				num = s1[i] - 97;
				idex = i + 1;
			}
			break;
		}
		else if (s1[i] == '=') {
			token = EQL;
			idex = i + 1;
			break;
		}
		else if (isdigit(s1[i]) != 0) {
			token = NUMBER;
			number[numberidx] = s1[i];
			numberidx++;
		}
		else if (s1[i] == '\n') {
			token = RET;
		}
		else if (s1[i] == ' ') {
			continue;
		}
		else {
			token = ERR;
			break;
		}
	}
}

void statement () {
	if (token == ID) {
		get_next_token();
		 if (token == EQL) {
			get_next_token();
				if (token == ERR) {
				err();
			token = END;
				}
			else {
				array[num] = expr();
				get_next_token();
				if (token != RET) {
					err();
			token = END;
				}
			}
		}
		else {
			err();
			token = END;
		}
	}
	else if (token == END) {
		printf("program close\n");
	}

	else if (token == PRINT) {
		get_next_token();
		if (token == ERR) {
			err();
			token = END;
		}
		else {
			printf("%d\n",expr());
			get_next_token();
			if (token != RET) {
				err();
				token = END;
			}
		}
	}
	else {
		err();
		token = END;
	}
}

int expr () {
	int r;
	r = term();
	while(token == PLUS) {
		get_next_token();
		if (token == ERR) {
			err();
			token = END;
			break;
		}
		r = r + term();
	}
	return r;
}
	
int term () {
	int r;
	r = factor();
	while(token == STAR) {
		get_next_token();
		if (token == ERR) {
			err();
			token = END;
			break;
		}
		r = r * factor();
	}
	return r;
}

int factor () {
	int r;
	if (token == NUMBER) {
		r = rst;
		get_next_token();
		
		if (token == ERR) {
			err();
			token = END;
		}
	
	}
	else if (token == ID) {
		r = array[num];
		get_next_token();
	}
	else if (token == LP) {
		get_next_token();
		if (token == ERR) {
			err();
			token = END;
		} 
		else { 
			r = expr();
		}

		if (token == RP) {
			
			get_next_token();
			
			if (token == ERR) {
				err();
				token = END;
			}
		
		}
		else {
			err();
			token = END;
		}
	}
	else { 
		err();
		token = END;
	}
	return r;
}


int main () {
	while(token != END){
		fgets(s1,sizeof(s1),stdin);
		idex = 0;
		get_next_token();
		statement();
		fflush(stdin);
	}
	
}
