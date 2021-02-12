
OBJS = file1.o file2.o
CC = cc
CFLAGS = -Wall -O -g
TARGET = helloworld

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o helloworld

file1.o : file1.c file2.c
	$(CC) $(CFLAGS) -c file1.c -o file1.o
	
file2.o : file2.c file2.h
	$(CC) $(CFLAGS) -c file2.c -o file2.o
	
clean:
	@$(RM) -rf *.o helloworld


#helloworld : file1.o file2.o
#	cc file1.o file2.o -o helloworld
	
#file1.o : file1.c file2.c
#	cc -c file1.c -o file1.o
	
#file2.o : file2.c file2.h
#	cc -c file2.c -o file2.o
	
#clean:
#	@rm -rf *.o helloworld