#include "interface.h"

#define BUTTON_X 250 // 按钮区域的左上角 X 坐标
#define BUTTON_Y 250 // 按钮区域的左上角 Y 坐标
#define BUTTON_W 260 // 按钮区域的宽度
#define BUTTON_H 230 // 按钮区域的高度

void show_interface_welcome()
{
    bmp_show_mix(0, 0, 800, 480, "interface1.bmp"); // 显示欢迎界面背景

    int fd_TS=open("/dev/input/event0",O_RDWR);
    if(fd_TS==-1)
    {
        perror("触摸屏设备文件打开失败");
    }
    int x,y,x1=256,y1=310;
    x=-1;
    y=-1;
    int fd_ts=open("/dev/input/event0",O_RDWR);
    if(fd_ts==-1)
    {
        perror("触摸屏设备文件打开失败");
    }
    int press_button=0;
    struct input_event ts;
    int ret;
    while(1)
    {
        x=-1,y=-1,x1=256,y1=310;;
        while(1)
        {

            ret= read(fd_ts,&ts,sizeof(ts));

            if(ret != sizeof(ts))
            {
                continue;
            }
            if(ts.type == EV_ABS && ts.code == ABS_X)//接收x坐标
            {
                if(x<0)
                    x = ts.value*800/1024;
                else
                    x1 = ts.value*800/1024;
            }
            if(ts.type == EV_ABS && ts.code == ABS_Y)//接收触点y坐标
            {
                if(y<0)
                    y = ts.value*480/600;
                else
                    y1=ts.value*480/600;
            }
            if((ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0\
        ||ts.type == EV_ABS && ts.code == ABS_PRESSURE && ts.value == 0))
            {
                if(255<x&&x<520&&305<y&&y<365)
                {
                    if(255<x1&&x1<520&&305<y1&&y1<365)
                        press_button=1;
                }
                break;
//            手指弹起停止获取;
            }
        }
        if(press_button==1)
            break;
        printf("(%d,%d)-->(%d,%d)\n",x,y,x1,y1);
    }
    close(fd_TS);
}

// 显示时间
void time_show(int n)
{

    int a1, a2, a3;
    char s[3][50];
    char st[3][50];
    int i;

    a1 = n / 100;     // 计算百位数字
    a2 = n / 10 % 10; // 计算十位数字
    a3 = n % 10;      // 计算个位数字

    for (i = 0; i < 3; i++)
    {

        bzero(s[i], 50); // 初始化字符串 s[i], 将其清零
    }

    s[0][0] = a1 + 48; // 将百位数字转换成字符，并存储到s[0]
    s[1][0] = a2 + 48; // 将十位数字转换成字符，并存储到s[1]
    s[2][0] = a3 + 48; // 将个位数字转换成字符，并存储到s[2]

    for (i = 0; i < 3; i++)
    {

        strcat(s[i], ".bmp\0");         // 在每个字符后面添加".bmp"扩展名
        strcpy(st[i], "./tetris_pic/"); // 将路径 "./tetris_pic/" 复制到 st[i]
        strcat(st[i], s[i]);            // 将文件名连接到路径后
        bmp_show_mix(280 + 20 * i, 45, 20, 20, st[i]);
        // printf("%s\n",st[i]);
    }
}

// 全局变量，用于线程间通信
int cut_down = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER; // 互斥锁，用于同步对 seconds_left 的访问
pthread_cond_t count_cond = PTHREAD_COND_INITIALIZER;    // 条件变量，用于线程间同步

void *touch_event_thread(void *args)
{
    int x, y, event_type;
    int button_down = 0;
    while (1)
    {
        if (capture_touch_events(&x, &y, &event_type) == -1)
        {
            // 触摸事件捕获失败，可能需要处理错误或退出
            break;
        }
        // 检查按钮是否被按下
        if (event_type == 1 && x > 440 && x < 620 && y > 360 && y < 460)
        {
                // 用户按下了按钮区域
            bmp_show_self(BUTTON_X, BUTTON_Y+5, BUTTON_W, BUTTON_H-10, "./pic/bk_push.bmp"); // 显示按钮按下的图片
            button_down = 1; // 标记按钮被按下
        }

        // 检查按钮是否被按下并释放

        if (event_type == 0 && button_down)
        {
            // 用户释放按钮，提前重启游戏
            button_down = 0; // 重置按钮状态
            // 触摸离开事件且按钮之前被按下
            bmp_show_self(BUTTON_X, BUTTON_Y, BUTTON_W, BUTTON_H, "./pic/bck.bmp"); // 恢复按钮正常状态

            if (x > 440 && x < 620 && y > 360 && y < 460)
            {
                pthread_mutex_lock(&count_mutex);
                cut_down = 1;
                pthread_cond_signal(&count_cond); // 发送信号给主线程
                pthread_mutex_unlock(&count_mutex);
                break;
            }
        }
        pthread_mutex_unlock(&count_mutex);
    }
    return NULL;
}

void show_interface_end()
{
    pause_game();
    // 重置倒计时和按钮状态
    int seconds_left = 0; // 20s 倒计时

    // 启动触摸事件线程
    pthread_t touch_thread_id;
    pthread_create(&touch_thread_id, NULL, touch_event_thread, NULL);

    bmp_show_mix(0, 0, 800, 480, "./pic/bck.bmp"); // 显示结束广告界面
    usleep(300000);
    bmp_show_mix(0, 0, 800, 480, "./pic/bk_bck.bmp"); // 显示结束广告界面



    while (1)
    {
        pthread_mutex_lock(&count_mutex);
        // 检查倒计时是否结束或按钮是否被按下
        if (seconds_left <= 0 || cut_down == 1)
        {
            pthread_mutex_unlock(&count_mutex);
            break; // 倒计时结束或按钮被按下，退出循环
        }
        pthread_mutex_unlock(&count_mutex);

        time_show(seconds_left); // 显示剩余时间
        seconds_left--;          // 倒计时减少
        sleep(1);                // 等待一秒
    }

    // 取消触摸事件线程，如果它还在运行
    pthread_cancel(touch_thread_id);
    pthread_join(touch_thread_id, NULL);

    // 倒计时结束或用户提前重启游戏
    restart_game();
}