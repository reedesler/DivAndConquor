//
// Created by Reed on 2019-01-30.
//

#ifndef DIVCONQ_GAMEARCHIVE_H
#define DIVCONQ_GAMEARCHIVE_H


#include "world.h"

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

struct Action
{};

class GameArchive {
    void saveWorld(World w);
    World loadWorld();

    void save(std::string archiveName);

    GameArchive load(std::string fileName);
private:
    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &gameObjects;
        ar &currentActions;
    }
    std::vector<Action> currentActions;
    std::vector<GameObject> gameObjects;

public:
    GameArchive(){};
    GameArchive(std::vector<Action> actions, std::vector<GameObject> objects) : currentActions(actions), gameObjects(objects)
    {
    }
};


#endif //DIVCONQ_GAMEARCHIVE_H
