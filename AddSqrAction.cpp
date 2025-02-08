#include "AddSqrAction.h"
#include "ApplicationManager.h"
#include<iostream>
#include<fstream>
using namespace std;
AddSqrAction::AddSqrAction(ApplicationManager* pApp):Action(pApp)
{
}

void AddSqrAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Square: Click at centre");

	//Reads the centre and stores in point P
	pIn->GetPointClicked(P.x, P.y);
	pIn->CheckPointClicked(ITM_SQU, pOut, P);      // Check the point if it's Valid (Inside the Drawing Area)
	SqrGfxInfo.isFilled = pOut->CrntFillingFlag();//default is not filled
	//get drawing, filling colors and pen width from the interface
	SqrGfxInfo.DrawClr = pOut->getCrntDrawColor();
	SqrGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

void AddSqrAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a square with the parameters read from the user
	Square = new CSquare(P, pOut->GetLengthSq(), SqrGfxInfo);
	//Add the square to the list of figures
	pManager->AddFigure(Square);

	pManager->AddActToUndoRedo(this);
	pManager->setWillBeDeleted(true);
	pManager->ResetRedoCnt();
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void AddSqrAction::UndoAction()
{
	pManager->DeleteSelectedFig(Square);
}

void AddSqrAction::RedoAction()
{
	pManager->AddFigure(Square);

}

void AddSqrAction::Record()
{
	Output* pOut = pManager->GetOutput();
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << pOut->shapenum;
	Square->Save(Rec);
	Rec.close();

}

void AddSqrAction::Play(fstream& Play)
{
	Output* pOut = pManager->GetOutput();
	Square = new CSquare( pOut->GetLengthSq());

	Square->Load(Play);
	pManager->AddFigure(Square);


}
