//
// Created by 陈宇轩 on 2024/8/14.
//

#ifndef MY_FRIST_PROJECT_BMP_H
#define MY_FRIST_PROJECT_BMP_H
#define LCD_PATH "/dev/fb0"

typedef struct BMP
{
    int width;
    int height;
    short depth;
}BMP;
void BMP_Display(const char * bmp_name, int x0 , int y0);
#endif //MY_FRIST_PROJECT_BMP_H
