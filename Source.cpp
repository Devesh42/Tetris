#include <iostream>
#include <sstream>
#include <Windows.h>
#include <thread>
using namespace std;

wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
int nScreenWidth = 80;
int nScreenHeight = 30;
unsigned char *pField = nullptr;


int Rotate(int px, int py, int r)
{
    switch (r%4)
    {
        case 0: return py * 4 + px;
        case 1: return 12 + py - (px * 4);
        case 2: return 15 - (py * 4) - px;
        case 3: return 3 - py + (px * 4);
    } 
    return 0;
}

bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY)
{
    
}

int main()
{
    //create assets

    //shape I
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");
    tetromino[0].append(L"..X.");

    //shape S
    tetromino[1].append(L"..X.");
    tetromino[1].append(L".XX.");
    tetromino[1].append(L".X..");
    tetromino[1].append(L"....");

    //shape Z
    tetromino[2].append(L".X..");
    tetromino[2].append(L".XX.");
    tetromino[2].append(L"..X.");
    tetromino[2].append(L"....");

    //shape O
    tetromino[3].append(L"....");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L".XX.");
    tetromino[3].append(L"....");

    //shape T
    tetromino[4].append(L"..X.");
    tetromino[4].append(L".XX.");
    tetromino[4].append(L"..X.");
    tetromino[4].append(L"....");

    //shape J
    tetromino[5].append(L"..X.");
    tetromino[5].append(L"..X.");
    tetromino[5].append(L".XX.");
    tetromino[5].append(L"....");

    //shape L
    tetromino[6].append(L".X..");
    tetromino[6].append(L".X..");
    tetromino[6].append(L".XX.");
    tetromino[6].append(L"....");

    pField = new unsigned char[nFieldWidth * nFieldHeight];
    for(int x = 0; x < nFieldWidth; x++)
    {
        for(int y = 0; y < nFieldHeight; y++)
        {
            pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth-1 || y == 0 || y == nFieldHeight -1)? 9 : 0;
        }
    }

    wchar_t *screen = new wchar_t[nScreenWidth * nScreenHeight];
    for(int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';

    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    //Game Logic state
    bool bGameOver = false;
    bool bKey[4] = {false};
    int nCurrentPiece = 3;
    int nCurrentRotation = 0;
    int nCurrentX = nFieldWidth/2;
    int nCurrentY = 1;


    while(!bGameOver)
    {


        //Game Timing
        this_thread::sleep_for(50ms);

        //Input
        for(int k=0; k < 4; k++)
        {
            bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;
        }

        //Game Logic



        //Display Frame
        //1. Update Screen Buffer (nFieldWidth x nFieldHeight) part
        //2. Write to console output
        nCurrentPiece = 0;
        for(int x = 0; x < nFieldWidth; x++)
            for(int y = 0; y < nFieldHeight; y++)
            {
                screen[(y)*nScreenWidth + (x)] = L" ABCDEFG=#"[pField[y*nFieldWidth + x]];
            }

        for(int px =0; px < 4; px++){
            for(int py =0; py < 4; py++){
                if(tetromino[nCurrentPiece][Rotate(px,py,nCurrentRotation)] == L'X'){
                    screen[nCurrentX + nScreenWidth*(nCurrentY + py) + px] = nCurrentPiece + 'A';
                }
            }
        }
        WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, {0,0}, &dwBytesWritten);
    }
}