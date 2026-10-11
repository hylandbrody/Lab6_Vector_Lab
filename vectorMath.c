/*
* File: vectorMath.c
* Description: Vector math and storage functions
* Author: Brody Hyland
* Date: 10/11/2026
*/

#include <stdio.h>
#include <string.h>
#include "vectorMath.h"
#include "myVect.h"

void list(Vect vectors[])
{
    int i;

    for (i = 0; i < MAX_VECTORS; i++)
    {
        if (vectors[i].name[0] != '\0')
        {
            showVect(vectors[i]);
        }
    }
}

void clear(Vect vectors[])
{
    int i;

    for (i = 0; i < MAX_VECTORS; i++)
    {
        vectors[i].name[0] = '\0';
    }
}

int storeVect(Vect vectors[], Vect newVect)
{
    int i;

    /* Replace an existing vector */
    for (i = 0; i < MAX_VECTORS; i++)
    {
        if (strcmp(vectors[i].name, newVect.name) == 0 &&
            vectors[i].name[0] != '\0')
        {
            vectors[i] = newVect;
            return 1;
        }
    }

    /* Find an empty location */
    for (i = 0; i < MAX_VECTORS; i++)
    {
        if (vectors[i].name[0] == '\0')
        {
            vectors[i] = newVect;
            return 1;
        }
    }

    return 0;
}

int findVect(Vect vectors[], char name[], Vect *result)
{
    int i;

    for (i = 0; i < MAX_VECTORS; i++)
    {
        if (strcmp(vectors[i].name, name) == 0 &&
            vectors[i].name[0] != '\0')
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
