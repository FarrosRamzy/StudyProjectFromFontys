#include <unity.h>
#include <testing_program.h>

#define MAX_CHAR 15

void setUp()
{
    ;
}

void tearDown()
{
    ;
}

void test_case_read_data_error()
{
    //Arrange:
    float CO = 8.01;
    float CO2 = 120;
    float TVOC = 0;

    uint16_t dataReceived = 0;

    char gasStatus[MAX_CHAR];
    
    //Act:
    processGasSensors(CO,CO2,TVOC,dataReceived,gasStatus);
    
    //Assert:
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Error",gasStatus,6);
}

void test_case_read_data_danger()
{
    //Arrange:
    float CO = 201;
    float CO2 = 450;
    float TVOC = 10;

    uint16_t dataReceived = 1;

    char gasStatus[MAX_CHAR];
    
    //Act:
    processGasSensors(CO,CO2,TVOC,dataReceived,gasStatus);
    
    //Assert:
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Danger",gasStatus,7);
}

void test_case_read_data_normal()
{
    //Arrange:
    float CO = 8.01;
    float CO2 = 400;
    float TVOC = 240;

    uint16_t dataReceived = 1;

    char gasStatus[MAX_CHAR];
    
    //Act:
    processGasSensors(CO,CO2,TVOC,dataReceived,gasStatus);
    
    //Assert:
    TEST_ASSERT_EQUAL_CHAR_ARRAY("Normal",gasStatus,7);
}

int main(void)
{
    UnityBegin(0);

    RUN_TEST(test_case_read_data_error,1);
    RUN_TEST(test_case_read_data_danger,1);
    RUN_TEST(test_case_read_data_normal,1);
    
    return UnityEnd();
}