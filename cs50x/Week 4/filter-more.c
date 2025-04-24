#include "helpers.h"
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int RGBaverage = round(
                ((float) image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = RGBaverage;
            image[i][j].rgbtGreen = RGBaverage;
            image[i][j].rgbtRed = RGBaverage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    bool ifeven = (width % 2 == 0);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // width/2 is possible as int will truncate
        {
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create copy of current image
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalBlue = 0;
            int totalGreen = 0;
            int totalRed = 0;
            int totalCount = 0;

            for (int ii = -1; ii < 2; ii++)
            {
                for (int jj = -1; jj < 2; jj++)
                {
                    int ni = i + ii;
                    int nj = j + jj;

                    if (ni >= 0 && nj >= 0 && ni < height && nj < width)
                    {
                        totalBlue += image[ni][nj].rgbtBlue;
                        totalGreen += image[ni][nj].rgbtGreen;
                        totalRed += image[ni][nj].rgbtRed;
                        totalCount += 1;
                    }
                }
            }
            temp[i][j].rgbtBlue = round((float) totalBlue / totalCount);
            temp[i][j].rgbtGreen = round((float) totalGreen / totalCount);
            temp[i][j].rgbtRed = round((float) totalRed / totalCount);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy of image
    RGBTRIPLE copy[height][width];

    int gx_array[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int gy_array[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_red = 0, gx_green = 0, gx_blue = 0, gy_red = 0, gy_green = 0, gy_blue = 0;
            int counter = 0;

            for (int ii = -1; ii < 2; ii++)
            {
                for (int jj = -1; jj < 2; jj++)
                {
                    int ni = i + ii;
                    int nj = j + jj;

                    if (ni >= 0 && nj >= 0 && ni < height && nj < width)
                    {
                        gx_red += gx_array[counter] * image[ni][nj].rgbtRed;
                        gx_green += gx_array[counter] * image[ni][nj].rgbtGreen;
                        gx_blue += gx_array[counter] * image[ni][nj].rgbtBlue;
                        gy_red += gy_array[counter] * image[ni][nj].rgbtRed;
                        gy_green += gy_array[counter] * image[ni][nj].rgbtGreen;
                        gy_blue += gy_array[counter] * image[ni][nj].rgbtBlue;
                    }
                    counter++;
                }
            }
            int final_red = round(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
            int final_green = round(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
            int final_blue = round(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2)));

            // Usage of ternary operator so that other values are not affected
            copy[i][j].rgbtRed = final_red > 255 ? 255 : final_red;
            copy[i][j].rgbtGreen = final_green > 255 ? 255 : final_green;
            copy[i][j].rgbtBlue = final_blue > 255 ? 255 : final_blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }
    return;
}
