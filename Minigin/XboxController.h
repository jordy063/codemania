#pragma once
#include <Xinput.h>
class xboxController {
private:

public:
    //overloaded constructor
    xboxController(int i);

    bool checkButtonPress(WORD press);
    XINPUT_STATE getState();
private:
    int m_ID;
    XINPUT_STATE controllerState;
};

