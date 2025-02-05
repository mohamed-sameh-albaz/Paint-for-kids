#pragma once
#include "Actions/Action.h"
class LoadAction :
    public Action
{
private:
  string  fileName;  // optional should be all paramaters here all not?
public:
    LoadAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();

};

