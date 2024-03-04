#include <stdio.h>

int main() {
	int a = 5;
	int *p = &a;
	printf("O endereço de memoria de %d e %p", a, p);
	return 0;
}
