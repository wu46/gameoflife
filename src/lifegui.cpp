#include "lifegui.h"

int main() {
  LifeGUI gui;
  gui.run();
  return 0;
}

LifeGUI::LifeGUI()
{
  gw.requestFocus();
  originX = (int) gw.getWidth() * marginRatio;
  originY = (int) gw.getHeight() * marginRatio;
  cellOffsetX = 0;
  cellOffsetY = 0;

  // add interactors
  tickButton = new GButton("tick");
  pauseButton = new GButton("pause");
  animateButton = new GButton("animate");
  quitButton = new GButton("quit");
  animateTextField = new GTextField(5);
  animateTextField->setText("50");
  startButton = new GButton("Start");
  centerButton = new GButton("center");
  fnameTextField = new GTextField(15);
  fnameTextField->setText("fishcoord.txt");
  FILE = new GLabel("  File name:");

  gw.addToRegion(quitButton, "SOUTH");
  gw.addToRegion(FILE, "EAST");
  gw.addToRegion(fnameTextField, "EAST");
  gw.addToRegion(startButton, "EAST");
}

LifeGUI::~LifeGUI()
{
  gw.close();
}

void LifeGUI::init(){
  while (true) {
    GActionEvent e = waitForEvent(ACTION_EVENT);
    if (e.getActionCommand().compare("Start")==0) {
      game = GameOfLife(fnameTextField->getText());
      world = game.getWorld();
      drawBoard(world);

      gw.addToRegion(tickButton, "SOUTH");
      gw.addToRegion(animateButton, "SOUTH");
      gw.addToRegion(animateTextField, "SOUTH");
      gw.addToRegion(quitButton, "SOUTH");
      gw.addToRegion(centerButton, "EAST");

      startButton->setEnabled(false);

      return;
    }

    if (e.getActionCommand().compare("quit") == 0){
      gw.close();
      return;
    }
  }
}

void LifeGUI::run(){

  init();

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
    if (e.getActionCommand().compare("center") == 0) {
      center(world);
      nIterations = 0;
    }


    while (it < nIterations){
      game.tick();
      world = game.getWorld();
      drawBoard(world);

      pause(PAUSE_TIME);
      it++;
    }
  }
}

void LifeGUI::drawBoard(Set<PointLL> &world){
  refreshBoard(world);
  lastWorld = world;
  gw.setColor("BLACK");
  for (Set<PointLL>::iterator it = world.begin(); it != world.end(); it++)
  {
    drawCell((*it).getX(), (*it).getY());
  }
  return;
}

void LifeGUI::clearBoard(Set<PointLL> &world){
  gw.setColor("WHITE");
  for (Set<PointLL>::iterator it = world.begin(); it != world.end(); it++)
  {
    drawCell((*it).getX(), (*it).getY());
  }
  return;
}

void LifeGUI::refreshBoard(Set<PointLL> &world){
  gw.setColor("WHITE");
  for (Set<PointLL>::iterator it = lastWorld.begin(); it != lastWorld.end(); it++)
  {
    // if not contained in next world, erase it
    if (!world.contains(*it))
    {
      drawCell((*it).getX(), (*it).getY());
    }

  }
  return;
}

void LifeGUI::center(Set<PointLL> &world) {
  // check if world is initialized. if not, center does nothing
  if (world.size()<1) {
    return;
  }
  // clear current board
  clearBoard(world);

  PointLL c = world.first();

  // draw new board

  int xloc = originX + c.getX()*cellWidth + cellOffsetX;
  int yloc = originY + c.getY()*cellWidth + cellOffsetY;

  cellOffsetX = gw.getWidth()/2.0 - originX - c.getX()*cellWidth;
  cellOffsetY = gw.getHeight()/2.0 - originY - c.getY()*cellWidth;


  xloc = originX + c.getX()*cellWidth + cellOffsetX;
  yloc = originY + c.getY()*cellWidth + cellOffsetY;

  drawBoard(world);
}

void LifeGUI::drawCell(int x, int y){
  // if cell is out of bounds, then don't draw it
  int xloc = originX + x*cellWidth + cellOffsetX;
  int yloc = originY + y*cellWidth + cellOffsetY;

  if (xloc < 0 || xloc > (int)gw.getWidth() ||
      yloc < 0 ||yloc > (int)gw.getHeight()) {
    // don't draw the cell
  } else {
    GRectangle cell(xloc, yloc, cellWidth, cellWidth);
    gw.fillRect(cell);
  }

}
