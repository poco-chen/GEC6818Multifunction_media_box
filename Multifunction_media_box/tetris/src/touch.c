#include "touch.h"

// 捕捉屏幕按下与离开事件的函数--》按下后返回一个坐标和按下信号，离开返回坐标和离开信号
/* 这段代码主要的功能是不断的额监听设备的输入事件，当检测到按下或者离开事件时,
   记录对应的坐标和事件类型，并返回给调用者。*/
int capture_touch_events(int *x, int *y, int *event_type)
{
    int fd_touch = open("/dev/input/event0", O_RDONLY);
    if (fd_touch == -1)
    {
        printf("open touch dev fail\n");
        return -1;
    }

    struct input_event ts; // 创建一个输入事件结构体

    while (1)
    {
        // 使用 read 函数从触摸屏设备中读取事件，存储到ts结构体中
        read(fd_touch, &ts, sizeof(ts));
        /* 该函数在没有检测到触摸事件时会一直阻塞在 read 函数处，
        因此在实际应用中可能需要在单独的线程中调用该函数，以免阻塞主程序的执行。*/

        if (ts.type == EV_ABS)
        {
            // 处理绝对输入事件，获取x和y坐标
            if (ts.code == ABS_X)
            {
                *x = ts.value;
            }
            else if (ts.code == ABS_Y)
            {
                *y = ts.value;
            }
        }
        else if (ts.type == EV_KEY && ts.code == BTN_TOUCH)
        {
            // 处理按键事件，判断按键类型（按下或离开）
            if (ts.value == 1)
            { // 按下
                *event_type = 1;
                break;
            }
            else if (ts.value == 0)
            { // 离开
                *event_type = 0;
                break;
            }
        }
    }

    close(fd_touch);
    return 0;
}
