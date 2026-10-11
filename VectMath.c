/*
* File: VectMath.c
* Description: Functions for main of lab5
* Author: Brody Hyland
* Date: 10/6/2016
*/
vect add(vect a, vect b)
{
    vect new;
    new.x = a.x + b.x;
    new.y = a.y + b.y;
    new.z = a.z + b.z;

    return new;
}

vect sub(vect a, vect b)
{
    vect new;
    new.x = a.x - b.x;
    new.y = a.y - b.y;
    new.z = a.z - b.z;

    return new;
}

vect mult(vect a, float b)
{
    vect new;
    new.x = a.x * b;
    new.y = a.y * b;
    new.z = a.z * b;
}



