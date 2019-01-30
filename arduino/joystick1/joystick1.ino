const int xIn = A1; //порт к которому подключен VRx
const int yIn = A0; //порт к которому подключен VRy
const int critL = 300; //от 0 до 400
const int critR = 700; //от 600 до 1000
const int critU = 250; //от 600 до 1000
const int critD = 750; //от 0 до 400

void setup() 
{
  Serial.begin(9600);
}

int prev = '0'; //предыдущее состояние джойстика

void loop() 
{
  int xVal, yVal;
  xVal = analogRead(xIn); //считывается x
  yVal = analogRead(yIn); //считывается y
  int test = (xVal >= critR) + (xVal <= critL) + (yVal <= critU) + (yVal >= critD); //количество критических состояний, которому удовлетворяет джойстик
  
  if (test >= 2) //если больше или равно 2, то это диагональ - не обрабатываем
    return;
  else if (test == 0) //если 0, то джойстик в исходном положении
  {
    prev = '0';
    return;
  }
  
  //блок проверок на соответствие критическому состоянию и отсутствия данного критического состояния до этого: чтобы выводить в Serial только при принципиальном изменении
  if (xVal >= critR && prev != 'r') 
  {
    prev = 'r';
    Serial.println('r');
    return;
  }
  
  if (xVal <= critL && prev != 'l')
  {
    prev = 'l';
    Serial.println('l');
    return;
  }
  
  if (yVal >= critD && prev != 'd')
  {
    prev = 'd';
    Serial.println('d');
    return;
  }
  
  if (yVal <= critU && prev != 'u')
  {
    prev = 'u';
    Serial.println('u');
    return;
  }
}
