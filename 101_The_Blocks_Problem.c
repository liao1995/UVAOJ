#include <stdio.h>
#define MAXSTACKS 25
#define MAXWORDLEN 5

int stacks[MAXSTACKS][MAXSTACKS];
int where[MAXSTACKS];
int stackTops[MAXSTACKS];
char firstWord[MAXWORDLEN], secondWord[MAXWORDLEN];

// return blocks on top of s
void returnBlocks(int s){
	int stack = where[s];
	int i = stackTops[stack] - 1;
	int element;
	for (; stacks[stack][i] != s; --i){
		element = stacks[stack][i];
		stacks[element][stackTops[element]++] = element;
		stackTops[stack]--;
		where[element] = element;
	}
}

int main()
{
	// freopen("101_data", "r", stdin);
	int i, from, to, top, n, stack, j;
	scanf("%d", &n);
	// initialize
	for (i = 0;i < n; ++i){
		stacks[i][stackTops[i]++] = i;
		where[i] = i;
	}
	while (scanf("%s", firstWord), *firstWord != 'q'){
		scanf("%d %s %d", &from, secondWord, &to);
		if (from == to || where[from] == where[to])
			continue;
		if (*firstWord == 'm'){
			// move a onto b
			if (secondWord[1] == 'n')
				returnBlocks(to);
			returnBlocks(from);
			// move [from] to top of [to]
			stackTops[where[from]]--;
			stacks[where[to]][stackTops[where[to]]++] = from;
			where[from] = where[to];
		}
		else{
			// pile a onto b
			if (secondWord[1] == 'n')
				returnBlocks(to);
			stack = where[from];
			for (i = 0; i < stackTops[stack]; ++i)
				if (stacks[stack][i] == from)
					break;
			top = i;
			for (; i < stackTops[stack]; ++i) {
				stacks[where[to]][stackTops[where[to]]++] = stacks[stack][i];
				where[stacks[stack][i]] = where[to];
			}
			stackTops[stack] = top;
		}
	}
	for (i = 0; i < n; ++i){
		printf("%d:", i);
		for (j = 0; j < stackTops[i]; ++j)
			printf(" %d", stacks[i][j]);
		putchar('\n');
	}
	return 0;
}
