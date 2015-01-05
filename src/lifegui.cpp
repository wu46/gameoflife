#include "lifegui.h"


LifeGUI::LifeGUI()
{
  gw.setSize(defaultWidth, defaultHeight);
  gw.requestFocus();
  originX = (int) gw.getWidth() * marginRatio;
  originY = (int) gw.getHeight() * marginRatio;

  // add interactors
  tickButton = new GButton("tick");
  animateButton = new GButton("animate");
  quitButton = new GButton("quit");
  animateTextField = new GTextField(5);
  animateTextField->setText("50");

  gw.addToRegion(tickButton, "SOUTH");
  gw.addToRegion(animateButton, "SOUTH");
  gw.addToRegion(animateTextField, "SOUTH");
  gw.addToRegion(quitButton, "SOUTH");

}

LifeGUI::~LifeGUI()
{
  //gw.close();
}

void LifeGUI::run(){
  GameOfLife game("fishcoord.txt");
  cout << "initialized game of life" << endl;
  while (true) {
    int it = 0;
    int nIterations;
    GActionEvent e = waitForEvent(ACTION_EVENT);
    if (e.getActionCommand().compare("tick") == 0) {
      nIterations = 1;
    }
    if (e.getActionCommand().compare("animate") == 0){
      nIterations = stringToInteger(animateTextField->getText());
    }
    if (e.getActionCommand().compare("quit") == 0){
      return;
    }

    while (it < nIterations){
      game.tick();
      Set<PointLL> world = game.getWorld();
      drawBoard(world);

      pause(100);
      it++;
    }
  }
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
