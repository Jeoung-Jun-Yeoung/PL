#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#define max_size 100

typedef struct variable {
	char alph;
	int num;
}variable;

variable varray[max_size];


char assignment[max_size];
char* stack[max_size];
char symbol[7] = { '(',')','+' ,'-' ,'*' ,'/','\n' };
int top = -1; //사용
int varray_index = 0; // 사용



char peek() {
	return stack[top];
}

char pop() {
	if (top < 0) {
		printf("stack is empty");
	}
	else {
		char temp;
		temp = stack[top];
		top--;
		return temp;
	}
}

void push(char* value) {
	top++;
	stack[top] = value;
}

bool is_number(char target) { // 문자열 탐색. 문자가 심볼이 아닐며
	for (int i = 0; i < 7; i++) {
		if (target == symbol[i]) {
			return false;
		}
	}
	return true;

}

void infix_to_postfix(char infix[]) {
	char temp[100] = {0, };
	char postfixlist[100][max_size];
	int postfix_index = 0;
	int temp_index = 0;
	

	for (int i = 0; i < strlen(infix); i++) {
		
		if (is_number(infix[i] == true)) {
			temp[temp_index] = infix[i];
			temp_index++;
		}

		else  {
			printf("%s\n", temp);
			
			strcpy(postfixlist[postfix_index],temp);
			postfix_index++;
			
			for (int j = 0; j < temp_index; j++) {
				temp[j] = ' ';
			}
			temp_index = 0;
			
			if (infix[i] == '+') {
				strcpy(postfixlist[postfix_index], "+");
				postfix_index++;
			}
			else if (infix[i] == '-') {
				strcpy(postfixlist[postfix_index], "-");
				postfix_index++;
			}
			else if (infix[i] == '*') {
				strcpy(postfixlist[postfix_index], "*");
				postfix_index++;
			}
			else if (infix[i] == '/') {
				strcpy(postfixlist[postfix_index], "/");
				postfix_index++;
			}
			else if (infix[i] == '(') {
				strcpy(postfixlist[postfix_index], "(");
				postfix_index++;
			}
			else if (infix[i] == ')') {
				strcpy(postfixlist[postfix_index], ")");
				postfix_index++;
			}
		}
	}

	for (int i = 0; i < postfix_index; i++) {
		printf("%s \n", postfixlist[i]);
	}
	
}



bool is_vaild_assignment(char assignmenti[]) {
	int i = 0;
	int equlchek = 0;
	int tokenlist_index = 0; 
	char tokenlist[3][max_size] = { NULL, };
	
	/*가장먼저 치환문이 맞는지 판별. 조건은 = 을 보고 판단*/
	
	for (int i = 0; i < 100; i++) {
		if (assignment[i] == '=') {
			equlchek++;
		}
	}
	
	if (equlchek != 1) {
		printf("??");
		return false;
	}

	char* token = strtok(assignment, "=");

	while (token != NULL) {
		strcpy(tokenlist[tokenlist_index], token);
		tokenlist_index++;
		token = strtok(NULL, "=");
	}
	// tokenlist[0]에는 =기준 오른쪽 문자열, tokenlist[1]에는 수식이 들어감.

	if (tokenlist[0][1] != NULL) { // 문자열에서 알파벳 하나가 아니라 두자 이상이면 조건만족x
		printf("variable is not single 변수가 알파벳 하나가아닙니다 \n");
		return false; // 
	}
	else {
	varray[varray_index].alph = tokenlist[0][0]; // 모든조건 만족시 구조체 배열에 담음
	varray_index++;
	}

	//tokenlist[1]을 가지고 계산. 결과값은 varray[varray_index].num에 저장함.

	
	infix_to_postfix(tokenlist[1]);
	return true;

}

int main() {
	while (1) {
		scanf("%s", &assignment);
		getchar();

		if (is_vaild_assignment(assignment) == false) {
			printf("ERROR");
		}
		else {
			printf("OK");
		}
	}
}