#include "PlyModBoth.h"
PlyModBoth::PlyModBoth(ApplicationManager* pApp) :Action(pApp)
{
	Correct = 0;
	Wrong = 0;
	Num_Shapes = 0;
	for (int i = 0; i < 5; i++)
	{
		for(int j = 0 ; j <7;j++)
		Shapes[i][j] = 0;
	}
	FirstGame = true;
}
void PlyModBoth::ReadActionParameters()
{
	for (int i = 0; i < pManager->ReturnFigCount(); i++)
		for (int j = 0; j < 5; j++)
			if (pManager->ReturnFigure(i)->GetShapeType() == shapes[j])
			{
				if (!((pManager->ReturnFigure(i))->Info().isFilled))
				{
					Shapes[j][0]++;
				}
				else if ((pManager->ReturnFigure(i))->Info().FillClr == BLACK)
				{
					Shapes[j][1]++;
				}
				else if ((pManager->ReturnFigure(i))->Info().FillClr == BLUE)
				{
					Shapes[j][2]++;
				}
				else if ((pManager->ReturnFigure(i))->Info().FillClr == GREEN)
				{
					Shapes[j][3]++;
				}
				else if ((pManager->ReturnFigure(i))->Info().FillClr == ORANGE)
				{
					Shapes[j][4]++;
				}
				else if ((pManager->ReturnFigure(i))->Info().FillClr == RED)
				{
					Shapes[j][5]++;
				}
				else if ((pManager->ReturnFigure(i))->Info().FillClr == YELLOW)
				{
					Shapes[j][6]++;
				}

	}
	for (int i = 0; i < 5; i++)
		for(int j = 0 ; j<7 ; j++)
		if (Shapes[i][j] != 0)
			Num_Shapes++;
}
void PlyModBoth::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	if (Num_Shapes)
	{
		Random = rand() % pManager->ReturnFigCount();
		for (int i = 0; i < 5; i++)
			if (pManager->ReturnFigure(Random)->GetShapeType() == shapes[i])
			{
				shape = shapes[i];
				if (!((pManager->ReturnFigure(Random))->Info().isFilled))
				{
					Num_Shapes = Shapes[i][0]; color = "No Fill";
				}
				else if ((pManager->ReturnFigure(Random))->Info().FillClr == BLACK)
				{
					Num_Shapes = Shapes[i][1]; color = "Black";
				}
				else if ((pManager->ReturnFigure(Random))->Info().FillClr == BLUE)
				{
					Num_Shapes = Shapes[i][2]; color = "Blue";
				}
				else if ((pManager->ReturnFigure(Random))->Info().FillClr == GREEN)
				{
					Num_Shapes = Shapes[i][3]; color = "Green";
				}
				else if ((pManager->ReturnFigure(Random))->Info().FillClr == ORANGE)
				{
					Num_Shapes = Shapes[i][4]; color = "Orange";
				}
				else if ((pManager->ReturnFigure(Random))->Info().FillClr == RED)
				{
					Num_Shapes = Shapes[i][5]; color = "Red";
				}
				else if ((pManager->ReturnFigure(Random))->Info().FillClr == YELLOW)
				{
					Num_Shapes = Shapes[i][6]; color = "Yellow";
				}
			}
		pOut->PrintMessage("Select all " + color + " " + shape);
		while (Num_Shapes)
		{
			pIn->GetPointClicked(P.x, P.y);
			if ((pManager->GetFigure(P.x, P.y)))
			{
				if ((pManager->ReturnFigure(Random))->GetShapeType() == pManager->GetFigure(P.x, P.y)->GetShapeType()
					&& pManager->GetFigure(P.x, P.y)->Info().FillClr == (pManager->ReturnFigure(Random))->Info().FillClr)
				{
					pOut->ClearDrawArea();
					Num_Shapes--;
					(pManager->GetFigure(P.x, P.y))->Hide();
					pManager->UpdateInterface();
					Correct++;
					pOut->PrintMessage("Correct!! Choose the next " + color + " " + shape);
				}
				else if (pManager->GetFigure(P.x, P.y))
				{
					pOut->ClearDrawArea();
					(pManager->GetFigure(P.x, P.y))->Hide();
					pManager->UpdateInterface();
					Wrong++;
					pOut->PrintMessage("Wrong!! Choose the " + color + " " + shape);
				}
			}
			else if (P.y < UI.ToolBarHeight && (P.x > (UI.MenuItemWidth * ITM_TYP_BOTH) && P.x < (UI.MenuItemWidth * ITM_SWITCH)))
			{
				Correct = 0;
				Wrong = 0;
				Num_Shapes = 0;
				FirstGame = false;
				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 5; j++)
						Shapes[j][i] = 0;
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
