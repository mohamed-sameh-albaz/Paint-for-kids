#include "DragAction.h"
#include "ApplicationManager.h"
DragAction::DragAction(ApplicationManager* pApp):Action(pApp)
{
	
}

void DragAction::ReadActionParameters()
{
	
}

void DragAction::Execute()
{
	bool loop = true;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Start draging the figure ;)");

	while (loop) {
		pIn->getMouseCoord(P.x, P.y);
		switch (pIn->mouseHeld(P.x, P.y)) {
		case BUTTON_UP:
			pIn->QuesPointClicked();
			break;
		case BUTTON_DOWN:
			CFigure* SelectedShape = pManager->GetLastSelected();
			CFigure* test = pManager->GetLastSelected();
			if (pIn->mouseHeld(P.x, P.y) &&pManager->GetFigCount()) {
				if (SelectedShape->getMovingValidity(P))
					SelectedShape->move(P);
				Sleep(1);// to see it while dragging
				pOut->ClearDrawArea();
				pManager->UpdateInterface();
				if (!pIn->mouseHeld(P.x, P.y))loop = false;
			}
			else
			{
				loop = false;
				pOut->ClearStatusBar();
			}
			break;
		}

	}
		
}
