#include "Input.h"
#include <Windows.h>


Aggrotech::Input::Input()
    : leftDown(false), rightDown(false), rotateRight(false), rotateLeft(false), quit(false)
{

}

void Aggrotech::Input::Update()
{
    leftDown = GetAsyncKeyState(VK_LEFT) < 0;
    rightDown = GetAsyncKeyState(VK_RIGHT) < 0;

    rotateRight = GetAsyncKeyState(VK_SPACE) < 0;
    rotateLeft = false;

    quit = GetAsyncKeyState(VK_ESCAPE) < 0;
}

bool Aggrotech::Input::IsMoveLeft()
{
    return leftDown;
}

bool Aggrotech::Input::IsMoveRight()
{
    return rightDown;
}

bool Aggrotech::Input::IsRotateRight()
{
    return rotateRight;
}

bool Aggrotech::Input::IsRotateLeft()
{
    return rotateLeft;
}

bool Aggrotech::Input::IsQuit()
{
    return quit;
}
