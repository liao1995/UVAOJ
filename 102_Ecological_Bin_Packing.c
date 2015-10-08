#include <stdio.h>

#define NUM 9
#define CNT 6

int main()
{
	// freopen("102_data", "r", stdin);
	int arr[NUM], min, minIndex, i, totalSum, moves[CNT];
	while (scanf("%d", arr) != EOF){
		totalSum = *arr;
		for (i = 1;i < NUM; ++i){
			scanf("%d", arr + i);
			totalSum += arr[i];
		}
		moves[0] = totalSum - arr[0] - arr[5] - arr[7];
		moves[1] = totalSum - arr[0] - arr[4] - arr[8];
		moves[2] = totalSum - arr[2] - arr[3] - arr[7];
		moves[3] = totalSum - arr[2] - arr[4] - arr[6];
		moves[4] = totalSum - arr[1] - arr[3] - arr[8];
		moves[5] = totalSum - arr[1] - arr[5] - arr[6];
		min = *moves;
		minIndex = 0;
		for (i = 1; i < CNT; ++i)
			if (moves[i] < min){
				min = moves[i];
				minIndex = i;
			}
		switch (minIndex) {
		case 0: 
			printf("BCG %d\n", min);
			break;
		case 1:
			printf("BGC %d\n", min);
			break;
		case 2:
			printf("CBG %d\n", min);
			break;
		case 3:
			printf("CGB %d\n", min);
			break;
		case 4:
			printf("GBC %d\n", min);
			break;
		case 5:
			printf("GCB %d\n", min);
			break;
		}		
	}
	return 0;
}
