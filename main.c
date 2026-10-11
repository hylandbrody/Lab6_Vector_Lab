/*
* File: main.c
* Description: Interactive vector calculator
* Author: Brody Hyland
* Date: 10/11/2026
*/

#include <stdio.h>
#include <string.h>
#include "vectorMath.h"

#define MAX_VECTORS 10

int main(void)
{
    Vect vectors[MAX_VECTORS] = {0};
    Vect a, b, result;
    char userinputs[100];
    char name[8], name1[8], name2[8];
    char op;
    float x, y, z, scalar;
    int q = 0;

    while (q == 0)
    {
        printf("minimat> ");

        if (fgets(userinputs, sizeof(userinputs), stdin) == NULL)
        {
            q = 1;
        }
        else
        {
            userinputs[strcspn(userinputs, "\n")] = '\0';

            for (int i = 0; userinputs[i] != '\0'; i++)
            {
                if (userinputs[i] == ',')
                {
                    userinputs[i] = ' ';
                }
            }

            if (strcmp(userinputs, "quit") == 0)
            {
                q = 1;
            }
            else if (strcmp(userinputs, "clear") == 0)
            {
                clear(vectors);
                printf("Vectors cleared.\n");
            }
            else if (strcmp(userinputs, "list") == 0)
            {
                list(vectors);
            }
            else if (sscanf(userinputs, "dot %7s %7s",
                            name1, name2) == 2)
            {
                if (findVect(vectors, name1, &a) &&
                    findVect(vectors, name2, &b))
                {
                    printf("ans = %g\n", dot(a, b));
                }
                else
                {
                    printf("Vector not found.\n");
                }
            }
            else if (sscanf(userinputs, "cross %7s %7s",
                            name1, name2) == 2)
            {
                if (findVect(vectors, name1, &a) &&
                    findVect(vectors, name2, &b))
                {
                    result = cross(a, b);
                    strcpy(result.name, "ans");
                    showVect(result);
                }
                else
                {
                    printf("Vector not found.\n");
                }
            }
            /* Assign a vector from three numbers */
            else if (sscanf(userinputs, " %7s = %f %f %f",
                            name, &x, &y, &z) == 4)
            {
                strcpy(result.name, name);
                result.x = x;
                result.y = y;
                result.z = z;

                if (storeVect(vectors, result))
                {
                    showVect(result);
                }
                else
                {
                    printf("Vector memory full.\n");
                }
            }
            
            /* Assign a vector multiplied by a scalar */
            else if (sscanf(userinputs, " %7s = %7s %c %f",
                            name, name1, &op, &scalar) == 4
                     && op == '*')
            {
                if (findVect(vectors, name1, &a))
                {
                    result = mult(a, scalar);
                    strcpy(result.name, name);

                    if (storeVect(vectors, result))
                    {
                        showVect(result);
                    }
                    else
                    {
                        printf("Vector memory full.\n");
                    }
                }
                else
                {
                    printf("Vector %s not found.\n", name1);
                }
            }
            /* Assign a scalar multiplied by a vector */
            else if (sscanf(userinputs, " %7s = %f %c %7s",
                            name, &scalar, &op, name1) == 4
                     && op == '*')
            {
                if (findVect(vectors, name1, &a))
                {
                    result = mult(a, scalar);
                    strcpy(result.name, name);

                    if (storeVect(vectors, result))
                    {
                        showVect(result);
                    }
                    else
                    {
                        printf("Vector memory full.\n");
                    }
                }
                else
                {
                    printf("Vector %s not found.\n", name1);
                }
            }
            /* Assign the result of vector addition or subtraction */
            else if (sscanf(userinputs, " %7s = %7s %c %7s",
                            name, name1, &op, name2) == 4
                     && (op == '+' || op == '-'))
            {
                if (findVect(vectors, name1, &a) &&
                    findVect(vectors, name2, &b))
                {
                    if (op == '+')
                    {
                        result = add(a, b);
                    }
                    else
                    {
                        result = sub(a, b);
                    }

                    strcpy(result.name, name);

                    if (storeVect(vectors, result))
                    {
                        showVect(result);
                    }
                    else
                    {
                        printf("Vector memory full.\n");
                    }
                }
                else
                {
                    printf("Vector not found.\n");
                }
            }
            /* Display a vector or calculate an operation */
            else if (sscanf(userinputs, " %7s %c %7s",
                            name1, &op, name2) == 3
                     && (op == '+' || op == '-'))
            {
                if (findVect(vectors, name1, &a) &&
                    findVect(vectors, name2, &b))
                {
                    if (op == '+')
                    {
                        result = add(a, b);
                    }
                    else
                    {
                        result = sub(a, b);
                    }

                    strcpy(result.name, "ans");
                    showVect(result);
                }
                else
                {
                    printf("Vector not found.\n");
                }
            }
            else if (sscanf(userinputs, " %7s %c %f",
                            name1, &op, &scalar) == 3
                     && op == '*')
            {
                if (findVect(vectors, name1, &a))
                {
                    result = mult(a, scalar);
                    strcpy(result.name, "ans");
                    showVect(result);
                }
                else
                {
                    printf("Vector %s not found.\n", name1);
                }
            }
            else if (sscanf(userinputs, " %7s", name) == 1)
            {
                if (findVect(vectors, name, &result))
                {
                    showVect(result);
                }
                else
                {
                    printf("Vector %s not found.\n", name);
                }
            }
            else if (userinputs[0] != '\0')
            {
                printf("Invalid command.\n");
            }
        }
    }

    return 0;
}