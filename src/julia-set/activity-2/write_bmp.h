int write_bmp_header(FILE *, int, int);
int write_bmp_body(FILE *f, unsigned char *, int, int);
int write_bmp_body_slice(FILE *f, unsigned char *, int, int, int, int);
