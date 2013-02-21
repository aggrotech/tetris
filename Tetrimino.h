#pragma once

#include <vector>

namespace Aggrotech
{
    typedef std::vector< std::vector< bool > > TetriminoShape;

    class Tetrimino
    {
    public:

        static Tetrimino *CreateStraightPolyomino();
        static Tetrimino *CreateSquarePolyomino();
        static Tetrimino *CreateTPolyomino();
        static Tetrimino *CreateJPolyomino();
        static Tetrimino *CreateLPolyomino();
        static Tetrimino *CreateSPolyomino();
        static Tetrimino *CreateZPolyomino();

        static Tetrimino *CreateRandomTetrimino();

        Tetrimino(int color, TetriminoShape shapeMatrix);

        TetriminoShape &GetShapeMatrix();
        int GetColor();

        void SetX(int x);
        void SetY(int y);
        int GetX();
        int GetY();
        int GetWidth();
        int GetHeight();

        void RotateClockwise();

    private:

        int x;
        int y;
        int calculatedWidth;
        int calculatedHeight;
        TetriminoShape shapeMatrix;
        int color;
    };
}
