#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int compute_words(string text, int len);
float compute_L(string text, int wordCount, int len);
float compute_S(string text, int wordCount, int len);
float compute_grade(float L, float S);

int main(void)
{
    string text = get_string("Text: ");
    int len = strlen(text);
    int wordCount = compute_words(text, len);

    float L = compute_L(text, wordCount, len);
    float S = compute_S(text, wordCount, len);
    float cli = compute_grade(L, S);
    int grade = round(cli);

    printf("Word Count: %i, L: %f, S: %f, CLI: %f\n", wordCount, L, S, cli);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 1 && grade <= 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int compute_words(string text, int len)
{
    int sum = 1;
    for (int i = 0; i < len; i++)
    {
        if (text[i] == ' ')
        {
            sum += 1;
        }
    }
    return sum;
}

float compute_L(string text, int wordCount, int len)
{
    int letters = 0;
    for (int i = 0; i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letters += 1;
        }
    }
    float L = (float) letters / wordCount * 100;
    return L;
}

float compute_S(string text, int wordCount, int len)
{
    int sentences = 0;
    for (int i = 0; i < len; i++)
    {
        if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            sentences += 1;
        }
    }
    float S = (float) sentences / wordCount * 100;
    return S;
}

float compute_grade(float L, float S)
{
    float index = 0.0588 * (float) L - 0.296 * S - 15.8;
    return index;
}
