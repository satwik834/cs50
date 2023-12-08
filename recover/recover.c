#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *image = fopen(argv[1], "r");
    FILE *img_out = NULL;

    typedef uint8_t BYTE;

    BYTE pkt[512];
    int img_count = 0;
    bool jpeg_open = false;
    while (fread(&pkt, 1, 512, image) == 512)
    {

        if (pkt[0] == 255 && pkt[1] == 216 && pkt[2] == 255 && pkt[3] <= 239 && pkt[3] >= 224)
        {
            if (jpeg_open == true && img_count > 0)
            {
                fclose(img_out);
                jpeg_open = false;
            }

            char filename[9];
            sprintf(filename, "%03i.jpg", img_count);
            img_count++;

            img_out = fopen(filename, "w");
            jpeg_open = true;
            fwrite(&pkt, 1, 512, img_out);
            continue;
        }
        else
        {
            if (jpeg_open == true)
            {
                fwrite(&pkt, 1, 512, img_out);
            }
        }
    }
    fclose(image);

    if (jpeg_open == true)
    {
        fclose(img_out);
    }
}