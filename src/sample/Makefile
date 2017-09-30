CC = ~/simgrid/SimGrid-3.13/bin/smpicc
CFLAGS = -Wall -Werror -Wmissing-prototypes
OBJS = roundtrip.o

all: roundtrip

roundtrip: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o roundtrip

clean:
	rm -f *~ *.o roundtrip
