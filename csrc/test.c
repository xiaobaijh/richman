#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "display.h"
#define BUF_LEN 1024
char buf[BUF_LEN];
char content[30];

char * initMap(){
    char * map = (char *)calloc(70, sizeof(char));
    int i = 0;
    map[i++] = 'S';
    for(int m = 0; m < 13; ++m)
        map[i++] = '0';
    map[i++] = 'H';
    for(int m = 0; m < 13; ++m)
        map[i++] = '0';
    map[i++] = 'T';
    for(int m = 0; m < 6; ++m)
        map[i++] = '0';
    map[i++] = 'G';
    for(int m = 0; m < 13; ++m)
        map[i++] = '0';
    map[i++] = 'P';
    for(int m = 0; m < 13; ++m)
        map[i++] = '0';
    map[i++] = 'M';
    for(int m = 0; m < 6; ++m)
        map[i++] = '$';
    return map;
}

int contain_string(char * content, char * str){
    if(!content || !str)
        return 0;
    int i;
    for(i = 0; content[i] != '\0' && str[i] != '\0'; ++i){
        if(str[i] != content[i])
            break;
    }
    if(content[i] != '\0')
        return 0;
    return i;
}

// char cmd_call(){
//     int len = 0, index = 0;
//     do{
//         buf[len] = getch();
//     }while(buf[len++] != '\n');
//     buf[--len] = '\0';
//     if(buf[0] == 'q')
//         return 0; //exit
    
//     sprintf(content, "print_info");
//     index = contain_string(content, buf);
//     if(index){
//         //解析参数并调用函数
//     }
//     return 1;
// }

int main(void){
    init_display();
    char * map = initMap();
    display_map(29, 8, map);
    refresh();
    // while(cmd_call());
    char tips[] = "asd\n\n\n\nasdf\n\n\n\n\n\n\nasdfawef\nasdf\naasdf\naasdf\nasdb\nasdfc\naasdfsdf\n\n\n\nasdf\nasdf\nasdf\nasdf";
    getch();
    char hint[] = "钱夫人>";
    char buf[1024];
    get_input(hint, COLOR_P1, buf, 1024);
    getch();
    endwin();
    printf("%s\n", buf);
    exit(0);
}

