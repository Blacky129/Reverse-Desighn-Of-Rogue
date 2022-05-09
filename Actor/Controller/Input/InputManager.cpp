#include "InputManager.h"

CInputManager::~CInputManager()
{
    delete Input;
}

bool CInputManager::initInput()
{
    if(SDL_Init(SDL_INIT_EVENTS))
        return false;

    Input = new SDL_Event;
    return true;
}

InputType CInputManager::getInput()
{
    
    while (SDL_WaitEvent(this->Input) != 0)
    {
        if (this->Input == NULL)
            continue;

        if (this->Input->type == SDL_QUIT)
            return InputType::Quit;


        if (this->Input->type != SDL_KEYDOWN)
            break;

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W])
            return InputType::MovementUp;
        else if (currentKeyStates[SDL_SCANCODE_X])
            return InputType::MovementDown;
        else if (currentKeyStates[SDL_SCANCODE_A])
            return InputType::MovementLeft;
        else if (currentKeyStates[SDL_SCANCODE_D])
            return InputType::MovementRight;
        else if (currentKeyStates[SDL_SCANCODE_Q])
            return InputType::MovementUpLeft;
        else if (currentKeyStates[SDL_SCANCODE_E])
            return InputType::MovementUpRight;
        else if (currentKeyStates[SDL_SCANCODE_Z])
            return InputType::MovementDownLeft;
        else if (currentKeyStates[SDL_SCANCODE_C])
            return InputType::MovementDownRight;
        else if (currentKeyStates[SDL_SCANCODE_S])
            return InputType::ExitLevel;
    }
    return InputType::Null;
}
