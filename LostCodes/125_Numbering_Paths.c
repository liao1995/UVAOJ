#include <stdio.h>
#include <string.h>

#define MAXN 32

char adj[MAXN][MAXN];
int n, num[MAXN];
int city;

void dfs(int start){
	int i;
	for (i = 0; i <= n; ++i)
		if (adj[start][i]){
			if (num[i] > MAXN)
				continue ;
			num[i]++;
			dfs(i);
		}
}

int main(){
	freopen("125_data", "r", stdin); 
	int i, a, b, m, j;
	while (scanf("%d", &m) != EOF){
		memset(adj, 0, sizeof(adj));
		for (i = 0, n = 0; i < m; ++i){
			scanf("%d%d", &a, &b);
			if (a > n) n = a;
			if (b > n) n = b;
			adj[a][b] = 1;
		}
		printf("matrix for city %d\n", city++);
		if (!m) continue;
		for (i = 0; i <= n; ++i){
			memset(num, 0, sizeof(num));
			dfs(i);
			
			if (*num > MAXN) printf("-1");
			else printf("%d", *num);
			for (j = 1; j <= n; ++j)
				if (num[j] > MAXN) printf(" -1");
				else printf(" %d", num[j]);
			putchar('\n');
		}
	}
	return 0;
}
