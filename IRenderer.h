#pragma once

namespace Aggrotech
{
    // Forward decl.
    class Playfield;
    class Tetrimino;

    class IRenderer
    {
    public:

        virtual ~IRenderer() { }

        virtual void RenderPlayfield(Playfield &field) = 0;

        virtual void RenderTetrimino(Tetrimino &tetrimino) = 0;

        virtual void RenderNextTetrimino(Tetrimino &nextTetrimino) = 0;

        virtual void RenderScore(int currentScore) = 0;
    };
}
