#include "move.h"

/*以下7个函数为7种形状显示的坐标初始化函数
  返回的是一个整形的数组指针，用malloc申请的堆内存，
  总共40个元素，分为5组，每组8个元素。
  第一组是此形状掉落时的初始化坐标（每种形状都有4个小方块）
  后面4组是变形时相对于之前的偏移量，加上这个偏移量就可以变形
*/

int *arry_init_O()
{

	int *a;

	a = (int *)malloc(sizeof(int) * 4 * 5 * 2);

	// 第一组，此形状掉落时的初始化坐标（每种形状都有4个小方块）
	// 图片左上角的位置，偶数为x坐标，奇数为y坐标
	a[0] = 140;
	a[1] = 20;
	a[2] = 120;
	a[3] = 20;
	a[4] = 120;
	a[5] = 40;
	a[6] = 140;
	a[7] = 40;

	// 后面4组是变形时相对于之前的偏移量，加上这个偏移量就可以变形
	a[8] = 0;
	a[9] = 0;
	a[10] = 0;
	a[11] = 0;
	a[12] = 0;
	a[13] = 0;
	a[14] = 0;
	a[15] = 0;

	a[16] = 0;
	a[17] = 0;
	a[18] = 0;
	a[19] = 0;
	a[20] = 0;
	a[21] = 0;
	a[22] = 0;
	a[23] = 0;

	a[24] = 0;
	a[25] = 0;
	a[26] = 0;
	a[27] = 0;
	a[28] = 0;
	a[29] = 0;
	a[30] = 0;
	a[31] = 0;

	a[32] = 0;
	a[33] = 0;
	a[34] = 0;
	a[35] = 0;
	a[36] = 0;
	a[37] = 0;
	a[38] = 0;
	a[39] = 0;

	return a;
}

int *arry_init_I()
{

	int *a;

	a = (int *)malloc(sizeof(int) * 4 * 5 * 2);

	a[0] = 180;
	a[1] = 20;
	a[2] = 160;
	a[3] = 20;
	a[4] = 140;
	a[5] = 20;
	a[6] = 120;
	a[7] = 20;

	a[8] = -20;
	a[9] = -20;
	a[10] = 0;
	a[11] = 0;
	a[12] = 20;
	a[13] = 20;
	a[14] = 40;
	a[15] = 40;

	a[16] = 20;
	a[17] = 20;
	a[18] = 0;
	a[19] = 0;
	a[20] = -20;
	a[21] = -20;
	a[22] = -40;
	a[23] = -40;

	a[24] = -20;
	a[25] = -20;
	a[26] = 0;
	a[27] = 0;
	a[28] = 20;
	a[29] = 20;
	a[30] = 40;
	a[31] = 40;

	a[32] = 20;
	a[33] = 20;
	a[34] = 0;
	a[35] = 0;
	a[36] = -20;
	a[37] = -20;
	a[38] = -40;
	a[39] = -40;

	return a;
}

int *arry_init_S()
{

	int *a;

	a = (int *)malloc(sizeof(int) * 4 * 5 * 2);

	a[0] = 160;
	a[1] = 20;
	a[2] = 140;
	a[3] = 20;
	a[4] = 140;
	a[5] = 40;
	a[6] = 120;
	a[7] = 40;

	a[8] = -20;
	a[9] = -20;
	a[10] = 0;
	a[11] = 0;
	a[12] = 20;
	a[13] = -20;
	a[14] = 40;
	a[15] = 0;

	a[16] = 20;
	a[17] = 20;
	a[18] = 0;
	a[19] = 0;
	a[20] = -20;
	a[21] = 20;
	a[22] = -40;
	a[23] = 0;

	a[24] = -20;
	a[25] = -20;
	a[26] = 0;
	a[27] = 0;
	a[28] = 20;
	a[29] = -20;
	a[30] = 40;
	a[31] = 0;

	a[32] = 20;
	a[33] = 20;
	a[34] = 0;
	a[35] = 0;
	a[36] = -20;
	a[37] = 20;
	a[38] = -40;
	a[39] = 0;

	return a;
}

int *arry_init_Z()
{

	int *a;

	a = (int *)malloc(sizeof(int) * 4 * 5 * 2);

	a[0] = 120;
	a[1] = 20;
	a[2] = 140;
	a[3] = 20;
	a[4] = 140;
	a[5] = 40;
	a[6] = 160;
	a[7] = 40;

	a[8] = 20;
	a[9] = 20;
	a[10] = 0;
	a[11] = 0;
	a[12] = 20;
	a[13] = -20;
	a[14] = 0;
	a[15] = -40;

	a[16] = -20;
	a[17] = -20;
	a[18] = 0;
	a[19] = 0;
	a[20] = -20;
	a[21] = 20;
	a[22] = 0;
	a[23] = 40;

	a[24] = 20;
	a[25] = 20;
	a[26] = 0;
	a[27] = 0;
	a[28] = 20;
	a[29] = -20;
	a[30] = 0;
	a[31] = -40;

	a[32] = -20;
	a[33] = -20;
	a[34] = 0;
	a[35] = 0;
	a[36] = -20;
	a[37] = 20;
	a[38] = 0;
	a[39] = 40;

	return a;
}

int *arry_init_L()
{

	int *a;

	a = (int *)malloc(sizeof(int) * 4 * 5 * 2);

	a[0] = 160;
	a[1] = 20;
	a[2] = 140;
	a[3] = 20;
	a[4] = 120;
	a[5] = 20;
	a[6] = 120;
	a[7] = 40;

	a[8] = -20;
	a[9] = -20;
	a[10] = 0;
	a[11] = 0;
	a[12] = 20;
	a[13] = 20;
	a[14] = 40;
	a[15] = 0;

	a[16] = -20;
	a[17] = 20;
	a[18] = 0;
	a[19] = 0;
	a[20] = 20;
	a[21] = -20;
	a[22] = 0;
	a[23] = -40;

	a[24] = 20;
	a[25] = 20;
	a[26] = 0;
	a[27] = 0;
	a[28] = -20;
	a[29] = -20;
	a[30] = -40;
	a[31] = 0;

	a[32] = 20;
	a[33] = -20;
	a[34] = 0;
	a[35] = 0;
	a[36] = -20;
	a[37] = 20;
	a[38] = 0;
	a[39] = 40;

	return a;
}

int *arry_init_J()
{

	int *a;

	a = (int *)malloc(sizeof(int) * 4 * 5 * 2);

	a[0] = 120;
	a[1] = 20;
	a[2] = 140;
	a[3] = 20;
	a[4] = 160;
	a[5] = 20;
	a[6] = 160;
	a[7] = 40;

	a[8] = 20;
	a[9] = 20;
	a[10] = 0;
	a[11] = 0;
	a[12] = -20;
	a[13] = -20;
	a[14] = 0;
	a[15] = -40;

	a[16] = 20;
	a[17] = -20;
	a[18] = 0;
	a[19] = 0;
	a[20] = -20;
	a[21] = 20;
	a[22] = -40;
	a[23] = 0;

	a[24] = -20;
	a[25] = -20;
	a[26] = 0;
	a[27] = 0;
	a[28] = 20;
	a[29] = 20;
	a[30] = 0;
	a[31] = 40;

	a[32] = -20;
	a[33] = 20;
	a[34] = 0;
	a[35] = 0;
	a[36] = 20;
	a[37] = -20;
	a[38] = 40;
	a[39] = 0;

	return a;
}
int *arry_init_T()
{

	int *a;

	a = (int *)malloc(sizeof(int) * 4 * 5 * 2);

	a[0] = 120;
	a[1] = 20;
	a[2] = 140;
	a[3] = 20;
	a[4] = 160;
	a[5] = 20;
	a[6] = 140;
	a[7] = 40;

	a[8] = 20;
	a[9] = 20;
	a[10] = 0;
	a[11] = 0;
	a[12] = -20;
	a[13] = -20;
	a[14] = 20;
	a[15] = -20;

	a[16] = 20;
	a[17] = -20;
	a[18] = 0;
	a[19] = 0;
	a[20] = -20;
	a[21] = 20;
	a[22] = -20;
	a[23] = -20;

	a[24] = -20;
	a[25] = -20;
	a[26] = 0;
	a[27] = 0;
	a[28] = 20;
	a[29] = 20;
	a[30] = -20;
	a[31] = 20;

	a[32] = -20;
	a[33] = 20;
	a[34] = 0;
	a[35] = 0;
	a[36] = 20;
	a[37] = -20;
	a[38] = 20;
	a[39] = 20;

	return a;
}

// 检查方块左右下移动时有无越界--》下越界返回0、左越界返回-1、右越界返回-2
int bound_check(int *p)
{

	int i;

	for (i = 0; i < 4; i++)
	{

		if (p[i * 2 + 1] > 460)
		{
			return 0; // down out
		}

		if (p[i * 2] > 300)
		{
			return -2; // right out
		}
		else if (p[i * 2] < 0)
		{
			return -1; // left out
		}
	}

	return 1;
}

// 移动方块，仅限三种方向
void change_dir(int *p, int dir)
{ // dir: 0-down  1-left  2-right
	//printf("dir:%d\n", dir);
	int i = 0;
	for (; i < 4; i++)
	{
		if (dir == 0)
		{
			p[i * 2 + 1] += 20;
		}
		else if (dir == 1)
		{
			p[i * 2] -= 20;
		}
		else if (dir == 2)
		{
			p[i * 2] += 20;
		}
	}
}

// 移动越界 需要恢复回原来的坐标--》dir: 0-down  1-left  2-right
void change_dir_off(int *p, int dir)
{ // dir: 0-down  1-left  2-right

	int i = 0;

	// if(dir == 0){
	// printf("change_dir_off error\n");
	// exit(-1);
	// }

	for (; i < 4; i++)
	{

		if (dir == 1)
		{
			p[i * 2] += 20;
		}
		else if (dir == 2)
		{
			p[i * 2] -= 20;
		}
		else if (dir == 0)
		{
			p[i * 2 + 1] -= 20;
		}
	}
}

// 变形
void change_type(struct block *bk)
{

	int i;

	if (bk->shape == 1)
	{ // 如果方块直接返回
		return;
	}

	for (i = 0; i < 4; i++)
	{
		// 更新坐标值到下一个形态
		bk->p[i * 2] += bk->p[i * 2 + bk->type * 8]; // 因为用int存贮，
													 // 且一个坐标信息占两个int所以要 *8
		bk->p[i * 2 + 1] += bk->p[i * 2 + bk->type * 8 + 1];
		// printf("%d\t%d\t",bk->p[i*2+bk->type*8],bk->p[i*2+bk->type*8+1]);
	}

	// 更新到下一个旋转状态
	bk->type++;

	if (bk->type >= 5)
	{
		bk->type = 1;
	}

	return;
}

// LCD显示移动的方块
void the_show(struct block *bk)
{

	int i;
	int *p = bk->p;
	int shp = bk->shape;

	char s[50];

	switch (shp)
	{

	case 1:
		strcpy(s, "./pic/O.bmp");
		break;
	case 2:
		strcpy(s, "./pic/I.bmp");
		break;
	case 3:
		strcpy(s, "./pic/S.bmp");
		break;
	case 4:
		strcpy(s, "./pic/Z.bmp");
		break;
	case 5:
		strcpy(s, "./pic/L.bmp");
		break;
	case 6:
		strcpy(s, "./pic/J.bmp");
		break;
	case 7:
		strcpy(s, "./pic/T.bmp");
		break;
	}

	for (i = 0; i < 4; i++)
	{
		bmp_show_mix(p[i * 2], p[i * 2 + 1], 20, 20, s);
	}
}

// 显示提示的下一个方块
void the_show_next(struct block *bk_next)
{

	int i;
	int *p = bk_next->p;
	int shp = bk_next->shape;

	char s[50];

	switch (shp)
	{

	case 1:
		strcpy(s, "./pic/O.bmp");
		break;
	case 2:
		strcpy(s, "./pic/I.bmp");
		break;
	case 3:
		strcpy(s, "./pic/S.bmp");
		break;
	case 4:
		strcpy(s, "./pic/Z.bmp");
		break;
	case 5:
		strcpy(s, "./pic/L.bmp");
		break;
	case 6:
		strcpy(s, "./pic/J.bmp");
		break;
	case 7:
		strcpy(s, "./pic/T.bmp");
		break;
	}

	for (i = 0; i < 4; i++)
	{
		// bmp_show_mix(p[i*2]+240,p[i*2+1]+90,20,20,s);
		bmp_show_mix(p[i * 2] + 320, p[i * 2 + 1] + 65, 20, 20, s);
	}
}

// 方块移动后需要把原来的方块--》消失--》显示背景色
void the_show_bck_dir(int *p, int dir)
{ // dir: 0-down  1-left  2-right

	int i;

	for (i = 0; i < 4; i++)
	{
		if (dir == 0)
		{
			bmp_show_self(p[i * 2], p[i * 2 + 1] - 20, 20, 20, "./pic/bck.bmp");
		}
		else if (dir == 1)
		{
			bmp_show_self(p[i * 2] + 20, p[i * 2 + 1], 20, 20, "./pic/bck.bmp");
		}
		else if (dir == 2)
		{
			bmp_show_self(p[i * 2] - 20, p[i * 2 + 1], 20, 20, "./pic/bck.bmp");
		}
	}
}

// 提示的下一个方块--》改变后，让之前的--》消失--》显示背景色
void the_show_bck_next(int *p)
{

	int i;

	for (i = 0; i < 4; i++)
	{

		// bmp_show_self(p[i*2]+240,p[i*2+1]+90,20,20,"./tetris_pic/bck.bmp");
		bmp_show_self(p[i * 2] + 320, p[i * 2 + 1] + 65, 20, 20, "./pic/bck.bmp");
	}
}

// 方块变形后让之前的--》消失--》显示背景色
void the_show_bck_type(struct block *bk)
{

	int i;
	if (bk->type == 1)
		bk->type = 5; // 如果是形态1将type改为5使其计算结果正确

	for (i = 0; i < 4; i++)
	{ // 还原上一个位置的背景图

		bmp_show_self(bk->p[i * 2] - bk->p[i * 2 + (bk->type - 1) * 8],
					  bk->p[i * 2 + 1] - bk->p[i * 2 + (bk->type - 1) * 8 + 1],
					  20, 20, "./pic/bck.bmp");
	}
	if (bk->type == 5)
		bk->type = 1; // 还原回来
}

// 方块掉落后 得到一个新形状的方块 初始化函数--》得出初始化结构体
struct block *bk_init(int shape)
{

	struct block *bk;
	bk = (struct block *)malloc(sizeof(struct block));

	switch (shape)
	{
	case 1:
		bk->p = arry_init_O();
		bk->shape = 1;
		break;
	case 2:
		bk->p = arry_init_I();
		bk->shape = 2;
		break;
	case 3:
		bk->p = arry_init_S();
		bk->shape = 3;
		break;
	case 4:
		bk->p = arry_init_Z();
		bk->shape = 4;
		break;

	case 5:
		bk->p = arry_init_L();
		bk->shape = 5;
		break;
	case 6:
		bk->p = arry_init_J();
		bk->shape = 6;
		break;
	case 7:
		bk->p = arry_init_T();
		bk->shape = 7;
		break;
	default:
		break;
	}

	bk->type = 1;

	return bk;
}

// 把掉落的方块加入到掉落方块的链表当中去，并消行和判满--》添加后链表满返回-1
int ls_updata(struct ls_all *head, struct block *bk)
{

	int *p = bk->p;

	int i;

	for (i = 0; i < 4; i++)
	{

		ls_add(head, p[i * 2], p[i * 2 + 1], bk->shape);
	}

	free(bk->p);

	free(bk);

	// 扫描检测消行和满
	if (ls_check_self(head) == -1)
	{
		return -1;
	}
}

// 方块移动后，检查是否掉落到底部
int ls_check(struct ls_all *head, int *p)
{

	struct ls_all *tmp;
	int i;

	for (i = 0; i < 4; i++)
	{ // 遍历方块的四个点
		tmp = head;
		tmp = tmp->next;

		while (tmp != head)
		{ // 遍历链表中的所有节点
			if (tmp->x0 == p[i * 2] && tmp->y0 == p[i * 2 + 1])
			{
				return -1; // 如果某个顶点与链表中的某个节点重叠，则返回-1
			}

			tmp = tmp->next;
		}
	}
	return 0; // 如果没有则返回0
}

// 检查整个链表有无消行--》把整个屏幕行扫描式检测--》方块到顶返回-1
int ls_check_self(struct ls_all *head)
{
	struct ls_all *tmp; // 零时指针，用于遍历链表
	int i = 460;		// 初始化为460，从屏幕底部开始扫描
	int n = 0;			// 统计当前行的方块数量
	tmp = head;
	tmp = tmp->next; // 初始化tmp为链表的第二个节点（链表为带头节点的双向链表）

	while (i >= 40)
	{		   // 从底部 460 开始一直扫描到顶部 40
		n = 0; // 每次开始循环将方块数置 0，tmp指向第二个节点
		tmp = head;
		tmp = tmp->next;

		// 1.扫描当前行
		while (tmp != head)
		{
			if (tmp->y0 == i)
			{ // 如果方块在当前行
				n++;
				if (i < 80)
				{						   // 如果方块在顶部区域（游戏结束）
					printf("game over\n"); //////////
					gameover = 1;
					bmp_show_self(184,157,455,94,"./pic/gameover.bmp"); // 显示游戏失败弹窗
					sleep(3);
					return -1; // 返回-1表示游戏结束
				}
			}
			// printf("%d  %d\n",i,tmp->y0);

			tmp = tmp->next;
		}

		// 2.判断当前行已经填满(即有16个方块在同一行)
		if (n == 16)
		{
			score++; // 消一行加一分
			printf("%d line\n", score);
			score_show(score);

			speed = score / 10;

			// 3.重新显示背景图(擦除所有的方块)
			bmp_show_self(0, 33, 320, 447, "./pic/bck.bmp");

			// 4.再次遍历链表，删除当前行的方块并下移上方的方块
			tmp = head;
			tmp = tmp->next;
			while (tmp != head)
			{
				if (tmp->y0 == i)
				{					   // 如果当前方块在删除行
					tmp = ls_del(tmp); // 删除当前方块
				}
				// printf("%d  %d\n",i,tmp->y0);
				else if (tmp->y0 < i)
				{				   // 如果当前方块在当前方块之上
					tmp->y0 += 20; // 将方块下移
				}

				tmp = tmp->next;
			}

			// 5.重新显示所有方块
			ls_all_show(head);
			i += 20; // 因为当前行被删除，需要下移一行重新检测
		}

		i -= 20; // 上移一行
	}

	return 0; // 正常退出，游戏继续进行
}

// 显示成绩
void score_show(int n)
{

	int a1, a2, a3;
	char s[3][50];
	char st[3][50];
	int i;

	a1 = n / 100;	  // 计算百位数字
	a2 = n / 10 % 10; // 计算十位数字
	a3 = n % 10;	  // 计算个位数字

	for (i = 0; i < 3; i++)
	{

		bzero(s[i], 50); // 初始化字符串 s[i], 将其清零
	}

	s[0][0] = a1 + 48; // 将百位数字转换成字符，并存储到s[0]
	s[1][0] = a2 + 48; // 将十位数字转换成字符，并存储到s[1]
	s[2][0] = a3 + 48; // 将个位数字转换成字符，并存储到s[2]

	for (i = 0; i < 3; i++)
	{

		strcat(s[i], ".bmp\0");			// 在每个字符后面添加".bmp"扩展名
		strcpy(st[i], "./pic/"); // 将路径 "./tetris_pic/" 复制到 st[i]
		strcat(st[i], s[i]);			// 将文件名连接到路径后
		bmp_show_mix(210 + 20 * i, 12, 20, 20, st[i]);
		// printf("%s\n",st[i]);
	}
}

// 显示整个掉落的方块链表
void ls_all_show(struct ls_all *head)
{

	char s[50];

	struct ls_all *tmp;
	tmp = head;
	tmp = tmp->next;

	while (tmp != head)
	{

		switch (tmp->shape)
		{

		case 1:
			strcpy(s, "./pic/O.bmp");
			break;
		case 2:
			strcpy(s, "./pic/I.bmp");
			break;
		case 3:
			strcpy(s, "./pic/S.bmp");
			break;
		case 4:
			strcpy(s, "./pic/Z.bmp");
			break;
		case 5:
			strcpy(s, "./pic/L.bmp");
			break;
		case 6:
			strcpy(s, "./pic/J.bmp");
			break;
		case 7:
			strcpy(s, "./pic/T.bmp");
			break;
		}

		bmp_show_mix(tmp->x0, tmp->y0, 20, 20, s);

		tmp = tmp->next;
	}
}