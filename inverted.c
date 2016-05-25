//inverted.c new implementation

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//#include <assert.h>
#include "searchT.h"

// use tree implementation, left is the different words, right is the urls 

Tree inverted(char **);

void printTree(Tree t);

char **getUrl(void); // gets url from collection.txt

int main(void) {
	char **url;
	url = getUrl(); // get url and put it into the array
	Tree t = newTree();
	t = inverted(url);
	printTree(t); // alittle different to the orginal showTree
	freeTree(t);
	return 0;
}
Tree inverted(char **url) {
	Tree t = newTree(); // tree.h
	int i, j, k;
	FILE *fp;
	char c;
	int maxStrLen = 1;
	int count;
	char *str;
	char *word;

	for (i = 0; url[i] != NULL; i ++) {
		fp = fopen(url[i], "r");
		c = fgetc(fp);
		count = 1;
		while (c != EOF) {
			for (count = 0; (c = fgetc(fp)) != '\0'; count ++);
			if (maxStrLen < count) {
				maxStrLen = count;
			}
		}
		str = malloc(sizeof(char) * maxStrLen); // make sure to copy and insert into nodes
		word = malloc(sizeof(char) * maxStrLen); // same as above
		fclose(fp);

		fp = fopen(url[i], "r");
		for (fgets(str, maxStrLen, fp); strncmp(str, "#start Section-2", 16) != 0 &&
			str != NULL; fgets(str, maxStrLen, fp));

		while (fgets(str,maxStrLen, fp) != NULL) {
			for (j = 0; str[j] != '\0'; j ++) {
				for (k = 0; !isspace(str[j]); k ++, j ++) {
					word[k] = tolower(str[j]);
				}
				word[k] = '\0';
				if (!wordIsInT(t, word)) { // make function
					t = insertWordT(t, word); //make function
					t = insetUrlT(t, url[i], word); // make function
				}
				
			}
		}
		free(str);
		free(word);
		fclose(fp);
	}
	return t;
}
void printTree(Tree t) {
	Tree temp1 = t;
	Tree temp2 = t;
	FILE *fp = fopen("invertedIndex.txt", "w");
	while (temp1 != NULL) {
		fprintf(fp, "%s", temp1->str);
		temp2 = temp1->right;
		while (temp2 != NULL) {
			fprintf(fp, " %s", temp2->str);
			temp2 = temp2->right;
		}
		putchar('\n');
		temp1 = temp1->left;
	}
	fclose(fp);
}
char **getUrl(void) { // gets url from collection.txt
	FILE *fp = fopen("collection.txt", "r");
	char c;
	char **url;
	int urlCount = 0;
	int i, j;


	
	for (c = fgetc(fp); c != EOF; c = fgetc(fp)) {
		if (!isspace(c)) {
			urlCount ++;
		}
		while (!isspace(c) || c != EOF) {
			c = fgetc(fp);
		}
	}
	url = malloc(4 * urlCount); // change to be specific
	for (i = 0; i < urlCount; i ++) {
		url[i] = malloc(sizeof(char) * 50);
	}
	fclose(fp);
	fp = fopen("collection.txt", "r");	
	for (c = fgetc(fp), j = 0; c != EOF; c = fgetc(fp), j ++) {
		if (!isspace(c)) {
			for (i = 0; !isspace(c) && c != '\0' && c != EOF; i ++, c = fgetc(fp)) {
				url[j][i] = c;
			}
			url[j][i] = '\0';
		}
	}
	for (i = 0; i < urlCount; i ++) {
		printf("%s ", url[i]);
	}
	putchar('\n');
	return url;
}
