//
// Created by RH on 25.05.2020.
//

#ifndef OPENBROODCRAFT_ORDER_H
#define OPENBROODCRAFT_ORDER_H

#include <glm/vec2.hpp>

enum OrderType {
    COMMAND_NONE = -1,
    COMMAND_HOLD,
    COMMAND_MOVE,
    COMMAND_PATROL,
    COMMAND_ATTACK
};

class Order {
public:
    Order() {
        this->StartPos = glm::vec2(0.0f, 0.0f);
        this->Destination = glm::vec2(0.0f, 0.0f);
    }

    Order(OrderType t_type, glm::vec2 startPos, glm::vec2 destination) : _Type(t_type) {
        if(t_type > 0) {
            this->StartPos = startPos;
            this->Destination = destination;
        } else {
            this->StartPos = startPos;
            this->Destination = startPos;
        }
    }

    OrderType _Type;
    glm::vec2 StartPos;
    glm::vec2 Destination;
};

#endif //OPENBROODCRAFT_ORDER_H
