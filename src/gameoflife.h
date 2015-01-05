#include "pointll.h"
#include "set.h"
#include <climits>
#include <string>
#include <iostream>

#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

using namespace std;

class GameOfLife
{
public:
  GameOfLife();
  GameOfLife(string filename);
  ~GameOfLife();
  Set<PointLL> getWorld() const;
  void tick();

private:
  Set<PointLL> world;
  Set<PointLL> deadNeighbours;
  void initializeWorld(string filename);
  void updateCells(bool alive, Set<PointLL>&pts, Set<PointLL>&nextworld);
  void getNeighbours(PointLL pt, Set<PointLL> &s);
};

#endif // GAMEOFLIFE_H
