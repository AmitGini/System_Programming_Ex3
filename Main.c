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
#define EXIT 0



void modify_StrList(StrList *list, int caseFlag);

int User_InputNumbers();

int main(){

    StrList* ptrStrList = StrList_alloc();

    if(ptrStrList == NULL){
        free(ptrStrList);
        return -1;
    }

    int inputCase = -1; // default - init

    while(inputCase != 0) {
        inputCase = User_InputNumbers();

        switch (inputCase) {

            case INSERT_LAST:  // 1 insert number of words and then the words to insert in the last position
                modify_StrList(ptrStrList, INSERT_LAST);
                break;

            case INSERT_AT_INDEX:  // 2 insert word at specific index
                modify_StrList(ptrStrList, INSERT_AT_INDEX);
                break;

            case PRINT_LIST_WORDS:  // 3 printing all the words
                StrList_print(ptrStrList);
                break;

            case PRINT_NUM_WORDS:  // 4 printing the number of words
                printf("%zu\n", StrList_size(ptrStrList));
                break;

            case PRINT_WORD_AT_INDEX:  // 5 printing word in a specific index
                StrList_printAt(ptrStrList,User_InputNumbers());
                break;

            case NUM_CHARS_AT_LIST:  // 6 printing the number of chars in the list
                printf("%d\n",StrList_printLen(ptrStrList));
                break;

            case NUM_SUBSTRING_AT_LIST: // 7
                modify_StrList(ptrStrList, NUM_SUBSTRING_AT_LIST);
                break;

            case REMOVE_WORD_IN_LIST: // 8
                modify_StrList(ptrStrList, REMOVE_WORD_IN_LIST);
                break;

            case REMOVE_WORD_AT_INDEX: // 9
                StrList_removeAt(ptrStrList, User_InputNumbers());
                break;

            case REVERSE_LIST: // 10
                StrList_reverse(ptrStrList);
                break;

            case DELETE_LIST:  // 11
                while(StrList_firstData(ptrStrList) != NULL)
                    StrList_removeAt(ptrStrList,0);
                break;

            case SORT_LIST_LEX: // 12
                StrList_sort(ptrStrList);
                break;

            case CHECK_IF_LEX_SORTED:  // 13
                if(StrList_isSorted(ptrStrList)) {
                    printf("true\n");
                } else printf("false\n");
                break;

            case EXIT: // 0
                break;

            default:
                printf("%d Invalid Case\n", inputCase);
        }
    }

    StrList_free(ptrStrList);
    free(ptrStrList);
    return 0;
}

void modify_StrList(StrList *list, int caseFlag) {
    int maxNumOfIteration = 0; //num of words user going to insert or remove
    int currentIteration = 0; //num of words that were inserted at specific iteration
    char *word; //word to insert
    int flagNewWord = 1; //start a new word flag is 1, else 0
    size_t len = 0;  //len of the word at specific iteration
    size_t capacity = 1; //memory capacity at specific iteration
    char ch;  //char input from user at each iteration
    int userInputIndex = -1; //default in case won't be used, part of cases needs another input of index from the user.

    // Cases: INSERT LAST - number of words INSERT AT INDEX - index in the list
    if(caseFlag == INSERT_LAST){
        maxNumOfIteration = User_InputNumbers(); // user input is the number of words
        if(maxNumOfIteration == -1) return;
    }else if(caseFlag == INSERT_AT_INDEX || caseFlag == REMOVE_WORD_AT_INDEX){
        userInputIndex = User_InputNumbers();
        maxNumOfIteration = 1;  // num of words to insert is one, and user input is the index to insert the word
        if(userInputIndex == -1) return;
    }else if(caseFlag == REMOVE_WORD_IN_LIST || caseFlag == NUM_SUBSTRING_AT_LIST){
        maxNumOfIteration = 1;
    }

    while ((ch = getchar()) != EOF) {

        // Ensure there's enough capacity in the buffer for the new character and a null terminator
        if(currentIteration != maxNumOfIteration) {

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

            if (ch != ' ' && ch != '\n') word[len++] = ch; // Add the character to the word in case it's not a space or new line

            if (word && (ch == ' ' || ch == '\n') && len > 0) { // Ensure we have a word to add
                word[len] = '\0'; // Null-terminate the word
                if(caseFlag == INSERT_LAST) StrList_insertLast(list, word);
                if(caseFlag == INSERT_AT_INDEX) StrList_insertAt(list, word, userInputIndex);
                if(caseFlag == REMOVE_WORD_AT_INDEX) StrList_removeAt(list, userInputIndex);
                if(caseFlag == REMOVE_WORD_IN_LIST) StrList_remove(list, word);
                if(caseFlag == NUM_SUBSTRING_AT_LIST) printf("%d\n",StrList_count(list, word));
                currentIteration++;
                len = 0;
                capacity = 1;
                free(word); // Free the buffer for the current word
                flagNewWord = 1;
            }
        }

        if(ch == '\n') break;
    }
}

int User_InputNumbers(){
    int userInput;
    int ch;
    int flagDontInsert = 1;
    // Receive input from the user, for the proper case
    if((userInput = (getchar() - '0')) > 9) {
        flagDontInsert = 0; // initial in case its just 1 number
        userInput = -1;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if(ch > '9') {
            userInput = -1;
            flagDontInsert = 0;
        }
        /// e.x input 234, iteration 1: 2*10+3=23 iteration 2: 23*10+4=234
        /// (ch - '0') calculate the value of the integer in the ascii table
        if(ch == ' ') flagDontInsert = 0; // break and cleaning the buffer at the main while that also handle the user words input
        if(flagDontInsert) userInput = (userInput * 10) + (ch - '0');
    }
   return userInput;
}