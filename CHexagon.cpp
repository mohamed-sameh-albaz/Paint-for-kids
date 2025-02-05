#include "CHexagon.h"
#include <cmath>
#include<fstream>
#define PI 3.14159

CHexagon::CHexagon(int l)
{
	hexLen = l + UI.PenWidth;
}
CHexagon::CHexagon(Point cntr,int l, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Centre = cntr;
	hexLen = l + UI.PenWidth;
	ID = ++countForID;
	canMove = false;
}

void CHexagon::Draw(Output* pOut) const
{
	pOut->DrawHex(Centre,hexLen, FigGfxInfo, Selected);
}

bool CHexagon::belongsTo(int x, int y)
{
	Point adjPoint1 , adjPoint2;
	float dLength = abs(Centre.y - y);
	if (y > (Centre.y - sqrt(3) * hexLen / 2.0) && y < (Centre.y + sqrt(3) * hexLen / 2.0)) // vertical check
	{ 
		adjPoint1.x = Centre.x + hexLen - dLength / sqrt(3);
		adjPoint2.x = Centre.x - hexLen + dLength / sqrt(3);
		if (x > adjPoint2.x && x < adjPoint1.x)
			return true;
	}
	return false;
}

void CHexagon::PrintInfo(Output* pOut)
{
	string DrawClr = FigGfxInfo.DrawClr; // Type conversion (from color to string)
	string FIllClr = FigGfxInfo.isFilled ? FigGfxInfo.FillClr : (string)(" No Fill");
	string msg = "The ID is " + to_string(ID) + " the Centre (" + to_string(Centre.x)
		+ " , " + to_string(Centre.y) + ") the length " + to_string(hexLen - UI.PenWidth)
		+ " Draw Color " + DrawClr + " Fill color " + FIllClr;

	pOut->PrintMessage(msg);
}
string CHexagon::GetShapeType()
{
	return "Hexagon";
}
void CHexagon::move(Point P)
{
	Centre = P;
}

bool CHexagon::getMovingValidity(Point P)
{
	canMove = false;
	if (P.y - hexLen > UI.ToolBarHeight /*&& UI.height - P.y > UI.StatusBarHeight*/)
	{
		if (P.y + hexLen < UI.height - UI.StatusBarHeight)
		{
			if (P.x - hexLen > 0)
			{
				if (P.x + hexLen < UI.width - 15) // 15 is tolerance
				{
					canMove = true;
				}
			}
		}
	}
	return canMove;
}

Point CHexagon::getPreCoord()
{
	return Centre;
}

Point * CHexagon::IsNearCorner(double a, double b, int& n)
{
	Point P;
	double D = 10;
	// Calculate the coordinates of the square's corners
	int vertices = 6;                // Number of vertices in Hexagon
	int* Px = new int[vertices];    // Array of X coordinate of Hexagon points
	int* Py = new int[vertices];   // Array of Y coordinate of Hexagon points


	//Set the values of the Array of vertices coordinates of Hexagon points 
	for (int i = 0; i < vertices; i++)
	{
		Px[i] = Centre.x + hexLen * cos((i) * (PI / 3));  //NOTE: The angle between two consecutive points is PI / 3
		Py[i] = Centre.y - hexLen * sin((i) * (PI / 3));  //======================================================//

	}

	// Check each corner to see if the click is near any of them
	for (int i = 0; i < vertices; ++i) {
		double distanceX = a - Px[i];
		double distanceY = b - Py[i];
		double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

		if (distanceSquared <= (D * D))
		{
			P.x = Px[i];
			P.y = Py[i];
			n = i;
			return &P; // Click is near this corner
		}
	}

	return NULL; // Click is not near any corner
}
void CHexagon::Resize(Point a, Point* b, int n)
{
}
bool CHexagon::Resizemax()
{
	return true;

}
void CHexagon::Save(fstream& saveHex)
{
	string drawnColor, fillColor;
	drawnColor = FigGfxInfo.DrawClr;
	if (FigGfxInfo.isFilled)
		fillColor = FigGfxInfo.FillClr;
	else
		fillColor = "NO_FILL";

	saveHex << "\t" << "HEX" << "\t" << ID<< "\t" << Centre.x<< "\t" <<Centre.y << "\t" << drawnColor <<"\t" <<fillColor<<endl;
}

void CHexagon::Load(fstream& loadHex)
{

	string drawnColor, fillColor;
	loadHex >> ID >> Centre.x >> Centre.y >> drawnColor >> fillColor;
	if (fillColor == "NO_FILL")
	{
		FigGfxInfo.isFilled = false;
	}
	else
			FigGfxInfo.FillClr = fillColor;   
	        FigGfxInfo.DrawClr = drawnColor;
		
}



