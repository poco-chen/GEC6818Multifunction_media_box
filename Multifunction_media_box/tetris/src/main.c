#include "move.h"
#include <pthread.h>
#include "touch.h"
#include "list.h"
#include "interface.h"
#include "game_control.h"
#include "global_vars.h"

int score;
int speed;

unsigned int shp, shp_next; // shape
static int dir;				// 控制移动方向
int paused = 0;				// 0运行 1暂停
int gameover = 0;
struct block *bk, *bk_next; // 类型方块结构体——>当前移动及下一个提示
struct block *move_check(struct ls_all *head, int dir);

pthread_mutex_t dir_mutex = PTHREAD_MUTEX_INITIALIZER;

void *auto_down(void *arg);
void *time_out(void *arg);
void pause_game();
void restart_game();

int main(int argc, char *argv[])
{

	show_interface_welcome();

	struct ls_all *head;

	// 显示背景图片
	bmp_show_mix(0, 0, 800, 480, "./pic/bck.bmp");

	int rt;

	pthread_t idt, idr;

	// 获取两种随机形状并初始化，得到初始化结构体
	srand((unsigned int)time(NULL));
	shp = ((unsigned int)rand()) % 7 + 1;
	shp_next = ((unsigned int)rand()) % 7 + 1;

	bk = bk_init(shp);
	bk_next = bk_init(shp_next);

	// 初始化掉落方块结构体
	head = ls_init();

	// 初始化分数和速度
	score = 0;
	speed = 0;

	// 显示移动方块 及 提示方块
	the_show(bk);
	the_show_next(bk_next);
	score_show(0); // 显示成绩

	// 创建控制方块移动线程
	pthread_create(&idt, NULL, auto_down, (void *)head);

	// 时间更新线程，时间到且无操作自动更新dir为下落状态
	pthread_create(&idr, NULL, time_out, NULL);

	while (1)
	{

		// 锁定互斥锁以安全地读取 dir
		pthread_mutex_lock(&dir_mutex);
		int current_dir = dir; // 假设这是在循环中读取 dir 变量的地方
		pthread_mutex_unlock(&dir_mutex);

		if (paused == 1 || gameover == 1 || current_dir == -2)
		{
			usleep(100);
			continue;
		}

		if (current_dir == -1)
		{ // 变形
			change_type(bk);
			the_show_bck_type(bk);
		}
		else
		{ // 移动
			change_dir(bk->p, current_dir);
			the_show_bck_dir(bk->p, current_dir);
		}

		// 移动检查是否越界及掉落到底部
		bk = move_check(head, current_dir);
		if (bk == NULL)
		{
			return -1;
		}

		// 显示方块形状
		the_show(bk);

		pthread_mutex_lock(&dir_mutex);
		dir = -2; // 在主线程中置为 -2 ，表示不动
		pthread_mutex_unlock(&dir_mutex);
	}

	return 0;
}

// 移动检查是否越界及掉落到底部
struct block *move_check(struct ls_all *head, int dir)
{

	int cross_type;

	// 1.检查是否掉落底部（链表底部）
	if (ls_check(head, bk->p) == -1)
	{

		// 1.1 变形越界则恢复原来（再变4次）
		if (dir == -1)
		{

			change_type(bk);
			change_type(bk);
			change_type(bk);

			the_show(bk); // 显示恢复后的方块
		}
		else
		{
			// 1.2 移动越界 则恢复原来
			change_dir_off(bk->p, dir);

			if (dir == 0)
			{ // 1.2.1 向下移动越界(到底)
				the_show(bk);
				if (ls_updata(head, bk) == -1)
				{ // 加入链表，包括重新显示整个链表、消行、判满
					show_interface_end();
					// return NULL; //game over ////////////////
				}
				shp_next = ((unsigned int)rand()) % 7 + 1; // 生成随机方块类型
				bk = bk_next;							   // 当前方块切换为下一个方块
				the_show_bck_next(bk_next->p);			   // 显示下一个方块位置的背景
				bk_next = bk_init(shp_next);			   // 初始化新的下一个方块
				the_show_next(bk_next);					   // 显示新的下一个方块
				speed = score / 10;						   // 根据得分调整速度
			}
			// 1.2.2 向左右移动越界
			else if (dir == 1 || dir == 2)
			{
				the_show(bk); // 重新显示原来的方块
			}
		}

		return bk; // 返回当前方块的指针
	}

	// 2. 越界检查
	cross_type = bound_check(bk->p);

	// 2.1 掉落底部
	if (cross_type == 0)
	{
		change_dir_off(bk->p, 0); // 调整位置确保不越界
		the_show(bk);
		ls_updata(head, bk); // 跟新链表将掉落的块放入链表中
		shp_next = ((unsigned int)rand()) % 7 + 1;
		bk = bk_next;
		the_show_bck_next(bk_next->p);
		bk_next = bk_init(shp_next);
		the_show_next(bk_next);
		speed = score / 10;
	}

	// 2.2 左右移动越界
	else if (cross_type == -1)
	{
		while (bound_check(bk->p) == -1)
		{
			change_dir_off(bk->p, 1); // 向左移只到不再越界
		}
	}
	else if (cross_type == -2)
	{
		while (bound_check(bk->p) == -2)
		{
			change_dir_off(bk->p, 2); // 向右移直到不再越界
		}
	}

	return bk; // 返回当前方块指针
}


void *auto_down(void *arg)
{

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	int x, y, event_type;

	int show_pause = 0, show_dir = 0,  show_shang = 0;

	while (1)
	{

		// get_xy(&x,&y);

		capture_touch_events(&x, &y, &event_type);

		if (event_type == 0)
		{
			// printf("Touch up at (%d, %d)\n", x, y);
			if (show_shang == 1)
			{
				show_shang = 0;
				bmp_show_self(640, 17, 142, 71, "./pic/bck.bmp"); // 恢复背景图
			}

			if (show_dir == 1)
			{
				show_dir = 0;
				bmp_show_self(510, 202, 228, 207, "./pic/bck.bmp"); // 恢复背景图
			}


			if (gameover == 1)
			{
				bmp_show_self(184, 157, 455, 94, "./pic/gameover.bmp"); // 显示游戏失败弹窗
			}

			if (paused == 1)
			{
				bmp_show_self(289, 159, 256, 115, "./pic/pause.bmp"); // 显示暂停弹窗
				show_pause = 1;
			}
			else if (show_pause == 1)
			{
				show_pause = 0;
				bmp_show_self(289, 159, 256, 115, "./pic/bck.bmp"); // 恢复背景图
			}


		}

		if (x > 760 && x < 840 && y > 390 && y < 470)
		{
			if (event_type == 1)
			{
				if (speed < 76)
				{
					speed = speed + 76;
				}
				bmp_show_self(584, 331, 76, 72, "./pic/bck_push.bmp"); // 显示按钮按下后的图片
				show_dir = 1;
			}
		}
		else if (x > 650 && x < 725 && y > 340 && y < 440)
		{
			if (event_type == 1)
			{
				pthread_mutex_lock(&dir_mutex);
				dir = 1; // 1-left
				pthread_mutex_unlock(&dir_mutex);
				speed = score / 10;
				bmp_show_self(513, 275, 84, 86, "./pic/bck_push.bmp"); // 显示按钮按下后的图片
				show_dir = 1;
			}
		}
		else if (x > 850 && x < 920 && y > 340 && y < 440)
		{
			if (event_type == 1)
			{
				pthread_mutex_lock(&dir_mutex);
				dir = 2; // 2-right
				pthread_mutex_unlock(&dir_mutex);
				speed = score / 10;
				bmp_show_self(660, 280, 71, 66, "./pic/bck_push.bmp"); // 显示按钮按下后的图片
				show_dir = 1;
			}
		}
		else if (x > 900 && x < 1010 && y > 20 && y < 90)
		{

			if (event_type == 1)
			{
				pause_game();
				bmp_show_self(716, 19, 59, 62, "./pic/bck_push.bmp"); // 显示按钮按下后的图片
				show_shang = 1;
			}
		}
		else if (x > 820 && x < 880 && y > 20 && y < 90)
		{
			if (event_type == 1)
			{
				bmp_show_self(644, 23, 57, 58, "./pic/bck_push.bmp"); // 显示按钮按下后的图片
				show_shang = 1;
			}
			else if (event_type == 0)
			{
				gameover = 1;
				paused = 1;
				show_interface_end(); // 进入结束界面
									  // restart_game((struct ls_all*)arg );
			}
		}
		else if (x > 740 && x < 840 && y > 240 & y < 350)
		{
			if (event_type == 1)
			{
				pthread_mutex_lock(&dir_mutex);
				dir = -1; // -1-旋转
				pthread_mutex_unlock(&dir_mutex);
				speed = score / 10;
				bmp_show_self(579, 206, 87, 76, "./pic/bck_push.bmp"); // 显示按钮按下后的图片
				show_dir = 1;
			}
		}
	}
}

void *time_out(void *arg)
{

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while (1)
	{
		if (paused == 1 && gameover == 0)
		{
			// printf("p:%d, g:%d\n", paused, gameover);
			usleep(100);
			continue;
		}
		usleep((400 - speed * 5) * 1000);
		//printf("speed: %d\n", speed);
		pthread_mutex_lock(&dir_mutex);
		dir = 0; // 下降
		pthread_mutex_unlock(&dir_mutex);
	}
}
