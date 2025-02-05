#pragma once
#include "Figures/CFigure.h"
class CTriangle :
    public CFigure
{private:
    Point vertex1;
    Point vertex2;
    Point vertex3;
    Point cntr;//used for moving the figure
    bool canMove;
   

public:
    CTriangle(); 
    CTriangle(Point, Point, Point, GfxInfo FigureGfxInfo);
    virtual void Draw(Output* pOut) const;
    virtual bool belongsTo(int, int);
    virtual void PrintInfo(Output* pOut);
    virtual void move(Point);
    virtual Point getPreCoord();
    virtual bool getMovingValidity(Point P);
    virtual string GetShapeType();
    Point* IsNearCorner(double a, double b,int& n);
    void Resize(Point a, Point* b, int n);
    virtual bool Resizemax();

    virtual void Save(fstream& saveTgl);
    virtual void Load(fstream& loadTgl);
};

