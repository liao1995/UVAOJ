#include <stdio.h>
#include <math.h>

int n, h, N, totalHeights, notWorkCats, l;
double val;

int main(){
	/* freopen("107_data", "r", stdin); */
	while (scanf("%d %d", &h, &n), h){
		if (n == 1){
			/* printf("log(%d) = %lf\n", h, log(h)/log(2)); */
			printf("%d %d\n",(int)ceil(log(h)/log(2)), 2 * h - 1);
			continue;
		}

		N = 2;
		val = log(h)/log(n);
		while (log(N+1)/log(N) - val > 1e-8) ++N;
		printf("%d %d\n", (n-1)/(N-1), (h - n) * N + h);
	}
	return 0;
}
