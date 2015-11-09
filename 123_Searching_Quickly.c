#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>

#define MAXIGNORES 55
#define MAXIGNLENS 15
#define MAXKEYWORDS 3200
#define MAXKEYLENS 55
#define MAXTITLES 205
#define MAXTITLENS 655

typedef struct{
	char key[MAXKEYLENS];
	int i;
	int j;
} Keyword;

char ignores[MAXIGNORES][MAXIGNLENS];
Keyword keywords[MAXKEYWORDS], tempKey;
char titles[MAXTITLES][MAXTITLENS];
char temp[MAXKEYLENS], *ptr;
int iIgnore, iTitle, i, len, jLen;
int iKeyword, j, minI, m, n;
char building, ch, buff[MAXTITLENS];

int cmp(const void *p1, const void *p2){
	Keyword *k1 = (Keyword *)p1;
	Keyword *k2 = (Keyword *)p2;
	int CmpRes = strcmp(k1->key, k2->key);
	if (CmpRes) return CmpRes;
	CmpRes = k1->i - k2->i;
	if (CmpRes) return CmpRes;
	return k1->j - k2->j;
}

int main(){
	/* freopen("123_data", "r", stdin); */
	while (fgets(ignores[iIgnore], MAXIGNLENS,
		stdin), ignores[iIgnore][0] != ':'){
		ignores[iIgnore][strlen(ignores[iIgnore])-1]='\0';
		++iIgnore;
	}
	/*
	for (i = 0; i < iIgnore; ++i)
		printf("[%s]\n", ignores[i]);
	*/
	while (fgets(titles[iTitle], 
				MAXTITLENS, stdin)){
		i = 0;
		while (ch = titles[iTitle][i]){
			if ((ch == ' ' || ch == '\n')
				&& building){
				temp[len] = '\0';
				for (j = 0; j < iIgnore; ++j)
					if (!strcasecmp(temp, ignores[j]))
						break;
				if (j == iIgnore){
					strcpy(keywords[iKeyword].key, temp);
					keywords[iKeyword].i = iTitle;
					keywords[iKeyword].j = jLen;
					++iKeyword;
				}
				len = 0;
				building = 0;
			}
			else if(isalpha(ch)){
				temp[len++] = toupper(ch);
				if (!building) jLen = i, building = 1;
			}
			++i;
		}
		/*
		while (titles[iTitle][len]){
			sscanf(titles[iTitle] + len, "%s", temp);
			for (i = 0; i < iIgnore; ++i)
				if (!strcasecmp(temp, ignores[i]))
					break;
			if (i == iIgnore){
				// strcpy(keywords[iKeyword].key, temp); 
				ptr = keywords[iKeyword].key;
				for (j = 0; temp[j]; ++j)
					ptr[j] = toupper(temp[j]);
				ptr[j] = '\0';
				keywords[iKeyword].i = iTitle;
				keywords[iKeyword].j = len;
				++iKeyword;
			}
			len += strlen(temp) + 1;
		}	*/		
		++iTitle;	
	}
	/*
	for (i = 0; i < iKeyword; ++i){
		printf("{%s:%d %d}\n", keywords[i].key, keywords[i].i, keywords[i].j);
	} */
	qsort(keywords, iKeyword, sizeof(Keyword), cmp);
/* selection sort 
	for (i = 0; i < iKeyword; ++i){
		minI = i;
		for (j = i + 1; j < iKeyword; ++j){
			if (strcmp(keywords[j].key, 
				keywords[minI].key) < 0)
				minI = j;			
		}
		tempKey = keywords[i];
		keywords[i] = keywords[minI];
		keywords[minI] = tempKey;
	} */
	for (i = 0; i < iKeyword; ++i){
		m = keywords[i].i;
		n = keywords[i].j;
		for (j = 0; j < n; ++j)
			buff[j] = tolower(titles[m][j]);
		buff[n] = '\0';
		strcat(buff, keywords[i].key);
		for (j = n+strlen(keywords[i].key);
			titles[m][j]; ++j)
			buff[j] = tolower(titles[m][j]);
		buff[j] = '\0';
		printf("%s", buff);			
	}
	return 0;		
}

