#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#define max_size 100

typedef struct variable {
	char alph[2];
	int num;
	struct variable* next;
}variable;

variable* head = NULL;

char assignment[max_size] = { 0, };
char tokenlist[3][max_size] = { NULL, };
char stack[max_size];
char output [6] = "print";
char is_real_output[6] = {0,};

int tokenlist_index = 0;
int top = -1;
int input;

char possible_alph[26] = { 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

char pop() {
	if (isempty() == true) {
		printf("stack is empty");
	}
	else {
		char temp;
		temp = stack[top];
		top--;
		return temp;
	}
}

void push(char value) {
	if (isfull() == true) {
		printf("stack is full");
	}
	else {
		top++;
		return stack[top] = value;
	}
}

void infix_to_postfix() {




}

/*
			 * ���� �����ڰ� rst += tmp�ǰ� ������ push�Ǹ��
			 *
			 * if. ���ÿ� ���������ڰ� �ְ� ���������ڰ� ���ö� �̶� �׳� ���ÿ� ���δ�. > ���ÿ� +�� �ְ� * �Ǵ� / �� ������ �׳�
			 * ���δ�. > ���ÿ� -�� �ְ� * �Ǵ� / �� ������ �׳� ���δ�.
			 *
			 * else if 2. ���ÿ� ���� �����ڰ� �ְ� ���� �����ڰ� ���ö�. �̶��� ���ÿ��� pop�� �ؼ� �ƿ�ǲ���ְ� ������ ���ÿ� Ǫ�� >
			 * ���ÿ� * ���ְ� + �Ǵ� -�� ������ *�� ���ϰ� �ƿ�ǲ�� ����ϰ� + - �� Ǫ���Ѵ�. > ���ÿ� / ���ְ� + �Ǵ� -�� ������
			 * /�� ���ϰ� �ƿ�ǲ�� ����ϰ� + - �� Ǫ���Ѵ�.
			 *
			 * else �������������� �׳� Ǫ���Ѵ�.


			 */

bool is_vaild_assignment(char assignmenti[]) {
	int i = 0;
	int input = 0;
	/*������� ġȯ���� �´��� �Ǻ�. ������ */
	for (int i = 0; i < 100; i++) {
		if (assignment[i] == '=') {
			printf("right ���");
			break;
		}
		else if (i == 99) {
			printf("waring = �� �����ϴ�. \n");
			return false;
		}
	}

	char* token = strtok(assignment, "=");

	while (token != NULL) {
		strcpy(tokenlist[tokenlist_index], token);
		tokenlist_index++;
		token = strtok(NULL, "=");
	}// token �и�
	if (tokenlist[0][1] != NULL) {
		printf("variable is not single ������ ���ĺ� �ϳ����ƴմϴ� \n");
		return false; // ������ '���ĺ� �ϳ��� �ƴϸ� Ʋ��.'
	}

	while (tokenlist[1][i] != NULL) {
		if (tokenlist[1][i] == '.') {
			printf("������ �ƴմϴ�.");
			return false;
		}
		i++;
	}
	input = atoi(tokenlist[1]);
}

int main() {

	for (int i = 0; i < 6; i++) {
		is_real_output[i] = assignment[i];
	}

	if (strcmp(assignment, is_real_output) == 0) {
		//�ڿ� ���� �������
	}
		
		scanf("%s", &assignment);
		getchar();
		
		is_vaild_assignment(assignment);
		
}