#include<iostream>

class TicTacToe{
   public:
      TicTacToe();	// empty initializer
      TicTacToe( char p1, char p2 );	// custom player names
      void initializeBoard();
      void setPlayer1(char c);
      void setPlayer2(char e);
      char getPlayer1();
      char getPlayer2();
      void printBoard();
      void setPlayers(char p1,char p2);
      void determinePlayerChoice(char player,int row, int col);
      void fillBoard(TicTacToe &p, bool t);
      bool turn(int *i);
      bool isFull();
   private:
      char board[3][3];
      char player1;
      char player2;

};
TicTacToe::TicTacToe()
{
   player1='X';
   player2='O';
   initializeBoard();
}

void TicTacToe::initializeBoard()
{
   for(int y =0;y<3;y++)
   {
      for(int x = 0;x<3;x++)
      {
	 board[y][x]=' ';

      }
   }
}

TicTacToe::TicTacToe(char p1, char p2)
{
   player1=p1;
   player2=p2;
   TicTacToe::initializeBoard();
}


void TicTacToe::setPlayer1(char c)
{  
   player1= c;
}



void TicTacToe::setPlayer2(char e)
{ 
   player2 = e;
}

char TicTacToe::getPlayer1()
{
   return player1;
}

char TicTacToe::getPlayer2()
{
   return player2;
}

void TicTacToe::setPlayers(char p1, char p2)
{
   setPlayer1(p1);
   setPlayer2(p2);
}



void TicTacToe::determinePlayerChoice(char player ,int row, int col)
{
   board[row-1][col-1]= player;

}

bool TicTacToe::turn(int *i)
{
   std::cout<<*i<<std::endl;

   if((*i)%2==0)
   {
      (*i)++;
      return(0); // false if it is an even number
   }
   else 
   {
      (*i)++;
      return(1); // true if it's an odd number
   }
}

void TicTacToe::fillBoard(TicTacToe &p,bool t)
{
   int row,col;
   if(t)
   {
      std::cout<<"Player 1 turn"<<std::endl;
      std::cout<<"Row: ";
      std::cin>>row;
      std::cout<<"Colume: ";
      std::cin>>col;
      determinePlayerChoice(p.player1, row,col);
   }
   else
   {
      std::cout<<"Player 2 turn"<<std::endl;
      std::cout<<"Row: ";
      std::cin>>row;;
      std::cout<<"Colume: ";
      std::cin>>col;
      determinePlayerChoice(p.player2, row,col);
   }
}




void TicTacToe::printBoard()
{
   for(int y =0;y<3;y++)
   {
      for(int x = 0;x<3;x++)
      {
	 std::cout<<"|"<<board[y][x]<<"|";
      }
      std::cout<<"\n";
   }
}

bool TicTacToe::isFull()
{
   int f=0;
   for(int y =0;y<3;y++)
   {
      for(int x = 0;x<3;x++)
      {
	 if(board[y][x]==' ')
	 {
	    f++;
	 }
      }
   }
   if(f==0)  
      return (0);
   else
      return(1);
}


int main()
{
   bool t,re;
   char p1,p2;
   int i=1;
   std::cout<<"Player1: ";
   std::cin>> p1;
   std::cout<<"Player2: ";
   std::cin>> p2;
   TicTacToe p(p1,p2);
   do{
      t=p.turn(&i);
      p.fillBoard(p, t);
      p.printBoard();
      re = p.isFull();
   }while(re);
   return 0;
}
