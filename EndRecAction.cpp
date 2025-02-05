#include "EndRecAction.h"
#include "ApplicationManager.h"
#include<fstream>
EndRecAction::EndRecAction(ApplicationManager* pApp) :Action(pApp)
{
}

void EndRecAction::ReadActionParameters()
{
}

void EndRecAction::Execute()
{

	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Stop Recording ");

	pManager->SetIsRecording(false);
	operationCount = 0;   


	if (!pManager->isMuted())
		PlaySound("sounds/endRec_effect", NULL, ASYNCH);
}



