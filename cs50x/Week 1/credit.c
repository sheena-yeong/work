#include <cs50.h>
#include <math.h>
#include <stdio.h>

int every_other_digit(long number);
int multiplyAndSum(int last_digit);
int sum_remaining_digits(long number);
int number_of_digits(long number);
bool ifAmex(long number, int numDigits);
bool ifMasterCard(long number, int numDigits);
bool ifVISA(long number, int numDigits);

int main(void)
{
    // Prompt for input
    long number = get_long("Enter Credit Card Number: ");

    int product = every_other_digit(number);
    printf("Sum of Alternate Digits Multiplied %i\n", product);

    int remaining = sum_remaining_digits(number);
    printf("Sum of Remaining Digits: %i\n", remaining);

    // Checks if AMEX OR MASTERCARD OR VISA OR INVALID
    int numDigits = number_of_digits(number);
    printf("Number of digits: %i\n", numDigits);

    bool isValidAmex = ifAmex(number, numDigits);
    bool isValidMasterCard = ifMasterCard(number, numDigits);
    bool isValidVISA = ifVISA(number, numDigits);

    int validation = product + remaining;
    int last_digit_validation = validation % 10;

    if (last_digit_validation != 0)
    {
        printf("Validation last digit: %i\n", last_digit_validation);
        printf("INVALID\n");
    }
    else if (isValidAmex == true)
    {
        printf("AMEX\n");
    }
    else if (isValidMasterCard == true)
    {
        printf("MASTERCARD\n");
    }
    else if (isValidVISA == true)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

int every_other_digit(long number)
{
    int sum = 0;
    bool isAlternateDigit = false;
    while (number > 0)
    {
        if (isAlternateDigit == true)
        {
            int last_digit = number % 10;
            int product = multiplyAndSum(last_digit);
            sum = sum + product;
        }
        isAlternateDigit = !isAlternateDigit;
        number = number / 10;
    }
    return sum;
}

int multiplyAndSum(int last_digit)
{
    int multiply = last_digit * 2;   // Multiply last digit by 2
    int sum_multiply_last_digit = 0; // create a integer to store the sum
    while (multiply > 0)
    {
        int last_digit_after_multiply = multiply % 10; // Getting last digit
        sum_multiply_last_digit =
            sum_multiply_last_digit + last_digit_after_multiply; // store last digit in sum
        multiply =
            multiply /
            10; // Remove the last digit in multiply. Only need to do it once as max is 2 digits
    }
    return sum_multiply_last_digit;
}

// sum of the digits that weren’t multiplied by 2 (starting from the end)
int sum_remaining_digits(long number)
{
    int sum = 0;
    bool isAlternateDigit = true;
    while (number > 0)
    {
        if (isAlternateDigit == true)
        {
            int last_digit = number % 10;
            sum = sum + last_digit;
        }
        isAlternateDigit = !isAlternateDigit;
        number = number / 10;
    }
    return sum;
}

// Count length of credit card number
int number_of_digits(long number)
{
    int sum = 0;
    while (number > 0)
    {
        sum += 1;
        number = number / 10;
    }
    return sum;
}

bool ifAmex(long number, int numDigits)
{
    int first_two_digits = number / pow(10, 13);
    if ((numDigits == 15) && (first_two_digits == 34 || first_two_digits == 37))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ifMasterCard(long number, int numDigits)
{
    int first_two_digits = number / pow(10, 14);
    if ((numDigits == 16) && (first_two_digits >= 51 && first_two_digits <= 55))
    {
        return true;
    }
    return false;
}

bool ifVISA(long number, int numDigits)
{
    if (numDigits == 16)
    {
        int first_digit = number / pow(10, 15);
        return (first_digit == 4);
    }
    else if (numDigits == 13)
    {
        int first_digit = number / pow(10, 12);
        return (first_digit == 4);
    }
    else
    {
        return false;
    }
}
