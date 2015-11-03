#include <stdio.h>
#include <string.h>

#define MAXN 51
#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3

typedef struct {
	int isBumper;
	int value;
	int cost;
} Bumper;

Bumper bumper[MAXN][MAXN], *pBumper;

int m, n, p, costWall, i, x, y;
int ballX, ballY, ballDirection;
int timeLeft, score, totalScores;

int main(){
	/* freopen("114_data", "r", stdin); */
	scanf("%d%d%d%d", &m, &n, &costWall, &p);
	for (i = 0; i < p; ++i){
		scanf("%d%d", &x, &y);
		bumper[x][y].isBumper = 1;
		scanf("%d%d", &bumper[x][y].value, &bumper[x][y].cost);
	}
	while (scanf("%d%d%d%d", &ballX, &ballY, 
			&ballDirection, &timeLeft) != EOF){
		score = 0;
		while (timeLeft > 1){
			switch (ballDirection) {
			case RIGHT:
				/* hit right wall */
				if (ballX + 1 == m) {
					timeLeft -= costWall;
					ballDirection = DOWN;
				}
				/* hit the bumper */
				else if ((pBumper=&bumper[ballX+1][ballY])->isBumper) {
					timeLeft -= pBumper->cost;
					score += pBumper->value;
					ballDirection = DOWN;
				}
				/* move right*/
				else 
					++ballX;
				break;			
			case UP:
				/* hit top wall */
				if (ballY + 1 == n) {
					timeLeft -= costWall;
					ballDirection = RIGHT;
				}
				/* hit the bumper */
				else if ((pBumper=&bumper[ballX][ballY+1])->isBumper) {
					timeLeft -= pBumper->cost;
					score += pBumper->value;
					ballDirection = RIGHT;
				}
				/* move up*/
				else 
					++ballY;
				break;
			case LEFT:
				/* hit left wall */
				if (ballX == 2) {
					timeLeft -= costWall;
					ballDirection = UP;
				}
				/* hit the bumper */
				else if ((pBumper=&bumper[ballX-1][ballY])->isBumper) {
					timeLeft -= pBumper->cost;
					score += pBumper->value;
					ballDirection = UP;
				}
				/* move left*/
				else 
					--ballX;
				break;			
			case DOWN:
				/* hit bottom wall */
				if (ballY == 2) {
					timeLeft -= costWall;
					ballDirection = LEFT;
				}
				/* hit the bumper */
				else if ((pBumper=&bumper[ballX][ballY-1])->isBumper) {
					timeLeft -= pBumper->cost;
					score += pBumper->value;
					ballDirection = LEFT;
				}
				/* move up*/
				else 
					--ballY;
				break;			
			}
			/* move cost */
			--timeLeft;
		}
		printf("%d\n", score);
		totalScores += score;
	}
	printf("%d\n", totalScores);
	return 0;
}
