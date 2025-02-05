#include "PlyModAction.h"

PlyModAction::PlyModAction(ApplicationManager* pApp) :Action(pApp)
{
}

void PlyModAction::ReadActionParameters()
{}

void PlyModAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	pOut->ClearToolBar();
	pOut->CreatePlayToolBar();
	pOut->PrintMessage("Play Mode");
	SelectedFig = pManager->GetLastSelected();
	if(SelectedFig)
	{
		SelectedFig->SetSelected(false);
	}
	
	if (!pManager->isMuted())
		PlaySound("sounds/play_effect", NULL, SND_ASYNC);
}
