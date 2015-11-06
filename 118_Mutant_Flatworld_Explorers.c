#include <stdio.h>
#include <string.h>
#define MAXN 52
#define MAXSTRLEN 105

char ins[MAXSTRLEN], *ptr;
char grid[MAXN][MAXN];
int x, y;
int maxX, maxY;
char orien, lost;

int main(){
	/* freopen("118_data", "r", stdin); */
	scanf("%d%d", &maxX, &maxY);
	while (scanf("%d %d %c", &x, &y, &orien)!=EOF){
		scanf("%s", ins);
		lost = 0;
		for (ptr = ins; *ptr; ++ptr){
			switch (*ptr){
			/* turn left */
			case 'L':
				switch (orien){
				case 'N':
					orien = 'W';
					break;
				case 'E':
					orien = 'N';
					break;
				case 'S':
					orien = 'E';
					break;
				case 'W':
					orien = 'S';
					break;
				}
				break;
			/* turn right */
			case 'R':
				switch (orien){
				case 'N':
					orien = 'E';
					break;
				case 'E':
					orien = 'S';
					break;
				case 'S':
					orien = 'W';
					break;
				case 'W':
					orien = 'N';
					break;
				}
				break;
			/* Forward */
			case 'F':
				switch (orien){
				case 'N':
					/* bound */
					if (y == maxY){
						if (!grid[x][y]){
							grid[x][y] = 1;
							lost = 1;
						}
					}
					else ++y;
					break;
				case 'E':
					if (x == maxX){
						if (!grid[x][y]){
							grid[x][y] = 1;
							lost = 1;
						}
					}
					else ++x;
					break;
				case 'S':
					if (!y){
						if (!grid[x][y]){
							grid[x][y] = 1;
							lost = 1;
						}
					}
					else --y;
					break;
				case 'W':
					if (!x){
						if (!grid[x][y]){
							grid[x][y] = 1;
							lost = 1;
						}
					}
					else --x;
					break;
				}
			}
			if (lost) break;
		}
		printf("%d %d %c", x, y, orien);
		if (lost) printf(" LOST");
		putchar('\n');
	}
	return 0;
}
