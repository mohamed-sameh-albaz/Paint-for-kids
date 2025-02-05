#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include"Actions/Action.h"
//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200, MaxUndoRedoCnt =5,MaxRecOperaion=20};	//Max no of figures

private:
	int CountForID;
	int UndoCnt;
	int redoCnt;
	bool willBeDeleted;
	int FigCount;		//Actual number of figures
	bool isRecording;  // Flag to know if there is a Recording
	bool isPlaying;
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	Action* UndoRedoList[MaxUndoRedoCnt];
	Action* TempUndoRedoList[MaxUndoRedoCnt];
	CFigure* deletedFigList[2000];
	CFigure* SelectedFig; //Pointer to the selected figure

	bool muted;
	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	bool PopUp;
public:	
	ApplicationManager(); 
	~ApplicationManager();
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	void AddActToUndoRedo(Action* pAct);
	void UndoAct();
	void RedoAct();
	int getUndoCnt();
	int getRedoCnt();
	int setRedoCnt(int cnt);
	void ResetUndoCnt();
	void ResetRedoCnt();
	
	void setMuted(bool);
	bool isMuted();
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y); //Search for a figure given a point inside the figure 
	CFigure *GetLastSelected(); 
	void DeleteSelectedFig(CFigure* SelectedFigure);
	void setWillBeDeleted(bool flag);
	bool getWillBeDeleted();
	void ClearAll();
	void ClearUndoRedoList();
	int GetFigCount() const;
	void SetIsRecording(bool record);
	void SetIsPlaying(bool play);
	bool GetIsPlaying()const;
	bool GetIsRecording() const;
	void SaveAllFigures(fstream &savefile);   // Call the virtual function savevto save all drawn figures 
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
	int ReturnFigCount() const;
	CFigure* ReturnFigure(int a) const;
};

#endif