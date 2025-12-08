#include "BankQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

int main(void)
{
    BankQueue q;
    if (init(&q, 20))
    {
        char str[20];
        while (1)
        {
            if (fgets(str, sizeof(str), stdin) == NULL)
            {
                break;
            }
            size_t len = strlen(str);
            if (len > 0 && str[len - 1] == '\n')
            {
                str[len - 1] = '\0';
            }
            if (strcmp(str, "#") == 0)
            {
                break;
            }
            else if (strcmp(str, "Calling") == 0)
            {
                deQueue(&q);
            }
            else
            {
                char *start = strchr(str, '<');
                char *end = strchr(str, '>');
                if (start && end && end > start)
                {
                    char number[20];
                    size_t num_len = (size_t)(end - start - 1);
                    if (num_len < sizeof(number))
                    {
                        strncpy(number, start + 1, num_len);
                        number[num_len] = '\0';
                        int value = atoi(number);
                        enQueue(&q, value);
                    }
                }
            }
        }
    }
    destroy(&q);
    return 0;
}