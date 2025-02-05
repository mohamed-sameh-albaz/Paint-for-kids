#pragma once
#include "Actions/Action.h"
#include "CSquare.h"
class AddSqrAction :
    public Action
{
private:
    Point P;
    GfxInfo SqrGfxInfo;
    CSquare* Square;
public:
    AddSqrAction(ApplicationManager* pApp);
    //Reads square parameters      
    virtual void ReadActionParameters();

    //Add square to the ApplicationManager
    virtual void Execute();
    virtual void UndoAction();
    virtual void RedoAction();

    virtual void Record();

    virtual void Play(fstream& Play); // can not be pure virtual because there are some actions that cannot be recorded


};

