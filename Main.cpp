#include <iostream>
#include"Solitaire.h"
#include"ConsoleFunctions.h"
using namespace std;


int main()
{
	ConsoleFunctions cf;
	
	Solitaire S;
	S.Shuffle();
	S.dealToPlayingPiles();
	S.DisplayGame();
	S.Play();

}