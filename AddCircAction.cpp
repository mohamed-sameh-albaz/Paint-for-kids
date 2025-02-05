#include "AddCircAction.h"
#include "ApplicationManager.h"
#include<iostream>
#include<fstream>
using namespace std;
AddCircAction::AddCircAction(ApplicationManager* pApp) :Action(pApp)
{
}

void AddCircAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at centre");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->CheckPointClicked(ITM_CIRC, pOut, P1, &P1);       // Check the first point if it's Valid (Inside the Drawing Area)
	pOut->DrawPoint(P1.x, P1.y);				      // To draw the Centre point to be able to determinate the radius much easier
	pOut->PrintMessage("New Cirle: Click at the second point");
	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->CheckPointClicked(ITM_CIRC, pOut, P1, &P2);       // Check the second point if it's Valid (Inside the Drawing Area)
	CircGfxInfo.isFilled = pOut->CrntFillingFlag();		//default is not filled
	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

//Execute the action
void AddCircAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	Circ = new CCircle(P1, P2, CircGfxInfo);
	//Add the rectangle to the list of figures
	pManager->AddFigure(Circ);

	pManager->AddActToUndoRedo(this);
	pManager->setWillBeDeleted(true);
	pManager->ResetRedoCnt();
	//Add the rectangle to the list of figures
	pManager->AddFigure(Circ);

	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void AddCircAction::UndoAction()
{
	pManager->DeleteSelectedFig(Circ);
}

void AddCircAction::RedoAction()
{
	pManager->AddFigure(Circ);
}

void AddCircAction::Record()
{
	Output* pOut = pManager->GetOutput();
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec <<"\t"<< pOut->shapenum;
	Circ->Save(Rec);
	Rec.close();
}

void AddCircAction::Play(fstream& Play)
{
	Circ = new CCircle();
	Circ->Load(Play);
	pManager->AddFigure(Circ);
}
