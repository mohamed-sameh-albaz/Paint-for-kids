#include "PlyModShapes.h"
PlyModShapes::PlyModShapes(ApplicationManager* pApp) :Action(pApp)
{
	Correct = 0;
	Wrong = 0;
	Num_Figures = 0;
	for (int i = 0; i < 5; i++)
	{
		Figures[i] = 0;
	}
	FirstGame = true;
}
void PlyModShapes::ReadActionParameters()
{
	for (int i = 0; i < pManager->ReturnFigCount(); i++)
	{
		for (int j = 0; j < 5; j++)
			if (pManager->ReturnFigure(i)->GetShapeType() == shapes[j])
				Figures[j]++;
	}
	for (int i = 0; i < 5; i++)
		if (Figures[i] != 0)
			Num_Figures++;
}
void PlyModShapes::Execute()
{
	bool game = true;

	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while (game)
	{
		game = false;
		ReadActionParameters();
		if (Num_Figures)
		{
			Random = rand() % pManager->ReturnFigCount();
			for (int i = 0; i < 5; i++)
			{
				if (((pManager->ReturnFigure(Random))->GetShapeType() == shapes[i]))
				{
					Num_Figures = Figures[i];
				}
			}
			pOut->PrintMessage("Select all " + (pManager->ReturnFigure(Random))->GetShapeType());
			while (Num_Figures)
			{
				pIn->GetPointClicked(P.x, P.y);
				if ((pManager->GetFigure(P.x, P.y)))
				{
					if ((pManager->GetFigure(P.x, P.y))->GetShapeType() == (pManager->ReturnFigure(Random))->GetShapeType())
					{
						pOut->ClearDrawArea();
						Num_Figures--;
						(pManager->GetFigure(P.x, P.y))->Hide();
						pManager->UpdateInterface();
						Correct++;
						pOut->PrintMessage("Correct!! Choose the next " + (pManager->ReturnFigure(Random))->GetShapeType());
					}
					else if (pManager->GetFigure(P.x, P.y))
					{
						pOut->ClearDrawArea();

						(pManager->GetFigure(P.x, P.y))->Hide();
						pManager->UpdateInterface();
						Wrong++;
						pOut->PrintMessage("Wrong!! Choose the " + (pManager->ReturnFigure(Random))->GetShapeType());
					}
				}
				else if (P.y < UI.ToolBarHeight && (P.x > (UI.MenuItemWidth * ITM_TYP_SHAPE) && P.x < (UI.MenuItemWidth * ITM_TYP_BOTH)))
				{
					Correct = 0;
					Wrong = 0;
					Num_Figures = 0;
					FirstGame = false;
					for (int i = 0; i < 5; i++)
					{
						Figures[i] = 0;
					}
					for (int i = 0; i < pManager->ReturnFigCount(); i++)
					{
						(pManager->ReturnFigure(i))->Show();
					}
					pManager->UpdateInterface();
					Execute();
					return;
				}
			}
			if (Correct)
			{
				pOut->PrintMessage("Correct Shapes Selected : " + to_string(Correct) + " Incorrect Shapes Selected : " + to_string(Wrong));
				pIn->GetPointClicked(P.x, P.y);
			}
			for (int i = 0; i < pManager->ReturnFigCount(); i++)
			{
				(pManager->ReturnFigure(i))->Show();
			}
			pOut->PrintMessage("Play Mode");
			pManager->UpdateInterface();
		}
	}
}