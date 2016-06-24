#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;

class Board
{
	public:
		Board();//instructor to initialize the ship

		struct Ship
		{
			string stype;
			int itype,spots;
			bool used;

		};

		//Functions in wonder land
		void BoardReset();
		void BoardPrint();
		void ShipInfo();
		void iInputX();
		void Input();
		bool ShipBound();
		void ShipDup();
		void ShipSetting();
		void ShipDirect();
		void ShipPlacingNS();
		void ShipPlacingEW();
		bool AllShip();
		bool ShipStackNS(int d);
		bool ShipStackEW(int d);
		bool Hit();
		void Attack();

		Ship *ShipMatch(int inShip);

	private:
		int board[10][10];
		char col, dir;
		int row,irow, icol,inShip;
		Ship Car, Bat, Des, Sub, Pat;
		Ship *TheShip;      
};


Board::Board()
{
	Car.stype = "Aircarft Carrier"; Car.itype=1; Car.spots=5; Car.used=0;
	Bat.stype = "Battleship"; Bat.itype=2; Bat.spots=4; Bat.used=0;
	Des.stype = "Destroyer"; Des.itype=3; Des.spots=3; Des.used=0;
	Sub.stype = "Submarine"; Sub.itype=4; Sub.spots=3; Sub.used=0;
	Pat.stype = "Patrol Boat"; Pat.itype=5; Pat.spots=2; Pat.used=0;
}



//Resetting the battle boards
void Board::BoardReset()
{
	int y =10, x=10;
	for(int j=0; j<y; j++)
	{
		for(int i=0; i<x; i++)
		{
			board[y][x] = 0;
		}
	}
}

//Printing the board
void Board:: BoardPrint()
{
	int y =10, x=10;
	cout<<"   A B C D E F G H I J "<<endl;
	for(int j=0; j<y; j++)
	{
		if(j<(y-1))
			cout<<j+1<<"  ";
		else
			cout<<j+1<<" ";
		for(int i=0; i<x; i++)
		{
			cout<<board[y][x]<<" ";  //print array
		}
		cout<<"\n";
	}
}

//Print ship information
void Board::ShipInfo()
{
	cout<<"Please choose a ship: \n [1] Aircraft Carrier - 5 spots\n [2] Battleship - 4 spots\n [3] Destroyer - 3 spots\n [4] Submarine - 3 spots\n [5] Patrol Boat -2 spots\n What ship would you like to put on a board?"<<endl;
}

//Change the input into an integer (Board grid)
void Board::iInputX() //interpret from letter to a number
{
	if(col=='a'||col=='A')
		icol=1;
	else if(col=='b'||col=='B')
		icol=2;
	else if(col=='c'||col=='C')
		icol=3;
	else if(col=='d'||col=='D')
		icol=4;
	else if(col=='e'||col=='E')
		icol=5;
	else if(col=='f'||col=='F')
		icol=6;
	else if(col=='g'||col=='G')
		icol=7;
	else if(col=='h'||col=='H')
		icol=8;
	else if(col=='i'||col=='I')
		icol=9;
	else if(col=='j'||col=='J')
		icol=10;
}

//Ask for input
void Board::Input()
{
	cout<<"Please insert a row [A-J]"<<endl;
	cin>>row;
	cout<<"Please insert a column [1-10]"<<endl;
	cin>>col;
	irow = row;
	iInputX();
}

//Check if the ship lies outside the bound
bool Board::ShipBound()
{
	bool out_of_bounds = 0;
	if(dir=='N'||dir=='n'||dir=='W'||dir=='w') //if ship lies toward north or west
	{
		if((irow-TheShip->spots)<0||(icol-TheShip->spots)<0)
		{
			cout<<"\n*** Error: Ship out of boundary ***\n"<<endl;
			out_of_bounds = 1;
		}
	}
	if(dir=='S'||dir=='s') //if ship lies toward south or east
	{
		if((irow+TheShip->spots)>11||(icol+TheShip->spots)>11)
		{
			cout<<"\n*** Error: Ship out of boundary ***\n"<<endl;
			out_of_bounds = 1;
		}
	}
	return out_of_bounds;
}

//Matching the ship  and return the ship struck to be stored in *TheShip
Board::Ship * Board::ShipMatch(int inShip) 
{
	Board::Ship * next;
	switch (inShip)
	{
		case 1:
			{
				next = &(Car);
				break;
			}
		case 2:
			{
				next = &(Bat);
				break;
			}
		case 3:
			{
				next = &(Des);
				break;
			}
		case 4:
			{
				next = &(Sub);
				break;
			}
		case 5:
			{
				next = &(Pat);
				break;
			}
	}
	return next;
}

//Check if the ship has been used
void Board::ShipDup()
{
	/* If this is run the first time, don't seg fault */
	bool used =1;
	if (TheShip!=0)
	{
		used = TheShip->used;
	}


	if (used)
	{
		do{
			cout<<"The "<<TheShip->stype<<" has been used"<<endl;
			ShipInfo();  //print out the ship info and ask what kind of ship the user want (store in int tyep)
			cin>> inShip;
			TheShip = ShipMatch(inShip); //Return the struct address of the ship that matched so it can be passed other functions.   
		}while(TheShip->used==1);   
		TheShip->used=1;  
	}
}


//Ask What direction to place a ship
void Board::ShipDirect()
{
	bool t;
	cout<<"What direction to put a ship?\n[N] North  [E] East  [W] West  [S] South"<<endl;
	cin>>dir;
	t=ShipBound();
	if(t)
	{
		ShipSetting();
	}  
}

//Check if ship stack on top of each other
bool Board::ShipStackNS(int d) //check for the north and south; recieve 'd' to multiply to control direction of N or S.
{
	bool place_err = 0;
	int c=0, co ,ro;
	for(int i=0;i<TheShip->spots-1;i++)
	{
		if(board[irow-(i*d)][icol]==0)
		{
			c++;
		}
		else
		{
			co = icol;
			ro = (irow -(i*d));
		}
		if(c==TheShip->spots) {
			place_err = 1;//if ship doesn't stack return true
			break;
		}
		else
		{
			cout<<TheShip->stype<<" has been placed at ("<<co<<","<<ro<<")"<<endl;
			place_err = 0; //if ship stack return false
			break;
		}
	}
	return place_err;
}

bool Board::ShipStackEW(int d) //check for the north and south; recieve 'd' to multiply to control direction of E or W.
{
	bool place_err = 0;
	int c=0, co ,ro;
	for(int i=0;i<TheShip->spots-1;i++)
	{
		if(board[irow][icol-(i*d)]==0)
		{
			c++;
		}
		else
		{
			co = (icol-(i*d));
			ro = irow;
		}
		if(c==TheShip->spots) {
			place_err = 1; //if ship doesn't stack return true.
			break;
		}
		else
		{
			std::cout<<TheShip->stype<<" has been placed at ("<<co<<","<<ro<<")"<<std::endl;
			place_err = 0;//if ship stacks return flase
			break;
		}
	}
	return place_err;
}


//Placing Ships
void Board::ShipPlacingNS() //placing the ship on the board in direction of N and S.
{
	int d=0; bool SS;
	if(dir=='n'||dir=='N')
		d=1;
	if(dir=='s'||dir=='S')
		d = -1;
	if(d==-1||d==1)
	{
		SS=ShipStackNS(d);
		if(SS)//if ship doesn't go on top of other ship, place it.
		{
			for(int i=0;i<TheShip->spots-1;i++) 
			{
				board[irow-(i*d)][icol]=TheShip->itype;
			}
		}
	}
	else
	{
		cout<<"Please enter a valid direction";
	}
}

void Board::ShipPlacingEW() //placing the ship on the board in direction of E and W.
{
	int d=0; bool SS;
	if(dir=='e'||dir=='E')
		d=1;
	if(dir=='w'||dir=='W')
		d = -1;
	if(d==-1||d==1)
	{
		SS=ShipStackEW(d);
		if(SS) //if ship doesn't go on top of other place the ship
		{
			for(int i=0;i<TheShip->spots-1;i++)
			{
				board[irow][icol-(i*d)]=TheShip->itype;
			}
		}
	}
	else
	{
		cout<<"Please enter a valid direction";
	}
}


bool Board::AllShip()//check if all the ships are used
{
	return (Car.used == 1 &&
			Bat.used == 1 &&
			Des.used == 1 &&
			Sub.used == 1 &&
			Pat.used == 1 );
}


//Where to put the ship in the board
void Board::ShipSetting() //the object that was passed now name p
{
	bool r,e;
	do{ // For each ship
		do{	// Choose a new ship to place
			ShipDup();
			Input();
			ShipDirect();
			e=ShipBound();
		}while(e);

		// Place the ship
		if(dir=='s'||dir=='S'||dir=='n'||dir=='N') 
			ShipPlacingNS();
		else if(dir=='e'||dir=='E'||dir=='w'||dir=='W')
			ShipPlacingEW();
		// What if they don't enter n, e, s, or w?

		r = AllShip();
	}while(r);	// until all the ships have been placed
}

//Check if it hits a ship
bool Board::Hit()
{
	return (board[irow][icol] != 0);
}

//Begin to attck ship
void Board::Attack()
{
	Input(); //input will be stored in irow, icol.

}


int main()
{
	Board p1, p2;
	p1.BoardReset(); 
	p1.BoardPrint(); 
	p1.ShipSetting();


	return 0;
}
