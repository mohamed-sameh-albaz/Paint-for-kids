#include "CSquare.h"
#include<fstream>


CSquare::CSquare(int l)
{
	sqLen = l + UI.PenWidth;

}

CSquare::CSquare(Point P,int l, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Centre = P;
	sqLen = l + UI.PenWidth;
	ID = ++countForID;
	canMove = false;
}

void CSquare::Draw(Output* pOut) const
{
	pOut->DrawSq(Centre , sqLen, FigGfxInfo, Selected);
	pOut->GetLengthSq();
}

bool CSquare::belongsTo(int x, int y)
{
	Point p1, p2, p3, p4;
	p1.x = Centre.x - sqLen / 2.0;p1.y = Centre.y - sqLen / 2.0;
	p2.x = Centre.x + sqLen / 2.0;p2.y = Centre.y - sqLen / 2.0;
	p3.x = Centre.x + sqLen / 2.0;p3.y = Centre.y + sqLen / 2.0;
	p4.x = Centre.x - sqLen / 2.0;p4.y = Centre.y + sqLen / 2.0;

	if ((x > p1.x && x < p2.x) && (y > p2.y && y < p3.y))
		return true;
	return false;
}

void CSquare::PrintInfo(Output* pOut)
{
	string DrawClr = FigGfxInfo.DrawClr;// Type conversion (from color to string)
	string FIllClr = FigGfxInfo.isFilled ? FigGfxInfo.FillClr : (string)(" No Fill");
	string msg = "The ID is " + to_string(ID) + " the Centre (" + to_string(Centre.x)
		+ " , " + to_string(Centre.y) + ") the length " + to_string(sqLen - UI.PenWidth) 
		+ " Draw Color" + DrawClr + "Fill color" + FIllClr;;
		
	pOut->PrintMessage(msg);
}

string CSquare::GetShapeType()
{
	return "Square";
}
Point* CSquare::IsNearCorner(double a, double b, int&n)
{
	Point P;
	double D = 20;
	// Calculate the coordinates of the square's corners
	double cornerX[4] = { Centre.x - sqLen / 2.0, Centre.x + sqLen / 2.0, Centre.x + sqLen / 2.0, Centre.x - sqLen / 2.0 };
	double cornerY[4] = { Centre.y - sqLen / 2.0, Centre.y - sqLen / 2.0, Centre.y + sqLen / 2.0, Centre.y + sqLen / 2.0 };

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
void CSquare::Resize(Point a, Point* b, int n)
{
	oldsqLen = sqLen;
	double Dx = (a.x - b->x)*2;
	double Dy = (a.y - b->y)*2;
	switch (n)
	{
	case 0:
		if (abs(Dx) >= abs(Dy))
		{
			sqLen = sqLen - Dx;
		}
		if (abs(Dx) < abs(Dy))
		{
			sqLen = sqLen - Dy;
		}
		break;
	case 1:
		if (abs(Dx) >= abs(Dy))
		{
			sqLen = sqLen + Dx;
		}
		if (abs(Dx) < abs(Dy))
		{
			sqLen = sqLen - Dy;
		}
		break;
	case 2:
		if (abs(Dx) >= abs(Dy))
		{
			sqLen = sqLen + Dx;
		}
		if (abs(Dx) < abs(Dy))
		{
			sqLen = sqLen + Dy;
		}
		break;
	case 3:
		if (abs(Dx) >= abs(Dy))
		{
			sqLen = sqLen - Dx;
		}
		if (abs(Dx) < abs(Dy))
		{
			sqLen = sqLen + Dy;
		}
		break;
	}

	
}

bool CSquare::Resizemax()
{
	double cornerX[4] = { Centre.x - sqLen / 2.0, Centre.x + sqLen / 2.0, Centre.x + sqLen / 2.0, Centre.x - sqLen / 2.0 };
	double cornerY[4] = { Centre.y - sqLen / 2.0, Centre.y - sqLen / 2.0, Centre.y + sqLen / 2.0, Centre.y + sqLen / 2.0 };
	for (int i = 0; i < 4; i++)
	{
		if ((cornerY[i] < UI.ToolBarHeight || cornerY[i] > UI.height - UI.StatusBarHeight))
		{
			sqLen = oldsqLen;
			return false;
		}
	}
	return true;
}

void CSquare::move(Point P)
{
		Centre = P;
}

Point CSquare::getPreCoord()
{
	return Centre;
}

bool CSquare::getMovingValidity(Point P)
{
	canMove =false;
	if (P.y-sqLen/2> UI.ToolBarHeight /*&& UI.height - P.y > UI.StatusBarHeight*/) 
	{
		if(P.y+sqLen/2<UI.height-UI.StatusBarHeight)
		{
			if(P.x-sqLen/2>0)
			{
				if(P.x+sqLen/2<UI.width)
				{
					canMove = true;
				}
			}
		}
	}
	return canMove;
}
void CSquare::Save(fstream& saveSq)
{
	string drawnColor, fillColor;
	drawnColor = FigGfxInfo.DrawClr;
	if (FigGfxInfo.isFilled)
		fillColor = FigGfxInfo.FillClr;
	else
		fillColor = "NO_FILL";

	saveSq << "\t" << "SQUARE" << "\t" << ID<<"\t" << Centre.x << "\t" << Centre.y << "\t" << drawnColor << "\t" << fillColor<<endl;
}

void CSquare::Load(fstream& loadSq)
{
	string drawnColor, fillColor;
	loadSq >>ID>> Centre.x >> Centre.y >> drawnColor >> fillColor;
	if (fillColor == "NO_FILL")
	{
		FigGfxInfo.isFilled = false;
	}
	else
			FigGfxInfo.FillClr = fillColor;   
	        FigGfxInfo.DrawClr = drawnColor;
		
}
