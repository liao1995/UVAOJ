#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXSTACK 10240

typedef struct TNode{
	int number;
	struct TNode *left;
	struct TNode *right;
}TNode, *PTNode;

int s1[MAXSTACK];
PTNode s2[MAXSTACK];
int top1, top2, find, I;

void dfs(PTNode tree, int sum){
	if (find) return;
	sum += tree->number;
	if (!tree->left && !tree->right){
		if (sum == I) 
			find = 1;
		return;
	}
	if(tree->left)
		dfs(tree->left, sum);
	if (tree->right)
		dfs(tree->right, sum);
}

void destroyTree(PTNode node){
	if (node == NULL) return;
	destroyTree(node->left);
	destroyTree(node->right);
	free(node);
}

int main(){
	int sum;
	char ch;
	PTNode tempNode;
	/* freopen("112_data", "r", stdin); */
	while (scanf("%d", &I) != EOF){
		top1 = top2 = 0;
		while (scanf("%c", &ch)){
			if (ch == '(' || ch == '-')
				s1[top1++] = ch;
			else if (isdigit(ch)){
				if (s1[top1-1] == '-')
					s1[top1-1] = -(ch-'0');
				else if (s1[top1-1] != '('){
					if(s1[top1-1] > 0)
						s1[top1-1] = s1[top1-1]*10+(ch-'0');
					else
						s1[top1-1] = s1[top1-1]*10-(ch-'0');
				}
				else
					s1[top1++] = ch-'0';
			}
			else if(ch == ')'){
				if (s1[--top1] == '(')
					s2[top2++] = NULL;
				else{
					tempNode = (PTNode) malloc (sizeof(TNode));
					tempNode->right = s2[--top2];
					tempNode->left = s2[--top2];
					tempNode->number = s1[top1];
					s2[top2++] = tempNode;
					top1--;	/* remove '(' */
				}
				if (!top1) break;
			}
		}
		tempNode = s2[0];	/* root of tree */
		if (tempNode == NULL){
			printf("no\n");
			continue;
		}
		sum = 0;
		find = 0;
		dfs(tempNode, sum);
		destroyTree(tempNode);
		if (find) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}
