#pragma once
#include "Actions/Action.h"
#include "ApplicationManager.h"

class EndRecAction :public Action
{
private:
public:

    EndRecAction(ApplicationManager* pApp) ;

    virtual void ReadActionParameters();

    virtual void Execute();





};

