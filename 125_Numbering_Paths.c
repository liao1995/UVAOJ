#include <stdio.h>
#include <string.h>

#define MAXN 32

char adj[MAXN][MAXN];
int n, num[MAXN][MAXN];
int city;

void floyd(){
	int i, j, k;
	for (k = 0; k <= n; ++k)
		for (i = 0; i <= n; ++i)
			for (j = 0; j <= n; ++j)
				num[i][j] = num[i][j] +
					num[i][k] * num[k][j];				
	for (k = 0; k <= n; ++k)
		if (num[k][k]){
			num[k][k] = -1;
			for (i = 0; i <= n; ++i)
				for (j = 0; j <= n; ++j)
					if (num[i][k] && num[k][j])
						num[i][j] = -1;
		}
}

int main(){
	/* freopen("125_data", "r", stdin); */
	int i, a, b, m, j;
	while (scanf("%d", &m) != EOF){
		memset(adj, 0, sizeof(adj));
		memset(num, 0, sizeof(num));
		for (i = 0, n = 0; i < m; ++i){
			scanf("%d%d", &a, &b);
			if (a > n) n = a;
			if (b > n) n = b;
			adj[a][b] = 1;
			num[a][b] = 1;
		}
		printf("matrix for city %d\n", city++);
		if (!m) continue;
		floyd();
		for (i = 0; i <= n; ++i){
			for (j = 0; j < n; ++j)
				printf("%d ", num[i][j]);
			printf("%d\n", num[i][n]);
		}
	}
	return 0;
}
