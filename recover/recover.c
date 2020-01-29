#include <stdio.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Please enter 1 file to open.\n");
        return 1;
    }
    FILE *rfile = fopen(argv[1], "r");
    if (rfile == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    FILE *image = NULL;
    unsigned char buffer[512];
    char filename[8];
    int i = 0;
    bool open = false;
    while (fread(buffer, 512, 1, rfile) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (open == true)
            {
                fclose(image);
            }
            else
            {
                open = true;
            }
            sprintf(filename, "%03i.jpg", i);
            image = fopen(filename, "w");
            i++;
        }
        if (open == true)
        {
            fwrite(&buffer, 512, 1, image);
        }
    }

    fclose(rfile);
    fclose(image);
    return 0;

}