#ifndef LIFEGUI_H
#define LIFEGUI_H

#include "grid.h"
#include "gwindow.h"
#include "set.h"
#include "pointll.h"
#include "ginteractors.h"
#include "gevents.h"
#include "gameoflife.h"
#include "goptionpane.h"
#include "simpio.h"
class LifeGUI
{
public:
    LifeGUI();
    ~LifeGUI();
    void drawBoard(Set<PointLL> &world);
    void run();

private:
    GWindow gw = GWindow(defaultWidth, defaultHeight);
    Set<PointLL> lastWorld;
    Set<PointLL> world;

    const static int PAUSE_TIME = 50;
    const static int defaultWidth = 1000;
    const static int defaultHeight = 500;
    const static int cellWidth = 5;
    // how much of window is used as margin
    const float marginRatio = 0.1;
    int originX; //TODO: recompute these when resized
    int originY;
    int cellOffsetX; // coord offset
    int cellOffsetY;



    // GUI components
    GButton *tickButton;
    GButton *animateButton;
    GButton *quitButton;
    GButton *startButton;
    GButton *pauseButton;
    GButton *centerButton;
    GTextField *animateTextField;
    GTextField *fnameTextField;
    GLabel *FILE;

    GameOfLife game;

    // private functions
    void init();
    void drawCell(int x, int y);
    void refreshBoard(Set<PointLL> &world);
    void clearBoard(Set<PointLL> &world);
    void center(Set<PointLL> &world);
};

#endif // LIFEGUI_H
