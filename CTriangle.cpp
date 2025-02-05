#include "CTriangle.h"
#include<fstream>
CTriangle::CTriangle()
{
}
CTriangle::CTriangle(Point p1, Point p2, Point p3, GfxInfo FigureGfxInfo) :CFigure(FigureGfxInfo)
{
	vertex1 = p1;
	vertex2 = p2;
	vertex3 = p3;
	ID = ++countForID;
	//canMove = false;
	cntr.x = (vertex1.x + vertex2.x + vertex3.x) / 3;
	cntr.y = (vertex1.y + vertex2.y + vertex3.y) / 3;
}

void CTriangle::Draw(Output* pOut) const
{
	pOut->DrawTgl(vertex1, vertex2, vertex3, FigGfxInfo, Selected);
}

bool CTriangle::belongsTo(int x, int y)
{
	float A, A1, A2, A3;
	// The area of the Triangle 123
	A = abs((vertex1.x * (vertex2.y - vertex3.y) + vertex2.x * (vertex3.y - vertex1.y) + vertex3.x * (vertex1.y - vertex2.y)) / 2.0);
	// The area of the Triangle P23
	A1 = abs((x * (vertex2.y - vertex3.y) + vertex2.x * (vertex3.y - y) + vertex3.x * (y - vertex2.y)) / 2.0);
	// The area of the Triangle P13
	A2 = abs((vertex1.x * (y - vertex3.y) + x * (vertex3.y - vertex1.y) + vertex3.x * (vertex1.y - y)) / 2.0);
	// The area of the Triangle P12
	A3 = abs((vertex1.x * (vertex2.y - y) + vertex2.x * (y - vertex1.y) + x * (vertex1.y - vertex2.y)) / 2.0);

	if (A == (A1 + A2 + A3))
		return true;
	return false;
}

void CTriangle::PrintInfo(Output* pOut)
{
	int height = abs(vertex1.y - vertex2.y) > abs(vertex1.y - vertex3.y) ?
		abs(vertex1.y - vertex2.y) : abs(vertex1.y - vertex3.y);
	int width = abs(vertex1.x - vertex2.x) > abs(vertex1.x - vertex3.x) ?
		abs(vertex1.x - vertex2.x) : abs(vertex1.x - vertex3.x);
	string DrawClr = FigGfxInfo.DrawClr;// Type conversion (from color to string)
	string FIllClr = FigGfxInfo.isFilled ? FigGfxInfo.FillClr : (string)(" No Fill");
	string msg = "The ID is " + to_string(ID) + " first Vertex (" + to_string(vertex1.x)
		+ " , " + to_string(vertex1.y) + ") second Vertex (" + to_string(vertex2.x)
		+ " , " + to_string(vertex2.y) + ") third Vertex (" + to_string(vertex3.x)
		+ " , " + to_string(vertex3.y) + ") the height " + to_string(height)
		+ " and the width " + to_string(width) +" Draw Color" + DrawClr +"Fill color" + FIllClr;

	pOut->PrintMessage(msg);
}

void CTriangle::move(Point P)
{
	cntr.x = (vertex1.x + vertex2.x + vertex3.x) / 3;
	cntr.y = (vertex1.y + vertex2.y + vertex3.y) / 3;
		vertex1 = vertex1 + P - cntr;
		vertex2 = vertex2 + P - cntr;
		vertex3 = vertex3 + P - cntr;
		cntr = P;
}

Point CTriangle::getPreCoord()
{
	
	return cntr;
}

bool CTriangle::getMovingValidity(Point P)
{
	canMove = false;
	Point tempVertex1, tempVertex2, tempVertex3;
	tempVertex1 = vertex1 + P - cntr;
	tempVertex2 = vertex2 + P - cntr;
	tempVertex3 = vertex3 + P - cntr;
	if (tempVertex1.y > UI.ToolBarHeight && tempVertex2.y > UI.ToolBarHeight && tempVertex3.y > UI.ToolBarHeight/*&& UI.height - P.y > UI.StatusBarHeight*/)
	{
		if (tempVertex1.y < UI.height - UI.StatusBarHeight && tempVertex2.y < UI.height - UI.StatusBarHeight && tempVertex3.y < UI.height - UI.StatusBarHeight)
		{
			if (tempVertex1.x > 0 && tempVertex2.x > 0 && tempVertex3.x > 0)
			{
				if (tempVertex1.x < UI.width-15 && tempVertex2.x < UI.width-15 && tempVertex3.x < UI.width - 15) // 15 is tolerance
				{
					canMove = true;
				}
			}
		}
	}
	return canMove;
}

string CTriangle::GetShapeType()
{
	return "Triangle";
}
Point* CTriangle::IsNearCorner(double clickX, double clickY,int& n) {
	Point P;
	double D = 10; // Define a threshold distance
	double vertexX[3] = { vertex1.x,vertex2.x,vertex3.x };
	double vertexY[3] = { vertex1.y,vertex2.y,vertex3.y };
	// Calculate the distance between the click coordinates and each triangle vertex
	for (int i = 0; i < 3; ++i) {
		double distanceX = clickX - vertexX[i];
		double distanceY = clickY - vertexY[i];
		double distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

		if (distanceSquared <= (D * D)) 
		{
			P.x = vertexX[i];
			P.y = vertexY[i];
			n = i;
			return &P; // Click is near this triangle corner
		}
	}

	return NULL; // Click is not near any triangle corner
}
void CTriangle::Resize(Point a, Point* b, int n)
{

}
bool CTriangle::Resizemax()
{
	return true;
}
void CTriangle::Save(fstream& saveTgl)
{
	string drawnColor, fillColor;
	drawnColor = FigGfxInfo.DrawClr;
	if (FigGfxInfo.isFilled)
		fillColor = FigGfxInfo.FillClr;
	else
		fillColor = "NO_FILL";
	saveTgl << "\t" << "TRIANG" << "\t" << ID<< "\t" << vertex1.x << "\t" << vertex1.y << "\t" << vertex2.x << "\t" << vertex2.y
		<< "\t" << vertex3.x << "\t" << vertex3.y << "\t" << drawnColor << "\t" << fillColor << endl;
}

void CTriangle::Load(fstream& loadTgl)
{
	string drawnColor, fillColor;
	loadTgl >> ID >> vertex1.x >> vertex1.y >> vertex2.x >> vertex2.y >> vertex3.x >> vertex3.y>>drawnColor>>fillColor;
		
	if (fillColor == "NO_FILL")
	{
		FigGfxInfo.isFilled = false;
	}
	else
		FigGfxInfo.FillClr = fillColor;
	FigGfxInfo.DrawClr = drawnColor;
}
