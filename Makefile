TARGET  = perfEG

SRCDIR = ./src/
INCDIR = ./include/

# LIKWID_HOME=/home/soft/likwid
LIKWID_HOME=/home/kivel/Downloads/likwid-5.2.2

CC			= gcc
CFILES		= $(wildcard $(SRCDIR)/*.c)
CFLAGS		= -Wall -Wextra -pedantic -std=c99 -O3 -mavx -march=native -I${LIKWID_HOME}/include -DLIKWID_PERFMON
LDFLAGS		= -I$(INCDIR)
LBLAGS		= -L${LIKWID_HOME}/lib -llikwid
OBJFILES	= $(patsubst %.c, %.o, $(CFILES))

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) -o $@ $^ $(LBFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(OBJFILES)

purge: 
	rm -f $(TARGET) $(OBJFILES) *.txt
