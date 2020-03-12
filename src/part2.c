#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 25
#define HEIGHT 6
#define MAX_LAYERS 100

int main (int argc, char * argv[])
{
    FILE * infile=NULL;
    char image[MAX_LAYERS][HEIGHT][WIDTH];
    char layer_buffer[WIDTH*HEIGHT+1];
    char final_image[HEIGHT][WIDTH];
    
    int minZeros=9999, answer, numZeros, numOnes, numTwos;
    
    memset(&layer_buffer, '\0', sizeof(layer_buffer));
    memset(&image, '\0', sizeof(image));
    memset(&final_image, '\0', sizeof(final_image));
    
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        exit(1);
    }
    
    fprintf(stderr, "Opening file %s\n", argv[1]);
    
    infile=fopen(argv[1], "r");
    if (infile == NULL)
    {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(1);
    }
    
    int layer=0;
    while (fgets(layer_buffer, sizeof(layer_buffer), infile))
    {
        int len = strlen(layer_buffer);
        if (len != HEIGHT * WIDTH)
        {
            continue;
        }

        for (int i=0; i<HEIGHT; i++)
        {
            for (int j=0; j<WIDTH; j++)
            {
                image[layer][i][j]=layer_buffer[i*WIDTH+j];
            }
        }
        
        layer++;
    }
    
    fclose(infile);
    
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            for (int k=0; k<layer; k++)
            {
                if (image[k][i][j] != '2')
                {
                    final_image[i][j]=image[k][i][j];
                    break;
                }
            }
        }
    }
            
    for (int i=0; i<HEIGHT; i++)
    {
        for (int j=0; j<WIDTH; j++)
        {
            printf("%c", final_image[i][j]!='0' ? '*' : ' ');
        }
        printf("\n");
    }
    
    return 0;
}
