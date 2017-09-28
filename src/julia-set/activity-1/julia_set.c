#include <stdio.h>
#include <stdlib.h>
#include "julia_pixel.h"
#include "write_bmp.h"
/*#include <mpi.h>*/

FILE *fp;
const int WIDTH = 4;
const int HEIGHT = 4;
const float TINT_BIAS = 2.2;

int main(int argc, char *argv[])
{
    int i, j = 0;
    int n = 0;
    unsigned char *image_rgb = NULL;

    // Validate input
    if (argc <= 1 || argc >= 3) {
        printf("Error: julia_set expects a single value as its input parameter.\n");
        return -1;
    }

    // Initialize variables with input
    n = atoi(argv[1]);
    image_rgb = malloc(n * (2 * n) * 3 * sizeof(char));

    // Compute pixels
    for (i=0; i < n; i++) {
        for (j=0; j < 2*n; j++) {
            compute_julia_pixel(i, j, n, 2*n, TINT_BIAS, &image_rgb[i * n + j]);
            /*printf("r: %d, g: %d, b:%d\n", (int) image_rgb[i * n + j], (int) image_rgb[i * n + j + 1], (int) image_rgb[i * n + j + 2]);*/
        }
    }

    // Save output file
    fp = fopen("./julia_set.bmp","w+");
    int write_result = 0;
    if (fp != NULL) {
        write_result += write_bmp_header(fp, n, 2*n);
        write_result += write_bmp_body(fp, image_rgb, n, 2*n);

        if (write_result != 0) {
            fprintf(stderr, "There was an error when writing to output BMP file.\n");
        }
    }

    fclose(fp);
    free(image_rgb);

    return 0;
}
