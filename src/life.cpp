
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include "vector.h"
using namespace std;

// function declarations
void initializeWorld(Grid<int>& world, Grid<int>& nextworld, string filename);
void updateWorld(Grid<int>& world, Grid<int>& nextworld);
void getNeighbours(int i, int j, Vector<int> &xcoord, Vector<int> &ycoord, Grid<int> &world);
void displayWorld(Grid<int> &world);
void testGUI();

int main() {
  Grid<int> world;
  Grid<int> nextworld;
  initializeWorld(world, nextworld, "glider-gun.txt");

  LifeGUI gui;

  // TODO: remove
  // test GUI
  // app will exit after this part

  //
  while (true) {
    string s = getLine("[a]nimate, [t]ick, [q]uit? ");
    int it = 0;
    int nIterations;

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
    while (it < nIterations){
        clearConsole();
        updateWorld(world,nextworld);
        gui.drawBoard(world);
        //displayWorld(world);
        pause(100);
        it++;
    }
  }
}

void initializeWorld(Grid<int>& world, Grid<int>& nextworld, string filename){

  ifstream infile;
  infile.open(filename.c_str());
  string nextline;


  // get grid size
  getline(infile,nextline);
  int num_rows = stringToInteger(nextline);

  getline(infile,nextline);
  int num_cols = stringToInteger(nextline);


  int line_count = 0;
  world.resize(num_rows, num_cols);
  nextworld.resize(num_rows, num_cols);

  // populate grid
  while (line_count < num_rows){
    getline(infile, nextline);
    for (int i=0; i<num_cols; i++){
      if (tolower(nextline[i]) == 'x'){
        world[line_count][i] = 1;
      }
    }
    line_count++;
  }
  return;
}

void updateWorld(Grid<int> &world, Grid<int> &nextworld) {
  for (int i = 0; i<world.nRows; i++) {
    for (int j=0; j<world.nCols; j++) {
      Vector<int> xcoords;
      Vector<int> ycoords;
      getNeighbours(i,j,xcoords,ycoords,world);

      //count the neighbours
      int nDeadNeighbors = 0;
      int nAliveNeighbors = 0;
      for (int i=0; i<xcoords.size(); i++) {
        if (world[xcoords[i]][ycoords[i]]){
          nAliveNeighbors++;
        } else {
          nDeadNeighbors++;
        }
      }

      // set the next state
      if (nAliveNeighbors < 2) {
        nextworld[i][j] = 0;
      } else if (nAliveNeighbors == 2) {
        nextworld[i][j] = world[i][j];
      } else if (nAliveNeighbors == 3 ) {
        nextworld[i][j] = 1;
      } else {
        nextworld[i][j] = 0;
      }

    }
  }

  // update the entire world
  world = nextworld;

}

void getNeighbours(int i, int j, Vector<int> &xcoord, Vector<int> &ycoord, Grid<int> &world){
  if (i-1 >= 0){
    xcoord.add(i-1); ycoord.add(j);
    if (j-1 >= 0) {
      xcoord.add(i-1); ycoord.add(j-1);
    }
    if (j+1 < world.nCols){
      xcoord.add(i-1); ycoord.add(j+1);
    }
  }

  if (i+1 < world.nRows) {
    xcoord.add(i+1); ycoord.add(j);
    if (j-1 >= 0) {
      xcoord.add(i+1); ycoord.add(j-1);
    }
    if (j+1 < world.nCols) {
      xcoord.add(i+1); ycoord.add(j+1);
    }
  }

  if (j-1 >= 0) {
    xcoord.add(i); ycoord.add(j-1);
  }
  if (j+1 < world.nCols) {
    xcoord.add(i); ycoord.add(j+1);
  }

  return;

}

void displayWorld(Grid<int> &world){
  cout << endl;
  for (int i=0; i<world.nRows; i++){
    for (int j=0; j<world.nCols; j++) {
      if(world[i][j] < 1) {
        cout << "-";
      } else {
        cout << "X";
      }
    }
    cout << endl;
  }
}

void testGUI(){
    cout << "called testgui" << endl;
    GWindow gw(1000,800);
    const int CELLWIDTH = 50; // px
    //const GRectangle rect = new GRectangle(100,500, CELLWIDTH, CELLWIDTH);

    gw.fillRect(100,100, CELLWIDTH, CELLWIDTH);
}
