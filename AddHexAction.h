#pragma once
#include "Actions/Action.h"
#include"CHexagon.h"

class AddHexAction :
    public Action
{
private:
    Point P;
    GfxInfo HexGfxInfo;
    CHexagon* Hexa;
public:
    AddHexAction(ApplicationManager* pApp);
    //Reads rectangle parameters            
    virtual void ReadActionParameters();

    //Add rectangle to the ApplicationManager
    virtual void Execute();
    virtual void UndoAction();
    virtual void RedoAction();

    virtual void Record();

    virtual void Play(fstream& Play) ; // can not be pure virtual because there are some actions that cannot be recorded

};

