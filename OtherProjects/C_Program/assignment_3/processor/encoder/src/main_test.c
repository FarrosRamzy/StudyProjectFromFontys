#include <unity.h>
#include <file_encoder.h>

/**
 * @brief Set the Up object
 * 
 */
void setUp()
{
    ;
}

/**
 * @brief Clean up the process after the project finished.
 * 
 */
void tearDown()
{
    ;
}

/**
 * @brief test the viability of encodeByte function to encode the high nibble.
 * 
 */
void test_case_encode_high_nibble()
{
    //Arrange:
    uint8_t inputByte = 87;

    uint8_t encodedHighNibble = 0;
    uint8_t encodedLowNibble = 0;

    uint8_t expectedEncodedHighNibble = 46;
    
    //Act:
    encodeByte(inputByte, &encodedHighNibble, &encodedLowNibble);
    
    //Assert:
    TEST_ASSERT_EQUAL_UINT8(encodedHighNibble, expectedEncodedHighNibble);
}

/**
 * @brief test the viability of encodeByte function to encode the low nibble.
 * 
 */
void test_case_encode_low_nibble()
{
    //Arrange:
    uint8_t inputByte = 87;

    uint8_t encodedHighNibble = 0;
    uint8_t encodedLowNibble = 0;

    uint8_t expectedEncodedLowNibble = 57;
    
    //Act:
    encodeByte(inputByte, &encodedHighNibble, &encodedLowNibble);
    
    //Assert:
    TEST_ASSERT_EQUAL_UINT8(encodedLowNibble, expectedEncodedLowNibble);
}

/**
 * @brief test the viability of addNibbleParity function to create and add parity values
 * from and also to the input byte.
 * 
 */
void test_case_add_nibble_parity_1()
{
    //Arrange:
    uint8_t inputNibble = 5;

    uint8_t nibbleParity = 0;
    uint8_t expectedNibbleParity = 46;

    //Act:
    nibbleParity = addNibbleParity(inputNibble);

    //Assert:
    TEST_ASSERT_EQUAL_UINT8(nibbleParity, expectedNibbleParity);
}

/**
 * @brief test the viability of addNibbleParity function to create and add parity values
 * from and also to the input byte.
 * 
 */
void test_case_add_nibble_parity_2()
{
    //Arrange:
    uint8_t inputNibble = 7;

    uint8_t nibbleParity = 0;
    uint8_t expectedNibbleParity = 57;

    //Act:
    nibbleParity = addNibbleParity(inputNibble);

    //Assert:
    TEST_ASSERT_EQUAL_UINT8(nibbleParity, expectedNibbleParity);
}

int main(void)
{
    UnityBegin(0);

    RUN_TEST(test_case_encode_high_nibble,1);
    RUN_TEST(test_case_encode_low_nibble,1);
    RUN_TEST(test_case_add_nibble_parity_1,1);
    RUN_TEST(test_case_add_nibble_parity_2,1);
    
    return UnityEnd();
}