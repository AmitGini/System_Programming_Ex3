#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0



// Node & StrList Data Structures
typedef struct Node {
    char *_data;
    struct Node *_next;
} Node;

struct _StrList {
    Node *_head;
    size_t _size;
};

void free_Node(Node *Node);
Node *Node_alloc(const char *data, Node *next);


// Allocation memory for node and data
Node *Node_alloc(const char *data, Node *next) {
    if(data == NULL){
        fprintf(stderr, "Error, Data is NULL\n");
        return NULL;
    }

    Node *ptrNode = (Node*)calloc(1,sizeof(Node)); // Memory allocation for the node

    if (ptrNode == NULL) {// Check Failure to allocate memory
        fprintf(stderr, "Error, Allocation memory for new node failed\n");
        return NULL;
    }

    char* ptrData = (char*)calloc(1,strlen(data) + 1);  // Memory allocation for the data field of node

    if(ptrData == NULL){
        fprintf(stderr, "Error allocating memory for node data\n" );
        free_Node(ptrNode);  // node and data field being freed in free_Node function
        return NULL;
    }

    strcpy(ptrData, data);  // copying the data to the node field
    ptrNode -> _data = ptrData;  // pointer to the data of the node
    ptrNode -> _next = next;  //sets the next node
    return ptrNode;
}

//Free the memory that been allocated for the node and for the data
void free_Node(Node* node) {
    if (node != NULL) {
        free(node->_data); // Free the data
        free(node); // Then free the node
    }
}

StrList* StrList_alloc(){
    StrList *ptrStrList = (StrList*)calloc(1,sizeof(StrList));

    if(ptrStrList == NULL){
        fprintf(stderr, "Error allocation memory for string list\n");
        return NULL;
    }

    ptrStrList -> _head = NULL;
    ptrStrList -> _size = 0;
    return ptrStrList;
}

void StrList_free(StrList* StrList) {
    if (StrList != NULL) {
        Node* current = StrList->_head;
        while (current != NULL) {
            Node* next = current->_next;
            free_Node(current); // Assumes free_Node frees the node and its data
            current = next;
        }
        free(StrList); // Don't forget to free the list structure itself
    }
}


size_t StrList_size(const StrList* StrList) {
    return StrList -> _size;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if(StrList == NULL) return;

    Node* ptrNewNode = Node_alloc(data, NULL);
    if(ptrNewNode == NULL) return;

    Node *ptrNode = StrList->_head;
    if(ptrNode == NULL){
        StrList->_head = ptrNewNode;

    } else {
        while (ptrNode->_next != NULL) ptrNode = ptrNode->_next;  // next to the last node, and insert after it,
        ptrNode->_next = ptrNewNode;
    }

    StrList -> _size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if(StrList == NULL) return;
    if (index < 0 || index > StrList -> _size) return;
    if(data == NULL) return;
    if(strlen(data) < 1) return;

    Node* ptrNewNode = Node_alloc(data, NULL);

    if(ptrNewNode == NULL) {
        free(ptrNewNode);
        return;
    }


    Node* ptrNode = StrList -> _head;
    Node* ptrPrevNode = ptrNode;
    int nodeAtIndex = 0;


    while(nodeAtIndex != index) {
        if(ptrNode == NULL) return;
        ptrPrevNode = ptrNode;
        ptrNode = ptrNode->_next;
        nodeAtIndex++;
    }

    ptrNewNode->_next = ptrNode;

    if(index == 0) StrList->_head = ptrNewNode;
    if(index > 0) ptrPrevNode->_next = ptrNewNode;

    StrList -> _size++;
}

char* StrList_firstData(const StrList* StrList){
    if(StrList == NULL) {return NULL;}
    else if(StrList->_head == NULL) {return NULL;}
    else return StrList -> _head -> _data;
}

void StrList_print(const StrList* StrList){
    if(StrList == NULL) {printf("\n");}
    else if (StrList -> _head == NULL) {printf("\n");}

    else{
        Node* ptrNode = StrList -> _head;
        char* ptrData;

        while(ptrNode-> _next != NULL){
            ptrData = ptrNode -> _data;
            printf("%s ",  ptrData);
            ptrNode = ptrNode -> _next;
        }
        ptrData = ptrNode -> _data;
        printf("%s\n", ptrData);  // last word will be printed a bit different
    }
}

//todo: check in the original file, correctness of the arguments in the functions at file h
void StrList_printAt(const StrList* Strlist,int index){
    if(Strlist == NULL) return;
    if(Strlist -> _size == 0) return;

    size_t sizeStrList = Strlist -> _size;

    if(index < 0 || index > sizeStrList) return;

    Node* ptrNode = Strlist -> _head;
    int nodeAtIndex = 0;

    while(nodeAtIndex != index){
        if(ptrNode -> _next == NULL) return;
        ptrNode = ptrNode -> _next;
        nodeAtIndex++;
    }
    printf("%s\n", ptrNode -> _data);
}


int StrList_printLen(const StrList* Strlist){
    if(Strlist == NULL) return 0;

    size_t sizeStrList = Strlist -> _size;
    if(sizeStrList == 0) return 0;

    Node* ptrNode = Strlist -> _head;
    if(ptrNode == NULL) return 0;

    size_t charCounter = 0;
    char* tempNodeData;

    while(ptrNode != NULL){
        tempNodeData = ptrNode -> _data;
        if(tempNodeData != NULL) charCounter += strlen(tempNodeData);
        ptrNode = ptrNode -> _next;
    }

    if(charCounter > INT_MAX) return -1;
    return (int)charCounter;
}

int StrList_count(StrList* StrList, const char* data){
    if(StrList == NULL) return -1;

    size_t sizeStrList = StrList -> _size;
    if(sizeStrList == 0) return 0;

    const int sizeData = strlen(data);  // size of data, the argument in sign of the function

    Node* ptrNodeAtStrList = StrList -> _head;
    char* ptrWordAtNode;
    int sizeWord;
    int countEqualWords = 0;  // initial state

    while(ptrNodeAtStrList != NULL) {
        ptrWordAtNode = ptrNodeAtStrList -> _data;
        sizeWord = strlen(ptrWordAtNode);  // number of chars at the word

        for (int firstCharAt = 0; firstCharAt <= sizeWord - sizeData; firstCharAt++) {  // run until the length of the remaining words is lower of the length of data
            // Compare the sub word start from the first char(index 0) in length of data,
            // and step to the next sub word start from the second char(index 1) and so on.
            if (strncmp(data, &ptrWordAtNode[firstCharAt], sizeData) == 0) countEqualWords++;  // return true if words equal and increase te counter.
        }

        ptrNodeAtStrList = ptrNodeAtStrList -> _next;  // moving to the next node, and the next data.
    }
    return countEqualWords;
}

void StrList_remove(StrList* StrList, const char* data){
    if(StrList == NULL) return;

    const int sizeData = strlen(data);

    if(data == NULL || sizeData == 0) return;

    Node* ptrNode = StrList -> _head;
    Node* ptrPrevNode  = NULL; // will be initialized at the loop, in case there is more than just head
    char* dataAtNode;

    if(ptrNode == NULL) return;

    while(ptrNode != NULL) {
        dataAtNode = ptrNode->_data;

        if ((strlen(dataAtNode) == sizeData) && (strcmp(dataAtNode,data) == 0)) {
            if (ptrPrevNode == NULL) {
                StrList->_head = ptrNode->_next;
                free_Node(ptrNode);
                ptrNode = StrList->_head;
            } else {
                ptrPrevNode->_next = ptrNode->_next;
                free_Node(ptrNode);
                ptrNode = ptrPrevNode->_next;
            }
            StrList->_size--;

        }else {
            ptrPrevNode = ptrNode;
            ptrNode = ptrNode->_next;
        }
    }
}

void StrList_removeAt(StrList* StrList, int index){
    if(StrList == NULL) return;
    if(index < 0 || index >= StrList -> _size) return;

    Node* ptrNode = StrList -> _head;

    if(index == 0){
        StrList->_head = ptrNode->_next;
        free_Node(ptrNode);
        return;
    }

    Node* ptrPrevNode = NULL;
    int nodeAtIndex = 0;

    while(nodeAtIndex != index) {
        if(ptrNode == NULL) return;
        ptrPrevNode = ptrNode;
        ptrNode = ptrNode->_next;
        nodeAtIndex++;
    }

    if(ptrPrevNode == NULL ) return;

    ptrPrevNode->_next = ptrNode->_next;
    StrList->_size--;
    free_Node(ptrNode);
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList1 == NULL || StrList2 == NULL) return TRUE;

    size_t sizeStrList1 = StrList1 -> _size;
    size_t sizeStrList2 = StrList1 -> _size;
    if (sizeStrList1 != sizeStrList2) return FALSE;

    Node* nodeStrList1 = StrList1->_head;
    Node* nodeStrList2 = StrList2->_head;
    if(nodeStrList1 == NULL || nodeStrList2 == NULL) return TRUE;  // we checked both list have the same size, so if head is null, list2 head is null

    char* dataNode1;
    char* dataNode2;
    int sizeDataNode1;
    int sizeDataNode2;

    while(nodeStrList1 != NULL && nodeStrList2 != NULL){  // check 1 of the list is sufficient, wrote for clarity
        dataNode1=nodeStrList1->_data;
        dataNode2=nodeStrList2->_data;
        sizeDataNode1=strlen(dataNode1);
        sizeDataNode2= strlen(dataNode2);
        if(sizeDataNode1 != sizeDataNode2) return FALSE;
        if(strcmp(dataNode1,dataNode2) != 0) return FALSE;
        nodeStrList1 = nodeStrList1->_next;
        nodeStrList2 = nodeStrList2->_next;
    }

    return TRUE;
}

StrList* StrList_clone(const StrList* StrList){
    if (StrList == NULL) return NULL;

    struct _StrList* newList = StrList_alloc();
    if (newList == NULL) return NULL; // Allocation failed, return NULL immediately.

    Node* tempNode = StrList->_head;
    while (tempNode != NULL) {
        // StrList_insertLast makes a deep copy of the data.
        StrList_insertLast(newList, tempNode->_data);
        tempNode = tempNode->_next;
    }
    if (newList->_size != StrList->_size) {
        // Handle insertion failure - case one of the allocation failed, size won't increase
        StrList_free(newList);
        return NULL;
    }
    return newList;
}

void StrList_reverse( StrList* StrList){
    if(StrList == NULL) return;
    if(StrList->_size < 2) return;

    Node *pCurr = StrList->_head;
    Node *pPrev = NULL;
    Node *pNext = NULL;

    while(pCurr){
        pNext = pCurr->_next;
        pCurr->_next = pPrev;
        pPrev = pCurr;
        pCurr = pNext;
    }
    StrList->_head = pPrev;
}

void StrList_sort( StrList* StrList){
    if (StrList == NULL || StrList->_head == NULL || StrList->_head->_next == NULL) {
        // The list is empty, has one element only, or the input is NULL.
        return;
    }

    int swapped;
    Node *current;
    Node *lastPtr = NULL;

    /* Looping until no swaps are needed; then, the list is sorted */
    do {
        swapped = 0;
        current = StrList->_head;

        while (current->_next != lastPtr) {
            if (strcmp(current->_data, current->_next->_data) > 0) {
                // Swap data of nodes if they're in the wrong lexicographical order
                char *temp = current->_data;
                current->_data = current->_next->_data;
                current->_next->_data = temp;

                swapped = 1;
            }
            current = current->_next;
        }

        lastPtr = current;
    }
    while (swapped);
}

int StrList_isSorted(StrList* StrList){
    if(StrList == NULL || StrList->_head == NULL || StrList->_head->_next == NULL) {
        return TRUE;
    }

    Node* tempNode = StrList->_head;
    while(tempNode->_next != NULL){
        // strcmp return the int value of two strings, if positive first string in the function is bigger then the second
        // then return false, since it's not sorted
        if(strcmp(tempNode->_data,tempNode->_next->_data) > 0) return FALSE;
        tempNode = tempNode->_next;
    }

    return TRUE;
}
