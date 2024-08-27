//
// Created by 陈宇轩 on 2024/8/23.
//

#ifndef MULTIFUNCTION_MEDIA_BOX_LIST_H
#define MULTIFUNCTION_MEDIA_BOX_LIST_H




typedef struct pic
{
    int num;//第几张照片
    char pic_name[256];
    char small_pic_name[256];
    struct pic * next;
    struct pic * pre;
}pic;

typedef struct Head
{
    pic * first;
    pic *last;
    int num;
}Head;


void delete_pic(Head* H,pic* p);
Head * read_pic_from_dir(char *pathname);



#endif //MULTIFUNCTION_MEDIA_BOX_LIST_H
