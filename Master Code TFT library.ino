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

#include <SPI.h> // We'll use SPI to transfer data. Faster!
#include <TFT.h> // Calling the arduino graphical interface

#define cs   10
#define dc   9
#define rst  8
#define TFTscreenWidth 160
#define TFTscreenHeight 128

TFT TFTscreen = TFT(cs, dc, rst);

int pointX = TFTscreen.width() / 2;
int pointY = TFTscreen.height() / 2; // puts the pointer in the middle

const byte PIN_BUTTON_SELECT = 2;

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 2;
const byte PIN_BUTTON_DOWN = 4;
const byte PIN_BUTTON_LEFT = 5;

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
  TFTscreen.begin();
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.background(255, 255, 255);
  TFTscreen.text("B3 SYSTEMS", 20, 55);
  delay(3000);
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

  if (choice == 1)
  {
    Serial.println(choice);
    TicTacToe();
  }
  else if (choice == 2)
  {
    EtchaSketch();

  }
  else
  {
    Pong();
  }
}

int menu() //This will hold the call for the menu: from this function
//each game will be called
{
  int buttonY;
  int buttonX;
  char * game1 = ">TIC-TAC-TOE";
  char * game2 = ">ETCHY SKETCH";
  char * game3 = ">PONG";
  int count = 1;
  
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.setTextSize(2);
  TFTscreen.background(255, 255, 255);
  TFTscreen.text("Game Menu", 27, 20);
  TFTscreen.text(game1, 7, 50);
  TFTscreen.text(" ETCHY SKETCH", 7, 70);
  TFTscreen.text(" PONG", 7, 90);
  TFTscreen.rect(20, 36, 120, 2);

  for (int i = 0; ; i++)
  {
    int pressA;
    int pressup;
    int pressdown;
    delay(200);
    pressA = digitalRead(PIN_BUTTON_RIGHT);
    if (pressA == LOW)
    {
      return count;
    }

    pressup = digitalRead(PIN_BUTTON_UP);
    pressdown = digitalRead(PIN_BUTTON_DOWN);
    if (pressdown == LOW || pressup == LOW)
    {
      if ( count == 1)
      {
        count = 2;
        TFTscreen.background(255, 255, 255);
        TFTscreen.text("Game Menu", 27, 20);
        TFTscreen.text(" TIC-TAC-TOE", 7, 50);
        TFTscreen.text(game2, 7, 70);
        TFTscreen.text(" PONG", 7, 90);
        TFTscreen.setTextSize(2);
        TFTscreen.rect(20, 36, 120, 2);
          
        pressup = digitalRead(PIN_BUTTON_UP);
        pressdown = digitalRead(PIN_BUTTON_DOWN);
        while ((pressup != HIGH) || (pressdown != HIGH))
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == HIGH)
          {
            return count;
          }
          pressup = digitalRead(PIN_BUTTON_UP);
          pressdown = digitalRead(PIN_BUTTON_DOWN);
        }
      }
      else if (count == 2)
      {
        count = 3;
        TFTscreen.background(255, 255, 255);
        TFTscreen.text("Game Menu", 27, 20);
        TFTscreen.text(" TIC-TAC-TOE", 7, 50);
        TFTscreen.text(" ETCHY SKETCH", 7, 70);
        TFTscreen.text(game3, 7, 90);
        TFTscreen.stroke(0, 0, 0);
        TFTscreen.setTextSize(2);
        TFTscreen.rect(20, 36, 120, 2);
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          pressup = digitalRead(PIN_BUTTON_UP);
          pressdown = digitalRead(PIN_BUTTON_DOWN);
        } while ( pressup != HIGH || pressdown != HIGH);
      }
      else if (count == 3)
      {
        count = 1;
        TFTscreen.background(255, 255, 255);
        TFTscreen.text("Game Menu", 27, 20);
        TFTscreen.text(game1, 7, 50);
        TFTscreen.text(" ETCHY SKETCH", 7, 70);
        TFTscreen.text(" PONG", 7, 90);
        TFTscreen.stroke(0, 0, 0);
        TFTscreen.setTextSize(2);
        TFTscreen.rect(20, 36, 120, 2);

        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          pressup = digitalRead(PIN_BUTTON_UP);
          pressdown = digitalRead(PIN_BUTTON_DOWN);
          Serial.println("MEME");
        } while ( pressdown != HIGH || pressup != HIGH);
      }
    }
  }
}

void Pong()
{
  int myWidth = TFTscreen.width() ;
  int myHeight = TFTscreen.height() / 2; // declares screen dimentions
  TFTscreen.background(255, 255, 255);
  bool test = true;
  int paddleX = 40;
  int paddleY = 120;
  int oldPaddleX, oldPaddleY;
  int ballDirectionX = 1;
  int ballDirectionY = 11;
  int ballX = 20;
  int ballY = 10;
  int oldBallX, oldBallY;
  while (test)
  {
    int pressX = analogRead(A0);
    Serial.println(pressX);
    if (pressX > 600)
    {
      paddleX += 3; //positon move the plus to corresponds to how fast the paddle moves
      if (paddleX > 140) //if reaching the edge of screen
      {
        paddleX = 140;
      }
    }
    else if (pressX < 450)
    {
      paddleX -= 3;
      if (paddleX < 0)
      {
        paddleX = 0;
      }
    }
    if (oldPaddleX != paddleX) // checks if the paddle has moved
    {
      TFTscreen.rect(oldPaddleX, oldPaddleY, 20, 5);
      TFTscreen.fill(255, 255, 255);
    }

    TFTscreen.fill(0, 0, 0);
    TFTscreen.rect(paddleX, paddleY, 20, 5); // draws new paddle and deletes old one

    oldPaddleX = paddleX;
    oldPaddleY = paddleY;

    test = moveBall(ballDirectionX, ballDirectionY, ballX, ballY, oldBallX, oldBallY, paddleX, paddleY);

  }

}

bool moveBall(int& ballDirectionX, int& ballDirectionY, int& ballX, int& ballY, int& oldBallX, int& oldBallY, int& paddleX, int& paddleY)
{
  if (ballX > TFTscreen.width() || ballX < 0)
  {
    ballDirectionX = -ballDirectionX;
  }

  if (ballY > TFTscreen.height())
  {
    return false; // kills game if the ball hits the bottom wall
  }
  if (ballY < 0)
  {
    ballDirectionY = -ballDirectionY; // makes the ball bounce if it hits a wall
  }

  if (inPaddle(ballX, ballY, paddleX, paddleY - 5, 20, 5))
  {
    ballDirectionX = -ballDirectionX + 1;
    ballDirectionY = -ballDirectionY; // bounces ball of the paddle
  }

  ballX += ballDirectionX;
  ballY += ballDirectionY; // direction of the ball

  TFTscreen.noStroke();
  TFTscreen.fill(255, 255, 255);
  TFTscreen.rect(oldBallX, oldBallY, 5, 5); // redraws the ball

  if (oldBallX != ballX || oldBallY != ballY) // tracks ball movement
  {
    TFTscreen.fill(0, 0, 0);
    TFTscreen.rect(ballX, ballY, 5, 5); // redraws the ball

  }

  delay(80);
  TFTscreen.noStroke();
  TFTscreen.fill(255, 255, 255);
  TFTscreen.rect(oldBallX, oldBallY, 5, 5); // draws the ball

  oldBallX = ballX;
  oldBallY = ballY;
  return true;
}
boolean inPaddle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight)
{
  boolean result = false;

  if ((x >= rectX && x <= (rectX + rectWidth)) && (y >= rectY && y <= (rectY + rectHeight)))
  {
    result = true;
  }

  return result;
}
void EtchaSketch()
{
  TFTscreen.background(255, 255, 255);
  int pressup = digitalRead(PIN_BUTTON_UP);
  int pressdown = digitalRead(PIN_BUTTON_DOWN);
  while ( pressup != HIGH || pressdown != LOW)
  {
    int xValue = analogRead(0);
    int yValue = analogRead(1); // reads the joystick values
    delay(50);

    pointX = pointX + (map(xValue, 0, 1023, -2, 3)) / 2;
    pointY = pointY + (map(yValue, 1023, 0, -2, 3)) / 2;   // map the values and update the position

    if (pointX > 159)
    {
      (pointX = 159);
    }

    if (pointX < 0)
    {
      (pointX = 0);
    }
    if (pointY > 127)
    {
      (pointY = 127);
    }
    if (pointY < 0)
    {
      (pointY = 0);   // won't let you draw past the edge of the screen
    }

    TFTscreen.stroke(0, 0, 0);
    TFTscreen.rect(pointX, pointY, 2, 2); // declares the color and size of the pointer

    if (digitalRead(PIN_BUTTON_RIGHT) == LOW)
    {
      TFTscreen.background(255, 255, 255); // clears the screen if the button is pushed
    }
    pressup = digitalRead(PIN_BUTTON_UP);
    pressdown = digitalRead(PIN_BUTTON_DOWN);
  }
}

void TicTacToe()
{
  TFTscreen.background(255, 255, 255);
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.setTextSize(2);
  
  int buttonY;
  char ans;
  char player2;
  int x, y;
  bool respo=true; //for the do while loop for continue game play
  char *b[3][3];
  char  * empty ;
  *empty = '\n';
  for(int i =0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
        b[i][j] =empty;  
    }  
  }
  int count = 1;
  
  TFTscreen.text("Player 2:", 0, 0);
  TFTscreen.text("> C", 0, 22);
  TFTscreen.text("  H", 0, 42);

  for (int j = 0; ; j++)
  {
    int pressA;
    delay(200);
    pressA = digitalRead(PIN_BUTTON_RIGHT);
    if (pressA == LOW)
    {
      player2 = 'C';
      goto stop;
    }
    buttonY =  analogRead(A1);
    if (buttonY < 300)
    {
      if (count = 1)
      {
        count = 2;
         TFTscreen.text("Player 2:", 0, 0);
         TFTscreen.stroke(255,255,255);
         TFTscreen.text(">  C", 0, 22);
         TFTscreen.stroke(0,0,0);
         TFTscreen.text("  C", 0, 22);
         TFTscreen.text("> H", 0, 42);
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            player2 = 'H';
            goto stop;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
      else if (count = 2)
      {
        count = 1;
          TFTscreen.text("Player 2:", 0, 0);
          TFTscreen.text("> C", 0, 22);
          TFTscreen.text("  H", 0, 42);
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            player2 = 'C';
            goto stop;
          }
          buttonY =  analogRead(A1);
        } while ( (buttonY >= 300) && (buttonY <= 400));
      }
    }
  }
stop:

  TFTscreen.background(255, 255, 255);
  if (player2 == 'H') // For two player humans
  {
    ans = EndGame(b);
    Printarray(b);
    while ( ans == 'c')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("Player 1:", 0, 0);
      
      HumanMoves(x, y, b);
      *b[x][y]='X';
      Printarray(b);
      ans =EndGame(b);
      if (ans != 'c')
      {
        goto s;
      }
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("Player 2:", 0, 0);
      HumanMoves(x, y, b);
      *b[x][y]='O';
      Printarray(b);
      ans = EndGame(b);
    }
s:
    if (ans == 't')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("It is a Tie!", 0, 32);
      delay(4000);
    }
    else if (ans == '1')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("Player 1 Wins!", 0, 32);
      delay(4000);
    }
    else if (ans == '2')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("Player 2 Wins!", 0, 32);
      delay(4000);
    }
  }

  if ( player2 == 'C') // For One human against computer
  {
    ans = EndGame(b);
    Printarray(b);

    while (ans == 'c')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("Player 1:", 0, 0);
      HumanMoves(x, y, b);
      *b[x][y]='X';
      Printarray(b);
      ans = EndGame(b);
      if (ans != 'c')
      {
        goto sto;
      }
      RandomMoves(b);
      Printarray(b);
      ans = EndGame(b);
    }
sto:
    if (ans == 't')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("It is a Tie!", 0, 32);
      delay(4000);
    }
    else if (ans == '1')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("Player 1 Wins!", 0, 32);
      delay(4000);
    }
    else if (ans == '2')
    {
      TFTscreen.background(255, 255, 255);
      TFTscreen.text("Player 2 Wins!", 0, 32);
      delay(4000);
    }
  }
}

void Printarray( char* b[3][3] )
{
  //Row 1
  TFTscreen.background(255, 255, 255);
  TFTscreen.text("+---+---+---+", 0, 0);
  TFTscreen.text("| ", 0, 20);
  TFTscreen.text(b[0][0], 10, 8);
  TFTscreen.text("| ", 44, 20);
  TFTscreen.text(b[0][1], 36, 20);
  TFTscreen.text("| ", 48, 20);
  TFTscreen.text(b[0][2], 60, 20);
  TFTscreen.text("| ", 72, 20);
  TFTscreen.text("+---+---+---+", 0, 24);
  
  //Row 2
  TFTscreen.text("| ", 0, 42);
  TFTscreen.text(b[1][0], 10, 42);
  TFTscreen.text("| ", 24, 42);
  TFTscreen.text(b[1][1], 36, 42);
  TFTscreen.text("| ", 48, 42);
  TFTscreen.text(b[1][2], 60, 42);
  TFTscreen.text("| ", 72, 42);
  TFTscreen.text("+---+---+---+", 0, 48);

  //Row 3
  TFTscreen.text("| ", 0, 68);
  TFTscreen.text(b[2][0], 10, 65);
  TFTscreen.text("| ", 24, 68);
  TFTscreen.text(b[2][1], 36, 65);
  TFTscreen.text("| ", 48, 68);
  TFTscreen.text(b[2][2], 60, 65);
  TFTscreen.text("| ", 72, 68);
  TFTscreen.text("+---+---+---+", 0, 70);

  delay(8000);
}

void HumanMoves( int& x, int& y, char * b[][3] )
{
  int count = 1;
  int pressA;
  int pressB;
  int buttonY;

  TFTscreen.text("Row: 1 ", 0, 25);
  TFTscreen.text("Column: 1 ", 0, 45);
 
  do
  {
    for (int i = 0; ; i++)
    {
      pressA = digitalRead(PIN_BUTTON_RIGHT);
      if (pressA == LOW)
      {
        
        x = 1;
        goto end;
        Serial.println("SHHHH");
      }
      buttonY =  analogRead(A1);
      if (buttonY < 300)
      {
        if (count == 1)
        {
          count = 2;
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Row: 1 ", 0, 25);

          TFTscreen.stroke(0,0,0);
          TFTscreen.text("Row: 2 ", 0, 25);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 2;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 2)
        {
          count = 3;
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Row: 2 ", 0, 25);

          TFTscreen.stroke(0,0,0);
          TFTscreen.text("Row: 3 ", 0, 25);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 3;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 3)
        {
          count = 1;
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Row: 3 ", 0, 25);

          TFTscreen.stroke(0,0,0);
          TFTscreen.text("Row: 1 ", 0, 25);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              x = 1;
              goto end;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
      }
    }
    
end:


    for (int i = 0; ; i++)
    {
      pressA = digitalRead(PIN_BUTTON_RIGHT);
      if (pressA == LOW)
      {
        y = 1;
        goto end;
      }
      pressB = digitalRead(PIN_BUTTON_DOWN);
        if (pressB == HIGH)
        {
          HumanMoves(x,y,b);
        }
      buttonY =  analogRead(A1);
      if (buttonY < 300)
      {
        pressB = digitalRead(PIN_BUTTON_DOWN);
        if (pressB == HIGH)
        {
          HumanMoves(x,y,b);
        }
        if (count == 1)
        {
          count = 2;
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Column: 1 ", 0, 45);
          TFTscreen.stroke(0,0,0);
          TFTscreen.text("Column: 2 ", 0, 45);
          
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 2;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 2)
        {
          count = 3;
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Column: 2 ", 0, 45);
          TFTscreen.stroke(0,0,0);
          TFTscreen.text("Column: 3 ", 0, 45);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 3;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
        else if (count == 3)
        {
          count = 1;
          TFTscreen.stroke(255,255,255);
          TFTscreen.text("Column: 3 ", 0, 45);
          TFTscreen.stroke(0,0,0);
          TFTscreen.text("Column: 1 ", 0, 45);
          do
          {
            pressA = digitalRead(PIN_BUTTON_RIGHT);
            if (pressA == LOW)
            {
              y = 1;
              goto done;
            }
            buttonY =  analogRead(A1);
          } while ( (buttonY >= 300) && (buttonY <= 400));
        }
      }
    }
done:
   x= x-1;
   y=y-1;

  } while ((*b[x][y] == 'X') || (*b[x][y] == 'O')) ; 
  
}

void RandomMoves( char * board[][3] )
{
  int x = random(3); //Finds first random values of x and y between 1 and 3
  int y = random(3);
  
  while ((*board[x][y] == 'X') || ( *board[x][y] == 'O')) // If there is already a letter there it will enter loop
  {
    
    x = random(3); //It will keep looping until a new place is found without a letter
    y = random(3);
  }
   *board[x][y]='O';
}
char EndGame(char * b[][3]) // returns a t for tie, c for continue, 1 for player 1 won, 2 for player two won
{
  bool tieTest=true;
  char const tie='t';
  char const cont= 'c';
  char const p1w = '1';
  char const p2w = '2';

  for(int i=0; i<3; i++) //Tests to see if it is a tie, at the end of all the if statements it will check if the bool is true
  {
    for(int j=0; j<3; j++)
    {
      if( *b[i][j] != '\n')//NOTE FOR RIGHT NOW TIE FUNCTION DOES NOT WORK CAN'T SEEM TO TELL WHEN ARRAY IS EMPTY FOR SOME REASON
      {
        Serial.println("CHICHIU");
        tieTest = false;
      }
    }
  }
  
  //All of the following statements check to see if the various ways to win have happened
  
  if(*b[0][0]=='X'&&*b[0][1]=='X'&&*b[0][2]=='X')
  {
    return p1w;
  }
  else if(*b[0][0]=='O'&&*b[0][1]=='O'&&*b[0][2]=='O')
  {
    return p2w;
  }
  else if(*b[1][0]=='X'&&*b[1][1]=='X'&&*b[1][2]=='X')
  {
    return p1w;
  }
  else if(*b[1][0]=='O'&&*b[1][1]=='O'&&*b[1][2]=='O')
  {
    return p2w;
  }
  else if(*b[2][0]=='X'&&*b[2][1]=='X'&&*b[2][2]=='X')
  {
    return p1w;
  }
  else if (*b[2][0]=='O'&&*b[2][1]=='O'&&*b[2][2]=='O')
  {
    return p2w;
  }
  else if (*b[0][0]=='X'&&*b[1][0]=='X'&&*b[2][0]=='X')
  {
    return p1w;
  }
  else if(*b[0][0]=='O'&&*b[1][0]=='O'&&*b[2][0]=='O')
  {
    return p2w;
  }
  else if(*b[0][1]=='X'&&*b[1][1]=='X'&&*b[2][1]=='X')
  {
    return p1w;
  }
  else if(*b[0][1]=='O'&&*b[1][1]=='O'&&*b[2][1]=='O')
  {
    return p2w;
  }
  else if(*b[0][2]=='X'&&*b[1][2]=='X'&&*b[2][2]=='X')
  {
    return p1w;
  }
  else if(*b[0][2]=='O'&&*b[1][2]=='O'&&*b[2][2]=='O')
  {
    return p2w;
  }
  else if(*b[0][0]=='X'&&*b[1][1]=='X'&&*b[2][2]=='X')
  {
    return p1w;
  }
  else if(*b[0][0]=='O'&&*b[1][1]=='O'&&*b[2][2]=='O')
  {
    return p2w;
  }
  else if(*b[0][2]=='X'&&*b[1][1]=='X'&&*b[2][0]=='X')
  {
    return p1w;
  }
  else if(*b[0][2]=='O'&&*b[1][1]=='O'&&*b[2][0]=='O')
  {
    return p2w;
  }
  else if(tieTest) //Tests the previous set bool to check if a tie has been made
  {
    return tie;
  }
  else  //If no other conditions return first then the game can continue
    return cont;//there is no win. 
}
