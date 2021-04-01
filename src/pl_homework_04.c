#include <stdio.h>

int main () {
	int z = 0;
	int u = 0;
	int v = 0;

	scanf("%d %d", &u,&v);

	while (u > 0) {
		if(u%2 == 1){
			z = z + v;
		}
		u = u/2;
		v = v*2;
	}
	printf("%d",z);
}
