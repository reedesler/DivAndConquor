//
// Created by Dmitry on 2019-01-25.
//

#ifndef DIVCONQ_WORLD_H
#define DIVCONQ_WORLD_H

#include <vector>
#include <string>

// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "drawable.h"
#include "Camera.h"

class World : Drawable
{
public:
  World(int w, int h, Camera *camera);

  ~World();

  void update() override;

  void draw(DrawContext *dc) override;

  Camera *camera;

  void save(std::string archiveName);

  GameArchive load(std::string fileName);

private:
  std::vector<std::vector<int>> tilemap;
  std::vector<std::string> savedFiles;
};

struct Action
{
};

struct GameObject
{
};

// illustrates serialization for the game object
class GameArchive
{
private:
  friend class boost::serialization::access;
  // When the class Archive corresponds to an output archive, the
  // & operator is defined similar to <<.  Likewise, when the class Archive
  // is a type of input archive the & operator is defined similar to >>.
  template <class Archive>
  void serialize(Archive &ar, const unsigned int version)
  {
    ar &objects;
    ar &actions;
  }
  std::vector<Action> currentActions;
  std::vector<GameObject> gameObjects;

public:
  GameArchive(){};
  GameArchive(std::vector<Action> actions, std::vector<GameObject> objects) : currentActions(actions), gameObjects(objects)
  {
  }
};

#endif //DIVCONQ_WORLD_H
