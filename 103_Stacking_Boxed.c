#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXDIMEN 12
#define MAXBOXES 32

int boxes[MAXBOXES][MAXDIMEN];
int dis[MAXBOXES][MAXBOXES];
int path[MAXBOXES][MAXBOXES];

int n, k, i, j, l, max, maxI, maxJ;

int mycmp(const void *p1, const void *p2){
	return (*(int *)p1 - *(int *)p2);
}

void isNested(){
	for (i = 0; i < k; ++i) 
		for (j = 0; j < k; ++j)
			if (i == j) dis[i][i] = 0;
			else {
				for (l = 0; l < n; ++l)
					if (boxes[i][l] >= boxes[j][l])
						break;
				if (l == n) {
					dis[i][j] = 1;
					max = 1;
					maxI = i;
					maxJ = j;				
				}
				else dis[i][j] = 0;
			}
}

void floyd(){
	for (l = 0; l < k; ++l)
		for (i = 0; i < k; ++i){
			if (!dis[i][l]) continue;		
			for (j = 0; j < k; ++j) {
				if (!dis[i][j] || !dis[l][j]) continue;
				if (dis[i][j] < dis[i][l] + dis[l][j]){
					dis[i][j] = dis[i][l] + dis[l][j];
					path[i][j] = path[i][l];
					if (dis[i][j] > max){
						max = dis[i][j];
						maxI = i;
						maxJ = j;
					}
				}
			}
		}
}

int main(){

	// freopen("103_data", "r", stdin);
	while (scanf("%d%d", &k, &n) != EOF){

		// get input
		for (i = 0; i < k; ++i){
			for (j = 0; j < n; ++j)
				scanf("%d", &boxes[i][j]);
			qsort(boxes[i], n, sizeof(int), mycmp);
		}

		// initialize distance and path
		max = 0;
		maxI = maxJ = 0;		
		isNested();
		for (i = 0; i < k; ++i)
			for (j = 0; j < k; ++j)
				path[i][j] = j;		

		// apply floyd algorithm and find maximum distance
		floyd();
		
		// print maximum distance and path
		printf("%d\n%d", max + 1, maxI + 1);
		
		if (max) {
			while (path[maxI][maxJ] != maxJ){
				maxI = path[maxI][maxJ];
				printf(" %d", maxI + 1);
			}
			printf(" %d", maxJ + 1);
		}
		putchar('\n');
	}	
	return 0;
}
