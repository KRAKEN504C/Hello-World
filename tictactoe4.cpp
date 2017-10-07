/*
  Konrad Roszczynialski
  kółko i krzyżyk wersja 9-planszowa.

  Do zrobienia:
  -SI
  -poprawa funkcji przemieszczajacej między mini planszami.
*/

#include <iostream>
#include <cstdlib>
#include <conio.h>

using namespace std;
char sq[9][9]={};
int checkwin=0;

//1.ta funkcja przyjmuje od gracza wspolrzedne, gdzie gracz chce umiescic swoj znak.
void move(int *x,int *y)
{
	int innex=-1, inney=-1;
		cout << "Prosze podac pole w ukladzie wspolrzednych od 1 do 3:\n";
		cout << "Prosze podac wspolrzedna x:\n";
		cin >> innex;
		while(innex<1 || innex>3){
			cout << "\nBlad! podano wspolrzadna spoza przedzialu od 1 do 3!\n";
			cin >> innex;
		}
		cout << "\nWybrales wspolrzedna x:" << innex <<"\n";
		cout << "prosze podac wspolrzedna y:";
		cin >> inney;
		while(inney<1 || inney>3){
			cout << "\nBlad! podano wspolrzadna spoza przedzialu od 1 do 3!\n";
			cin >> inney;
		}
		cout << "\nWybrales wpolrzedna y:" << inney <<"\n";
		*x=innex;
		*y=inney;
		//cout << "test";
}
//3.ta funkcja bierze zmodyfikawane wspolrzedne, i wstawia znak w odpowiednie miejsce.
void makemove(int *x, int *y, int *plr)
{
  if (*plr==0)
  {
		sq[*x-1][*y-1]=88;
    *plr=1;
  }else
  {
    sq[*x-1][*y-1]=79;
    *plr=0;
  }
}

//4.ta funkcja przesuwa pole, na ktorym odbywa sie rozgrywka.
//specjalna alternatywa. 9 if-ów. kazdy zmienia pole w zaleznosci od niezmodyfikowanych wspolrzednych
//trza poprawic
int moveminiboard(int x, int y,int chboard)
{
  if (x==1 && y==1)
  {
    if (chboard==4 || chboard==7) {return chboard-=3;}else
    if (chboard==3 || chboard==2) {return chboard-=1;}else
    if (chboard==1) {return chboard;}else
    return chboard-=4;
  }else
  if (x==1 && y==2)
  {
    if (chboard==1 || chboard==4 || chboard==7){return chboard;}else
    return chboard-=1;
  }else
  if (x==1 && y==3)
  {
    if(chboard==1 || chboard==4){return chboard+=3;}else
    if(chboard==8 || chboard==9){return chboard-=1;}else
    if(chboard==7){return chboard;}else
    return chboard+=2;
  }else
  if (x==2 && y==1)
  {
    if(chboard>=1 && chboard <=3){return chboard;}else
    return chboard-=3;
  }else
  if (x==2 && y==2)
  {
    return chboard;
  }else
  if (x==2 && y==3)
  {
    if(chboard>=7 && chboard <=9){return chboard;}else
    return chboard+=3;
  }else
  if (x==3 && y==1)
  {
    if(chboard==2 || chboard==1){return chboard+=1;}else
    if(chboard==6 || chboard==9){return chboard-=3;}else
    if(chboard==3){return chboard;}else
    return chboard-=2;
  }else
  if (x==3 && y==2)
  {
    if (chboard==3 || chboard==6 || chboard==9){return chboard;}else
    return chboard+=1;
  }else
  if (x==3 && y==3)
  {
    if (chboard==3 || chboard==6) {return chboard+=3;}else
    if (chboard==7 || chboard==8) {return chboard+=1;}else
    if (chboard==9) {return chboard;}else
    return chboard+=4;
  }
}

//pomniejsza funkcja wskazujaca miejsce akcji, i aktualnego gracza.
miejsceakcji(int chboard, int plr)
{
  cout << "aktualny ruch odbedzie sie na planszy: ";
  switch (chboard)
  {
    case 1:
    cout << "polnocno zachodniej.\n";
    break;
    case 2:
    cout << "polnocnej.\n";
    break;
    case 3:
    cout << "polnocno wschodniej.\n";
    break;
    case 4:
    cout << "zachodniej.\n";
    break;
    case 5:
    cout << "srodkowej.\n";
    break;
    case 6:
    cout << "wschodniej.\n";
    break;
    case 7:
    cout << "poludniowo zachodniej.\n";
    break;
    case 8:
    cout << "poludniowej.\n";
    break;
    case 9:
    cout << "poludniowo wschodniej.\n";
    break;
  }
  cout << "\n\n Aktualny  ruch nalezy do gracza ze znakiem :";
  if(plr==0)  {cout << "\t X\n"; }else
  {cout << "\t O\n";}
}


//2.ta funkcja modyfikuje podane wspolrzedne, zeby wskazywaly poprawna plansze.
void checkboard (int chboard, int *x, int *y)
{
	switch (chboard)
	{
		case 1:
			*x+=0;
			*y+=0;
		break;
		case 2:
			*x+=3;
			*y+=0;
		break;
		case 3:
			*x+=6;
			*y=0;
		break;
		case 4:
			*x+=0;
			*y+=3;
		break;
		case 5:
			*x+=3;
			*y+=3;
		break;
		case 6:
			*x+=6;
			*y+=3;
		break;
		case 7:
			*x+=0;
			*y+=6;
		break;
		case 8:
			*x+=3;
			*y+=6;
		break;
		case 9:
			*x+=6;
			*y+=6;
		break;

	}
}

//0. ta funkcja wyswietla pole gry.
void board()
{
	system("cls");
	cout << "\n\n\tTic Tac Toe\n\n";
	cout << "\nGra zaczyna sie od srodkowego pola i ruch gracza wyznacza 1 z 9 plansz na ktorych bedzie mozna dokonac nastepnego ruchu. tak dopuki ni pojawi sie 3 x lub o pod rzad.\n";
	cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
	cout << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][0] << "  |  " << sq[1][0] << "  |  " << sq[2][0] << "          " << sq[3][0] << "  |  " << sq[4][0] << "  |  " << sq[5][0] << "          " << sq[6][0] << "  |  " << sq[7][0] << "  |  " << sq[8][0] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][1] << "  |  " << sq[1][1] << "  |  " << sq[2][1] << "          " << sq[3][1] << "  |  " << sq[4][1] << "  |  " << sq[5][1] << "          " << sq[6][1] << "  |  " << sq[7][1] << "  |  " << sq[8][1] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][2] << "  |  " << sq[1][2] << "  |  " << sq[2][2] << "          " << sq[3][2] << "  |  " << sq[4][2] << "  |  " << sq[5][2] << "          " << sq[6][2] << "  |  " << sq[7][2] << "  |  " << sq[8][2] << endl;
	cout << "     |     |                |     |                |     |     " << endl << endl;

	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][3] << "  |  " << sq[1][3] << "  |  " << sq[2][3] << "          " << sq[3][3] << "  |  " << sq[4][3] << "  |  " << sq[5][3] << "          " << sq[6][3] << "  |  " << sq[7][3] << "  |  " << sq[8][3] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][4] << "  |  " << sq[1][4] << "  |  " << sq[2][4] << "          " << sq[3][4] << "  |  " << sq[4][4] << "  |  " << sq[5][4] << "          " << sq[6][4] << "  |  " << sq[7][4] << "  |  " << sq[8][4] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][5] << "  |  " << sq[1][5] << "  |  " << sq[2][5] << "          " << sq[3][5] << "  |  " << sq[4][5] << "  |  " << sq[5][5] << "          " << sq[6][5] << "  |  " << sq[7][5] << "  |  " << sq[8][5] << endl;
	cout << "     |     |                |     |                |     |     " << endl << endl;

	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][6] << "  |  " << sq[1][6] << "  |  " << sq[2][6] << "          " << sq[3][6] << "  |  " << sq[4][6] << "  |  " << sq[5][6] << "          " << sq[6][6] << "  |  " << sq[7][6] << "  |  " << sq[8][6] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][7] << "  |  " << sq[1][7] << "  |  " << sq[2][7] << "          " << sq[3][7] << "  |  " << sq[4][7] << "  |  " << sq[5][7] << "          " << sq[6][7] << "  |  " << sq[7][7] << "  |  " << sq[8][7] << endl;
	cout << "_____|_____|_____      _____|_____|_____      _____|_____|_____" << endl;
	cout << "     |     |                |     |                |     |     " << endl;
	cout << "  " << sq[0][8] << "  |  " << sq[1][8] << "  |  " << sq[2][8] << "          " << sq[3][8] << "  |  " << sq[4][8] << "  |  " << sq[5][8] << "          " << sq[6][8] << "  |  " << sq[7][8] << "  |  " << sq[8][8] << endl;
	cout << "     |     |                |     |                |     |     " << endl;
}

//funkcja sprawdzajaca, czy ktorys gracz wygrał. albo cay nie bylo remisu. Jest 8 mozliwosci wygranej w normalne kolko i krzyzyk. dziala z opuznieniem jednego ruchu.
int fcheckwin()
{
  //int x=0,y=0;
  int check=0;
  int wincondition=0;

  for(int x=0;x<=8;x+=3)
  {
    for(int y=0;y<=8;y+=3)
    {

      //if(sq[x][y]==0 || sq[x+1][+1]==0 || sq[x+2][y+2]==0){return 0;}else   {
      if(sq[x][y]==sq[x+1][y] && sq[x+1][y]==sq[x+2][y]){if(sq[x][y]==88){return 1;}else if(sq[x][y]==79){return 2;}}else
      if(sq[x][y+1]==sq[x+1][y+1] && sq[x+1][y+1]==sq[x+2][y+1]){if(sq[x][y+1]==88){return 1;}else if(sq[x][y+1]==79){return 2;}}else
      if(sq[x][y+2]==sq[x+1][y+2] && sq[x+1][y+2]==sq[x+2][y+2]){if(sq[x][y+2]==88){return 1;}else if(sq[x][y+2]==79){return 2;}}else

      if(sq[x][y]==sq[x][y+1] && sq[x][y+1]==sq[x][y+2]){if(sq[x][y]==88){return 1;}else if(sq[x][y]==79){return 2;}}else
      if(sq[x+1][y]==sq[x+1][y+1] && sq[x+1][y+1]==sq[x+1][y+2]){if(sq[x+1][y]==88){return 1;}else if(sq[x+1][y]==79){return 2;}}else
      if(sq[x+2][y]==sq[x+2][y+1] && sq[x+2][y+1]==sq[x+2][y+2]){if(sq[x+2][y]==88){return 1;}else if(sq[x+2][y]==79){return 2;}}else

      if(sq[x][y]==sq[x+1][y+1] && sq[x+1][y+1]==sq[x+2][y+2]){if(sq[x][y]==88){return 1;}else if(sq[x][y]==79){return 2;}}else
      if(sq[x+3][y]==sq[x+1][y+1] && sq[x+1][y+1]==sq[x][y+3]){if(sq[x+3][y]==88){return 1;}else if(sq[x+3][y]==79){return 2;}}   //}

      //cout << x << "\t" << y << endl;
    }
  }

  //if(wincondition==1){return 1;}else if(wincondition==2){return 2;}else

  for(int i=0;i<=8;i++)
  {
    for(int z=0;z<=8;z++)
    {
      if(sq[i][z]!=0){check++;}
    }
  }
  if(check==81){return 3;}else
  return 0;
}


//sztuczna inteligencja. Bardzo sztuczna.
int SI(int ruchSI)
{

}






int main()
{
  int player=0;
  int *wspplr=& player;
	int chboard=5;
	int newchboard;
	int wartoscx=-1;
	int wartoscy=-1;
  int niezmienionex;
  int niezmienioney;
	int *wspx= &wartoscx;
	int *wspy=& wartoscy;


	while(checkwin==0)
	{
		board();
    miejsceakcji(chboard,player);

		move(wspx,wspy);

		//cout << *wspx << *wspy << endl;

    niezmienionex=*wspx; niezmienioney=*wspy;
		checkboard(chboard,wspx,wspy);
		while(sq[*wspx-1][*wspy-1]!=0)
		{
			cout << "\nBlad! podano wspolrzedne, ktora juz jest oznaczona.\n\n";
			move(wspx,wspy);
      niezmienionex=*wspx; niezmienioney=*wspy;
			checkboard(chboard,wspx,wspy);
		}

		//cout << *wspx << *wspy;

		makemove(wspx,wspy,wspplr);

    newchboard=moveminiboard(niezmienionex,niezmienioney,chboard);
    chboard=newchboard;

    cout <<niezmienionex << "\t" <<niezmienioney << endl << chboard << "\t" << newchboard;
    //system("pause");
    checkwin=fcheckwin();
    system("pause");
	}

  board();

if(checkwin==1){cout << "\n\n\t\tGratulacje Wygrales!!!";}else
if(checkwin==2){cout << "\n\n\t\tKomputer wygral.";}else
if(checkwin==3){cout << "\n\n\t\tnie ma mozliwosci wykonania ruchu. Remis.";}else
{cout << "\n\n\n\tNastapil jakis niespodziewany blad. hmmm... ciekawe.";}

//board();


    return 0;
}
