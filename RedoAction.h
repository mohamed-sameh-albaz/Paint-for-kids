#pragma once
#include "Actions/Action.h"
#include"Figures/CFigure.h"
#include "ApplicationManager.h"

class RedoAction :
    public Action
{private:
public:
    RedoAction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Record();
    virtual void Play(fstream& Play);


};

