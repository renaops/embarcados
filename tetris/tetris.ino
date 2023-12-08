#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIDTH 64
#define HEIGHT 128

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const char pieces_S_l[2][2][4] = {{{0, 0, 1, 1}, {0, 1, 1, 2}}, {{0, 1, 1, 2}, {1, 1, 0, 0}}};
const char pieces_S_r[2][2][4]{{{1, 1, 0, 0}, {0, 1, 1, 2}}, {{0, 1, 1, 2}, {0, 0, 1, 1}}};     
const char pieces_L_l[4][2][4] = {{{0, 0, 0, 1}, {0, 1, 2, 2}},{{0, 1, 2, 2}, {1, 1, 1, 0}},{{0, 1, 1, 1}, {0, 0, 1, 2}},{{0, 0, 1, 2}, {1, 0, 0, 0}}};
const char pieces_Sq[1][2][4] = {{{0, 1, 0, 1}, {0, 0, 1, 1}}};
const char pieces_T[4][2][4] = {{{0, 0, 1, 0},{0, 1, 1, 2}},{{0, 1, 1, 2},{1, 0, 1, 1}},{{1, 0, 1, 1},{0, 1, 1, 2}},{{0, 1, 1, 2},{0, 0, 1, 0}}};
const char pieces_l[2][2][4] = {{{0, 1, 2, 3}, {0, 0, 0, 0}},{{0, 0, 0, 0}, {0, 1, 2, 3}}};

const short MARGIN_TOP = 19;
const short MARGIN_LEFT = 3;
const short SIZE = 5;
const short TYPES = 6;

word currentType, nextType, rotation;
short pieceX, pieceY;
short piece[2][4];

int interval = 500, score;
long timer, delayer;

boolean grid[10][18];
boolean b1, b2, b3;

const uint8_t PROGMEM a_btn{2};
const uint8_t PROGMEM c_btn{4};
const uint8_t PROGMEM d_btn{5};
const uint8_t PROGMEM b_btn{3};
const uint8_t PROGMEM e_btn{6};
const uint8_t PROGMEM f_btn{7};
const uint8_t PROGMEM k_btn{8};
const uint8_t PROGMEM x_joystick = A0;
const uint8_t PROGMEM y_joystick = A1;

boolean prev_a_btn = false;
boolean prev_c_btn = false;
boolean prev_d_btn = false;
boolean prev_b_btn = false;
boolean prev_e_btn = false;
boolean prev_f_btn = false;
boolean prev_k_btn = false;

const int PROGMEM cir_x{25};
const int PROGMEM cir_y{32};
const int PROGMEM cir_r{13};

void btn_cb(bool new_val, bool &old_val)
{
  if (new_val == old_val)
    return;
  old_val = new_val;
}

void setup() {

  pinMode(a_btn, INPUT);
  pinMode(c_btn, INPUT);
  pinMode(d_btn, INPUT);
  pinMode(b_btn, INPUT);
  pinMode(e_btn, INPUT);
  pinMode(f_btn, INPUT);
  pinMode(k_btn, INPUT);
  
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.setRotation(1);
  display.clearDisplay();
  drawLayout();
  display.display();
  randomSeed(analogRead(0));
  nextType = random(TYPES);
  generate();
  
  timer = millis();
}

void loop() {
  btn_cb(digitalRead(a_btn) == LOW, prev_a_btn); 
  btn_cb(digitalRead(b_btn) == LOW, prev_b_btn);
  btn_cb(digitalRead(c_btn) == LOW, prev_c_btn);
  btn_cb(digitalRead(d_btn) == LOW, prev_d_btn);
  btn_cb(digitalRead(e_btn) == LOW, prev_e_btn);
  btn_cb(digitalRead(f_btn) == LOW, prev_f_btn);

  int new_x_joystick = map(analogRead(x_joystick), 0, 1000, -1 * cir_r, cir_r);
  int new_y_joystick = map(analogRead(y_joystick), 0, 1000, -1 * cir_r, cir_r);

  if(millis() - timer > interval){
    checkLines();
    refresh();
    
    if(nextCollision()){
      for(short i = 0; i < 4; i++)
        grid[pieceX + piece[0][i]][pieceY + piece[1][i]] = 1;
      generate();
    }else
      pieceY++;
      
    timer = millis();
  }

  // Esquerda
  if(prev_d_btn || new_x_joystick < -10){
    if(b1){
      if(!nextHorizontalCollision(piece, -1)){
        pieceX--;
        refresh();
      }
      b1 = false;
    }
  }else{ 
    b1 = true;
  }

  // Direita
  if(prev_b_btn || new_x_joystick > 10){
    if(b2){
      if(!nextHorizontalCollision(piece, 1)){
        pieceX++;
        refresh();
      }
      b2 = false;
    }
  }else{ 
    b2 = true;
  }

  // Descer peça com velocidade
  if(prev_c_btn || new_y_joystick < -10){
    interval = 20;
  }else{
    interval = 400;
  }

  // Rodar peça
  if(prev_a_btn || new_y_joystick > 10){
    if(b3){
      if(rotation == getMaxRotation(currentType) - 1 && canRotate(0)){
        rotation = 0;
      }else if(canRotate(rotation + 1)){
        rotation++;
      }
        
      copyPiece(piece, currentType, rotation);
      refresh();
      
      b3 = false;
      delayer = millis();
    }
  } else if(millis() - delayer > 50){ 
    b3 = true;
  }
}

void checkLines(){
  boolean full;
  for(short y = 17; y >= 0; y--){
    full = true;
    for(short x = 0; x < 10; x++){
      full = full && grid[x][y];
    }
    if(full){
      breakLine(y);
      y++;
    }
  }
}

void breakLine(short line){
  for(short y = line; y >= 0; y--){
    for(short x = 0; x < 10; x++){
      grid[x][y] = grid[x][y-1];
    }
  }
  for(short x = 0; x < 10; x++){
     grid[x][0] = 0;
  }
  display.invertDisplay(true);
  delay(50);
  display.invertDisplay(false);
  score += 10;
}

void refresh(){
    display.clearDisplay();
    drawLayout();
    drawGrid();
    drawPiece(currentType, 0, pieceX, pieceY);
    display.display();
}

void drawGrid(){
  for(short x = 0; x < 10; x++)
    for(short y = 0; y < 18; y++)
      if(grid[x][y])
        display.fillRect(MARGIN_LEFT + (SIZE + 1)*x, MARGIN_TOP + (SIZE + 1)*y, SIZE, SIZE, WHITE);
}

boolean nextHorizontalCollision(short piece[2][4], int amount){
  for(short i = 0; i < 4; i++){
    short newX = pieceX + piece[0][i] + amount;
    if(newX > 9 || newX < 0 || grid[newX][pieceY + piece[1][i]])
      return true;
  }
  return false;
}

boolean nextCollision(){

  for(short i = 0; i < 4; i++){
    short y = pieceY + piece[1][i] + 1;
    short x = pieceX + piece[0][i];
    if(y > 17 || grid[x][y])
      return true;
  }

  return false;
}

void generate(){
  currentType = nextType;
  nextType = random(TYPES);
  if(currentType != 5)
    pieceX = random(9);
  else
    pieceX = random(7);
  pieceY = 0;
  rotation = 0;
  copyPiece(piece, currentType, rotation);
}

void drawPiece(short type, short rotation, short x, short y){
  for(short i = 0; i < 4; i++)
    display.fillRect(MARGIN_LEFT + (SIZE + 1)*(x + piece[0][i]), MARGIN_TOP + (SIZE + 1)*(y + piece[1][i]), SIZE, SIZE, WHITE);
}

void drawNextPiece(){
  short nPiece[2][4];
  copyPiece(nPiece, nextType, 0);
  for(short i = 0; i < 4; i++)
    display.fillRect(50 + 3*nPiece[0][i], 4 + 3*nPiece[1][i], 2, 2, WHITE);
}

void copyPiece(short piece[2][4], short type, short rotation){
  switch(type){
  case 0: //L_l
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_L_l[rotation][0][i];
      piece[1][i] = pieces_L_l[rotation][1][i];
    }
    break;
   case 1: //S_l
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_S_l[rotation][0][i];
      piece[1][i] = pieces_S_l[rotation][1][i];
    }
    break;
   case 2: //S_r
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_S_r[rotation][0][i];
      piece[1][i] = pieces_S_r[rotation][1][i];
    }
    break;
   case 3: //Sq
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_Sq[0][0][i];
      piece[1][i] = pieces_Sq[0][1][i];
    }
    break;
    case 4: //T
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_T[rotation][0][i];
      piece[1][i] = pieces_T[rotation][1][i];
    }
    break;
    case 5: //l
    for(short i = 0; i < 4; i++){
      piece[0][i] = pieces_l[rotation][0][i];
      piece[1][i] = pieces_l[rotation][1][i];
    }
    break;
  }
}

short getMaxRotation(short type){
  if(type == 1 || type == 2 || type == 5)
    return 2;
  else if(type == 0 || type == 4)
    return 4;
  else if(type == 3)
    return 1;
  else 
    return 0;
}

boolean canRotate(short rotation){
  short piece[2][4];
  copyPiece(piece, currentType, rotation);
  return !nextHorizontalCollision(piece, 0);
}

void drawLayout(){
  display.drawLine(0, 15, WIDTH, 15, WHITE);
  display.drawRect(0, 0, WIDTH, HEIGHT, WHITE);
  drawNextPiece();
  char text[6];
  itoa(score, text, 10);
  drawText(text, getNumberLength(score), 7, 4);
}

short getNumberLength(int n){
  short counter = 1;
  while(n >= 10){
    n /= 10;
    counter++;
  }
  return counter;
}

void drawText(char text[], short length, int x, int y){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(x, y);
  display.cp437(true);

  for(short i = 0; i < length; i++)
    display.write(text[i]);
}