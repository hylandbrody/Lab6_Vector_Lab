#ifndef FILEIO_H
#define FILEIO_H

#include "myVect.h"

int saveVectFile(char *filename, Vect *vectors, int count);

int loadVectFile(char *filename, Vect **vectors,
                 int *count, int *capacity);

#endif