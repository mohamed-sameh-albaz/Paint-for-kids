#pragma once
#include "Figures/CFigure.h"
class CCircle :public CFigure
{
private:
	Point Centre;
	Point CircPoint;
	bool canMove;

public:
	CCircle();
	CCircle(Point, Point, GfxInfo FigureGfxInfo);
	virtual void Draw(Output* pOut) const;
	virtual bool belongsTo(int,int);
	virtual void PrintInfo(Output* pOut);
	virtual void move(Point);
	virtual Point getPreCoord();
	virtual bool getMovingValidity(Point P);
	virtual string GetShapeType();
	Point* IsNearCorner(double a, double b,int& n);
	void Resize(Point a, Point* b, int n);
	virtual bool Resizemax();
	virtual void Save(fstream& saveCir);
	virtual void Load(fstream& loadCir);

};

