#ifndef LIFEGUI_H
#define LIFEGUI_H

#include "grid.h"
#include "gwindow.h"
#include "set.h"
#include "pointll.h"
class LifeGUI
{
public:
    LifeGUI();
    ~LifeGUI();
    void drawBoard(Set<PointLL> &world);

private:
    GWindow gw;
    Set<PointLL> currentWorld;
    const static int defaultWidth = 1000;
    const static int defaultHeight = 500;
    const static int cellWidth = 5;
    // how much of window is used as margin
    const float marginRatio = 0.2;
    int originX; //TODO: recompute these when resized
    int originY;
    void drawCell(int x, int y);
    void clearBoard(Set<PointLL> &world);
};

#endif // LIFEGUI_H
