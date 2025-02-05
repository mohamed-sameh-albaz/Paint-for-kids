#include "Input.h"
#include "Output.h"

Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}
void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
void Input::QuesPointClicked()
{
	pWind->FlushMouseQueue();
}
void Input::QuesKeyClicked()
{
	pWind->FlushKeyQueue();
}
void Input::CheckPointClicked(int CaseShape, Output* outPtr, Point& P1, Point* P2) const
{
	//writing on statusBar for validity check

	switch (CaseShape)
	{

	case ITM_RECT:		//Rectangle Validity
	{
		while (P1.y < UI.ToolBarHeight|| UI.height- P1.y<UI.StatusBarHeight)
		{
			outPtr->ClearStatusBar();
			outPtr->PrintMessage("Failed to Draw a Rectangle, Please Click another point.");
			GetPointClicked(P1.x, P1.y);
		}
		break;
	}

	case ITM_CIRC:		//Circle validity
	{
		while (P1.y < UI.ToolBarHeight || UI.height - P1.y < UI.StatusBarHeight) //////check the center 
		{
			outPtr->ClearStatusBar();
			outPtr->PrintMessage("Failed to put the Center of the Circle, Please Click another point.");
			GetPointClicked(P1.x, P1.y);
			outPtr->ClearStatusBar();
		}
		while (P1.y - sqrt(pow((P2->x - P1.x), 2) + pow((P2->y - P1.y), 2)) < UI.ToolBarHeight ||
			UI.height - (P1.y + sqrt(pow((P2->x - P1.x), 2) + pow((P2->y - P1.y), 2))) < UI.StatusBarHeight||
			P1.x - sqrt(pow((P2->x - P1.x), 2) + pow((P2->y - P1.y), 2))<0|| P1.x + sqrt(pow((P2->x - P1.x), 2) + pow((P2->y - P1.y), 2))>UI.width-15) //////chaeck for raduis 
		{
			outPtr->ClearStatusBar();
			outPtr->PrintMessage("Failed to Draw a Circle, Please Click another point.");
			GetPointClicked(P2->x, P2->y);
			outPtr->ClearStatusBar();
		}
		break;
	}

	case ITM_TRI:
	{
		while (P1.y < UI.ToolBarHeight|| UI.height - P1.y < UI.StatusBarHeight)		//Triangle Validity
		{
			outPtr->ClearStatusBar();
			outPtr->PrintMessage("Failed to Draw a Triangle, Please Click another point.");
			GetPointClicked(P1.x, P1.y);
			outPtr->ClearStatusBar();

		}
		outPtr->PrintMessage("Drawing a Triangle, Continue choosing the rest of the points");
		break;
	}

	case ITM_HEX:
	{
		while (P1.y - outPtr->GetLengthHex() * cos((cdPi / 6)) < UI.ToolBarHeight ||
			UI.height - (P1.y + outPtr->GetLengthHex() * cos((cdPi / 6)))<UI.StatusBarHeight||
			P1.x - outPtr->GetLengthHex() * cos((cdPi / 6)) < 0 || (P1.x + outPtr->GetLengthHex() * cos((cdPi / 6))) > UI.width-15)		//Hexagon validity
		{
			outPtr->ClearStatusBar();
			outPtr->PrintMessage("Failed to Draw a Hexagon, Please Click another point.");
			GetPointClicked(P1.x, P1.y);
			outPtr->ClearStatusBar();
		}
		break;
	}

	case ITM_SQU:
	{
		while (P1.y - outPtr->GetLengthSq() / 2 < UI.ToolBarHeight||
			UI.height - (P1.y + outPtr->GetLengthSq() / 2) < UI.StatusBarHeight||
			P1.x - outPtr->GetLengthSq() / 2 < 0 || (P1.x + outPtr->GetLengthSq() / 2) > UI.width-15)		//Square validity
		{
			outPtr->ClearStatusBar();
			outPtr->PrintMessage("Failed to Draw a Square, Please Click another point.");
			GetPointClicked(P1.x, P1.y);
			outPtr->ClearStatusBar();
		}
		break;
	}
	}

}





buttonstate Input::mouseHeld(int& iX, int& iY)
{
	return pWind->GetButtonState(LEFT_BUTTON, iX, iY);
}

void Input::getMouseCoord(int& iX, int& iY)
{
	pWind->GetMouseCoord(iX, iY);
}

string Input::GetString(Output* pO) const
{


	string Label;
	char Key;
	while (1)
	{

		pWind->WaitKeyPress(Key);
		if (Key == 27)			//ESCAPE key is pressed
			return "";			//returns nothing as user has cancelled label
		if (Key == 13)			//ENTER key is pressed
		{
			return Label;
		}
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check which Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x cord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_SLCT: return SELECT;
			case ITM_SHAPES: return TO_ShapesToolBar;
			case ITM_PLYMOD: return TO_PLAY;
			case ITM_COLOR: return TO_COLOR;
			case ITM_FILL: return TO_FILL;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_DLET: return DEL;
			case ITM_CLR: return CLEAR;
			case ITM_MOVE: return MOVE;
			case ITM_RESIZE: return RESIZE;
			case ITM_DRAG: return DRAG;
			case ITM_REC: return RECVID;
			case ITM_END: return ENDVID;
			case ITM_PLY: return PLYVID;
			case ITM_SAVE: return SAVE;
			case ITM_LOAD: return LOAD;
			case ITM_VOICE: return VOICE;
			case ITM_EXIT_DRAWMODE: return EXIT;
			
			default: return EMPTY;	//A click on empty place in design toolbar
			}
		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_PLAY)	//GUI is in PLAY mode
	{

		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder) {

			case ITM_SWITCH:return TO_DRAW;
			case ITM_TYP_COLOR:return PLAYCOLOR;
			case ITM_TYP_SHAPE:return PLAYSHAPE;
			case ITM_TYP_BOTH:return PLAYBOTH;
			case ITM_EXIT_PLAYMODE:return EXIT;

			default: return EMPTY;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		return STATUS;
	}
	else if (UI.InterfaceMode == MODE_PLAY)	//GUI is in PLAY mode
	{

		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder) {

			case ITM_SWITCH:return TO_DRAW;
			case ITM_TYP_COLOR:return PLAYCOLOR;
			case ITM_TYP_SHAPE:return PLAYSHAPE;
			case ITM_TYP_BOTH:return PLAYBOTH;
			case ITM_EXIT_PLAYMODE:return EXIT;

			default: return EMPTY;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		return STATUS;
	}
	else if (UI.InterfaceMode == COLOR_SELECTION) //GUI is in Color Selection
	{
		if (y >= UI.ToolBarHeight && y < 2 * UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth) -1 ;

			switch (ClickedItemOrder) {

			case ITM_BLACK:return SELECT_BLACK;
			case ITM_BLUE:return SELECT_BLUE;
			case ITM_GREEN:return SELECT_GREEN;
			case ITM_ORANGE:return SELECT_ORANGE;
			case ITM_RED:return SELECT_RED;
			case ITM_YELLOW:return SELECT_YELLOW;


			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}
		else if (y >= 0 && y < UI.ToolBarHeight)
		{
			return TOOLBAR;
		}

		return STATUS;
	}
	else if (UI.InterfaceMode == FILL_COLOR_SELECTION) //GUI is in Fill Color Selection
	{
		if (y >= UI.ToolBarHeight && y < 2 * UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth) - 3;



			switch (ClickedItemOrder) {

			case ITM_NO_FILL:return SELECT_NO_FILL;
			case ITM_BLACK:return SELECT_BLACK_FILL;
			case ITM_BLUE:return SELECT_BLUE_FILL;
			case ITM_GREEN:return SELECT_GREEN_FILL;
			case ITM_ORANGE:return SELECT_ORANGE_FILL;
			case ITM_RED:return SELECT_RED_FILL;
			case ITM_YELLOW:return SELECT_YELLOW_FILL;

			default: return EMPTY;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}
		else if (y >= 0 && y < UI.ToolBarHeight)
		{
			return TOOLBAR;
		}

		return STATUS;

	}
	else if (UI.InterfaceMode == SHAPES_SELECTION) //GUI is in Shapes Selection
	{
		if (y >= UI.ToolBarHeight && y < 2 * UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder) {
			case ITM_RECT:return DRAW_RECT;
			case ITM_CIRC:return DRAW_CIRCLE;
			case ITM_TRI:return DRAW_TRIANGLE;
			case ITM_HEX:return DRAW_HEXAGON;
			case ITM_SQU:return DRAW_SQUARE;

			default: return EMPTY;

			}

		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}
		else if (y >= 0 && y < UI.ToolBarHeight)
		{
			return TOOLBAR;
		}
		return STATUS;

	}
}

Input::~Input() {}
buttonstate Input::GetMouseState(int &a, int &b)
{
	return pWind->GetButtonState(LEFT_BUTTON, a, b);
}
