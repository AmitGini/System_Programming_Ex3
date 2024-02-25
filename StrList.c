#include "StrList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    // allocate memory for the data field of the node
    pNode -> _data = (char*)malloc(strlen(data) + 1); // + 1 for null terminator
    if(pNode -> _data == NULL){
        fprintf(stderr, "Error allocating memory for node data" );
        free(pNode);  // case allocation data failed, node allocation of the memory freed
        return NULL;
    }

    // allocation succeed, copying the data to the node field
    strcpy(pNode -> _data, data);
    //sets the next node
    pNode -> _next = next;
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
    if (StrList == NULL) return; // Null exception handled in the alloc_StrList function
    Node *pNode = StrList->_head;
    Node* pNewNode = Node_alloc(data, NULL);
    if(pNewNode == NULL) return;  // Null exception handled in the alloc_Node function
    if (pNode == NULL) { // Case head is Null, insert at head
        StrList -> _head = pNewNode;
    } else {
        while (pNode->_next != NULL) {  // next to the last node, and insert after it,
            pNode = pNode->_next;
        }
        pNode -> _next = pNewNode;
    }
    StrList -> _size++;
}

void StrList_insertAt(StrList* StrList, const char* data, int index) {
    if (StrList == NULL) return; // Case 1: StrList argument NULL, exception handled in the StrList_alloc function
    else if (index < 0) {  // Case 2: Index argument is smaller then 0
        printf("Invalid Index");
    } else { // Case index >= 0
        Node* pNode = StrList -> _head;
        Node* pNewNode = Node_alloc(data, NULL);
        if(pNewNode == NULL) return;   // Case Node_allocation failed, Null exception handled in the alloc_Node function
        else if(index == 0) {
            pNewNode -> _next = pNode;
            StrList -> _head = pNewNode;
        }else{
            int nodeAtIndex = 0;
            while(nodeAtIndex != index) {
                if(pNewNode){
                    // todo: incase index > 0, get to the node at index - 1, the next node will point to new node
                    //  and the new node will point to node at index +1
                }
            }
        }
        StrList -> _size++;


    }
}