#include <stdio.h>
#include <string.h>
#define MAXVARS 10

char vars[MAXVARS][MAXVARS*2] = 
	{"", "a", "a,b", "a,b,c",
	 "a,b,c,d", "a,b,c,d,e",
	 "a,b,c,d,e,f","a,b,c,d,e,f,g",
	 "a,b,c,d,e,f,g,h", ""};

char spaces[MAXVARS][MAXVARS*2] =
	{"", "  ", "    ", "      ",
	 "        ", "          ",
	 "            ", "              ",
	 "                ", ""};
	
int M, n;

void printOut(char *var, int j, int numSpaces){
	int cur, i, first;
	char tempVar[MAXVARS], varJ;

	varJ = 'a' - 1 + j;
	
	for (cur = j - 1; cur >= 0; --cur){
		if (cur == j - 1){
			printf("%sif %c < %c then\n", spaces[numSpaces], 
				var[cur-1], varJ);
			strcpy(tempVar, var);
			tempVar[j - 1] = varJ;
			tempVar[j] = '\0';
		}
		else if (cur == 0){
			printf("%selse\n",spaces[numSpaces]);
			tempVar[0] = varJ;
			strcpy(tempVar + 1, var);
		}
		else{
			for (i = 0; i <= cur; ++i) tempVar[i] = var[i];
			tempVar[cur] = varJ;
			for (i = cur + 1; i < j; ++i) tempVar[i] = var[i-1];
			tempVar[j] = '\0';
			printf("%selse if %c < %c then\n", spaces[numSpaces],
				var[cur-1], varJ);
		}
		if (j == n){
			printf("%s  writeln(%c", spaces[numSpaces], tempVar[0]);
			for (i = 1; i < j; ++i)
				printf(",%c", tempVar[i]);
			printf(")\n");
		}
		else printOut(tempVar, j + 1, numSpaces + 1);
	}	
}

int main()
{
	/* freopen("110_data", "r", stdin);
	freopen("110_output", "w", stdout); */
	scanf("%d", &M);
	while (M--){
		scanf("%d", &n);
		puts("program sort(input,output);");
		printf("var\n%s : integer;\nbegin\n", vars[n]);
		printf("  readln(%s);\n", vars[n]);
		if (n == 1) printf("  writeln(a)\n");
		else printOut("a", 2, 1);
		printf("end.\n");
		if (M) putchar('\n');
	}
	return 0;
}

