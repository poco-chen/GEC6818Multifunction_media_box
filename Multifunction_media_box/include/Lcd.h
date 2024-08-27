//
// Created by 陈宇轩 on 2024/8/13.
//

#ifndef LCD_LCD_H
#define LCD_LCD_H
#define LCD_PATH "/dev/fb0"

void Lcd_Init(void);
void Draw_React(int x,int y,int len,int weight,int color);
void Draw_Point(int x,int y,int color);
void Lcd_ReInit(void);


#endif //LCD_LCD_H
