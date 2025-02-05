#pragma once
#include "ApplicationManager.h"
#include "Actions/Action.h"
#include "Figures/CFigure.h"
#include "Figures/CRectangle.h"
#include "CCircle.h"
#include "CHexagon.h"
#include "CTriangle.h"
#include "CSquare.h"

class PlyModShapes :
    public Action
{
private:
    int Correct, Wrong, Random, Num_Figures;
    int Figures[5] = { 0,0,0,0,0 };
    string shapes[5] = { "Rectangle" , "Circle" ,"Triangle", "Hexagon" , "Square" };
    Point P;
    bool FirstGame;

public:
    PlyModShapes(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};


