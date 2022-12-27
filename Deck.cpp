#include "Deck.h"

Deck::Deck()
{
	size = 52;
	int j = 0;
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCards(i, PlayingCards::Diamond);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCards(i, PlayingCards::Heart);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCards(i, PlayingCards::Spade);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCards(i, PlayingCards::Club);
		j++;
	}
}

Deck::~Deck()
{
	for (int i = 0; i < size; i++)
	{
		if (deck[i] != nullptr)
		{
			delete deck[i];
		}
	}
}


int Deck::getSize()
{
	return size;
}

bool Deck::IsEmpty()
{
	if (size == 0)
	{
		return true;
	}
	return false;
}

PlayingCards Deck::Remove(int i)
{
	if (deck[i] != nullptr)
	{
		PlayingCards* temp = deck[i];
		deck[i] = nullptr;
		for (int index = i + 1; index < size; index++)
		{
			deck[index - 1] = deck[index];
		}
		size--;
		return *temp;
	}
}


