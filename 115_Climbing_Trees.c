#include <stdio.h>
#include <string.h>

#define MAXNAMELEN 32
#define MAXNAMES 301

char names[MAXNAMES][MAXNAMELEN];
int parent[MAXNAMES], levels[MAXNAMES];
char cName[MAXNAMELEN], pName[MAXNAMELEN];
int iName = 1, iChild, iParent;

int findName(char *name){
	int i;
	for (i = 1; i < iName; ++i)
		if (!strcmp(names[i], name))
			return i;
	return -1;
}

int main(){
	/* freopen("115_data", "r", stdin); */
	int i, j, k, m, n;
	while (scanf("%s %s", cName, pName), 
		strcmp(cName, "no.child")){
		iChild = findName(cName);
		if (iChild == -1){
			strcpy(names[iName], cName);
			iChild = iName++;
		}
		iParent = findName(pName);
		if (iParent == -1){
			strcpy(names[iName], pName);
			iParent = iName++;
		}
		parent[iChild] = iParent;
	}
	
	/* calc levels */
    for (i = 1; i < iName; ++i){
        k = i;
        do{
            j = parent[k];
            if (levels[j]){
                levels[i] += (levels[j] + 1);
                levels[k] = levels[j] + 1;
                break;
            }
            else
                levels[i]++;
            k = j;
        }while (k);
    }
    
	while (scanf("%s %s", cName, pName) != EOF){
		iChild = findName(cName);
		iParent = findName(pName);
		/* not find or same names */
		if (iChild == -1 || iParent == -1 
			|| iChild == iParent)
			printf("no relation\n");
		/* sibling */
		else if (parent[iChild] == parent[iParent])
			printf("sibling\n");
		else{
			/* find LCA */
			i = iChild, j = iParent;
			while ((i || j) && (i != j)){
				if (levels[i] > levels[j]) i = parent[i];
				else if (levels[i] < levels[j]) j = parent[j];
				else i = parent[i], j = parent[j];
			}
			/* no realtion */
			if (i != j) printf("no relation\n");
			/* great... grand parent */
			else if (i == iChild){
				j = levels[iParent] - levels[i];
				if (j > 1){
					for (k = 0; k < j - 2; ++k)
						printf("great ");
					printf("grand ");
				}
				printf("parent\n");
			}
			/* great... grand child */
			else if (i == iParent){
				j = levels[iChild] - levels[i];
				if (j > 1){
					for (k = 0; k < j - 2; ++k)
						printf("great ");
					printf("grand ");
				}
				printf("child\n");
			}
			/* cousin */
			else{
				m = levels[iChild] - levels[i] - 1;
				n = levels[iParent] - levels[i] - 1;
				if (m < n) k = m, j = n - m;
				else k = n, j = m - n;
				printf("%d cousin", k);
				if (j) printf(" removed %d", j);
				putchar('\n');
			}
		}
	}
	return 0;
}
