#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	SELECT,
	TO_ShapesToolBar,
	DRAW_RECT,
	DRAW_SQUARE,
	DRAW_CIRCLE,
	DRAW_TRIANGLE,
	DRAW_HEXAGON,
	EXIT,
	TO_DRAW,			// Switch interface to Draw mode
	TO_PLAY,			// Switch interface to Play mode
	TO_COLOR,
	TO_FILL,
	UNDO,
	REDO,
	DEL,				// Select delete figure
	CLEAR,				// Clear all figures
	MOVE,				// Move figures
	RESIZE,
	DRAG,				// Dragging figures
	RECVID,				// Start recording video
	ENDVID,				// End recording video
	PLYVID,				// Play video
	SAVE,				// Save the file
	LOAD,				// Load saved files
	PLAYCOLOR,			// Select color to play with
	PLAYSHAPE,			// Select the shape to play with
	PLAYBOTH,			// Select both colors and shapes to play with
	VOICE,
	EMPTY,				// A click on empty place in the toolbar
	TOOLBAR,			// A click on the toolbar 
	DRAWING_AREA,		// A click on the drawing area
	STATUS,				// A click on the status bar
	SELECT_BLACK,
	SELECT_BLUE,
	SELECT_GREEN,
	SELECT_ORANGE,
	SELECT_RED,
	SELECT_YELLOW,
	SELECT_BLACK_FILL,
	SELECT_BLUE_FILL,
	SELECT_GREEN_FILL,
	SELECT_ORANGE_FILL,
	SELECT_RED_FILL,
	SELECT_YELLOW_FILL,
	SELECT_NO_FILL


};

struct Point	//To be used for figures points
{
	int x, y;
	Point operator=(Point p) {
		x = p.x;
		y = p.y;
		return *this;
	}
	Point operator-(Point p) const {
		Point z;
		z.x = x - p.x;
		z.y = y - p.y;
		return z;
	}
	Point operator+(Point p) const {
		Point z;
		z.x = x + p.x;
		z.y = y + p.y;
		return z;
	}
};

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif