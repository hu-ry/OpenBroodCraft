//
// Created by RH on 06.10.2019.
//

#ifndef OPENBROODCRAFT_KERNELSTORE_H
#define OPENBROODCRAFT_KERNELSTORE_H

enum Control_Mode {
    NOTHING_SELECTED,
    SOMETHING_SELECTED
};

typedef struct{
    bool inBoxSelection;
    bool abortBoxSelection;
    bool inIngameMenu;
    bool hasSelected;
} GameControlFlags;

struct KernelStore {
    GameControlFlags flags;
    bool fog_of_war;
    unsigned int entity_amount;
};


#endif //OPENBROODCRAFT_KERNELSTORE_H
