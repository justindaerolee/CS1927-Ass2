// tfdi.c
// part 2 of assignment 2 of COMP1927
// 30/05/2016

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "DLList.h"

int termf(char *url, char *term); //gets the term frequency in the url
// ".txt" at the end of the url is added in the function
DLList getListOfurls(int argc, char **argv);
// finds the urls that that contain the following strings

// the functions below are used within the functions that mentioned above
// dont worry about the functions below unless you feel the need to use it
void getUrlStr(char url[], char *str, int start);
// gets the url in the string provided, int start determines where to begin the search
DLList cmpLists(DLList a, DLList b);
// compares two lists, all common nodes are added to a new list which is returned at the end
// of the function
int maxLen(char *fileN); // returns the largest length of the string in a given file
// ".txt" is not added in the function, must be done prior

/*
int main(int argc, char **argv) { //used to test
	char *url = "url11";
	char *str = "mars";
	printf("term f of mars in url11, %d\n", termf(url, str));
	DLList l = getListOfurls(argc, argv);
	if (DLListIsEmpty(l)) {
		printf("error\n");
	}
	showDLList(l);
	return 0;
} */

int termf(char *url, char *term) { // finds the term frequency in the url
	char urlTxt[54];
	strcpy(urlTxt, url);
	strcat(urlTxt, ".txt"); //adds in the .txt so that the file can be opened
	int termf = 0;

	int maxStrLen = maxLen(urlTxt);
	printf("maxStrLen = %d\n", maxStrLen);
	char *str = malloc(sizeof(char) * (maxStrLen + 1)); // make sure to copy and insert into nodes
	assert(str != NULL);
	char *word = malloc(sizeof(char) * (maxStrLen + 1)); // same as above
	assert(word != NULL);

	FILE *urlFile = fopen(urlTxt, "r");
	assert(urlFile != NULL);
	int j, k;
	while (fgets(str, maxStrLen, urlFile) != NULL && strncmp(str, "#start Section-2", 16) != 0);
	while (fgets(str,maxStrLen, urlFile) != NULL) {
		if (strncmp(str, "#end Section-2", 14) == 0) {
			break;
		}
		for (j = 0; str[j] != '\0'; j ++) {
			if (isalnum(str[j])) {
				for (k = 0; isalnum(str[j]); k ++, j ++) {
					word[k] = tolower(str[j]);
				}
				word[k] = '\0';
				if (strcmp(term, word) == 0) {
					termf ++;
				}
			}
			
		}
	}
	free(str);
	free(word);
	fclose(urlFile);
	return termf;
}
void getUrlStr(char url[], char *str, int start) {
	int i, j;
	for (i = start; str[i] != '\0' && str[i] != '\n'; i ++) {
		if (str[i] == 'u') {
			for (j = 0; isalnum(str[i]); j ++, i ++) { //would url contain just words and numbers??
				url[j] = str[i];
			}
			url[j] = '\0';
			break;
		}
	}
}
DLList cmpLists(DLList a, DLList b) {
	if (DLListIsEmpty(b)) {
		return a;
	}
	DLList new = newDLList();
	DLListNode *temp = a->first;
	DLListNode *temp2 = b->first;
	while (temp != NULL) {
		temp2 = b->first;
		while (temp2 != NULL) {
			if (strcmp(temp->urlname, temp2->urlname) == 0) {
				DLListAfter(new, temp->urlname, 0);
				break;
			}
			temp2 = temp2->next;
		}
		temp = temp->next;
	}
	freeDLList(a);
	freeDLList(b);
	
	return new;
}
DLList getListOfurls(int argc, char **argv) {
	char url[50];
	int maxStrLen = maxLen("invertedIndex.txt");
	char *str = malloc(sizeof(char) * (maxStrLen + 1));
	DLList l = newDLList();
	DLList l2 = newDLList();
	int i, j;
	FILE *indexFp = fopen("invertedIndex.txt", "r");
	assert(indexFp != NULL);
	for (i = 1; i < argc; i ++) {
		while (fgets(str, maxStrLen, indexFp) != NULL) {
			if (strncmp(str, argv[i], strlen(argv[i])) == 0) {
				l = newDLList();
				for (j = 0; str[j] != '\0' && str[j] != '\n'; j ++) {
					if (str[j] == 'u') {
						getUrlStr(url, str, j);
						DLListAfter(l, url, 0);
					}
				}
				if (DLListIsEmpty(l)) { // The word does not exist in the index
					return 0; // Hence there will be no output and the program exits early
				}
				l2 = cmpLists(l, l2);
				break;
			}
		}
		fclose(indexFp);
		indexFp = fopen("invertedIndex.txt", "r");
		assert(indexFp != NULL);
	}
	fclose(indexFp);

	return l2;
}
int maxLen(char *fileN) {
	FILE *fp = fopen(fileN, "r");
	assert(fp != NULL);
	int count = 1;
	int maxStrLen = 0;
	char c = fgetc(fp);
	while (c != EOF) { // check if this really works to get the maxStrLen;
		for (count = 1; c != EOF && c != '\n' && c != '\0'; count ++) {
			c = fgetc(fp);
		}
		if (maxStrLen < count) {
			maxStrLen = count;
		}
		c = fgetc(fp);
	}
	fclose(fp);
	return maxStrLen;
}
