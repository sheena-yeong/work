#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_score(string upper_input);
string upper_case(string input);

// Store the key in global scope for functions to access
int points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main(void)
{
    string input1 = get_string("Player 1: ");
    string input2 = get_string("Player 2: ");

    string upper_input1 = upper_case(input1);
    string upper_input2 = upper_case(input2);

    int score1 = compute_score(upper_input1);
    int score2 = compute_score(upper_input2);

    printf("Score 1: %i\n", score1);
    printf("Score 2: %i\n", score2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string upper_input)
{
    int score = 0;
    for (int i = 0, len = strlen(upper_input); i < len; i++)
    {
        score = score + points[upper_input[i] - 'A'];
    }
    return score;
}

string upper_case(string input)
{
    for (int i = 0, len = strlen(input); i < len; i++)
    {
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            input[i] = input[i] - 32;
        }
        else if (input[i] >= 'A' && input[i] <= 'Z')
        {
            input[i] = input[i];
        }
        else if (input[i] < 'a' || input[i] > 'z')
        {
            input[i] = 0;
        }
    }
    return input;
}
