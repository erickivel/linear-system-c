TARGET  = perfEG

SRCDIR = ./src/
INCDIR = ./include/

CC			= gcc
CFILES		= $(wildcard $(SRCDIR)/*.c)
CFLAGS		= -Wall -Wextra -pedantic -O3 -mavx -march=native -DLIKWID_PERFMON
LDFLAGS		= -I$(INCDIR) -I${LIKWID_INCLUDE}
LBLAGS		= -L${LIKWID_LIB} -llikwid
OBJFILES	= $(patsubst %.c, %.o, $(CFILES))

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) -o $@ $^ $(LBFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $^

clean:
	rm -f $(TARGET) $(OBJFILES)

purge: 
	rm -f $(TARGET) $(OBJFILES) *.txt *.log
