CC = mpicc -lm
/*CC = ~/simgrid/SimGrid-3.13/bin/smpicc -lm*/
CFLAGS = -Wall -Werror -Wmissing-prototypes
OBJS = julia_set.o julia_pixel.o write_bmp.o

all: julia_set

julia_set: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o julia_set -lm

julia_set.o:
	$(CC) $(CFLAGS) -c julia_set.c

julia_pixel.o:
	$(CC) $(CFLAGS) -c julia_pixel.c

write_bmp.o:
	$(CC) $(CFLAGS) -c write_bmp.c

clean:
	rm -f *~ *.o *.bmp julia_set
