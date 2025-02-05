#include "CRectangle.h"
#include <string>
#include <fstream>
CRectangle::CRectangle()
{
}
CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	ID = ++countForID;
	//canMove = false;
	cntr.x = (Corner1.x + Corner2.x) / 2;
	cntr.y = (Corner1.y + Corner2.y) / 2;
	again = true;
}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

bool CRectangle::belongsTo(int x, int y)
{
	//corner3 is (Corner2.x,Corner1.y) ,corner 4 (Corner1.x,Corner2.y)
	int A, A1, A2, A3, A4;
	A = abs((Corner1.x - Corner2.x) * (Corner1.y - Corner2.y));//The area of the whole rectangle
	A1 = abs((x - Corner1.x) * (y - Corner1.y));	//The area of the rectangle between P and Corner1
	A2 = abs((x - Corner2.x) * (y - Corner2.y));	//The area of the rectangle between P and Corner2
	A3 = abs((x - Corner2.x) * (y - Corner1.y));	//The area of the rectangle between P and Corner3
	A4 = abs((x - Corner1.x) * (y - Corner2.y));	//The area of the rectangle between P and Corner4
	
	if (A == A1 + A2 + A3 + A4) 
		return true;

	else return false;
}

void CRectangle::PrintInfo(Output* pOut)
{
	string DrawClr = FigGfxInfo.DrawClr;// Type conversion (from color to string)
	string FIllClr = FigGfxInfo.isFilled ? FigGfxInfo.FillClr :(string)(" No Fill");
	
	string msg = "The ID is " + to_string(ID) + " first Corner (" + to_string(Corner1.x)
		+ " , " + to_string(Corner1.y) + ") second Corner (" + to_string(Corner2.x)
		+ " , " + to_string(Corner2.y) + ") the height " + to_string(abs(Corner1.y - Corner2.y))
		+ " and the width " + to_string(abs(Corner1.x - Corner2.x))+ " Draw Color" + DrawClr + "Fill color" + FIllClr;

	pOut->PrintMessage(msg);
	
}

void CRectangle::move(Point P)//bool to check if i want to move or not
{
	cntr.x = (Corner1.x + Corner2.x) / 2;
	cntr.y = (Corner1.y + Corner2.y) / 2;
	Corner1 = Corner1 + P - cntr;
	Corner2 = Corner2 + P - cntr;
}

bool CRectangle::getMovingValidity(Point P)
{
	canMove = false;
	int rectHeight = abs(Corner1.y - Corner2.y);
	int rectWidth = abs(Corner1.x - Corner2.x);
	if (P.y - rectHeight / 2 > UI.ToolBarHeight)
	{
		if (P.y + rectHeight / 2 < UI.height - UI.StatusBarHeight)
		{
			if (P.x - rectWidth / 2 > 0)
			{
				if (P.x + rectWidth / 2 < UI.width-15) // 15 is tolerance
				{
					canMove = true;
				}
			}
		}
	}
	return canMove;
}

Point CRectangle::getPreCoord()
{
	return cntr;
}



string CRectangle::GetShapeType()
{
	return "Rectangle";
}
Point * CRectangle::IsNearCorner(double a, double b, int& n)
{
	Point P;
	double D = 10;
	// Calculate the coordinates of the square's corners
	double cornerX[4];
	double cornerY[4];
	// Check each corner to see if the click is near any of them
	for (int i = 0; i < 4; ++i) {
		double distanceX = a - cornerX[i];
		double distanceY = b - cornerY[i];
		double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

		if (distanceSquared <= (D * D))
		{
			P.x = cornerX[i];
			P.y = cornerY[i];
			n = i;

			return &P; // Click is near this corner
		}
	}

	return NULL; // Click is not near any corner
}
void CRectangle::Resize(Point a, Point* b, int n)
{
}
bool CRectangle::Resizemax()
{
	return true;
}
void CRectangle::Save(fstream& saveRect)
{
	string drawnColor, fillColor;

	drawnColor = FigGfxInfo.DrawClr;   // Type conversion from Color to String
	if(FigGfxInfo.isFilled)
	fillColor = FigGfxInfo.FillClr;
	else
	fillColor = "NO_FILL";

	saveRect << "\t" << "RECT" << "\t" << ID<< "\t" << Corner1.x << "\t" << Corner1.y << "\t" << Corner2.x << "\t" << Corner2.y<<"\t"
		<< drawnColor << "\t" << fillColor<<endl;
}

void CRectangle::Load(fstream& loadRect)

{
	string drawnColor, fillColor;
	loadRect >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> drawnColor >> fillColor;
	if (fillColor == "NO_FILL")
	{
		FigGfxInfo.isFilled = false;
	}
	else
			FigGfxInfo.FillClr = fillColor;   
	        FigGfxInfo.DrawClr = drawnColor;
		
}



