// asignment 2 inverted.c 
// Dae Ro Lee (Justin) z5060887
//

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "graph.h"
#include "queue.h"

void normalise(char *str);
void inverted(Graph g);

int main(int argc, char **argv) {
	FILE *fp = fopen(argv[1], "r");
	inverted(fp);
	fclose(fp);
}
void normalise(char *str) { //normalises to just lower characters 
	int i;
	for (i = 0; str[i] != '\0'; i ++) {
		str[i] = tolower(str[i]);
	}
}
void inverted(Graph g) {
	Queue wordL = newQueue();
	char *str;
	int strLen;
	FILE *fp;
	char str2[100]; // if MAX_CHAR_LEN cannot be defined use another way 
	int i;
	int found = 0;

	// copy a word in the url().txt // also determine the word character length

	enterQueue(wordL,str);
	fprintf("invertedIndex.txt", "%s ", str);
	fprintf("invertedIndex.txt", "%s", ) // first url
	fp = fopen(, "r") //opens the second url from the collection.txt
	while (fgets(str2, 100, fp) != NULL && !found) {
		for (i = 0; str2[i] != '\0'; i ++) {
			if (strncmp(&str2[i], str, strLen)) { //normalise first
				fprintf("invertedIndex.txt", "%s ", ); // prints the url into the txt
				found = 1;
				break;
			}
		}
	}
	// repeat for the next word in the first url then move to the next url etc.
	// check if the word being compared has alreday been searched for, by iterating through
	// the queue, if the queue does not contain the word then repeat.


	FILE *invTxt = fopen("invertedIndex.txt", "w");

}
