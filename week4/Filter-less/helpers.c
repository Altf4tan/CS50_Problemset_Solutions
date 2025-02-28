#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each row until max height
    for (int row = 0; row < height; row++)
    {
        // Loop through each column until max width
        for (int col = 0; col < width; col++)
        {
            // Get each value for each color
            int red_value = image[row][col].rgbtRed;
            int green_value = image[row][col].rgbtGreen;
            int blue_value = image[row][col].rgbtBlue;
            // Find the average value and apply to each pixel
            float average = round((red_value + green_value + blue_value) / 3.0);
            image[row][col].rgbtRed = average;
            image[row][col].rgbtGreen = average;
            image[row][col].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Get each value for each color
            int red_value = image[row][col].rgbtRed;
            int green_value = image[row][col].rgbtGreen;
            int blue_value = image[row][col].rgbtBlue;
            // Get each sepia color value
            float sepiaRed = .393 * red_value + .769 * green_value + .189 * blue_value;
            float sepiaGreen = .349 * red_value + .686 * green_value + .168 * blue_value;
            float sepiaBlue = .272 * red_value + .534 * green_value + .131 * blue_value;
            // Ensure the value is not bigger than 255 for each color
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[row][col].rgbtRed = (int) round(sepiaRed);
            image[row][col].rgbtGreen = (int) round(sepiaGreen);
            image[row][col].rgbtBlue = (int) round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        // Only iterate halfway through the row because each pixel is swapped with its mirror on the opposite side
        for (int col = 0; col < (width / 2); col++)
        {
            // Calculate the index of the pixel on the opposite side of the row
            int mirror = (width - 1) - col;
            // Swap pixels so the left side is mirrored with the right side
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][mirror];
            image[row][mirror] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    // Loop through each row until max height
    for (int row = 0; row < height; row++)
    {
        // Loop through each column until max width
        for (int col = 0; col < width; col++)
         {
            // Resetting sums once per pixel
            int sum_red = 0, sum_green = 0, sum_blue = 0;
            int neighbor_count = 0;
            // Doing neighbor loops to accumulate sums of pixels
            for (int neighbor_row = row - 1; neighbor_row <= row + 1; neighbor_row++)
            {
                for (int neighbor_col = col - 1; neighbor_col <= col + 1; neighbor_col++)
                {
                    // Making sure (row, col) is within the image bounds
                    if (0 <= neighbor_row && neighbor_row < height)
                    {
                        if (0 <= neighbor_col && neighbor_col < width)
                        {
                            // Accumulating the color values of all the neighbors (including the pixel itself)
                            sum_red += image[neighbor_row][neighbor_col].rgbtRed;
                            sum_green += image[neighbor_row][neighbor_col].rgbtGreen;
                            sum_blue += image[neighbor_row][neighbor_col].rgbtBlue;
                            neighbor_count++;
                        }
                    }
                }
            }
            // Once the channels are summed, we do the floating-point division so we get an accurate decimal
            float new_red = (float) sum_red / neighbor_count;
            float new_green = (float) sum_green / neighbor_count;
            float new_blue = (float) sum_blue / neighbor_count;

            // This prevents messing up the original before finishing calculating neighbors for all other pixels.
            copy[row][col].rgbtRed = round(new_red);
            copy[row][col].rgbtGreen = round(new_green);
            copy[row][col].rgbtBlue = round(new_blue);
        }
    }
    // Copy the temporary array into image itself for making sure our image is blurred
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}
