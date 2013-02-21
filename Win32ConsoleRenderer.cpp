#include "Win32ConsoleRenderer.h"
#include "Playfield.h"
#include "Tetrimino.h"
#include "Cell.h"

Aggrotech::Win32ConsoleRenderer::Win32ConsoleRenderer()
{
    consoleHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
}

Aggrotech::Win32ConsoleRenderer::~Win32ConsoleRenderer()
{
    ::CloseHandle(consoleHandle);
}

void Aggrotech::Win32ConsoleRenderer::RenderPlayfield(Playfield &playfield)
{
    RenderEmbellishments();

    for (unsigned int x = 0; x < playfield.GetWidth(); ++x)
    {
        for (unsigned int y = 0; y < playfield.GetHeight(); ++y)
        {
            Cell *cell = playfield.GetCellAt(x, y);

            RenderCell(x + 1, y + 1, cell);
        }
    }

    COORD charBufSize = {12,22};
    COORD characterPos = {0,0};
    SMALL_RECT writeArea = {0,0,11,21};

    WriteConsoleOutputA(consoleHandle, consoleBuffer, charBufSize, characterPos, &writeArea);

    COORD charBufSize2 = {20,6};
    COORD characterPos2 = {0,0};
    SMALL_RECT writeArea2 = {14,0,34,6};

    WriteConsoleOutputA(consoleHandle, sidebarBuffer, charBufSize2, characterPos2, &writeArea2);

    ClearBuffer();
}

void Aggrotech::Win32ConsoleRenderer::RenderTetrimino(Tetrimino &tetrimino)
{
    int topX = tetrimino.GetX() + 1;
    int leftY = tetrimino.GetY() + 1;
    
    TetriminoShape &shape = tetrimino.GetShapeMatrix();

    for (size_t y = 0; y < shape.size(); y++)
    {
        for (size_t x = 0; x < shape[y].size(); x++)
        {
            if (shape[y][x])
            {
                int pos = (topX + x) + 12 * (leftY + y);

                consoleBuffer[pos].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                consoleBuffer[pos].Char.AsciiChar = '+';
            }
        }
    }
}

void Aggrotech::Win32ConsoleRenderer::RenderNextTetrimino(Tetrimino &nextTetrimino)
{
    TetriminoShape &shape = nextTetrimino.GetShapeMatrix();

    for (size_t y = 0; y < shape.size(); y++)
    {
        for (size_t x = 0; x < shape[y].size(); x++)
        {
            if (shape[y][x])
            {
                int pos = x + (20 * (y + 2));
                sidebarBuffer[pos].Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
                sidebarBuffer[pos].Char.AsciiChar = '+';
            }
        }
    }
}

void Aggrotech::Win32ConsoleRenderer::RenderScore(int currentScore)
{
    char scoreText[20];

    sprintf(scoreText, "Score: %d", currentScore);

    for (int i = 0; scoreText[i] != '\0'; i++)
    {
        sidebarBuffer[i].Char.AsciiChar = scoreText[i];
    }
}

void Aggrotech::Win32ConsoleRenderer::RenderCell(unsigned int x, unsigned int y, Cell *cell)
{
    if (cell == NULL)
    {
        return;
    }

    int pos = x + 12 * y;

    consoleBuffer[pos].Attributes = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    consoleBuffer[pos].Char.AsciiChar = '#';
}

void Aggrotech::Win32ConsoleRenderer::RenderEmbellishments()
{
    consoleBuffer[0].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    consoleBuffer[0].Char.AsciiChar = 0xC9;

    for (int i = 1; i < 11; i++)
    {
        consoleBuffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        consoleBuffer[i].Char.AsciiChar = 0xCD;
    }

    consoleBuffer[11].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    consoleBuffer[11].Char.AsciiChar = 0xBB;

    for (int i = 1; i < 21; i++)
    {
        consoleBuffer[12 * i].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        consoleBuffer[12 * i].Char.AsciiChar = 0xBA;
    }

    for (int i = 1; i < 21; i++)
    {
        consoleBuffer[11 + 12 * i].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        consoleBuffer[11 + 12 * i].Char.AsciiChar = 0xBA;
    }

    consoleBuffer[12 * 21].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    consoleBuffer[12 * 21].Char.AsciiChar = 0xC8;

    consoleBuffer[11 + 12 * 21].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    consoleBuffer[11 + 12 * 21].Char.AsciiChar = 0xBC;

    for (int i = 1; i < 11; i++)
    {
        consoleBuffer[i + 12 * 21].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        consoleBuffer[i + 12 * 21].Char.AsciiChar = 0xCD;
    }
}

void Aggrotech::Win32ConsoleRenderer::ClearBuffer()
{
    for (int i = 0; i < 12 * 22; i++)
    {
        consoleBuffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        consoleBuffer[i].Char.AsciiChar = 0;
    }

    for (int i = 0; i < 6 * 20; i++)
    {
        sidebarBuffer[i].Attributes = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
        sidebarBuffer[i].Char.AsciiChar = 0;
    }
}
