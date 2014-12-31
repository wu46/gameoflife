#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <climits>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include "vector.h"
#include "pointll.h"
#include "set.h"
#include "gameoflife.h"
using namespace std;

// function declarations
void initializeWorld(Set<PointLL>& world,string filename);
void updateWorld(Set<PointLL>& world);
void updateDeadCells(Set<PointLL> deadQ, Set<PointLL> &world, Set<PointLL> &nextworld);
void getNeighbours(PointLL pt, Set<PointLL> &s);

int main() {
  GameOfLife game("fishcoord.txt");

  //Set<PointLL> world;
  //Set<PointLL> nextworld;

  //initializeWorld(world,"glider-gun_coord.txt");


  LifeGUI gui;
  while (true) {
    string s = getLine("[a]nimate, [t]ick, [q]uit? ");
    int it = 0;
    int nIterations;

    // choose mode
    switch (s[0]) {
      case 'a':
        nIterations = stringToInteger(getLine("How many frames? "));
        break;
      case 't':
        nIterations = 1;
        break;
      case 'q':
        cout << "Have a nice Life!" << endl;
        return 0;
    }
    // main loop
    while (it < nIterations){
      //updateWorld(world);
      game.tick();
      Set<PointLL> world = game.getWorld();
      gui.drawBoard(world);
      //gui.drawBoard(game.getWorld());

      pause(100);
      it++;
    }
  }

}

void initializeWorld(Set<PointLL>& world, string filename){
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

void updateDeadCells(Set<PointLL> deadNeighbours, Set<PointLL> &world, Set<PointLL> &nextworld)
{
  for (Set<PointLL>::iterator it=deadNeighbours.begin();
       it!=deadNeighbours.end(); it++)
    {
      Set<PointLL> neighbours;
      getNeighbours(*it, neighbours);

      //count the neighbours
      int nDeadNeighbours = 0;
      int nAliveNeighbours = 0;

      for(Set<PointLL>::iterator n=neighbours.begin();
          n!=neighbours.end(); n++)
        {
          // if world contains a neighbour, it is alive
          if (world.contains(*n))
            {
              nAliveNeighbours++;
              //cout << (*n) << "is a living neighbour of " << *it << endl;
            }
          else
            {
              nDeadNeighbours++;
              //cout << (*n) << "is a dead neighbour of " << *it << endl;
            }
        } // for all neighbours

      if (nAliveNeighbours == 3)
        {
          nextworld.add(*it);
        }
    }
  return;
}

void updateWorld(Set<PointLL> &world) {
  Set<PointLL> nextworld;
  Set<PointLL> deadNeighbours;

  for(Set<PointLL>::iterator it=world.begin(); it!=world.end(); it++) {
    Set<PointLL> neighbours;
    getNeighbours(*it, neighbours);

    //count the neighbours
    int nDeadNeighbours = 0;
    int nAliveNeighbours = 0;

    for(Set<PointLL>::iterator n=neighbours.begin();
        n!=neighbours.end(); n++)
      {
        // if world contains a neighbour, it is alive
        if (world.contains(*n))
          {
            nAliveNeighbours++;
            //cout << (*n) << "is a living neighbour of " << (*it) << endl;
          }
        else
          {
            nDeadNeighbours++;
            deadNeighbours.add(*n);
            //cout << (*n) << "is a dead neighbour of " << (*it) << endl;
          }
      } // for all neighbours

    // process living cells
    // only stay alive if 3 living neighbours
    if (nAliveNeighbours == 2 || nAliveNeighbours == 3)
      {
        nextworld.add(*it);
      }
  } // for all living cells
  //cout <<"dead q contains:" << deadNeighbours.toString() << endl;


  updateDeadCells(deadNeighbours, world, nextworld);

// update the entire world

world = nextworld;
//cout << "nextworld has: " << nextworld;
//cout <<"world has: " << world;
}

//TODO: change vector to set

void getNeighbours(PointLL pt, Set<PointLL> &s)
{
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
