
## 说明
- 模板如下:
  ```make
    CROSS_COMPILE ?= 
    EXTRA_CFLAGS += -Wall -Wextra -O2 -fPIC -g

    SRC = $(wildcard *.c)
    OBJECTS = $(SRC:.c=.o)
    OUTPUT = a.out

    all: $(OUTPUT)

    $(OUTPUT): $(OBJECTS)
            $(CROSS_COMPILE)gcc $(EXTRA_CFLAGS) -o $@ $^

    %.o: %.c
        $(CROSS_COMPILE)gcc $(EXTRA_CFLAGS) -MMD -o $@ -c $^
        
    -include $(OBJECTS:.o=.d)

    clean:
        $(RM) *.[od] 

    PHONY: all clean
  ```
- 该 makefile 用于将当前目录下所有的.c源文件编译为.o，最后生成可执行文件a.out 。
- 在此基础上，改变默认目标文件，可编译出.a, .so和可执行文件。
    + 静态库(依赖于.o)：ar -rc $@ $^
    + 动态库(依赖于.o)：gcc -shared $@ $^
- 也可以在上层 Makefile 中调用该子目录下的 Makefile，达到管理子目录的效果。

