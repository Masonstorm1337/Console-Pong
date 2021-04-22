// Console-pong.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <chrono>
#include <thread>
#include <Windows.h>;

using namespace std;


int nScreenWidth = 120;
int nScreenHeight = 30;


int playerA = 15;
int playerB = 15;
int score = 0;
int ai;
int flatRander;
int projectialA[4] = { nScreenWidth / 2 , 15, 0, 0};
bool bKeyUp = false;
bool bKeyDown = false;



int main()
{
    wchar_t* screen = new wchar_t[nScreenWidth * nScreenWidth];
    for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    for (int x = 0; x < nScreenHeight; x++) {
        for (int y = 0; y < nScreenWidth; y++) {
            if (x < 2 || x > nScreenHeight - 3) screen[x * nScreenWidth + y] = L'X';
            if (y < 2 || y > nScreenWidth - 3) screen[x * nScreenWidth + y] = L'X';
        }
    }
    wsprintf(&screen[10], L"Masonstorm Pong                WIN LOSS: %d", score);
    screen[projectialA[0] + projectialA[1] * nScreenWidth] = L'O';
    projectialA[2] = rand() % 6 + 1;

    
    while (1) 
    {
        // timing 
        this_thread::sleep_for(50ms);
        // Get Input, 
        bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('\x28'))) != 0;
        bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('\x26'))) != 0;
        if (bKeyUp == true) playerA++;
        if (bKeyDown == true) playerA--;
        if (playerA < 2) playerA = 2;
        if (playerA > nScreenHeight - 5) playerA--;

        // AI
        
        ai = rand() % 10 + 1;
        if (ai > 7) {
            if (projectialA[1] > playerB) {
                playerB++;
            }
            else playerB--;


        }
                

        //Clear moved location
        for (int x = 2; x < nScreenHeight - 2; x++) {
            screen[nScreenWidth * x + 4] = L' ';
            screen[nScreenWidth * x + nScreenWidth - 6 ] = L' ';
        }

        screen[ projectialA[0] + projectialA[1] * nScreenWidth] =L' ';
        projectialA[3] = projectialA[2];
        
        
        
        switch (projectialA[2]) {
        case 1:
            projectialA[0] = projectialA[0] + 1;
            projectialA[1] = projectialA[1] + 0;
            break;
        case 2:
            projectialA[0] = projectialA[0] + 1;
            projectialA[1] = projectialA[1] + 1;
            break;
        case 3:
            projectialA[0] = projectialA[0] + 1;
            projectialA[1] = projectialA[1] - 1;
            break;
        case 4:
            projectialA[0] = projectialA[0] - 1;
            projectialA[1] = projectialA[1] + 0;
            break;
        case 5:
            projectialA[0] = projectialA[0] - 1;
            projectialA[1] = projectialA[1] + 1;
            break;
        case 6:
            projectialA[0] = projectialA[0] - 1;
            projectialA[1] = projectialA[1] - 1;
            break;

        
        }
        
        for (int x = 0; x < 3; x++) {
            screen[nScreenWidth * (playerA + x) + 4] = L'l';
            screen[nScreenWidth * (playerB + x) + nScreenWidth - 6] = L'l';
        }

        if (screen[projectialA[0] + projectialA[1] * nScreenWidth] == L'X'){
            if (projectialA[0] < 2) {
                score--; 
                projectialA[0] = nScreenWidth / 2;
                projectialA[1] = 15;
                projectialA[2] = rand() % 6 + 1 ;
                projectialA[3] = projectialA[2];
            } else if (projectialA[0] > nScreenWidth -3) {
                score++;
                projectialA[0] = nScreenWidth / 2;
                projectialA[1] = 15;
                projectialA[2] = rand() % 6 + 1;
                projectialA[3] = projectialA[2];
                
            }
            else {
                switch (projectialA[3]) {
                case 1:
                    projectialA[0] = projectialA[0] - 1;
                    projectialA[1] = projectialA[1] + 0;
                    flatRander = rand() % 3;
                    switch (flatRander) {
                    case 1:
                        projectialA[2] = 4;
                        break;
                    case 2:
                        projectialA[2] = 5;
                        break;
                    case 3:
                        projectialA[2] = 6;
                        break;
                    }
                    break;
                case 2:
                    projectialA[0] = projectialA[0] - 1;
                    projectialA[1] = projectialA[1] - 1;
                    projectialA[2] = 3;
                    break;
                case 3:
                    projectialA[0] = projectialA[0] - 1;
                    projectialA[1] = projectialA[1] + 1;
                    projectialA[2] = 2;
                    break;
                case 4:
                    projectialA[0] = projectialA[0] + 1;
                    projectialA[1] = projectialA[1] - 0;
                    flatRander = rand() % 3;
                    switch (flatRander) {
                    case 1:
                        projectialA[2] = 1;
                        break;
                    case 2:
                        projectialA[2] = 2;
                        break;
                    case 3:
                        projectialA[2] = 3;
                        break;
                    }
                    break;
                case 5:
                    projectialA[0] = projectialA[0] + 1;
                    projectialA[1] = projectialA[1] - 1;
                    projectialA[2] = 6;
                    break;
                case 6:
                    projectialA[0] = projectialA[0] + 1;
                    projectialA[1] = projectialA[1] + 1;
                    projectialA[2] = 5;
                    break;
                }
            }
                
        }

        if (screen[projectialA[0] + projectialA[1] * nScreenWidth] == L'l')
        {
            if (projectialA[0] >  5) {
                projectialA[0] = projectialA[0] - 10;
                projectialA[1] = projectialA[1] + 0;
                flatRander = rand() % 3 +1;
                    switch (flatRander) {
                    case 1:
                        projectialA[2] = 4;
                        break;
                    case 2:
                        projectialA[2] = 5;
                        break;
                    case 3:
                        projectialA[2] = 6;
                        break;
                        projectialA[3] = projectialA[2];
                    }
            }
            if (projectialA[0] < 5) 
            {
                projectialA[0] = projectialA[0] + 1;
                projectialA[1] = projectialA[1] + 0;
                flatRander = rand() % 3 + 1;
                    switch (flatRander)
                    {
                    case 1:
                        projectialA[2] = 1;
                        break;
                    case 2:
                        projectialA[2] = 2;
                        break;
                    case 3:
                        projectialA[2] = 3;
                        break;
                        projectialA[3] = projectialA[2];
                    }
            }
            }
        
            //projectialA[0] = nScreenWidth / 2;
            //projectialA[1] = 15;
            //projectialA[2] = rand() % 6 + 1;



        
        screen[projectialA[0] + projectialA[1] * nScreenWidth] = L'O';


        
        
        wsprintf(&screen[10], L"  Masonstorm Pong                WIN LOSS: %d", score);
        WriteConsoleOutputCharacter(hConsole, screen , nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
        
    }
  }


