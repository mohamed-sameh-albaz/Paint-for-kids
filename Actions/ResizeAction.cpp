#include "ResizeAction.h"
#include <Windows.h>

ResizeAction::ResizeAction(ApplicationManager* pApp) :Action(pApp)
{
    bool loop = false;
    bool LOOP = true;
}
void ResizeAction::ReadActionParameters()
{

}

void ResizeAction::Execute()
{
    Output* pOut = pManager->GetOutput();
    Input* pIn = pManager->GetInput();
    pOut->PrintMessage("Resize The Selected Shape, Click on the Resize Icon to Exit");
    bool game = true;
    if(game)
    if (pManager->GetLastSelected())
    {
        while (LOOP)
        {
            switch (pIn->GetMouseState(B.x, B.y))
            {
            case BUTTON_UP:
            {
                loop = false;
                A = B;
                if(LOOP)
                pIn->QuesPointClicked();

                break;
            }
            case BUTTON_DOWN:
            {
                {
                    if (B.y >= UI.ToolBarHeight && B.y < UI.height - UI.StatusBarHeight)
                    {
                        if (!loop)
                        {
                            ResizeFig = pManager->GetFigure(B.x, B.y);
                            if (ResizeFig && ResizeFig->Resizemax()&&ResizeFig->IsSelected())
                            {
                                C = ResizeFig->IsNearCorner(B.x, B.y, n);
                                if (ResizeFig->IsNearCorner(B.x, B.y, n))
                                {
                                    ResizeFig->Resize(B, &A, n);
                                    pOut->ClearDrawArea();
                                    pManager->UpdateInterface();
                                    A = B;
                                    loop = true;
                                }
                            }
                        }
                        else
                        {
                            if (ResizeFig->Resizemax())
                            {
                                ResizeFig->Resize(B, &A, n);
                                pOut->ClearDrawArea();
                                pManager->UpdateInterface();
                                A = B;
                                loop = true;
                            }
                            else
                            {
                                pOut->PrintMessage("FAILED:You are Trying to Resize Outside Drawing Area, The Shapes will Retrun to its maximum size after exit");
                                pOut->CreateDrawToolBar();
                                pOut->ClearStatusBar();
                            }
                        }
                    }
                    else if (A.y < UI.ToolBarHeight && (A.x > (UI.MenuItemWidth * ITM_RESIZE) && A.x < (UI.MenuItemWidth * ITM_REC)))
                    {
                        LOOP = false;
                    }
                }

                break;
            }
            }
            Sleep(20);
        }
    }
    else
    {
        pOut->PrintMessage("No Selected Figures");
    }

    pOut->PrintMessage("Exiting Resize, Choose Action");
    pIn->GetPointClicked(B.x, B.y);
    pIn->QuesPointClicked();
    pOut->ClearDrawArea();
    pManager->UpdateInterface();
}