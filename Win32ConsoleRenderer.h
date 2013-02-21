#pragma once

#include "IRenderer.h"
#include <Windows.h>

namespace Aggrotech
{
    // Forward decl
    class Cell;

    class Win32ConsoleRenderer : public IRenderer
    {
    public:

        Win32ConsoleRenderer();
        ~Win32ConsoleRenderer();

        virtual void RenderPlayfield(Playfield &field);
        virtual void RenderTetrimino(Tetrimino &tetrimino);
        virtual void RenderNextTetrimino(Tetrimino &nextTetrimino);
        virtual void RenderScore(int currentScore);

    private:

        void RenderCell(unsigned int x, unsigned int y, Cell *cell);
        void RenderEmbellishments();
        void ClearBuffer();

        ::HANDLE consoleHandle;

        ::CHAR_INFO consoleBuffer[12 * 22];
        ::CHAR_INFO sidebarBuffer[6 * 20];
    };
}
