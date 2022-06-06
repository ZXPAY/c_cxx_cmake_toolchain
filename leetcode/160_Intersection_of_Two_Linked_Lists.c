#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>


struct ListNode {
    int val;
    struct ListNode *next;
};


struct ListNode *generate_node(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->next = NULL;
    node->val = val;

    return node;
}


struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *nodea = headA;
    struct ListNode *nodeb = headB;

    while(nodea != nodeb) {
        nodea = nodea->next;
        nodeb = nodeb->next;

        if(nodea == nodeb) break;

        if(nodea == NULL) nodea = headB;
        if(nodeb == NULL) nodeb = headA;
    }

    return nodea;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }
    struct ListNode *heada = generate_node(4);
    heada->next = generate_node(1);
    heada->next->next = generate_node(8);
    heada->next->next->next = generate_node(4);
    heada->next->next->next->next = generate_node(5);

    struct ListNode *headb = generate_node(5);
    headb->next = generate_node(6);
    headb->next->next = generate_node(1);
    headb->next->next->next = heada->next->next;

    struct ListNode *result = getIntersectionNode(heada, headb);
    printf("%d\n", result->val);

}

