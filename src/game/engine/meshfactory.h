//
// Created by RH on 14/10/2019.
//

#ifndef OPENBROODCRAFT_MESHFACTORY_H
#define OPENBROODCRAFT_MESHFACTORY_H


#include "../../headerinclude.h"
#include "../map/gamemap.h"

class MeshFactory {
public:
    MeshFactory();

    MeshObject createMapMesh(GameMap t_map);

};


#endif //OPENBROODCRAFT_MESHFACTORY_H
