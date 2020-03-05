#ifndef LIGHTSYS_ADAK_SIMULATION_H
#define LIGHTSYS_ADAK_SIMULATION_H

#include "UUID.h"
#include "Network.h"
#include <iostream>
#include <fstream>

class Simulation {
private:
//    std::vector<UUID> uuidList;
//    std::map<UUID, Node*> nodes;
//    std::vector<Channel*> channels;
    Network* network;
public:
    Simulation();

    // Getters
    Network* getNetwork() { return this->network; }
};

#endif //LIGHTSYS_ADAK_SIMULATION_H