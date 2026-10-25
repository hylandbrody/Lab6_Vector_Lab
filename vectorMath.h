
#include "myVect.h"

int storeVect(Vect **vectors, int *count, int *capacity, Vect v);
int findVect(Vect *vectors, int count, char *name, Vect *result);
void list(Vect *vectors, int count);
void clear(Vect **vectors, int *count, int *capacity);
void showVect(Vect a);

Vect add(Vect a, Vect b);
Vect sub(Vect a, Vect b);
Vect mult(Vect a, float b);
float dot(Vect a, Vect b);
Vect cross(Vect a, Vect b);