#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXN 1000002

int m, n, x, y, z, N, k, triples, nots, sqrtN;
char belongs[MAXN];

int gcd(int a, int b){
	while (b^=a^=b^=a%=b);
	return a;
}

int main(){
	/* freopen("106_data", "r", stdin); */
	while (scanf("%d", &N) != EOF){
		memset(belongs, 0, sizeof(belongs));
		triples = nots = 0;
		sqrtN = sqrt(N) + 1;
		for (m = 2; m < sqrtN; ++m)
			for (n = (m & 1 ? 2 : 1); n < m; n += 2){
				if (gcd(m ,n) != 1) continue;				
				z = m * m + n * n;
				if (z > N) continue;
				x = m * m - n * n;
				y = 2 * m * n;
				++triples;
				/* if (belongs[z]) continue; */
				for (k = 1; k * z <= N; ++k)
					belongs[x * k] = belongs[y * k] = belongs[z * k] = 1;
			}
		for (k = 1; k <= N; ++k)
			if (!belongs[k]) ++nots;
		printf("%d %d\n", triples, nots);
	}
	return 0;
}
