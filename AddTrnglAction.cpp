#include "AddTrnglAction.h"
#include "ApplicationManager.h"
#include<fstream>

AddTrnglAction::AddTrnglAction(ApplicationManager* pApp):Action(pApp)
{
}

void AddTrnglAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("New Triangle: Click at first vertex");
	
	//Read 1st vertex and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);
	pIn->CheckPointClicked(ITM_TRI, pOut, P1);       // Check the first point if it's Valid (Inside the Drawing Area)
	pOut->PrintMessage("New Triangle: Click at second vertex");
	
	//Read 2nd vertex and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	pIn->CheckPointClicked(ITM_TRI, pOut, P2);       // Check the second point if it's Valid (Inside the Drawing Area)
	pOut->PrintMessage("New Triangle: Click at third vertex");

	//Read 2nd vertex and store in point P2
	pIn->GetPointClicked(P3.x, P3.y);
	pIn->CheckPointClicked(ITM_TRI, pOut, P3);       // Check the third point if it's Valid (Inside the Drawing Area)
	pOut->PrintMessage("New Triangle: Click at third vertex");

	TrnglGfxInfo.isFilled = pOut->CrntFillingFlag();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	TrnglGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TrnglGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

void AddTrnglAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a triangle with the parameters read from the user
	Trig = new CTriangle(P1, P2,P3, TrnglGfxInfo);
	//Add the triagle to the list of figures
	pManager->AddFigure(Trig);

	pManager->AddActToUndoRedo(this);
	pManager->setWillBeDeleted(true);
	pManager->ResetRedoCnt();
	 if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		 Record();
}

void AddTrnglAction::UndoAction()
{
	pManager->DeleteSelectedFig(Trig);
}

void AddTrnglAction::RedoAction()
{
	pManager->AddFigure(Trig);
}

void AddTrnglAction::Record()
{
	Output* pOut = pManager->GetOutput();
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << pOut->shapenum;
	Trig->Save(Rec);
	Rec.close();
}

void AddTrnglAction::Play(fstream& Play)
{
	Trig = new CTriangle();

	Trig->Load(Play);
	pManager->AddFigure(Trig);


}
