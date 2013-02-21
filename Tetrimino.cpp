#include "Tetrimino.h"

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateStraightPolyomino()
{
    TetriminoShape shape;

    std::vector<bool> row1;

    row1.push_back(true);
    row1.push_back(true);
    row1.push_back(true);
    row1.push_back(true);

    shape.push_back(row1);

    Tetrimino *tetrimino = new Tetrimino(0, shape);

    return tetrimino;
}

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateSquarePolyomino()
{
    TetriminoShape shape;

    std::vector<bool> row1;

    row1.push_back(true);
    row1.push_back(true);

    shape.push_back(row1);
    shape.push_back(row1);

    Tetrimino *tetrimino = new Tetrimino(0, shape);

    return tetrimino;
}

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateTPolyomino()
{
    TetriminoShape shape;

    std::vector<bool> row1;
    std::vector<bool> row2;

    row1.push_back(true);
    row1.push_back(true);
    row1.push_back(true);

    row2.push_back(false);
    row2.push_back(true);
    row2.push_back(false);

    shape.push_back(row1);
    shape.push_back(row2);

    Tetrimino *tetrimino = new Tetrimino(0, shape);

    return tetrimino;
}

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateJPolyomino()
{
    TetriminoShape shape;

    std::vector<bool> row1;
    std::vector<bool> row2;

    row1.push_back(true);
    row1.push_back(true);
    row1.push_back(true);

    row2.push_back(false);
    row2.push_back(false);
    row2.push_back(true);

    shape.push_back(row1);
    shape.push_back(row2);

    Tetrimino *tetrimino = new Tetrimino(0, shape);

    return tetrimino;
}

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateLPolyomino()
{
    TetriminoShape shape;

    std::vector<bool> row1;
    std::vector<bool> row2;

    row1.push_back(true);
    row1.push_back(true);
    row1.push_back(true);

    row2.push_back(true);
    row2.push_back(false);
    row2.push_back(false);

    shape.push_back(row1);
    shape.push_back(row2);

    Tetrimino *tetrimino = new Tetrimino(0, shape);

    return tetrimino;
}

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateSPolyomino()
{
    TetriminoShape shape;

    std::vector<bool> row1;
    std::vector<bool> row2;

    row1.push_back(false);
    row1.push_back(true);
    row1.push_back(true);

    row2.push_back(true);
    row2.push_back(true);
    row2.push_back(false);

    shape.push_back(row1);
    shape.push_back(row2);

    Tetrimino *tetrimino = new Tetrimino(0, shape);

    return tetrimino;
}

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateZPolyomino()
{
    TetriminoShape shape;

    std::vector<bool> row1;
    std::vector<bool> row2;

    row1.push_back(true);
    row1.push_back(true);
    row1.push_back(false);

    row2.push_back(false);
    row2.push_back(true);
    row2.push_back(true);

    shape.push_back(row1);
    shape.push_back(row2);

    Tetrimino *tetrimino = new Tetrimino(0, shape);

    return tetrimino;
}

Aggrotech::Tetrimino *Aggrotech::Tetrimino::CreateRandomTetrimino()
{
    Tetrimino *t = NULL;

    int tetriminoIndex = rand() % 7;

    switch (tetriminoIndex)
    {
    case 0:
        t = Tetrimino::CreateStraightPolyomino();
        break;

    case 1:
        t = Tetrimino::CreateSquarePolyomino();
        break;

    case 2:
        t = Tetrimino::CreateTPolyomino();
        break;

    case 3:
        t = Tetrimino::CreateSPolyomino();
        break;

    case 4:
        t = Tetrimino::CreateZPolyomino();
        break;

    case 5:
        t = Tetrimino::CreateJPolyomino();
        break;

    case 6:
        t = Tetrimino::CreateLPolyomino();
        break;
    }

    return t;
}

Aggrotech::Tetrimino::Tetrimino(int color, Aggrotech::TetriminoShape shapeMatrix)
    : color(color), shapeMatrix(shapeMatrix), x(0), y(0), calculatedWidth(-1), calculatedHeight(-1)
{

}

Aggrotech::TetriminoShape &Aggrotech::Tetrimino::GetShapeMatrix()
{
    return shapeMatrix;
}

int Aggrotech::Tetrimino::GetColor()
{
    return color;
}

void Aggrotech::Tetrimino::SetX(int x)
{
    this->x = x;
}

void Aggrotech::Tetrimino::SetY(int y)
{
    this->y = y;
}

int Aggrotech::Tetrimino::GetX()
{
    return x;
}

int Aggrotech::Tetrimino::GetY()
{
    return y;
}

int Aggrotech::Tetrimino::GetWidth()
{
    if (calculatedWidth == -1)
    {
        for (int y = 0; y < shapeMatrix.size(); y++)
        {
            int currentSize = shapeMatrix[y].size();

            if (currentSize > calculatedWidth)
            {
                calculatedWidth = currentSize;
            }
        }
    }

    return calculatedWidth;
}

int Aggrotech::Tetrimino::GetHeight()
{
    if (calculatedHeight == -1)
    {
        calculatedHeight = shapeMatrix.size();
    }

    return calculatedHeight;
}

void Aggrotech::Tetrimino::RotateClockwise()
{
    int newWidth = GetHeight();
    int newHeight = GetWidth();
    std::vector< std::vector < bool > > newShapeMatrix;

    for (int i = 0; i < newHeight; i++)
    {
        std::vector < bool > values;

        for (int j = 0; j < newWidth; j++)
        {
            values.push_back(false);
        }

        newShapeMatrix.push_back(values);
    }

    for (int y = 0; y < shapeMatrix.size(); y++)
    {
        for (int x = 0; x < shapeMatrix[y].size(); x++)
        {
            int newY = 1 - (x - (GetWidth() - 2)); // http://stackoverflow.com/a/1996506
            newShapeMatrix[newY][y] = shapeMatrix[y][x];
        }
    }

    shapeMatrix = newShapeMatrix;
    calculatedWidth = -1;
    calculatedHeight = -1;
}
