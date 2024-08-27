#include "bmp_show.h"

// 指定位置显示 指定大小图片
int bmp_show_mix(int x0, int y0, int width, int height, char *name)
{

	int fd_bmp = open(name, O_RDONLY);
	if (fd_bmp == -1)
	{
		printf("can not open %s\n", name);
		return -1;
	}

	struct stat pst; // 文件状态结构体
	if (fstat(fd_bmp, &pst) == -1)
	{
		perror("Cannot stat BMP file");
		close(fd_bmp);
		return -1;
	}

	fstat(fd_bmp, &pst); // 获取文件状态信息，比如文件大小，存入pst中
	// printf("bmp size:%d\n",pst.st_size);

	char *buf;						   // 定义指针用于存放bmp文件内容
	buf = (char *)malloc(pst.st_size); // 为bmp文件分配内存
	if (!buf)
	{
		perror("Malloc failed");
		close(fd_bmp);
		return -1;
	}

	if (lseek(fd_bmp, 54, SEEK_SET) == -1)
	{ // 跳过文件头、
		perror("Lseek failed");
		close(fd_bmp);
		free(buf);
		return -1;
	}

	read(fd_bmp, buf, pst.st_size - 54); // 读取像素到缓冲区中

	int fd_lcd = open("/dev/fb0", O_RDWR); // 打开设备文件
	if (fd_bmp == -1)
	{
		printf("can not open lcd\n");
		close(fd_bmp);
		free(buf);
		return -1;
	}

	char *p;																			  // 定义指针用于内存映射framebuffer
	p = (char *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0); // 内存映射framebuffer

	// return 0;

	int i, j;
	int lcd_offset, bmp_offset; // 定义偏移变量

	// 复制bmp图片到framebuffer指定位置
	for (j = 0; j < 480 - y0 && j < height; j++)
	{
		for (i = 0; i < 800 - x0 && i < width; i++)
		{

			lcd_offset = ((j + y0) * 800 + i + x0) * 4;		 // 计算framebuffer中的偏移量
			bmp_offset = ((height - 1 - j) * width + i) * 3; // 计算bmp数据中的偏移量
			memcpy(p + lcd_offset, buf + bmp_offset, 3);	 // 将bmp数据复制到framebuffer
		}
	}

	munmap(p, 800 * 480 * 4); // 关闭内存映射
	close(fd_lcd);
	close(fd_bmp);
	free(buf);

	return 0;
}

// 显示背景图片的指定区域
int bmp_show_self(int x0, int y0, int width, int height, char *name)
{

	int fd_bmp = open(name, O_RDONLY);
	if (fd_bmp == -1)
	{
		printf("can not open %s\n", name);
		return -1;
	}

	struct stat pst;

	fstat(fd_bmp, &pst);
	// printf("bmp size:%d\n",pst.st_size);

	char *buf;
	buf = (char *)malloc(pst.st_size);

	lseek(fd_bmp, 54, SEEK_SET);
	read(fd_bmp, buf, pst.st_size - 54);

	int fd_lcd = open("/dev/fb0", O_RDWR);
	if (fd_bmp == -1)
	{
		printf("can not open lcd\n");
		close(fd_bmp);
		free(buf);
		return -1;
	}

	char *p;
	p = (char *)mmap(NULL, 800 * 480 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, fd_lcd, 0);

	// return 0;

	int i, j;
	int lcd_offset, bmp_offset;

	for (j = 0; j < 480 - y0 && j < height; j++)
	{
		for (i = 0; i < 800 - x0 && i < width; i++)
		{

			lcd_offset = ((j + y0) * 800 + i + x0) * 4;

			bmp_offset = ((479 - y0 - j) * 800 + i + x0) * 3;

			memcpy(p + lcd_offset, buf + bmp_offset, 3);
		}
	}

	close(fd_lcd);
	close(fd_bmp);
	free(buf);
	munmap(p, 800 * 480 * 4);

	return 0;
}
