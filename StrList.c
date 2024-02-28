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
        StrList_free(ptrStrList);
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
    free(strList);
}

size_t StrList_size(const StrList* strList) {
    return strList -> _size;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if(StrList == NULL){
        printf("StrList is NULL\n");
        return;
    }

    Node* ptrNewNode = Node_alloc(data, NULL);
    if(ptrNewNode == NULL) return;  // Null exception handled in the alloc_Node function

    Node* ptrNode = StrList -> _head;
    if (ptrNode == NULL) { // Case head is Null, insert at head
        StrList->_head = ptrNewNode;

    } else {
        while (ptrNode->_next != NULL) {  // next to the last node, and insert after it,
            ptrNode = ptrNode->_next;
        }
        ptrNode -> _next = ptrNewNode;
    }

    StrList -> _size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    size_t sizeStrList = StrList -> _size;
    if (index < 0 || index > sizeStrList) {  // Case 1: Index argument is smaller than 0 or bigger then list size
        printf("Invalid Index\n");
        return;
    }
    else if(data == NULL || strlen(data) < 1){
        printf("Invalid data\n");
        return;

    } else {
        Node* ptrNode = StrList -> _head;
        Node* ptrNewNode = Node_alloc(data, NULL);

        if(ptrNewNode == NULL) return;   // Case 1: Node_allocation failed, Null exception handled in the alloc_Node function

        if(index == 0) {
            ptrNewNode -> _next = ptrNode;
            StrList -> _head = ptrNewNode;

        } else if(ptrNode == NULL) {  // Case 2: ptrNode is the _head, equal to Null, and index is larger than 0, Fail and exit.
            printf("Head is Null, insertion at index larger then 0 Failed");
            return;

        } else {
            int nodeAtIndex = 1;

            while(nodeAtIndex != index) {
                if (ptrNode == NULL) {
                    printf("Invalid index");
                    return;
                }
                ptrNode = ptrNode->_next;
                nodeAtIndex++;
            }
            ptrNewNode -> _next = ptrNode ->_next;
            ptrNode -> _next = ptrNewNode;
        }

        StrList -> _size++;
    }
}

char* StrList_firstData(const StrList* StrList){
    if(StrList == NULL){
        printf("StrList is NULL\n");
        return NULL;

    } else if(StrList->_head == NULL) {
        printf("No data\n");
        return NULL;
    }

    return StrList -> _head -> _data;
}

void StrList_print(const StrList* StrList){
    if(StrList == NULL){
        printf("StrList NULL\n");
        return;

    } else if (StrList -> _size == 0){
        printf("StrList is empty\n");
        return;
    }

    Node* ptrNode = StrList -> _head;
    size_t numOfWords = StrList -> _size;
    char* ptrData = ptrNode ->_data;


    while(numOfWords > 1){
        printf("%s ",  ptrData);
        ptrNode = ptrNode -> _next;
        ptrData = ptrNode -> _data;
        numOfWords--;
    }

    printf("%s\n", ptrData);  // last word will be printed a bit different
}

//todo: check in the original file, correctness of the arguments in the functions at file h
void StrList_printAt(const StrList* Strlist,int index){
    if(Strlist == NULL){
        printf("StrList is NULL\n");
        return;

    } else if(Strlist -> _size == 0){
        printf("StrList is empty\n");
        return;
    }

    size_t sizeStrList = Strlist -> _size;

    if(index < 0 || index > sizeStrList) {
        printf("Index cannot be negative or larger then StrList size: %zu\n", sizeStrList);
        return;
    }

    Node* ptrNode = Strlist -> _head;
    int nodeAtIndex = 0;

    while(nodeAtIndex != index){
        if(ptrNode -> _next == NULL){
            printf("There is no data in that index\n");
            return;
        }
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

    if(charCounter > INT_MAX) {
        fprintf(stderr,"Number of char is greater then INT_MAX, return Failed!");
        return -1;
    }

    return (int)charCounter;
}

int StrList_count(StrList* StrList, const char* data){
    if(StrList == NULL) return 0;

    size_t sizeStrList = StrList -> _size;
    if(sizeStrList == 0) return 0;

    Node* ptrNode = StrList -> _head;
    char* ptrWord = ptrNode -> _data;
    const size_t sizeArgWord = strlen(data);  // data length of the given argument
    size_t sizeWordInList = 0;  // data length in the node - dynamic.
    size_t counterSubWord = 0;

    while(ptrNode != NULL) {

        if(ptrWord != NULL) {
            sizeWordInList = strlen(ptrWord);

            for (int i = 0; i <= sizeWordInList - sizeArgWord; i++) {
                
//                if (strncmp(&ptrWord[i], data, sizeArgWord) == 0) counterSubWord++;  // Compare substrings of data in ptrWord, start for index i
            }
        }
        ptrNode = ptrNode -> _next;
    }

    if(counterSubWord > INT_MAX) {
        fprintf(stderr,"Number of char is greater then INT_MAX, return Failed!");
        return -1;
    }
    return (int)counterSubWord;
}
