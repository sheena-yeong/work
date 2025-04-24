# Coleman-Liau index: 0.0588 * L - 0.296 * S - 15.8, where L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text. Output should be "Before Grade 1, Grade 1..Grade 16+

from cs50 import get_string


def main():
    text = get_string("Text: ")

    letters = 0
    sentences = 0
    spaces = 0

    for char in text:
        if char.isalpha():
            letters += 1
        elif char in ".!?":
            sentences += 1
        elif char in " ":
            spaces += 1
    words = spaces + 1

    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {round(index)}")


main()
