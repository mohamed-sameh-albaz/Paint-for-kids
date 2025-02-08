#pragma once
#include "Actions/Action.h"
#include"Figures/CFigure.h"
#include "ApplicationManager.h"
class Undoaction : public Action
{
private:
    Action* pAct;

public:
    Undoaction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
    virtual void Record();

    virtual void Play(fstream& Play);


};

