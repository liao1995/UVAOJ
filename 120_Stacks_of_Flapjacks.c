#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 200
#define MAXCAKES 35

typedef struct{
	int num;
	int index;
}CakeCom;

char line[MAXSTRLEN];
char *ptr, building;
int n, i, cake[MAXCAKES], j, t;
int temp;
CakeCom com[MAXCAKES];

int mycmp(const void *p1, const void *p2){
	return (((CakeCom *)p1)->num-((CakeCom *)p2)->num);
}

int main(){
	/* freopen("120_data", "r", stdin); */
	while (fgets(line, MAXSTRLEN, stdin)){
		memset(cake, 0, sizeof(cake));
		/* get input */
		building = 0;
		for (ptr = line, n = 1; *ptr; ++ptr){
			if ((*ptr == ' ') && building)
				n++, building = 0;
			else if (*ptr >= '0' && *ptr <= '9'){
				cake[n] = cake[n] * 10 + (*ptr - '0');
				building = 1;
			}
		}
		if (!building) --n;
		if (n <= 0) continue;
		/* build structure */
		for (i = 1; i <= n; ++i){
			com[i].num = cake[i];
			com[i].index = i;
		}
		/* sort structure */
		qsort(&com[1], n, sizeof(CakeCom), mycmp);
		/* construct cake */
		for (i = 1; i <= n; ++i)
			cake[com[i].index] = i;
		fputs(line, stdout);
		for (i = n; i >= 1; --i){
			if (cake[i] == i) continue;
			if (cake[1] != i){
				for (j = 1; j <= n; ++j)
					if (cake[j] == i) break;
				printf("%d ", n - j + 1);
				/* flip */
				for (t = 0; t <= (j - 1) >> 1; ++t){
					temp = cake[1+t];
					cake[1+t] = cake[j-t];
					cake[j-t] = temp;
				}
			}
			printf("%d ", n - i + 1);
			/* flip */
			for (t = 0; t <= (i - 1) >> 1; ++t){
				temp = cake[1+t];
				cake[1+t] = cake[i-t];
				cake[i-t] = temp;
			}
		}
		printf("0\n");
	}
	return 0;
}
