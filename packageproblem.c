//
//  https://www.codeeval.com/open_challenges/114/
//  packageproblem
//
//  Created by Stephan Warren on 12/25/14.
//  Copyright (c) 2014 Stephan Warren. All rights reserved.
//
/*
 PACKAGE PROBLEM
 CHALLENGE DESCRIPTION:
 
 You want to send your friend a package with different things.
 Each thing you put inside the package has such parameters as index number, weight and cost.
 The package has a weight limit.
 Your goal is to determine which things to put into the package so that the total weight is less than or equal to the package limit and the total cost is as large as possible.
 
 You would prefer to send a package which weights less in case there is more than one package with the same price.
 
 INPUT SAMPLE:
 
 Your program should accept as its first argument a path to a filename. The input file contains several lines. Each line is one test case.
 
 Each line contains the weight that the package can take (before the colon) and the list of things you need to choose. Each thing is enclosed in parentheses where the 1st number is a thing's index number, the 2nd is its weight and the 3rd is its cost. E.g.
 
 81 : (1,53.38,$45) (2,88.62,$98) (3,78.48,$3) (4,72.30,$76) (5,30.18,$9) (6,46.34,$48)
 8 : (1,15.3,$34)
 75 : (1,85.31,$29) (2,14.55,$74) (3,3.98,$16) (4,26.24,$55) (5,63.69,$52) (6,76.25,$75) (7,60.02,$74) (8,93.18,$35) (9,89.95,$78)
 56 : (1,90.72,$13) (2,33.80,$40) (3,43.15,$10) (4,37.97,$16) (5,46.81,$36) (6,48.77,$79) (7,81.80,$45) (8,19.36,$79) (9,6.76,$64)
 
 OUTPUT SAMPLE:
  For each set of things that you put into the package provide a list (items’ index numbers are separated by comma). E.g.

 4
 -
 2,7
 8,9
 CONSTRAINTS:
 
 Max weight that a package can take is ≤ 100
 There might be up to 15 items you need to choose from
 Max weight and cost of an item is ≤ 100
 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int inum, iwx100, icost;
} item_t;

static short maxtotalcost = 0;
static short maxtotalweight = 10001;
static char maxcnt = 0;
static char max[15];
static char good[15];

void recurse(item_t * ilist, char icnt, char gcnt, short maxw, short curcost, short curw)
{
    char i, j, icnt_n;
    short curw_n, curcost_n;
    
    item_t * ilist_n = (item_t *) malloc(sizeof(item_t) * icnt);
    //item_t ilist_n[15];
    
//    printf("+ icnt = %d, gcnt = %d, maxw = %d, curcost = %d, curw = %d\n", icnt, gcnt, maxw, curcost, curw);
//    for(i = 0; i < icnt; i++) {
//        printf("  (%d):  #%d, w = %d, c = %d\n", i, ilist[i].inum, ilist[i].iwx100, ilist[i].icost);
//    }
    
    if(curw <= maxw) {
        if(((curcost == maxtotalcost) && (curw < maxtotalweight)) ||
           (curcost > maxtotalcost))
        {
//            printf("New Max: curtotal$ = %d, lasttot = %d:\n", curcost, maxtotalcost);
            for(i = 0; i < gcnt; i++) {
                max[i] = good[i];
//                printf("   %d - %d\n", i, max[i]);
            }
            maxcnt = gcnt;
            maxtotalcost = curcost;
            maxtotalweight = curw;
//            printf(" Maxes: cnt = %d, totalcost = %d, wt = %d\n", maxcnt, maxtotalcost, maxtotalweight);
            
        }
//        else {
//            printf("Failed: curtotal$ = %d, lasttot = %d:\n", curcost, maxtotalcost);
//            for(i = 0; i < gcnt; i++) {
//                printf("   %d - %d\n", i, good[i]);
//            }
//        }
        for(i = 0; i < icnt; i++) {
            curw_n = (short) (((int) curw) + ilist[i].iwx100);
//            printf("    for %d: new = %d, passed in = %d item = %d\n", ilist[i].inum, curw_n, curw, ilist[i].iwx100);
            curcost_n = (short) (((int) curcost) + ilist[i].icost);
            good[gcnt] = ilist[i].inum;
            icnt_n = 0;
            
            for(j = i+1; j < icnt; j++) {
                if((maxw >= curw_n) && (i != j)) {
                    ilist_n[icnt_n].inum = ilist[j].inum;
                    ilist_n[icnt_n].icost = ilist[j].icost;
                    ilist_n[icnt_n].iwx100 = ilist[j].iwx100;
                    icnt_n++;
                }
            }
            recurse(ilist_n, icnt_n, gcnt + 1, maxw, curcost_n, curw_n);
        }
    }
    free(ilist_n);
    //   printf("rec retn\n");
    return;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    FILE *file = fopen(argv[1], "r");
    //    printf("FILE * = %p\n", file);
    char line[1024];
    item_t item[15];
    char * ptr;
    int maxw, iw1, iw2;
    char i;
    while(fgets(line, 1024, file)) {
//        printf("\n\n%s\n", line);
        maxcnt = 0;
        maxtotalcost = 0;
        maxtotalweight = 10001;
        ptr = strtok(line, ":");
        if(sscanf(ptr, "%d", &maxw) != 1) printf("Unexpected.\n");
        maxw *= 100;
        i = 0;
        while(ptr) {
            ptr = strtok(NULL, " ");
            if(!ptr) break;
            if(sscanf(ptr, "(%d,%d.%d,$%d)",
                    &item[i].inum, &iw1, &iw2, &item[i].icost) != 4) printf("U2\n");

            item[i].iwx100 = iw1 * 100 + iw2;
//            printf("%d = (%d, %d, %d)\n", i, item[i].inum, item[i].iwx100, item[i].icost);
            if(item[i].iwx100 <= maxw) i++;
        }
        //       items good icnt gcnt     maxw    curw, curc
        recurse(item, i, 0,  (short) maxw,  0, 0);
//        printf("\nSolution:\n");
//        for(i = 0; i < maxcnt; i++) {
//            printf("   %d: %d\n",i, max[i]);
//        }
//        printf("\nSolution:\n");
        if(maxcnt == 0) printf("-\n");
        else {
            char tbuf[2] = {0,0};
            for(i = 0; i < maxcnt; i++) {
                printf("%s%d",tbuf, max[i]);
                tbuf[0] = ',';
            }
            printf("\n");
        }
    }


}
