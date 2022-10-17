#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "display.h"

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

int main(void){
    init_display();
    char * map = initMap();
    display_map(29, 8, map);
    refresh();
    // for(int i = 0; i < 70; ++i){
    //     change_map(i, '0'+i, COLOR_BASIC);
    //     getch();
    // }
    getch();
    char * buf = (char *)calloc(1, 10);
    char hint[] = "钱夫人>";
    do{
        get_input(hint, COLOR_P1, buf, 10);
    }while(buf[0] != 'q');
    endwin();

    exit(0);
}

