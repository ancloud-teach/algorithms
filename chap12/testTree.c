#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "../init.h"
#include "./tree.h"

int main(int argc, char **argv)
{
    printf("You can key in the value, which you would be push in\n");
    char line[256];
    char *str = NULL;
    int value = 0;

    Tree tree;
    struct treeNode *nodep, *sucp, *predp;

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
                tree.inorderWalk(rootp);
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
