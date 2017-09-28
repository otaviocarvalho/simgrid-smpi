#include <stdio.h>
#include <stdlib.h>
#include "write_bmp.h"

/* write_bmp_header():
 *
 *   In:
 *      f: A file open for writing ('w')
 *      (width, height): image dimensions
 *
 *   Return:
 *      0 on success, -1 on failure
 *
 */
int write_bmp_header(FILE *f, int width, int height) {

  unsigned int row_size_in_bytes = width * 3 +
	  ((width * 3) % 4 == 0 ? 0 : (4 - (width * 3) % 4));

  // Define all fields in the bmp header
  char id[2] = "BM";
  unsigned int filesize = 54 + (int)(row_size_in_bytes * height * sizeof(char));
  short reserved[2] = {0,0};
  unsigned int offset = 54;

  unsigned int size = 40;
  unsigned short planes = 1;
  unsigned short bits = 24;
  unsigned int compression = 0;
  unsigned int image_size = width * height * 3 * sizeof(char);
  int x_res = 0;
  int y_res = 0;
  unsigned int ncolors = 0;
  unsigned int importantcolors = 0;

  // Write the bytes to the file, keeping track of the
  // number of written "objects"
  size_t ret = 0;
  ret += fwrite(id, sizeof(char), 2, f);
  ret += fwrite(&filesize, sizeof(int), 1, f);
  ret += fwrite(reserved, sizeof(short), 2, f);
  ret += fwrite(&offset, sizeof(int), 1, f);
  ret += fwrite(&size, sizeof(int), 1, f);
  ret += fwrite(&width, sizeof(int), 1, f);
  ret += fwrite(&height, sizeof(int), 1, f);
  ret += fwrite(&planes, sizeof(short), 1, f);
  ret += fwrite(&bits, sizeof(short), 1, f);
  ret += fwrite(&compression, sizeof(int), 1, f);
  ret += fwrite(&image_size, sizeof(int), 1, f);
  ret += fwrite(&x_res, sizeof(int), 1, f);
  ret += fwrite(&y_res, sizeof(int), 1, f);
  ret += fwrite(&ncolors, sizeof(int), 1, f);
  ret += fwrite(&importantcolors, sizeof(int), 1, f);

  // Success means that we wrote 17 "objects" successfully
  return (ret != 17);
}

/* write_bmp_body():
 *
 *   In:
 *      f: A file open for writing ('w')
 *      image_rgb: RGB image content for writing
 *      (width, height): image dimensions
 *
 *   Return:
 *      0 on success, -1 on failure
 *
 */
int write_bmp_body(FILE *f, unsigned char *image_rgb, int width, int height) {
    size_t ret = 0;
    int i,j = 0;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            ret += fwrite(&image_rgb[i * width + j], sizeof(unsigned char), 3, f);
        }
    }

    return (ret != width * height * 3);
}
