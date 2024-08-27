//
// Created by 陈宇轩 on 2024/8/14.
//

#ifndef MY_FRIST_PROJECT_TOUCH_H
#define MY_FRIST_PROJECT_TOUCH_H
#define TS_PATH "/dev/input/event0"

typedef struct point
{
    int x;//横坐标
    int y;//纵坐标
}point;

typedef enum direction
{
     left=1,
     right,
     up,
     down
}direction;

struct point Get_Point(void);
int Get_Direction(void);

#endif //MY_FRIST_PROJECT_TOUCH_H