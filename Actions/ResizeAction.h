#pragma once
#include "Action.h"
#include "../GUI/Output.h"
#include "../ApplicationManager.h"
#include "../Figures/CRectangle.h"
#include "../CCircle.h"
#include "../CHexagon.h"
#include "../CTriangle.h"
#include "../CSquare.h"
#include "../CMUgraphicsLib/CMUgraphics.h"
class ResizeAction :public Action
{
private:
    Point A;
    Point B;
    Point *C;
    bool loop;
    bool LOOP;
    int n;
    CFigure* ResizeFig;
public:
	ResizeAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

