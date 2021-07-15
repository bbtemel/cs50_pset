#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int greyscale;
            greyscale = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);

            image[i][j].rgbtRed = greyscale;
            image[i][j].rgbtGreen = greyscale;
            image[i][j].rgbtBlue = greyscale;
        }
    }
    return;
}

void swap(RGBTRIPLE *limage , RGBTRIPLE *rimage)
{
    RGBTRIPLE temp = *limage;
    *limage = *rimage;
    *rimage = temp;

    ;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
           swap(&image[i][j], &image[i][width -j -1]);
        }
    }

    return;
}
bool check_validity(int i, int j, int height, int width)
{
    return i >= 0 && i < height && j >= 0 && j < width;
}
RGBTRIPLE get_blurred_pixel(int i, int j, int height, int width, RGBTRIPLE real_image[height][width])
{
    int redsum=0;
    int greensum=0;
    int bluesum=0;
    int pixelcount=0;
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = di+i;
            int new_j = dj+j;
            if(check_validity(new_i, new_j, height ,width))
            {
             pixelcount++;
             redsum += real_image[new_i][new_j].rgbtRed;
             greensum += real_image[new_i][new_j].rgbtGreen;
             bluesum += real_image[new_i][new_j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = round((float)redsum/pixelcount);
    blurred_pixel.rgbtGreen = round((float)greensum/pixelcount);
    blurred_pixel.rgbtBlue = round((float)bluesum/pixelcount);

    return blurred_pixel;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            new_image[i][j] = get_blurred_pixel(i,j,height, width,image);

        }
    }

    for(int i = 0; i<height;i++)
    {
        for(int j = 0; j<width;j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}


int cap(int x)
{
    return x > 255 ? 255 : x;
}

RGBTRIPLE get_edge_pixel(int i, int j, int height, int width, RGBTRIPLE real_image[height][width])
{
    int redsumgx=0;
    int greensumgx=0;
    int bluesumgx=0;
    int redsumgy=0;
    int greensumgy=0;
    int bluesumgy=0;
    int gx[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int gy[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    for (int di = -1; di <= 1; di++)
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            int new_i = di+i;
            int new_j = dj+j;
            if( new_i < 0  || new_i > height-1 || new_j < 0 || new_j > width-1)
            {
                redsumgx += 0;
                greensumgx += 0;
                bluesumgx += 0;

                redsumgy += 0;
                greensumgy += 0;
                bluesumgy += 0;

            }
            else{
            redsumgx += gx[di + 1][dj + 1] * real_image[new_i][new_j].rgbtRed;
            greensumgx += gx[di + 1][dj + 1] * real_image[new_i][new_j].rgbtGreen;
            bluesumgx += gx[di + 1][dj + 1] * real_image[new_i][new_j].rgbtBlue;

            redsumgy += gy[di + 1][dj + 1] * real_image[new_i][new_j].rgbtRed;
            greensumgy += gy[di + 1][dj + 1] * real_image[new_i][new_j].rgbtGreen;
            bluesumgy += gy[di + 1][dj + 1] * real_image[new_i][new_j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE edge_pixel;
    edge_pixel.rgbtRed = cap(round(sqrt(redsumgx*redsumgx + redsumgy*redsumgy)));
    edge_pixel.rgbtGreen = cap(round(sqrt(greensumgx*greensumgx + greensumgy*greensumgy)));
    edge_pixel.rgbtBlue = cap(round(sqrt(bluesumgx*bluesumgx + bluesumgy*bluesumgy)));
    return edge_pixel;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            new_image[i][j] = get_edge_pixel(i,j,height, width,image);

        }
    }
    for(int i = 0; i<height;i++)
    {
        for(int j = 0; j<width;j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}
