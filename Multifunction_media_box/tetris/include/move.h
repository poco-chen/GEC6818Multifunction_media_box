/*
	move.h-->关于方块移动变形 及 显示 的控制函数的声明

*/

#ifndef __MOVE_H
#define __MOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "bmp_show.h"
#include "touch.h"
#include "list.h"
#include "global_vars.h"


struct block{
	
	int *p;		// 指向形状的数组指针
	
	int shape; 	// 形状类型 (1-7)

	int type; 	// 方块的旋转状态 (1-4)
};

extern int score; 
extern int speed;

int * arry_init_L();
int * arry_init_J();
int * arry_init_T();
int bound_check(int *P);
void change_dir(int *p,int dir);
void the_show(struct block *bk);
void the_show_next(struct block *bk_next);

void the_show_bck_next(int *p);
void the_show_bck_dir(int *p,int dir);
void change_dir_off(int *p,int dir);

void change_type(struct block *bk);
void the_show_bck_type(struct block *bk);

void score_show(int n);

struct block * bk_init(int shape);
int ls_check(struct ls_all *head,int *p);
int ls_updata(struct ls_all *head,struct block *bk);
int ls_check_self(struct ls_all *head);
void ls_all_show(struct ls_all *head);

#endif