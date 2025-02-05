#include "CCircle.h"
#include<fstream>

CCircle::CCircle()
{
	
}

CCircle::CCircle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Centre = P1;
	CircPoint = P2;
	ID = ++countForID;
	canMove = false;
}

void CCircle::Draw(Output* pOut) const
{
	pOut->DrawCir(Centre, CircPoint, FigGfxInfo, Selected);
}

bool CCircle::belongsTo(int x,int y)
{	
	
	if (sqrt(pow((Centre.x - CircPoint.x), 2) + pow((Centre.y - CircPoint.y), 2)) >=sqrt( pow((Centre.x - x), 2) + pow((Centre.y - y), 2)))
		return true;

	else return false;
}

void CCircle::PrintInfo(Output* pOut)
{
	string DrawClr = FigGfxInfo.DrawClr;// Type conversion (from color to string)
	string FIllClr = FigGfxInfo.isFilled ? FigGfxInfo.FillClr : (string)(" No Fill");
	string msg = "The ID is " + to_string(ID) + " Centre (" + to_string(Centre.x)
		+ " , " + to_string(Centre.y) + ") second Corner (" + to_string(CircPoint.x)
		+ " , " + to_string(CircPoint.y) + ") the Radius " +
		to_string(sqrt(pow((Centre.x - CircPoint.x), 2) + pow((Centre.y - CircPoint.y), 2))) 
		+ " Draw Color" + DrawClr + "Fill color" + FIllClr;

	pOut->PrintMessage(msg);
}

void CCircle::move(Point P)
{
		CircPoint = CircPoint + (P - Centre);
		Centre = P;
}

Point CCircle::getPreCoord()
{
	return Centre;
}

bool CCircle::getMovingValidity(Point P)
{
	canMove = false;
	double radius = sqrt(pow((CircPoint.x - Centre.x), 2) + pow((CircPoint.y - Centre.y), 2)); //to not break DRY principal(Don't repeat your self)
	if (P.y - radius > UI.ToolBarHeight /*&& UI.height - P.y > UI.StatusBarHeight*/)
	{
		if (P.y + radius < UI.height - UI.StatusBarHeight /*UI.height - (P.y + radius) > UI.StatusBarHeight*/)
		{
			if (P.x - radius > 0)
			{
				if (P.x + radius < UI.width)
				{
					canMove = true;
				}
			}
		}
	}
	return canMove;
}
string CCircle::GetShapeType()
{
	return "Circle";
}
Point* CCircle::IsNearCorner(double a, double b,int&n)
{
	double thresholdDistance = 30;
	double distanceX = a - Centre.x;
	double distanceY = b - Centre.y;
	double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);
	double Radius = sqrt(pow((Centre.x - CircPoint.x), 2) + pow((Centre.y - CircPoint.y), 2));
	double radiusSquared = Radius * Radius;


		if (distanceSquared >= (radiusSquared - thresholdDistance * thresholdDistance) &&
			distanceSquared <= (radiusSquared + thresholdDistance * thresholdDistance))
		{
			return &CircPoint;
		}

		return NULL; 
	}
void CCircle::Resize(Point a, Point* b, int n)
{
	CircPoint = a;
}
bool CCircle::Resizemax()
{
	
	if ((Centre.y - sqrt(pow((Centre.x - CircPoint.x), 2) + pow((Centre.y - CircPoint.y), 2))) < UI.ToolBarHeight)
	{
		CircPoint.x = Centre.x;
		CircPoint.y = UI.ToolBarHeight + 5;
		return false;
	}
	if (Centre.y + sqrt(pow((Centre.x - CircPoint.x), 2)) > UI.height - UI.StatusBarHeight)
	{
		CircPoint.x = Centre.x;
		CircPoint.y = UI.height - UI.StatusBarHeight - 5;
		return false;
	}
	return true;
}
void CCircle::Save(fstream& saveCir)
{
	string drawnColor, fillColor;
	drawnColor = FigGfxInfo.DrawClr;    // optional
	if (FigGfxInfo.isFilled)           // we will change it to 2 variables in cfigure and method will be in constructor
		fillColor = FigGfxInfo.FillClr;  /// should i take care of highlighted(selected) ??
	else
		fillColor = "NO_FILL";
	saveCir << "\t" <<"CIRCLE" << "\t" << ID<< "\t" << Centre.x << "\t" << Centre.y << "\t" << CircPoint.x << "\t" << CircPoint.y <<"\t"
		<< drawnColor << "\t" << fillColor<<endl;
}

void CCircle::Load(fstream& loadCir)
{
	string drawnColor, fillColor;
	loadCir >> ID >> Centre.x >> Centre.y >> CircPoint.x >> CircPoint.y >> drawnColor >> fillColor;
	if (fillColor == "NO_FILL")
	{
		FigGfxInfo.isFilled = false;
	}
	else
		FigGfxInfo.FillClr = fillColor;   
		FigGfxInfo.DrawClr = drawnColor;
		
}
