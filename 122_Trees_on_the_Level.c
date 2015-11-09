#include <stdio.h>
#include <string.h>
#define MAXNODES 260
#define MAXLINE 30

typedef struct Node{
	int num;
	int left;
	int right;
}Node;

int pos, num, i, cur;
Node trees[MAXNODES];
char line[MAXLINE], temp[MAXLINE];
int queue[MAXNODES], front, back;
char notComplete;

int main(){
	/* freopen("122_data", "r", stdin); */
	while (scanf("%s", line) != EOF){
		if (line[1] == ')'){
			/* level travel */
			queue[back++] = 0; /* push root */
			while (front != back){
				if (!trees[queue[front]].num && 
					(trees[queue[front]].left ||
					trees[queue[front]].right)){
					notComplete = 1;
					break;	
				}
				if (trees[queue[front]].left)
					queue[back++] = trees[queue[front]].left;
				if (trees[queue[front]].right)
					queue[back++] = trees[queue[front]].right;
				++front;
			}
			if (notComplete) printf("not complete\n");
			else{
				front = 0;
				printf("%d", trees->num);
				++front;
				while (front < back)
					printf(" %d", trees[queue[front++]].num);
				putchar('\n');
			}
			/* initialize */
			memset(trees, 0, sizeof(trees));
			pos = front = back = 0;
			notComplete = 0;
		}
		else{
			sscanf(line, "(%d,%s", &num, temp);
			cur = 0;
			for (i = 0; temp[i] != ')'; ++i){
				switch (temp[i]){
				case 'L':
					if (!trees[cur].left)
						trees[cur].left = ++pos;
					cur = trees[cur].left;
					break;
				case 'R':
					if (!trees[cur].right)
						trees[cur].right = ++pos;
					cur = trees[cur].right;
					break;
				default:
					break;
				}
			}
			if (trees[cur].num) notComplete = 1;
			trees[cur].num = num;
		}
	}
	return 0;
}
