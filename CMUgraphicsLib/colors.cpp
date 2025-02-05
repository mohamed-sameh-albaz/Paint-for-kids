/* 
See "version.h" for version info and copyright information
This file was last modified on 05.16.1999
*/

#include "colors.h"
#include <iostream>
#include"..\GUI\UI_Info.h"
using namespace std;

bool operator==(color a, color b) {

  return ((a.ucRed == b.ucRed) && (a.ucGreen == b.ucGreen) && (a.ucBlue == b.ucBlue));

}

bool operator!=(color a, color b) {

  return !(a == b);
  
}

color::operator std::string()
{
	if (*this == BLACK)return "Black";
	if (*this == GREEN)return "Green";
	if (*this == RED)return "Red";
	if (*this == BLUE)return "Blue";
	if (*this == YELLOW)return "Yellow";
	if (*this == ORANGE)return "Orange";

}

color color::operator=(string line)
{
	if (line == "Black") *this =BLACK;
	else if (line == "Green") *this =GREEN;
	else if (line == "Red")  *this =RED;
	else if (line == "Blue")  *this =BLUE;
	else if (line == "Yellow")*this =YELLOW;
	else if (line == "Orange") *this =ORANGE;   // optional
	return *this;
}
color::operator int()
{
	if (*this == BLACK)
		return ITM_BLACK_FILL;
	else if (*this == BLUE)
		return ITM_BLUE_FILL;
	else if (*this == GREEN)
		return ITM_GREEN_FILL;              /////optional NOTE i #include ui otherwise it will return 1 2 3 etc ???
	else if (*this == ORANGE)
		return ITM_ORANGE_FILL;
	else if (*this == RED)
		return ITM_RED_FILL;
	else if (*this == YELLOW)
		return ITM_YELLOW_FILL;
	else
		return ITM_NO_FILL;

}
