#pragma once

#include <vector>

namespace Aggrotech
{
    // Forward decl.
    class Cell;
    class Tetrimino;

    class Playfield
    {
    public:

        static const int DefaultWidth;
        static const int DefaultHeight;

        Playfield(unsigned int width, unsigned int height);
        ~Playfield();

        unsigned int GetWidth();
        unsigned int GetHeight();

        Cell *GetCellAt(unsigned int x, unsigned int y);
        Cell *SetAndGetPreviousCellAt(unsigned int x, unsigned int y, Cell *cell);

        void SetCellsFromTetrimino(Tetrimino &tetrimino);
        bool IsTetriminoInCollision(Tetrimino &tetrimino);

        int ClearFilledAndReturnAffectedRows();
        void DropCells();

    private:

        std::vector< Cell* > cells;

        unsigned int width;
        unsigned int height;
    };
}
