#pragma once
#include<stdio.h>
#include <stdlib.h>
#include<Windows.h>
#include<conio.h>
#include <time.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>;


enum Color
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGRAY,
    DARKGRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

//키보드 정의
#define UP  10
#define DOWN  11
#define RIGHT  13
#define LEFT  14
#define SPACE 15
#define ESC 16


#define WIDTH 100
#define HEIGHT 28
#define BNum 5

typedef struct
{
    int x;
    int y;

    int con;
}Hurdle;