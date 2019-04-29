#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "../init.h"
#include "./RBTree.h"

int main(int argc, char **argv)
{
    int maxNum= 100;
    if (argc ==2) {
        int powNum = atoi(argv[1]);
        maxNum = (int)pow(10, powNum);
    }
    
    printf("You can key in the value, which you would be push in\n");
    char line[256];
    char *str = NULL;
    int value = 0;

    uint32_t data[] = {3,7,10,12,14,15,16,17,19,20,21,23,26,28,30,35,38,39,41,47,48,49,50,51,52,53,54,55,56,57,58,59,60};

    Tree tree;
    RBtree rbtree;
    struct treeNode *nodep, *sucp, *predp;

    for (int i=0; i<sizeof(data)/sizeof(data[0]); i++) {
        struct treeNode * insTreep = (struct treeNode *)malloc(sizeof(struct treeNode));
        memset(insTreep, 0, sizeof(struct treeNode));
        insTreep->key = data[i];
        tree.insert(insTreep);
        
        struct treeNode * insRBtreep = (struct treeNode *)malloc(sizeof(struct treeNode));
        memset(insRBtreep, 0, sizeof(struct treeNode));
        insRBtreep->key = data[i];
        rbtree.insert(insRBtreep);
    }
    
    for (int i=61; i<maxNum; i++) {
#if 1        
        struct treeNode * insTreep = (struct treeNode *)malloc(sizeof(struct treeNode));
        memset(insTreep, 0, sizeof(struct treeNode));
        insTreep->key = i;
        tree.insert(insTreep);
#endif        
        struct treeNode * insRBtreep = (struct treeNode *)malloc(sizeof(struct treeNode));
        memset(insRBtreep, 0, sizeof(struct treeNode));
        insRBtreep->key = i;
        rbtree.insert(insRBtreep);
    }
    printf("Init OK\n");

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
                struct treeNode *rootp = rbtree.getRoot();
                rbtree.inorderWalk(rootp);
            } else if (line[0] == 'd') {
                //- delete
                uint32_t val = atoi(&line[1]); 
                nodep = rbtree.search(rbtree.getRoot(), val);
                if (NULL != nodep) {
                    nodep = rbtree.del(nodep);
                    if (NULL != nodep) {
                        APLOG("del node OK. addr=0x%X, val=%d\n", (uint32_t)nodep, nodep->key);
                        free(nodep);
                    } 
                }
            }else {
                if (line[0] == 's'){
                    //- search
                    uint32_t val = atoi(&line[1]); 
                    clock_t start, finish;  
                    double duration;  

                    start = clock(); 
                    nodep = tree.search(tree.getRoot(),val);
                    finish = clock(); 
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;  
                    printf("Tree exec time: %f sec\n", duration);

                    start = clock(); 
                    nodep = rbtree.search(rbtree.getRoot(),val);
                    finish = clock(); 
                    duration = (double)(finish - start) / CLOCKS_PER_SEC;  
                    printf("RBtree exec time: %f sec\n", duration);
        
                }  else if (!strncmp(line, "min", 3)) {
                    nodep = rbtree.min(rbtree.getRoot());
                } else if (!strncmp(line, "max", 3)) {
                    nodep = rbtree.max(rbtree.getRoot());
                }

                if (NULL != nodep) {
                    APLOG("search result: node addr=0x%X val=%d\n", (uint32_t)nodep, nodep->key);

                    sucp = rbtree.successor(nodep);
                    if (NULL != sucp) {
                        APLOG("successor: addr=0x%X, val=%d\n", (uint32_t)sucp, sucp->key);
                    } else {
                        APLOG("Can't find the successor!!!\n");
                    }

                    predp = rbtree.predecessor(nodep);
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
            rbtree.insert(insp);
        }
    }
}
