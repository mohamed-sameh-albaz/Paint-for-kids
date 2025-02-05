#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H
#include "..\Figures\CRectangle.h"

#include "Action.h"
#include "..\Figures\CRectangle.h"

//Add Rectangle Action class
class AddRectAction: public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
	CRectangle* Rect;
public:
	AddRectAction(ApplicationManager *pApp);

	//Reads rectangle parameters            NOTE: we need to know why there is the virtual keyword
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual void Execute() ;
	virtual void UndoAction();
	virtual void RedoAction();
	virtual void Record();
	virtual void Play(fstream& Play);
};

#endif