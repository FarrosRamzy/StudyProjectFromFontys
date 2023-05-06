#include <unity.h>
#include <file_channeler.h>

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
 * @brief test the viability of the transmitByte function to change or interrupt
 * the data. (the output should be 99.9% different from the input)
 *
 */
void test_case_transmit_byte_1()
{
    // Arrange:
    uint8_t inputByte = 65;
    uint8_t outputByte = 0;

    uint8_t expectedOutputByte = 65;

    // Act:
    transmitByte(inputByte, &outputByte);

    // Assert:
    TEST_ASSERT_NOT_EQUAL_UINT8(outputByte, expectedOutputByte);
}

/**
 * @brief test the viability of the transmitByte function to change or interrupt
 * the data. (the output should be 99.9% different from the input)
 *
 */
void test_case_transmit_byte_2()
{
    // Arrange:
    uint8_t inputByte = 77;
    uint8_t outputByte = 0;

    uint8_t expectedOutputByte = 77;

    // Act:
    transmitByte(inputByte, &outputByte);

    // Assert:
    TEST_ASSERT_NOT_EQUAL_UINT8(outputByte, expectedOutputByte);
}

/**
 * @brief testing the viability of transmitByte by looking at the interrupt position.
 *
 */
void test_case_interrupt_position_1()
{
    // Arrange:
    uint8_t inputByte = 65;
    uint8_t outputByte = 0;
    uint8_t interruptPosition = 0;

    uint8_t expectedInterruptPosition = 0;

    // Act:
    interruptPosition = transmitByte(inputByte, &outputByte);

    // Assert:
    TEST_ASSERT_UINT8_WITHIN(7, expectedInterruptPosition, interruptPosition);
}

/**
 * @brief testing the viability of transmitByte by looking at the interrupt position.
 *
 */
void test_case_interrupt_position_2()
{
    // Arrange:
    uint8_t inputByte = 77;
    uint8_t outputByte = 0;
    uint8_t interruptPosition = 0;

    uint8_t expectedInterruptPosition = 8;

    // Act:
    interruptPosition = transmitByte(inputByte, &outputByte);

    // Assert:
    TEST_ASSERT_UINT8_WITHIN(7, expectedInterruptPosition, interruptPosition);
}

int main(void)
{
    UnityBegin(0);

    srand((unsigned)time(NULL));

    RUN_TEST(test_case_transmit_byte_1, 1);
    RUN_TEST(test_case_transmit_byte_2, 2);
    RUN_TEST(test_case_interrupt_position_1, 1);
    RUN_TEST(test_case_interrupt_position_2, 2);

    return UnityEnd();
}