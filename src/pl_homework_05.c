#include <stdio.h>
#include <stdlib.h>


int is_leap_year(int year) {
	if ((year % 4 == 0) && (year % 100 !=0) || (year % 400 == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}



int main () {
	int array[42], *p;
	int year;
	int month;
	int day[7] = {5,6,0,1,2,3,4};
	// 2021 year 1 / 1 = 금.
	int leap_month [2][12] = {
		{31,28,31,30,31,30,31,31,30,31,30,31}, // [0][]이 윤년이 아닐때.
		{31,29,31,30,31,30,31,31,30,31,30,31} // [1][]이 윤년일때.
	};

	scanf("%d",&year);
	month = 1;
	int tmp;
	int temp = 0;
	if (year > 2021) {
		for (int i = 2021; i < year; i++) {
			if (is_leap_year(i)) {
				temp += 366;
			}
			else {
				temp += 365;
			}
		}
		int flag = is_leap_year(year);

		for (int i = 0; i < month - 1; i++) {
			temp += leap_month[flag][i];
		}
	}

	else {
		for (int i = 2021 - 1; i > year; i--) {
			if (is_leap_year(i)) {
				temp -= 366;
			}
			else {
				temp -= 365;
			}
		}
		int flag = is_leap_year(year);
		for (int i = 11; i >= month - 1; i--) {
			temp -= leap_month[flag][i];
		}

		temp = (temp % 7) + 7;

	}

	tmp = day[temp % 7];
	p = array;
	int a = is_leap_year(year);
	int num = 1;
	int ber = 1;
	for (int i = 0; i < 42; i++) {
		if (tmp != 0) {
			*p = leap_month[a][(month + 10) % 12] - tmp + 1; // month index값을 맞추기 위해 +10을 해준다.
			tmp--;
		}
		else if (ber <= leap_month[a][month - 1]) {
			*p = ber;
			ber++;
		}
		else {
			*p =  num;
			num++;
		}
		p++;
	}
	p = array;
	for (int i = 0; i < 42; i++) {
		printf("%d ", *p);
		p++;
	}
}
