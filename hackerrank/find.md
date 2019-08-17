#include <cstdio>

int main(int argc, char *argv[]) {
	int t;
	scanf("%d", &t);
	while(t--) {
		int x1, y1, x2, y2;
		int x3, y3;
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

		x3 = x1 + 2 * (x2 - x1);
		y3 = y1 + 2 * (y2 - y1);

		printf("%d %d\n", x3, y3);
	}
	return 0;
}
