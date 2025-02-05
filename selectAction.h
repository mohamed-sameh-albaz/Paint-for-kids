#pragma once
#include "Actions/Action.h"
class selectAction :
    public Action
{
private:
    Point P;
public:
    selectAction(ApplicationManager* pApp);



    virtual void ReadActionParameters();

    virtual void Execute();

    virtual void Record();
   
    virtual void Play(fstream& Play) ;


};

