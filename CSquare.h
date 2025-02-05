#pragma once
#include "Figures/CFigure.h"
class CSquare :
    public CFigure
{
private:
    Point Centre;
    int sqLen;
    bool canMove;
    int oldsqLen;
public:
    CSquare(int l);
    CSquare(Point,int, GfxInfo FigureGfxInfo);
    virtual void Draw(Output* pOut) const;
    virtual bool belongsTo(int,int);
    virtual void PrintInfo(Output* pOut);
    virtual void move(Point);
    virtual Point getPreCoord();
    virtual bool getMovingValidity(Point p);
    virtual string GetShapeType();
    Point* IsNearCorner(double a, double b,int &n);
    void Resize(Point a, Point*b,int n);
    virtual bool Resizemax();
    virtual void Save(fstream& saveSq);
    virtual void Load(fstream& loadSq);

};

