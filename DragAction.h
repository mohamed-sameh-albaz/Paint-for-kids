#pragma once
#include "Actions/Action.h"
class DragAction : public Action
{
private:
	Point P;
    bool IsHeld;
public:
    DragAction(ApplicationManager* pApp);

    virtual void ReadActionParameters();

    virtual void Execute();
};

