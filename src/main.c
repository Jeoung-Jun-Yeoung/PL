#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#define max_size 100

typedef struct variable {
	char alph;
	int num;
}variable;

char assignment[max_size] = { 0, };
char tokenlist[3][max_size] = { NULL, };
char stack[max_size];

int tokenlist_index = 0;
int top = -1;

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

/*
			 * 높은 연산자가 rst += tmp되고 낮은게 push되면됨
			 *
			 * if. 스택에 낮은연산자가 있고 높은연산자가 들어올때 이때 그냥 스택에 쌓인다. > 스택에 +가 있고 * 또는 / 가 들어오면 그냥
			 * 쌓인다. > 스택에 -가 있고 * 또는 / 가 들어오면 그냥 쌓인다.
			 *
			 * else if 2. 스택에 높은 연산자가 있고 낮은 연산자가 들어올때. 이때는 스택에서 pop을 해서 아웃풋에넣고 낮은걸 스택에 푸쉬 >
			 * 스택에 * 가있고 + 또는 -가 들어오면 *를 팝하고 아웃풋에 출력하고 + - 를 푸쉬한다. > 스택에 / 가있고 + 또는 -가 들어오면
			 * /를 팝하고 아웃풋에 출력하고 + - 를 푸쉬한다.
			 *
			 * else 같은순위끼리는 그냥 푸쉬한다.


			 */

bool is_vaild_assignment(char assignmenti[]) {
	int i = 0;
	int input = 0;
	/*가장먼저 치환문이 맞는지 판별. 조건은 */
	for (int i = 0; i < 100; i++) {
		if (assignment[i] == '=') {
			printf("right 통과");
			break;
		}
		else if (i == 99) {
			printf("waring = 이 없습니다. \n");
			return false;
		}
	}

	char* token = strtok(assignment, "=");

	while (token != NULL) {
		strcpy(tokenlist[tokenlist_index], token);
		tokenlist_index++;
		token = strtok(NULL, "=");
	}// token 분리
	if (tokenlist[0][1] != NULL) {
		printf("variable is not single 변수가 알파엣하나가아닙니다 \n");
		return false; // 변수가 '알파벳 하나가 아니면 틀림.'
	}

	while (tokenlist[1][i] != NULL) {
		if (tokenlist[1][i] == '.') {
			printf("정수가 아닙니다.");
			return false;
		}
		i++;
	}
	input = atoi(tokenlist[1]);
}

int main() {
	scanf("%s", &assignment);

	printf("\n");
	printf("\n");
	printf("\n");

	is_vaild_assignment(assignment);

	printf("확인");

}