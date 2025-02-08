#include "PlayRecAction.h"
#include "ApplicationManager.h"
#include<fstream>
#include "CTriangle.h"
#include "Figures/CRectangle.h"
#include "CHexagon.h"
#include "CSquare.h"
#include "CCircle.h"
#include "MoveAction.h"
#include "AddColorAction.h"
#include "AddFillAction.h"
#include "selectAction.h"
#include "UndoAction.h"
#include "RedoAction.h"
#include "DeleteAction.h"
#include "ClrAllAction.h"
#include "popUpAction.h"
#include "clearPopUpAction.h"
#include "Actions\AddRectAction.h"
#include "AddCircAction.h"
#include "AddTrnglAction.h"
#include "AddHexAction.h"
#include "AddSqrAction.h"
PlayRecAction::PlayRecAction(ApplicationManager* pApp) :Action(pApp)
{
}

void PlayRecAction::ReadActionParameters()
{
}

void PlayRecAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	fstream playFile(recordFile);
	


	{


		if (!pManager->GetIsRecording())
		{
			if (pManager->GetFigCount())
			{
				pManager->ClearAll();

			}
			pManager->SetIsPlaying(true);   /// for read information 
			pOut->PrintMessage(" Play Recording ");
			string currentDrawcolor;
			string currentfillcolor;
			playFile >> currentDrawcolor;
			playFile >> currentfillcolor;
			UI.DrawColor = currentDrawcolor;

			if (currentfillcolor == "NO_FILL")
				UI.FillColor = UI.BkGrndColor;                 // true or not ??optional
			else
				UI.FillColor = currentfillcolor;

			playFile >> pOut->shapenum >> pOut->colornum >> pOut->fillcolornum;
			pOut->CreateShapesToolBarTAB();
			pOut->CreateColorsToolBarTAB();
			pOut->CreateFillColorsToolBarTAB();

			Action* pAct = NULL;
			Action* pAddPopUp = NULL;
			Action* pClrPopUp = NULL;

			string type;
			while (!playFile.eof())
			{

				playFile >> type;
				if (type == "Select")
				{
					pAct = new selectAction(pManager);

				}
				else if (type == "Move")
				{
					pAct = new MoveAction(pManager);
				}
				else if (type == "Delete")
				{
					pAct = new DeleteAction(pManager);
				}
				else if (type == "Undo")
				{
					pAct = new Undoaction(pManager);
				}
				else if (type == "Redo")
				{
					pAct = new Redoaction(pManager);
				}
				else if (type == "popUpAction")
				{
					int typePopUp;
					playFile >> typePopUp;
					ActionType PopAct;
					string name;
					switch (typePopUp)
					{
					case TO_ShapesToolBar:
						PopAct = TO_ShapesToolBar;
						playFile >> pOut->shapenum;
						pAddPopUp = new popUpAction(PopAct, pManager);
						pClrPopUp = new clearPopUpAction(PopAct, pManager);
						//playFile.ignore(6);
						playFile >> name;
						switch (pOut->shapenum)
						{
						case ITM_RECT:
							pAct = new AddRectAction(pManager);
							break;
						case ITM_CIRC:
							pAct = new AddCircAction(pManager);
							break;
						case ITM_TRI:
							pAct = new AddTrnglAction(pManager);
							break;
						case ITM_HEX:
							pAct = new AddHexAction(pManager);
							break;
						case ITM_SQU:
							pAct = new AddSqrAction(pManager);
							break;
						}
						break;
					case TO_COLOR:
						PopAct = TO_COLOR;

						pAddPopUp = new popUpAction(PopAct, pManager);
						playFile >> pOut->colornum;
						pClrPopUp = new clearPopUpAction(PopAct, pManager); /// optional I commented the body of it in record func
						pAct = new AddColorAction(pManager);
						break;
					case TO_FILL:
						PopAct = TO_FILL;
						pAddPopUp = new popUpAction(PopAct, pManager);
						playFile >> pOut->fillcolornum;
						pClrPopUp = new clearPopUpAction(PopAct, pManager);
						pAct = new AddFillAction(pManager);
						break;

					}
					if (pAddPopUp != NULL)
					{
						Sleep(1000);
						pAddPopUp->Execute();// optional   can be only one body with last func
						pManager->UpdateInterface();
						delete pAddPopUp;
						pAddPopUp = NULL;
					}
					if (pClrPopUp != NULL)
					{
						Sleep(1000);
						pClrPopUp->Execute();
						pManager->UpdateInterface();
						delete pClrPopUp;
						pClrPopUp = NULL;
					}
					if (pAct != NULL)
					{
						Sleep(1000);
						bool willBeDeleted;
						willBeDeleted = false;//default
						pAct->Play(playFile);//Execute
						pManager->UpdateInterface();
						if (!willBeDeleted)
						{
							delete pAct;    //You may need to change this line depending to your implementation
							pAct = NULL;
						}
					}
				}
			}
		}
		pManager->SetIsPlaying(false);
	}
	pOut->PrintMessage("done");
}

