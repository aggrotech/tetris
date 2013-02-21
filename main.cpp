// http://tetris.wikia.com/wiki/Tetris_Guideline

#include "Win32ConsoleRenderer.h"
#include "Playfield.h"
#include "Cell.h"
#include "Timer.h"
#include "GameState.h"
#include "IRenderer.h"
#include "Input.h"
#include <cstdlib>
#include <cstdio>


void GameLoop()
{
    Aggrotech::GameState gameState;
    Aggrotech::Timer gameTicker;
    Aggrotech::Win32ConsoleRenderer renderer;
    Aggrotech::Input input;

    float inputDelay = 0;

    while (!input.IsQuit())
    {
        input.Update();

        gameTicker.Tick();
        float delta = gameTicker.GetDeltaSinceLastTick();

        inputDelay += delta;

        if (inputDelay > 0.075f)
        {
            if (input.IsMoveLeft())
            {
                gameState.TryMoveTetriminoLeft();
            }

            if (input.IsMoveRight())
            {
                gameState.TryMoveTetriminoRight();
            }

            if (input.IsRotateRight())
            {
                gameState.TryRotateTetriminoClockwise();
            }

            inputDelay = 0.0f;
        }

        gameState.ExecuteFrame(delta);
        gameState.Render(renderer);
    }
}

int main(int argc, char *argv[])
{
    ::SetConsoleTitle(L"Aggrotech::Tetris");

    GameLoop();

    return EXIT_SUCCESS;
}
