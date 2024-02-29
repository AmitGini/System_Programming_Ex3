#include <stdio.h>
#include "StrList.h"

void clearInputBuffer();

void insertWordsIntoList(StrList *list, int numOfWords);

int main(){

    StrList* ptrStrList = StrList_alloc();
    StrList* ptrStrList2 = StrList_alloc();

    if(ptrStrList == NULL){
        free(ptrStrList);
        return -1;
    }
    if(ptrStrList2 == NULL){
        free(ptrStrList2);
        return -1;
    }

    int inputCase = -1; // default
    int inputForCases;

    while(inputCase != 0) {
        inputCase = getchar() - '0';
        getchar();

        switch (inputCase) {

            case 1:  // insert number of words and then the words to insert in the last position
                inputForCases = getchar() - '0';
                getchar();
                insertWordsIntoList(ptrStrList, inputForCases);
                break;

            case 2:  // insert word at specific index
                //todo: In case double is being send, it covert to int and still work, check required limitations.
//                StrList_insertAt(ptrStrList, string5,1);
                break;

            case 3:  // printing all the words
                StrList_print(ptrStrList);
                break;

            case 4:  // printing the number of words
                printf("%zu\n", StrList_size(ptrStrList));
                break;

            case 5:  // printing word in a specific index
                StrList_printAt(ptrStrList,4);
                break;

            case 6:  // printing the number of chars in the list
                printf("%d\n",StrList_printLen(ptrStrList));
                break;

            case 7:
//                printf("%d\n",StrList_count(ptrStrList,string6));
                break;

            case 8:
//                StrList_remove(ptrStrList, string7);
                break;

            case 9:
                StrList_removeAt(ptrStrList, 2);
                break;

            case 10:
                break;

            case 11:
                StrList_reverse(ptrStrList);
                break;

            case 12:
                break;

            case 13:
                break;

            case 0:
                break;

            default:
                printf("%d Invalid Case, try again 0 - 13", inputCase);
        }
    }

    StrList_free(ptrStrList);
    StrList_free(ptrStrList2);
    return 0;
}

void insertWordsIntoList(StrList *list, int numOfWords) {

    int numOfInsertions = 0;
    char *word;
    int flagNewWord = 1;
    size_t len = 0;
    size_t capacity = 1;
    char ch;

    while ((ch = getchar()) != EOF) {
        // Ensure there's enough capacity in the buffer for the new character and a null terminator
        if(numOfInsertions != numOfWords) {

            if(flagNewWord == 1){
                word = malloc(1); // Initially allocate a small buffer for the word
                if (!word) {
                    fprintf(stderr, "Failed to allocate memory for the word.\n");
                    return;
                }
                flagNewWord = 0;
            }

            if (len + 1 >= capacity) {
                capacity *= 2; // Increase capacity
                char *newWord = realloc(word, capacity);
                if (!newWord) {
                    fprintf(stderr, "Failed to reallocate memory for the word.\n");
                    free(word);
                    word = NULL;
                    break;
                }
                word = newWord;
            }

            if (ch != ' ') word[len++] = ch; // Add the character to the word in case its not a space or new line

            if (word && (ch == ' ' || ch == '\n') && len > 0) { // Ensure we have a word to add
                word[len] = '\0'; // Null-terminate the word
                StrList_insertLast(list, word);
                numOfInsertions++;
                len = 0;
                capacity = 1;
                free(word); // Free the buffer for the current word
                flagNewWord = 1;
            }
        }

        if(ch == '\n') break;
    }
}

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {printf("Clear: %c\n",c); }
}
