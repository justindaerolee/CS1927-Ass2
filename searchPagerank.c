// part 1-C of assignment 2 COMP1927 searchPagerank.c
// By : Dae Ro Lee (Justin) z5060887
// Date of completion 29/05/2016

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "DLList.h"

void getUrlStr(char url[], char *str, int start);
DLList cmpLists(DLList a, DLList b);

int main(int argc, char **argv) {
	int i;
	int maxStrLen = 0;
	int count;
	FILE *fp = NULL;
	char c;

	if (argc == 1) {
		return 0;
	}
	FILE *indexFp = fopen("invertedIndex.txt", "r");
	FILE *pageRkFp = fopen("pagerank.txt", "r");

	//finds the length of the longest string in the files to malloc space for string comparison
	fp = indexFp;
	for (i = 0; i < 2 ; i ++) {
		c = fgetc(fp);
		while (c != EOF) {
				for (count = 1; c != EOF && c != '\n'; count ++) {
					c = fgetc(fp);
				}
				if (maxStrLen < count) {
					maxStrLen = count;
				}
				c = fgetc(fp);
		}
		fp = pageRkFp;
	}
	//printf("maxStrLen = %d\n", maxStrLen);
	char *str = malloc(sizeof(char) * maxStrLen); // free after used
	fclose(indexFp);
	fclose(pageRkFp);
	indexFp = fopen("invertedIndex.txt", "r");


	//find argv[1] in invertedIndex.txt 
	//add the url's into a list

	//find argv[2] in invertedIndex.txt
	//using the urls of the corresponding argv[2],
	//if the url is in the List of urls made previously 
	//then make a new list and add it to the list 
	//else nothing, repeat till no more command line arguments 

	char url[50];
	DLList l = newDLList();
	DLList l2 = newDLList();
	int j;
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
	}

	//using pageRkFp compare the first url from pageRkFp with the urls in the list
	// if the url from pageRkFp is in the list print it to stdout
	// finish when after 10 urls are printed or when there is no more urls left
	pageRkFp = fopen("pagerank.txt", "r");
	DLListNode *node = NULL;
	i = 0;
	while (fgets(str, maxStrLen, pageRkFp) != NULL) {
		getUrlStr(url, str, 0);
		node = l2->first;
		while (node != NULL) {
			if (strcmp(node->urlname, url) == 0) {
				printf("%s\n", url);
				i ++;
				if (i >= 10) {
					return 0;
				}
				break;
			}
			node = node->next;
		}
	}
	free(str);
	freeDLList(l2);
	return 0;

}

void getUrlStr(char url[], char *str, int start) {
	int i, j;
	for (i = start; str[i] != '\0' && str[i] != '\n'; i ++) {
		if (str[i] == 'u') {
			for (j = 0; isalnum(str[i]); j ++, i ++) {
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