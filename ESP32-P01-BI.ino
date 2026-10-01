#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
Adafruit_SH1106G display(128,64,&Wire,-1);
#define BUTTON_PIN 5
#define LED_PIN 18
const int laneX[3]={30,64,98};
int playerLane=1;
float playerX=64;
float targetPlayerX=64;
int obstacleLane=1;
float obstacleY=-18;
float obstacleSpeed=1.4;
int roadOffset=0;
int score=0;
bool gameRunning=false;
bool gameOver=false;
bool oldButton=HIGH;
unsigned long lastButtonTime=0;
bool laneBlink=false;
bool crashBlink=false;
unsigned long laneBlinkStart=0;
unsigned long crashBlinkTime=0;
bool crashLedState=true;
unsigned long lastFrame=0;

bool buttonPressed(){
  bool current=digitalRead(BUTTON_PIN);
  if(oldButton==HIGH&&current==LOW){
    if(millis()-lastButtonTime>160){
      lastButtonTime=millis();
      oldButton=LOW;
      return true;
    }
  }
  if(current==HIGH)oldButton=HIGH;
  return false;
}

void updateLED(){
  if(crashBlink){
    if(millis()-crashBlinkTime>=250){
      crashBlinkTime=millis();
      crashLedState=!crashLedState;
      digitalWrite(LED_PIN,crashLedState);
    }
    return;
  }
  if(laneBlink){
    if(millis()-laneBlinkStart>=120){
      laneBlink=false;
      digitalWrite(LED_PIN,HIGH);
    }
    return;
  }
  digitalWrite(LED_PIN,HIGH);
}

void drawStartScreen(){
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(2);
  display.setCursor(18,5);
  display.println("ROAD");
  display.setCursor(18,26);
  display.println("RUSH");
  display.fillRect(86,34,25,9,SH110X_WHITE);
  display.fillRect(91,30,15,5,SH110X_WHITE);
  display.fillRect(94,31,5,3,SH110X_BLACK);
  display.fillRect(101,31,5,3,SH110X_BLACK);
  display.fillCircle(91,44,3,SH110X_BLACK);
  display.fillCircle(106,44,3,SH110X_BLACK);
  display.setTextSize(1);
  display.setCursor(20,50);
  display.println("PRESS TO START");
  display.display();
}

void drawGameOver(){
  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
  display.setTextSize(2);
  display.setCursor(12,8);
  display.println("CRASHED!");
  display.setTextSize(1);
  display.setCursor(40,32);
  display.print("SCORE: ");
  display.println(score);
  display.setCursor(16,49);
  display.println("PRESS TO RESTART");
  display.display();
}

void drawRoad(){
  display.drawLine(8,0,8,63,SH110X_WHITE);
  display.drawLine(119,0,119,63,SH110X_WHITE);
  for(int y=-12;y<64;y+=12){
    int yy=y+roadOffset;
    if(yy>=10&&yy<64){
      display.fillRect(47,yy,3,6,SH110X_WHITE);
      display.fillRect(78,yy,3,6,SH110X_WHITE);
    }
  }
  for(int y=-18;y<64;y+=18){
    int yy=y+((roadOffset*2)%18);
    if(yy>=10&&yy<64){
      display.fillRect(12,yy,3,5,SH110X_WHITE);
      display.fillRect(113,yy,3,5,SH110X_WHITE);
    }
  }
}

void drawPlayerCar(){
  int x=(int)playerX;
  int bounce=(millis()/120)%2;
  int y=49+bounce;
  display.fillRect(x-9,y-2,18,2,SH110X_WHITE);
  display.fillRect(x-6,y,12,5,SH110X_WHITE);
  display.fillRect(x-10,y+4,20,9,SH110X_WHITE);
  display.fillRect(x-4,y+1,8,3,SH110X_BLACK);
  display.fillRect(x-8,y+6,3,2,SH110X_BLACK);
  display.fillRect(x+5,y+6,3,2,SH110X_BLACK);
  display.fillCircle(x-7,y+13,3,SH110X_BLACK);
  display.fillCircle(x+7,y+13,3,SH110X_BLACK);
  if((millis()/100)%2==0){
    display.drawPixel(x-7,y+13,SH110X_WHITE);
    display.drawPixel(x+7,y+13,SH110X_WHITE);
  }
  if((millis()/100)%2==0){
    display.drawLine(x-3,y+13,x-3,y+17,SH110X_WHITE);
    display.drawLine(x+3,y+13,x+3,y+17,SH110X_WHITE);
  }
}

void drawEnemyCar(){
  int x=laneX[obstacleLane];
  int y=(int)obstacleY;
  display.fillRect(x-9,y+4,18,10,SH110X_WHITE);
  display.fillRect(x-6,y,12,6,SH110X_WHITE);
  display.fillRect(x-4,y+1,3,3,SH110X_BLACK);
  display.fillRect(x+1,y+1,3,3,SH110X_BLACK);
  display.fillRect(x-7,y+7,3,2,SH110X_BLACK);
  display.fillRect(x+4,y+7,3,2,SH110X_BLACK);
  display.fillCircle(x-7,y+14,3,SH110X_BLACK);
  display.fillCircle(x+7,y+14,3,SH110X_BLACK);
}

void drawGame(){
  display.clearDisplay();
  drawRoad();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(2,1);
  display.print("S:");
  display.print(score);
  display.setCursor(91,1);
  display.print("SPD:");
  display.print((int)obstacleSpeed);
  drawEnemyCar();
  drawPlayerCar();
  display.display();
}

void startGame(){
  playerLane=1;
  playerX=laneX[playerLane];
  targetPlayerX=playerX;
  obstacleLane=random(0,3);
  obstacleY=-18;
  score=0;
  obstacleSpeed=1.4;
  roadOffset=0;
  gameRunning=true;
  gameOver=false;
  laneBlink=false;
  crashBlink=false;
  crashLedState=true;
  digitalWrite(LED_PIN,HIGH);
  lastFrame=millis();
}

bool checkCollision(){
  int carY=49;
  int playerLeft=(int)playerX-8;
  int playerRight=(int)playerX+8;
  int playerTop=carY;
  int playerBottom=carY+14;
  int enemyX=laneX[obstacleLane];
  int enemyLeft=enemyX-8;
  int enemyRight=enemyX+8;
  int enemyTop=(int)obstacleY;
  int enemyBottom=(int)obstacleY+14;
  if(playerRight>=enemyLeft&&playerLeft<=enemyRight){
    if(playerBottom>=enemyTop&&playerTop<=enemyBottom)return true;
  }
  return false;
}

void setup(){
  pinMode(BUTTON_PIN,INPUT_PULLUP);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH);
  Wire.begin(21,22);
  if(!display.begin(0x3C,true)){
    while(true){}
  }
  randomSeed(micros());
  drawStartScreen();
}

void loop(){
  updateLED();

  if(!gameRunning&&!gameOver){
    if(buttonPressed())startGame();
    delay(5);
    return;
  }

  if(gameOver){
    if(buttonPressed())startGame();
    delay(5);
    return;
  }

  if(buttonPressed()){
    playerLane++;
    if(playerLane>2)playerLane=0;
    targetPlayerX=laneX[playerLane];
    laneBlink=true;
    laneBlinkStart=millis();
    digitalWrite(LED_PIN,LOW);
  }

  if(millis()-lastFrame>=25){
    lastFrame=millis();

    float difference=targetPlayerX-playerX;
    playerX+=difference*0.25;

    roadOffset+=(int)(obstacleSpeed*2);
    if(roadOffset>=12)roadOffset-=12;

    obstacleY+=obstacleSpeed;

    if(obstacleY>64){
      score++;
      obstacleSpeed+=0.08;
      if(obstacleSpeed>3.5)obstacleSpeed=3.5;
      obstacleY=-18;
      obstacleLane=random(0,3);
    }

    if(checkCollision()){
      gameRunning=false;
      gameOver=true;
      crashBlink=true;
      crashBlinkTime=millis();
      crashLedState=true;
      digitalWrite(LED_PIN,HIGH);
      drawGameOver();
      return;
    }

    drawGame();
  }
}