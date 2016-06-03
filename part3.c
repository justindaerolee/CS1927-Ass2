//part3.c
//z5060887
// do isIn function 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "DLList.h"



int strIsIn(DLList, char *);
//void positionArry(int n, int *p);
void getPos(int n, int j, int *visited, int *p, double *minScaleFDist, DLList l, int numOfFiles);
void fileSize(DLList l, int *s);
int factorial(int n);
double scalFootDist(DLList l, int n, int *p, int numOfFiles);
double minScaleFDist(DLList l, int n, int numOfFiles);


int main(void) {
	DLList l = newDLList();
	DLListAfter(l, "url11", 0, 1);
	DLListAfter(l, "url12", 0, 2);
	DLListAfter(l, "url13", 0, 3);
	//DLListAfter(l, "url14", 0, 4);
	//DLListAfter(l, "url15", 0, 5);
	DLListAfter(l, "3", 0, 0);
	//DLListAfter(l, "url14", 0, 1);
	DLListAfter(l, "url13", 0, 1);
	DLListAfter(l, "url11", 0, 2);
	//DLListAfter(l, "url12", 0, 4);
	DLListAfter(l, "2", 0, 0);
	
	int a = 2;
	int b = 3;
	showDLList(l);

	double d = minScaleFDist(l, b, a);
	printf("%0.6lf\n", d);
	return 0;

}

double scalFootDist(DLList l, int n, int *p, int numOfFiles) {
	double sum = 0;
	char str[50]; // the string array that contained the url string
	DLList visited = newDLList(); // list of the visited urls
	int *sizeT = malloc(sizeof(int) * numOfFiles); // array of the size of the various files, e.g sizeT[0] = the size of the first file.
	fileSize(l, sizeT);
	int i;
	int fI = 0; // file Itterator
	if (!DLListIsEmpty(l)) {
		for (i = 0; i < n; i ++) {
			DLListMoveTo(l, i + 1); // moves the current node in l back
			fI = 0;
			// if the current string has alreday been visited skip
			while (strIsIn(visited, DLListCurrent(l)) || strncmp(DLListCurrent(l), "url", 3) != 0) {
				printf("t %d\n", strncmp(DLListCurrent(l), "url", 3));
				if (strncmp(DLListCurrent(l), "url", 3) != 0) {
					fI ++;
				}
				if (DLListMove(l, 1) == 1) {
					free(sizeT);
					return sum;
				}
			}
			
			strcpy(str, DLListCurrent(l));
			DLListAfter(visited, str, 0, 0);
			sum = fabs((double)getDegree(l)/(double)sizeT[fI] - (double)p[i]/(double)n) + sum;
			// finds the same url in the list
			while (DLListMove(l, 1) == 0) {
				if (strncmp(DLListCurrent(l), "url", 3) != 0) {
					fI ++;
				} else {
					if (strcmp(DLListCurrent(l), str) == 0) {
						sum += fabs((double)getDegree(l)/(double)sizeT[fI] - (double)p[i]/(double)n);
					}
				}
			}
		}
	}
	free(sizeT);
	return sum;
}
//finds the different sets of p and uses the output to find the Scale of Distance
void getPos(int n, int j, int *visited, int *p, double *minScaleFDist, DLList l, int numOfFiles) {
	int i;
	double num;
	if (j == n) {
		if (*minScaleFDist < 0) {
			*minScaleFDist = scalFootDist(l, n, p, numOfFiles);
		} else {
			num = scalFootDist(l, n, p, numOfFiles);
			if (*minScaleFDist > num) {
				*minScaleFDist = num;
			}
		}
	}
	for (i = 0; i < n; i ++) {
		if (visited[i] == 0) {
			p[j] = i + 1;
			visited[i] = 1;
			getPos(n, j + 1, visited, p, minScaleFDist, l, numOfFiles);
			visited[i] = 0;
		}
	}
} // does the string belong in the List, 1 if true, 0 otherwise
int strIsIn(DLList l, char *str) {
	if (DLListIsEmpty(l)) {
		return 0;
	}
	if (strcmp(DLListCurrent(l), str) == 0) {
		return 1;
	}
	while (DLListMove(l, 1) == 0) {
		if (strcmp(DLListCurrent(l), str) == 0) {
			return 1;
		}
	}
	return 0;
}
// wrapper function
double minScaleFDist(DLList l, int n, int numOfFiles) {
	int factN = factorial(n);
	double *minScaleFDist = malloc(sizeof(double));
	*minScaleFDist = -1;
	int i;
	int *visited = malloc(sizeof(int) * n);
	assert(visited != NULL);
	for (i = 0; i < n; i ++) {
		visited[i] = 0;
	}
	int *p = malloc(sizeof(int) * n);
	getPos(n, 0, visited, p, minScaleFDist, l, numOfFiles);
	free(visited);
	double min = *minScaleFDist;
	free(minScaleFDist);
	free(p);
	return min;
}

void fileSize(DLList l, int *s) {
	int i = 0;
	if (!DLListIsEmpty(l)) {
		DLListMoveTo(l, 1);
		if (strncmp(DLListCurrent(l), "url", 3) != 0) {
			sscanf(DLListCurrent(l), "%d", &s[i]);
			i ++;
		}
		while (isNext(l)) {
			DLListMove(l, 1);
			if (strncmp(DLListCurrent(l), "url", 3) != 0) {
				sscanf(DLListCurrent(l), "%d", &s[i]);
				i ++;
			}
		}
		DLListMoveTo(l, 1);
	}
} 
int factorial(int n) {
	if (n > 1) {
		return n * factorial(n - 1);
	}
	return 1;
}
