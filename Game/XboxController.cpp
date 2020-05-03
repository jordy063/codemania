#include "MiniginPCH.h"
#include "XboxController.h"
xboxController::xboxController(int i)
    :m_ID{i}
{
    
}
bool xboxController::checkButtonPress(WORD press) {
    return (controllerState.Gamepad.wButtons & press) != 0;
}
XINPUT_STATE xboxController::getState() {
    //Understand what these lines are doing, and how to use them for your own needs.
    ZeroMemory(&controllerState, sizeof(XINPUT_STATE));
    XInputGetState(m_ID, &controllerState);
    return controllerState;
}