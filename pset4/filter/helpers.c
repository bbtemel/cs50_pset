#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int grey_value;
    for(int i = 0; i < height ; i++)
    {
        for ( int j = 0 ; j < width; j++)
        {
            grey_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = grey_value;
            image[i][j].rgbtGreen = grey_value;
            image[i][j].rgbtRed = grey_value;
        }
    }
    return;
}
int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height ; i++)
    {
        for ( int j = 0 ; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int originalRed = pixel.rgbtRed;
            int originalGreen = pixel.rgbtGreen;
            int originalBlue = pixel.rgbtBlue;
            image[i][j].rgbtRed = cap(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            image[i][j].rgbtGreen = cap(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            image[i][j].rgbtBlue = cap(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

        }
    }
    return;
}

void swap( RGBTRIPLE *limage, RGBTRIPLE *rimage)
{
     RGBTRIPLE temp = *limage;
     *limage = *rimage;
     *rimage = temp;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height ; i++)
    {
        for ( int j = 0 ; j < width/2 ; j++)
        {
            swap(&image[i][j] ,&image[i][width-j-1]);
        }
    }
    return;
}

bool check_validty(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}

RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int pixel_amount = 0;
    int redsum = 0;
    int greensum = 0;
    int bluesum = 0;
    for(int di = -1; di <= 1 ; di++)
    {
        for ( int dj = -1 ; dj <= 1; dj++)
        {
            int new_i=di+i;
            int new_j=dj+j;
            if(check_validty(new_i,new_j, height ,width))
            {
                pixel_amount++;
                redsum += image[new_i][new_j].rgbtRed;
                greensum += image[new_i][new_j].rgbtGreen;
                bluesum += image[new_i][new_j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = round((float) redsum / pixel_amount);
    blurred_pixel.rgbtGreen = round((float) greensum / pixel_amount);
    blurred_pixel.rgbtBlue = round((float) bluesum / pixel_amount);
    return blurred_pixel;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for(int i = 0; i < height ; i++)
    {
        for ( int j = 0 ; j < width; j++)
        {
            new_image[i][j]=get_blurred_pixel(i, j, height, width, image);
        }
    }
     for(int i = 0; i < height ; i++)
    {
        for ( int j = 0 ; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    return;
}
