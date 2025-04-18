#include <cs50.h>
#include <stdio.h>

void print_brick(int i);
void print_blank(int i);

int main(void)
{
    int height;
    do
    {
        // Prompt user for pyramid height
        height = get_int("Input height of pyramid: ");
    }
    while (height < 1 || height > 8);

    // Calls the print_row function
    for (int i = 0; i < height; i++)
    {
        print_blank(height - i - 1);
        print_brick(i + 1);
        print_blank(2);
        print_brick(i + 1);
        printf("\n");
    }
}

// Prints bricks "#"
void print_brick(int i)
{
    for (int j = 0; j < i; j++)
    {
        printf("#");
    }
}

// Prints blanks " "
void print_blank(int i)
{
    for (int k = 0; k < i; k++)
    {
        printf(" ");
    }
}
