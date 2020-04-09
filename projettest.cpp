#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void ClearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
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
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }

void coutstr(string a, int nombre)
{
	for(int i=0; i<nombre; i++)
	{
		cout<<a;
	}
}




void coutc(int couleur, int sortie, int fond)
{
   HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute( handle,16*couleur+fond);
   cout<< sortie;
   SetConsoleTextAttribute( handle, 15);

}
void affichePion(int tableau[24], int position)
{
	if (tableau[position] == 1)
		coutc(1,position,15);
	if (tableau[position] == 2)
	{
		coutc(4,position,15);
	}
	if (tableau[position] == 0)
	{
		coutc(0,position,14);
	}
}






void affichePlateau(int v[24], int turnJ[2])
{
//	ClearScreen();
	cout <<endl;
	coutstr(" ",16); cout << "           Grille de jeu" <<endl;
	coutstr(" ",16); affichePion(v,1); coutstr("-",16); affichePion(v,2); coutstr("-",16); affichePion(v,3); cout<<endl;
	coutstr(" ",16); cout << "|                |                |" <<endl;
	coutstr(" ",16); cout << "|    "; affichePion(v,9); cout<< "-----------" ; affichePion(v,10); cout<< "----------" ; affichePion(v,11); cout<< "   |"<<endl; 
	coutstr(" ",16); cout << "|    |           |           |    |" << endl;
	coutstr(" ",16); cout << "|    |   " ; affichePion(v,17); cout<< "------" ; affichePion(v,18); cout<< "-----" ; affichePion(v,19); cout<< "   |    |" <<endl;
	coutstr(" ",16); cout << "|    |    |             |    |    |" << endl;
	coutstr(" ",16); affichePion(v,0); cout<< "----" ; affichePion(v,8); cout<< "---" ; affichePion(v,16); cout<< "             " ; affichePion(v,20); cout<< "---" ; affichePion(v,12); cout<< "---" ; affichePion(v,4); cout<<endl;
	coutstr(" ",16); cout << "|    |    |             |    |    |" <<endl;
	coutstr(" ",16); cout << "|    |   " ; affichePion(v,23); cout<< "------" ; affichePion(v,22); cout<< "-----" ; affichePion(v,21); cout<< "   |    |" <<endl;
	coutstr(" ",16); cout << "|    |           |           |    |" <<endl;
	coutstr(" ",16); cout << "|   " ; affichePion(v,15); cout<< "-----------" ; affichePion(v,14); cout<< "----------" ; affichePion(v,13); cout<< "   |" <<endl;
	coutstr(" ",16); cout << "|                |                |" <<endl;
	coutstr(" ",16); affichePion(v,7); coutstr("-",16); affichePion(v,6); coutstr("-",16); affichePion(v,5); cout<<endl << endl;
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





void chngTour(int turnJ[2]) 
{
	int a = turnJ[0];
	turnJ[0] = turnJ[1];
	turnJ[1] = a;
}





int placePion(int tab[24], int turnJ[2],int* dernierMove)
{
	cout <<"Joueur "<<turnJ[0]<< ",entrez la position entre 0 et 23 ou vous voulez placer votre pion : ";
	*dernierMove = demandeVal();
	if (tab[*dernierMove] == 0)
	{
		tab[*dernierMove] = turnJ[0];
	}
	else { cout << "La case choisie n'est pas disponible"<<endl; placePion(tab, turnJ,dernierMove); }
	return *dernierMove;
}





bool checkMove(int tableau[24], int turnJ[2], int pionSelect, int prochainMove)//pionSelect:pion qu'on veut déplacer, prochainMove:case ou l'on veut déplacer le pion
{
	bool move = false;
	//Pairs
	if (pionSelect % 2 == 0)
	{
		if (pionSelect % 8 == 0)
		{
			move = (pionSelect + 1 == prochainMove) || (pionSelect + 7 == prochainMove); 
			if (move) 
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (pionSelect + 1 == prochainMove) || (pionSelect - 1 == prochainMove); 
			if (move) 
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (pionSelect < 8) 
		{
			move = (pionSelect + 8 == prochainMove);
		}//Entre les carrés(carré externe)
		if (pionSelect >= 8 && pionSelect < 16) 
		{
			move = (pionSelect - 8 == prochainMove) || (pionSelect + 8 == prochainMove);
		}//Entre les carrés(carré milieu)	
		if (pionSelect >= 16) 
		{
			move = (pionSelect - 8 == prochainMove);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (pionSelect % 2 == 1)
	{
		if (pionSelect % 8 == 7) 
		{
			move = (pionSelect - 7 == prochainMove) || (pionSelect - 1 == prochainMove);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else 
		{
			move = (pionSelect - 1 == prochainMove) || (pionSelect + 1 == prochainMove);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}





bool checkMoulin(int tableau[24], int turnJ[2], int* dernierMove, int a)//dernierMove: dernier mouvement
{
	bool moulin=false;
	//Pairs
	if (*dernierMove % 2 == 0)
	{
		if (*dernierMove % 8 == 0) 
		{
			moulin = ((tableau[*dernierMove + 1]) == turnJ[a]) && (tableau[*dernierMove + 7] == turnJ[a]); 
			if (moulin) 
			{
				return moulin;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else 
		{
			moulin = (tableau[*dernierMove + 1]) == turnJ[a] && (tableau[*dernierMove - 1] == turnJ[a]); 
			if (moulin) 
			{
				return moulin;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
	if (*dernierMove < 8)
	{
		moulin = (tableau[*dernierMove + 8]) == turnJ[a] && (tableau[*dernierMove + 16] == turnJ[a]);
	}//Entre les carrés(carré externe)
	if (*dernierMove >= 8 && *dernierMove < 16)
	{
		moulin = (tableau[*dernierMove - 8]) == turnJ[a] && (tableau[*dernierMove + 8] == turnJ[a]);
	}//Entre les carrés(carré milieu)	
	if (*dernierMove >= 16)
	{
		moulin = (tableau[*dernierMove - 8]) == turnJ[a] && (tableau[*dernierMove - 16] == turnJ[a]);
	}//Entre les carrés(carré interne)
	}
	//Impairs
	if (*dernierMove % 2 == 1) 
	{
		if (*dernierMove % 8 == 1) 
		{ 
			moulin=(tableau[*dernierMove - 1]) == turnJ[a] && (tableau[*dernierMove + 6] == turnJ[a]); 
			if (moulin) 
			{
				return moulin;
			}
		}//pour 1,9 et 17 (indices précédents), si vrai on retourne le résultat immédiatement
			else
			{ 
				moulin=(tableau[*dernierMove - 1]) == turnJ[a] && (tableau[*dernierMove - 2] == turnJ[a]); 
				if (moulin) 
				{
					return moulin;
				}
			}//pour les autres valeurs (indices précédents), si vrai on retourne le résultat immédiatement
		if (*dernierMove % 8 == 7) 
		{
			moulin = (tableau[*dernierMove - 7]) == turnJ[a] && (tableau[*dernierMove - 6] == turnJ[a]);
		}//pour 7,15 et 23 (indices suivants)
		else
		{
			moulin = (tableau[*dernierMove + 1]) == turnJ[a] && (tableau[*dernierMove + 2] == turnJ[a]);
		}//pour les autres valeurs (indices suivants)
	}
return moulin;
}





bool moulinPartout(int tableau[24], int turnJ[2])
{
	bool toutMoul = true;
	int cpt = 0;
	while (toutMoul && cpt < 24)
	{
		if (tableau[cpt] == turnJ[1])
		{
			toutMoul = checkMoulin(tableau, turnJ, &cpt,1);
		}
		cpt++;
	}
	return toutMoul;
}





bool checkMovePion(int tableau[24], int pionSelect)//pionSelect:pion qu'on veut déplacer, prochainMove:case ou l'on veut déplacer le pion
{  // si libre vraie si bloqué false
	bool move = false;
	//Pairs
	if (pionSelect % 2 == 0)
	{
		if (pionSelect % 8 == 0)
		{
			move = (tableau[pionSelect + 1] == 0) || (tableau[pionSelect + 7] == 0);
			if (move)
			{
				return move;
			}
		} //Sur les carrés(pour 0,8,16), si vrai on retourne le résultat immédiatement
		else
		{
			move = (tableau[pionSelect + 1] == 0) || (tableau[pionSelect - 1] == 0);
			if (move)
			{
				return move;
			}
		}//Sur les carrés(sauf 0,8,16 qui posent problème), si vrai on retourne le résultat immédiatement
		if (pionSelect < 8)
		{
			move = (tableau[pionSelect + 8] == 0);
		}//Entre les carrés(carré externe)
		if (pionSelect >= 8 && pionSelect < 16)
		{
			move = (tableau[pionSelect - 8] == 0) || (tableau[pionSelect + 8] == 0);
		}//Entre les carrés(carré milieu)	
		if (pionSelect >= 16)
		{
			move = (tableau[pionSelect - 8] == 0);
		}//Entre les carrés(carré interne)
	}
	//Impairs
	if (pionSelect % 2 == 1)
	{
		if (pionSelect % 8 == 7)
		{
			move = (tableau[pionSelect - 7] == 0) || (tableau[pionSelect - 1] == 0);
		}//pour 7,15 et 23 (indices suivants/précédents)
		else
		{
			move = (tableau[pionSelect - 1] == 0) || (tableau[pionSelect + 1] == 0);
		}//pour les autres valeurs (indices suivants/précédents)
	}
	return move;
}





bool blockPartout(int tableau[24], int turnJ[2])
{
	bool toutBlock = true;
	int pionSelect = 0;
	while (toutBlock && pionSelect < 24)
	{
		if (tableau[pionSelect] == turnJ[0])
		{
			toutBlock = !(checkMovePion(tableau, pionSelect));
		}
		pionSelect++;
	}
	return toutBlock;
}





void movePion(int tableau[24], int turnJ[2], int* dernierMove) 
{
	int prochainMove;
	int pionSelect;
	cout << "Joueur " << turnJ[0] << ",entrez le pion entre 0 et 23 que vous voulez deplacer : ";
	pionSelect = demandeVal();
	if (!checkMovePion(tableau, pionSelect))
	{
		cout<<"ce pion est bloque"<<endl;
		movePion(tableau, turnJ, dernierMove);
	}
	if (tableau[pionSelect] == turnJ[0]) 
	{
		if (!checkMovePion(tableau, pionSelect))
		{
			cout<<"ce pion est bloque"<<endl;
			movePion(tableau, turnJ, dernierMove);
		}
		cout << "Joueur " << turnJ[0] << ",entrez la position entre 0 et 23 ou vous voulez deplacer votre pion : ";
		prochainMove = demandeVal();
		if (tableau[prochainMove] == 0)
		{
			if (checkMove(tableau, turnJ, pionSelect, prochainMove))
			{
				tableau[pionSelect] = 0;
				*dernierMove = prochainMove;
				tableau[*dernierMove] = turnJ[0];
			}
			else
			{
				cout << "Vous ne pouvez pas deplacer le pion ici" << endl; movePion(tableau, turnJ, dernierMove);
			}
		}
		else 
		{
			cout << "Cette case est deja occupee par un pion" << endl; movePion(tableau, turnJ, dernierMove);
		}
	}
	else 
	{
		cout << "Cette case est vide ou le pion appartient au joueur adverse"<<endl;
		movePion(tableau, turnJ, dernierMove);
	}
}





void movePionIII(int tableau[24], int turnJ[2], int* dernierMove)
{
	int prochainMove;
	int pionSelect;
	cout << "Joueur " << turnJ[0] << ",entrez le pion entre 0 et 23 que vous voulez deplacer : ";
	pionSelect = demandeVal();
	if (tableau[pionSelect]!=turnJ[0])
	{
		cout<<"Aucun de vos pions se trouve dans cette position, Choisissez une autre position"<<endl;
		movePionIII(tableau, turnJ, dernierMove);
	}
	cout << "Joueur " << turnJ[0] << ",entrez la position entre 0 et 23 ou vous voulez deplacer votre pion"<<endl<< "ou entrez vorte position actuelle pour selectionner un autre pion ";
	prochainMove = demandeVal();
	if (tableau[prochainMove] == 0)
	{
		tableau[pionSelect] = 0;
		*dernierMove = prochainMove;
		tableau[prochainMove] = turnJ[0];
	}
	else 
	{
		cout << "Cette case n''est pas vide, Veuillez choisir a nouveau."<<endl;
		movePionIII(tableau, turnJ, dernierMove);
	}
	
	
}





void supprimePion(int tableau[24],int pions[2], int turnJ[2])
{
	cout << "Joueur " << turnJ[0] << ",entrez le numero du pion entre 0 et 23 que vous voulez supprimer : ";
	int valSupprime = demandeVal();
	if (tableau[valSupprime]==turnJ[1])
	{

		if (moulinPartout(tableau, turnJ)) 
		{
			tableau[valSupprime] = 0; 
			(pions[turnJ[1]-1])--;
		}
		else 
		{
			if (checkMoulin(tableau, turnJ, &valSupprime,1)) 
			{
				cout << "Ce pion fait parti d'un moulin !" << endl; supprimePion(tableau, pions, turnJ);
			}
			else 
			{
				tableau[valSupprime] = 0; 
				(pions[turnJ[1]-1])--;
			}
		}
	}
	else 
	{
		cout << "Vous ne pouvez pas supprimer cette case" << endl; supprimePion(tableau, pions, turnJ);
	}
}





void phase1(int tableau[24],int turnJ[2],int* dernierMove, int pions[2]) 
{
	for (int i = 0; i < 18; i++)
	{
		*dernierMove = placePion(tableau, turnJ, dernierMove);
		affichePlateau(tableau, turnJ);
		if (checkMoulin(tableau, turnJ, dernierMove,0)) 
		{
			supprimePion(tableau, pions, turnJ); 
			affichePlateau(tableau, turnJ);
		}
		chngTour(turnJ);
	}
}





bool phase2(int tableau[24],int turnJ[2],int* dernierMove, int pions[2])
{
	while (!(blockPartout(tableau, turnJ)))
	{
		movePion(tableau, turnJ, dernierMove);
		affichePlateau(tableau, turnJ);
		if (checkMoulin(tableau, turnJ, dernierMove,0))
		{
			supprimePion(tableau, pions, turnJ); 
			affichePlateau(tableau, turnJ);
		}
		chngTour(turnJ);
		if(pions[0]<4 || pions[1]<4)
		{
			return true;
		}
	}
	cout<<"Le joueur "<<turnJ[1]<<" a gagne le jeu.";
	return false;
}

bool phase3(int tableau[24],int turnJ[2],int* dernierMove, int pions[2])
{
	if(phase2(tableau, turnJ, dernierMove, pions))
	{
		while((pions[0]< 4 ^ pions[1]< 4))
		{
			if(pions[turnJ[0]-1] ==3)
			{
				movePionIII(tableau, turnJ, dernierMove);
				affichePlateau(tableau, turnJ);
			}
			else
			{
				movePion(tableau, turnJ, dernierMove);
				affichePlateau(tableau, turnJ);
			}
			if(checkMoulin(tableau, turnJ, dernierMove,0))
			{
				supprimePion(tableau, pions, turnJ); 
				affichePlateau(tableau, turnJ);
			}
			if(pions[turnJ[1]-1] < 3)
			{
				cout<<"Le joueur "<<turnJ[0]<<" a gagne le jeu.";
				return true;
			}
			chngTour(turnJ);		
		}
		cout<<"Il vous reste 20 coups"<<endl;
		for(int i = 0; i < 40; i++)
		{
			movePionIII(tableau, turnJ, dernierMove);
			affichePlateau(tableau, turnJ);
			if(checkMoulin(tableau, turnJ, dernierMove,0))
			{
				cout<<"Le joueur "<<turnJ[0]<<" a gagne le jeu.";
				return true;
			}
			chngTour(turnJ);
		}
		cout<<"Match nul";
		return true;
	}
}





int main()
{
	int tableau[24] = {0};
	int pions[2] = {9, 9};
	int turnJ[2] = {1, 2};
	int dernierMove;
	affichePlateau(tableau, turnJ);
	phase1(tableau, turnJ, &dernierMove, pions);
	phase3(tableau, turnJ, &dernierMove, pions);
	return 0;
}
