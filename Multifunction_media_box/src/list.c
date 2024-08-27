//
// Created by 陈宇轩 on 2024/8/23.
//

#include "list.h"
#include<stdio.h>
#include <dirent.h>
#include<string.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>





Head * read_pic_from_dir(char *pathname)
{
     int n=0;
    DIR *dir = opendir(pathname);
    if(dir ==NULL)
    {
        perror("open 1 error");
        return NULL;
    }

    char buf[1024];
    struct dirent* dir_p = NULL ; //目录项指针
    Head *head=calloc(1,sizeof(*head));

    while(  dir_p = readdir(dir)  )
    {

        if (strcmp(dir_p->d_name,"." )==0|| strcmp(dir_p->d_name,".." )==0 )
        {
            continue;
        }
        struct stat st ; //保存文件的属性
        char f[256];
        sprintf(f,"%s/%s",pathname,dir_p->d_name);
        lstat(f, &st);
        if(S_ISDIR(st.st_mode))
        {
            continue;
        }
        if(head->first==NULL)//第一次进入链表
        {
            pic *p=calloc(1,sizeof (*p));
            sprintf(buf,"%s/%s",pathname,dir_p->d_name);
            sprintf(p->small_pic_name,"%s/small_pic/small_%s",pathname,dir_p->d_name);
            strcpy(p->pic_name,buf);
            p->num=n++;
            head->first=p;
            head->last=p;
            p->pre=p;
            p->next=p;
        }
            //尾插法
        else
        {
            pic *tem=calloc(1,sizeof(*tem));
            sprintf(buf,"%s/%s",pathname,dir_p->d_name);
            sprintf(tem->small_pic_name,"%s/small_pic/small_%s",pathname,dir_p->d_name);
            strcpy(tem->pic_name,buf);
            tem->num=n++;
            head->last->next=tem;
            tem->pre=head->last;
            tem->next=head->first;
            head->first->pre=tem;
            head->last=tem;
        }
    }
    return head;
}

