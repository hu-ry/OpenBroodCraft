//
// Created by RH on 20/09/2019.
//

#ifndef OPENBROODCRAFT_COMMAND_H
#define OPENBROODCRAFT_COMMAND_H

#include <glm/vec2.hpp>

enum CommandType {
    COMMAND_NONE = -1,
    COMMAND_HOLD,
    COMMAND_MOVE,
    COMMAND_PATROL,
    COMMAND_ATTACK
};

class Command {
public:
    virtual ~Command() {}
    virtual void execute() = 0;

    //Command() {
    //    this->StartPos = glm::vec2(0.0f, 0.0f);
    //    this->Destination = glm::vec2(0.0f, 0.0f);
    //}
    //
    //Command(CommandType type, glm::vec2 startPos, glm::vec2 destination) {
    //    this->Type = type;
    //    if(type > 0) {
    //        this->StartPos = startPos;
    //        this->Destination = destination;
    //    } else {
    //        this->StartPos = startPos;
    //        this->Destination = startPos;
    //    }
    //}
    //
    //glm::vec2 StartPos;
    //glm::vec2 Destination;
};

class MoveCommand : public Command {
public:
    MoveCommand(glm::vec2 destination) : Destination(destination){}

    virtual void execute() { /* TODO: insert functionality */ }

private:
    glm::vec2 Destination;
};


#endif //OPENBROODCRAFT_COMMAND_H
