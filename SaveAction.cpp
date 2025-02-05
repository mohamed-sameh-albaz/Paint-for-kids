#include "SaveAction.h"
#include "ApplicationManager.h"
#include<fstream>
SaveAction::SaveAction(ApplicationManager* pApp) :Action(pApp)
{
	fileName= "save/";
}

void SaveAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->ClearStatusBar();
	pIn->QuesKeyClicked();
	pOut->PrintMessage("  Please enter the Save file name  ");
	fileName += pIn->GetString(pOut);
	pIn->QuesPointClicked();
	


}

void SaveAction::Execute()
{

	Output* pOut = pManager->GetOutput();

	if (!(pManager->GetFigCount()))
	{
		pOut->PrintMessage(" there is nothing to save ");   // Optional to tell the user that there is no drawn figures
	}
	else
	{
		ReadActionParameters();

		// To make sure that file has the right extention
	/*	int index = fileName.rfind(".");
		if (index)
			fileName.replace(index, 4, ".txt");
		else*/
		fileName += ".txt";



		fstream saveFile(fileName,ios::out);    // I didn't check if the file is open or not because i check it in previous


		if (!saveFile.is_open()) // optional because  I checked if the file name is correct or not in previous step
		{
			pOut->PrintMessage("  cannot open the file please try again ");
		}


		else
		{	
		string currentDrawcolor = pOut->getCrntDrawColor();      // optional should i made them as private in .h??? 
		string currentfillcolor;
		if (pOut->CrntFillingFlag())
			currentfillcolor = pOut->getCrntFillColor();      //optional should i made cfigure save is virtual not pure
		else
			currentfillcolor = "NO_FILL";
		saveFile << "\t" << currentDrawcolor << "\t" << currentfillcolor << endl;// optional and call pointer in the beginning of func saveall in application man.. 
		saveFile << "\t" << pManager->GetFigCount() << endl;    // optional like that FigList[0]->CFigure::Save(offile);
		pManager->SaveAllFigures(saveFile);
		pOut->PrintMessage(" File is saved successfully :) "); // optional
	

		}
		saveFile.close();
	}
}
