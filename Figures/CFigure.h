#ifndef CFIGURE_H
#define CFIGURE_H

#include "..\defs.h"
#include "..\GUI\Output.h"


//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	bool Hidden; ////karim
	GfxInfo FigGfxInfo;	//Figure graphis info
	static int countForID; // to make give every figure a unique Id 
	
	/// Add more parameters if needed.

public:
	CFigure();  /// optional  or should i do default paramaters
	CFigure(GfxInfo FigureGfxInfo);

	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual bool belongsTo(int, int) = 0;

	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	virtual void move(Point) = 0;	//to move the figure
	virtual Point getPreCoord() = 0;
	virtual bool getMovingValidity(Point p)=0;

	
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	

    virtual void Save(fstream &saveFile) = 0 ;	//Save the figure parameters to the file
	virtual void Load(fstream &Infile) =0;	//Load the figure parameters to the file

	//print all figure info on the status bar
	virtual void PrintInfo(Output* pOut)=0 ;	//print all figure info on the status bar
	void Hide();
	void Show();
	bool IsHidden();
	virtual string GetShapeType() = 0;
	GfxInfo Info();
	virtual Point* IsNearCorner(double a, double b,int &n) = 0;
	virtual void Resize(Point a, Point* b,int n) = 0;
	virtual bool Resizemax() = 0;
};

#endif