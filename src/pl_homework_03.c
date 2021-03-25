#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum {ERR = 0,PLUS = 1,STAR = 2,NUMBER = 3,LP = 4,RP = 5,END = 6,ID = 7, PRINT = 8, EQL = 9, RET = 10}token;
// NN은 틀린 토큰
// END는 문자열 끝
char* str;
char s1[500];
int idex = 0;
enum token;
int num;

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
	token = -1;
	for (int i = idex; i < strlen(s1); i++){
		if (token == ERR){
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
		else if (s1[i]  >= 97 && s1[i] <= 122) { // 일단 알파벳이라는 이야기.
			//다음문자가  공백이면 입력받은 알파벳이 ID가되고.
			//다음 문자가  equl이면 입력받은 알파벳이 ID가 되고.
			// 다음문자가 또 문자면 print로 의심을 해봐야하고 strncmp
			//프린트까지 봣는데 프린트가 맞았어 그럼 프린트 바로 다음에 숫자나 영어가 바로 나오면 에러. 공백이 있는지 봐준다. 
			// 나머지 경우는 err printa+3

		}
		else if (isdigit(s1[i]) != 0) {
			token = NUMBER;
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
		int idx = num;
		get_next_token();

		else if (token == EQL) {
			get_next_token();
			if (token == ERR) {
				err();
			}
			else {
				array[idx] = expr();
				get_net_token();
				if (token != RET) {
					err();
				}
			}
		}

		else {
			err();
		}
	}
	else if (token == END) {
		printf("program close\n");
	}
	else if (token == PRINT) {
		get_next_token();
		if (token == ERR) {
			err();
		}
		else {
			printf("%d\n",expr());
			get_next_token();
			if (token != RET) {
				err();
			}
		}
	}
	else {
		err();
	}
}

int expr () {
	int r;
	r = term();
	while(token == PLUS) {
		get_next_token();
		if (token == ERR) {
			err();
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
		if (token == NN) {
			err();
			break;
		}
		r = r * factor();
	}
	return r;
}

int factor () {
	int r;
	if (token == NUMBER) {
		r = num;
		get_next_token();
		
		if (token == ERR) {
			err();
		}
	
	}
	else if (token == ID) {
		r = array[num];
		get_netx_token();
	}
	else if (token == LP) {
		get_next_token();
		if (token == ERR) {
			err();
		} 
		else { 
			r = expr();
		}

		if (token == RP) {
			
			get_next_token();
			
			if (token == ERR) {
				err();
			}
		
		}
		else {
			err();
			token = ERR;
		}
	}
	else { 
		err();
		token = ERR;
	}
	return r;
}


int main () {
	fgets(s1,sizeof(s1),stdin);
	get_next_token();
	expr();
	if (token == END) {
		printf("complete\n");
	}
	else {
		err();
	}
}
