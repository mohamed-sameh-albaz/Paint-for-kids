#pragma once
#include "Actions/Action.h"
#include"Figures/CFigure.h"
#include "ApplicationManager.h"

class DeleteAction :
    public Action
{
private:
    CFigure* SelectedFig;
public:
    DeleteAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
    virtual void UndoAction();
    virtual void RedoAction();

    virtual void Record();

    virtual void Play(fstream& Play);


};
