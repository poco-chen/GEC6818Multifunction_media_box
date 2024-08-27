//
// Created by 陈宇轩 on 2024/8/14.
//

#include "Bmp.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include"Lcd.h"
#include<string.h>

static BMP Get_info(const char * bmp_name)
{
    //1.打开图片文件
    int fd_bmp;
    fd_bmp = open(bmp_name, O_RDWR);
    if(fd_bmp == -1)
    {
        perror("打开bmp文件错误");
    }
    //2.读取图片文件内容
    BMP info;
    //读取位图宽度
    unsigned char buf[4];
    lseek(fd_bmp , 0x12, SEEK_SET);
    int r = read(fd_bmp, buf, 4);
    if(r == -1)
    {
        perror("读取位图宽度失败");
    }
    info.width = (buf[3]<<24)|(buf[2]<<16)|(buf[1]<<8)|(buf[0]<<0);

    //读取位图高度
    lseek(fd_bmp , 0x16, SEEK_SET);
    r = read(fd_bmp, buf, 4);
    if(r == -1)
    {
        perror("读取位图高度失败");
    }
    info.height = (buf[3]<<24)|(buf[2]<<16)|(buf[1]<<8)|(buf[0]<<0);

    //读取位图色深
    lseek(fd_bmp , 0x1C, SEEK_SET);
    r = read(fd_bmp, buf, 2);
    if(r == -1)
    {
        perror("读取位图色深失败");
    }
    info.depth = (buf[1]<<8)|(buf[0]<<0);

//    printf("w = %d, h = %d, d = %d\n", info.width, info.height, info.depth);

    //3.关闭图片文件
    close(fd_bmp);
    return info;
}


void BMP_Display(const char * bmp_name, int x0 , int y0)
{

    //1.获取图片文件的信息(宽度、高度、色深)
    BMP info = Get_info(bmp_name);

    int line = abs(info.width) * info.depth/8 ;
    int laizi = 0;
    if(line % 4)
    {
        laizi = 4 - line%4;
    }
    //一行的总字节数: 一行实际的字节数(line) + 赖子(laizi)
    //实际大小
    int size = (line + laizi) * abs(info.height);

    //3. 开辟像素数组大小的内存空间，读取像素数组的内容
    unsigned char * p = malloc(size);

    //将光标偏移到像素数组的位置
    int fd_bmp = open(bmp_name, O_RDWR);
    if(fd_bmp == -1)
    {
        perror("显示bmp文件时打开bmp文件失败");
    }
    lseek(fd_bmp, 54 , SEEK_SET );
    int ret = read(fd_bmp, p , size);
    if(ret == -1)
    {
        perror("读取bmp文件信息错误");
    }

    //4.解析每一个像素点的颜色值，并且在对应的坐标位置画点
    unsigned char a, r, g ,b;
    int color;
    int i, j;
    int k = 0;
    for(j = 0;  j < abs(info.height) ; j++)
    {
        for(i = 0; i < abs(info.width); i++)
        {
            //b = *(p+k);k++;
            b = p[k++];
            g = p[k++];
            r = p[k++];
            if(info.depth == 32)
                a = p[k++];
            else
                a = 0;
            color = a<<24 | r<<16 | g<<8 | b;
            Draw_Point(
                    (info.width > 0) ? (x0 + i):(x0 + abs(info.width)-1 -i),
                    (info.height > 0)? (y0 + abs(info.height)-1 - j) : (y0 + j),
                    color);
        }
        //过滤掉 赖子
        k += laizi;
    }

    //5. 释放空间，关闭文件
    free(p);
    close(fd_bmp);
}




