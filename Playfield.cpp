#include "Playfield.h"
#include "Cell.h"
#include "Tetrimino.h"
#include <cassert>

const int Aggrotech::Playfield::DefaultWidth = 10;
const int Aggrotech::Playfield::DefaultHeight = 20;


Aggrotech::Playfield::Playfield(unsigned int width, unsigned int height)
    : width(width), height(height)
{
    assert(width > 0 && height > 0);
    cells.resize(width * height, NULL);
}

Aggrotech::Playfield::~Playfield()
{
    std::vector< Cell* >::iterator currentIterator = cells.begin();
    std::vector< Cell* >::iterator endIterator = cells.end();

    while(currentIterator != endIterator)
    {
        Cell* cell = *currentIterator;

        if(cell != NULL)
        {
            delete cell;
        }
    }
}

unsigned int Aggrotech::Playfield::GetWidth()
{
    return width;
}

unsigned int Aggrotech::Playfield::GetHeight()
{
    return height;
}

Aggrotech::Cell *Aggrotech::Playfield::GetCellAt(unsigned int x, unsigned int y)
{
    unsigned int arrayCellLocation = (y * width) + x;

    assert(arrayCellLocation < cells.size());

    return cells[arrayCellLocation];
}

Aggrotech::Cell *Aggrotech::Playfield::SetAndGetPreviousCellAt(unsigned int x, unsigned int y, Cell *cell)
{
    Cell *previousCell = GetCellAt(x, y);

    cells[(y * width) + x] = cell;

    return previousCell;
}

void Aggrotech::Playfield::SetCellsFromTetrimino(Aggrotech::Tetrimino &tetrimino)
{
    TetriminoShape shapeMatrix = tetrimino.GetShapeMatrix();

    int originX = tetrimino.GetX();
    int originY = tetrimino.GetY();

    for (unsigned int y = 0; y < shapeMatrix.size(); y++)
    {
        for (unsigned int x = 0; x < shapeMatrix[y].size(); x++)
        {
            if (shapeMatrix[y][x])
            {
                int finalX = originX + x;
                int finalY = originY + y;

                Cell *cell = new Cell();
                SetAndGetPreviousCellAt(finalX, finalY, cell);
            }
        }
    }
}

bool Aggrotech::Playfield::IsTetriminoInCollision(Aggrotech::Tetrimino &tetrimino)
{
    TetriminoShape shapeMatrix = tetrimino.GetShapeMatrix();

    int originX = tetrimino.GetX();
    int originY = tetrimino.GetY();

    for (int y = 0; y < shapeMatrix.size(); y++)
    {
        for (int x = 0; x < shapeMatrix[y].size(); x++)
        {
            if (shapeMatrix[y][x])
            {
                int finalX = originX + x;
                int finalY = originY + y;

                if (GetCellAt(finalX, finalY))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int Aggrotech::Playfield::ClearFilledAndReturnAffectedRows()
{
    std::vector< unsigned int > fullLineYIndices;

    for (unsigned int y = 0; y < height; y++)
    {
        bool fullLineFound = true;

        for (unsigned int x = 0; x < width; x++)
        {
            if (GetCellAt(x, y) == NULL)
            {
                fullLineFound = false;
            }
        }

        if (fullLineFound)
        {
            fullLineYIndices.push_back(y);
        }
    }

    std::vector< unsigned int>::const_iterator it = fullLineYIndices.begin();

    while (it != fullLineYIndices.end())
    {
        for (unsigned int x = 0; x < width; x++)
        {
            SetAndGetPreviousCellAt(x, *it, NULL);
        }

        it++;
    }

    return fullLineYIndices.size();
}

void Aggrotech::Playfield::DropCells()
{

}
