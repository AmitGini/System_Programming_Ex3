#include <stdio.h>
#include "StrList.h"

#define INSERT_LAST 1
#define INSERT_AT_INDEX 2
#define PRINT_LIST_WORDS 3
#define PRINT_NUM_WORDS 4
#define PRINT_WORD_AT_INDEX 5
#define NUM_CHARS_AT_LIST 6
#define NUM_SUBSTRING_AT_LIST 7
#define REMOVE_WORD_IN_LIST 8
#define REMOVE_WORD_AT_INDEX 9
#define REVERSE_LIST 10
#define DELETE_LIST 11
#define SORT_LIST_LEX 12
#define CHECK_IF_LEX_SORTED 13
#define INVALID_CASE_FAILURE -2
#define EXIT 0
#define DEFAULT_STATE -1

// Declaration of functions for list operations
int readIntegerInput();
char* readWordInput();

int main(){

    StrList* myList = StrList_alloc();
    if (!myList) {
        fprintf(stderr, "Failed to initialize the string list.\n");
        return EXIT_FAILURE;
    }

    int operation = DEFAULT_STATE; // initial state
    int numOfWords = DEFAULT_STATE;
    char* word = NULL;

    while(operation != EXIT) {
        operation = readIntegerInput();

        switch (operation) {

            case INSERT_LAST:  // 1 insert number of words and then the words to insert in the last position
                numOfWords = readIntegerInput();
                while(numOfWords > 0){
                    word = readWordInput();
                    StrList_insertLast(myList ,word);
                    free(word);
                    numOfWords--;
                }
                break;

            case INSERT_AT_INDEX:  // 2 insert word at specific index
                word = readWordInput();
                StrList_insertAt(myList, word, readIntegerInput());
                free(word);
                break;

            case PRINT_LIST_WORDS:  // 3 printing all the words
                StrList_print(myList);
                break;

            case PRINT_NUM_WORDS:  // 4 printing the number of words
                printf("%zu\n", StrList_size(myList));
                break;

            case PRINT_WORD_AT_INDEX:  // 5 printing word in a specific index
                StrList_printAt(myList, readIntegerInput());
                break;

            case NUM_CHARS_AT_LIST:  // 6 printing the number of chars in the list
                printf("%d\n",StrList_printLen(myList));
                break;

            case NUM_SUBSTRING_AT_LIST: // 7
                word = readWordInput();
                printf("%d\n",StrList_count(myList, word));
                free(word);
                break;

            case REMOVE_WORD_IN_LIST: // 8
                word = readWordInput();
                StrList_remove(myList, word);
                free(word);
                break;

            case REMOVE_WORD_AT_INDEX: // 9
                StrList_removeAt(myList, readIntegerInput());
                break;

            case REVERSE_LIST: // 10
                StrList_reverse(myList);
                break;

            case DELETE_LIST:  // 11
                while(StrList_firstData(myList) != NULL)
                    StrList_removeAt(myList, 0);
                break;

            case SORT_LIST_LEX: // 12
                StrList_sort(myList);
                break;

            case CHECK_IF_LEX_SORTED:  // 13
                if(StrList_isSorted(myList)) {
                    printf("true\n");
                } else printf("false\n");
                break;

            case EXIT: // 0
                break;

            default:
                printf("Invalid Case\n");
        }
    }

    StrList_free(myList); // Cleanup
    return EXIT;
}

// Reads an integer from user input, with optional prompt
int readIntegerInput() {
    int value;
    char line[256]; // Buffer to read input line

    if (!fgets(line, sizeof(line), stdin)) {
        fprintf(stderr, "Error reading input.\n");
        return INVALID_CASE_FAILURE; // Indicate failure
    }

    // Check if the input can be converted to an integer
    if (sscanf(line, "%d", &value) != 1) {
        return INVALID_CASE_FAILURE; // Indicate failure on non-integer input
    }

    return value;
}

// Dynamically reads a word from user input
char* readWordInput() {
    char* word = malloc(1); // Start with minimal allocation
    char ch;
    int len = 0, capacity = 1;

    while ((ch = getchar()) && ch != '\n'&& ch != ' ' && ch != EOF) {
        // Expand buffer if needed
        if (len + 1 >= capacity) {
            capacity *= 2;
            char* temp = realloc(word, capacity);
            if (!temp) {
                free(word);
                fprintf(stderr, "Failed to allocate memory for word.\n");
                return NULL;
            }
            word = temp;
        }
        word[len++] = ch;
    }
    word[len] = '\0'; // Null-terminate the word

    return word;
}
