#include <stdio.h>
#include <string.h>
#include "fileIO.h"
#include "vectorMath.h"

int saveVectFile(char *filename, Vect *vectors, int count)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Unable to open file for saving.\n");
        return 0;
    }

    for (int i = 0; i < count; i++)
    {
        if (fprintf(file, "%s,%g,%g,%g\n",
                    vectors[i].name,
                    vectors[i].x,
                    vectors[i].y,
                    vectors[i].z) < 0)
        {
            fclose(file);
            printf("Error writing to file.\n");
            return 0;
        }
    }

    if (fclose(file) != 0)
    {
        printf("Error closing file.\n");
        return 0;
    }

    printf("Vectors saved successfully.\n");
    return 1;
}

int loadVectFile(char *filename, Vect **vectors,
                 int *count, int *capacity)
{
    FILE *file = fopen(filename, "r");
    char line[256];
    char name[8];
    char extra;
    float x, y, z;
    Vect result;
    int line_number = 0;
    int loaded = 0;

    if (file == NULL)
    {
        printf("Unable to open file for loading.\n");
        return 0;
    }

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line_number++;

        /* Skip blank lines */
        if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
            continue;

        /* Read one CSV row and reject extra fields */
        if (sscanf(line, " %7[^,],%f,%f,%f %c",
                   name, &x, &y, &z, &extra) != 4)
        {
            printf("Skipping invalid CSV row %d.\n", line_number);
            continue;
        }

        strcpy(result.name, name);
        result.x = x;
        result.y = y;
        result.z = z;

        if (!storeVect(vectors, count, capacity, result))
        {
            printf("Unable to allocate memory for vector.\n");
            fclose(file);
            return 0;
        }

        loaded++;
    }

    if (ferror(file))
    {
        printf("Error reading file.\n");
        fclose(file);
        return 0;
    }

    fclose(file);

    printf("Loaded %d vector(s).\n", loaded);
    return 1;
}