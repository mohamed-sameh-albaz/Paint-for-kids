#include "LoadAction.h"
#include "ApplicationManager.h"
#include<fstream>
#include "CTriangle.h"
#include "Figures/CRectangle.h"
#include "CHexagon.h"
#include "CSquare.h"
#include "CCircle.h"





LoadAction::LoadAction(ApplicationManager* pApp) :Action(pApp)
{
	fileName="Save/";
}

void LoadAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();

	pOut->ClearStatusBar();
	pIn->QuesKeyClicked();
	pOut->PrintMessage("  Please enter the Load file name  ");
	fileName += pIn->GetString(pOut);
	pIn->QuesPointClicked();
}

void LoadAction::Execute()
{
	char toCheck ='Y';
	string Check;
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	if (pManager->GetFigCount())
	{
		pIn->QuesKeyClicked();
		pOut->PrintMessage(" there are drawn figures if you load file all your progress will be lost if you want to continue press Y otherwise press any key "); 
		Check=pIn->GetString(pOut);
		pIn->QuesPointClicked();
		toCheck = Check[0];
	}
	
	
		if (toupper(toCheck) == 'Y')  //optional space exit enter etc should i be aware of them
		{
			pManager->ClearAll();
			////call action clearall(clear drawing area and clear figcount and clear figlist )
			ReadActionParameters();

			fileName += ".txt";



			fstream loadFile(fileName, ios::in);    // I didn't check if the file is open or not because i check it in previous


			if (!loadFile.is_open()) // optional  (not optional because if there is no file)because  I checked if the file name is correct or not in previous step
				pOut->PrintMessage(" ERROR :cannot open the file please try again ");
			

			else
			{
				CFigure* pFigure;   // optional should i made them as private in .h??? 
				string  type;
				string currentDrawcolor;           //NOTEE  //type casting for << >>  for colors to string and string to color and string to int 
				string currentfillcolor;
				int numOfFigures;
				loadFile >> currentDrawcolor;    // optional ????you should convert from string to color or using if 
				loadFile >> currentfillcolor;   // or using enums orrrrrr using type casting for string to color 
				loadFile >> numOfFigures;        // should i make setters for ui,draw color in output
				                                // and should i do type casting for << and >>  
				UI.DrawColor = currentDrawcolor;
			                                       /// should i make setters optional
				if (currentfillcolor =="NO_FILL")
					UI.FillColor = UI.BkGrndColor;                 // true or not ??optional
				else
					UI.FillColor = currentfillcolor;

				pOut->colornum = pOut->getCrntDrawColor();
				pOut->CreateColorsToolBarTAB();
				pOut->fillcolornum = pOut->getCrntFillColor();
				pOut->CreateFillColorsToolBarTAB();
			
			///  kman lma a5le lwn lazm tab fe tool bar will be changed
				for (int i = 0; i < numOfFigures; i++) // optional ????you should read the first two lines of the file fisrt
				{
					loadFile >> type;                   //int type  for(){ switch()
					if (type == "RECT")
					{
						pFigure = new CRectangle();
					}

					else if (type == "SQUARE")
					{
						pFigure = new CSquare(pOut->GetLengthSq());
					}
					else if (type == "TRIANG")
					{
						pFigure = new CTriangle();
					}

					else if (type == "HEX")
					{
						pFigure = new CHexagon(pOut->GetLengthHex());
					}
					else
					{                                      //Sure it's a circle
						pFigure = new CCircle();
					}
								      
					pFigure->Load(loadFile);
					pManager->AddFigure(pFigure);
					
					                                          //optional should i do enums instead???


				}


				//loadFile.close();
			}
			loadFile.close();


		}
	

	
}


