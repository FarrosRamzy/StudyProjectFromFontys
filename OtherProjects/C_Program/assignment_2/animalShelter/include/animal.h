#ifndef _ANIMAL_H
#define _ANIMAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH_NAME 30
#define MAX_NUMBER_ANIMAL 25
#define MAX_LENGTH_SPECIES 15

typedef enum
{
    Cat,
    Chinchilla,
    Dog,
    Turtle,
} Species;

typedef struct
{
    int id;
    char name[MAX_LENGTH_NAME];
    Species species;
} Animal;

// To do : declare your functions

bool add_animal(Animal *, uint8_t *, Animal);
bool amount_of_hosted_animals(uint8_t);
void show_animals(Animal *, uint8_t);
uint8_t search_animal(Animal *, uint8_t, char[], Animal *);
void release_animal(Animal *, uint8_t *, int);
uint8_t find_most_popular_species(Animal *, uint8_t, int *, uint8_t *);

// Extra:

void classify_by_names(Animal *, uint8_t);

#endif