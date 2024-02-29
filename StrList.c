#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

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

// Allocation for the node and its data
Node *Node_alloc(const char *data, Node *next) {
    if(data == NULL){
        fprintf(stderr, "Error, Data is NULL\n");
        return NULL;
    }

    Node *ptrNode = (Node*)malloc(sizeof(Node)); // Memory allocation for the node

    if (ptrNode == NULL) {// Check Failure to allocate memory
        fprintf(stderr, "Error, Allocation memory for new node failed\n");
        free(ptrNode);
        return NULL;
    }

    char* ptrData = (char*)malloc(strlen(data) + 1);  // Memory allocation for the data field of node

    if(ptrData == NULL){
        fprintf(stderr, "Error allocating memory for node data\n" );
        free_Node(ptrNode);  // node and data field of node freed
        return NULL;
    }

    strcpy(ptrData, data);  // copying the data to the node field
    ptrNode -> _data = ptrData;  // pointer to the data of the node
    ptrNode -> _next = next;  //sets the next node
    return ptrNode;
}

//Free the memory that been allocated for the node
//todo: need to be tested
void free_Node(Node *node){
    if(node != NULL)
        free(node -> _data);
    free(node);
}

StrList* StrList_alloc(){
    StrList *ptrStrList = (StrList*)malloc(sizeof(StrList));

    if(ptrStrList == NULL){
        fprintf(stderr, "Error allocation memory for string list\n");
        free(ptrStrList);
        return NULL;
    }

    ptrStrList -> _head = NULL;
    ptrStrList -> _size = 0;
    return ptrStrList;
}

//todo: need to be tested
void StrList_free(StrList* strList){
    if (strList != NULL) {
        Node *ptrNode = strList->_head;
        Node *ptrTempNode;

        while (ptrNode != NULL) {
            ptrTempNode = ptrNode;
            ptrNode = ptrNode->_next;
            free_Node(ptrTempNode);
        }
    }
}

size_t StrList_size(const StrList* strList) {
    return strList -> _size;
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

    size_t sizeStrList = StrList -> _size;
    if (index < 0 || index > sizeStrList) return;

    if(data == NULL || strlen(data) < 1) return;

    Node* ptrNewNode = Node_alloc(data, NULL);

    if(ptrNewNode == NULL) return;   // Case 1: Node_allocation failed, Null exception handled in the alloc_Node function

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
    if(StrList == NULL) return NULL;
    if(StrList->_head == NULL) return NULL;
    return StrList -> _head -> _data;
}

void StrList_print(const StrList* StrList){
    if(StrList == NULL) return;
    if (StrList -> _size == 0) return;

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

    while(ptrNode -> _next != NULL) {
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

    size_t sizeStrList = StrList -> _size;
    if (index < 0 || index >= sizeStrList) return;

    Node* ptrNode = StrList -> _head;
    Node* ptrPrevNode = NULL;
    int nodeAtIndex = 0;

    while(nodeAtIndex != index) {
        if (ptrNode == NULL) return;
        ptrPrevNode = ptrNode;
        ptrNode = ptrNode->_next;
        nodeAtIndex++;
    }

    if (index == 0) StrList->_head = ptrNode->_next;
    StrList->_size--;
    if(ptrPrevNode == NULL ) return;

    ptrPrevNode->_next = ptrNode->_next;
    free_Node(ptrNode);

}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2){
    if(StrList1 == NULL || StrList2 == NULL) return 0;

    size_t sizeStrList1 = StrList1 -> _size;
    size_t sizeStrList2 = StrList1 -> _size;
    if (sizeStrList1 != sizeStrList2) return 0;

    Node* nodeStrList1 = StrList1->_head;
    Node* nodeStrList2 = StrList2->_head;
    if(nodeStrList1 == NULL) return 1;  // we checked both list have the same size, so if head is null, list2 head is null

    char* dataNode1;
    char* dataNode2;
    int sizeDataNode1;
    int sizeDataNode2;

    while(nodeStrList1 != NULL && nodeStrList2 != NULL){  // check 1 of the list is sufficient, wrote for clarity
        dataNode1=nodeStrList1->_data;
        dataNode2=nodeStrList2->_data;
        sizeDataNode1=strlen(dataNode1);
        sizeDataNode2= strlen(dataNode2);
        if(sizeDataNode1 != sizeDataNode2) return 0;
        if(strcmp(dataNode1,dataNode2) != 0) return 0;
        nodeStrList1 = nodeStrList1->_next;
        nodeStrList2 = nodeStrList2->_next;
    }
    return 1;
}

//StrList* StrList_clone(const StrList* StrList){
//    return StrList;
//}

void StrList_reverse( StrList* StrList){
    if(StrList == NULL) return;
    size_t sizeList = StrList->_size;
    if(sizeList < 1) return;
    for(int i = 0; i < sizeList; i++){
        StrList_insertAt(StrList,StrList->_head->_data,sizeList-i);
        StrList_removeAt(StrList,0);
    }
}

//void StrList_sort( StrList* StrList);
//
//int StrList_isSorted(StrList* StrList);
