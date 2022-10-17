#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "display.h"
#include <string.h>

static int shape_map[3] = {0};
static int _color_array[] = {COLOR_BLACK, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE};

#define curs_color(color) ((color < NUM_COLOR) ?  _color_array[color] : _color_array[COLOR_BASIC])

static int color_num(int fg, int bg){
    int B, bbb, ffff;
    B = 1 << 7;
    bbb = (7 & bg) << 4;
    ffff = 7 & fg;
    return (B | bbb | ffff);
}

static void init_colorpairs(void){
    int fg, bg;
    int colorpair;

    for (bg = 0; bg < NUM_COLOR; bg++) {
        for (fg = 0; fg < NUM_COLOR; fg++) {
            colorpair = color_num(fg, bg);
            init_pair(colorpair, curs_color(fg), curs_color(bg));
        }
    }
}

int is_bold(int fg){
    /* return the intensity bit */

    int i;

    i = 1 << 3;
    return (i & fg);
}

static void setcolor(int fg, int bg){
    /* set the color pair (color_num) and bold/bright (A_BOLD) */
    attron(COLOR_PAIR(color_num(fg, bg)));
    if (is_bold(fg)) {
        attron(A_BOLD);
    }
}

static void unsetcolor(int fg, int bg){
    /* unset the color pair (color_num) and
       bold/bright (A_BOLD) */
    attroff(COLOR_PAIR(color_num(fg, bg)));
    if (is_bold(fg)) {
        attroff(A_BOLD);
    }
}

char init_display(){
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    raw();
    noecho();
    curs_set(0); // 隐藏光标
    start_color();
    init_colorpairs();
    if (has_colors() == FALSE) {
        puts("Your terminal does not support color");
        return 1;
    }
    return 0;
    // if ((LINES < 24) || (COLS < 80)) {
    //     endwin();
    //     puts("Your terminal needs to be at least 80x24");
    //     exit(2);
    // }
    
}

char jump2pos(int pos){
    if(pos < 0 || pos >= shape_map[2])
        return 1;
    if(pos < shape_map[0]){
        move(0, pos);
        return 0;
    }
    pos -= (shape_map[0] - 1);
    if(pos < shape_map[1]){
        move(pos, shape_map[0]-1);
        return 0;
    }
    pos -= (shape_map[1] - 2);
    if(pos < shape_map[0]){
        move(shape_map[1]-1, shape_map[0] - pos);
        return 0;
    }
    pos -= (shape_map[0] - 1);
    move(shape_map[1]-pos, 0);
    return 0;
}

void display_rect(int col, int row, char * content){
    move(0, 0);
    int i = 0, m = 0, x = 0, y = 0;
    for(m = col; m--; )
        addch(content[i++]);
    getyx(stdscr, y, x);
    --x;
    for(m = row - 2; m-- > 0; ){    
        move(++y,x);
        addch(content[i++]);
    }
    i = 2*(col+row)-5;
    y += (3 - row);
    x -= (col-1);
    move(y, x);
    for(m = row - 2; m-- > 0; ){
        addch(content[i--]);
        move(++y, x);
    }
    for(m = col; m--; ){
        addch(content[i--]);
    }
    refresh();
}

char display_map(int col, int row, char * content){
    if(!content)
        return 2;
    setcolor(COLOR_BASIC, COLOR_BACKGROUD);
    shape_map[0] = col;
    shape_map[1] = row;
    shape_map[2] = 2*(col+row-2);
    display_rect(col, row, content);
    unsetcolor(COLOR_BASIC, COLOR_BACKGROUD);
    return 0;
}

char change_map(int pos, char content, int color){
    if(pos < 0 || pos >= shape_map[2]){
        // printf("Trying to change a place out of the map(%d)\n", pos);
        return 1;
    }
    if(jump2pos(pos))
        return 1;
    setcolor(color, COLOR_BACKGROUD);
    addch(content);
    unsetcolor(color, COLOR_BACKGROUD);
    refresh();
    return 0;
}

char clean_info(){
    clrtoeol();
    move(shape_map[1], 0); 
    refresh();
    return 0;
}

char print_info(char * content){
    clean_info();
    addstr(content);
    refresh();
    return 0;
}

char replace_line(int x, int y, char * content, int color){
    if(!content)
        return 2;
    if(x < 0 || y < 0)
        return 1; 
    move(y, x);
    addstr(content);
    refresh();
    setcolor(color, COLOR_BACKGROUD);
    addstr(content);
    unsetcolor(color, COLOR_BACKGROUD);
    refresh();
    return 0;
}

char print_line(int x, int y, char * content, int color){
    if(x < 0 || y < 0 )
        return 1; 
    move(y, x);
    clrtobot();
    char res = 2;
    if(content){
        setcolor(color, COLOR_BACKGROUD);
        addstr(content);
        unsetcolor(color, COLOR_BACKGROUD);
        res = 0;
    }
    refresh();
    return res;
}

int get_input(char * hint, int color, char * buf, int len){
    print_line(0, LINES-1, hint, color);
    int x = strlen(hint);
    int count = 0;
    while(1){
        for(count = 0; count < len-1; ++count){
            buf[count] = getch();
            if(buf[count] == '\n'){
                move(LINES-1,0);
                clrtobot();
                buf[count] = '\0';
                return count;
            }else{
                addch(buf[count]);
            }
        }
        count = getch();
        while(count != '\n'){
            addch(count);
            count = getch();
        }
        move(LINES-1, x);
        clrtobot();
    }
}