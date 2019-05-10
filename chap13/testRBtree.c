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
    int maxNum= 20;
    if (argc ==2) {
        int powNum = atoi(argv[1]);
        maxNum = (int)pow(10, powNum);
    }
    
    printf("You can key in the value, which you would be push in\n");
    char line[256];
    char *str = NULL;
    int value = 0;

    Tree tree;
    RBtree rbtree;
    struct treeNode *nodep, *sucp, *predp;

#if 0
    int data[] = {3,7,10,12,14,15,16,17,19,20,21,23,26,28,30,35,38,39,41,47,48,49,50,51,52,53,54,55,56,57,58,59,60};
    for (int i=0; i<sizeof(data)/sizeof(data[0]); i++) {       
        rbtree.insert(data[i], NULL);
    }

#else    
    int *datap = (int*)malloc(sizeof(int)*maxNum);
    int r=0;
    for (int i=0; i<maxNum; i++) {
        r = rand()%maxNum;
        
        nodep = rbtree.search(rbtree.getRoot(), r);
        if (NULL != nodep) {
            datap[i] = -1;
            continue;
        }
        rbtree.insert(r, NULL);
        datap[i] = r;    
    }

    APLOG("tree size=%d\n", rbtree.size());
    for (int i=0; i<maxNum; i++) {
        if (datap[i] < 0)
            continue;
        
        nodep = rbtree.search(rbtree.getRoot(), datap[i]);
        if (NULL == nodep) {
            APLOG("Err cant find the  key(%d), i=%d!!!!\n", datap[i], i);
            return -1;
        }
    }
    int ret = rbtree.check();
    if (ret < 0) {
        APLOG("rbtree check error(%d)\n", ret);
    }

    //- test the delete
    printf("\n");
    APLOG("Check the delete\n");
    for (int i=0; i<maxNum; i++) {
        r = rand()%maxNum;
        if (datap[r] < 0)
            continue;

        //- search all other nodes
        rbtree.del(datap[r]);
        datap[r] = -1;
        for (int j=0; j<maxNum; j++) {
            if (datap[j] < 0)
                continue;
            
            nodep = rbtree.search(rbtree.getRoot(), datap[j]);
            if (NULL == nodep) {
                APLOG("Err cant find the  key(%d), i=%d!!!!\n", datap[j], j);
                return -1;
            }
        } 

        //- check the rbtree
        int ret = rbtree.check();
        if (ret < 0) {
            APLOG("rbtree check error(%d)\n", ret);
            return -2;
        }      
    }   
    for (int i=0; i<maxNum; i++) {
        if (datap[i] < 0){
            continue;
        }
        
        rbtree.del(datap[i]);
        datap[i] = -1;

        //- search all other nodes
        for (int j=0; j<maxNum; j++) {
            if (datap[j] < 0)
                continue;
            
            nodep = rbtree.search(rbtree.getRoot(), datap[j]);
            if (NULL == nodep) {
                APLOG("Err cant find the  key(%d), i=%d!!!!\n", datap[j], j);
                return -1;
            }
        } 

        //- check the rbtree
        int ret = rbtree.check();
        if (ret < 0) {
            APLOG("rbtree check error(%d)\n", ret);
            return -2;
        }
    }
#endif

#if 0    
    for (int i=61; i<maxNum; i++) {
        
        struct treeNode * insTreep = (struct treeNode *)malloc(sizeof(struct treeNode));
        memset(insTreep, 0, sizeof(struct treeNode));
        insTreep->key = i;
        tree.insert(insTreep);
        
        struct treeNode * insRBtreep = (struct treeNode *)malloc(sizeof(struct treeNode));
        memset(insRBtreep, 0, sizeof(struct treeNode));
        insRBtreep->key = i;
        rbtree.insert(insRBtreep);
    }
#endif    
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
                rbtree.inorderWalk(rootp, NULL);
            } else if (line[0] == 'P') {
                struct treeNode *lastp = NULL;
                do {
                    lastp = rbtree.inorderWalk(lastp);
                    if (NULL == lastp)
                        break;
                    rbtree.printNode(lastp);
                } while(1);
            } else if (line[0] == 'd') {
                //- delete
                uint32_t val = atoi(&line[1]); 
                rbtree.del(val);
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
                    APLOG("search result: node addr=0x%X val=%lld\n", (uint32_t)nodep, nodep->key);

                    sucp = rbtree.successor(nodep);
                    if (NULL != sucp) {
                        APLOG("successor: addr=0x%X, val=%lld\n", (uint32_t)sucp, sucp->key);
                    } else {
                        APLOG("Can't find the successor!!!\n");
                    }

                    predp = rbtree.predecessor(nodep);
                    if (NULL != predp) {
                        APLOG("predecessor: addr=0x%X, val=%lld\n", (uint32_t)predp, predp->key);
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
            rbtree.insert(value, NULL);
        }
    }
}
