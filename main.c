#include <stdio.h>
#include <string.h>
#include <math.h>
#include <windows.h> // カーソルを非表示にするために必要

void hideCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // カーソルを非表示に設定
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

int
    k;
double sin(), cos();

int main()
{
    hideCursor(); // カーソルを非表示にする

    float A = 0, B = 0, i, j;
    float z[1760];
    char b[1760];
    printf("\x1b[2J");

    // 事前に計算しておくことで毎回のループでの浮動小数点演算を削減
    float cosB, sinB, cosA, sinA, cosj, sinj, cosi, sini, D, l, t, h;
    int x, y, o, N;

    for (;;)
    {
        memset(b, 32, 1760);
        memset(z, 0, 7040);

        cosA = cos(A);
        sinA = sin(A);
        cosB = cos(B);
        sinB = sin(B);

        for (j = 0; 6.28 > j; j += 0.07)
        {
            cosj = cos(j);
            sinj = sin(j);
            h = cosj + 2;

            for (i = 0; 6.28 > i; i += 0.02)
            {
                cosi = cos(i);
                sini = sin(i);

                // 計算の一部を事前にしておく
                D = 1 / (sini * h * sinA + sinj * cosA + 5);
                l = cosi;
                t = sini * h * cosA - sinj * sinA;

                x = 40 + 30 * D * (l * h * cosB - t * sinB);
                y = 12 + 15 * D * (l * h * sinB + t * cosB);
                o = x + 80 * y;
                N = 8 * ((sinj * sinA - sini * cosj * cosA) * cosB - sini * cosj * sinA - sinj * cosA - l * cosj * sinB);

                if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o])
                {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }

        printf("\x1b[H"); // カーソル位置をホームに戻す
        for (k = 0; 1761 > k; k++)
        {
            putchar(k % 80 ? b[k] : 10); // 80文字ごとに改行
        }

        // 更新速度を少し速くするため、増分を変更
        A += 0.07;
        B += 0.03;
    }
}
