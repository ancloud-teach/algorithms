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

    while (1) {
        str = gets(line);
        if (str == NULL){
            continue;
        }
        printf("You key in: %s\n", line);
        if (!isdigit(line[0])) {
            if (line[0] == 'p') {
                struct treeNode *rootp = tree.getRoot();
                tree.inorderWalk(rootp);
            } else if (line[0] == 's'){
                uint32_t val = atoi(&line[1]); 
                struct treeNode *nodep = tree.search(tree.getRoot(), val);
                if (NULL != nodep) {
                    printf("search result: node addr=0x%X val=%d\n", (uint32_t)nodep, nodep->key);
                } else {
                    printf("Can't find the node(val=%d)!!!\n", val);
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
