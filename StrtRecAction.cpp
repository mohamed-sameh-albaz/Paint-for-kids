#include "StrtRecAction.h"
#include "ApplicationManager.h"
#include<fstream>
using namespace std;
int  Action::operationCount = 0;
StrtRecAction::StrtRecAction(ApplicationManager* pApp) :Action(pApp)
{
}

void StrtRecAction::ReadActionParameters()
{
}

void StrtRecAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (!pManager->GetIsRecording())
	{
		if (pManager->GetFigCount())
		{
			pOut->PrintMessage("Error : You can't record operations unless you first  use clear all ");

		}
		else
		{
			pManager->ClearAll();  
			fstream Rec(recordFile, ios::out);
			pOut->PrintMessage(" start Recording ..( maximum 20 operations) ");

			pManager->SetIsRecording(true); 
			//Action::recordFile.open(file,OUT);
			string currentDrawcolor = pOut->getCrntDrawColor();      
			string currentfillcolor;
			currentfillcolor = (pOut->CrntFillingFlag()) ? pOut->getCrntFillColor() : string("NO_FILL");
			Rec << "\t" << currentDrawcolor << "\t" << currentfillcolor << "\t" <<pOut->shapenum << "\t" << pOut->colornum << "\t" << pOut->fillcolornum << endl;
			Rec.close();
		}
	}
	
	if (!pManager->isMuted())
		PlaySound("sounds/rec_effect", NULL, SND_ASYNC);
}
