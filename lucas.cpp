#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
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

void coutstr(string a, int nombre)
{
	for (int i = 0; i < nombre; i++)
	{
		cout << a;
	}
}

void coutc(int couleur, int sortie, int fond)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 16 * couleur + fond);
	cout << sortie;
	SetConsoleTextAttribute(handle, 15);

}

void affichePion(int tableau[24], int position)
{
	if (tableau[position] == 1)
		coutc(1, position, 15);
	if (tableau[position] == 2)
	{
		coutc(4, position, 15);
	}
	if (tableau[position] == 0)
	{
		coutc(0, position, 14);
	}
}

void affPlateau(int v[24])
{
	ClearScreen();
	cout << endl;
	coutstr(" ", 16); cout << "           Grille de jeu" << endl;
	coutstr(" ", 16); affichePion(v, 1); coutstr("-", 16); affichePion(v, 2); coutstr("-", 16); affichePion(v, 3); cout << endl;
	coutstr(" ", 16); cout << "|                |                |" << endl;
	coutstr(" ", 16); cout << "|    "; affichePion(v, 9); cout << "-----------"; affichePion(v, 10); cout << "----------"; affichePion(v, 11); cout << "   |" << endl;
	coutstr(" ", 16); cout << "|    |           |           |    |" << endl;
	coutstr(" ", 16); cout << "|    |   "; affichePion(v, 17); cout << "------"; affichePion(v, 18); cout << "-----"; affichePion(v, 19); cout << "   |    |" << endl;
	coutstr(" ", 16); cout << "|    |    |             |    |    |" << endl;
	coutstr(" ", 16); affichePion(v, 0); cout << "----"; affichePion(v, 8); cout << "---"; affichePion(v, 16); cout << "             "; affichePion(v, 20); cout << "---"; affichePion(v, 12); cout << "---"; affichePion(v, 4); cout << endl;
	coutstr(" ", 16); cout << "|    |    |             |    |    |" << endl;
	coutstr(" ", 16); cout << "|    |   "; affichePion(v, 23); cout << "------"; affichePion(v, 22); cout << "-----"; affichePion(v, 21); cout << "   |    |" << endl;
	coutstr(" ", 16); cout << "|    |           |           |    |" << endl;
	coutstr(" ", 16); cout << "|   "; affichePion(v, 15); cout << "-----------"; affichePion(v, 14); cout << "----------"; affichePion(v, 13); cout << "   |" << endl;
	coutstr(" ", 16); cout << "|                |                |" << endl;
	coutstr(" ", 16); affichePion(v, 7); coutstr("-", 16); affichePion(v, 6); coutstr("-", 16); affichePion(v, 5); cout << endl << endl;
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

void chngTour(int turn[2])
{
	int a = turn[0];
	turn[0] = turn[1];
	turn[1] = a;
}

int placePion(int tab[24], int turn[2], int* dm)
{
	cout << "Joueur " << turn[0] << ",entrez la position entre 0 et 23 ou vous voulez placer votre pion : ";
	*dm = demandeVal();
	if (tab[*dm] == 0)
	{
		tab[*dm] = turn[0];
		ClearScreen();
	}
	else
	{
		cout << "La case choisie n'est pas disponible" << endl;
		placePion(tab, turn, dm); 
	}
	return *dm;
}

bool checkMoulin(int tableau[24], int turn[2], int* dernierMove, int Joueur1ou2)//dernierMove: dernier mouvement
{
	bool moulin = false;
	//Pairs
	if (*dernierMove % 2 == 0)
	{
		if (*dernierMove % 8 == 0)
		{
			moulin = ((tableau[*dernierMove + 1]) == turn[Joueur1ou2]) && (tableau[*dernierMove + 7] == turn[Joueur1ou2]);
			if (moulin)
			{
				return moulin;
			}
		} 
		//Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement

		else
		{
			moulin = (tableau[*dernierMove + 1]) == turn[Joueur1ou2] && (tableau[*dernierMove - 1] == turn[Joueur1ou2]);
			if (moulin)
			{
				return moulin;
			}
		}
		//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement

		if (*dernierMove < 8)
		{
			moulin = (tableau[*dernierMove + 8]) == turn[Joueur1ou2] && (tableau[*dernierMove + 16] == turn[Joueur1ou2]);
		}
		//Entre les carrés(carré externe)

		if (*dernierMove >= 8 && *dernierMove < 16)
		{
			moulin = (tableau[*dernierMove - 8]) == turn[Joueur1ou2] && (tableau[*dernierMove + 8] == turn[Joueur1ou2]);
		}
		//Entre les carrés(carré milieu)

		if (*dernierMove >= 16)
		{
			moulin = (tableau[*dernierMove - 8]) == turn[Joueur1ou2] && (tableau[*dernierMove - 16] == turn[Joueur1ou2]);
		}
		//Entre les carrés(carré interne)

	}
	//Impairs
	if (*dernierMove % 2 == 1)
	{
		if (*dernierMove % 8 == 1)
		{
			moulin = (tableau[*dernierMove - 1]) == turn[Joueur1ou2] && (tableau[*dernierMove + 6] == turn[Joueur1ou2]);
			if (moulin)
			{
				return moulin;
			}
		}
		//pour 1,9 et 17 (indices précédents), si vrai on retourne le résultat immédiatement
		
		else
		{
			moulin = (tableau[*dernierMove - 1]) == turn[Joueur1ou2] && (tableau[*dernierMove - 2] == turn[Joueur1ou2]);
			if (moulin)
			{
				return moulin;
			}
		}
		//pour les autres valeurs (indices précédents), si vrai on retourne le résultat immédiatement
		
		if (*dernierMove % 8 == 7)
		{
			moulin = (tableau[*dernierMove - 7]) == turn[Joueur1ou2] && (tableau[*dernierMove - 6] == turn[Joueur1ou2]);
		}
		//pour 7,15 et 23 (indices suivants)
		
		else
		{
			moulin = (tableau[*dernierMove + 1]) == turn[Joueur1ou2] && (tableau[*dernierMove + 2] == turn[Joueur1ou2]);
		}
		//pour les autres valeurs (indices suivants)
	}
	return moulin;
}

bool MoulinPartout(int tab[24], int turn[2])
{
	bool condition = true;
	int cpt = 0;
	while (condition && cpt < 24)
	{
		if (tab[cpt] == turn[1])
		{
			condition = checkMoulin(tab, turn, &cpt, 1); // 1 car on désigne l'autre joueur
		}
		cpt++;
	}
	return condition;
}

void supprPion(int tab[24],int turn[2], int pions[2])
{
	cout << "Joueur " << turn[0] << ",entrez le numero du pion entre 0 et 23 que vous voulez supprimer : ";
	int valSupprime = demandeVal();
	if (tab[valSupprime] == turn[1])
	{

		if (MoulinPartout(tab, turn))
		{
			tab[valSupprime] = 0;
			(pions[turn[1] - 1])--;
		}
		else
		{
			if (checkMoulin(tab, turn, &valSupprime, 1))
			{
				cout << "Ce pion fait parti d'un moulin !" << endl; supprPion(tab, turn, pions);
			}
			else
			{
				tab[valSupprime] = 0;
				(pions[turn[1] - 1])--;
			}
		}
	}
	else
	{
		cout << "Vous ne pouvez pas supprimer cette case" << endl; supprPion(tab, turn, pions);
	}
}

bool checkMove(int proMove, int sPion)
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

bool checkBlocPartout(int tab[24], int sPion)
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
				condition = !checkBlocPartout(tab, cpt);
			}
			cpt++;
		}
		return condition;
	}
}

void movePion(int tab[24], int turn[2], int* dm) {
	int promove;
	int spion;
	cout << "Joueur " << turn[0] << ",entrez le pion entre 0 et 23 que vous voulez deplacer : ";
	spion = demandeVal();
	if (tab[spion] == turn[0])
	{
		if (checkBlocPartout(tab, spion))
		{
			cout << "Joueur " << turn[0] << ",entrez la position entre 0 et 23 ou vous voulez deplacer votre pion : ";
			promove = demandeVal();
			if (tab[promove] == 0)
			{
				if (checkMove(spion, promove))
				{
					tab[spion] = 0;
					*dm = promove;
					tab[*dm] = turn[0];
				}
				else
				{
					cout << "Vous ne pouvez pas deplacer le pion ici" << endl; movePion(tab, turn, dm);
				}
			}
			else
			{
				cout << "Cette case est deja occupee par un pion" << endl; movePion(tab, turn, dm);
			}
		}
		else
		{
			cout << "Ce pion est bloque" << endl;
			movePion(tab, turn, dm);
		}
	}
	else
	{
		cout << "Cette case est vide ou le pion appartient au joueur adverse" << endl;
		movePion(tab, turn, dm);
	}
}

void movePion3(int tab[24], int turn[2], int* dm)
{
	int promove;
	int spion;
	cout << "Joueur " << turn[0] << ",entrez le pion entre 0 et 23 que vous voulez deplacer : ";
	spion = demandeVal();
	if (tab[spion] == turn[0])
	{
		cout << "Joueur " << turn[0] << ",entrez la position entre 0 et 23 ou vous voulez deplacer votre pion : ";
		promove = demandeVal();
		if (tab[promove] == 0)
		{
			tab[spion] = 0;
			*dm = promove;
			tab[*dm] = turn[0];
		}
		else
		
		{
			cout << "Cette case est deja occupee par un pion" << endl; 
			movePion3(tab, turn, dm);
		}

	}
	
	else
	{
		cout << "Cette case est vide ou le pion appartient au joueur adverse" << endl;
		movePion3(tab, turn, dm);
	}
}

void phase1(int tab[24], int turn[2], int* dm, int pions[2])
{

	for (int i = 0; i < 18; i++)
	{
		*dm = placePion(tab, turn, dm);
		affPlateau(tab);
		if (checkMoulin(tab, turn, dm, 0))
		{
			supprPion(tab, turn, pions);
		}
		chngTour(turn);
	}
}

void phase2(int tab[24], int turn[2], int* dm, int pions[2])
{
	int toursRestants = 20;
	while ((pions[0] > 3 || pions[1] > 3))
	{
		if (pions[turn[0] - 1] == 3)
		{
			movePion3(tab, turn, dm);
			affPlateau(tab);
		}
		else if (!(blocPartout(tab, turn)))
		{
			movePion(tab, turn, dm);
			affPlateau(tab);
		}
		else
		{
			cout << "Le joueur " << turn[1] << " a gagne le jeu." <<endl;
			return;
		}
		if (checkMoulin(tab, turn, dm, 0))
		{
			supprPion(tab, turn, pions);
			affPlateau(tab);
		}
		if (pions[turn[1] - 1] < 3)
		{
			cout << "Le joueur " << turn[0] << " a gagne le jeu." << endl;
			return;
		}
		chngTour(turn);
	}
	cout << "Il vous reste 20 coups" << endl;
	for (int i = 0; i < 40; i++)
	{
		chngTour(turn);
		if (i % 2 == 0 )
		{
			toursRestants--;
		}
		cout << "il vous restes " << toursRestants << "tours" << endl;
		movePion3(tab, turn, dm);
		affPlateau(tab);
		if (checkMoulin(tab, turn, dm, 0))
		{
			cout << "Le joueur " << turn[0] << " a gagne le jeu." << endl;
			return;
		}

	}
	cout << "Match nul" << endl;
	return;

}

int main()
{
	int tableau[24] = { 0 };
	// 1 si c est le tour de p1 2 si c est le tour de p2 
	int turn[2] = { 1,2 };
	int dermove;
	int pions[2] = { 9,9 };
	affPlateau(tableau);
	phase1(tableau, turn, &dermove, pions);
	phase2(tableau, turn, &dermove, pions);
	string rejouer = "oui";
	string choix;
	cout << "si vous voulez rejouer entrez: oui" << endl;
	cout << "si vous voulez vous arréter entrez: non" << endl;
	cin >> choix;
	if (choix == rejouer)
	{
		main();
	}
	return 0;
}
