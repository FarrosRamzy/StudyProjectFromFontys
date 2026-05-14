#include <animal.h>
// To do : define your functions

/**
 * @brief 
 * Print out the amount of instances from the shelter array.
 * 
 * Note:
 * Return true if the shelter is not empty.
 * Return false if the shelter is empty.
 * 
 * @param numberOfAnimals amount of instances from the shelter array.
 * @return true 
 * @return false 
 */
bool amount_of_hosted_animals(uint8_t numberOfAnimals)
{
    if (numberOfAnimals > 0)
    {
        if (numberOfAnimals > 1)
        {
            printf("\nThere are %hhu animals inside this shelter.\n\n", numberOfAnimals);
        }
        else
        {
            printf("\nThere is an animal hosted this shelter.\n\n");
        }
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief 
 * Adding a new animal into the shelter by checking the shelter size, the availability of the 
 * new animal's name, the unique ID of the new animal, and the species of the new animal.
 * 
 * Return true if the new animal has succesfully added into the shelter array.
 * Return false if the new animal has failed to be added into the shelter array.
 * 
 * @param animals The array of hosted animals in the shelter.
 * @param numberOfAnimals The number of animals inside the shelter.
 * @param newAnimal The new animal object that to be added into the array.
 * @return true
 * @return false
 */
bool add_animal(Animal *animals, uint8_t *numberOfAnimals, Animal newAnimal)
{
    uint8_t animalWithSameId = 0;
    bool allowedToAdd = false;
    
    if (*numberOfAnimals < MAX_NUMBER_ANIMAL)
    {
        if ((strlen(newAnimal.name) <= MAX_LENGTH_NAME) && (strlen(newAnimal.name) > 0))
        {
            if (*numberOfAnimals > 0)
            {
                for (uint8_t i = 0; i < *numberOfAnimals; i++)
                {
                    if ((animals + i)->id == newAnimal.id)
                    {
                        animalWithSameId++;
                    }
                }

                if (animalWithSameId > 0)
                {
                    allowedToAdd = false;
                }
                else
                {
                    *(animals + *numberOfAnimals) = newAnimal;
                    *numberOfAnimals = *numberOfAnimals + 1;
                    allowedToAdd = true;
                }
            }
            else
            {
                *(animals + *numberOfAnimals) = newAnimal;
                *numberOfAnimals = *numberOfAnimals + 1;
                allowedToAdd = true;
            }
        }
        else
        {
            allowedToAdd = false;
        }
    }
    else
    {
        allowedToAdd = false;
    }

    return allowedToAdd;
}

/**
 * @brief 
 * A function to remove an animal by using their ID number.
 * 
 * @param animals the shelter array.
 * @param numberOfAnimals the amount of instances within the shelter array.
 * @param id the ID number of an instance that will be removed.
 */
void release_animal(Animal *animals, uint8_t *numberOfAnimals, int id)
{
    bool founded = false;
    bool delete = false;
    if (*numberOfAnimals > 0)
    {
        for (uint8_t i = 0; (i < *numberOfAnimals) && (founded == false); i++)
        {
            if ((animals + i)->id == id)
            {
                founded = true;
            }
        }

        if (!founded)
        {
            printf("\nSorry, but animal with ID: %d is not registered in this shelter.\n", id);
        }
        else
        {
            for (uint8_t i = 0; (i < *numberOfAnimals) && (delete == false); i++)
            {
                if ((animals + i)->id == id)
                {
                    for (uint8_t j = i; j < *numberOfAnimals - 1; j++)
                    {
                        *(animals + j) = *(animals + (j + 1));
                    }
                    *numberOfAnimals = *numberOfAnimals - 1;
                    delete = true;
                }
            }
            printf("\nThe animal with the ID number %d has released into the wild.\n", id);
        }
    }
    else
    {
        printf("\nUnfortunately, this command cannot be executed since the shelter is still empty.\n");
    }
}

/**
 * @brief 
 * A function to search animals by using their name.
 * 
 * @param animals the shelter array.
 * @param numberOfAnimals the amount of instances within the shelter array.
 * @param name the input name to search the corresponding instance from the shelter array.
 * @param animalFound the array data to return the related instance that has been found.
 * @return uint8_t The number of instances that has been found through the shelter array.
 */
uint8_t search_animal(Animal *animals, uint8_t numberOfAnimals, char name[], Animal *animalFound)
{
    uint8_t found = 0;
    for (uint8_t i = 0; i < numberOfAnimals; i++)
    {
        if (strcmp((animals + i)->name, name) == 0)
        {
            found++;
            animalFound = realloc(animalFound, found * sizeof(Animal));
            *(animalFound + (found - 1)) = *(animals + i);
        }
    }
    return found;
}

/**
 * @brief 
 * A function to print out the detail data of the shelter array's instances.
 * @param animals The shelter array.
 * @param numberOfAnimals The amount of the shelter array's instances.
 */
void show_animals(Animal *animals, uint8_t numberOfAnimals)
{
    if (numberOfAnimals > 0)
    {
        char animalSpecies[MAX_LENGTH_SPECIES];
        printf("\nRegistered animals in this shelter are:\n\n");
        for (uint8_t i = 0; i < numberOfAnimals; i++)
        {
            switch ((*(animals + i)).species)
            {
            case 0:
                strcpy(animalSpecies, "Cat");
                break;
            case 1:
                strcpy(animalSpecies, "Chinchilla");
                break;
            case 2:
                strcpy(animalSpecies, "Dog");
                break;
            case 3:
                strcpy(animalSpecies, "Turtle");
                break;
            default:
                break;
            }
            printf("ID: %d  %s  (%s)\n", (animals + i)->id, (animals + i)->name, animalSpecies);
        }
        printf("\n");
    }
    else
    {
        printf("\nunfortunately, the animal shelter is still empty.\n\n");
    }
}

/**
 * @brief 
 * find most popular species in the shelter by putting all available species into an array,
 * looking for the highest number of the species, then finding the other species that might
 * have the same number of animals in this shelter.
 *
 * Note: if all species have the same number of animals, then there is no popular species.
 * 
 * @param animals The shelter array.
 * @param numberOfAnimals The amount of instances inside the shelter array.
 * @param popularSpecies The array of species with the most number of instances. 
 * @param sizeOfFound The size of the popularSpecies array.
 * @return uint8_t The amount of instances inside each popularSpecies array.
 */
uint8_t find_most_popular_species(Animal *animals, uint8_t numberOfAnimals, int *popularSpecies, uint8_t *sizeOfFound)
{
    uint8_t nrOfPopularSpecies = 0;
    int animalsPerSpecies[sizeof(Species)] = {0};
    for (uint8_t i = 0; i < numberOfAnimals; i++)
    {
        animalsPerSpecies[(animals + i)->species]++;
    }

    for (uint8_t i = 0; i < sizeof(Species); i++)
    {
        if (nrOfPopularSpecies < animalsPerSpecies[i])
        {
            nrOfPopularSpecies = animalsPerSpecies[i];
        }
    }

    for (uint8_t i = 0; i < sizeof(Species); i++)
    {
        if (animalsPerSpecies[i] == nrOfPopularSpecies)
        {
            *sizeOfFound = *sizeOfFound + 1;
            popularSpecies = realloc(popularSpecies, *sizeOfFound * sizeof(uint8_t));
            *(popularSpecies + (*sizeOfFound - 1)) = i;
        }
    }
    return nrOfPopularSpecies;
}

/**
 * @brief 
 * Re-arrange the shelter array instances due to the order of the instances' names,
 * or ID if multiple similar name has detected.
 * 
 * @param animals The shelter array.
 * @param numberOfAnimals The amount of instances inside the shelter array.
 */
void classify_by_names(Animal *animals, uint8_t numberOfAnimals)
{
    if (numberOfAnimals > 0)
    {
        Animal temporary;
        for (uint8_t i = 0; i < numberOfAnimals; i++)
        {
            for (size_t j = i + 1; j < numberOfAnimals; j++)
            {
                if ((strcmp((animals + i)->name, (animals + j)->name) > 0) || (((animals + i)->id) > ((animals + j)->id)))
                {
                    temporary = *(animals + i);
                    *(animals + i) = *(animals + j);
                    *(animals + j) = temporary;
                }
            }
        }
        printf("\nAll animals' data in this shelter have been sorted to their name.\n");
    }
    else
    {
        printf("\nThere is no data can be sorted since the shelter is still empty.\n");
    }
}
