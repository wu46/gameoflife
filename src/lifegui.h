#ifndef LIFEGUI_H
#define LIFEGUI_H

#include "grid.h"
#include "gwindow.h"
class LifeGUI
{
public:
    LifeGUI();
    ~LifeGUI();
    void drawBoard(Grid<int> &world);
private:
    GWindow gw;
    const static int defaultWidth = 1000;
    const static int defaultHeight = 500;
    const static int cellWidth = 5;
    // how much of window is used as margin
    const float marginRatio = 0.2;
    int originX; //TODO: recompute these when resized
    int originY;
    void drawCell(int row, int col, bool alive);
};

#endif // LIFEGUI_H
