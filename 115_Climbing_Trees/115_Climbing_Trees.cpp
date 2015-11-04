// Wrong Anwser
#include <cstdio>
#include <map>
#include <string>
#include <cstring>
#include <cstdlib>

#define MAXSTRLEN 32
#define MAXNODES 301
#define MAXLOG 9

using std::string;
using std::map;

map<string, int> names;
map<string,int>::iterator it;
int L[MAXNODES], P[MAXNODES][MAXLOG];
int iName = 1, childI, i, j, k, parentI;
int m, n;
int parent[MAXNODES];
char childName[MAXSTRLEN];
char parentName[MAXSTRLEN];

int query (int p, int q){
    int tmp, log;

    if (L[p] < L[q])
        tmp = p, p = q, q = tmp;

    // find the value of log(L[p])
    for (log = 1; 1 << log <= L[p]; ++log);
    --log;

    for (j = log; j >= 0; --j)
        if (L[p] - (1 << j) >= L[q])
            p = P[p][j];

    if (p == q) return p;

    for (j = log; j >= 0; --j)
        if (P[p][j] && P[p][j] != P[q][j])
            p = P[p][j], q = P[q][j];

    if ((parent[p] != parent[q]) ||
        parent[p] == 0) return -1;
    else return parent[p];
}

int main(){
    // freopen("115_data", "r", stdin);
    while (scanf("%s %s", childName, parentName),
            strcmp(childName, "no.child")){
        string s1(childName);
        if ((it = names.find(s1)) == names.end()){
            names[s1] = iName;
            childI = iName++;
        }
        else
            childI = it->second;
        string s2(parentName);
        if ((it = names.find(s2)) == names.end()){
            names[s2] = iName;
            parentI = iName++;
        }
        else
            parentI = it->second;
        // build parent-child relationships
        parent[childI] = parentI;
        P[childI][0] = parentI;
    }

    // bottom up dynamic programing
    for (j = 1; j << 1 < iName; ++j)
        for (i = 1; i < iName; ++i){
            if (P[i][j - 1])
                P[i][j] = P[P[i][j-1]][j - 1];
        }

    // get levels of all nodes
    for (i = 1; i < iName; ++i){
        k = i;
        do{
            j = parent[k];
            if (L[j]){
                L[i] += (L[j] + 1);
                L[k] = L[j] + 1;
                break;
            }
            else
                L[i]++;
            k = j;
        }while (k);
    }

    while (scanf("%s %s", childName, parentName) != EOF){
        string s1(childName);
        string s2(parentName);
        if (names.find(s1) == names.end()
            || names.find(s2) == names.end()){
            printf("no relation\n");
            continue;
        }
        childI = names[s1];
        parentI = names[s2];

        if (childI == parentI ||
            (parent[childI] == 0 && parent[parentI] == 0))
            printf("no relation\n");
        else if (parent[childI] == parent[parentI])
                printf("sibling\n");
        else{
            k = query(childI, parentI);
            if (k == childI){
                j = L[parentI] - L[childI];
                if(j == 1)
                    printf("parent\n");
                else{
                    for (i = 0; i < j - 2; ++i)
                        printf("great ");
                    printf("grand parent\n");
                }
            }
            else if (k == parentI){
                j = L[childI] - L[parentI];
                if(j == 1)
                    printf("child\n");
                else{
                    for (i = 0; i < j - 2; ++i)
                        printf("great ");
                    printf("grand child\n");
                }
            }
            else if (k == -1)
                printf("no relation\n");
            else{
                m = L[childI] - L[k] - 1;
                n = L[parentI] - L[k] - 1;
                if (m > n){
                    i = n;
                    j = m - n;
                }
                else{
                    i = m;
                    j = n - m;
                }
                printf("%d cousin", i);
                if (j)
                    printf(" removed %d", j);
                putchar('\n');
            }
        }

    }
    return 0;
}
