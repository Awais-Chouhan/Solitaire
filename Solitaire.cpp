#include "Solitaire.h"
#include"PileofCards.h"

Solitaire::Solitaire()
{
	stock = new PileofCards(52);
	stock->setStartPt(2, 2);
	stock->setEndPt(9, 8);
	waste = new PileofCards(52);
	waste->setStartPt(2, 10);
	waste->setEndPt(9, 16);
	int x = 26, y = 32;
	for (int i = 0; i < 4; i++)
	{
		home[i] = new PileofCards(13);
		home[i]->setStartPt(2, x);
		home[i]->setEndPt(9, y);
		x += 8;
		y += 8;
	}
	int index = 14, s = 2;
	for (int i = 0; i < 7; i++)
	{
		playingPile[i] = new PileofCards(index);
		index++;
		playingPile[i]->setStartPt(15, s);
		s += 8;
	}
}

void Solitaire::Shuffle()
{
	int i;
	while (!deckofCards.IsEmpty())
	{
		i = rand() % deckofCards.getSize();
		PlayingCards c = deckofCards.Remove(i);
		c.setFaceUp(false);
		stock->Add(c);
	}
}

void Solitaire::dealToPlayingPiles()
{
	int r = 20, c = 0;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < i + 1; j++) {
			PlayingCards temp = stock->Remove();
			temp.setFaceUp(false);
			temp.setTop(false);
			if (j + 1 == i + 1) {
				temp.setFaceUp(true);
				temp.setTop(true);
				r += 2; c += 8;
				playingPile[i]->setEndPt(r, c);
			}
			playingPile[i]->Add(temp);
		}
	}
}

void Solitaire::DisplayGame()
{
	stock->SimpleDisplay(1);
	waste->SimpleDisplay(0);
	for (int i = 0; i < 4; i++)
		home[i]->SimpleDisplay(0);
	for (int i = 0; i < 7; i++)
		playingPile[i]->CascadingDisplay(i);
}

point Solitaire::getClickedPoint()
{
	point a;
	while (true)
	{
		cf.DetectEvent();
		if (cf.IsMouseLeftClickEvent(a))
		{
			break;
		}
	}
	return a;
}

PileofCards* Solitaire::getClickedPile(point p, int& a, int& c)
{
	if (p.x >= stock->getStartPt().y && p.y >= stock->getStartPt().x && p.x <= stock->getEndPt().y && p.y <= stock->getEndPt().x)  //stock pile
	{
		return stock;
	}

	else if (p.x >= waste->getStartPt().y && p.y >= waste->getStartPt().x && p.x <= waste->getEndPt().y && p.y <= waste->getEndPt().x)
	{
		return waste;
	}

	for (int i = 0; i < 4; i++)
	{
		if (p.x >= home[i]->getStartPt().y && p.y >= home[i]->getStartPt().x && p.x <= home[i]->getEndPt().y && p.y <= home[i]->getEndPt().x)
		{
			a = i;
			return home[i];
		}
	}
 
	for (int i = 0; i < 7; i++)
	{
		if (p.x >= playingPile[i]->getStartPt().y && p.y >= playingPile[i]->getStartPt().x && p.x <= playingPile[i]->getEndPt().y && p.y <= playingPile[i]->getEndPt().x)
		{
			//int ca = 0;
			int index = 0;
			int ab = playingPile[i]->getTop();
			for (int ac = playingPile[i]->getStartPt().x; ac <= playingPile[i]->getEndPt().x; ac = ac + 2)
			{
				if (ab == 0)
				{
					c = 0;
					break;
				}
                else if (ab == index - 1)
                {
                    c = ab;
                    break;
                }
				else if (ac == p.y || ac + 1 == p.y)
				{
					c = ac - index - playingPile[i]->getStartPt().x;
					break;
				}
				index++;
			}
            a = i;
			return playingPile[i];

		}

	}
}

void Solitaire::moveFromStock()
{
	PlayingCards obj;
	obj = stock->Remove();
	obj.setFaceUp(true);
	waste->Add(obj);
}

void Solitaire::moveFromWasteToHome(int a)
{
	PlayingCards obj;
	obj = waste->Remove();
	obj.setFaceUp(true);
	home[a]->Add(obj);
}

void Solitaire::moveFromWasteToPlayingPile(int a, int c)
{
	PlayingCards obj;
	obj = waste->Remove();
	obj.setFaceUp(true);
	playingPile[a]->Add(obj);
  
	if (playingPile[a]->getTop() != 0)
	{
		int x = playingPile[a]->getEndPt().x, y = playingPile[a]->getEndPt().y;
		x = x + 2;
		playingPile[a]->setEndPt(x,y);
	}
  
}

void Solitaire::moveFromPlayingPileToHome(int a, int b, int c)
{
	PlayingCards obj;
	obj = playingPile[b]->Remove();
	obj.setFaceUp(true);
	home[a]->Add(obj);
	if (!playingPile[a]->IsEmpty())
	{
		int x = playingPile[a]->getEndPt().x, y = playingPile[a]->getEndPt().y;
		x = x - 2;
		playingPile[a]->setEndPt(x,y);
	}
}

void Solitaire::moveFromPlayingPileToPlayingPile(int a, int b, int c1, int c2)
{
	int i = c2;
	while (i <= playingPile[b]->getTop())
	{
		PlayingCards obj = playingPile[b]->viewCard(i);
		obj.setFaceUp(true);
		playingPile[a]->Add(obj);
		if (!playingPile[b]->IsEmpty())
		{
			int x = playingPile[b]->getEndPt().x, y = playingPile[b]->getEndPt().y;
			x = x - 2;
			playingPile[b]->setEndPt(x,y);
		}

		if (playingPile[a]->getTop() != 0)
		{
			int x = playingPile[a]->getEndPt().x, y = playingPile[a]->getEndPt().y;
			x = x + 2;
			playingPile[a]->setEndPt(x,y);
		}
		i++;
	}

    for (int i = playingPile[b]->getTop(); i >= c2; i--) {
        PlayingCards abc = playingPile[b]->Remove();
    }
}

void Solitaire::moveFromHomeToPlayingPile(int a, int b, int c)
{
	PlayingCards obj;
	obj = home[b]->Remove();
	obj.setFaceUp(true);
	playingPile[a]->Add(obj);

	if (playingPile[a]->getTop() != 0)
	{
		int x = playingPile[a]->getEndPt().x, y = playingPile[a]->getEndPt().y;
		x = x + 2;
		playingPile[a]->setEndPt(x,y);
	}

}
void Solitaire::Play() {
    point p;
    PileofCards* khel;
    int a = -1, b = -1, c = -1,d = -1;
   for(int awais = 0;;) {
        p = getClickedPoint();
        khel = getClickedPile(p, a, c);

        if (khel != playingPile[a] && khel != home[a] && khel != stock && khel != waste)
        {
            DisplayGame();
            cf.SetCursorAt(0, 0);
            cout << "In valid Click" << endl;
            continue;
        }

        if (khel->getTop() == -1 && khel != stock)
        {
            DisplayGame();
            cf.SetCursorAt(0, 0);
            cout << "Incorrect click retry" << endl;
            continue;
        }

        if (khel == stock){
            cf.SetCursorAt(0, 0);
            cout << "Stock clicked" << endl;
            if (stock->getTop() == -1)
            {
                for (int i = waste->getTop(); i > -1; i--)
                {
                    PlayingCards temp = waste->Remove();
                    temp.setFaceUp(false);
                    stock->Add(temp);
                }
            }
            else if (stock->getTop() != -1)
            {
                moveFromStock();
            }

            DisplayGame();

        }

        else if (khel == home[a])
        {
            b = a;
            p = getClickedPoint();
            khel = getClickedPile(p, a, c);

            if (khel != playingPile[a])
            {
                continue;
            }
            int ht = home[b]->getTop(), pt = playingPile[a]->getTop();
            if ((home[b]->viewCard(ht).getColor() == playingPile[a]->viewCard(pt).getColor() || home[b]->viewCard(ht).getRank() + 1 != playingPile[a]->viewCard(pt).getRank()) && (pt != -1))
            {

                DisplayGame();
                cf.SetCursorAt(0, 0);
                cout << " Invalid Move " << endl;

                continue;
            }
            while (pt != c)
            {
                p = getClickedPoint();
                khel = getClickedPile(p, a, c);
            }

            moveFromHomeToPlayingPile(a, b, c);
            DisplayGame();
        }

        else if (khel == playingPile[a])
        {

            if (khel->viewCard(c).isFaceUp() == false || playingPile[a]->getTop() == -1)
            {
                DisplayGame();
                cf.SetCursorAt(0, 0);
                cout << "Invalid Click " << endl;
                continue;
            }

            int b1 = a;
            d = c;
            p = getClickedPoint();
            khel = getClickedPile(p, a, c);

            if (khel == home[a])
            {
                if (home[a]->getTop() == -1)
                {
                    int pt = playingPile[b1]->getTop();
                    if (playingPile[b1]->viewCard(pt).getRank() != 1)
                    {
                        cf.clearConsole();
                        DisplayGame();
                        cf.SetCursorAt(0, 0);
                        cout << "Invalid Move" << endl;

                        continue;
                    }

                    else
                    {
                        moveFromPlayingPileToHome(a, b1, c);
                    }
                }

                else
                {
                    int pt = playingPile[b1]->getTop(), ht = home[a]->getTop();
                    if ((playingPile[b1]->viewCard(pt).getSuit() != home[a]->viewCard(ht).getSuit() || playingPile[b1]->viewCard(pt).getRank() - 1 != home[a]->viewCard(ht).getRank()))
                    {

                        cf.clearConsole();
                        DisplayGame();
                        cf.SetCursorAt(0, 0);
                        cout << "Invalid Move" << endl;

                        continue;

                    }

                    else
                    {
                        moveFromPlayingPileToHome(a, b1, c);
                    }
                }
            }

            else if (khel == playingPile[a])
            {
                int pt = playingPile[a]->getTop();
                if ((playingPile[b1]->viewCard(d).getColor() == playingPile[a]->viewCard(pt).getColor() || playingPile[b1]->viewCard(d).getRank() + 1 != playingPile[a]->viewCard(c).getRank()) && (pt != -1))
                {
                    cf.clearConsole();
                    DisplayGame();
                    cf.SetCursorAt(0, 0);
                    cout << "Invalid Move1" << endl;
                    continue;
                }

               if (pt != c)
               {
                    cf.clearConsole();
                    DisplayGame();
                    cf.SetCursorAt(0, 0);
                    cout << "Invalid Move2" << endl;
                    continue;
               }
               
               moveFromPlayingPileToPlayingPile(a, b1, c, d);
            }
           
            else {
                cout << "In valid " << endl;
                continue;
            }
            system("cls");
            DisplayGame();
        }

        else if (khel == waste)
        {
            if (khel->IsEmpty()) {
                cf.clearConsole();
                DisplayGame();
                cf.SetCursorAt(0, 0);
                cout << "Empty Pile " << endl;
                continue;
            }

            p = getClickedPoint();
            khel = getClickedPile(p, a, c);
            if (khel == home[a]){
                if (home[a]->getTop() == -1) {
                    if (waste->Peek().getRank() == 1) {
                        moveFromWasteToHome(a);

                    }
                    else
                    {
                        cf.clearConsole();
                        DisplayGame();
                        cf.SetCursorAt(0, 0);
                        cout << "Invalid Move " << endl;

                        continue;
                    }
                }
                else {
                    if ((waste->Peek().getSuit() != home[a]->Peek().getSuit() || waste->Peek().getRank() - 1 != home[a]->Peek().getRank()))
                    {

                        cf.clearConsole();
                        DisplayGame();
                        cf.SetCursorAt(0, 0);
                        cout << " Invalid Move " << endl;
                        continue;
                    }
                    else
                    {
                        moveFromWasteToHome(a);
                    }
                }
            }
            else if (khel == playingPile[a]){
                if ((waste->Peek().getColor() == playingPile[a]->Peek().getColor() || waste->Peek().getRank() + 1 != playingPile[a]->Peek().getRank()) && (playingPile[a]->getTop() != -1))
                {

                    cf.clearConsole();
                    DisplayGame();
                    cf.SetCursorAt(0, 0);
                    cout << "Invalid Move " << endl;

                    continue;

                }
                if (playingPile[a]->getTop() != c)
                {

                    cf.clearConsole();
                    DisplayGame();
                    cf.SetCursorAt(0, 0);
                    cout << "Invalid Move " << endl;
                    continue;

                }
                moveFromWasteToPlayingPile(a, c);
            }
            else {
                cout << "In valid " << endl;
                continue;
            }
            cf.clearConsole();
            DisplayGame();
        }

        int papo = 0;
        for (int i = 0; i < 4; i++)
        {
            if (home[i]->getTop() == 13 - 1)
            {papo++;}
               

            if (papo == 4)
            {return;}
               
        }
    }
}

Solitaire::~Solitaire()
{
    if (stock != NULL)
        delete stock;

    if (waste != NULL)
        delete waste;

    for (int i = 0; i < 4; i++)
        if (home[i] != NULL)
            delete home[i];

    for (int i = 0; i < 7; i++)
        if (playingPile[i] != NULL)
            delete playingPile[i];
}


