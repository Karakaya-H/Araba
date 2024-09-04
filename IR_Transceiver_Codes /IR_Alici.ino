#include <IRremote.h>

int ir_alici_pin=2;
IRrecv ir_alicim(ir_alici_pin); 

decode_results results;   

void setup() {
  
  Serial.begin(9600);
  Serial.println("IR alıcı etkinleştiriliyor...");
  ir_alicim.enableIRIn();
  Serial.println("IR alıcı etkinleştirildi."); 
}

void loop() {
  
  if(ir_alicim.decode(&results))    
  {
    Serial.println(results.value,DEC);
    ir_alicim.resume(); 
    }
   delay(100);
}
