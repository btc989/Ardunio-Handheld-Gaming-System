/*
 * Notes for Button and Joystick circuit
 * 
 * The space shows VIN; The following instructions are setup up 
 * from the right side of pins to left ending with the space then pin
 * 
 * Far right:
 * 
 * Gnd -> Gnd
 * A0 -> A0
 * A1 -> A1
 * A2 -> A2
 * D1 -> 2
 * P1 -> 3
 * D2 -> 8 //far left button
 * P2 -> 10
 * D3 -> 12 //far right button
 * P3 -> unkonw at moment out due to screen pins 6 or 11 are no longer avalable
 * VDD -> 5V
 * VIN -> VIN
 * const byte PIN_BUTTON_SELECT = 2; 

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 4;
const byte PIN_BUTTON_DOWN = 5;
const byte PIN_BUTTON_LEFT = 6;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

 * I am not if all these pins are needed yet since the board have slots for
 * two joysticks and we are only using one.
 * 
 * 
 * 
 * https://www.virtuabotix.com/running-a-versalino-load-board-with-a-regular-arduino/
 * http://www.josephdattilo.com/writing-bluetooth-packet-based-sketch-versalino-control-board/
 * https://www.virtuabotix.com/arduino-gamepad-versalino-control-1-0-pin-usage/
 * 
 * 
 * 
 * 
 * 
 * 
 */

#include<Board.h>
#include <SPI.h> // We'll use SPI to transfer data. Faster!
#include <TFT.h> // Calling the arduino graphical interface

#define scePin  7  // SCE - Chip select, pin 3 on LCD.
#define rstPin 6  // RST - Reset, pin 4 on LCD.
#define dcPin 5   // DC - Data/Command, pin 5 on LCD.
#define sdinPin  11  // DN(MOSI) - Serial data, pin 6 on LCD.
#define sclkPin 13  // SCLK - Serial clock, pin 7 on LCD.
#define blPin 9   // LED - Backlight LED, pin 8 on LCD.

TFT screen = TFT(scePin, dcPin, rstPin);

const byte PIN_BUTTON_SELECT = 2; 

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 4;
const byte PIN_BUTTON_DOWN = 5;
const byte PIN_BUTTON_LEFT = 6;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;


void setup()
{
  Serial.begin(9600);
  pinMode(PIN_BUTTON_RIGHT, INPUT);
  pinMode(PIN_BUTTON_UP, INPUT);
  pinMode(PIN_BUTTON_LEFT, INPUT);
  pinMode(PIN_BUTTON_DOWN, INPUT);
  pinMode(PIN_BUTTON_SELECT, INPUT);

  randomSeed(analogRead(4));
  screen.begin();
  screen.background(0,0,0);
}

void loop()
{
  static int cursorX = 0;
  static int cursorY = 0;
  int choice;
  int buttonX = analogRead(PIN_ANALOG_X);
  int buttonY =  analogRead(PIN_ANALOG_Y);
  choice = menu(); //menu function call
  Serial.println("Made it back to menu");

  if(choice == 1)
  {
    TicTacToe(); 
  }
  else if(choice == 2)
  {
    Pong(); 
  }
  else
  {
    Snake();
  }  
}

int menu() //This will hold the call for the menu: from this function 
//each game will be called
{
  int buttonY;
  int buttonX;
  char * game1 = ">TIC-TAC-TOE";
  char * game2 = ">SNAKE";
  char * game3 = ">PONG";
  int count=1;

  screen.stroke(255,255,255);
  screen.text("Game Menu", 12, 0);

  screen.text(game1, 0, 12);
  screen.text(" SNAKE", 0, 22);
  screen.text(" PONG", 0, 32);
  
  for(int i =0; ; i++)
  { 
    int pressA;
    delay(200);
    pressA = digitalRead(PIN_BUTTON_RIGHT);
    if(pressA == LOW)
    {
       return count;
    }
    
    buttonY =  analogRead(A1);
    Serial.println(buttonY);
    if(buttonY <350)
    {
      //delay(500);
      Serial.println(count);
      if( count == 1)
      {
        Serial.println("Made it into first if an count");
        count = 2;
        
        screen.text(" TIC-TAC-TOE", 0, 12);
        screen.text(game2, 0, 22);
        screen.text(" PONG", 0, 32);
        
        //delay(1000);
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT); 
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 350) && (buttonY <= 400));
      }
      else if(count == 2)
      {
        count = 3;
        screen.text(" TIC-TAC-TOE", 0, 12);
        screen.text(" SNAKE", 0, 22);
        screen.text(game3, 0, 32);
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT);
           Serial.println(pressA);
           
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
          Serial.println(buttonY);
        }while( (buttonY >= 350) && (buttonY <= 400));
      }
     else if(count == 3)
      {
        count = 1;
        screen.text(game1, 0, 12);
        screen.text(" SNAKE", 0, 22);
        screen.text(" PONG", 0, 32);
       
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT); 
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 350) && (buttonY <= 400));
      } 
    }

    else if (buttonY > 400)
    {
      //delay(500);
      if( count == 1)
      {
        count = 3;

        screen.text(" TIC-TAC-TOE", 0, 12);
        screen.text(" SNAKE", 0, 22);
        screen.text(game3, 0, 32);
        
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT); 
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 350) && (buttonY <= 400));
      }
      
      else if(count == 2)
      {
        count = 1;

        screen.text(game1, 0, 12);
        screen.text(" SNAKE", 0, 22);
        screen.text(" PONG", 0, 32);
          
        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT);
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 350) && (buttonY <= 400));
      }
      
      else if(count == 3)
      {
        count = 2;

        screen.text(" TIC-TAC-TOE", 0, 12);
        screen.text(game2, 0, 22);
        screen.text(" PONG", 0, 32);

        do
        {
           pressA = digitalRead(PIN_BUTTON_RIGHT);
          if(pressA == LOW)
          {
            return count;
          }
          buttonY =  analogRead(A1);
        }while( (buttonY >= 350) && (buttonY <= 400));
      }
      }
    } 
  } 

void Pong()
{

  
}

void Snake()
{

  
}

void TicTacToe()
{
  int buttonY;
  char ans;
  char player1= 'H'; //to see if player or computer
  char player2;
  int x, y;
  char respo; //for the do while loop for continue game play
  char* b[3][3];
  int count = 1;
  screen.stroke(255,255,255);
 

    screen.text("Please state if you want Player 2 to be human or computer? Enter C or H: ", 0, 12);
    screen.text("> C", 0, 22);
    screen.text("> H", 0, 32);
    

    for(int j =0; ; j++)
    {
       int pressA;
       delay(200);
       pressA = digitalRead(PIN_BUTTON_RIGHT);
       if(pressA == LOW)
       {
          player2= 'H';
          goto stop;
       }
       buttonY =  analogRead(A1);
       if(buttonY <350)
       {
        if(count = 1)
        {   
            count =2;
            screen.text("  C", 0, 22);
            screen.text("> H", 0, 32);
          do
          {
             pressA = digitalRead(PIN_BUTTON_RIGHT); 
             if(pressA == LOW)
              {
                player2 = 'H';
                goto stop;
               }
               buttonY =  analogRead(A1);
            }while( (buttonY >= 350) && (buttonY <= 400));
         }
        else if(count = 2)
        {   
            count =1;
            screen.text("> C", 0, 22);
            screen.text("  H", 0, 32);
            do
            {
              pressA = digitalRead(PIN_BUTTON_RIGHT); 
              if(pressA == LOW)
              {
                  player2= 'H';
                  goto stop;
              }
              buttonY =  analogRead(A1);
              }while( (buttonY >= 350) && (buttonY <= 400));
          }
        }
    }
        stop:

    if( (player1== 'H') && (player2=='H')) // For two player humans
    {
      Board board;
      ans = board.EndGame();
      Printarray(b);
      while( ans == 'c')
      {
        screen.text("Player 1 please select your next move (row column) ", 0, 36);
        HumanMoves(x,y,b);

        board.Update(x, y, 'X');
        Printarray(b);
        ans = board.EndGame();
        if(ans != 'c')
        {
          goto s;
        }
        screen.text("Player 2 please select your next move (row column) ", 0, 36);
        HumanMoves(x,y,b);
        board.Update(x, y, 'O');
        Printarray(b);
        ans = board.EndGame();
      }
      s:
      if(ans == 't')
      {
         screen.text("It is a Tie!", 0, 32);   
      }
      else if(ans == '1')
      {
         screen.text("Player 1 Wins!", 0, 32);  
      }
      else if(ans == '2')
      {
         screen.text("Player 2 Wins!", 0, 32);  
      }
    }

    if( (player1== 'H') && (player2=='C')) // For two player humans
    {
      Board board;
      ans = board.EndGame();
      Printarray(b);
      
      while( ans == 'c')
      {
        screen.text("Player 1 please select your next move (row column) ", 0, 36);
        HumanMoves(x,y,b);
        board.Update(x, y, 'X');
        Printarray(b);
        ans = board.EndGame();
        if(ans != 'c')
        {
          goto sto;
        }
        RandomMoves(x,y,b);
        board.Update(x, y, 'O');
        Printarray(b);
        ans = board.EndGame();

      }
      sto:
       if(ans == 't')
        {
            screen.text("It is a Tie!", 0, 32);  
        }
        else if(ans == '1')
        {
           screen.text("Player 1 Wins!", 0, 32);  
        }
        else if(ans == '2')
        {
           screen.text("Player 2 Wins!", 0, 32);  
        }
     
    }
   
  
}

void Printarray( char* b[3][3] ) 
{
  screen.stroke(255,255,255);
  char* a = b[0][0];
  char* c = b[0][1];
  char* d = b[0][2];
  char* e = b[1][0];
  char* f = b[1][1];
  char* g = b[1][2];
  char* h = b[2][0];
  char* i = b[2][1];
  char* j = b[2][2];
  //Row 1
  screen.text("+---+---+---+", 0, 0);
  screen.text("| ", 0, 12);   
  screen.text(a, 3, 12);      
  screen.text("| ", 6, 12);   
  screen.text(c, 14, 12); 
  screen.text("| ", 16, 12);   
  screen.text(d, 18, 12); 
  screen.text("| ", 20, 12);   
  screen.text("+---+---+---+", 0, 14); 
 
   //Row 2  
  screen.text("| ", 0, 22);   
  screen.text(e, 3, 22);      
  screen.text("| ", 6, 22);   
  screen.text(f, 14, 22); 
  screen.text("| ", 16, 22);   
  screen.text(g, 18, 22); 
  screen.text("| ", 20, 22);   
  screen.text("+---+---+---+", 0, 24); 

  //Row 3
  screen.text("+---+---+---+", 0, 0);
  screen.text("| ", 0, 32);   
  screen.text(h, 3, 32);      
  screen.text("| ", 6, 32);   
  screen.text(i, 14, 32); 
  screen.text("| ", 16, 32);   
  screen.text(j, 18, 32); 
  screen.text("| ", 20, 32);   
  screen.text("+---+---+---+", 0, 34); 

}

void HumanMoves( int x, int y, char* b[][3] )
{
   int count =1;
   int pressA;
   int buttonY;
   int w ;
   int v ;
   char  *p1;
   char  *p2 ;

   *p1='X';
   *p2='Y';
   
   screen.text("Row: 1 ", 0, 38);
   screen.text("Column: 1 ", 0, 38);
  do
  {
   for(int i =0; ; i++)
   {
      pressA = digitalRead(PIN_BUTTON_RIGHT);
      if(pressA == LOW)
      {
         x = 1;
         goto end;
      }
      buttonY =  analogRead(A1);
      if(buttonY <350)
      {
         if(count = 1)
         {   
            count =2;
            screen.text("Row: 2 ", 0, 38);
            do
            {
               pressA = digitalRead(PIN_BUTTON_RIGHT); 
               if(pressA == LOW)
               {
                 x=2;
                 goto end;
               }
               buttonY =  analogRead(A1);
             }while( (buttonY >= 350) && (buttonY <= 400));
          }
       else if(count = 2)
       {   
         count =3;
         screen.text("Row: 3 ", 0, 38);
         do
         {
           pressA = digitalRead(PIN_BUTTON_RIGHT); 
           if(pressA == LOW)
           {
              x= 3;
              goto end;
            }
            buttonY =  analogRead(A1);
           }while( (buttonY >= 350) && (buttonY <= 400));
         }
         else if(count = 3)
         {   
           count =1;
           screen.text("Row: 1 ", 0, 38);
           do
           {
             pressA = digitalRead(PIN_BUTTON_RIGHT); 
             if(pressA == LOW)
             {
                x= 1;
                goto end;
              }
              buttonY =  analogRead(A1);
              }while( (buttonY >= 350) && (buttonY <= 400));
            }   
        }
   }
   end:

   for(int i =0; ; i++)
   {
      pressA = digitalRead(PIN_BUTTON_RIGHT);
      if(pressA == LOW)
      {
         y = 1;
         goto end;
      }
      buttonY =  analogRead(A1);
      if(buttonY <350)
      {
         if(count = 1)
         {   
            count =2;
            screen.text("Column: 2 ", 0, 38);
            do
            {
               pressA = digitalRead(PIN_BUTTON_RIGHT); 
               if(pressA == LOW)
               {
                 y=2;
                 goto done;
               }
               buttonY =  analogRead(A1);
             }while( (buttonY >= 350) && (buttonY <= 400));
          }
          else if(count = 2)
          {   
            count =3;
            screen.text("Column: 3 ", 0, 38);
            do
            {
              pressA = digitalRead(PIN_BUTTON_RIGHT); 
              if(pressA == LOW)
              {
                  y= 3;
                  goto done;
              }
              buttonY =  analogRead(A1);
             }while( (buttonY >= 350) && (buttonY <= 400));
          }
          else if(count = 3)
          {   
            count =1;
            screen.text("Column: 1 ", 0, 38);
            do
            {
              pressA = digitalRead(PIN_BUTTON_RIGHT); 
              if(pressA == LOW)
              {
                  y= 1;
                  goto done;
              }
              buttonY =  analogRead(A1);
              }while( (buttonY >= 350) && (buttonY <= 400));
            }   
        }
   }
           done:
           w = x-1;
           v = y-1;
       
 }while((b[w][v] == p1) || (b[w][v] == p2)) ;  

}

void RandomMoves( int& x, int& y,char* board[][3] )
{
  char  *p1;
  char  *p2 ;
  x = random(3); //Finds first random values of x and y between 1 and 3
  y = random(3);
  *p1='X';
  *p2='Y';
   

  while((board[x][y] == p1) || ( board[x-1][y-1] == p2))// If there is already a letter there it will enter loop
  {
    x = random(3); //It will keep looping until a new place is found without a letter
    y = random(3);
  }
}
