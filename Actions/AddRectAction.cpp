#include "AddRectAction.h"
#include "..\ApplicationManager.h"
#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include<fstream>

AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->CheckPointClicked(ITM_RECT, pOut, P1);       // Check the first point if it's Valid (Inside the Drawing Area)
	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->CheckPointClicked(ITM_RECT, pOut, P2);       // Check the second point if it's Valid (Inside the Drawing Area)

	RectGfxInfo.isFilled =pOut->CrntFillingFlag();
	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	
	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute() 
{
	Output* pOut = pManager->GetOutput();
	//This action needs to read some parameters first
		 ReadActionParameters();
	
	//Create a rectangle with the parameters read from the user
	Rect=new CRectangle(P1, P2, RectGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(Rect);

	pManager->AddActToUndoRedo(this);
	pManager->setWillBeDeleted(true);
	pManager->ResetRedoCnt();
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void AddRectAction::UndoAction()
{
	pManager->DeleteSelectedFig(Rect);
}

void AddRectAction::RedoAction()
{
	pManager->AddFigure(Rect);
}

void AddRectAction::Record()
{
	Output* pOut = pManager->GetOutput();
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << pOut->shapenum;
	Rect->Save(Rec);
	Rec.close();
}

void AddRectAction::Play(fstream& Play)
{
	Rect = new CRectangle();
	Rect->Load(Play);
	pManager->AddFigure(Rect);

}
