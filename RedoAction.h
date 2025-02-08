#pragma once
#include "Actions/Action.h"
#include"Figures/CFigure.h"
#include "ApplicationManager.h"

class Redoaction :
    public Action
{private:
public:
    Redoaction(ApplicationManager* pApp);
    virtual void ReadActionParameters();
    virtual void Execute();
    virtual void Record();
    virtual void Play(fstream& Play);


};

