#include "GameState.h"
#include "Playfield.h"
#include "IRenderer.h"
#include "Tetrimino.h"

float Aggrotech::GameState::SecondsPerGameTick = 0.75f;
float Aggrotech::GameState::CollisionWiggleSeconds = 1.0f;

Aggrotech::GameState::GameState()
    : currentTetrimino(NULL), nextTetrimino(NULL), currentFrameTime(0.0f), currentScore(0)
{
    playfield = new Playfield(Playfield::DefaultWidth, Playfield::DefaultHeight);

    nextTetrimino = Tetrimino::CreateRandomTetrimino();
    SpawnTetrimino();
}

Aggrotech::GameState::~GameState()
{
    if (playfield)
    {
        delete playfield;
        playfield = NULL;
    }

    if (currentTetrimino)
    {
        delete currentTetrimino;
        currentTetrimino = NULL;
    }
}

void Aggrotech::GameState::Render(IRenderer &renderer)
{
    renderer.RenderPlayfield(*playfield);
    renderer.RenderScore(currentScore);

    if (currentTetrimino != NULL)
    {
        renderer.RenderTetrimino(*currentTetrimino);
    }

    renderer.RenderNextTetrimino(*nextTetrimino);
}

void Aggrotech::GameState::ExecuteFrame(float dt)
{
    currentFrameTime += dt;

    if (currentFrameTime >= SecondsPerGameTick)
    {
        TryMoveTetriminoDown();
        currentFrameTime = 0.0f;
    }
}

void Aggrotech::GameState::TryMoveTetriminoLeft()
{
    if (currentTetrimino)
    {
        int x = currentTetrimino->GetX();

        if (x > 0)
        {
            currentTetrimino->SetX(x - 1);

            if (playfield->IsTetriminoInCollision(*currentTetrimino))
            {
                currentTetrimino->SetX(x);
            }
        }
    }
}

void Aggrotech::GameState::TryMoveTetriminoRight()
{
    if (currentTetrimino)
    {
        unsigned int x = currentTetrimino->GetX();
        unsigned int width = currentTetrimino->GetWidth();

        if (x + width < playfield->GetWidth())
        {
            currentTetrimino->SetX(x + 1);

            if (playfield->IsTetriminoInCollision(*currentTetrimino))
            {
                currentTetrimino->SetX(x);
            }
        }
    }
}

void Aggrotech::GameState::TryRotateTetriminoClockwise()
{
    if (currentTetrimino)
    {
        currentTetrimino->RotateClockwise();
    }
}

void Aggrotech::GameState::TryMoveTetriminoDown()
{
    if (currentTetrimino)
    {
        unsigned int y = currentTetrimino->GetY();
        unsigned int height = currentTetrimino->GetHeight();

        if (y + height >= playfield->GetHeight())
        {
            playfield->SetCellsFromTetrimino(*currentTetrimino);

            int affectedRows = playfield->ClearFilledAndReturnAffectedRows();

            if (affectedRows > 0)
            {
                IncrementScore(affectedRows);
            }
            
            SpawnTetrimino();

            return;
        }

        currentTetrimino->SetY(y + 1);

        if (playfield->IsTetriminoInCollision(*currentTetrimino))
        {
            currentTetrimino->SetY(y);

            playfield->SetCellsFromTetrimino(*currentTetrimino);

            int affectedRows = playfield->ClearFilledAndReturnAffectedRows();

            if (affectedRows > 0)
            {
                IncrementScore(affectedRows);
            }

            SpawnTetrimino();
        }
    }
}

void Aggrotech::GameState::SpawnTetrimino()
{
    if (currentTetrimino)
    {
        delete currentTetrimino;
    }

    currentTetrimino = nextTetrimino;

    nextTetrimino = Tetrimino::CreateRandomTetrimino();

    currentTetrimino->SetX(0);
    currentTetrimino->SetY(0);
}

int Aggrotech::GameState::GetCurrentScore()
{
    return currentScore;
}

void Aggrotech::GameState::IncrementScore(int rowsAffected)
{
    int score = 0;

    switch (rowsAffected)
    {
    case 4:
        score = 1200;
        break;

    case 3:
        score = 300;
        break;

    case 2:
        score = 100;
        break;

    case 1:
        score = 40;
        break;

    default:
        score = 40;
        break;
    }

    currentScore += score;
}
