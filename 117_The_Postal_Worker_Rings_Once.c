#include <stdio.h>
#include <string.h>
#define MAXN 30
#define MAXLEN 32
#define INF 10000

int adj[MAXN][MAXN];
int degree[MAXN];
char str[MAXLEN];
int len, sum, start, end, min, v, i;
char visited[MAXN], find;
int dis[MAXN];


int main(){
	/* freopen("117_data", "r", stdin); */
	while (scanf("%s", str) != EOF)
		if (strcmp(str, "deadend")){
			len = strlen(str);
			adj[*str-'a'+1][str[len-1]-'a'+1] = len;
			adj[str[len-1]-'a'+1][*str-'a'+1] = len;
			++degree[*str-'a'+1];
			++degree[str[len-1]-'a'+1];
			sum += len;
		}
		else{
			start = find = 0;
			for (i = 1; i < MAXN; ++i)
				if (degree[i]&1){
					find = 1;
					if (start){ end = i; break;}
					else start = i;
				}
			if (find){
				/* Dijkstra's algorithm */
				for (i = 1; i < MAXN; ++i)
					if (adj[start][i]) dis[i] = adj[start][i];
					else dis[i] = INF;
				
				while (1){
					min = INF; visited[start] = 1;
					for (i = 1; i < MAXN; ++i)
						if (!visited[i] && dis[i] < min){
							min = dis[i];
							v = i;		
						}
					/* all vertices has been visited */	
					if (min == INF) break;
					/* run algorithm */
					visited[v] = 1;
					for (i = 0; i < MAXN; ++i)
						if (!visited[i] && adj[v][i])
							if(dis[i] > min + adj[v][i])
								dis[i] = min + adj[v][i];
				}
				printf("%d\n", sum + dis[end]);
			}
			else printf("%d\n", sum);
			sum = 0;
			memset(degree, 0, sizeof(degree));
			memset(visited, 0, sizeof(visited));
			memset(adj, 0, sizeof(adj));
		}
	return 0;
}
