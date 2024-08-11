.PHONY: all clean
HEADERS = xdp.h
SRCS = 	 lex.c ut.c

CFLAGS = -Wall -g

OBJS = $(SRCS:.c=.o)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	$(CC) -o xdp $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) xdp