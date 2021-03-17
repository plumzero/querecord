文件I/O函数
	Linux的基本文件操作函数包括：open、read、write、iseek和close等，这些函数也被称为文件I/O函数，也被称为"不带缓冲的I/O"。
	文件I/O函数都是针对文件描述符进行操作。但是由于其需要多次反复调用对应的系统调用，效率很低。
流I/O函数
	流I/O函数的操作则是围绕流（Stream）进行的，当使用流I/O库打开或创建一个文件时，可以使一个流与一个文件相结合，接下来的操作过程就与基本文件描述符
	的I/O操作过程十分相似：对流进行读写，定位操作等，最后关闭流。
	不带缓冲的文件I/O操作也不是直接对文件进行的，只不过用户层没有缓存区，所以被称为不带缓冲的I/O，但对于Linux内核来说，还是进行了缓冲。当用户调用不
	带缓冲的I/O函数写数据到文件的时候（即，对磁盘存储区进行读写），linux内核会先将数据写入到内核中所设的缓冲储存区。假设该缓冲储存区的长度是50个字
	节，调用write函数进行写操作时，如果每次写入长度为10个字节，则需要调用5次write函数，而在这个过程中数据还是在内核的缓冲区中，并没有写入到磁盘。当
	50个字节已经写满的时候才进行实际的I/O操作，把数据写入到磁盘上。
	带缓冲的I/O是在用户层建立了另一个缓存区（即，流缓冲区）。假设流缓存的长度同样也是50字节，当调用对应的写入库函数时会将数据写入到这个流缓存区里面，
	然后一次性进行内核缓存区，此时再使用系统调用将数据写入到文件（实质是磁盘空间）上，从而减少了系统调用。
	不带缓冲：数据->内核缓存区->磁盘
	带缓冲：数据->流缓存区->内核缓存区->磁盘
	流操作函数的对象不是文件描述符，而是一个流缓冲区。当打开一个流时，返回一个指向FILE对象的指针。该对象通常是一个结构体，它包含了为管理该流需要的所
	有信息，包括用于实际I/O的文件描述符、指向流缓存的指针、缓存的长度、当前在缓存的字符数、出错标志等。
	为了引用一个流，需将FILE指针作为参数传递给相应I/O函数即可。
流的打开和关闭
	打开流的过程实际上是建立一个缓冲区，并且将这个缓冲区和对应的文件相关联（自动关联）的过程。linux提供了fopen系列函数来完成相应的工作。
	当完成对一个流的操作之后，需要调用相应的函数将其关闭，linux提供了fclose函数用于该操作。当调用fclose函数的时候，将会把流中的数据写入对应文件中，并
	且清除整个缓冲区。如果应用代码不调用该函数，在调用exit函数返回的时候，系统也会自动调用fclose函数完成对应的操作。

对流的读写操作可以按照操作的缓冲区大小分为3种：
	字符读写：每次读写一个字符
	行读写：当遇到换行符的时候，则将流中换行符之前的内容送到缓冲区中，即每次读写一行
	块读写：以块为单位进行读写
字符读写 <stdio.h>
	字符读
		如果调用成功则返回即将读取的下一个字符，如果已经到达文件结束或者出错则返回EOF。
		int fgetc(FILE * stream);	//不能被实现为宏，调用函数通常所需的时间长于调用宏
		int getc(FILE * stream);	//可以被实现为宏
		int getchar(void);			//相当于调用getc(stdin)
	字符写
		调用函数成功则返回输出字符c，若出错则为EOF
		int fputc(int c, FILE * stream);	//不能被实现为宏
		int putc(int c, FILE * stream);		//可以被实现为宏
		int putchar(int c);					//相当于调用putc(c, stdout)
行读写 <stdio.h>
	行读
		从流stream中读出一行数据，送到由s指定的大小为size的缓冲区中；如果操作成功返回缓冲区，如果已到达文件尾或出错则返回NULL。
		char * fgets(char * s, int size, FILE * stream);
	行写
		如果调用成功则返回一个非负值，如果出错则返回EOF。
		int fputs(const char * s, FILE * stream);
二进制读写 <stdio.h>
	二进制读
		fread用于执行直接输出操作，ptr是指向读取数据的缓冲区指针，size是每次读取对象的大小，nmemb是要读取的对象的个数，fp是指向要读取的流的FILE结构指针
		返回值是读的对象数，如果出错或到达文件尾，则此返回值可以少于nmemb。在这种情况，应调用ferror或feof判断究竟是哪一种情况。
		size_t fread(void * ptr, size_t size, size_t nmemb, FILE * stream);
	二进制写
		fwrite用于执行直接输入操作，ptr是指向存放要输入数据的缓冲区的指针，size是每次写入对象的大小，nmemb是要写入的对象的个数，fp是指向要写入的流的FILE结构指针
		返回值为写入的对象数，如果返回值少于所要求的nmemb，则出错。
		size_t fwrite(const void * ptr, size_t size, size_t nmemb, FILE * stream);
	
流的定位 <stdio.h>
	适用于二进制文件和文本文件
		用于修改stream所指的文件偏移量，参数whence指明参数offset的偏移起点。成功则返回0，否则返回一个非0值。
		int fseek(FILE * stream, long offset, int whence);
		如果调用成功，返回stream指定流的当前文件的位置，它是从文件开始的字节数；否则失败则返回-1。
		long ftell(FILE * stream);
		用于将偏移量设定到流的起始部分，等价于fseek(fp, 0L, SEEK_SET)。
		void rewind(FILE * stream);
	适用于文本文件
		int fseeko(FILE * stream, off_t offset, int whence);
		off_t ftello(FILE * stream);

流的格式化输出和输入
	格式化输出
		用于将格式化的数据写入到一个由stream指针指向的流。操作成功返回输出字符数，操作失败返回一个负值。
		int fprintf(FILE * stream, const char * format, ...);
		用于将格式化的数据写入到str指向的缓冲区数组，并且在末尾加上NULL。操作成功返回数组的字符，操作失败返回一个负值。
		int sprintf(char * str, const char * format, ...);
		可以使用size来指定缓冲区数组大小，超出的数据将被丢弃。操作成功返回数组的字符，操作失败返回一个负值。
		int snprintf(char * str, size_t size, const char * format, ...);
	格式化输入
		用于从一个流按照格式读取数据。调用成功返回输入项数，输入出错或者到达文件结尾返回EOF。
		int fscanf(FILE * stream, const char * format, ...);
		用于从str指定的字符缓冲区中读取数据。调用成功返回输入项数，输入出错或者到达文件结尾返回EOF。
		int sscanf(const char * str, const char * format, ...);

基于文件描述符的I/O操作使用文件描述符来标识，基于流的I/O操作使用文件指针（FILE*）来标识。
为了引用一个流，需要将FILE指针作为参数传递给每个标准I/O函数。