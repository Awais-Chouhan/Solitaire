#pragma once
class PlayingCards
{

private:
	int rank; //integer 1 – 13
	int suit; //integer 0 – 3
	char color; // red or black - ‘b’ for black , ‘r’ for red
	bool faceUp; //tells if a card is face up or not
	bool top; //tells if a card is on top of a pile
public:
	PlayingCards(int rank = 0, int suit = 0);
	void display(int x, int y);
	const int static Diamond = 0;
	const int static Heart = 1;
	const int static Spade = 2;
	const int static Club = 3;
	bool isFaceUp(); //retunrs value of faceUp
	void setFaceUp(bool); //sets value of faceUp
	bool isTop(); //retunrs value of top
	void setTop(bool); //sets value of top
	int getSuit(); //getter for suit value
	int getRank(); //getter for rank value
	char getColor(); //getter for color value
};



