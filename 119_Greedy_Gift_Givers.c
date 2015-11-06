#include <stdio.h>
#include <string.h>
#define MAXN 12
#define MAXSTRLEN 15

int money[MAXN];
char people[MAXN][MAXSTRLEN];
char name[MAXSTRLEN];
int n, x, i, j, m, k, l;
char flag;

int main(){
	/* freopen("119_data", "r", stdin); */
	while (scanf("%d", &n) != EOF){
		if (!flag)
			flag = 1;
		else
			putchar('\n');
		memset(money, 0, sizeof(money));
		for (i = 0; i < n; ++i)
			scanf("%s", people[i]);
		for (i = 0; i < n; ++i){
			scanf("%s %d %d", name, &x, &m);
			for (j = 0; j < n; ++j)
				if (!strcmp(people[j], name)) break;
			if (m) k = x / m;
			else continue;
			money[j] -= (k * m);
			for (j = 0; j < m; ++j){
				scanf("%s", name);
				for (l = 0; l < n; ++l)
					if (!strcmp(name, people[l])) break;
				money[l] += k;
			}
		}
		for (i = 0; i < n; ++i)
			printf("%s %d\n", people[i], money[i]);
	}
	return 0;
}
