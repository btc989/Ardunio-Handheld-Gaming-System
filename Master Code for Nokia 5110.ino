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
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define screenHeight 48
#define screenWidth 84
#define scePin  7  // SCE - Chip select, pin 3 on LCD.
#define rstPin 6  // RST - Reset, pin 4 on LCD.
#define dcPin 5   // DC - Data/Command, pin 5 on LCD.
#define sdinPin  11  // DN(MOSI) - Serial data, pin 6 on LCD.
#define sclkPin 13  // SCLK - Serial clock, pin 7 on LCD.
#define blPin 8// LED - Backlight LED, pin 8 on LCD.

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 11, 5, 7, 6);

const byte PIN_BUTTON_SELECT = 2;

const byte PIN_BUTTON_RIGHT = 3;
const byte PIN_BUTTON_UP = 4;
const byte PIN_BUTTON_DOWN = 5;
const byte PIN_BUTTON_LEFT = 6;

const byte PIN_ANALOG_X = 0;
const byte PIN_ANALOG_Y = 1;

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

/*****For Snake*****/
int screenheight = 48;
int screenwidth = 84;
int direction=0;
const int size = 25;
int layout[size];
int bodyX[size];
int bodyY[size];

/**********/

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_BUTTON_RIGHT, INPUT);
  pinMode(PIN_BUTTON_UP, INPUT);
  pinMode(PIN_BUTTON_LEFT, INPUT);
  pinMode(PIN_BUTTON_DOWN, INPUT);
  pinMode(PIN_BUTTON_SELECT, INPUT);

  randomSeed(analogRead(4));
  display.begin();
  display.clearDisplay();
  display.setContrast(70);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(12,14);
  display.println("B3 SYSTEMS");
  display.display();
  delay(2000);
  
  
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
  display.clearDisplay();
  display.display();
  Serial.println(choice);
  if (choice == 1)
  {
    TicTacToe();
  }
  else if (choice == 2)
  {
      EtchASketch();
    
  }
  else if(choice == 3)
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
  char * game2 = ">ETCH-A-SKETCH";
  char * game3 = ">PONG";
  int count = 4;

  display.clearDisplay();
  display.display();
  
  display.setCursor(12,0);
  display.println("Game Menu");
  
  display.setCursor(0,12);
  display.println(game1);
  display.setCursor(0,22);
  display.println(" ETCH-A-SKETCH");
  display.setCursor(0,32);
  display.println(" PONG");
  display.display();
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

    //buttonY =  analogRead(A1);
    pressup = digitalRead(PIN_BUTTON_UP);
    pressdown = digitalRead(PIN_BUTTON_DOWN);
    //Serial.println(buttonY);
    if (pressdown==LOW)
    {
      if ( count == 1)
      {
        count = 2;

        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(" TIC-TAC-TOE");
        display.setCursor(0,22);
        display.println(game2);
        display.setCursor(0,32);
        display.println(" PONG");
        display.display();
        //delay(1000);
        //buttonY =  analogRead(A1);
        pressup = digitalRead(PIN_BUTTON_UP);
        pressdown = digitalRead(PIN_BUTTON_DOWN);
        while ((pressup != LOW) || (pressdown != LOW))
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          //buttonY =  analogRead(A1);
          pressup = digitalRead(PIN_BUTTON_UP);
          pressdown = digitalRead(PIN_BUTTON_DOWN);
        } 
      }
      else if (count == 2)
      {
        count = 3;
        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(" TIC-TAC-TOE");
        display.setCursor(0,22);
        display.println(" ETCH-A-SKETCH");
        display.setCursor(0,32);
        display.println(game3);
        display.display();
        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          //buttonY =  analogRead(A1);
          //Serial.println(buttonY);
          pressup = digitalRead(PIN_BUTTON_UP);
          pressdown = digitalRead(PIN_BUTTON_DOWN);
        } while ( pressup !=LOW || pressdown != LOW);
      }
      else if (count == 3)
      {
        count = 4;
        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(">SNAKE");
        display.display();

        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          //buttonY =  analogRead(A1);
          pressup = digitalRead(PIN_BUTTON_UP);
          pressdown = digitalRead(PIN_BUTTON_DOWN);
        } while ( pressdown != LOW || pressup != LOW);
      }
       else if (count == 4)
      {
        count = 1;
        display.clearDisplay();
        display.setCursor(12,0);
        display.println("Game Menu");
        display.setCursor(0,12);
        display.println(game1);
        display.setCursor(0,22);
        display.println(" ETCH-A-SKETCH");
        display.setCursor(0,32);
        display.println(" PONG");
        display.display();

        do
        {
          pressA = digitalRead(PIN_BUTTON_RIGHT);
          if (pressA == LOW)
          {
            return count;
          }
          //buttonY =  analogRead(A1);
          pressup = digitalRead(PIN_BUTTON_UP);
          pressdown = digitalRead(PIN_BUTTON_DOWN);
        } while ( pressdown != LOW || pressup != LOW);
      }
    }
  }
}

void Pong()
{
    // variables for the position of the ball and paddle
    display.setContrast(65);
    int pX = 10;
    int pY = 35;
    int oldPX, oldPY;
    int directionX = 1;
    int directionY = 1;
    int ballSpeed = 10; // lower numbers are faster
    int ballX =20;
    int ballY = 10; 
    int oldBallX =1;
    int oldBallY=1;
    int myWidth = 84;
    int myHeight = 48;
    int count=0;
    bool running = true;

    while(running)
    {
      int pressX = analogRead(A0);
      if(pressX>400)
      {
        pX+=2; //positon move the plus to corresponds to how fast the paddle moves
        if(pX>display.width()) //if reaching the edge of screen
        {
          pX=display.width();
        } 
      }
      else if(pressX<300)
      {
        pX-=2;
        if(pX<0)
        {
         pX=0;
        }
      }
   
      if (oldPX != pX) //if position has changed
      {
        display.drawLine(oldPX, oldPY, oldPX+10, oldPY, WHITE);  //erases old paddle
        display.display();
      } 
      display.drawLine(pX, pY, pX+10, pY, BLACK); //draws in new paddle
      display.display();
      oldPX = pX;
      oldPY = pY; 
      running = moveBall(directionX,directionY, ballX, ballY, oldBallX, oldBallY, pX,pY, count);
    }
    display.clearDisplay();
    display.display();
    display.setCursor(12,0);
    display.println("Game over!");
    display.setCursor(0,22);
    display.println("Your score is: ");
    display.setCursor(39,35);
    display.println(count);
    display.display();
    delay(4000);
    
}

bool moveBall(int& directionX,int& directionY, int& ballX,int& ballY, int& oldBallX, int& oldBallY, int& pX, int& pY, int& count) 
{
  
  if (ballY > display.height() )
  {
    return false;
  }
  if (ballY < 0)  //when wall that is not base wall is hit direction is reversed
  {
    directionY = -directionY ; 
  }

  if (ballX > display.width()) 
  {
    directionX = -directionX;
  }

  if(ballX < 0)
  {
    directionX = -directionX+1; //with a little more randomness and increases speed everytime this wall is hit
  }

  if (inPaddle(ballX, ballY, pX, pY, 10, 10,count)) //if paddle hits the ball
  {
    directionX = -directionX; //ball direction is reversed
    directionY = -directionY;
  }

  // update the ball's position
  ballX += directionX;
  ballY += directionY;

  
  display.fillRect(ballX, ballY, 2, 2, WHITE); // erase the ball's previous position
  display.display();
  if (oldBallX != ballX || oldBallY != ballY) 
  {
    display.fillRect(ballX, ballY, 2, 2, BLACK);
    display.display();
  }
  display.fillRect(ballX, ballY, 2, 2, WHITE);
  display.display();
  oldBallX = ballX; //assigns new to old
  oldBallY = ballY;
  return true; //game is still going
}
boolean inPaddle(int x, int y, int rectX, int rectY, int rectWidth, int rectHeight, int& count) 
{
  boolean result = false;
  if ((x >= rectX && x <= (rectX + rectWidth)) && (y >= rectY && y <= (rectY + rectHeight))) 
  {
    result = true;
    count++;
  }
  return result;
}

void Snake()
{   
     display.setContrast(65);
     byte RIGHT = 3;
     byte UP = 2;
     byte DOWN = 4;
     byte LEFT = 5;
    layout[0]=1;
    bodyX[0]=20;
    bodyY[0]=20;
    for(int i =1; i<size; i++)
    {
      layout[i]=0;
      bodyX[i]=0;
      bodyY[i]=0; 
    }
    int headxpos=20;
    int headypos=20;
    int foodx=0;
    int foody=0;
    int food = 0;
    int olddx;
    int olddy;
    bool running;
    running = true;
  
    generateFood(foodx,foody); //first draws food...function call
    while (running) 
    {
        int buttonY =  analogRead(A1); //read in values from joystick
        int buttonX =  analogRead(A0);
        if (buttonY <300 )
        {
            direction = 0; //each number corresponds in update
         }
        if (buttonX >400)
        {
          direction = 1;
        }
        if (buttonY> 400)
        {
          direction = 2;
         }
        if (buttonX <300)
        {
          direction = 3;  
        }
        update( headxpos, headypos, food, running, foodx, foody, olddx, olddy); //function call
        delay(80); //the greater the delay the slower the snake will move--can adjust this value for harder or easier game
       
       
    }

    display.clearDisplay(); //game is done
    display.display();
    display.setCursor(12,0);
    display.println("Game over!");
    display.setCursor(0,22);
    display.println("Your score is: ");
    display.setCursor(39,35);
    display.println(food);
    display.display();
    delay(4000);
}

// Updates the map
void update( int& headxpos, int& headypos, int& food, bool& running,  int& foodx, int& foody, int& olddx, int& olddy) 
{
    // each corresponding direction passes coordinates to move inorder to change the head of snake
    if(direction == 3)
    {
         move(-1, 0, headxpos, headypos, food, running,foodx,foody, olddx, olddy);
    }
    else if(direction==0)
    {
       move(0, 1,headxpos, headypos,food,running,foodx,foody, olddx, olddy);
    }
    else if(direction==1)
    {
      move(1, 0, headxpos, headypos,food,running,foodx,foody, olddx, olddy);
    }
    else if(direction==2)
    {
      move(0, -1,headxpos, headypos,food,running, foodx,foody, olddx, olddy);
    }
}
// Moves snake head to new location
void move(int dx, int dy, int& headxpos,int& headypos,  int& food,bool& running, int& foodX, int& foodY, int& olddx, int& olddy) 
{
    // determine new head position, according to passed coordinates and previous position
    int newx = headxpos + dx;
    int newy = headypos + dy;

    if (newy > display.height() ) //checks if wall has been hit, if so ends game.. can also comment out and just have it reverse directions
    {
      //newy= -newy;
      running=false;
      return;
    }
    if (newy < 0)  
    {
      running=false;
      return;
      //newy = -newy ; 
    }

    if (newx > display.width()) 
    {
      running=false;
      return;
      //newx= -newx;
    }

    if(newx < 0)
    {
      running=false;
      return;
      //newx = -newx; 
    }
    
    bodyX[0]=newx;
    bodyY[0]=newy;
    display.clearDisplay(); //clears screen briefly
    display.display();
    display.drawPixel(foodX, foodY, BLACK); //rewrites food
    display.drawPixel(headxpos, headypos, WHITE);
    display.drawPixel(bodyX[0], bodyY[0], BLACK); //writes in body
     
    display.display();
    for(int i = size-1; i>0; i--) //starts at back of snake
    {
      if(bodyX[i]!=0) //as long as there is a 1 in the spot
      {
        if(i==1) //if at first body segment
        {
          if(dx==-1 && dy==0) //checks the passed in coordinates to determine where the body should go inline with the snake
          {
            bodyX[i]=headxpos + dx -i;
            bodyY[i]=headypos + dy;
            display.drawPixel(bodyX[i], bodyY[i], BLACK);
            display.display();
          }
          else if(dx==0 && dy==1)
          {
            bodyX[i]=headxpos + dx;
            bodyY[i]=headypos + dy+i;
            display.drawPixel(bodyX[i], bodyY[i], BLACK);
            display.display();
          }
          else if(dx==1 && dy==0)
          {
            bodyX[i]=headxpos + dx +i;
            bodyY[i]=headypos + dy;
            display.drawPixel(bodyX[i], bodyY[i], BLACK);
            display.display();
          }
          if(dx==0 && dy==-1)
          {
            bodyX[i]=headxpos + dx ;
            bodyY[i]=headypos + dy-i;
            display.drawPixel(bodyX[i], bodyY[i], BLACK);
            display.display();
          }
        }
        else
        {
            bodyX[i]=bodyX[i-1]; //assigns current body segment to the position of the one before it
            bodyY[i]=bodyY[i-1];
            display.drawPixel(bodyX[i], bodyY[i], BLACK);
            display.display(); 
        } 
      }
    }

  /* This is for collison with the body....this feature is not yet working
    if(food>5)
    {
      for(int i = size-1; i>0; i--)
      {
        if(bodyX[i]!=0)
        {
          if(newx == bodyX[i])
          {
            if(newy == bodyY[i])
            {
                Serial.println(i);
                Serial.println("In ending loop");
                //running = false;
                //return;
            }
          }  
          break;
        }
      }
    }*/
    
    if(bodyX[0]==foodX) //if head hits the food
    {
      if(bodyY[0]==foodY)
      {
        display.drawPixel(foodY, foodX, WHITE); //erases the food
        display.display();
        food++; //increases the amount
        if(food+1==size) //at the end of the snake no more can be added to the array
        {
          running=false;
          display.clearDisplay();
          display.display();
          display.setCursor(12,0);
          display.println("You Win!");
          display.display();
          delay(4000);
          return;
        }
           layout[food]=1; //increases body
           bodyX[food]=headxpos + dx+1; //gives new positions 
           bodyY[food]=headypos + dy+1;
           generateFood(foodX,foodY); //function call to create another food
      }
    }
   
    // assigns the new to the old
    headxpos = newx;
    headypos = newy;
}
// Generates new food on map
void generateFood(int& foodx, int& foody) 
{
    
    foodx = random(80)+2; // Generate random x and y values within the map the plus two is so the values can't end up on the very top of the screen
    foody = random(42)+2;
    display.drawPixel(foodx, foody, BLACK); //draws food
    display.display();      
}


void TicTacToe()
{
  int buttonY;
  char ans;
  char player2;
  int x, y;
  bool respo=true; //for the do while loop for continue game play
  char b[3][3];
  for(int i =0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
        b[i][j] ='\n';  
    }  
  }
  int count = 1;
  display.clearDisplay();
  display.display();
  display.setCursor(0,0);
  display.println("Player 2:human or computer?");
  display.setCursor(0,22);
  display.println("> C");
  display.setCursor(0,32);
  display.println(" H");
  display.display();
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
         display.clearDisplay();
        display.setCursor(0,0);
        display.println("Player 2:human or computer?");
        display.setCursor(0,22);
        display.println("  C");
        display.setCursor(0,32);
        display.println("> H");
        display.display();
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
        display.clearDisplay();
        display.setCursor(0,0);
        display.println("Player 2:human or computer?");
        display.setCursor(0,22);
        display.println("> C");
        display.setCursor(0,32);
        display.println("  H");
        display.display();
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

  display.clearDisplay();
  if (player2 == 'H') // For two player humans
  {
    ans = EndGame(b);
    Printarray(b);
    while ( ans == 'c')
    {
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Player 1: ");
      display.display();
      HumanMoves(x, y, b);
      b[x][y]='X';
      Printarray(b);
      ans =EndGame(b);
      if (ans != 'c')
      {
        goto s;
      }
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Player 2: ");
      display.display();
      HumanMoves(x, y, b);
      b[x][y]='O';
      Printarray(b);
      ans = EndGame(b);
    }
s:
    if (ans == 't')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("It is a Tie!");
      display.display();
      delay(4000);
    }
    else if (ans == '1')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 1 Wins!");
      display.display();
      delay(4000);
    }
    else if (ans == '2')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 2 Wins!");
      display.display();
      delay(4000);
    }
  }

  if ( player2 == 'C') // For One human against computer
  {
    ans = EndGame(b);
    Printarray(b);

    while (ans == 'c')
    {
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Player 1: ");
      display.display();
      HumanMoves(x, y, b);
      b[x][y]='X';
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
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("It is a Tie!");
      display.display();
      delay(4000);
    }
    else if (ans == '1')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 1 Wins!");
      display.display();
      delay(4000);
    }
    else if (ans == '2')
    {
      display.clearDisplay();
      display.setCursor(0,32);
      display.println("Player 2 Wins!");
      display.display();
      delay(4000);
    }
  }
}

void Printarray( char b[3][3] )
{
  //Row 1
  display.setTextSize(0.1);
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("+---+---+---+");
  display.setCursor(0,10);
  display.println("| ");
  display.setCursor(10,8);
  display.println(b[0][0]);
  display.setCursor(24,10);
  display.println("| ");
  display.setCursor(36,8);
  display.println(b[0][1]);
  display.setCursor(48,10);
  display.println("| ");
  display.setCursor(60,8);
  display.println(b[0][2]);
  display.setCursor(72,10);
  display.println("| ");
  display.setCursor(0,14);
  display.println("+---+---+---+");

  //Row 2
  display.setCursor(0,22);
  display.println("| "); 
  display.setCursor(10,22);
  display.println(b[1][0]);
  display.setCursor(24,22);
  display.println("| ");
  display.setCursor(36,22);
  display.println(b[1][1]);
  display.setCursor(48,22);
  display.println("| ");
  display.setCursor(60,22);
  display.println(b[1][2]);
  display.setCursor(72,22);
  display.println("| ");
  display.setCursor(0,28);
  display.println("+---+---+---+");

  //Row 3
  display.setCursor(0,38);
  display.println("| ");
  display.setCursor(10,35);
  display.println(b[2][0]);
  display.setCursor(24,38);
  display.println("| ");
  display.setCursor(36,35);
  display.println(b[2][1]);
  display.setCursor(48,38);
  display.println("| ");
  display.setCursor(60,35);
  display.println(b[2][2]);
  display.setCursor(72,38);
  display.println("| ");
  display.setCursor(0,40);
  display.println("+---+---+---+"); 
  display.display();
  delay(3000);
}

void HumanMoves( int& x, int& y, char b[][3] )
{
  int count = 1;
  int pressA;
  int pressB;
  int buttonY;

  display.setCursor(0,15);
  display.println("Row: 1 ");
  display.setCursor(0,25);
  display.println("Column: 1 ");
  display.display();
  do
  {
    for (int i = 0; ; i++)
    {
      pressA = digitalRead(PIN_BUTTON_RIGHT);
      if (pressA == LOW)
      {
        x = 1;
        goto end;
      }
      buttonY =  analogRead(A1);
      if (buttonY < 300)
      {
        if (count == 1)
        {
          count = 2;
          display.setTextColor(WHITE);
          display.setCursor(0,15);
          display.println("Row: 1 ");
          display.setTextColor(BLACK);
          display.setCursor(0,15);
          display.println("Row: 2 ");
          display.display();
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
          display.setTextColor(WHITE);
          display.setCursor(0,15);
          display.println("Row: 2 ");
          display.setTextColor(BLACK);
          display.setCursor(0,15);
          display.println("Row: 3 ");
          display.display();
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
          display.setTextColor(WHITE);
          display.setCursor(0,15);
          display.println("Row: 3 ");
          display.setTextColor(BLACK);
          display.setCursor(0,15);
          display.println("Row: 1 ");
          display.display();
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
          display.setTextColor(WHITE);
          display.setCursor(0,25);
          display.println("Column: 1 ");
          display.setTextColor(BLACK);
          display.setCursor(0,25);
          display.println("Column: 2 ");
          display.display();
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
          display.setTextColor(WHITE);
          display.setCursor(0,25);
          display.println("Column: 2 ");
          display.setTextColor(BLACK);
          display.setCursor(0,25);
          display.println("Column: 3 ");
          display.display();
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
          display.setTextColor(WHITE);
          display.setCursor(0,25);
          display.println("Column: 3 ");
          display.setTextColor(BLACK);
          display.setCursor(0,25);
          display.println("Column: 1 ");
          display.display();
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

  } while ((b[x][y] == 'X') || (b[x][y] == 'O')) ; 
  
}

void RandomMoves( char board[][3] )
{
  int x = random(3); //Finds first random values of x and y between 1 and 3
  int y = random(3);
  
  while ((board[x][y] == 'X') || ( board[x][y] == 'O')) // If there is already a letter there it will enter loop
  {
    
    x = random(3); //It will keep looping until a new place is found without a letter
    y = random(3);
  }
   board[x][y]='O';
}
char EndGame(char b[][3]) // returns a t for tie, c for continue, 1 for player 1 won, 2 for player two won
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
      if( b[i][j] == '\n')//sets array to 0
      {
        tieTest = false;
      }
    }
  }
  
  //All of the following statements check to see if the various ways to win have happened
  
  if(b[0][0]=='X'&&b[0][1]=='X'&&b[0][2]=='X')
  {
    return p1w;
  }
  else if(b[0][0]=='O'&&b[0][1]=='O'&&b[0][2]=='O')
  {
    return p2w;
  }
  else if(b[1][0]=='X'&&b[1][1]=='X'&&b[1][2]=='X')
  {
    return p1w;
  }
  else if(b[1][0]=='O'&&b[1][1]=='O'&&b[1][2]=='O')
  {
    return p2w;
  }
  else if(b[2][0]=='X'&&b[2][1]=='X'&&b[2][2]=='X')
  {
    return p1w;
  }
  else if (b[2][0]=='O'&&b[2][1]=='O'&&b[2][2]=='O')
  {
    return p2w;
  }
  else if (b[0][0]=='X'&&b[1][0]=='X'&&b[2][0]=='X')
  {
    return p1w;
  }
  else if(b[0][0]=='O'&&b[1][0]=='O'&&b[2][0]=='O')
  {
    return p2w;
  }
  else if(b[0][1]=='X'&&b[1][1]=='X'&&b[2][1]=='X')
  {
    return p1w;
  }
  else if(b[0][1]=='O'&&b[1][1]=='O'&&b[2][1]=='O')
  {
    return p2w;
  }
  else if(b[0][2]=='X'&&b[1][2]=='X'&&b[2][2]=='X')
  {
    return p1w;
  }
  else if(b[0][2]=='O'&&b[1][2]=='O'&&b[2][2]=='O')
  {
    return p2w;
  }
  else if(b[0][0]=='X'&&b[1][1]=='X'&&b[2][2]=='X')
  {
    return p1w;
  }
  else if(b[0][0]=='O'&&b[1][1]=='O'&&b[2][2]=='O')
  {
    return p2w;
  }
  else if(b[0][2]=='X'&&b[1][1]=='X'&&b[2][0]=='X')
  {
    return p1w;
  }
  else if(b[0][2]=='O'&&b[1][1]=='O'&&b[2][0]=='O')
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

void EtchASketch()
{  
  int pointX=30;
  int pointY=30; 
  int oldpointx=30;
  int oldpointy=30;
  int pressup;
  int pressdown;
  pressup = digitalRead(PIN_BUTTON_UP);
  pressdown = digitalRead(PIN_BUTTON_DOWN);
  while ( pressdown != LOW || pressup != LOW) //loops until button is pressed
  {
      int buttonY = analogRead(1);
      int buttonX = analogRead(0); // reads the joystick values
      delay(50);
        if (buttonY <300 )
        {
            pointY++;
        }
        if (buttonX >400)
        {
          pointX++;
        }
        if (buttonY> 400)
        {
          pointY--;
         }
        if (buttonX <300)
        {
          pointX--;  
        }
        
        if (pointY > display.height() ) //checks if screen edge has been reached does not let it go further
        {
            pointY= display.height()-2;
        }
        if (pointY < 0)  
        {
          pointY = 2; 
        }
        if (pointX > display.width()) 
        {
            pointX = display.width()-2;
        }
        if(pointX < 0)
        {
          pointX = 2; 
        }
      if(oldpointx!=pointX || oldpointy != pointY) //if position has changed
      {
        
          display.drawPixel(pointX, pointY, BLACK);//draws in new pixel
          display.display();
        
      }
      if (digitalRead(PIN_BUTTON_RIGHT) == LOW) //clears the screen if button pressed
      {
        display.clearDisplay();
        display.display();
       }
       oldpointx=pointX;
       oldpointy=pointY;
       pressup = digitalRead(PIN_BUTTON_UP);
       pressdown = digitalRead(PIN_BUTTON_DOWN);
  }
}
