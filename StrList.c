#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Node & StrList Data Structures
typedef struct _Node {
    char* _pNode;
    struct _Node* _pNextNode;
} Node;

struct _StrList {
    Node* _pHead;
    size_t _size;
};

// Allocation for the node and its data
Node* Node_alloc(char* data, Node* nextNode) {
    Node *pNode = (Node*)malloc(sizeof(Node)); // Memory allocation for the node
    if (pNode == NULL) {// Check Failure to allocate memory
        fprintf(stderr, "Error allocating memory for new node\n");
        return NULL;
    }

    // allocate memory for the data field of the node
    pNode -> _pNode = (char*)malloc(strlen(data) + 1); // + 1 for null terminator
    if(pNode -> _pNode == NULL){
        fprintf(stderr, "Error allocating memory for node data" );
        free(pNode);  // case allocation data failed, node allocation of the memory freed
        return NULL;
    }

    // allocation succeed, copying the data to the node field
    strcpy(pNode -> _pNode, data);
    //sets the next node
    pNode -> _pNextNode = nextNode;
    return pNode;
}

//Free the memory that been allocated for the node
void free_Node(Node* pNode){
    free(pNode);
}

StrList* StrList_alloc(){
    StrList* pStrList = (StrList*)malloc(sizeof(StrList));
    if(pStrList == NULL){
        fprintf(stderr, "Error allocation memory for string list");
        return NULL;
    }
    pStrList -> _pHead = NULL;
    pStrList -> _size = 0;
    return pStrList;
}

void StrList_free(StrList* strList){
    if (strList == NULL) return;
    Node* pNode = strList -> _pHead;
    Node* pTempNode;
    while(pNode != NULL){
        pTempNode = pNode;
        pNode = pNode -> _pNextNode;
        free_Node(pTempNode);
    }
    free(strList);
}

size_t StrList_size(const StrList* strList) {
    return strList -> _size;
}

void StrList_insertLast(StrList* StrList, const char* data){
    if(StrList != NULL){
        Node* p_nodeStrList = StrList -> _pHead;
    }
}