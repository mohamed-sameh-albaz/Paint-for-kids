#include "CFigure.h"
#include<fstream>

int CFigure::countForID = 0;

CFigure::CFigure()
{
	Selected = false;
	Hidden = false;
	countForID++;
}

CFigure::CFigure(GfxInfo FigureGfxInfo)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	Hidden = false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }


void CFigure::ChngDrawClr(color Dclr)
{
	FigGfxInfo.DrawClr = Dclr;
}

void CFigure::ChngFillClr(color Fclr)
{	

	FigGfxInfo.FillClr = Fclr; 
	FigGfxInfo.isFilled = Fclr==UI.BkGrndColor?false:true;
}
void CFigure::Hide()
{
	Hidden = true;
}
void CFigure::Show()
{
	Hidden = false;
}
bool CFigure::IsHidden()
{
	return Hidden;
}
GfxInfo CFigure::Info()
{
	return FigGfxInfo;
}


