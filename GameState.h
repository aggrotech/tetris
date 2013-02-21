#pragma once

namespace Aggrotech
{
    // Forward decl.
    class Playfield;
    class Tetrimino;
    class IRenderer;

    class GameState
    {
    public:

        GameState();

        ~GameState();

        static float SecondsPerGameTick;
        static float CollisionWiggleSeconds;

        void ExecuteFrame(float dt);

        void Render(IRenderer &renderer);

        void TryMoveTetriminoLeft();
        void TryMoveTetriminoRight();
        void TryRotateTetriminoClockwise();

        void SpawnTetrimino();

        int GetCurrentScore();

    private:

        void TryMoveTetriminoDown();
        void IncrementScore(int rowsAffected);

        Playfield *playfield;
        Tetrimino *currentTetrimino;
        Tetrimino *nextTetrimino;

        float currentFrameTime;
        int currentScore;
    };
}
