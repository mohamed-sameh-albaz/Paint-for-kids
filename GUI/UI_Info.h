#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,				//Drawing mode (startup mode)
	MODE_PLAY,				//Playing mode
	COLOR_SELECTION,		//Color toolbar
	FILL_COLOR_SELECTION,	//Fillers toolbar
	SHAPES_SELECTION		//Shapes toolbar
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{
	//Note: Items are **(ordered)** here as they appear in menu
	//If you want to change the menu items order, change the order here
	ITM_SLCT,
	ITM_SHAPES,
	ITM_COLOR,
	ITM_FILL,
	ITM_UNDO,
	ITM_REDO,
	ITM_DLET,
	ITM_CLR,
	ITM_MOVE,
	ITM_RESIZE,
	ITM_DRAG,
	ITM_REC,
	ITM_END,
	ITM_PLY,
	ITM_SAVE,
	ITM_LOAD,
	ITM_PLYMOD,
	ITM_VOICE,
	ITM_EXIT_DRAWMODE,
	DRAW_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu 
{
	ITM_TYP_COLOR,
	ITM_TYP_SHAPE,
	ITM_TYP_BOTH,
	ITM_SWITCH,
	ITM_EXIT_PLAYMODE,
	PLAY_ITM_COUNT

};
enum ShapesItems  //The items of the Shapes menu
{
	ITM_SHAPE,		//Blank item in draw mode
	ITM_RECT,		//Rectangle item in toolbar
	ITM_CIRC,		//Circle item in toolbar
	ITM_TRI,		//Triangle item in toolbar
	ITM_HEX,		//Hexagon item in toolbar
	ITM_SQU,		//Square item in toolbar
	SHAPES_ITM_COUNT
};
enum ColorItems  //The items of the Colors menu
{

	ITM_NONE,		//Blank item in draw mode
	ITM_BLACK,		//Black color in toolbar
	ITM_BLUE,		//Blue color in toolbar
	ITM_GREEN,		//Green color in toolbar
	ITM_ORANGE,		//Orange color in toolbar
	ITM_RED,		//Red color in toolbar
	ITM_YELLOW,		//Yellow color in toolbar
	COLOR_ITM_COUNT
};
enum FillColorItems  //The items of the FillColors menu
{

	ITM_NO_FILL,		//Blank item in draw mode and no fill in toolbar
	ITM_BLACK_FILL,		//Black fill color in toolbar
	ITM_BLUE_FILL,		//Blue fill color in toolbar
	ITM_GREEN_FILL,		//Green fill color in toolbar
	ITM_ORANGE_FILL,	//Orange fill color in toolbar
	ITM_RED_FILL,		//Red fill color in toolbar
	ITM_YELLOW_FILL,	//Yellow fill color in toolbar
	FILL_COLOR_ITM_COUNT
};



__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,	    //Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Height
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth;		//Width of each item in toolbar menu


	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	int PenWidth;			//width of the pen that draws shapes


}UI;	//create a global object UI

#endif
