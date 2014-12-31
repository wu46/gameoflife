#include "gameoflife.h"

GameOfLife::GameOfLife() {
  string fname = "simple_coord.txt";
  initializeWorld(fname);
}

GameOfLife::GameOfLife(string fname) {
  initializeWorld(fname);
}

GameOfLife::~GameOfLife() {

}


void GameOfLife::getNeighbours(PointLL pt, Set<PointLL> &s) {
  if (pt.getX() > LLONG_MIN)
  {
    s.add(PointLL(pt.getX()-1, pt.getY()));

    if (pt.getY() > LLONG_MIN)
    {
      s.add(PointLL(pt.getX()-1, pt.getY()-1));
    }

    if (pt.getY() < LLONG_MAX){
      s.add(PointLL(pt.getX()-1, pt.getY()+1));
    }
  }

  if (pt.getX() < LLONG_MAX) {
    s.add(PointLL(pt.getX()+1, pt.getY()));
    if (pt.getY() > LLONG_MIN) {
      s.add(PointLL(pt.getX()+1, pt.getY()-1));
    }
    if (pt.getY() < LLONG_MAX) {
      s.add(PointLL(pt.getX()+1, pt.getY()+1));
    }
  }

  if (pt.getY() > LLONG_MIN) {
    s.add(PointLL(pt.getX(), pt.getY()-1));
  }
  if (pt.getY() < LLONG_MAX) {
    s.add(PointLL(pt.getX(), pt.getY()+1));
  }

  return;
}

void GameOfLife::updateCells(bool alive, Set<PointLL>&pts, Set<PointLL> &nextworld) {

  for(Set<PointLL>::iterator it=pts.begin(); it!=pts.end(); it++) {
    Set<PointLL> neighbours;
    getNeighbours(*it, neighbours);

    //count the neighbours
    int nDeadNeighbours = 0;
    int nAliveNeighbours = 0;

    for(Set<PointLL>::iterator n=neighbours.begin();
        n!=neighbours.end(); n++) {
        // if world contains a neighbour, it is alive
        if (world.contains(*n)) {
            nAliveNeighbours++;
            //cout << (*n) << "is a living neighbour of " << (*it) << endl;
          }
        else {
            nDeadNeighbours++;
            if (alive) {
              deadNeighbours.add(*n);
            }
            //cout << (*n) << "is a dead neighbour of " << (*it) << endl;
          }
      } // for all neighbours
    // process living cells
    // only stay alive if 3 living neighbours
    if (alive) {
      if (nAliveNeighbours == 2 || nAliveNeighbours == 3) {
        nextworld.add(*it);
      }
    } else {
      if (nAliveNeighbours == 3) {
        nextworld.add(*it);
      }
    }

  }
}

void GameOfLife::tick() {
  Set<PointLL> nextworld;
  deadNeighbours.clear();

  updateCells(true, world, nextworld);
  updateCells(false, deadNeighbours, nextworld);

// update the entire world

  world = nextworld;
}

void GameOfLife::initializeWorld(string filename) {
  cout << "called initialize world" << endl;
  ifstream infile;
  infile.open(filename.c_str());

  cout << filename.c_str() << endl;

  string nextline;

  // Input file has the form:
  // (x1,y1)
  // (x2,y2)
  // ...
  cout << "opening file: " << filename << endl;
  if (infile.is_open()) {
    cout << "file is OPEN!" << endl;
  } else {
    cout << "file is NOT open :(" << endl;
  }

  while (getline(infile,nextline)) {
    nextline = stringReplace(nextline, "(", "");
    nextline = stringReplace(nextline, ")", "");
    vector<string> v = stringSplit(nextline, ",");
    PointLL pt(stringToLongLong(v[0]),
        stringToLongLong(v[1]));
    world.add(pt);
  }
  return;
}

Set<PointLL> GameOfLife::getWorld() const {
  return world;
}

