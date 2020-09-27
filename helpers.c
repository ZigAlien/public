#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE *r = &image[h][w].rgbtRed;
            BYTE *g = &image[h][w].rgbtGreen;
            BYTE *b = &image[h][w].rgbtBlue;
            float avg = (*r + *g + *b) / 3.0;
            BYTE avgg = round(avg);
            image[h][w].rgbtRed = avgg;
            image[h][w].rgbtBlue = image[h][w].rgbtRed;
            image[h][w].rgbtGreen = image[h][w].rgbtRed;
        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            BYTE *originalRed = &image[h][w].rgbtRed;
            BYTE *originalGreen = &image[h][w].rgbtGreen;
            BYTE *originalBlue = &image[h][w].rgbtBlue;
            float sepiaRed = .393 * *originalRed + .769 * *originalGreen + .189 * *originalBlue;
            float sepiaGreen = .349 * *originalRed + .686 * *originalGreen + .168 * *originalBlue;
            float sepiaBlue = .272 * *originalRed + .534 * *originalGreen + .131 * *originalBlue;
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
            BYTE sepiaRedd = round(sepiaRed);
            BYTE sepiaGreenn = round(sepiaGreen);
            BYTE sepiaBluee = round(sepiaBlue);

            *originalRed = sepiaRedd;
            *originalBlue = sepiaBluee;
            *originalGreen = sepiaGreenn;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < half; w++)
        {
            BYTE *r1 = &image[h][w].rgbtRed;
            BYTE *g1 = &image[h][w].rgbtGreen;
            BYTE *b1 = &image[h][w].rgbtBlue;

            BYTE *r2 = &image[h][width - w - 1].rgbtRed;
            BYTE *g2 = &image[h][width - w - 1].rgbtGreen;
            BYTE *b2 = &image[h][width - w - 1].rgbtBlue;

            BYTE tempr = *r1;
            BYTE tempg = *g1;
            BYTE tempb = *b1;

            image[h][w].rgbtRed = *r2;
            image[h][w].rgbtGreen = *g2;
            image[h][w].rgbtBlue = *b2;
            image[h][width - w - 1].rgbtRed = tempr;
            image[h][width - w - 1].rgbtGreen = tempg;
            image[h][width - w - 1].rgbtBlue = tempb;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //makes a copy of the image in an array called temp
    RGBTRIPLE *temp = (RGBTRIPLE *)malloc(height * width * sizeof(RGBTRIPLE));
    if (temp == NULL)
    {
        printf("malloc failed\n");
        return;
    }
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            temp[h * width + w] = image[h][w];
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            double rsum = 0;
            double gsum = 0;
            double bsum = 0;
            int pixelnum = 0;

            //all middle pixels
            if (h > 0 && h < height - 1 && w > 0 && w < width - 1)
            {
                for (int i = -1; i < 2; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //top left corner
            else if (h == 0 && w == 0)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //top right corner
            else if (h == 0 && w == width - 1)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = -1; j < 1; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //bottom left corner
            else if (h == height - 1 && w == 0)
            {
                for (int i = -1; i < 1; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //bottom right corner
            else if (h == height - 1 && w == width - 1)
            {
                for (int i = -1; i < 1; i++)
                {
                    for (int j = -1; j < 1; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //top edge
            else if (h == 0)
            {
                for (int i = 0; i < 2; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //bottom edge
            else if (h == height - 1)
            {
                for (int i = -1; i < 1; i++)
                {
                    for (int j = -1; j < 2; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //left edge
            else if (w == 0)
            {
                for (int i = -1; i < 2; i++)
                {
                    for (int j = 0; j < 2; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }

            //right edge
            else if (w == width - 1)
            {
                for (int i = -1; i < 2; i++)
                {
                    for (int j = -1; j < 1; j++)
                    {
                        rsum += temp[(h + i) * width + w + j].rgbtRed;
                        gsum += temp[(h + i) * width + w + j].rgbtGreen;
                        bsum += temp[(h + i) * width + w + j].rgbtBlue;
                        pixelnum++;
                    }
                }
            }
            float ravg = rsum / pixelnum;
            float gavg = gsum / pixelnum;
            float bavg = bsum / pixelnum;
            BYTE r = round(ravg);
            BYTE g = round(gavg);
            BYTE b = round(bavg);
            image[h][w].rgbtRed = r;
            image[h][w].rgbtGreen = g;
            image[h][w].rgbtBlue = b;
        }
    }
    //remember to free all malloc space
    free(temp);
    return;
}

/*could improve blur program by creating function to calculate the average
void average (int h, int w, int i, int j, RGBTRIPLE temp[h * width + w])
{
    double rsum = 0;
    double gsum = 0;
    double bsum = 0;
    int pixelnum = 0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = -1; j < 1; j++)
        {
            rsum += temp[(h + i) * width + w + j].rgbtRed;
            gsum += temp[(h + i) * width + w + j].rgbtGreen;
            bsum += temp[(h + i) * width + w + j].rgbtBlue;
            pixelnum++;
        }
    }
    float ravg = rsum / pixelnum;
    float gavg = gsum / pixelnum;
    float bavg = bsum / pixelnum;
    BYTE r = round(ravg);
    BYTE g = round(gavg);
    BYTE b = round(bavg);
}*/
