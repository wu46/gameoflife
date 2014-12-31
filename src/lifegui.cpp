#include "lifegui.h"


LifeGUI::LifeGUI()
{
  gw.setSize(defaultWidth, defaultHeight);
  gw.requestFocus();
  originX = (int) gw.getWidth() * marginRatio;
  originY = (int) gw.getHeight() * marginRatio;
}

LifeGUI::~LifeGUI()
{
  //gw.close();
}

/*
void LifeGUI::drawBoard(Grid<int> &world){
  gw.clear();
  for(int i=0; i<world.nRows; i++){
      for (int j=0; j<world.nCols; j++){
          drawCell(i,j, (world[i][j]!=0));
      }
  }
}
*/

void LifeGUI::drawBoard(Set<PointLL> &world){
  clearBoard(world);
  currentWorld = world;
  gw.setColor("BLACK");
  for (Set<PointLL>::iterator it = world.begin(); it != world.end(); it++)
    {
      drawCell((*it).getX(), (*it).getY());
    }
  return;
}

void LifeGUI::clearBoard(Set<PointLL> &world){
  gw.setColor("WHITE");
  for (Set<PointLL>::iterator it = currentWorld.begin(); it != currentWorld.end(); it++)
    {
      // if not contained in next world, erase it
      if (!world.contains(*it))
        {
          drawCell((*it).getX(), (*it).getY());
        }

    }
  return;
}

void LifeGUI::drawCell(int x, int y){
  GRectangle cell(originX + x * cellWidth,
               originY + y * cellWidth,
               cellWidth, cellWidth);
  gw.fillRect(cell);
}
