#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int main()
{
    while (1)
    {
        List * list = list_new();
        char symbol;
        printf("Enter string: ");
        do
        {
            symbol = getchar();
            if (symbol == EOF)
            {
                list_delete(list);
                printf("Closed\n");
                exit(EXIT_SUCCESS);
            }
            if (symbol != '\n')
            {
                list_push_back(list, symbol);
            }
        } while (symbol != '\n');
        noExtraSpaces(list);
        decToHex(list);
        if (list->head->next != NULL)
        {
            delHead(list);
        }
        printf("Result: ");
        list_print(list);
        printf("\n");
        list_delete(list);
    }
}
