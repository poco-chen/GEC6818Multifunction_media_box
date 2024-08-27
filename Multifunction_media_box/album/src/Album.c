//
// Created by 陈宇轩 on 2024/8/24.
//

#include"list.h"
#include "Album.h"
#include"Bmp.h"
#include"touch.h"
#include<stdio.h>
#include"Lcd.h"
#include<unistd.h>
#include<pthread.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>



pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t tid ;

void show_small_pic();
void *capture_bottom(void *arg);
void *play_pic(void *arg);
void *Is_exit(void *arg);
void *random_play(void *arg);
void *enlarging_pic(void *arg);
void *Display_pre_next_pic(void *arg);
void *Is_delete_pic(void *p);



Head * H;
int press=1;
int page=0;
int page_max;
int bottom=1;//主界面
int quit=0;
int home=1;
int delete=0;
point point1;
//pic *p;



int main()
{

    Lcd_Init();
    H=read_pic_from_dir("/home/cyx/album");
    page_max=(H->num/16)+1;
    P:
    while(1)
    {
        if(press==1&&bottom==1||home==1)//上下页
        {
            show_small_pic();
            press=0;
            home=0;
            pthread_create(&tid,NULL,capture_bottom,NULL);
//            puts("---------------------");
            goto P;
        }
        else if(press==1&&bottom==2)
        {
            pthread_t tid;
            pthread_create(&tid,NULL, play_pic,NULL);
            press=0;
            bottom=1;
            goto P;
        }
        else if(press==1&&bottom==3)
        {
//            随机播放
            pthread_t tid;
            pthread_create(&tid,NULL, random_play,NULL);
            press=0;
            bottom=1;
            goto P;
        }
        else if(press==1&&bottom==4)
        {
//            放大照片
            pthread_t tid;
            pthread_create(&tid,NULL, enlarging_pic,NULL);
            press=0;
            bottom=1;
            goto P;
        }
    }
}

void *capture_bottom(void *arg)
{
//    pthread_detach(pthread_self());
    while(1)
    {
         point1 =Get_Point();
        if(50<point1.x&&point1.x<130&&400<point1.y&&point1.y<480)
        {
            puts("pre page");
            if(0<page)
            {
                press=1;
                page-=1;
                bottom=1;
                break;
            }
        }
        else if(250<point1.x&&point1.x<330&&400<point1.y&&point1.y<480)
        {
            puts("play");
            press=1;
            bottom=2;
            break;
        }
        else if(450<point1.x&&point1.x<530&&400<point1.y&&point1.y<480)
        {
            puts("random play");
            press=1;
            bottom=3;
            break;
        }
        else if(650<point1.x&&point1.x<730&&400<point1.y&&point1.y<480)
        {
            puts("next page");
            if(page<page_max)
            {
                press=1;
                page+=1;
                bottom=1;
                break;
            }
        }
        else if(0<point1.x&&point1.x<800&&0<point1.y&&point1.y<400)
        {
            //点到照片放大
            puts("放大照片");
            press=1;
            bottom=4;
            break;
        }
        else
        {
            continue;
        }
    }
}


void show_small_pic()
{

//    printf("show_pic\n");
    BMP_Display("/home/cyx/buttom/black.bmp",0,0);
    BMP_Display("/home/cyx/buttom/up.bmp",50,400);
    BMP_Display("/home/cyx/buttom/play.bmp",250,400);
    BMP_Display("/home/cyx/buttom/random.bmp",450,400);
    BMP_Display("/home/cyx/buttom/down.bmp",650,400);
    int flag=0,k=page*16;
    pic *head=H->first;
    printf("H->num==%d\n",H->num);
    while(k--)
    {
        head=head->next;
    }
    int i=0,j=0;
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            BMP_Display(head->small_pic_name,(j*200),(i*100));
            head=head->next;
            if(head->next==H->first)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            break;
        }
    }
}

void *play_pic(void *arg)
{
    pic *p=H->first;
    pthread_t t;
    pthread_create(&t,NULL, Is_exit,NULL);
    while(p)
    {
        BMP_Display(p->pic_name,0,0);
        sleep(1);
        p=p->next;
        if(quit==1)
        {
            quit=0;
            break;
        }
    }
}

void *Is_exit(void *arg)
{
    while(1)
    {
        int D=Get_Direction();
        if(D==3)
        {
            quit=1;
            press=1;
            bottom=1;
            break;
        }
    }
    return NULL;
}

void *random_play(void *arg)
{
    pic *p=H->first;
    pthread_t t;
    pthread_create(&t,NULL, Is_exit,NULL);
    while(p)
    {
        pic *p=H->first;
        srand(time(NULL));
        int n=rand()%(H->num)+1;
        while(n)
        {
            p=p->next;
            n--;
        }
        BMP_Display(p->pic_name,0,0);
        sleep(1);
        if(quit==1)
        {
            quit=0;
            break;
        }
    }
}

void *enlarging_pic(void *arg)
{

    int num=(point1.y/100)*4 + ( (point1.x/200)+1 )-1;
    pic *p=H->first;
    int page_n=page*16;
    while(page_n)
    {
        p=p->next;
        page_n--;
    }
    while(num)
    {
        p=p->next;
        num--;
    }
    BMP_Display(p->pic_name,0,0);
//    pthread_t t2,t1;
    pthread_t t2,t1;
//    pthread_create(&t1,NULL, Is_exit,NULL);
    pthread_create(&t2,NULL, Display_pre_next_pic,(void *)p);
    pthread_create(&t1,NULL, Is_delete_pic,(void *)p);
    while(1)
    {
        if(quit==1)
        {
            printf("我要退出啦\n");
            quit=0;
            break;
        }
    }
}

void *Display_pre_next_pic(void *arg)
{
    pic *p=(pic *)arg;
    int n=-1;
    while(1)
    {

        if(n>10)
        {
            n=0;
        }
        int D=Get_Direction();
        if(D==1)
        {
            p=p->next;
            BMP_Display(p->pic_name,0,0);
            puts("--------------左滑------------\n");
        }
        else if(D==2)
        {
            p=p->pre;
            BMP_Display(p->pic_name,0,0);
            puts("--------------右滑------------\n");
        }
        else if(D==3)
        {
            quit=1;
            press=1;
            bottom=1;
            puts("--------------上滑------------\n");
            break;
        }
        else if(D==4&&n!=-1)
        {
            puts("--------------下滑------------\n");
            delete=1;
        }
        n++;
    }
}
void *Is_delete_pic(void *arg)
{
    int flag=0;
    pic *p=(pic *)arg;
    while(1)
    {

        if(delete==1)
        {
            if(H->num==0)
            {
                puts("链表为空不能删除！！！！！！！！！！");
//            home=1;
//            quit=1;
//            press=1;
                delete=0;
                break;
            }
            if(H->num==1)
            {
                H->first=H->last=NULL;
                free(p);
//            quit=1;
//            press=1;
                delete=0;
                break;
            }
            else
            {
                if (p == H->first)//删除第一个元素
                {
                    pic *q = p->next;
                    q->pre = H->last;
                    H->first = q;
                    H->last->next = q;
                    free(p);
//                quit=1;
//                press=1;
                    H->num--;
                    delete=0;
                    break;
                }
                else if (p == H->last)//删除最后一个元素
                {
                    pic *q = p->pre;
                    q->next = H->first;
                    H->last = q;
                    H->first->pre = q;
                    free(p);
                    H->num--;
//                quit=1;
//                press=1;
                    delete=0;
                    break;
                }
                else//删除中间节点元素
                {
                    p->pre->next = p->next;
                    p->next->pre = p->pre;
                    free(p);
                    H->num--;
//                quit=1;
//                press=1;
                    delete=0;
                    break;
                }
            }
        }
    }
}