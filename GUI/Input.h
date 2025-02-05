#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;   // forward declaration

class Input		//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	//enum PopUpAction { TO_ShapesToolBar, TO_COLOR, TO_FILL};
	int popUpActionType = 0;
	Input(window* pW);		//Constructor
	void GetPointClicked(int& x, int& y) const;//Get coordinate where user clicks

	void CheckPointClicked(int a, Output* statusPo, Point& P, Point* P2 = NULL) const;
	//We need the second point pointer to make it null in each case except the circle

	void QuesPointClicked();	 //This is necessary because if someone accidentally hits a key or clicks 
	void QuesKeyClicked();		// the mouse that event will stay in the buffer until it
	// is removed, which may be at a time that input would be wanted by the user	

	buttonstate mouseHeld(int& iX, int& iY);

	void getMouseCoord(int& iX, int& iY);

	string GetString(Output* pO) const;	 //Returns a string entered by the user

	ActionType GetUserAction() const; //Read the user click and map to an action

	~Input();
	buttonstate GetMouseState(int& a, int& b);
};

#endif
