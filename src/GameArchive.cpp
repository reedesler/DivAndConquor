//
// Created by Reed on 2019-01-30.
//

#include <fstream>
#include "GameArchive.h"

void GameArchive::saveWorld(World w) {

}

World GameArchive::loadWorld() {
    return World(0, 0, nullptr);
}

void GameArchive::save(std::string archiveName)
{
    /*// create and open a character archive for output
    std::ofstream ofs(archiveName + ".dnq");

    // create class instance
    const GameArchive g;

    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << g;
        // archive and stream closed when destructors are called
    }*/
}

GameArchive GameArchive::load(std::string fileName)
{
    // ... some time later restore the class instance to its orginal state
    /*GameArchive newg;
    {
        // create and open an archive for input
        std::ifstream ifs(fileName);
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> newg;
        // archive and stream closed when destructors are called
    }
    return newg;*/
}