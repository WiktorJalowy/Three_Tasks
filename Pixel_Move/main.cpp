#include <iostream>
#include <chrono>
#include <cmath>
#include <thread>
#if _WIN32
#include <windows.h>
#endif


using namespace std;


class Screen
{
public:
        Screen()
        {
#ifdef _WIN32
                _hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
#endif
                hideCursor();
                saveCursorPosition();
        }


        void clear()
        {
                for(int i = 0; i < height; i++)
                {
                        for(int j = 0; j < width; j++)
                        {
                                _screen[i][j]='x';
                        }
                }
        }


        void draw(char value, float x, float y)
        {
                int xPos = lround(x);
                int yPos = lround(y);
                if(xPos < width && yPos < height)
                {
                        _screen[yPos][xPos]=value;
                }
        }


        void flush()
        {
                restoreCursorPosition();


                for(int i = 0; i < height; i++)
                {
                        for(int j = 0; j < width; j++)
                        {
                                if(_screen[i][j]!='x')
                                {
                                        setRedFont();
                                }
                                else
                                {
                                        setWhiteFont();
                                }
                                cout << _screen[i][j];
                        }
                        cout << "\n";
                }
        }


private:
        void hideCursor()
        {
#ifdef _WIN32
                CONSOLE_CURSOR_INFO cursorInfo; 
                GetConsoleCursorInfo(_hConsole, &cursorInfo);
                cursorInfo.dwSize = 1;
                cursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(_hConsole, &cursorInfo);
#else
                cout << "\33[?25l";//disable cursor
#endif


        }


        void saveCursorPosition()
        {
#ifdef _WIN32
                CONSOLE_SCREEN_BUFFER_INFO coninfo;
                GetConsoleScreenBufferInfo(_hConsole, &coninfo);
                _prevPos = coninfo.dwCursorPosition;
#else
                cout << "\33[s";
#endif
                
        }


        void restoreCursorPosition()
        {
#ifdef _WIN32
                SetConsoleCursorPosition(_hConsole, _prevPos);
#else
                cout << "\338";
#endif
        }


        void setRedFont()
        {
#ifdef _WIN32
                WORD attributes = FOREGROUND_RED;
                SetConsoleTextAttribute(_hConsole, attributes);
#else
                cout << "\33[31m";//red color
#endif
        }


        void setWhiteFont()
        {
#ifdef _WIN32
                WORD attributes = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE;
                SetConsoleTextAttribute(_hConsole, attributes);
#else
                cout << "\33[37m";//white color
#endif
        }


        static constexpr int width{60};
        static constexpr int height{20};
        char _screen[height][width];
#ifdef _WIN32
        HANDLE _hConsole;
        COORD _prevPos;
#endif
};


struct Position
{
        float x;
        float y;
};


using Pixel = char;


class Engine
{
public:
        void update(chrono::milliseconds deltaTime)
        {
                float timer = deltaTime.count() % 6000;
                if(timer <= 2000)
                {
                        position.x = timer / 50;
                }
                else if(timer <= 5000)
                {
                        position.y = (timer - 2000) / 300;
                }
                else if(timer <= 6000)
                {
                        position.x = 40 - ((timer - 5000) / 25);
                        position.y = 10 - ((timer - 5000) / 100);
                }
        }

        void render(Screen& screen)
        {
                screen.draw(pixel, position.x, position.y);
        }
private:
        Pixel pixel{1};
        Position position{0.0f, 0.0f};
};


int main()
{
        Engine engine;
        Screen screen;


        auto startTime = chrono::high_resolution_clock::now();
        while(1)
        {
                auto now = chrono::high_resolution_clock::now();
                auto deltaTime = chrono::duration_cast<chrono::milliseconds>(now - startTime);
                if(deltaTime >=20ms)
                {
                        screen.clear();
                        engine.update(deltaTime);
                        engine.render(screen);
                        screen.flush();
                        startTime = now;
                }
        }


        return 0;
}