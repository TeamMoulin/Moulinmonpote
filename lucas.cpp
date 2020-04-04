#include <iostream>
#include <windows.h>
using namespace std;
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void affPlateau(int v[24])
{
	cout << "Grille exemple:" << "                            " << "Grille de jeu:" << endl << endl;
	cout << "1" << "----------------" << "2" << "----------------" << "3" << "        " << v[1] << "----------------" << v[2] << "----------------" << v[3] << endl;
	cout << "|                |                |" << "        " << "|                |                |" << endl;
	cout << "|    " << "9" << "-----------" << "10" << "----------" << "11" << "   |" << "        " << "|    " << v[9] << "-----------" << v[10] << "-----------" << v[11] << "    |" << endl;
	cout << "|    |           |           |    |" << "        " << "|    |           |           |    |" << endl;
	cout << "|    |    " << "17" << "-----" << "18" << "-----" << "19" << "   |    |" << "        " << "|    |    " << v[17] << "------" << v[18] << "------" << v[19] << "    |    |" << endl;
	cout << "|    |    |             |    |    |" << "        " << "|    |    |             |    |    |" << endl;
	cout << "0" << "----" << "8" << "----" << "16" << "            " << "20" << "---" << "12" << "---" << "4" << "        " << v[0] << "----" << v[8] << "----" << v[16] << "             " << v[20] << "----" << v[12] << "----" << v[4] << endl;
	cout << "|    |    |             |    |    |" << "        " << "|    |    |             |    |    |" << endl;
	cout << "|    |    " << "23" << "-----" << "22" << "-----" << "21" << "   |    |" << "        " << "|    |    " << v[23] << "------" << v[22] << "------" << v[21] << "    |    |" << endl;
	cout << "|    |           |           |    |" << "        " << "|    |           |           |    |" << endl;
	cout << "|    " << "15" << "----------" << "14" << "----------" << "13" << "   |" << "        " << "|    " << v[15] << "-----------" << v[14] << "-----------" << v[13] << "    |" << endl;
	cout << "|                |                |" << "        " << "|                |                |" << endl;
	cout << "7" << "----------------" << "6" << "----------------" << "5" << "        " << v[7] << "----------------" << v[6] << "----------------" << v[5] << endl << endl;

}

int demandeVal()
{
	int position;
	cin >> position;
	if (position > 23 || position < 0)
	{
		cout << "Cette positon n'existe pas." << endl;
		demandeVal();
	}
	return(position);
}

void chgt_tour(int* tour) {
	if (*tour == 1) { *tour = 2; }
	else { *tour = 1; }
}

int placePion(int tab[24], int* tour)
{
	cout << "Joueur " << *tour << ",entrez la position entre 0 et 23 ou vous voulez placer votre pion : ";
	int dm = demandeVal();
	if (tab[dm] == 0)
	{
		tab[dm] = *tour;
		ClearScreen();
	}
	else { cout << "La case choisie n'est pas disponible" << endl; placePion(tab, tour); }
	return dm;
}

bool check_moulin(int tab[24], int* tour, int* dm)//dm: dernier mouvement
{
	bool moulin = false;
	//Pairs
	if (*dm % 2 == 0)
	{

		if (*dm % 8 == 0)
		{
			moulin = ((tab[*dm + 1]) == *tour) && (tab[*dm + 7] == *tour);
			if (moulin)
			{
				return moulin;
			}
		}
		//Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			moulin = (tab[*dm + 1]) == *tour && (tab[*dm - 1] == *tour);
			if (moulin)
			{
				return moulin;
			}
		}
		//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (*dm < 8)
		{
			moulin = (tab[*dm + 8]) == *tour && (tab[*dm + 16] == *tour);
		}
		//Entre les carrés(carré externe)
		if (*dm >= 8 && *dm < 16)
		{
			moulin = (tab[*dm - 8]) == *tour && (tab[*dm + 8] == *tour);
		}
		//Entre les carrés(carré milieu)	
		if (*dm >= 16)
		{
			moulin = (tab[*dm - 8]) == *tour && (tab[*dm - 16] == *tour);
		}
		//Entre les carrés(carré interne)

	}
	//Impairs
	if (*dm % 2 == 1)
	{
		if (*dm % 8 == 1)
		{
			moulin = (tab[*dm - 1]) == *tour && (tab[*dm + 6] == *tour);
			if (moulin)
			{
				return moulin;
			}
		}
		//pour 1,9 et 17 (indices précédents), si vrai on retourne le résultat immédiatement
		else
		{
			moulin = (tab[*dm - 1]) == *tour && (tab[*dm - 2] == *tour);
			if (moulin)
			{
				return moulin;
			}
		}
		//pour les autres valeurs (indices précédents), si vrai on retourne le résultat immédiatement
		if (*dm % 8 == 7)
		{
			moulin = (tab[*dm - 7]) == *tour && (tab[*dm - 6] == *tour);
		}
		//pour 7,15 et 23 (indices suivants)
		else
		{
			moulin = (tab[*dm + 1]) == *tour && (tab[*dm + 2] == *tour);
		}
		//pour les autres valeurs (indices suivants)
	}
	return moulin;
}

bool MoulinPartout(int tab[24], int* autreJ)
{
	bool condition = true;
	int cpt = 0;
	while (condition && cpt < 24)
	{
		if (tab[cpt] == *autreJ)
		{
			condition = check_moulin(tab, autreJ, &cpt);
		}
		cpt++;
	}
	return condition;
}

void supprPion(int tab[24], int* tour, int* pionJ1, int* pionJ2)
{
	int autreJ;
	cout << "Joueur " << *tour << ",entrez le numero du pion entre 0 et 23 que vous voulez supprimer : ";
	int valsuppr = demandeVal();
	{
		if ((tab[valsuppr] != 0) && (tab[valsuppr] != *tour))
		{
			if (*tour == 1)
			{
				autreJ = 2;
				if (MoulinPartout(tab, &autreJ))
				{
					//cout << "suprimez le pion de votre choix" << endl;
					tab[valsuppr] = 0;
				}
				else if (check_moulin(tab, &autreJ, &valsuppr))
				{
					cout << "Ce pion fait parti d'un moulin !" << endl;
					supprPion(tab, tour, pionJ1, pionJ2);
				}
				else
				{
					tab[valsuppr] = 0;
				}
				(*pionJ2)--;
			}
			if (*tour == 2)
			{
				autreJ = 1;
				if (MoulinPartout(tab, &autreJ))
				{
					//cout << "suprimez le pion de votre choix" << endl;
					tab[valsuppr] = 0;
				}
				else if (check_moulin(tab, &autreJ, &valsuppr))
				{
					cout << "Ce pion fait parti d'un moulin !" << endl;
					supprPion(tab, tour, pionJ1, pionJ2);
				}
				else
				{
					tab[valsuppr] = 0;
				}
				(*pionJ1)--;
			}
		}
		else
		{
			cout << "Vous ne pouvez pas supprimer cette case" << endl; supprPion(tab, tour, pionJ1, pionJ2);
		}
		affPlateau(tab);
	}

}

bool checkMove(int tab[24], int* tour, int proMove, int sPion)
{
	bool move = false;
	//Pairs
	if (sPion % 2 == 0)
	{
		if (sPion % 8 == 0)
		{
			move = (sPion + 1 == proMove) || (sPion + 7 == proMove);
			if (move)
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (sPion + 1 == proMove) || (sPion - 1 == proMove);
			if (move)
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (sPion < 8)
		{
			move = (sPion + 8 == proMove);
		}//Entre les carrés(carré externe)
		if (sPion >= 8 && sPion < 16)
		{
			move = (sPion - 8 == proMove) || (sPion + 8 == proMove);
		}//Entre les carrés(carré milieu)	
		if (sPion >= 16)
		{
			move = (sPion - 8 == proMove);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (sPion % 2 == 1)
	{
		if (sPion % 8 == 7)
		{
			move = (sPion - 7 == proMove) || (sPion - 1 == proMove);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else
		{
			move = (sPion - 1 == proMove) || (sPion + 1 == proMove);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}

bool checkBlocPartout(int tab[24], int* tour, int sPion)
{
	// vérifie si un pion est boqué
	//revoie vrai si une case st libre
	bool move = false;
	//Pairs
	if (sPion % 2 == 0)
	{
		if (sPion % 8 == 0)
		{
			move = (tab[sPion + 1] == 0) || (tab[sPion + 7] == 0);
			if (move)
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (tab[sPion + 1] == 0) || (tab[sPion - 1] == 0);
			if (move)
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (sPion < 8)
		{
			move = (tab[sPion + 8] == 0);
		}//Entre les carrés(carré externe)
		if (sPion >= 8 && sPion < 16)
		{
			move = (tab[sPion - 8] == 0) || (tab[sPion + 8] == 0);
		}//Entre les carrés(carré milieu)	
		if (sPion >= 16)
		{
			move = (tab[sPion - 8] == 0);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (sPion % 2 == 1)
	{
		if (sPion % 8 == 7)
		{
			move = (tab[sPion - 7] == 0) || (tab[sPion - 1] == 0);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else
		{
			move = (tab[sPion - 1] == 0) || (tab[sPion + 1] == 0);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}

bool blocPartout(int tab[24], int* tour)
{
	// vérifie si tout les pions sont bloquées
	//renvoie vrai si le joueur ne peu pas bouger 
	{
		bool condition = true;
		int cpt = 0;
		while (condition && cpt < 24)
		{
			if (tab[cpt] == *tour)
			{
				condition = !checkBlocPartout(tab, tour, cpt);
			}
			cpt++;
		}
		return condition;
	}
}

void movePion(int tab[24], int* tour, int* dm)
{
	int proMove;
	int sPion;
	cout << "J" << *tour << " selectionne du pion a bouger" << endl;
	sPion = demandeVal();
	if (!checkBlocPartout(tab, tour, sPion))
	{
		cout << "ce pion est bloqué, prends en un autre ;)" << endl;
		movePion(tab, tour, dm);

	}
	else 
	{
		if (tab[sPion] == *tour)
		{
			cout << "selection de la case ou le bouger" << endl;
			proMove = demandeVal();
			if (tab[proMove] == 0)
			{
				if (checkMove(tab, tour, proMove, sPion))
				{
					*dm = proMove;
					tab[*dm] = *tour;
					tab[sPion] = 0;
				}
				else
				{
					cout << "ce mouvement est impossible, choisit une autre valeur ;)" << endl;
					movePion(tab, tour, dm);

				}
			}
			else
			{
				cout << "Cette case est deja occupee par un pion" << endl; 
				movePion(tab, tour, dm);	
			}
		}
	}
}

void phase1(int tab[24], int* tour, int* dm, int* pionJ1, int* pionJ2)
{

	for (int i = 0; i < 18; i++)
	{
		*dm = placePion(tab, tour);
		affPlateau(tab);
		if (check_moulin(tab, tour, dm))
		{
			supprPion(tab, tour, pionJ1, pionJ2);
		}
		chgt_tour(tour);
	}
}

void phase2(int tab[24], int* tour, int* dm, int* pionJ1, int* pionJ2)
{
	while (*pionJ1 > 3 || *pionJ2 > 3)
	{
		if (!blocPartout(tab, tour))
		{
			affPlateau(tab);
			movePion(tab, tour, dm);
			if (check_moulin(tab, tour, dm))
			{
				supprPion(tab, tour, pionJ1, pionJ2);
			}
			chgt_tour(tour);
		}
		else
		{
			cout << "tu as perdu" << endl;
		}
	}
}

int main()
{
	int tableau[24] = { 0 };
	// 1 si c est le tour de p1 2 si c est le tour de p2 
	int turnP = 1;
	int dermove;
	int pionJ1 = 9;
	int pionJ2 = 9;
	affPlateau(tableau);
	phase1(tableau, &turnP, &dermove, &pionJ1, &pionJ2);
	phase2(tableau, &turnP, &dermove, &pionJ1, &pionJ2);

	return 0;
}
