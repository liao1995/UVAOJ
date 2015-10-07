#include <stdio.h>

int main()
{
	// freopen("100_data", "r", stdin);
	int i, j, k, n, min, max, len, maxLen;
	while (scanf("%d %d", &i, &j) != EOF){
		max = i > j ? (min = j, i):(min = i, j);
		maxLen = 0;
		for (n = min; n <= max; ++n){
			k = n;			
			len = 1;
			while (k != 1){
				if (k & 1)
					k = (k << 2) - k + 1;
				else
					k >>= 1;
				++len;
			}
			if (len > maxLen)
				maxLen = len;
		}
		printf("%d %d %d\n", i, j, maxLen);
	}
	return 0;
}
