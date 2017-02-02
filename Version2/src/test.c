#include <stdio.h>

int main() {
	int a, b, c, d;
	int tab[41];
	for(int i = 0; i < 41; i ++)
		tab[i] = 0;
	for (int i = 1; i <= 40; i++) {
		for (int j = 1; j <= 40 && j != i; j++) {
			for (int k = 1; k <= 40 && k != j && k != i; k++) {
				for (int l = 1; l <= 40 && l != k && l != j && l != i; l++) {
					a = i % 10;
					b = j % 10;
					c = k % 10;
					d = l % 10;
					if (a == 0 || a >= 8)
						a = 10;
					if (b == 0 || b >= 8)
						b = 10;
					if (c == 0 || c >= 8)
						c = 10;
					if (d == 0 || d >= 8)
						d = 10;
					tab[a+b+c+d] ++;
				}
			}
		}
	}
	for(int i = 1; i < 41; i++)
		printf("%d : %d\n", i, tab[i]);
	int s = 0;
	for(int i = 0; i < 41; i++)
		s += tab[i];
	printf("somme : %d\n", s);
	return 0;
}