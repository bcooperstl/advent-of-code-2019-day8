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
    
    int minZeros=9999, answer, numZeros, numOnes, numTwos;
    
    memset(&layer_buffer, '\0', sizeof(layer_buffer));
    memset(&image, '\0', sizeof(image));
    
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
    
    for (int i=0; i<layer; i++)
    {
        numZeros = 0;
        numOnes = 0;
        numTwos = 0;
        for (int j=0; j<HEIGHT; j++)
        {
            for (int k=0; k<WIDTH; k++)
            {
                if (image[i][j][k] == '0')
                    numZeros++;
                if (image[i][j][k] == '1')
                    numOnes++;
                if (image[i][j][k] == '2')
                    numTwos++;
            }
        }
        if (numZeros < minZeros)
        {
            minZeros = numZeros;
            answer = numOnes * numTwos;
        }
    }
    
    printf("Answer is %d\n", answer);
    
    return 0;
}