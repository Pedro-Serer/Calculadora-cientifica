/**
  Calculadora científica
 
  @author 
  	Pedro Serer <pedrotiserer@hotmail.com>
  	Gustavo Cazoni gucazoni147@gmail.com
  
  @version 0.0.2
*/


#include <LiquidCrystal.h>
#include <Keypad.h>
#include <stdlib.h>

/*Configuração dos pinos do display*/
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

void operacao(char left[], char right[], char flop);
void display(int valores_na_tela, char seq[]);

const byte Lines = 4;                      
const byte Coluns = 4;                          

int qtd = 0, qtd1 = 0;
bool flag = false;

char operadores[] = {'+', '-', 'x', '/'};
char seq[14], left[14], right[14];                
char key, flop = '\0';                            

char Teclado [Lines][Coluns] = {
  {'1', '2', '3', '/'},
  {'4', '5', '6', 'x'},
  {'7', '8', '9', '-'},
  {'.', '0', '=', '+'}
};

/*Configuração dos pinos do teclado*/
byte pinosLinhas[Lines] = {9, 8, 7, 6};        
byte pinosColunas[Coluns] = {5, 4, 3, 2};

/*Objeto do teclado*/
Keypad keyp = Keypad(makeKeymap(Teclado), pinosLinhas, pinosColunas, Lines, Coluns); 

void setup()
{
  lcd.begin(16, 2);
} 

void loop()
{ 
  key = keyp.getKey();
  delay(50);

  if (key) {
    seq[qtd] = (char) key;               	  // Array Push
    
    for (int i = 0; i < 4; i++) {     
      if (key == operadores[i]) {
      	flop = operadores[i];
      }
    }
    
    if ((key != flop) && (flag == false)) {
        left[qtd] = key;
    } else {
      	flag = true;
		right[qtd1] = key;
        qtd1 += 1;
    }
    
    if (key == '=') {
    	operacao(left, right, flop);
    }
    
    qtd += 1;
    Display(qtd, seq);        
  }
}

void Display(int valores_na_tela, char seq[])
{
  lcd.setCursor((15 - valores_na_tela), 0);

  for (int i = 0; i < valores_na_tela; i++) {     
    lcd.print(seq[i]);
  }
}

void operacao(char left[], char right[], char flop){
  lcd.setCursor(13, 1);
  right[0] = '+';								           //coloca o array como positivo
  
  switch (flop) {
  	case '+':
    	lcd.print(atoi(left) + atoi(right));
    	break;
  	case '-':
    	lcd.print(atoi(left) - atoi(right));
    	break;
  	case 'x':
    	lcd.print(atoi(left) * atoi(right));
    	break;
  	case '/':
    	lcd.print(atoi(left) / atoi(right));
    	break;
  }
}
