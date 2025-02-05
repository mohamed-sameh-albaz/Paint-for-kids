#include "selectAction.h"
#include "ApplicationManager.h"
#include "CCircle.h"
#include "Figures/CRectangle.h"
#include "CTriangle.h"
#include "CSquare.h"
#include "CHexagon.h"
#include<fstream>
selectAction::selectAction(ApplicationManager* pApp):Action(pApp)
{

}

void selectAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	pIn->GetPointClicked(P.x, P.y);
}

void selectAction::Execute()
{	
		Output* pOut = pManager->GetOutput();
	if (pManager->GetFigCount()) {

		pOut->PrintMessage("Select a Figure");

			//This action needs to read some parameters first
		if(!pManager->GetIsPlaying())
			{
				ReadActionParameters();
			}
			
		if(P.y>UI.ToolBarHeight)
		{
			CFigure* SelectedShape = pManager->GetFigure(P.x, P.y);
			CFigure* lstSelectedFig = pManager->GetLastSelected();
			if (!SelectedShape)
				pOut->ClearStatusBar(); //alternative 

			else if (SelectedShape->IsSelected())//for unselecting by reclicking
				SelectedShape->SetSelected(false);
			else 
			{
				if (lstSelectedFig)
					lstSelectedFig->SetSelected(false);//unselecting the last selected one
				SelectedShape->SetSelected(true);
				SelectedShape->PrintInfo(pOut);

			}
		}
	}
	else 
		pOut->PrintMessage("No Figures to select!");

	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void selectAction::Record()
{	
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << "Select" << "\t" << P.x << "\t" << P.y << endl;             
	Rec.close();
		
	
}

void selectAction::Play(fstream& Play)
{
	Play >> P.x >> P.y;
	Execute();
}

