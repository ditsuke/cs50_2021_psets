#include "helpers.h"

#include <math.h>
#include <stdbool.h>

// Utility macro to swap values of subpixel intensities
#define swap_e(a, b) \
    {                \
        a += b;      \
        b = a - b;   \
        a -= b;      \
    }

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of pixels
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel in row
        for (int j = 0; j < width; j++)
        {
            // For greyscale, rgb values are average of pixel intensities of each color rounded to nearest int
            unsigned char rgbtGreyscale = round((image[i][j].rgbtRed + 
                                                 image[i][j].rgbtGreen + 
                                                 image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = rgbtGreyscale;
            image[i][j].rgbtGreen = rgbtGreyscale;
            image[i][j].rgbtBlue = rgbtGreyscale;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of pixels
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel in row
        for (int j = 0; j < width; j++)
        {
            // Store sepia values
            int sepiaRed, sepiaGreen, sepiaBlue;

            // Compute sepia values
            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 
                             0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 
                               0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 
                              0.131 * image[i][j].rgbtBlue);

            // Cap values at 255 if they exceed it, else keep them as computed sepia values as per spec
            image[i][j].rgbtRed = (sepiaRed < 255) ? (sepiaRed) : (255);
            image[i][j].rgbtGreen = (sepiaGreen < 255) ? (sepiaGreen) : (255);
            image[i][j].rgbtBlue = (sepiaBlue < 255) ? (sepiaBlue) : (255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each row of pixels
    for (int i = 0; i < height; i++)
    {
        // Iterate over half the pixels in row
        for (int j = 0; j < width / 2; j++)
        {
            // Swap subpixel intensities with those of pixel at the same index from the end
            swap_e(image[i][j].rgbtRed, image[i][width - j - 1].rgbtRed);
            swap_e(image[i][j].rgbtGreen, image[i][width - j - 1].rgbtGreen);
            swap_e(image[i][j].rgbtBlue, image[i][width - j - 1].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurImage[height][width];

    // Iterate over each row of pixels
    for (int i = 0; i < height; i++)
    {
        // Iterate over each pixel in row
        for (int j = 0; j < width; j++)
        {
            // Store sum of neighbor pixel intensities
            int sumRed = 0, sumGreen = 0, sumBlue = 0;

            // Keep track of valid neighbors
            int neighborCount = 0;

            // Iterate over 3x3 grid around each pixel, add pixel intensities
            // Skip if outside bound
            for (int k = -1; k <= 1; k++)
            {
                // Jump to next iteration if cell row is out of bounds
                if (i + k < 0 || i + k >= height)
                {
                    continue;
                }
                for (int l = -1; l <= 1; l++)
                {
                    // Jump to next iteration if cell column is out of bounds
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    neighborCount++;
                    sumRed += image[i + k][j + l].rgbtRed;
                    sumGreen += image[i + k][j + l].rgbtGreen;
                    sumBlue += image[i + k][j + l].rgbtBlue;
                }
            }

            // Compute average subpixel intensities from sum of neighbor intensities
            // rounded to nearest int
            blurImage[i][j].rgbtRed = round(sumRed / (float)neighborCount);
            blurImage[i][j].rgbtGreen = round(sumGreen / (float)neighborCount);
            blurImage[i][j].rgbtBlue = round(sumBlue / (float)neighborCount);
        }
    }
    // Copies subpixel values from blurImage to image
    // Iterating over each row in pixel grid
    for (int i = 0; i < height; i++)
    {
        // Iterating over each pixel
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurImage[i][j].rgbtRed;
            image[i][j].rgbtGreen = blurImage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = blurImage[i][j].rgbtBlue;
        }
    }

    return;
}