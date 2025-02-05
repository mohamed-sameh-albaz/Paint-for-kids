#include "voiceAction.h"
#include "ApplicationManager.h"
voiceAction::voiceAction(ApplicationManager* pApp):Action(pApp)
{
	
}

void voiceAction::ReadActionParameters()
{
}

void voiceAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	if (!pManager->isMuted())
	{
		pOut->CreateMutedTAB();
		pManager->setMuted(true);
	}
	else
	{
	 pOut->CreateDrawToolBar();
	 pManager->setMuted(false);
	}
		
}
