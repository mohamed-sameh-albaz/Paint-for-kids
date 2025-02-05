#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point cntr;//used for moving the figure
	bool canMove;
	bool again;
public:
	CRectangle();
	CRectangle(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	virtual bool belongsTo(int, int);
	virtual void PrintInfo(Output* pOut);
	virtual void move(Point);
	virtual Point getPreCoord();
	virtual bool getMovingValidity(Point P);
	virtual string GetShapeType();
	Point* IsNearCorner(double a, double b, int& n);
	void Resize(Point a, Point* b, int n);
	virtual bool Resizemax();
	 
	virtual void Save(fstream& saveRect);
	virtual void Load(fstream& loadRect);

};

#endif