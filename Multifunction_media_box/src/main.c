//
// Created by 陈宇轩 on 2024/8/23.
//
#include<stdio.h>
#include"Bmp.h"
#include"touch.h"
#include"list.h"
#include"Lcd.h"
#include<unistd.h>
#include"unlock.h"
#include<pthread.h>
#include <sys/types.h>
#include <signal.h>
#include<stdlib.h>

#define home_pic_path "/home/cyx/homepic"
int into=0;
int error_time=0;
int exit_S=0;
void* capture_exit(void *arg);
int urs1=0;
int urs2=0;
int main()
{
    Lcd_Init();
    //左右滑动切换锁屏壁纸

    Head *H = read_pic_from_dir(home_pic_path);
    pic *head=H->first;
    flag:
    BMP_Display(head->pic_name,0,0);

//    ----------------锁屏界面--------------

    while(1)
    {
        int p=Get_Direction();
//        左右滑动切换图片
        if(p==1||p==2)
        {
            if(p==1)
            {
                head=head->pre;
                puts("你在左划");
                BMP_Display(head->pic_name,0,0);
            }
            else
            {
                head=head->next;
                BMP_Display(head->pic_name,0,0);
                puts("你在右划");
            }
        }

//          上滑解锁屏幕
        else if(p==3||p==4)
        {
            break;
        }
    }
    BMP_Display("/home/cyx/lock/login.bmp",0,0);
    point point1;
    login:
    point1=Get_Point();
    if(130<point1.x&&point1.x<280&&120<point1.y&&point1.y<305)
    {
        puts("---------------\n");
        urs1=1;
    }
    else if(465<point1.x&&point1.x<626&&126<point1.y&&point1.y<310)
    {
        urs2=1;
    }
    else
    {
        puts("----------++++---\n");
        goto login;
    }
//    -----------退出锁屏界面----------------------
    BMP_Display("/home/cyx/lock/lock.bmp",0,0);
    unlock();
    if(into==0)
    {
        if(error_time==5)
        {
            warning();
            return 0;
        }
        goto flag;
    }
flag2:
    BMP_Display("./interface.bmp",0,0);

    while(1)//主循环
    {
        point p = Get_Point();
//        printf("%d %d\n",p.x,p.y);
        if(90<p.x&&p.x<190&&320<p.y&&p.y<420)
        {
            //俄罗斯方块
            puts("俄罗斯方块");

            pthread_t pid =fork();
            printf("\npid = %d\n",pid);
            if(pid >0)
            { //            调用线程检测exit按钮是否被按下
                pthread_t tid;
                pthread_t *arg;
                arg =&pid;
                pthread_create(&tid,NULL,capture_exit,(void*)arg);
                pthread_join(tid,NULL);
                if(exit_S==1)
                {
                    exit_S=0;
                    goto flag2;
                }
                //              按下后全局变量exit==1 然后发送kill信号给俄罗斯方块进程
            }
            else if(pid == 0)
            {
                char *args[] = {"tetris", NULL};
                execv(args[0], args);
                perror("execv");
//                exit(EXIT_FAILURE);
            }
        }
        else if(260<p.x&&p.x<360&&320<p.y&&p.y<420)
        {
//            音视频播放器
            puts("音视频播放器");

            pthread_t pid =fork();
            printf("\npid = %d\n",pid);
            if(pid >0)
            { //            调用线程检测exit按钮是否被按下
                pthread_t tid;
                pthread_t *arg;
                arg =&pid;
                pthread_create(&tid,NULL,capture_exit,(void*)arg);
                pthread_join(tid,NULL);
                if(exit_S==1)
                {
                    exit_S=0;
                    goto flag2;
                }
                //              按下后全局变量exit==1 然后发送kill信号给俄罗斯方块进程
            }
            else if(pid == 0)
            {
                char *args[] = {"player", NULL};
                execv(args[0], args);
                perror("execv");
//                exit(EXIT_FAILURE);
            }
        }
        else if(435<p.x&&p.x<535&&320<p.y&&p.y<420)
        {
//            电子相册
            puts("电子相册");
            pthread_t pid =fork();
            printf("\npid = %d\n",pid);
            if(pid >0)
            { //            调用线程检测exit按钮是否被按下
                pthread_t tid;
                pthread_t *arg;
                arg =&pid;
                pthread_create(&tid,NULL,capture_exit,(void*)arg);
                pthread_join(tid,NULL);
                if(exit_S==1)
                {
                    exit_S=0;
                    goto flag2;
                }
                //              按下后全局变量exit==1 然后发送kill信号给俄罗斯方块进程
            }
            else if(pid == 0)
            {
                if(urs1==1)
                {
                    char *args[] = {"album_test", NULL};
                    execv(args[0], args);
                    perror("execv");
                }
                if(urs2==1)
                {
                    char *args[] = {"album_test", NULL};
                    execv(args[0], args);
                    perror("execv");
                }
//                exit(EXIT_FAILURE);
            }
        }
        else if(700<p.x&&p.x<800&&0<p.y&&p.y<100)
        {
            //关机
            puts("关机");
            BMP_Display("/home/cyx/buttom/black.bmp",0,0);
            exit(0);
        }
        else if(615<p.x&&p.x<715&&322<p.y&&p.y<422)
        {
            //修改密码
            puts("修改密码");
            char buf[256];
            BMP_Display("/home/cyx/lock/lock.bmp",0,0);
            FILE *file_d;
            if(urs1==1)
            {
                file_d=fopen("/home/cyx/lock/lock.txt", "r+");
            }
            if(urs2==1)
            {
                file_d=fopen("/home/cyx/lock/lock1.txt", "r+");
            }
            get_password(buf);
            fwrite(buf,1,256,file_d);
            fclose(file_d);
            goto flag2;
        }
    }
}

void* capture_exit(void *arg)
{
    BMP_Display("./exit.bmp",0,0);
    while(1)
    {
        point p=Get_Point();
        if(0<p.x&&p.x<40&&0<p.y&&p.y<40)
        {
            exit_S=1;
            printf("\npid = %d\n",*((int *)arg));
            kill(*((int *)arg),SIGKILL);
            break;
        }
        else
        {
            continue;
        }
    }
}