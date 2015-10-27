#include <stdio.h>
#include <string.h>

#define MAXN 22

int X[MAXN], Y[MAXN];
int LCS[MAXN][MAXN];

int main(){
	/* freopen("111_data", "r", stdin); */
	int n, i, j;
	scanf("%d", &n);
	for (i = 1;i <= n; ++i){
		scanf("%d", &j);
		X[j] = i;
	}
	while (scanf("%d", &j) != EOF){
		Y[j] = 1;
		for (i = 2; i <= n; ++i){
			scanf("%d", &j);
			Y[j] = i;
		}
		for (i = 1; i <= n; ++i)
			for (j = 1; j <= n; ++j){
				if (X[i]==Y[j])
					LCS[i][j] = LCS[i-1][j-1] + 1;
				else if(LCS[i][j-1] < LCS[i-1][j])
					LCS[i][j] = LCS[i-1][j];
				else
					LCS[i][j] = LCS[i][j-1];
			}
		printf("%d\n", LCS[n][n]);
	}
	return 0;
}
