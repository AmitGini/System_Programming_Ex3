#include <stdio.h>
#include "StrList.h"


int main(){

    StrList* ptrStrList = StrList_alloc();

    if(ptrStrList == NULL){
        StrList_free(ptrStrList);
        return -1;
    }

    int input = -1; // default
    while(input != 0) {
        scanf("%d",&input);

        char *string1 = {"Hello"};
        char *string2 = {"is"};
        char *string3 = {"it"};
        char *string4 = {"working?"};
        char *string5 = {"TestCase2?"};

        switch (input) {

            case 1:
                //todo: Implementation - for now Just tests
                printf("Enter number of words: 4\n");
                printf("Hello is it working?\n");

                StrList_insertLast(ptrStrList, string1);
                StrList_insertLast(ptrStrList, string2);
                StrList_insertLast(ptrStrList, string3);
                StrList_insertLast(ptrStrList, string4);

                break;

            case 2:
                //todo: In case double is being send, it covert to int and still work, check required limitations.
                StrList_insertAt(ptrStrList, string5,1);
                break;

            case 3:
                StrList_print(ptrStrList);
                break;

            case 4:
                printf("%zu\n", StrList_size(ptrStrList));
                break;

            case 5:
                StrList_printAt(ptrStrList,4);
                break;
            case 6:
                break;

            case 7:
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
                printf("%d Invalid Case, try again 0 - 13", input);
        }
    }

    StrList_free(ptrStrList);
    return 0;
}