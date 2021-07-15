#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512
#define FILENAMESIZE 8
typedef uint8_t BYTE;
bool startof_newjpeg(BYTE buffer[BLOCK_SIZE]);
int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open memory card
    FILE *f = fopen(argv[1], "r");
    if(f == NULL)
    {
        printf("Could not open the file\n");
        return 1;
    }


    BYTE buffer[BLOCK_SIZE];

    bool have_found_firstjpeg = false;

    FILE *outputfile;
    int filecount = 0;
    //repeat until end of card
    while (fread(buffer, BLOCK_SIZE, 1, f) != 0)
    {
        //Read 512 bytes into buffer


        //if start of new jpeg
        if(startof_newjpeg(buffer))
        {
            //if first jpeg

            if(!have_found_firstjpeg)
            {
                have_found_firstjpeg = true;
            }
            //else
            else
            {
                fclose(outputfile);
            }
            char filename[FILENAMESIZE];
            sprintf ( filename, "%03i.jpg", filecount++);
            outputfile = fopen(filename, "w");
            if (outputfile == NULL)
            {
                printf("Could not open the file\n");
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE,1, outputfile);

        }
        //already found jpeg
        else if (have_found_firstjpeg)
        {
            fwrite(buffer, BLOCK_SIZE,1, outputfile);
        }
    //close any remainig files
    }
    fclose(f);
    fclose(outputfile);
    return 0;
}

bool startof_newjpeg(BYTE buffer[BLOCK_SIZE])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}