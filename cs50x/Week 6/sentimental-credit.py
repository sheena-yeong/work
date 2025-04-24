from cs50 import get_string

# 4003600000000014
# AMEX 378282246310005
# MASTERCARD 5555555555554444
# VISA 4111111111111111


def main():
    number = get_string("Enter Credit Card Number: ")
    if valid(number) == False:
        print("INVALID")
    elif ifAMEX(number):
        print("AMEX")
    elif ifMASTERCARD(number):
        print("MASTERCARD")
    elif ifVISA(number):
        print("VISA")
    else:
        print("INVALID")

# INVALID numbers: 369421438430814, 4062901840, 5673598276138003, 1234567890


def valid(number):
    # Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.

    reverse = number[::-1]
    total = 0

    for i in range(1, len(reverse), 2):
        digit = int(reverse[i]) * 2
        if digit > 9:
            total += digit // 10 + digit % 10
        else:
            total += digit

    # Add the sum to the sum of the digits that weren’t multiplied by 2.

    for i in range(0, len(reverse), 2):
        total += int(reverse[i])

    # If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

    if total % 10 == 0:
        return True
    else:
        return False


def ifAMEX(number):
    # 15 digits, start with 34 or 37

    if len(number) == 15 and number[:2] in ("34", "37"):
        return True
    else:
        return False


def ifMASTERCARD(number):
    # 16 digits, start with 51, 52, 53, 54, 55

    if len(number) == 16 and number[:2] in ("51", "52", "53", "54", "55"):
        return True
    else:
        return False


def ifVISA(number):
    # 13 or 16 digits, start with 4

    if len(number) in (13, 16) and number[:1] == "4":
        return True
    else:
        return False


main()
