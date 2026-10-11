
#include "myVect.h"

void list(Vect vectors[]);
void clear(Vect vectors[]);
int storeVect(Vect vectors[], Vect newVect);
int findVect(Vect vectors[], char name[], Vect *result);
void showVect(Vect a);

Vect add(Vect a, Vect b);
Vect sub(Vect a, Vect b);
Vect mult(Vect a, float b);
float dot(Vect a, Vect b);
Vect cross(Vect a, Vect b);