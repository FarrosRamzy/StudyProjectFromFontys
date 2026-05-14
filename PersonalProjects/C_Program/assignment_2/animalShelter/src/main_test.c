#include <animal.h>
#include <unity.h>

#define MAX_TEST_ANIMAL 2

void setUp(void)
{
    // To do: optionally add the code to be executed before each unit test
}

void tearDown(void)
{
    // To do: optionally add the code to be executed after each unit test
}

/**
 * @brief 
 * Test if the shelter array has not changed after the show_array function executed.
 */
void test_case_show_animals()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Ucok", 1}, {2, "Osama", 0}};

    Animal expectedArray[MAX_TEST_ANIMAL] = {{1, "Ucok", 1}, {2, "Osama", 0}};

    // Act:
    show_animals(testArray, currentNrOfTestAnimals);

    // Assert:
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, testArray, 1);
}

/**
 * @brief 
 * Test the shelter if it is not empty after one or two animal has added into the shelter.
 */
void test_case_amount_of_hosted_animals()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    // Animal testArray[MAX_TEST_ANIMAL] = {{1, "Ucok", 1}, {2, "Osama", 0}};

    // Act:
    bool shelterIsNotEmpty = amount_of_hosted_animals(currentNrOfTestAnimals);

    // Assert:
    TEST_ASSERT_TRUE(shelterIsNotEmpty);
}

/**
 * @brief 
 * Test if the new animal succesfully added into the shelter.
 */
void test_case_add_animal_is_true()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 1;
    Animal TestArray[MAX_TEST_ANIMAL] = {{1, "Trump", 2}};

    Animal newTestAnimal = {2, "Osama", 0};

    // Act:
    bool testAddAnimal = add_animal(TestArray, &currentNrOfTestAnimals, newTestAnimal);

    // Assert:
    TEST_ASSERT_TRUE(testAddAnimal);
}

/**
 * @brief 
 * Test if the new animal cannot be added into the shelter if the size is already full.
 */
void test_case_add_animal_is_false()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 1;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Trump", 2}, {2, "Osama", 0}};

    Animal newTestAnimal = {1, "Ucok", 1};

    // Act:
    bool testAddAnimal = add_animal(testArray, &currentNrOfTestAnimals, newTestAnimal);

    // Assert:
    TEST_ASSERT_FALSE(testAddAnimal);
}

/**
 * @brief 
 * Test if the shelter array instance trully changed, due to the deleted instance.
 */
void test_case_array_after_release_animal()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Ucok", 1}, {2, "Osama", 0}};
    int testToRemoveID = 1;

    Animal expectedArray[MAX_TEST_ANIMAL] = {{2, "Osama", 0}};

    // Act:
    release_animal(testArray, &currentNrOfTestAnimals, testToRemoveID);

    // Assert:
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, testArray, 1);
}

/**
 * @brief 
 * Test if the shelter array instance trully decreased after one instance has been deleted.
 */
void test_case_number_of_hosted_after_release_animal()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Osama", 0}, {2, "Trump", 2}};
    int testToRemoveID = 2;

    uint8_t expectedCurrentNrOfTestAnimals = 1;

    // Act:
    release_animal(testArray, &currentNrOfTestAnimals, testToRemoveID);

    // Assert:
    TEST_ASSERT_EQUAL_UINT8(expectedCurrentNrOfTestAnimals, currentNrOfTestAnimals);
}

/**
 * @brief 
 * Test if the number of animal that has found in the array is correct and keep updated.
 */
void test_case_number_of_found_in_search_animal()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    uint8_t sizeOfFound = 0;
    Animal *testFoundArray;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Osama", 0}, {2, "Osama", 1}};

    char nameToFind[MAX_LENGTH_NAME] = {"Osama"};

    uint8_t expectToFind = 2;

    // Act:
    testFoundArray = (Animal *)calloc(sizeOfFound, sizeof(Animal));
    uint8_t testToFind = search_animal(testArray, currentNrOfTestAnimals, nameToFind, testFoundArray);

    // Assert:
    TEST_ASSERT_EQUAL_UINT8(expectToFind, testToFind);
    free(testFoundArray);
}

/**
 * @brief 
 * Test if the search animal by name in the shelter array results the correct instance.
 */
void test_case_animal_found_in_search_animal()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    uint8_t sizeOfFound = 0;
    Animal *testFoundArray;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Osama", 0}, {2, "Ucok", 1}};

    char nameToFind[MAX_LENGTH_NAME] = {"Ucok"};

    Animal expectToFindArray[1] = {{2, "Ucok", 1}};

    // Act:
    testFoundArray = (Animal *)calloc(sizeOfFound, sizeof(Animal));
    search_animal(testArray, currentNrOfTestAnimals, nameToFind, testFoundArray);

    // Assert:
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectToFindArray, testFoundArray, 1);
    free(testFoundArray);
}

/**
 * @brief 
 * Test if the number of animals in the popular species is correct.
 */
void test_case_number_of_found_in_find_popular_species()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    uint8_t sizeOfFound = 0;
    int *testFoundPopular;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Osama", 0}, {2, "Ali", 0}};

    uint8_t expectNrOfAnimal = 2;

    // Act:
    testFoundPopular = (int *)calloc(sizeOfFound, sizeof(int));
    uint8_t nrOfPopularAnimal = find_most_popular_species(testArray, currentNrOfTestAnimals, testFoundPopular, &sizeOfFound);

    // Assert:
    TEST_ASSERT_EQUAL_UINT8(expectNrOfAnimal, nrOfPopularAnimal);
    free(testFoundPopular);
}

/**
 * @brief 
 * Test if the popular species in the shelter array is correctly identified.
 */
void test_case_find_popular_species()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    uint8_t sizeOfFound = 0;
    int *testFoundPopular;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Osama", 0}, {2, "Ali", 0}};

    int expectPopularSpecies[1] = {0};

    // Act:
    testFoundPopular = (int *)calloc(sizeOfFound, sizeof(int));
    find_most_popular_species(testArray, currentNrOfTestAnimals, testFoundPopular, &sizeOfFound);

    // Assert:
    TEST_ASSERT_EQUAL_INT_ARRAY(expectPopularSpecies, testFoundPopular, 1);
    free(testFoundPopular);
}

/**
 * @brief 
 * Test if the array order has changed due to the name of the instances.
 */
void test_case_name_order_in_classify_by_names()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    Animal testArray[MAX_TEST_ANIMAL] = {{1, "Osama", 0}, {2, "Ali", 0}};

    Animal expectedArray[MAX_TEST_ANIMAL] = {{2, "Ali", 0}, {1, "Osama", 0}};

    // Act:
    classify_by_names(testArray, currentNrOfTestAnimals);

    // Assert:
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, testArray, 1);
}

/**
 * @brief 
 * Test if the array order has changed due to the ID number if there are multiple
 * instances with the same name.
 */
void test_case_id_order_in_classify_by_names()
{
    // Arrange:
    uint8_t currentNrOfTestAnimals = 2;
    Animal testArray[MAX_TEST_ANIMAL] = {{2, "Ali", 0}, {1, "Ali", 0}};

    Animal expectedArray[MAX_TEST_ANIMAL] = {{1, "Ali", 0}, {2, "Ali", 0}};

    // Act:
    classify_by_names(testArray, currentNrOfTestAnimals);

    // Assert:
    TEST_ASSERT_EQUAL_PTR_ARRAY(expectedArray, testArray, 1);
}

int main(void)
{
    UnityBegin(0);

    // To do : add your unit tests

    RUN_TEST(test_case_show_animals, 1);

    RUN_TEST(test_case_amount_of_hosted_animals, 1);
    
    RUN_TEST(test_case_add_animal_is_true, 1);
    RUN_TEST(test_case_add_animal_is_false, 1);
    
    RUN_TEST(test_case_array_after_release_animal, 1);
    RUN_TEST(test_case_number_of_hosted_after_release_animal, 1);
    
    RUN_TEST(test_case_number_of_found_in_search_animal, 1);
    RUN_TEST(test_case_animal_found_in_search_animal, 1);
    
    RUN_TEST(test_case_number_of_found_in_find_popular_species, 1);
    RUN_TEST(test_case_find_popular_species, 1);
    
    RUN_TEST(test_case_name_order_in_classify_by_names, 1);
    RUN_TEST(test_case_id_order_in_classify_by_names, 1);

    return UnityEnd();
}
