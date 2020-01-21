//
// Created by RH on 21/01/2020.
//

#ifndef OPENBROODCRAFT_INPUTAGENT_H
#define OPENBROODCRAFT_INPUTAGENT_H

#include "command.h"

enum InputAction {
    KEY_ESCAPE = 0x63,
    KEY_Q,
    KEY_W,
    KEY_E,
    KEY_R,
    KEY_A,
    KEY_S,
    KEY_D,
    KEY_F,
    KEY_Y,
    KEY_X,
    KEY_C,
    KEY_V,
    KEY_SPACE,
    KEY_CTRL,
    KEY_SHIFT,
    KEY_ALT,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    MOUSE_LEFT,
    MOUSE_RIGHT
};

class InputAgent {
public:
    InputAgent() = default;

    void handleInput(Command* t_commando);


    void initStdCommand();
    void assignCommand(Command t_newcmd, InputAction t_keytoassign);

private:
    Command* keyEscape_;
    Command* keyQ_;
    Command* keyW_;
    Command* keyE_;
    Command* keyR_;
    Command* keyA_;
    Command* keyS_;
    Command* keyD_;
    Command* keyF_;
    Command* keyY_;
    Command* keyX_;
    Command* keyC_;
    Command* keyV_;
    Command* keySpace_;
    Command* keyCtrl_;
    Command* keyShift_;
    Command* keyAlt_;
    Command* key1_;
    Command* key2_;
    Command* key3_;
    Command* key4_;
    Command* key5_;

    Command* mouseLeft_;
    Command* mouseRight_;

};



#endif //OPENBROODCRAFT_INPUTAGENT_H
