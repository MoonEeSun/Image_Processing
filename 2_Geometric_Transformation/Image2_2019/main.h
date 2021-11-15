#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS


#define WIDTH      512              // 영상의 가로 크기
#define HEIGHT     512              // 영상의 세로 크기

#define scaleConstant  2.32         // 스케일링 상수 - 축소/확대

// 흑백영상 range (0~255)
#define maxVal    255
#define minVal    0

typedef unsigned char UChar;
typedef char          Char;
typedef double		  Double;
typedef int           Int;

