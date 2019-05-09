#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "../init.h"
#include "./tree/tree.h"

int main(int argc, char **argv)
{
    printf("You can key in the value, which you would be push in\n");
    char line[256];
    char *str = NULL;
    int value = 0;

    uint32_t data[] = {3,7,10,12,14,15,16,17,19,20,21,23,26,28,30,35,38,39,41,47,48,49,50,51,52,53,54,55,56,57,58,59,60};

    Tree tree;
    struct treeNode *nodep, *sucp, *predp;

    for (int i=0; i<sizeof(data)/sizeof(data[0]); i++) {
        struct treeNode * insTreep = (struct treeNode *)malloc(sizeof(struct treeNode));
        memset(insTreep, 0, sizeof(struct treeNode));
        insTreep->key = data[i];
        tree.insert(insTreep);
    }

    while (1) {
        str = gets(line);
        if (str == NULL){
            continue;
        }
        nodep=NULL;
        sucp=NULL;
        predp=NULL;
        
        printf("You key in: %s\n", line);
        if (!isdigit(line[0])) {
            if (line[0] == 'p') {
                struct treeNode *rootp = tree.getRoot();
                tree.inorderWalk(rootp, NULL);
            } else if (line[0] == 'P') {
                struct treeNode *lastp = NULL;
                do {
                    lastp = tree.inorderWalk(lastp);
                    if (NULL == lastp)
                        break;
                    printf("node(0x%x): %d color=%s\t(par=0x%x, left=0x%x, right=0x%x, next=0x%x)--\n", 
                        (uint32_t)lastp, lastp->key, lastp->color==RED?"Red":"Black",
                        (uint32_t)lastp->parentp, (uint32_t)lastp->leftp, (uint32_t)lastp->rightp, (uint32_t)lastp->nextp);
                } while(1);
            } else if (line[0] == 'd') {
                //- delete
                uint32_t val = atoi(&line[1]); 
                nodep = tree.search(tree.getRoot(), val);
                if (NULL != nodep) {
                    nodep = tree.del(nodep);
                    if (NULL != nodep) {
                        APLOG("del node OK. addr=0x%X, val=%d\n", (uint32_t)nodep, nodep->key);
                        free(nodep);
                    } 
                }
            }else {
                if (line[0] == 's'){
                    //- search
                    uint32_t val = atoi(&line[1]); 
                    nodep = tree.search(tree.getRoot(),val);
                }  else if (!strncmp(line, "min", 3)) {
                    nodep = tree.min(tree.getRoot());
                } else if (!strncmp(line, "max", 3)) {
                    nodep = tree.max(tree.getRoot());
                }

                if (NULL != nodep) {
                    APLOG("search result: node addr=0x%X val=%d\n", (uint32_t)nodep, nodep->key);

                    sucp = tree.successor(nodep);
                    if (NULL != sucp) {
                        APLOG("successor: addr=0x%X, val=%d\n", (uint32_t)sucp, sucp->key);
                    } else {
                        APLOG("Can't find the successor!!!\n");
                    }

                    predp = tree.predecessor(nodep);
                    if (NULL != predp) {
                        APLOG("predecessor: addr=0x%X, val=%d\n", (uint32_t)predp, predp->key);
                    } else {
                        APLOG("Can't find the predecessor!!!\n");
                    }
                } else {
                    APLOG("Can't find the node!!!\n");
                }
            }
        } else {
            value = atoi(line);
            printf("insert value=%d + \n", value);
            struct treeNode * insp = (struct treeNode *)malloc(sizeof(struct treeNode));
            memset(insp, 0, sizeof(struct treeNode));
            insp->key = value;
            tree.insert(insp);
        }
    }
}
