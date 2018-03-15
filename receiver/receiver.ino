#include <IRremote.h>  

int input = 8;
int RECV_PIN = 12;  

uint32_t vol_up_code = 3777255591;
uint32_t vol_down_code= 3777273951;

IRrecv irrecv(RECV_PIN);  
decode_results results; 

void setup()  
{   
  Serial.begin(9600);
  irrecv.enableIRIn(); // Inicializa o receptor IR
  pinMode(input, OUTPUT);
}  
   
void loop()  
{ 
  if (irrecv.decode(&results))  
  { 
    if(results.value == vol_up_code){
      Serial.print(1);
    }
    else if(results.value == vol_down_code){
      Serial.print(2);
    }
    digitalWrite(input, LOW);
    delay(100);
    irrecv.resume(); //Le o próximo valor  
  }
  else{
    digitalWrite(input, HIGH);
    Serial.print(0);
  }
}

