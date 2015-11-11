#include <stdio.h>
#include <string.h>

#define MAXN 30
#define MAXLINE 300

char map[MAXN], ch;
int imap[MAXN], n;
int indegree[MAXN];
char line[MAXLINE];
char first;
char adj[MAXN][MAXN];
char vis[MAXN];
char temp[MAXN];
int iTemp;
int notFirst;
char maxCh;

void topSort(){
	int k, i, j;
	for (k = 0; k <= maxCh; ++k){
		if (!imap[k]) continue;
		i = imap[k];
		if (!vis[i] && !indegree[i]){
			vis[i] = 1;
			temp[iTemp++] = i;
			if (iTemp == n - 1){
				/* print out */
				for (j = 0; j < iTemp; ++j)
					printf("%c", map[temp[j]]);
				printf("\n");
				iTemp--;
				vis[i] = 0;
				return ;
			}
			/* modified indegree */
			for (j = 1; j <= n; ++j)
				if (adj[i][j]) indegree[j]--;
			topSort();
			vis[i] = 0;
			--iTemp;
			/* modified indegree */
			for (j = 1; j <= n; ++j)
				if (adj[i][j]) indegree[j]++;
		}
	}
}

int main(){
	/* freopen("124_data", "r", stdin); */
	int i, j;
	while (fgets(line, MAXLINE, stdin)){
		n = 1;
		maxCh = 'a';
		memset(imap, 0, sizeof(imap));
		memset(map, 0, sizeof(map));
		for (i = 0; line[i]; ++i)
			if (line[i] >= 'a' && line[i] <= 'z'){
				if (imap[line[i]-'a']) continue;
				map[n] = line[i];		 
				imap[line[i]-'a'] = n++;
				if (line[i] > maxCh) maxCh = line[i];
			}
		maxCh -= 'a';
		/* read pair */
		fgets(line, MAXLINE, stdin);
		memset(adj, 0, sizeof(adj));
		first = 1;
		memset(indegree, 0, sizeof(indegree));
		memset(vis, 0, sizeof(char));
		for (i = 0; line[i]; ++i)
			if (line[i] >= 'a' && line[i] <= 'z'){
				if (first){
					first = 0;
					ch = line[i];
				}
				else{
					adj[imap[ch-'a']][imap[line[i]-'a']] = 1;
					indegree[imap[line[i]-'a']]++;
					first = 1;
				}
			}
		iTemp = 0;
		if (!notFirst) notFirst = 1;
		else putchar('\n');
		topSort();
	}
}

