/*
* File: vectorMath.c
* Description: Vector math and storage functions
* Author: Brody Hyland
* Date: 10/11/2026
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vectorMath.h"
#include "myVect.h"

void list(Vect *vectors, int count)
{
    int i;

    for (i = 0; i < count; i++)
    {
        showVect(vectors[i]);
    }
}

void clear(Vect **vectors, int *count, int *capacity)
{
    free(*vectors);
    *vectors = NULL;
    *count = 0;
    *capacity = 0;
}

int storeVect(Vect **vectors, int *count, int *capacity, Vect v)
{
     int i;
    Vect *temp;

    /* Replace an existing vector */
    for (i = 0; i < *count; i++)
    {
        if (strcmp((*vectors)[i].name, v.name) == 0)
        {
            (*vectors)[i] = v;
            return 1;
        }
    }

    /* Expand the array if it is full */
    if (*count == *capacity)
    {
        int new_capacity;

        if (*capacity == 0)
        {
            new_capacity = 4;
        }
        else
        {
            new_capacity = *capacity * 2;
        }

        temp = realloc(*vectors,
                       new_capacity * sizeof(Vect));

        if (temp == NULL)
        {
            return 0;
        }

        *vectors = temp;
        *capacity = new_capacity;
    }

    /* Add the new vector */
    (*vectors)[*count] = v;
    (*count)++;

    return 1;
}

int findVect(Vect *vectors, int count, char *name, Vect *result)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (strcmp(vectors[i].name, name) == 0)
        {
            *result = vectors[i];
            return 1;
        }
    }

    return 0;
}


void showVect(Vect a)
{
     printf("%s = %.2f %.2f %.2f\n",
           a.name, a.x, a.y, a.z);
}

Vect add(Vect a, Vect b)
{
    Vect new;
    new.x = a.x + b.x;
    new.y = a.y + b.y;
    new.z = a.z + b.z;

    return new;
}

Vect sub(Vect a, Vect b)
{
    Vect new;
    new.x = a.x - b.x;
    new.y = a.y - b.y;
    new.z = a.z - b.z;

    return new;
}

Vect mult(Vect a, float b)
{
    Vect new;
    new.x = a.x * b;
    new.y = a.y * b;
    new.z = a.z * b;

    return new;
}

float dot(Vect a, Vect b)
{
    return a.x * b.x +
           a.y * b.y +
           a.z * b.z;
}

Vect cross(Vect a, Vect b)
{
    Vect result = {"ans", 0, 0, 0};

    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;

    return result;
}
