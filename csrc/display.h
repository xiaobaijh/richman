#ifndef _DISPLAY_H_
#define _DISPLAY_H_

enum {COLOR_BACKGROUD=0, COLOR_BASIC, COLOR_P1, COLOR_P2, NUM_COLOR};

char init_display();

/* 在屏幕左上角打印方形地图（颜色统一为COLOR_BASIC，默认绿）
 * col row指定地图形状 content指定地图上地点的符号
 */
char display_map(int col, int row, char * content);

/* 更改指定位置的地图元素
 * pos~[0,69] 非法地点报错，不修改地图 
 * color 使用宏列表中数值，否则为BASIC_COLOR
 */
char change_map(int pos, char content, int color);

/* 清除消息区域（从地图的下一行到倒数第二行），并将游标放在消息区起始位置
 * 考虑到流程（不会在有getinput完成前清除），选择连输入也清除
 */
char clean_info();

/* 清空消息区域并打印内容
 * 注意：未换行且长度超出屏幕宽度的部分只会保留最后打印的一个字
 */
char print_info(char * content);

/* 将指定位置到行尾清空并打印内容
 * 对于超出屏幕范围的x,y不进行操作
 */
char print_line(int x, int y, char * content);

/* 将内容打印到指定位置
 * 对超出屏幕范围的x,y不进行操作
 */
char replace_line(int x, int y, char * content);

/* 获取一定长度内的内容，复制到buffer中（以\0结尾）
 * 超出长度的输入视为无效，在得到有效输入前阻塞
 */
int get_input(char * buf, int len);

#include <ncurses.h>


#endif
