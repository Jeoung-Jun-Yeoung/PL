#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#define max_size 100
#define MAX 100

typedef struct variable {
	char alph;
	int num;
}variable;

typedef struct stack {
	int data[MAX];
	int top;
}stack;

char assignment[max_size];
char chek_print[] = "print";
int varray_index = 0; // 사용
variable varray[max_size];

bool is_not_opertor(char t []) {
	char symbol[6] = { '(',')','+' ,'-' ,'*' ,'/' };
	for (int i = 0; i < sizeof(t); i++) {
		for (int j = 0; j < 6; j++) {
			if (t[i] == symbol[j]) {
				return false;
			}
		}
	}
	return true;
}


int precedence(char x)
{
	if (x == '(')
		return(0);
	if (x == '+' || x == '-')
		return(1);
	if (x == '*' || x == '/' || x == '%')
		return(2);

	return(3);
}

void init(stack* s)
{
	s->top = -1;
}

int empty(stack* s)
{
	if (s->top == -1)
		return(1);

	return(0);
}

int full(stack* s)
{
	if (s->top == MAX - 1)
		return(1);

	return(0);
}

void push(stack* s, int x)
{
	s->top = s->top + 1;
	s->data[s->top] = x;
}

int pop(stack* s)
{
	int x;
	x = s->data[s->top];
	s->top = s->top - 1;
	return(x);
}

int top(stack* p)
{
	return (p->data[p->top]);
}

void infix_to_postfix(char infix[], char postfix[])
{
	stack s;
	char x, token;
	int i, j;    //i-index of infix,j-index of postfix
	init(&s);
	j = 0;

	for (i = 0; infix[i] != '\0'; i++) {
		token = infix[i];
		if (isalnum(token))
			postfix[j++] = token;
		else
			if (token == '(')
				push(&s, '(');
			else
				if (token == ')')
					while ((x = pop(&s)) != '(')
						postfix[j++] = x;
				else {
					while (precedence(token) <= precedence(top(&s)) && !empty(&s)) {
						x = pop(&s);
						postfix[j++] = x;
					}
					push(&s, token);
				}
	}
	while (!empty(&s)) {
		x = pop(&s);
		postfix[j++] = x;
	}
	postfix[j] = '\0';
}

int calculate (char postfix[]) {
	int num1, num2, rst, i;
	int postlen = (int)strlen(postfix);
	char ch;
	stack c;
	init(&c);
	for (i = 0; i < postlen; i++) {
		ch = postfix[i];
		if ((int)isalpha(ch) != 0) {
			for (int j = 0; j < varray_index; j++) {
				if (varray[j].alph == ch) {
					rst = varray[j].num;
					push(&c, rst);

				}
			}
			continue;
		}
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			rst = ch - '0';
			push(&c, rst);
			continue;
		}

		num1 = pop(&c);
		num2 = pop(&c);

		switch (ch) {
			
			case '+': rst = num1 + num2; 
				break;
			
			case '-': rst = num1 - num2;
				break;
			
			case '*': rst = num1 * num2; 
				break;
			
			case '/': rst = num1 / num2; 
				break;
		}

		push(&c, rst);
	}

	return pop(&c);
}

void assignment_is_token (char assignmenti[]) {

	int equlchek = 0;
	int flag = 0;
	int tokenlist_index = 0; 
	char tokenlist[3][max_size] = {NULL, };
	char postfix[30];
	
	/*가장먼저 치환문이 맞는지 판별. 조건은 = 을 보고 판단*/
	
	for (int i = 0; i < 100; i++) {
		if (assignment[i] == '=') {
			equlchek++;
		}
	}
	
	if (equlchek != 1) {
		printf("치환문 조건에 어긋납니다.\n");
	}

	char* token = strtok(assignment, "=");

	while (token != NULL) {
		strcpy(tokenlist[tokenlist_index], token);
		tokenlist_index++;
		token = strtok(NULL, "=");
	}
	// =을 기준으로 tokenlist[0]에는 오른쪽 문자열, tokenlist[1]에는 수식이 들어감.

	if (tokenlist[0][1] != NULL) { //문자열에서 알파벳 하나가 아니라 두자 이상이면 조건만족x
		printf("variable is not single 변수가 알파벳 하나가아닙니다 \n"); 
	}
	else {
		varray[varray_index].alph = tokenlist[0][0]; // 모든조건 만족시 구조체 배열에 담음
	}

	if (!is_not_opertor(tokenlist[1])) {
		int result = 0;

		infix_to_postfix(tokenlist[1], postfix);
		result = calculate(postfix);
		varray[varray_index].num = result;
		varray_index++;
	}
	else {
		varray[varray_index].num = atoi(tokenlist[1]);
		varray_index++;
	}
}

int rst (char assigment) {
	int tokenlist_index = 0;
	int result = 0;
	char tokenlist[3][max_size] = { NULL, };
	char postfix[30];

	char* token = strtok(assignment," ");

	while (token != NULL) {
		strcpy(tokenlist[tokenlist_index], token);
		tokenlist_index++;
		token = strtok(NULL, " ");
	}
	infix_to_postfix(tokenlist[1], postfix);
	result = calculate(postfix);
	return result;

}
int main() {
	while (1) {	
		gets(assignment);
		if (strncmp(chek_print, assignment, 5) == 0) {
			int t = 0;
			t = rst(assignment);
			printf("%d\n", t);
		}
		else {
			assignment_is_token(assignment);
		}
	}
}
