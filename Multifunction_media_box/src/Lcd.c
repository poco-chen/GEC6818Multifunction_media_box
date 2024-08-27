//
// Created by 陈宇轩 on 2024/8/13.
//
#include "Lcd.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include <unistd.h>

int *Lcd_p=NULL;
int fd=-1;

void Lcd_Init(void)
{
    fd=open(LCD_PATH,O_RDWR);//打开设备文件
    if(fd==-1)
    {
        perror("打开设备文件出错");
    }

    Lcd_p=mmap(NULL,800*480*4,PROT_WRITE |PROT_READ,MAP_SHARED,fd,0);//映射设备文件
}

void Draw_Point(int x,int y,int color)
{
    if(x<800&&x>=0 && y>=0&&y<480)
    {
        *(Lcd_p+800*y+x)=color;
    }
}

void Draw_React(int x,int y,int len,int weight,int color)
{
    int i,j;
    for(i=x;i<x+len;i++)
    {
        for(j=y;j<y+weight;j++)
        {
            Draw_Point(i,j,color);
        }
    }
}

void Lcd_ReInit(void)
{
    close(fd);
    munmap(Lcd_p,800*480*4);
}