

const int Vm = 0;
const int Vd = 1;
const int Am = 2;

const int TLC = 0;
const int TLP = 1;

const int TLC1 = 0;
const int TLC2 = 1;

const int TLP1 = 0;
const int TLP2 = 1;
const int TLP34 = 2;

const int TIME_MULT = 1;


// TLC1 {Vermelho, Verde, Amarelo } TLC2 {Vermelho, Verde, Amarelo} NADA {}
int TL [2][3][3] = {{{2,3,4},{5,6,7},{-1,-1,-1}},
// TLP1 {Vermelho, Verde, ---} TLP2 {Vermelho, Verde, ---} TLP3/TLP4 {Vermelho, Verde, ---}
                    {{8,9,-1},{10,11,-1},{12,13,-1}}};

// Botão pedestre
int btn [] = {1};

int aptbtn = 0;
int state = 0;
int nextState = 0;
// SETUP


long int tempoInicio = 0;
long int tempoDeEspera = 0;
void setup() {
  // Configura todos os pinos 
  for( int j = 0; j < 2; j++){ 
    for (int x = 0; x < 3; x++){
      for (int y = 0; y < 3; y++){
        // -1 é utiliazado para indicar campos do array onde não existe nenhum led
        if(TL[j][x][y] != -1){
          pinMode(TL[j][x][y], OUTPUT);
          if ( y == Vm ){
            //Começa com vermelho ligado em tudo
            digitalWrite(TL[j][x][y], HIGH);
          }else{
            digitalWrite(TL[j][x][y], LOW);
          }
          
        }
      }
    }
  }
  //configura botão de saída
  pinMode(btn[0], INPUT);
}

void reset(){
  // Configura todos os pinos 
  for( int j = 0; j < 2; j++){ 
    for (int x = 0; x < 3; x++){
      for (int y = 0; y < 3; y++){
        // -1 é utiliazado para indicar campos do array onde não existe nenhum led
        if(TL[j][x][y] != -1){
          if ( y == Vm ){
            //Começa com vermelho ligado em tudo
            digitalWrite(TL[j][x][y], HIGH);
          }else{
            digitalWrite(TL[j][x][y], LOW);
          }
        }
      }
    }
  }
}
// RUN
void loop() {
  // Update Time
  long int now = millis();
  
  int btnval = digitalRead(btn[0]);
  
  // Alguém apertou o botão de pedestre
  if (btnval == HIGH){
      aptbtn= true; 
  }

  if (now - tempoInicio < tempoDeEspera){
      return;
  }
  state = nextState;
  // Get into it
  
  tempoInicio = millis();
  switch (state){
    case 0:
      reset();
      tempoDeEspera = 4500*TIME_MULT;
      setLight(TLC, TLC1, Vd);
      setLight(TLP, TLP2, Vd);
      nextState = 1;
      break;
    case 1:
      tempoDeEspera = 1500*TIME_MULT;
      setLight(TLC, TLC1, Am);
      nextState = 2;
      break;
    case 2:
      tempoDeEspera = 4500*TIME_MULT;
      setLight(TLC, TLC1, Vm);
      setLight(TLC, TLC2, Vd);
      setLight(TLP, TLP1, Vd);
      setLight(TLP, TLP2, Vm);
      nextState = 3;
      break;
    case 3:
      tempoDeEspera = 1500*TIME_MULT;
      setLight(TLC, TLC2, Am);
      if (aptbtn)
        nextState = 4;
      else
        nextState = 0;
      break;
    case 4:
      tempoDeEspera = 1500*TIME_MULT;
      setLight(TLC, TLC2, Vm);
      setLight(TLP, TLP1, Vd);
      setLight(TLP, TLP2, Vd);
      setLight(TLP, TLP34, Vd);
      nextState = 0;
      aptbtn = 0;
      break;
  }
}


void setLight(int tl, int light, int cor){
  if( TL[tl][light][cor] == -1){
    return;
  }
  for (int x = 0; x < 3 ; x++){
    if( TL[tl][light][x] != -1){
      if ( cor == x ){
        digitalWrite(TL[tl][light][x], HIGH);
      }else{
        digitalWrite(TL[tl][light][x], LOW);
      }
    }
  }
}


