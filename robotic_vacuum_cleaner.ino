#include <LiquidCrystal.h>
#include<QMC5883.h>
LiquidCrystal lcd(8, 9, 10, 4, 5, 6, 7);

  // Motor A connections
  int enR = 12,in1 = 24,in2 = 26;
  // Motor B connections
  int enL = 13,in3 = 22,in4 = 28;
  //touchsensors
  int touchforward1=2,touchforward2=3,touchright=18,touchleft=19;
  int j=1;
  float deg;
  const unsigned char tr=50;
  unsigned char speed = 0;
  unsigned long lastDebounceTime=0,debounceDelay=50,currentTime,turndelaytime,lasttime;
  char str[20];
  int calib_point[5],deg2,i=0,beriz[5]; 
  unsigned char sorayya=0;
  QMC5883 GY271;

  void setup(){
  config();

  lcd.setCursor(0, 0);
  lcd.print("zakiyeh");
  lcd.setCursor(0, 1);
  lcd.print("naghizadeh 1.2");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("callibration...");
}
  void loop(){ 
  deg=getdeg();
  Serial.println(deg);
      
      lcd.clear();
      lcd.setCursor(7,1);
      GY271.calculate();
      lcd.print(GY271.getHeadingDegree('z'));
    
  if(i>4){   //khesht avval
    if(sorayya==0)
    { 
      lcd.clear();
      lcd.print("velam kon");
      delay(5000);
      detection();
      
      /////////////////////////////////////////////////
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("turndelaytime=");
      lcd.setCursor(0,1);
      sprintf(str,"%d ms",turndelaytime);
      lcd.print(str);
      delay(2000);
      ////////////////////////////////////////////////
      sorayya=1;

      turnright();
    } 
     Serial.println(deg);
   
    beriz[1]=calib_point[1];
    beriz[2]=calib_point[2];
    beriz[3]=calib_point[3];
    beriz[4]=calib_point[4];
   
  
    
   if(((360>=beriz[1] && 350 < beriz[1]) || (10>=beriz[1] && 0 < beriz[1])) || ((360>=beriz[3] && 350 < beriz[3]) || (10>=beriz[3] && 0 < beriz[3])) ){
   
    turnright();
    calib_point[3]=beriz[4];
    calib_point[4]=beriz[1];
    calib_point[1]=beriz[2];
    calib_point[2]=beriz[3];

    

    Serial.println("cal jadid");
    Serial.println(calib_point[1]);
    Serial.println(calib_point[2]);
    Serial.println(calib_point[3]);
    Serial.println(calib_point[4]);
    Serial.println("cal ghadim");
    Serial.println(beriz[1]);
    Serial.println(beriz[2]);
    Serial.println(beriz[3]);
    Serial.println(beriz[4]);

while(1){
    algorithm2();
}
    } 
else{
  while(1){
    algorithm();
      }}
      
      /////////
      delay(400);
     
      lcd.clear();
      lcd.setCursor(0, 0);
      GY271.calculate();
      lcd.print(GY271.getHeadingDegree('z'));
      delay(20);
   }
  delay(100);
}
  float getdeg (void){////////////////////////////////////////////////////////////////////////////////////////////////////////
  GY271.calculate();
  return(GY271.getHeadingDegree('z'));
}
  void cal(){/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  currentTime=millis();
  if((currentTime-lastDebounceTime)>debounceDelay){
    
  
  if(i<5){
   
   calib_point[i]=deg;
   Serial.println(i);
   Serial.println(calib_point[i]);

      lcd.clear();
      lcd.setCursor(0,0);
      sprintf(str,"calib_point[%d]=",i);
      lcd.print(str);
      sprintf(str,"%d",calib_point[i]);
      lcd.setCursor(0,1);
      lcd.print(str);
      delay(500);
   i++;
    }else{
      detachInterrupt(digitalPinToInterrupt(touchright));
      }
    lastDebounceTime=currentTime;
    }

  }
  void goforward(int j){//////////////////////////////////////////////////////////////////////////////////////////////////////////
  speed = 100;
   
  Serial.println(calib_point[j]);
  deg=getdeg();
   if(deg>calib_point[j]){  //turning left
      analogWrite(enR,speed+10+tr);
      analogWrite(enL,speed-tr);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("turning left");
   }
  else if(deg<calib_point[j]){ //turning right
      analogWrite(enR,speed+25-tr);
      analogWrite(enL,speed+tr);
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("turning right");
   }
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

}
  void gobackward(){//////////////////////////////////////////////////////////////////////////////////////////////////////////

  speed = 50;
  analogWrite(enR,speed+25);
  analogWrite(enL,speed);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
    }
  void turnright(){/////////////////////////////////////////////////////////////////////////////////////////////////////////
  speed=45;
  //right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  //chap
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  analogWrite(enR,speed);
  analogWrite(enL,speed);
  delay(turndelaytime);
  
  stop();
  delay(200);
}
  void goforward2(){///////////////////////////////////////////////////////////////////////////////////////////////////////////
  speed = 100;
  analogWrite(enR,speed+25);
  analogWrite(enL,speed);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
    
    } 
  void turnleft(){///////////////////////////////////////////////////////////////////////////////////////////////////////////
  speed=40;
  //right
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  //chap
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  
  analogWrite(enR,speed);
  analogWrite(enL,speed);
  delay(turndelaytime);
 
  stop();
  delay(200);
}
  void stop(){///////////////////////////////////////////////////////////////////////////////////////////////////////////////

  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  }
  void config(){/////////////////////////////////////////////////////////////////////////////////////////////////////////////

            Serial.begin(9600);
            GY271.begin();
            lcd.begin (16, 2);
            analogWrite(11, 120);
            pinMode(touchforward1,INPUT_PULLUP);
            pinMode(touchforward2,INPUT_PULLUP);
            pinMode(touchright,INPUT_PULLUP);
            pinMode(touchleft,INPUT_PULLUP);
            pinMode(enR, OUTPUT);
            pinMode(enL, OUTPUT);
            pinMode(in1, OUTPUT);
            pinMode(in2, OUTPUT);
            pinMode(in3, OUTPUT);
            pinMode(in4, OUTPUT); 
            attachInterrupt(digitalPinToInterrupt(18),cal,LOW);
    }
  void detection(){//////////////////////////////////////////////////////////////////////////////////////////////////////////

            currentTime=millis();
            GY271.calculate();
            int firstdeg=getdeg();
            speed=40;
            //right
            digitalWrite(in1, HIGH);
            digitalWrite(in2, LOW);
            //chap
            digitalWrite(in3, LOW);
            digitalWrite(in4, HIGH);
            analogWrite(enR,speed);
            analogWrite(enL,speed);
            delay(500);
            GY271.calculate();
            deg2=getdeg();
            while((deg2>firstdeg+3)||(deg2<firstdeg-3)){
                    GY271.calculate();
                    deg2=getdeg();}
            stop(); 
            turndelaytime=(millis()-currentTime)/4;
      
      }
  void algorithm(void){//////////////////////////////////////////////////////////////////////////////////////////////////////////
         s1: 
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S1");
     while((digitalRead(touchforward1) && digitalRead(touchforward2))){
     goforward(1);
     }
     stop();
     delay(500);
     gobackward();
     
    s2:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S2");
      delay(400);
      turnright();
    s3:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S3");
      goforward2();
      delay(1500);
      stop();
      delay(300);
    s4:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S4");
      delay(400);
      turnleft();
      delay(400);
      while((digitalRead(touchforward1) && digitalRead(touchforward2))){
        lasttime=millis();
      goforward(1);
      }
      currentTime=millis()-lasttime;
      if(currentTime>1000){
        goto s1;
        }else{
      stop();
      delay(500);
      gobackward();
      delay(500);
      turnright();
      delay(500);
      turnright();
          
          }    
    s5:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S5");
      delay(400);
       while((digitalRead(touchforward1) && digitalRead(touchforward2))){
      goforward(3);
       }
     stop();
     delay(200);
     gobackward();
     
    s6:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S6");
      delay(400);
      turnleft();
    s7:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S7");
     delay(400);
     goforward2();
     delay(1500);
     stop();
    
     s8:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S8");

      delay(400);
       turnright();
      delay(400);
      while((digitalRead(touchforward1) && digitalRead(touchforward2))){
        lasttime=millis();
      goforward(3);
      }
      currentTime=millis()-lasttime;
      if(currentTime>1000){
        goto s5;
        }else{
      stop();
      delay(500);
      gobackward();
      delay(500);
      turnleft();
      delay(500);
      turnleft();
        
        }}
  void algorithm2(void){
               s1: 
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S1");
     while((digitalRead(touchforward1) && digitalRead(touchforward2))){
     goforward(1);
     }
     stop();
     delay(500);
     gobackward();
     
    s2:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S2");
      delay(400);
      turnleft();
    s3:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S3");
      goforward2();
      delay(1500);
      stop();
      delay(300);
    s4:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S4");
      delay(400);
      turnright();
      delay(400);
      while((digitalRead(touchforward1) && digitalRead(touchforward2))){
        lasttime=millis();
      goforward(1);
      }
      currentTime=millis()-lasttime;
      if(currentTime>1000){
        goto s1;
        }else{
      stop();
      delay(500);
      gobackward();
      delay(500);
      turnleft();
      delay(500);
      turnleft();
          
          }    
    s5:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S5");
      delay(400);
       while((digitalRead(touchforward1) && digitalRead(touchforward2))){
      goforward(3);
       }
     stop();
     delay(200);
     gobackward();
     
    s6:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S6");
      delay(400);
      turnright();
    s7:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S7");
     delay(400);
     goforward2();
     delay(1500);
     stop();
    
     s8:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("S8");

      delay(400);
       turnleft();
      delay(400);
      while((digitalRead(touchforward1) && digitalRead(touchforward2))){
        lasttime=millis();
      goforward(3);
      }
      currentTime=millis()-lasttime;
      if(currentTime>1000){
        goto s5;
        }else{
      stop();
      delay(500);
      gobackward();
      delay(500);
      turnright();
      delay(500);
      turnright();
        
        }
        }
        
