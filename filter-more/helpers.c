#include "helpers.h"
#include "math.h"

int final_value(int colour[3][3]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            float avg = (image[i][k].rgbtBlue + image[i][k].rgbtGreen + image[i][k].rgbtRed) / 3.0;
            image[i][k].rgbtBlue = round(avg);
            image[i][k].rgbtGreen = round(avg);
            image[i][k].rgbtRed =   round(avg);

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < (width / 2); k++)
        {
            RGBTRIPLE *original_left = &image[i][k];
            RGBTRIPLE *original_right = &image[i][width - k - 1];

            RGBTRIPLE tmp = image[i][k];
            *original_left = image[i][width - k - 1];
            *original_right = tmp;
        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE final[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            int sum_blue  = 0;
            int sum_red   = 0;
            int sum_green = 0;
            float avg_count = 0.0;
            RGBTRIPLE *original = &image[i][k];
            for (int p = -1; p < 2; p++)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (!(i + p < 0 || k + m < 0 || i + p > height - 1 || k + m > width - 1))
                    {
                        sum_blue  += image[i + p][k + m].rgbtBlue;
                        sum_red   += image[i + p][k + m].rgbtRed;
                        sum_green += image[i + p][k + m].rgbtGreen;
                        avg_count++;
                    }

                }

            }
            final[i][k].rgbtBlue = round(sum_blue / avg_count);
            final[i][k].rgbtRed = round(sum_red / avg_count);
            final[i][k].rgbtGreen = round(sum_green / avg_count);

        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = final[i][j].rgbtBlue;
            image[i][j].rgbtGreen = final[i][j].rgbtGreen;
            image[i][j].rgbtRed = final[i][j].rgbtRed;
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            // make a 3*3 matrix of all colours
            int blue[3][3];
            int red[3][3];
            int green[3][3];
            for (int p = -1; p < 2; p++)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (!(i + p < 0 || k + m < 0 || i + p > height - 1 || k + m > width - 1))
                    {
                        blue[p + 1][m + 1] = image[i + p][k + m].rgbtBlue;
                        red[p + 1][m + 1] = image[i + p][k + m].rgbtRed;
                        green[p + 1][m + 1] = image[i + p][k + m].rgbtGreen;
                    }
                    else
                    {
                        blue[p + 1][m + 1] = 0;
                        red[p + 1][m + 1] = 0;
                        green[p + 1][m + 1] = 0;
                    }

                }

            }
            temp[i][k].rgbtRed   = (final_value(red) > 255) ? 255 : final_value(red);
            temp[i][k].rgbtBlue  = (final_value(blue) > 255) ? 255 : final_value(blue);
            temp[i][k].rgbtGreen = (final_value(green) > 255) ? 255 : final_value(green);
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

int final_value(int colour[3][3])
{

    int gx[3][3];
    int gy[3][3];

    gx[0][1] = gx[1][1] = gx[2][1] = 0;
    gx[0][0] = gx[2][0] = -1;
    gx[0][2] = gx[2][2] =  1;
    gx[1][0] = -2;
    gx[1][2] =  2;

    gy[1][0] = gy[1][1] = gy[1][2]  = 0;
    gy[0][0] = gy[0][2] = -1;
    gy[2][0] = gy[2][2] =  1;
    gy[0][1] = -2;
    gy[2][1] =  2;

    float final_colour = 0;
    int final_gx = 0;
    int final_gy = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {
            final_gx += colour[i][k] * gx[i][k];
            final_gy += colour[i][k] * gy[i][k];
        }
    }
    final_colour = sqrt(((final_gx * final_gx) + (final_gy * final_gy)));

    return round(final_colour);
}