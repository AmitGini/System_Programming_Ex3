#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

// Node & StrList Data Structures
typedef struct _Node {
    char* _data;
    struct _Node* _next;
} Node;

struct _StrList {
    Node* _head;
    size_t _size;
};

// Allocation for the node and its data
Node* Node_alloc(char* data, Node* next) {
    Node *pNode = (Node*)malloc(sizeof(Node)); // Memory allocation for the node

    if (pNode == NULL) {// Check Failure to allocate memory
        fprintf(stderr, "Error allocating memory for new node\n");
        return NULL;
    }

    pNode -> _data = (char*)malloc(strlen(data) + 1);  //allocate memory for the data field of the node

    if(pNode -> _data == NULL){
        fprintf(stderr, "Error allocating memory for node data" );
        free(pNode);  // case allocation data failed, node allocation of the memory freed
        return NULL;
    }

    strcpy(pNode -> _data, data);  // copying the data to the node field
    pNode -> _next = next;  //sets the next node
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

    pStrList -> _head = NULL;
    pStrList -> _size = 0;
    return pStrList;
}

void StrList_free(StrList* strList){
    if (strList == NULL) return;

    Node* pNode = strList -> _head;
    Node* pTempNode;

    while(pNode != NULL){
        pTempNode = pNode;
        pNode = pNode -> _next;
        free_Node(pTempNode);
    }

    free(strList);
}

size_t StrList_size(const StrList* strList) {
    return strList -> _size;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    Node *pNode = StrList->_head;
    Node* pNewNode = Node_alloc(data, NULL);

    if(pNewNode == NULL) return;  // Null exception handled in the alloc_Node function

    if (pNode == NULL) { // Case head is Null, insert at head
        StrList->_head = pNewNode;

    } else {

        while (pNode->_next != NULL) {  // next to the last node, and insert after it,
            pNode = pNode->_next;
        }

        pNode -> _next = pNewNode;
    }

    StrList -> _size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    size_t sizeStrList = StrList -> _size;
    if (index < 0 || index > sizeStrList) {  // Case 1: Index argument is smaller then 0 or bigger then list size
        printf("Invalid Index");
        return;
    }

    else { // Case 2: index >= 0
        Node* pNode = StrList -> _head;
        Node* pNewNode = Node_alloc(data, NULL);

        if(pNewNode == NULL) return;   // Case 3: Node_allocation failed, Null exception handled in the alloc_Node function

        if(index == 0) {
            pNewNode -> _next = pNode;
            StrList -> _head = pNewNode;
        }

        else if(pNode == NULL) {  // Case 4: pNode is the _head, equal to Null, and index is larger than 0, Fail and exit.
            printf("Head is Null, insertion at index larger then 0 Failed");
            return;
        }

        else {
            int nodeAtIndex = 1;

            while(nodeAtIndex != index) {
                if (pNode == NULL) {
                    printf("Invalid index");
                    return;
                }

                pNode = pNode->_next;
                nodeAtIndex++;
            }

            pNewNode -> _next = pNode ->_next;
            pNode -> _next = pNewNode;
        }

        StrList -> _size++;
    }
}

char* StrList_firstData(const StrList* StrList){
    if(StrList->_head == NULL) {
        printf("No data");
        return NULL;
    }

    return StrList -> _head -> _data;
}

void StrList_print(const StrList* StrList){
    Node* pNode = StrList -> _head;
    int sizeStrList = StrList -> _size;
    if(sizeStrList == 0) return;

    while(pNode != NULL){
        //todo: consider the possibility it will add extra backspace in the end - NEED TO BE CHECKED
        if(pNode -> _data != NULL) printf("%s",pNode -> _data);
        pNode = pNode -> _next;
    }
}

//todo: check in the original file, correctness of the arguments in the functions at file h
void StrList_printAt(const StrList* Strlist,int index){
    size_t sizeStrList = Strlist -> _size;

    if(index < 0 || index > sizeStrList) {
        printf("Index cannot be negative");
        return;
    }

    Node* pNode = Strlist -> _head;
    int nodeAtIndex = 0;

    while(nodeAtIndex != index){
        if(pNode -> _next == NULL){
            printf("There is no data in that index");
            return;
        }

        pNode = pNode -> _next;
        nodeAtIndex++;
    }

    if(pNode -> _data == NULL){
        printf("No data exist in that index");
        return;
    }

    printf("%s",pNode -> _data);
}


int StrList_printLen(const StrList* Strlist){
    size_t sizeStrList = Strlist -> _size;
    if(sizeStrList == 0) return 0;

    Node* pNode = Strlist -> _head;
    if(pNode == NULL) return 0;

    if(pNode -> _data == NULL) return 0;

    size_t charCounter = 0;
    char* tempNodeData;

    while(pNode != NULL){

        tempNodeData = pNode -> _data;
        if(tempNodeData != NULL) charCounter += strlen(tempNodeData);

        pNode = pNode -> _next;
    }

    if(charCounter > INT_MAX) {
        fprintf(stderr,"Number of char is greater then INT_MAX, return Failed!");
        return -1;
    }

    return (int)charCounter;
}

int StrList_count(StrList* StrList, const char* data){
    size_t sizeStrList = StrList -> _size;
    if(sizeStrList == 0) return 0;

    Node* pNode = StrList -> _head;
    if(pNode == NULL) return 0;

    size_t counterSubData = 0;
    char* pTempData = pNode -> _data;
    size_t sizeTempData;  // data length in the node.
    size_t sizeSubData= strlen(data);  // data length of the given argument

    while(pNode != NULL) {

        if(pTempData != NULL) {
            sizeTempData = strlen(pTempData);

            for (int i = 0; i <= sizeTempData - sizeSubData; i++) {
                if (strncmp(&pTempData[i], data, sizeSubData) ==
                    0) {  // Compare substrings of data in pTempData, start for index i
                    counterSubData++;
                }
            }
        }

        pNode = pNode -> _next;
    }

    if(counterSubData > INT_MAX) {
        fprintf(stderr,"Number of char is greater then INT_MAX, return Failed!");
        return -1;
    }
    return (int)counterSubData;
}
