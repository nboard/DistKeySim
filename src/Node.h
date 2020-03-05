#ifndef LIGHTSYSTEMP_NODE_H
#define LIGHTSYSTEMP_NODE_H

#include <iostream>
#include <vector>

#include "UUID.h"


typedef unsigned long Keyspace;

///TODO integrate RPC into the class
///TODO likely other things that I didn't consider.
class Node {
private:
    UUID uuid;
    Keyspace keySpace;
    double keyShareRate;
    double keyGenRate;
    double aggregateGenRate;
    double shortTermAllocationRatio;
    double longTermAllocationRatio;
    double aggregateAllocationRatio;
    double provisioningRatio;
    bool active;
    std::vector<Node*> peers; ///called directConnection on the board.
public:
    Node();

    ///getter and setter for nodeID
    ///Alter these based on the fact that the nodeID should be be a UUID
    UUID getUUID() const { return uuid; }
    void setUUID(UUID nid) { uuid = nid; }

    ///getter and setter for keySpace
    Keyspace getKeySpace() const { return keySpace; }
    void setKeySpace(Keyspace ks) { keySpace = ks; }

    ///getter and setter for keyGenRate
    double getKeyGenRate() const { return keyGenRate; }
    void setKeyGenRate(double kgr) { keyGenRate = kgr; }

    double getKeyShareRate() const { return keyShareRate; }
    void setKeyShareRate(double ksr) { keyShareRate = ksr; }

    double getAggregateKGenRate() const { return aggregateGenRate; }
    void setAggregateGenRate(double agr) { aggregateGenRate = agr; }

    double getShortTermAllocationRatio() const { return shortTermAllocationRatio; }
    void setShortTermAllocationRatio(double star) { shortTermAllocationRatio = star; }

    double getLongTermAllocationRatio() const { return longTermAllocationRatio; }
    void setLongTermAllocationRatio(double lar) { longTermAllocationRatio = lar; }

    double getAggregateAllocationRatio() const { return aggregateAllocationRatio; }
    void setAggregateAllocationRatio(double aar) { aggregateAllocationRatio = aar; }

    double getProvisioningRatio() const { return provisioningRatio; }
    void setProvisioningRatio(double pr) { provisioningRatio = pr; }

    bool getActive() const { return active; }
    void setActive(bool a) { active = a; }

    //Keyspace createKeySpace();
    //double computeAggregateGenRate();
    /*double computeShortTermAllocationRatio();
    double computeLongTermAllocationRatio();
    double computeAggregateAllocationRatio();
    double computeProvisioningRatio();*/
};

#endif //LIGHTSYSTEMP_NODE_H
