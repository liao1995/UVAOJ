#include <stdio.h>
#include <limits.h>

#define MAXN 105

int sums[MAXN][MAXN], sum[MAXN], i, j, k;
int localMax, localLocalMax, max, N;
char allNeg;

int main(){
	/* freopen("108_data", "r", stdin); */
	while (scanf("%d", &N) != EOF){
		max = INT_MIN;
		allNeg = 1;
		/* get input */
		for (i = 1; i <= N; ++i)
			for (j = 1; j <= N; ++j){
				scanf("%d", &k);
				sums[i][j] = sums[i - 1][j] +  k;
				if (k >= 0) allNeg = 0;
				if (allNeg && k > max) max = k;
			}
		/* special case */
		if (allNeg){
			printf("%d\n", max);
			continue;
		}

		max = 0;
		/* main algorithm */
		for (i = 1; i <= N; ++i)
			for (j = i; j <= N; ++j){
				for (k = 1; k <= N; ++k)
					sum[k] = sums[j][k] - sums[i - 1][k];
				localMax = localLocalMax = 0;
				for (k = 1; k <= N; ++k){
					localLocalMax += sum[k];
					if (localLocalMax > localMax)
						localMax = localLocalMax;
					else if (localLocalMax < 0)
						localLocalMax = 0;
				}
				if (localMax > max) max = localMax;
			}
		printf("%d\n", max);
	}
	return 0;
}


