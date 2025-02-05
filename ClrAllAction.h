#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"
class ClrAllAction :
    public Action
{
private:
public:
    ClrAllAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Record();

    virtual void Play(fstream& Play);


};

