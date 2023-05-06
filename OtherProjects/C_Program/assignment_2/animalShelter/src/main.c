#include <animal.h>

//////////////////////////////////////////////////////////////////////
//<assignment 2 animal shelter>
//
//Course	    : C Programming (PRC)
//Assignment	: Pointers & Unit-Test Functions
//Date		    : 30-04-2022
//Student		: Farros Ramzy(3767353)
//
//
//                Resubmit to fix errors at (02/06/2022)
//////////////////////////////////////////////////////////////////////

int main()
{
    Animal animals[MAX_NUMBER_ANIMAL];
    uint8_t numberOfAnimals = 0;
    int8_t option = -1;

    Animal *animalFound;
    int *popularSpecies;

    while (option != 0)
    {
        /*
         * Menu of the animal shelter
         * Mandatory assignment (option 0 to 6)
         * Optional assignment (option 7)
         */
        printf("\nMENU\n====\n");
        printf("1: Amount of hosted animals\n");
        printf("2: Show animals\n");
        printf("3: Add animal\n");
        printf("4: Search animals by name\n");
        printf("5: Remove animal by id\n");
        printf("6: Find most popular species\n");
        printf("7: Classify animals by name\n");
        printf("0: Quit program\n\n");

        printf("Your choice: ");

        scanf("%hhd", &option);

        switch (option)
        {
        // To do: add the code to be executed in each case
        case 1:
            printf("Amount of hosted animals\n");
            if (!amount_of_hosted_animals(numberOfAnimals))
            {
                printf("\nThere is no animal hosted inside this shelter yet.\n\n");
            }
            break;
        case 2:
            printf("Show animals\n");
            show_animals(animals, numberOfAnimals);
            break;
        case 3:
            printf("Add animal\n");
            Animal newAnimal;

            printf("\nThe new animal's ID: ");
            scanf("%d", &newAnimal.id);
            printf("\n");

            printf("\nThe new animal's name: ");
            scanf("%s", newAnimal.name);
            printf("\n");

            printf("There are %lld species that are allowed to be hosted in this shelter.", sizeof(Species));
            printf("\nType one of the numbers below to select the new animal species!\n");
            printf("\n0 -Cat\n");
            printf("1 -Chinchilla\n");
            printf("2 -Dog\n");
            printf("3 -Turtle\n\n");
            printf("\nThis animal species is: ");
            scanf("%u", &newAnimal.species);
            printf("\n");

            if (add_animal(animals, &numberOfAnimals, newAnimal))
            {
                char newAnimalSpecies[MAX_LENGTH_SPECIES];
                switch (newAnimal.species)
                {
                case 0:
                    strcpy(newAnimalSpecies, "Cat");
                    break;
                case 1:
                    strcpy(newAnimalSpecies, "Chinchilla");
                    break;
                case 2:
                    strcpy(newAnimalSpecies, "Dog");
                    break;
                case 3:
                    strcpy(newAnimalSpecies, "Turtle");
                    break;
                default:
                    break;
                }
                printf("\nA %s named %s has added into the shelter with ID number %d.\n", newAnimalSpecies, newAnimal.name, newAnimal.id);
            }
            else
            {
                printf("\nAn Error Accured while adding the new animal.\nIf the shelter still some spaces, please check the species or the ID number of the new animal again.\n");
            }
            break;
        case 4:
            printf("Search animals by name\n");

            char nameToFind[MAX_LENGTH_NAME];
            uint8_t sizeOfFound = 0;
            printf("\nThe name of the animal: ");
            scanf("%s", nameToFind);
            printf("\n");
            animalFound = (Animal *)calloc(sizeOfFound, sizeof(Animal));
            uint8_t found = search_animal(animals, numberOfAnimals, nameToFind, animalFound);
            if (found > 0)
            {
                if (found > 1)
                {
                    printf("\nThere are %hhu animals which named as %s in this shelter. And they are:\n\n", numberOfAnimals, nameToFind);
                }
                else
                {
                    printf("\nThere is one animal with the name %s in this shelter. And it is:\n\n", nameToFind);
                }

                char animalSpecies[MAX_LENGTH_SPECIES];
                for (uint8_t i = 0; i < found; i++)
                {
                    switch ((*(animalFound + i)).species)
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
                    printf("ID: %d  %s  (%s)\n", (animalFound + i)->id, (animalFound + i)->name, animalSpecies);
                }
                printf("\n");
            }
            else
            {
                printf("\nThere is no animal named %s in this shelter.\n\n", nameToFind);
            }
            free(animalFound);
            break;
        case 5:
            printf("Remove animal by id\n");
            int animalID;
            printf("\nThe ID of the animal: ");
            scanf("%d", &animalID);
            printf("\n");
            release_animal(animals, &numberOfAnimals, animalID);
            break;
        case 6:
            printf("Find most popular species\n");
            if (numberOfAnimals > 0)
            {
                uint8_t sizeOfFound = 0;
                popularSpecies = (int *)calloc(sizeOfFound, sizeof(int));
                uint8_t nrOfPopularSpecies = find_most_popular_species(animals, numberOfAnimals, popularSpecies, &sizeOfFound);
                if (sizeOfFound == sizeof(Species))
                {
                    printf("\nAll species available in this shelter are equals.\n");
                }
                else
                {
                    printf("\nThe most popular species in this shelter:\n");
                    for (uint8_t i = 0; i < sizeOfFound; i++)
                    {
                        switch (*(popularSpecies + i))
                        {
                        case 0:
                            printf("\n- Cat ");
                            break;
                        case 1:
                            printf("\n- Chinchilla ");
                            break;
                        case 2:
                            printf("\n- Dog ");
                            break;
                        case 3:
                            printf("\n- Turtle ");
                            break;
                        default:
                            break;
                        }
                    }
                    printf("\n\nwith total %hhd animals represents in each species.\n", nrOfPopularSpecies);
                }
                free(popularSpecies);
            }
            else
            {
                printf("\nUnfortunately, there is no animal available yet in this shelter.\n");
            }
            break;
        case 7:
            printf("Classify animals by name\n");
            classify_by_names(animals, numberOfAnimals);
            break;
        case 0:
            printf("Quit program\n");
            break;
        default:
            printf("ERROR: option %hhd is not available\n", option);
            break;
        }
    }
    return 0;
}