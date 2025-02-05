#include "PlyModColors.h"
PlyModColors::PlyModColors(ApplicationManager* pApp) :Action(pApp)
{
	Correct = 0;
	Wrong = 0;
	Num_Colors = 0;
	FirstGame = true;
	for (int i = 0; i < 7; i++)
	{
		Colors[i] = 0;
	}
}
void PlyModColors::ReadActionParameters()
{
	for (int i = 0; i < pManager->ReturnFigCount(); i++)
	{
		if (((pManager->ReturnFigure(i))->Info().isFilled) == false)
			Colors[0]++;
		else if ((pManager->ReturnFigure(i))->Info().FillClr == BLACK)
			Colors[1]++;
		else if ((pManager->ReturnFigure(i))->Info().FillClr == BLUE)
			Colors[2]++;
		else if ((pManager->ReturnFigure(i))->Info().FillClr == GREEN)
			Colors[3]++;
		else if ((pManager->ReturnFigure(i))->Info().FillClr == ORANGE)
			Colors[4]++;
		else if ((pManager->ReturnFigure(i))->Info().FillClr == RED)
			Colors[5]++;
		else if ((pManager->ReturnFigure(i))->Info().FillClr == YELLOW)
			Colors[6]++;
	}
	for (int i = 0; i < 4; i++)
		if (Colors[i] != 0)
			Num_Colors++;
}
void PlyModColors::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
		ReadActionParameters();
	if (Num_Colors)
	{
		string Color;
		Random = rand() % pManager->ReturnFigCount();
		if (((pManager->ReturnFigure(Random))->Info().isFilled) == false)
		{
			Num_Colors = Colors[0]++;
			Color = "Not Filled";
		}
		else if ((pManager->ReturnFigure(Random))->Info().FillClr == BLACK)
		{
			Num_Colors = Colors[1]++;
			Color = "Black";
		}
		else if ((pManager->ReturnFigure(Random))->Info().FillClr == BLUE)
		{
			Num_Colors = Colors[2]++;
			Color = "Blue";
		}
		else if ((pManager->ReturnFigure(Random))->Info().FillClr == GREEN)
		{
			Num_Colors = Colors[3]++;
			Color = "Green";
		}
		else if ((pManager->ReturnFigure(Random))->Info().FillClr == ORANGE)
		{
			Num_Colors = Colors[4]++;
			Color = "Orange";
		}
		else if ((pManager->ReturnFigure(Random))->Info().FillClr == RED)
		{
			Num_Colors = Colors[5]++;
			Color = "Red";
		}
		else if ((pManager->ReturnFigure(Random))->Info().FillClr == YELLOW)
		{
			Num_Colors = Colors[6]++;
			Color = "Yellow";
		}
		pOut->PrintMessage("Select all " + Color);
		while (Num_Colors)
		{
			pIn->GetPointClicked(P.x, P.y);
			if (pManager->GetFigure(P.x, P.y))
			{
				if (pManager->GetFigure(P.x, P.y)->Info().FillClr == (pManager->ReturnFigure(Random))->Info().FillClr)
				{
					pOut->ClearDrawArea();
					Num_Colors--;
					(pManager->GetFigure(P.x, P.y))->Hide();
					pManager->UpdateInterface();
					Correct++;
					pOut->PrintMessage("Correct!! Choose the next " + Color);
				}
				else if (pManager->GetFigure(P.x, P.y))
				{
					pOut->ClearDrawArea();
					(pManager->GetFigure(P.x, P.y))->Hide();
					pManager->UpdateInterface();
					Wrong++;
					pOut->PrintMessage("Wrong!! Choose the " + Color);
				}
			}
				else if (P.y < UI.ToolBarHeight && (P.x > (UI.MenuItemWidth * ITM_TYP_COLOR) && P.x < (UI.MenuItemWidth * ITM_TYP_SHAPE)))
				{
				Correct = 0;
				Wrong = 0;
				Num_Colors = 0;
				FirstGame = false;
			for (int i = 0; i < 7; i++)
				{
					Colors[i] = 0;
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
				pOut->PrintMessage("Correct Colors Selected : " + to_string(Correct) + " Incorrect Colors Selected : " + to_string(Wrong));

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
