#include "RedoAction.h"
#include<fstream>
Redoaction::Redoaction(ApplicationManager* pApp):Action(pApp)
{
}

void Redoaction::ReadActionParameters()
{
}

void Redoaction::Execute()
{
	Output* pOut = pManager->GetOutput();
	pOut->ClearStatusBar();
	if (pManager->getRedoCnt())
	{
		pManager->RedoAct();
		pOut->PrintMessage("Redo");
		pOut->ClearDrawArea();
		pManager->setRedoCnt(pManager->getRedoCnt()-1);
	}
	else
	{
		pOut->PrintMessage("No actions to be Redone");
	}
	if (pManager->GetIsRecording() && operationCount < MaxRecOperaion)
		Record();
}

void Redoaction::Record()
{
	operationCount++;
	fstream Rec(recordFile, ios::app);
	Rec << "\t" << "Redo" << endl;              
	Rec.close();
		
	
}

void Redoaction::Play(fstream& Play)
{
	Execute();

}
