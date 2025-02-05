#pragma once
#include "ApplicationManager.h"
#include "Actions/Action.h"
#include "Figures/CFigure.h"
#include "Figures/CRectangle.h"
#include "CCircle.h"
#include "CHexagon.h"
#include "CTriangle.h"
#include "CSquare.h"

class PlyModBoth :
    public Action
{
private:
    int Correct, Wrong, Random, Num_Shapes;
    int Shapes[5][7];
    Point P;
    string shapes[5] = { "Rectangle" , "Circle" ,"Triangle", "Hexagon" , "Square" };
    string colors[7] = { "No Fill", "Black", "Blue", "Green" , "Orange" , "Red" , "Yellow" };
    string shape;
    string color;
    bool FirstGame;

public:
    PlyModBoth(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};


