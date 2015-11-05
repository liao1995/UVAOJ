#include <stdio.h>
#define MAXM 20
#define MAXN 120

int grid[MAXM][MAXN];
int cost[MAXM][MAXN];
int path[MAXM][MAXN];
int m, n, i, j, min;

int main(){
	/* freopen("116_data", "r", stdin); */
	while (scanf("%d %d", &m, &n) != EOF){
		/* get input and initialize */
		for (i = 1; i <= m; ++i){
			for (j = 1; j <= n; ++j)
				scanf("%d", &grid[i][j]);
			cost[i][n] = grid[i][n];
		}
		/* special case (m == 1, 2) */
		if (m == 1){
			min = grid[1][1];
			printf("1");
			for (i = 2; i <= n; ++i){
				min += grid[1][i];
				printf(" 1");
			}
			printf("\n%d\n", min);
			continue;
		}
		else if (m == 2){
			if (grid[1][1] <= grid[2][1]){
				min = grid[1][1];
				printf("1");
			}
			else{
				min = grid[2][1];
				printf("2");
			}
			for (i = 2; i <= n; ++i){
				if (grid[1][i] <= grid[2][i]){
					min += grid[1][i];
					printf(" 1");
				}
				else{
					min += grid[2][i];
					printf(" 2");
				}
			}
			printf("\n%d\n", min);
			continue;
		}
		/* special case n == 1 */
		if (n == 1){
			min = grid[1][1];
			j = 1;
			for (i = 2; i <= m; ++i)
				if (grid[i][1] < min){
					min = grid[i][1];
					j = i;
				}
			printf("%d\n%d\n", j, min);
			continue;
		}
		
		/* dynamic programming */
		for (j = n - 1; j >= 1; --j){
			/* for the first row */
			cost[1][j] = cost[1][j+1];
			path[1][j] = 1;
			if (cost[2][j+1] < cost[1][j]){
				cost[1][j] = cost[2][j+1];
				path[1][j] = 2;
			}
			if (cost[m][j+1] < cost[1][j]){
				cost[1][j] = cost[m][j+1];
				path[1][j] = m; 
			}
			cost[1][j] += grid[1][j];
			
			/* from second to (m - 1)th row */
			for (i = 2; i < m; ++i){
				cost[i][j] = cost[i-1][j+1];
				path[i][j]  = i - 1;
				if (cost[i][j+1] < cost[i][j]){
					cost[i][j] = cost[i][j+1];
					path[i][j] = i;
				}
				if (cost[i+1][j+1] < cost[i][j]){
					cost[i][j] = cost[i+1][j+1];
					path[i][j] = i + 1;
				}
				cost[i][j] += grid[i][j];
			}
			/* the mth row */
			cost[m][j] = cost[1][j+1];
			path[m][j] = 1;
			if (cost[m-1][j+1] < cost[m][j]){
				cost[m][j] = cost[m-1][j+1];
				path[m][j] = m - 1;
			}
			if (cost[m][j+1] < cost[m][j]){
				cost[m][j] = cost[m][j+1];
				path[m][j] = m;
			}
			cost[m][j] += grid[m][j];
		}
		
		/* find minimum cost */
		min = cost[1][1], j = 1;
		for (i = 2; i <= m; ++i)
			if (cost[i][1] < min){
				min = cost[i][1];
				j = i;
			}
		
		/* print out the result */
		printf("%d", j);
		for (i = 1; i < n; ++i){
			j = path[j][i];
			printf(" %d", j);
		}
		printf("\n%d\n", min);
	}
	return 0;
}
