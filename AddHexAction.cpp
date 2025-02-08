#include "AddHexAction.h"
#include "ApplicationManager.h"
#include<fstream>
AddHexAction::AddHexAction(ApplicationManager* pApp):Action(pApp)
{
}

void AddHexAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click at center");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P.x, P.y);
	pIn->CheckPointClicked(ITM_HEX, pOut, P);       // Check the first point if it's Valid (Inside the Drawing Area)
	HexGfxInfo.isFilled = pOut->CrntFillingFlag();	//default is not filled
	//get drawing, filling colors and pen width from the interface
	HexGfxInfo.DrawClr = pOut->getCrntDrawColor();
	HexGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}

void AddHexAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	//Create a hexagon with the parameters read from the user
	Hexa= new CHexagon(P,pOut->GetLengthHex(), HexGfxInfo);
	//Add the hexagon to the list of figures
	pManager->AddFigure(Hexa);

	pManager->AddActToUndoRedo(this);
	pManager->setWillBeDeleted(true);
	pManager->ResetRedoCnt();
	 if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		 Record();

}

void AddHexAction::UndoAction()
{
	pManager->DeleteSelectedFig(Hexa);
}

void AddHexAction::RedoAction()
{
	pManager->AddFigure(Hexa);
}

void AddHexAction::Record()
{
	Output* pOut = pManager->GetOutput();
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << pOut->shapenum;
	Hexa->Save(Rec);
	Rec.close();

}

void AddHexAction::Play(fstream& Play)
{
	Output* pOut = pManager->GetOutput();
	Hexa = new CHexagon(pOut->GetLengthHex());

	Hexa->Load(Play);
	pManager->AddFigure(Hexa);


}
