//
// Created by 陈宇轩 on 2024/8/23.
//

#include "unlock.h"
#include<stdio.h>
#include<string.h>
#include"touch.h"
#include <fcntl.h>
#include <unistd.h>

extern int urs1;
extern int urs2;
void get_password(char *Buf)
{
    int num=0;//输入密码个数
    while(1)
    {
        point p=Get_Point();
        if(200<p.x&&p.x<270&&5<p.y&&p.y<95)
        {
            Buf[num]='1';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(365<p.x&&p.x<430&&5<p.y&&p.y<95)
        {
            Buf[num]='2';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(510<p.x&&p.x<560&&5<p.y&&p.y<95)
        {
            Buf[num]='3';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(210<p.x&&p.x<272&&115<p.y&&p.y<210)
        {
            Buf[num]='4';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(375<p.x&&p.x<430&&120<p.y&&p.y<210)
        {
            Buf[num]='5';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(510<p.x&&p.x<570&&120<p.y&&p.y<210)
        {
            Buf[num]='6';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(215<p.x&&p.x<273&&240<p.y&&p.y<330)
        {
            Buf[num]='7';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(370<p.x&&p.x<430&&240<p.y&&p.y<330)
        {
            Buf[num]='8';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(510<p.x&&p.x<570&&240<p.y&&p.y<330)
        {
            Buf[num]='9';
            printf("%c\n",Buf[num]);
            num++;
        }
        else if(365<p.x&&p.x<435&&350<p.y&&p.y<460)
        {
            Buf[num]='0';
            printf("%c\n",Buf[num]);
            num++;
        }
        else
        {
            continue;
        }
        if(num==6)
        {
            break;
        }
    }
}

void unlock(void)
{
    FILE *file_d;
    if(urs1==1)
        file_d=fopen("/home/cyx/lock/lock.txt", "r+");
    if(urs2==1)
        file_d=fopen("/home/cyx/lock/lock1.txt", "r+");
    char buf[256]={0};
    char  buf1[256]={0};//存放密码
    get_password(buf);
    size_t r=fread(buf1, 1, 256, file_d);
    if(r==-1)
    {
        perror("open unlock file error");
    }
    printf("%s\n",buf);
    printf("%s\n",buf1);
    if(strcmp(buf,buf1)==0)
    {
        printf("unlock success!!!\n");
        into=1;
    }
    else
    {
        printf("unlock failed!!!\n");
        error_time++;
    }
    fclose(file_d);
}
void warning()
{
    int fd = open("/sys/kernel/gec_ctrl/beep",O_RDWR);//打开所有的LED文件
    if(fd == -1)
    {
        printf("sorry , open beep failed\n");
        return ;
    }
    int k = 1;
    write(fd,&k,4); //写入1
    sleep(3);
    k=0;
    write(fd,&k,4); //写入0
    close(fd);
}
