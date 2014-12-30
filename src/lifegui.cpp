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

void LifeGUI::drawBoard(Grid<int> &world){
  gw.clear();
  for(int i=0; i<world.nRows; i++){
      for (int j=0; j<world.nCols; j++){
          drawCell(i,j, (world[i][j]!=0));
      }
  }
}

void LifeGUI::drawCell(int row, int col, bool alive){
  GRectangle cell(originX + col * cellWidth,
               originY + row * cellWidth,
               cellWidth, cellWidth);
  if (alive){
    gw.fillRect(cell);
  }
}
