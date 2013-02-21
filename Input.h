#pragma once

namespace Aggrotech
{
    class Input
    {
    public:

        Input();

        void Update();

        bool IsMoveLeft();
        bool IsMoveRight();

        bool IsRotateLeft();
        bool IsRotateRight();

        bool IsQuit();

    private:

        bool leftDown;
        bool rightDown;

        bool rotateLeft;
        bool rotateRight;

        bool quit;
    };
}
