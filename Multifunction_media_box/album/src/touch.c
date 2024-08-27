//
// Created by 陈宇轩 on 2024/8/14.
//
#include "touch.h"
#include<stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<linux/input.h>
#include <unistd.h>
#include"Lcd.h"
#include"Bmp.h"
struct point Get_Point(void)
{
    point p;
    p.x=-1;
    p.y=-1;
    int fd_ts=open(TS_PATH,O_RDWR);
    if(fd_ts==-1)
    {
        perror("触摸屏设备文件打开失败");
    }

    struct input_event ts;
    int ret;
    while(1)
    {
        ret= read(fd_ts,&ts,sizeof(ts));

        if(ret != sizeof(ts))
        {
            continue;
        }
        if(ts.type == EV_ABS && ts.code == ABS_X)//接收x坐标
        {

            p.x = ts.value*800/1024;
        }
        if(ts.type == EV_ABS && ts.code == ABS_Y)//接收触点y坐标
        {

            p.y = ts.value*480/600;
        }

        if(p.x>0 && p.y>0)
            break;
    }
    close(fd_ts);
    return p;
}
int Get_Direction(void)
{
    int x0=-1,y0=-1;
    int x1,y1;
    //打开触摸屏文件
    int fd_TS=open(TS_PATH,O_RDWR);
    if(fd_TS == -1)
    {
        perror("获取触摸屏方向时 触摸屏文件打开失败");
        return -1;
    }
    //获取触摸方向
    struct input_event tc;
    while(1)
    {
        int r=read(fd_TS,&tc,sizeof(tc));
        if(r != sizeof(tc))
        {
            continue;
        }
        //获取x坐标
        if(tc.type == EV_ABS && tc.code == ABS_X)
        {
            if(x0<0)
            {
                x0=tc.value*800/1024;
            }
            else
                x1=tc.value*800/1024;
        }

        //获取y坐标
        if(tc.type == EV_ABS && tc.code == ABS_Y)
        {
            if(y0<0)
            {
                y0=tc.value*480/600;
            }
            else
                y1=tc.value*480/600;
        }
//        手指弹起事件
        if((tc.type == EV_KEY && tc.code == BTN_TOUCH && tc.value == 0\
        ||tc.type == EV_ABS && tc.code == ABS_PRESSURE && tc.value == 0))
        {
            break;
//            手指弹起停止获取;
        }
    }
    //左右滑动
    if(abs(x1-x0)>abs(y1-y0))
    {
        if(x1-x0>0)
        {
            //右滑动
            return 2;
        }
        else
        {
            //左滑动
            return 1;
        }
    }
//    上下滑动
    else
    {
        if(y1-y0<0)
        {
            //上滑动
            return 3;
        }
        else
        {
            return 4;
        }
    }
    close(fd_TS);
}
