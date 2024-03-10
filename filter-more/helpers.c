#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            float average_f = (blue + green + red) / 3.0;
            int average_i = average_f;
            float first_decimal_f = (average_f - average_i) * 10;
            int first_decimal = first_decimal_f;
            int average = average_f;
            if (first_decimal >= 5)
            {
                average++;
            }

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE empt[1][1];
            empt[0][0] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = empt[0][0];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE rep[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_b = 0;
            int sum_g = 0;
            int sum_r = 0;
            int sum_counter = 0;
            for (int y = -1; y <=1; y++)
            {
                for (int x = -1; x <=1; x++)
                {
                    if (i + y < 0 || i + y > (height - 1) || j + x < 0 || j + x > (width - 1))
                    {
                        continue;
                    }
                    sum_b = sum_b + image[i + y][j + x].rgbtBlue;
                    sum_g = sum_g + image[i + y][j + x].rgbtGreen;
                    sum_r = sum_r + image[i + y][j + x].rgbtRed;
                    sum_counter++;
                }
            }

            float average_b = 1.0 * sum_b / sum_counter;
            float average_g = 1.0 * sum_g / sum_counter;
            float average_r = 1.0 * sum_r / sum_counter;

            average_b = round(average_b);
            average_g = round(average_g);
            average_r = round(average_r);

            rep[i][j].rgbtBlue = average_b;
            rep[i][j].rgbtGreen = average_g;
            rep[i][j].rgbtRed = average_r;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = rep[i][j].rgbtBlue;
            image[i][j].rgbtGreen = rep[i][j].rgbtGreen;
            image[i][j].rgbtRed = rep[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE rep[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gx_blue = 0;
            int gx_green = 0;
            int gx_red = 0;

            int gy_blue = 0;
            int gy_green = 0;
            int gy_red = 0;

            int order_of_y = 0;
            for (int y = -1; y <= 1; y++)
            {
                int order_of_x = 0;
                for (int x = -1; x <= 1; x++)
                {
                    if (i + y < 0 || i + y > (height - 1) || j + x < 0 || j + x > (width - 1))
                    {
                        order_of_x++;
                        continue;
                    }

                    int x_factor = x;
                    if (order_of_y % 2 != 0)
                    {
                        x_factor = x_factor * 2;
                    }

                    gx_blue = gx_blue + image[i + y][j + x].rgbtBlue * x_factor;
                    gx_green = gx_green + image[i + y][j + x].rgbtGreen * x_factor;
                    gx_red = gx_red + image[i + y][j + x].rgbtRed * x_factor;

                    int y_factor = y;
                    if (order_of_x % 2 != 0)
                    {
                        y_factor = y_factor * 2;
                    }

                    gy_blue = gy_blue + image[i + y][j + x].rgbtBlue * y_factor;
                    gy_green = gy_green + image[i + y][j + x].rgbtGreen * y_factor;
                    gy_red = gy_red + image[i + y][j + x].rgbtRed * y_factor;

                    order_of_x++;
                }
                order_of_y++;
            }

            int g_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));
            if (g_blue > 255)
            {
                g_blue = 255;
            }

            int g_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            if (g_green > 255)
            {
                g_green = 255;
            }

            int g_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            if (g_red > 255)
            {
                g_red = 255;
            }

            rep[i][j].rgbtBlue = g_blue;
            rep[i][j].rgbtGreen = g_green;
            rep[i][j].rgbtRed = g_red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = rep[i][j].rgbtBlue;
            image[i][j].rgbtGreen = rep[i][j].rgbtGreen;
            image[i][j].rgbtRed = rep[i][j].rgbtRed;
        }
    }
    return;
}