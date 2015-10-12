#include <stdio.h>
#include <string.h>

#define MAXN 22

double dp[MAXN][MAXN][MAXN];
int path[MAXN][MAXN][MAXN];
int i, j, k, s, n, hasFind;


void floyd(){
	hasFind = 0;
	for (s = 2; s <= n; ++s)
	{
		for (k = 1; k <= n; ++k)
		{
			for(i = 1; i <= n; ++i)
			{
				for (j = 1; j <= n; ++j)
				{
					if (dp[i][j][s] < dp[i][k][s-1]*dp[k][j][1]){
						dp[i][j][s] = dp[i][k][s-1]*dp[k][j][1];
						path[i][j][s] = path[i][k][s-1];
					}
					if (i == j && dp[i][i][s] > 1.01){
						hasFind = 1;
						return ;
					}					
				}
			}
		}
	}
}

int main(){

	/* freopen("104_data", "r", stdin); */
	while (scanf("%d", &n) != EOF){
		/* get input */
		memset(dp, 0, sizeof(dp));		
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j) {
				if (i == j) dp[i][i][1] = 1.0;
				else scanf("%lf", &dp[i][j][1]);
				path[i][j][1] = j;
		}
	
		/* modified floyd algorithm */
		floyd();

		/* print out result */
		if (hasFind){
			printf("%d", i);
			for (j = s, k = i; j >= 1; --j){
				printf(" %d", path[i][k][j]);
				i = path[i][k][j];
			}			
			putchar('\n');
		}
		else
			printf("no arbitrage sequence exists\n");
	}
	return 0;
}
