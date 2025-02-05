#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"
#include "GUI/Output.h"
#include"Figures/CFigure.h"
class PlyModAction :
    public Action
{
private:
    CFigure* SelectedFig;
public:
    PlyModAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

