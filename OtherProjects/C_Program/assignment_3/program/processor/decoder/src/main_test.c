#include <unity.h>
#include <file_decoder.h>

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
 * @brief test the viability of the decodeByte function by looking
 * at the output character.
 * 
 */
void test_case_decode_byte_1()
{
    //Arrange:
    uint8_t firstInputByte = 56;
    uint8_t secondInputByte = 68;
    uint8_t outputChar;

    uint8_t expectedOutputChar = 120;

    //Act:
    decodeByte(firstInputByte, secondInputByte, &outputChar);

    //Assert:
    TEST_ASSERT_EQUAL_UINT8(outputChar,expectedOutputChar);
}

/**
 * @brief test the viability of the decodeByte function by looking
 * at the output character.
 * 
 */
void test_case_decode_byte_2()
{
    //Arrange:
    uint8_t firstInputByte = 46;
    uint8_t secondInputByte = 57;
    uint8_t outputChar;

    uint8_t expectedOutputChar = 87;

    //Act:
    decodeByte(firstInputByte, secondInputByte, &outputChar);

    //Assert:
    TEST_ASSERT_EQUAL_UINT8(outputChar,expectedOutputChar);
}

/**
 * @brief test the viability of the getNibble function by comparing
 * at the output character.
 * 
 */
void test_case_get_a_nibble_from_a_byte_1()
{
    //Arrange:
    uint8_t inputByte = 33;
    uint8_t nibble;

    uint8_t expectedNibble = 37;

    //Act:
    nibble = getNibble(inputByte);

    //Assert:
    TEST_ASSERT_EQUAL_UINT8(nibble,expectedNibble);
}

/**
 * @brief test the viability of the getNibble function by comparing
 * at the output character.
 * 
 */
void test_case_get_a_nibble_from_a_byte_2()
{
    //Arrange:
    uint8_t inputByte = 54;
    uint8_t nibble;

    uint8_t expectedNibble = 50;

    //Act:
    nibble = getNibble(inputByte);

    //Assert:
    TEST_ASSERT_EQUAL_UINT8(nibble,expectedNibble);
}

/**
 * @brief test the viability of the checkInterrupt function by looking
 * at the boolean after adding a value which is incorrect from the
 * parity mask diagram.
 * 
 */
void test_case_check_interrupt_true()
{
    //Arrange:
    uint8_t inputByte = 62;
    bool interrupted;

    //Act:
    interrupted = checkInterrupt(inputByte,FIRST_PARITY_MASK);

    //Assert:
    TEST_ASSERT_TRUE(interrupted);
}

/**
 * @brief test the viability of the checkInterrupt function by looking
 * at the boolean after adding a correct value which contains the
 * proper parity values.
 * 
 */
void test_case_check_interrupt_false()
{
    //Arrange:
    uint8_t inputByte = 46;
    bool interrupted;

    //Act:
    interrupted = checkInterrupt(inputByte,FIRST_PARITY_MASK);

    //Assert:
    TEST_ASSERT_FALSE(interrupted);
}

int main(void)
{
    UnityBegin(0);

    RUN_TEST(test_case_decode_byte_1,1);
    RUN_TEST(test_case_decode_byte_2,1);
    RUN_TEST(test_case_get_a_nibble_from_a_byte_1,1);
    RUN_TEST(test_case_get_a_nibble_from_a_byte_2,1);
    RUN_TEST(test_case_check_interrupt_true,1);
    RUN_TEST(test_case_check_interrupt_false,1);
    
    return UnityEnd();
}