#pragma once
#include "ApplicationManager.h"
#include "Actions/Action.h"
#include "Figures/CFigure.h"
#include "Figures/CRectangle.h"
#include "CCircle.h"
#include "CHexagon.h"
#include "CTriangle.h"
#include "CSquare.h"

class PlyModColors :
    public Action
{
private:
    int Correct, Wrong, Random, Num_Colors;
    int Colors[7];
    Point P;
    bool FirstGame;
public:
    PlyModColors(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};


