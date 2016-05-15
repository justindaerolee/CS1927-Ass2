/*
PageRank(d, diffPR, maxIterations)

            Read "web pages" from the collection in file "collection.txt"
            and build a graph structure using Adjacency List Representation

            N = number of urls in the collection
            diff = 0;
            For each url pi in the collection
                PR(pi) = 1/N  ;

            iteration = 0;
            While (iteration < maxIteration AND diff >= diffPR)
                iteration++;
                For each url pi in the collection
                    PR_old = PR(pi);
                    sum = 0 ;
                    for each url pj pointing to pi (ignore self-loops and parallel edges)
                        sum = sum + PR(pj) / out-degree-of(pj);

                    PR(pi) = (1-d)/N + d * sum
                    diff = diff + Abs(PR_old - PR(pi);
*/
#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

PageRank(d, diffPR, maxIterations) {

    FILE * collection;
    int URLs[];
    int i;
    int URLcount = 0;

    collection = fopen ("collection.txt", "r");
    for (i = 0;;i++) {
        URL[i] = fgetc(collection);
        URLcount++;
        if (feof(collection)) {
            break;
        }
    }
    fclose(collection);
    Graph webPages = newGraph(URLcount);

    int pR[URLcount];
    for (i = 0; i <= URLcount; i++) {
        pR[i] = (1/URLcount);
    }
}
