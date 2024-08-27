# 定义编译器
CC=arm-linux-gcc

# 定义编译选项，这里包含了 -pthread 选项
CFLAGS=-Wall -Wextra -I. -pthread

# 定义链接选项
LDFLAGS=

# 定义目标名称
TARGET=tetris2

# 指定所有相关的 .c 文件
SRCS=main.c bmp_show.c list.c move.c touch.c interface.c game_control.c 

# 默认目标是编译程序
all: $(TARGET)

# 直接链接 .c 文件来生成可执行文件
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# 清理编译生成的文件
clean:
	rm -f $(TARGET)

# 声明伪目标
.PHONY: all clean
