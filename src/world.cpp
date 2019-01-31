//
// Created by Dmitry on 2019-01-25.
//
#include <fstream>

#include "world.h"

World::World(int w, int h, Camera *camera) : camera(camera)
{
    this->tilemap.resize(w, std::vector<int>(h, 0));
}

World::~World() = default;

void World::update()
{
    camera->update();
}

void World::draw(DrawContext *dc)
{
    camera->draw(dc);
    for (int i = 0; i < 100; i++)
    {
        camera->drawRect({200 + 10 * i, 200, 10, 10}, {0, 255, 255, 255});
    }
    camera->drawRect({50, 50, 100, 100}, {0, 255, 255, 255});
    camera->drawRect({75, 0, 50, 50}, {0, 255, 0, 0});
}

void World::save(std::string archiveName)
{
    // create and open a character archive for output
    std::ofstream ofs(archiveName + ".dnq");

    // create class instance
    const GameArchive g();

    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa << g;
        // archive and stream closed when destructors are called
    }
}

GameArchive World::load(std::string fileName)
{
    // ... some time later restore the class instance to its orginal state
    GameArchive newg;
    {
        // create and open an archive for input
        std::ifstream ifs(fileName);
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        ia >> newg;
        // archive and stream closed when destructors are called
    }
    return newg;
}