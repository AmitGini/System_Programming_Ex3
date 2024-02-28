#include <stdio.h>
#include "StrList.h"


int main(){

    StrList* ptrStrList = StrList_alloc();

    if(ptrStrList == NULL){
        StrList_free(ptrStrList);
        return -1;
    }

    int inputCase = -1; // default
    while(inputCase != 0) {
        scanf("%d",&inputCase);

        char *string1 = {"Hello"};
        char *string2 = {"is"};
        char *string3 = {"it"};
        char *string4 = {"working?"};
        char *string5 = {"Test-wrwrwwrw?"};

        switch (inputCase) {

            case 1:  // insert number of words and then the words to insert in the last position
                //todo: Implementation - for now Just tests
                printf("Enter number of words: 4\n");

                StrList_insertLast(ptrStrList, string1);
                StrList_insertLast(ptrStrList, string2);
                StrList_insertLast(ptrStrList, string3);
                StrList_insertLast(ptrStrList, string4);

                break;

            case 2:  // insert word at specific index
                //todo: In case double is being send, it covert to int and still work, check required limitations.
                StrList_insertAt(ptrStrList, string5,1);
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
                printf("%d\n", StrList_count(ptrStrList,"wrw"));
                break;

            case 8:
                break;

            case 9:
                break;

            case 10:
                break;

            case 11:
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
    return 0;
}