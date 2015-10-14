#include <stdio.h>
#include <string.h>

#define MAX_X 20006

int heights[MAX_X];
int leftmost, rightmost, L, H, R, i;

int main(){
	/* freopen("105_data", "r", stdin); */
	/* get first group data and initialize */
	scanf("%d %d %d", &L, &H, &R);
	leftmost = L;
	rightmost = R;
	/* memset(heights, 0, sizeof(heights)); */
	for (i = L * 2; i <= R * 2; ++i) 
		heights[i] = H;

	/* build heights array and find leftmost and rightmost */
	while (scanf("%d %d %d", &L, &H, &R) != EOF){
		for (i = L * 2; i <= R * 2; ++i)
			if (heights[i] < H) heights[i] = H;
		if (R > rightmost) rightmost = R;
	}

	/* print out the skyline */
	printf("%d %d", leftmost, heights[leftmost * 2]);
	for (i = leftmost * 2 + 1; i <= rightmost * 2 + 1; ++i){
		if (heights[i] == heights[i - 1]) continue;
		if (heights[i] < heights[i - 1])
			printf(" %d", (i - 1) / 2);
		else printf(" %d", i / 2);
		printf(" %d", heights[i]);
	}
	putchar('\n');
	return 0;
}
