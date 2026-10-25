/*
* File: main.c
* Description: Interactive vector calculator
* Author: Brody Hyland
* Date: 10/11/2026
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vectorMath.h"
#include "myVect.h"
#include "fileIO.h"

int main(void)
{
    char filename[100];
    Vect *vectors = NULL;
    int vector_count = 0;
    int vector_capacity = 0;

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
            if(strcmp(userinputs, "help") == 0)
            {
                printf("quit - to exit \n");
                printf("clear - to clear vectors \n");
                printf("list - to list vectors \n");
                printf("dot vector1 vector2 - to get dot product of 2 vectors \n");
                printf("cross vector1 vector2 - to get cross product of 2 vectors \n");
                printf("vector1 = vector2 + vector3 - to set vector1 equal to vector2 + vector3 \n");
                printf("vector1 = vector2 - vector3 - to set vector1 equal to vector2 - vector3 \n");
                printf("vector1 = vector2 * constant - to set vector1 equal to vector2 * constant \n");
                printf("vector = constant constant constant - to create a vector \n");
                printf("vector1 + vector2 - to show the product of vector1 + vector2 \n");
                printf("vector1 - vector2 - to show the product of vector1 - vector2 \n");
                printf("vector * constant - to show the product of vector + constant \n");
            }

            else if (strcmp(userinputs, "quit") == 0)
            {
                q = 1;
            }
            else if (sscanf(userinputs, "load %99s", filename) == 1)
            {
                loadVectFile(filename, &vectors,
                            &vector_count, &vector_capacity);
            }
            else if (sscanf(userinputs, "save %99s", filename) == 1)
            {
                saveVectFile(filename, vectors, vector_count);
            }
            else if (strcmp(userinputs, "clear") == 0)
            {
                clear(&vectors, &vector_count, &vector_capacity);
                printf("Vectors cleared.\n");
            }
            else if (strcmp(userinputs, "list") == 0)
            {
                list(vectors, vector_count);
            }
            else if (sscanf(userinputs, "dot %7s %7s",
                            name1, name2) == 2)
            {
                if (findVect(vectors, vector_count, name1, &a) &&
                    findVect(vectors, vector_count, name2, &b))
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
                if (findVect(vectors, vector_count, name1, &a) &&
                    findVect(vectors, vector_count, name2, &b))
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

                if (storeVect(&vectors, &vector_count, &vector_capacity, result))
                {
                    showVect(result);
                }
                else
                {
                    printf("Unable to store vector.\n");
                }
            }
            /* Assign a vector multiplied by a scalar */
            else if (sscanf(userinputs, " %7s = %7s %c %f",
                            name, name1, &op, &scalar) == 4
                     && op == '*')
            {
                if (findVect(vectors, vector_count, name1, &a))
                {
                    result = mult(a, scalar);
                    strcpy(result.name, name);

                    if (storeVect(&vectors, &vector_count, &vector_capacity, result))
                    {
                        showVect(result);
                    }
                    else
                    {
                        printf("Unable to store vector.\n");
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
                if (findVect(vectors, vector_count, name1, &a))
                {
                    result = mult(a, scalar);
                    strcpy(result.name, name);

                    if (storeVect(&vectors, &vector_count, &vector_capacity, result))
                    {
                        showVect(result);
                    }
                    else
                    {
                        printf("Unable to store vector.\n");
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
                if (findVect(vectors, vector_count, name1, &a) &&
                    findVect(vectors, vector_count, name2, &b))
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

                    if (storeVect(&vectors, &vector_count, &vector_capacity, result))
                    {
                        showVect(result);
                    }
                    else
                    {
                    printf("Unable to store vector.\n");
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
                if (findVect(vectors, vector_count, name1, &a) &&
                    findVect(vectors, vector_count, name2, &b))
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
            else if (sscanf(userinputs, " %7s %c %f",       /*FiX*/
                            name1, &op, &scalar) == 3
                     && op == '*')
            {
                if (findVect(vectors, vector_count, name1, &a))
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
            else if (sscanf(userinputs, " %f %c %7s",       /*FiX*/
                            &scalar, &op, name1) == 3
                     && op == '*')
            {
                if (findVect(vectors, vector_count, name1, &a))
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
                if (findVect(vectors, vector_count, name, &result))
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

    clear(&vectors, &vector_count, &vector_capacity);
    return 0;
}