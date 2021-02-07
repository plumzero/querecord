

SRCS        = *.c
OBJS        = $(SRCS:.c=.o)
LIB         = libasn1.a

CFLAGS += -g -O0 -I. -D_DEFAULT_SOURCE -fPIC -c

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) && $(AR) cr $(LIB) $(OBJS)
	
.PHONY: clean
clean:
	rm -rf $(LIB) $(OBJS)
