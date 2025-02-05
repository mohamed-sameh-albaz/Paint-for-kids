#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "popUpAction.h"
#include "clearPopUpAction.h"
#include "AddCircAction.h"
#include "AddTrnglAction.h"
#include "AddHexAction.h"
#include "AddSqrAction.h"
#include "AddColorAction.h"
#include "AddFillAction.h"
#include "selectAction.h"
#include "UndoAction.h"
#include "RedoAction.h"
#include "DeleteAction.h"
#include "ClrAllAction.h"
#include "StrtRecAction.h"
#include "EndRecAction.h"
#include "PlayRecAction.h"
#include "SaveAction.h"
#include "LoadAction.h"
#include "PlyModAction.h"
#include "MoveAction.h"
#include "Actions/ResizeAction.h"
#include "PlyModAction.h"
#include "PlyModShapes.h"
#include "PlyModColors.h"
#include "PlyModBoth.h"
#include "DrwModAction.h"
#include "ExitAction.h"
#include "DragAction.h"
#include "voiceAction.h"

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	FigCount = 0;
	UndoCnt = 0;
	redoCnt = 0;
	willBeDeleted = false;
	PopUp = true;
	pOut->shapenum = 0;
	isRecording = false;
	muted = false;
	isPlaying = false;

	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
	for (int i = 0; i < 5; i++)
	{
		UndoRedoList[i] = NULL;
		TempUndoRedoList[i] = NULL;
	}
	for (int i = 0; i < 2000; i++)
	{
		deletedFigList[i] = NULL;
	}
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	Action* pPopUp = NULL;
	switch (ActType)
	{	
		case SELECT:
			pAct = new selectAction(this);
			break;
		case TO_ShapesToolBar:
			pAct = new popUpAction(TO_ShapesToolBar,this);
			PopUp = false;
			break;
		case DRAW_RECT:
			PopUp = true;
			pOut->shapenum = 1;
			pPopUp = new clearPopUpAction(TO_ShapesToolBar,this);
			pAct = new AddRectAction(this);
			break;
		case DRAW_CIRCLE:
			PopUp = true;
			pOut->shapenum = 2;
			pPopUp = new clearPopUpAction(TO_ShapesToolBar, this);
			pAct = new AddCircAction(this);
			break;
		case DRAW_TRIANGLE:
			PopUp = true;
			pOut->shapenum = 3;
			pPopUp = new clearPopUpAction(TO_ShapesToolBar, this);
			pAct = new AddTrnglAction(this);
			break;
		case DRAW_HEXAGON:
			PopUp = true;
			pOut->shapenum = 4;
			pPopUp = new clearPopUpAction(TO_ShapesToolBar, this);
			pAct = new AddHexAction(this);
			break;
		case DRAW_SQUARE:
			PopUp = true;
			pOut->shapenum = 5;
			pPopUp = new clearPopUpAction(TO_ShapesToolBar, this);
			pAct = new AddSqrAction(this);
			break;
		case TO_COLOR:
			pAct = new popUpAction(TO_COLOR, this);
			PopUp = false;
			break;
		case SELECT_BLACK:
			PopUp = true;
			pOut->colornum = 1;
			pPopUp = new clearPopUpAction(TO_COLOR, this);
			pAct = new AddColorAction(this);
			break;
		case SELECT_BLUE:
			PopUp = true;
			pOut->colornum = 2;
			pPopUp = new clearPopUpAction(TO_COLOR, this);
			pAct = new AddColorAction(this);
			break;
		case SELECT_GREEN:
			PopUp = true;
			pOut->colornum = 3;
			pPopUp = new clearPopUpAction(TO_COLOR, this);
			pAct = new AddColorAction(this);
			break;
		case SELECT_ORANGE:
			PopUp = true;
			pOut->colornum = 4;
			pPopUp = new clearPopUpAction(TO_COLOR, this);
			pAct = new AddColorAction(this);
			break;
		case SELECT_RED:
			PopUp = true;
			pOut->colornum = 5;
			pPopUp = new clearPopUpAction(TO_COLOR, this);
			pAct = new AddColorAction(this);
			break;
		case SELECT_YELLOW:
			PopUp = true;
			pOut->colornum = 6;
			pPopUp = new clearPopUpAction(TO_COLOR, this);
			pAct = new AddColorAction(this);
			break;
		case TO_FILL:
			pAct = new popUpAction(TO_FILL, this);
			PopUp = false;
			break;
		case SELECT_NO_FILL:
			PopUp = true;
			pOut->fillcolornum = 0;
			pPopUp = new clearPopUpAction(TO_FILL, this);
			pAct = new AddFillAction(this);
			break;
		case SELECT_BLACK_FILL:
			PopUp = true;
			pOut->fillcolornum = 1;
			pPopUp = new clearPopUpAction(TO_FILL, this);
			pAct = new AddFillAction(this);
			break;
		case SELECT_BLUE_FILL:
			PopUp = true;
			pOut->fillcolornum = 2;
			pPopUp = new clearPopUpAction(TO_FILL, this);
			pAct = new AddFillAction(this);
			break;
		case SELECT_GREEN_FILL:
			PopUp = true;
			pOut->fillcolornum = 3;
			pPopUp = new clearPopUpAction(TO_FILL, this);
			pAct = new AddFillAction(this);
			break;
		case SELECT_ORANGE_FILL:
			PopUp = true;
			pOut->fillcolornum = 4;
			pPopUp = new clearPopUpAction(TO_FILL, this);
			pAct = new AddFillAction(this);
			break;
		case SELECT_RED_FILL:
			PopUp = true;
			pOut->fillcolornum = 5;
			pPopUp = new clearPopUpAction(TO_FILL, this);
			pAct = new AddFillAction(this);
			break;
		case SELECT_YELLOW_FILL:
			PopUp = true;
			pOut->fillcolornum = 6;
			pPopUp = new clearPopUpAction(TO_FILL, this);
			pAct = new AddFillAction(this);
			break;
		case UNDO:
			pAct = new UndoAction(this);
			break;
		case REDO:
			pAct = new RedoAction(this);
			break;
		case DEL:
			pAct = new DeleteAction(this);
			break;
		case CLEAR:
			pAct = new ClrAllAction(this);
			break;
		case MOVE:
			pAct = new MoveAction(this);
			break;
		case RESIZE:
			pAct = new ResizeAction(this);
		case DRAG:
			pAct = new DragAction(this);
			break;
		case RECVID:
			pAct = new StrtRecAction(this);
			break;
		case ENDVID:
			pAct = new EndRecAction(this);
			break;
		case PLYVID:
			pAct = new PlayRecAction(this);
			break;
		case SAVE:
			pAct = new SaveAction(this);
			break;
		case LOAD:
			pAct = new LoadAction(this);
			break;
		case TO_PLAY:
			pAct = new PlyModAction(this);
			break;
		case VOICE:
			pAct = new voiceAction(this);
			break;
		case PLAYCOLOR:
			pAct = new PlyModColors(this);
			break;
		case PLAYSHAPE:
			pAct = new PlyModShapes(this);
			break;
		case PLAYBOTH:
			pAct = new PlyModBoth(this);
			break;
		case TO_DRAW:
			pAct = new DrwModAction(this);
			break;
		case EXIT:
			pAct = new ExitAction(this);
			break;
		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	//Execute the created action
	if (pPopUp != NULL) 
	{
		pPopUp->Execute(); 
		delete pPopUp;
		pPopUp = NULL;
	}
	if(pAct != NULL)
	{
		willBeDeleted = false;//default 
		pAct->Execute();//Execute
		if(!willBeDeleted)
		{
			delete pAct;	//You may need to change this line depending to your implementation
			pAct = NULL;
		}
	}
}
void ApplicationManager::AddActToUndoRedo(Action* pAct)
{
	if (pAct)
	{
		if (UndoCnt < MaxUndoRedoCnt)
		{
			UndoRedoList[UndoCnt] = pAct;
			TempUndoRedoList[UndoCnt] = UndoRedoList[UndoCnt];
			UndoCnt++;
		}
		else
		{
			delete UndoRedoList[0]; //first action in the list deleted here
			// not after the switch up in the execute func
			UndoRedoList[0] = NULL; 
			for(int i=0;i<MaxUndoRedoCnt-1;i++)
			{
				UndoRedoList[i] = UndoRedoList[i + 1];
				TempUndoRedoList[i] = TempUndoRedoList[i+1];
			}
			UndoRedoList[4] = pAct;
			TempUndoRedoList[4] = pAct;
		}
	}
}
void ApplicationManager::UndoAct()
{
	UndoRedoList[--UndoCnt]->UndoAction();
	UndoRedoList[UndoCnt]=NULL;
	pOut->ClearDrawArea();
	//still in Temp list for redo
}

void ApplicationManager::RedoAct()
{
	if (UndoRedoList[UndoCnt] == NULL)
	{
		UndoRedoList[UndoCnt] = TempUndoRedoList[UndoCnt];
	}
	UndoRedoList[UndoCnt++]->RedoAction();
}

int ApplicationManager::getUndoCnt()
{
	return UndoCnt;
}

int ApplicationManager::getRedoCnt()
{
	return redoCnt;
}

int ApplicationManager::setRedoCnt(int cnt)
{
	redoCnt = cnt > 0 ? cnt : 0;
	return redoCnt;
}

void ApplicationManager::ResetUndoCnt()
{
	UndoCnt=0;
}

void ApplicationManager::ResetRedoCnt()
{
	redoCnt = 0;
}

void ApplicationManager::setMuted(bool s)
{
	muted = s;
}
bool ApplicationManager::isMuted()
{
	return muted;
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) // NOTE!!!! I deleted the CONST keyword
{
	SelectedFig = NULL;
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	for (int i = 0; i < FigCount; i++)
	{
		if (!(FigList[i]->IsHidden()))
		{
			if (FigList[i]->belongsTo(x, y)) 
			{
				SelectedFig = FigList[i];
				return SelectedFig;
			}
		}
	}
	return SelectedFig ;

}

CFigure* ApplicationManager::GetLastSelected() // NOTE!!!! I deleted the CONST keyword
{
	
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected()) return FigList[i];
	return NULL;
}

void ApplicationManager::DeleteSelectedFig(CFigure* SelectedFigure)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (SelectedFigure == FigList[i])
		{
			int k = 0;
			bool freePosition = false;
			while(k<2000&&!freePosition)
			{
				if (deletedFigList[i] == NULL)
				{
					deletedFigList[i] = SelectedFig;
					freePosition = true;
				}
				k++;
			}
			SelectedFig = NULL;
			FigList[i] = FigList[--FigCount];
			FigList[FigCount] = NULL;
			break;
		}
	}
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i] == NULL)
		{
			FigList[i] = FigList[i + 1];
		}
	}
}

void ApplicationManager::setWillBeDeleted(bool flag)
{
	willBeDeleted = flag;
}

bool ApplicationManager::getWillBeDeleted()
{
	return willBeDeleted;

}

void ApplicationManager::ClearAll()
{
	for (int i = 0; i < FigCount; i++)
	{
		if(FigList[i]!=NULL)
		{
			delete FigList[i];
			FigList[i] = NULL;
		}
	}
	FigCount = 0;
}

void ApplicationManager::ClearUndoRedoList()
{
	for (int i = 0; i < UndoCnt; i++)
	{
		if(UndoRedoList[i]!=NULL)
		{
			delete UndoRedoList[i];
			UndoRedoList[i] = NULL;
		}
	}
}

int ApplicationManager::GetFigCount() const
{
	return FigCount;
}

void ApplicationManager::SetIsRecording(bool record)
{
	isRecording = record;
}

void ApplicationManager::SetIsPlaying(bool play)
{
	isPlaying = play;
}

bool ApplicationManager::GetIsPlaying() const
{
	return isPlaying;
}

bool ApplicationManager::GetIsRecording() const
{
	return isRecording;
}

void ApplicationManager::SaveAllFigures(fstream& saveFile)  
{

	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(saveFile);

}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const {
	for (int i = 0; i < FigCount; i++) {
		if (PopUp && !FigList[i]->IsHidden())
		{
			FigList[i]->Draw(pOut);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < 2000; i++)
	{
		//delete deletedFigList[i];
		deletedFigList[i] = NULL;
	}
	for (int i = 0; i < MaxUndoRedoCnt; i++)
	{	
		if(UndoRedoList[i]!=NULL)
		{
			UndoRedoList[i] = NULL;
		}
		if (TempUndoRedoList[i] != NULL)
		{
			TempUndoRedoList[i] = NULL;
		}
	}
	for(int i=0; i<FigCount; i++)
	{
		delete FigList[i];
	}
	delete pIn;
	delete pOut;
}
////////////////////////////////////////////////////////////////
CFigure* ApplicationManager::ReturnFigure(int a) const
{
	return FigList[a];
}
/////////////////////////////
int ApplicationManager::ReturnFigCount() const
{
	return FigCount;
}