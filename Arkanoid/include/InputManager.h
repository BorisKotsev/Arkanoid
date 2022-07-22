#pragma once

#include <utility>

#include <SDL.h>
#include <fstream>
#include <string>

#include "defines.h"
#include "Engine.h"

/*
* \brief input handler
* In order to use this class first you must init it from the World
* if you need any variable you can pass it by reference
* don't call SDL_PollEvent or SDL_GetKeyboardState anywhere else
*/

class InputManager
{
public:
    InputManager();
    ~InputManager();

    static int2 m_mouseCoor;
    static bool m_drag;

    static const Uint8* m_keyboardState;

    int m_scroll;

    void handleInput(); //< call the SDL_PollEvent fnc and update all variables
    void setMouseMultiply(float2 multiplier); //< multiply the mouseCoor corespondingly to the screen resolution

    static bool mouseIsPressed();	
    static bool mouseIsHolded();

private:
    SDL_Event m_event;

    float2 m_mouseMultiply;

    int2 m_screenCenter;

    static bool m_mouseIsPressed;
    static bool m_mouseIsDoubleClicked;
    // mouse is being pressed for first time
    static bool m_mouseOnClick;
    static bool m_mouseOnRelease;
    static bool m_mouseIsPressedPrevFrame;
    static bool m_mouseIsHolded;
};

bool isMouseInRect(SDL_Rect rect);
bool mouseIsPressed();
bool isAnyKeyPressed();