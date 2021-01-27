#include<stdio.h>
#include"katachar.h"

Kata CharToKata(char Line[]){
    Kata currkata;
    int i = 0;

    while (Line[i] != '\n' && Line[i] != '\0'){
        currkata.TabKata[i] = Line[i];
        i++;
    }
    currkata.Length = i;
    
    return currkata;
}