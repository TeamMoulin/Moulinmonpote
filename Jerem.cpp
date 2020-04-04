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
	cin>>position;
	if(position>23||position<0)
	{
		cout<<"Cette positon n'existe pas."<<endl;
		demandeVal();
	}
	return(position);
}

void chgt_tour(int* tour) {
	if (*tour == 1) { *tour = 2; }
	else { *tour = 1; }
}

int placePion(int tab[24], int* tour,int* dm)
{
	cout <<"Joueur "<<*tour<< ",entrez la position entre 0 et 23 ou vous voulez placer votre pion : ";
	*dm = demandeVal();
	if (tab[*dm] == 0)
	{
		tab[*dm] = *tour;
		ClearScreen();
	}
	else { cout << "La case choisie n'est pas disponible"<<endl; placePion(tab, tour,dm); }
	return *dm;
}

bool check_move(int tab[24], int* tour, int spion, int promove)//spion:pion qu'on veut déplacer, promove:case ou l'on veut déplacer le pion
{
	bool move = false;
	//Pairs
	if (spion % 2 == 0)
	{
		if (spion % 8 == 0)
		{
			move = (spion + 1 == promove) || (spion + 7 == promove); 
			if (move) 
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (spion + 1 == promove) || (spion - 1 == promove); 
			if (move) 
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (spion < 8) 
		{
			move = (spion + 8 == promove);
		}//Entre les carrés(carré externe)
		if (spion >= 8 && spion < 16) 
		{
			move = (spion - 8 == promove) || (spion + 8 == promove);
		}//Entre les carrés(carré milieu)	
		if (spion >= 16) 
		{
			move = (spion - 8 == promove);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (spion % 2 == 1)
	{
		if (spion % 8 == 7) 
		{
			move = (spion - 7 == promove) || (spion - 1 == promove);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else 
		{
			move = (spion - 1 == promove) || (spion + 1 == promove);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}


bool check_BlockPartout(int tab[24], int* tour, int spion)//spion:pion qu'on veut déplacer, promove:case ou l'on veut déplacer le pion
{
	bool move = false;
	//Pairs
	if (spion % 2 == 0)
	{
		if (spion % 8 == 0)
		{
			move = (tab[spion + 1] == 0) || (tab[spion + 7] == 0);
			if (move)
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (tab[spion + 1] == 0) || (tab[spion - 1] == 0);
			if (move)
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (spion < 8)
		{
			move = (tab[spion + 8] == 0);
		}//Entre les carrés(carré externe)
		if (spion >= 8 && spion < 16)
		{
			move = (tab[spion - 8] == 0) || (tab[spion + 8] == 0);
		}//Entre les carrés(carré milieu)	
		if (spion >= 16)
		{
			move = (tab[spion - 8] == 0);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (spion % 2 == 1)
	{
		if (spion % 8 == 7)
		{
			move = (tab[spion - 7] == 0) || (tab[spion - 1] == 0);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else
		{
			move = (tab[spion - 1] == 0) || (tab[spion + 1] == 0);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}
//si libre renvoie vrai,sinon si tout est bloque renvoie false, verifie pour un pion

bool BlockPartout(int tab[24], int* tour)
{
	bool toutBlock = true;
	int spion = 0;
	while (toutBlock && spion < 24)
	{
		if ((tab[spion] != 0) && (tab[spion] == *tour))
		{
			toutBlock = !(check_BlockPartout(tab, tour, spion ));
		}
		spion++;
	}
	return toutBlock;
}
//si tous les pions sont bloques renvoie vrai, sinon renvoie faux

bool check_moulin(int tab[24], int* tour, int* dm)//dm: dernier mouvement
{
	bool moulin=false;
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
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else 
		{
			moulin = (tab[*dm + 1]) == *tour && (tab[*dm - 1] == *tour); 
			if (moulin) 
			{
				return moulin;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
	if (*dm < 8)
	{
		moulin = (tab[*dm + 8]) == *tour && (tab[*dm + 16] == *tour);
	}//Entre les carrés(carré externe)
	if (*dm >= 8 && *dm < 16)
	{
		moulin = (tab[*dm - 8]) == *tour && (tab[*dm + 8] == *tour);
	}//Entre les carrés(carré milieu)	
	if (*dm >= 16)
	{
		moulin = (tab[*dm - 8]) == *tour && (tab[*dm - 16] == *tour);
	}//Entre les carrés(carré interne)
	}
	//Impairs
	if (*dm % 2 == 1) 
	{
		if (*dm % 8 == 1) 
		{ 
			moulin=(tab[*dm - 1]) == *tour && (tab[*dm + 6] == *tour); 
			if (moulin) 
			{
				return moulin;
			}
		}//pour 1,9 et 17 (indices précédents), si vrai on retourne le résultat immédiatement
			else
			{ 
				moulin=(tab[*dm - 1]) == *tour && (tab[*dm - 2] == *tour); 
				if (moulin) 
				{
					return moulin;
				}
			}//pour les autres valeurs (indices précédents), si vrai on retourne le résultat immédiatement
		if (*dm % 8 == 7) 
		{
			moulin = (tab[*dm - 7]) == *tour && (tab[*dm - 6] == *tour);
		}//pour 7,15 et 23 (indices suivants)
		else
		{
			moulin = (tab[*dm + 1]) == *tour && (tab[*dm + 2] == *tour);
		}//pour les autres valeurs (indices suivants)
	}
return moulin;
}

bool MoulinPartout(int tab[24], int* autreJ)
{
	bool toutMoul = true;
	int cpt = 0;
	while (toutMoul && cpt < 24)
	{
		if ((tab[cpt] != 0) && (tab[cpt] == *autreJ))
		{
			toutMoul = check_moulin(tab, autreJ, &cpt);
		}
		cpt++;
	}
	return toutMoul;
}

void move_pion(int tab[24], int* tour, int* dm) {
	int promove;
	int spion;
	cout << "Joueur " << *tour << ",entrez le pion entre 0 et 23 que vous voulez deplacer : ";
	spion = demandeVal();
	if (check_BlockPartout(tab, tour, spion))
	{
		if (tab[spion] == *tour)
		{
			cout << "Joueur " << *tour << ",entrez la position entre 0 et 23 ou vous voulez deplacer votre pion : ";
			promove = demandeVal();
			if (tab[promove] == 0)
			{
				if (check_move(tab, tour, spion, promove))
				{
					tab[spion] = 0;
					*dm = promove;
					tab[*dm] = *tour;
					ClearScreen();
				}
				else
				{
					cout << "Vous ne pouvez pas deplacer le pion ici" << endl; move_pion(tab, tour, dm);
				}
			}
			else
			{
				cout << "Cette case est deja occupee par un pion" << endl; move_pion(tab, tour, dm);
			}
		}
		else
		{
			cout << "Cette case est vide ou le pion appartient au joueur adverse" << endl;
			move_pion(tab, tour, dm);
		}
	}
	else
	{
		cout << "Ce pion est bloque" << endl; move_pion(tab, tour, dm);
	}
}
void supprPion(int tab[24], int* tour,int* pionj1,int* pionj2)
{
	cout << "Joueur " << *tour << ",entrez le numero du pion entre 0 et 23 que vous voulez supprimer : ";
	int valsuppr = demandeVal();
	int autreJ;
	{
		if ((tab[valsuppr] != 0) && (tab[valsuppr] != *tour))
		{
			if (*tour == 1) 
			{
				autreJ = 2;
				if (MoulinPartout(tab, &autreJ)) 
				{
					cout << "Tous les pions font parti d'un moulin!" << endl; 
					tab[valsuppr] = 0; 
					(*pionj2)--;
					ClearScreen();
				}
				else 
				{
					if (check_moulin(tab, &autreJ, &valsuppr)) 
					{
						cout << "Ce pion fait parti d'un moulin !" << endl; supprPion(tab, tour, pionj1, pionj2);
					}
					else 
					{
						tab[valsuppr] = 0; 
						(*pionj2)--;
						ClearScreen();
					}
				}
			}
			else 
			{
				autreJ = 1;
				if (MoulinPartout(tab, &autreJ)) 
				{
					tab[valsuppr] = 0; 
					(*pionj1)--;
					ClearScreen();
				}
				else 
				{
					if (check_moulin(tab, &autreJ, &valsuppr)) 
					{
						cout << "Ce pion fait parti d'un moulin !" << endl; supprPion(tab, tour, pionj1, pionj2);
					}
					else 
					{
						tab[valsuppr] = 0; 
						(*pionj1)--;
						ClearScreen();
					}
				}
			}
		}
		else 
		{
			cout << "Vous ne pouvez pas supprimer cette case" << endl; supprPion(tab, tour, pionj1, pionj2);
		}
	}
}

void phase1(int tab[24],int* tour,int* dm,int* pionj1,int* pionj2) {
	for (int i = 0; i < 18; i++)
	{
		*dm = placePion(tab, tour,dm);
		affPlateau(tab);
		if (check_moulin(tab, tour, dm)) 
		{
			supprPion(tab, tour, pionj1, pionj2); affPlateau(tab);
		}
		chgt_tour(tour);
	}
}

void phase2(int tab[24], int* tour, int* dm, int* pionj1, int* pionj2)
{
	if (BlockPartout(tab, tour))
	{
		cout << "Vous avez perdu joueur " << *tour << endl;
	}
	else
	{
		while (*pionj1 > 3 && *pionj2 > 3)
		{
			move_pion(tab, tour, dm);
			affPlateau(tab);
			if (check_moulin(tab, tour, dm))
			{
				supprPion(tab, tour, pionj1, pionj2); affPlateau(tab);
			}
			chgt_tour(tour);
		}
	}
}

int main()
{
	int tableau[24] = { 0 };
	// 1 si c est le tour de p1 2 si c est le tour de p2 
	int pionj1 = 9;
	int	pionj2 = 9;
	int turnP = 1;
	int dermove;
	affPlateau(tableau);
	phase1(tableau, &turnP, &dermove,&pionj1,&pionj2);
	phase2(tableau, &turnP, &dermove, &pionj1, &pionj2);
	return 0;
}
