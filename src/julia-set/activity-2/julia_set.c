#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <sys/time.h>
#include "julia_pixel.h"
#include "write_bmp.h"

int main(int argc, char *argv[]) {

    FILE *fp;
    const float TINT_BIAS = 1.0;

    int i, j = 0;
    int n = 0;
    unsigned char *image_rgb = NULL;
    struct timeval start, end;
    int num_processes, rank;
    MPI_Status status;
    int token = 0;
    int tag = 171;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_processes);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Validate input
    if (argc != 2) {
        printf("Error: julia_set expects a single value as its input parameter.\n");
        return -1;
    }

    // Initialize variables with input and execute MPI slicing logic
    n = atoi(argv[1]);
    int slice_size = n / num_processes;
    int slice_start = (rank % n) * slice_size;
    int slice_end = slice_start + slice_size - 1;
    image_rgb = malloc(n * (2 * n) * 3 * sizeof(char));
    printf("[Process %d out of %d]: I should compute pixel rows %d to %d, for a total of %d rows\n",
            rank, num_processes, slice_start, slice_end, slice_size);

    // Compute pixels for each slice
    for (i = slice_start; i < slice_end; i++) {
        for (j=0; j < 2*n; j++) {
            compute_julia_pixel(i, j, n, 2*n, TINT_BIAS, &image_rgb[i * n + j]);
        }
    }

    gettimeofday(&start, NULL);

    // Save to output file
    if (rank == 0) {

        fp = fopen("./julia_set.bmp","w+");
        int write_result = 0;
        if (fp != NULL) {
            write_result += write_bmp_header(fp, n, 2*n);
            write_result += write_bmp_body_slice(fp, image_rgb, slice_start, slice_end, n, 2*n);

            if (write_result != 0) {
                fprintf(stderr, "There was an error when writing to output BMP file.\n");
            }
        }

        fclose(fp);

        // Send message to the next process
        MPI_Send(&token, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);

    }
    else {
        // Receive message signalling to start processing
        MPI_Recv(&token, 1, MPI_INT, rank-1, tag, MPI_COMM_WORLD, &status);

        fp = fopen("./julia_set.bmp","a+");
        int write_result = 0;
        if (fp != NULL) {
            write_result += write_bmp_body_slice(fp, image_rgb, slice_start, slice_end, n, 2*n);

            if (write_result != 0) {
                fprintf(stderr, "There was an error when writing to output BMP file.\n");
            }
        }

        fclose(fp);

        if (rank != num_processes-1) {
            // Send message to the next process
            MPI_Send(&token, 1, MPI_INT, rank + 1, tag, MPI_COMM_WORLD);
        }

    }

    gettimeofday(&end, NULL);

    printf("total rank %d time: %f\n", rank, (end.tv_sec * 1000000.0 + end.tv_usec -
            start.tv_sec * 1000000.0 + start.tv_usec) / 1000000.0);

    MPI_Finalize();

    free(image_rgb);

    return 0;
}
