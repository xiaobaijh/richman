#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
// #include "display.h"
#include <string.h>
#include "display.h"

static int shape_map[3] = {0};
static int _color_array[] = {COLOR_BLACK, COLOR_GREEN, COLOR_YELLOW, COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW};

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
    move(shape_map[1], 0); 
    clrtobot();
    refresh();
    return 0;
}

char print_info(const char * content){
    // getch();
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

char print_line(int x, int y, const char * content, int color){
    if(x < 0 || y < 0 )
        return 1; 
    move(y, x);
    clrtoeol();
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

int get_input(const char * hint, int color, char * buf, int len){
    fflush(stdin);
    if(len == 0){
        getch();
        return 1;
    }
    print_line(0, LINES-1, hint, color);
    const int x = strlen(hint)-3;
    int count = 0, input = 0;
    while(1){
        count = 0;
        do{
get_input_load:
            input = getch();
            switch(input){
                case '\n':
                    move(LINES-1,0);
                    clrtoeol();
                    buf[count] = '\0';
                    return count;
                case 263:
                    if(count > 0){
                        addstr("\b \b");
                        --count;
                    }
                    break;
                default:
                    addch(input);
                    buf[count] = input;
                    ++count;
                    break;
            }
        }while(count < len);
        do{
            input = getch();
            if(input == 263){
                addstr("\b \b");
                if(--count < len - 1)
                    goto get_input_load;
            }else{
                addch(input);
                ++count;
            }
        }while(input != '\n');
        move(LINES-1, x);
        clrtoeol();
    }
}

#define BUFFER_LINE_BASE 20
typedef struct{
    char ** content; // 
    int cap; // number of valid content entry
    int line;
    int col;
    int row;
    int color;
} Tips;

static Tips tips = {0};
// '\n' turn into '\0\n'
void str2tips(const char * content){
    if(!tips.col || !tips.row) // tips not initialized
        return;

    int index, row, col, line_index;
    for(index = 0; content[index] != '\0'; ){
        tips.content = (char **) realloc(tips.content, (tips.cap+BUFFER_LINE_BASE)*sizeof(char *));
        row = tips.cap;
        tips.cap += BUFFER_LINE_BASE;

        for(col = 0, line_index = 0; row < tips.cap; ++row, col = 0, line_index = 0){
            tips.content[row] = (char *)calloc(1, (tips.col)*3+1); // chinese char takes 3 bytes
            while(col < tips.col){
                switch(content[index]){
                    case '\0':
                        tips.content[row][line_index] = '\0';
                        tips.cap = row+1;
                        tips.content = (char **)realloc(tips.content, tips.cap*sizeof(char*));
                        return;
                    case '\n':
                        tips.content[row][line_index] = '\0';
                        tips.content[row][line_index+1] = '\n';
                        ++index;
                        col = tips.col; // end this in-loop
                        break;
                    default:
                        if(content[index] < 0 && (content[index+1] < 0 || content[index+1] > 63)){ // chinese char
                            for(int i = 0; i < 3; ++i){
                                tips.content[row][line_index++] = content[index++];
                            }
                        }else{
                            tips.content[row][line_index++] = content[index++];
                        }
                            ++col;
                        break;
                }
            }
        } 
    }
}


char * tips2str(void){
    char * str = NULL;
    for(int line = 0, size = 0; line < tips.cap; ++line){
// sprintf, turn '\0\n' to '\n'
    }
    return str;
}

void init_tips(const char * content, int color){
    if(!content)
        return;
    if(tips.cap != 0){
        for(int i = 0; i < tips.cap; free(tips.content[i++]));
        free(tips.content);
    }
    getmaxyx(stdscr, tips.row, tips.col);
    tips.cap = 0;
    tips.content = NULL;
    str2tips(content);    
    tips.color = color;
}

void show_tips(void){
    clean_info();
    attron(COLOR_PAIR(color_num(tips.color, COLOR_BACKGROUD)));
    int row = tips.row - shape_map[1] - 1;
    row = (row < tips.cap) ? row : tips.cap;
    int index = 0;
    move(shape_map[1],0);
    char input = 's';
    while(input != 'q'){
        switch(input){
            case 's':
                clean_info();
                index = 0;
                for(index = 0; index < row; ++index){
                    move(shape_map[1]+index, 0);
                    addstr(tips.content[index]);
                }
                refresh();
                break;
            case 'j': // up half page
                if(!index)
                    break;
                clean_info();
                index -= ((row>>1)+row);
                index = (index < 0) ? 0 : index;
                for(int i = 0; i < row; ++i){
                    move(shape_map[1]+i, 0);
                    // printf("%s", tips.content[index]);
                    addstr(tips.content[index++]);
                    refresh();
                }
                break;
            case 'k':
                if(index == tips.cap)
                    break;
                clean_info();
                index -= row >> 1;
                for(int i = 0; i < row && index < tips.cap; ++i){
                    move(shape_map[1]+i, 0);
                    // printf("%s", tips.content[index]);
                    addstr(tips.content[index++]);
                    refresh();
                }
                break;
            default:
                break;
        }
        move(LINES-1, 0);
        addstr("s:开头,j:下翻(半页),k:上翻(半页),q:退出");
        clrtoeol();
        input = getch();
    }
    attroff(COLOR_PAIR(tips.color));
}

void end_display(){
    endwin();
}