#include <Servo.h> 

Servo esc1;   //Esc 1 
Servo esc2;   //Esc 2
int sensorPinX = A0;  //Joystick X ekseni
int sensorPinY = A1;  //Joystick Y ekseni
int button = 10;      //Joystick buton
int speedvalue = 0;   
int speedvaluex = 0;  //X ekseninden gelen hız değişkeni
int speedvaluey = 0;  //Y ekseninden gelen hız değişkeni
int initiate = 0;     
int buttonVal = 0;    //Butondan okundan değer
int condition = 1;        //Çalışma koşulu



void setup() {
  pinMode(sensorPinX, INPUT);
  pinMode(sensorPinY, INPUT);
  pinMode(button, INPUT);
  //Serial.begin(9600);

  esc1.attach(8);     //Esc 1 pin e atanıyor
  esc2.attach(9);     //Esc 2 pin e atanıyor
}


void loop() 
{
    //BUTON KONTROLÜ
    buttonVal = digitalRead(button);   //Butondan değer okunuyor
    //Serial.print(buttonVal);          

    if(buttonVal == 1 ){  //Butona basıldıysa bu koşula giriyor
      delay(100);         //100 ms gecikme(butondan birden fazla değer almamak için kullandık)
      condition = !condition;     //Butondan gelen değere göre çalışma koşulu tersine çevriliyor
    }

    //ÇALIŞMA KOŞULU
    if(condition == 0){   //Çalışma koşulu 0 -> Çalış

          int speedvalx = analogRead(sensorPinX);   //Joystickten X ekseninin analog değeri speedvalx değişkenine alınıyor
          int speedvaly = analogRead(sensorPinY);   //Joystickten Y ekseninin analog değeri speedvaly değişkenine alınıyor

          speedvaluex = map(speedvalx, 0, 1023, 500, 2000);   //speedvalx değerine alınan analog değer 500-2000 aralığına dağıtılıyor
          speedvaluey = map(speedvaly, 0, 1023, 500, 2000);   //speedvaly değerine alınan analog değer 500-2000 aralığına dağıtılıyor
           

          if (initiate == 0) {  //Motorlar duran durumdan harekete geçiyorsa bu koşul gerçekleşiyor
            throttleUp();       //Motorların başlangıç için hızlanma fonksiyonları
            initiate = 1;       //Motorların harekete geçtiği bilgisi initiate değişkenine atanıyor
            //Serial.println("  throttleUp");
          }

          if (initiate < 2) {   //Motorların hareketli olduğu durumda girilen koşul
              //Serial.println("  run");
              esc1.writeMicroseconds(speedvaluex);  //Hesaplanan değer motora gönderiliyor
              esc2.writeMicroseconds(speedvaluey);  //Hesaplanan değer motara gönderiliyor
              delay(1);                             //1 ms gecikme
              initiate = 1;                         //Motorların hareket halinde olduğu belirtiliyor
          }    
          
    //DURMA DURUMU      
    } else if(condition == 1){                //Çalışma koşulu 1 -> Dur                
          esc1.writeMicroseconds(700);    //Motoru durdurmak için 700 yazılması gerekiyor(Motor Durduruluyor)
          esc2.writeMicroseconds(700);    //Motoru durdurmak için 700 yazılması gerekiyor(Motor Durduruluyor)
          //Serial.println("  stop");
          initiate = 0;                   //Motorların durduğu bilgisi initiate değişkenine atanıyor
          buttonVal = 0;                  //Buton hataların engellemek için butondan okunan değeri 0 yapıyoruz
          delay(200);                     //200 ms gecikme
    }

    delay(10);    //10 ms gecikme
} 


//HIZLANMA FONKSİYONU
void throttleUp() { 
    int arm = 1000                             
    for (int count = 0; count < 300; count++) {
      esc1.writeMicroseconds(arm);
      esc2.writeMicroseconds(arm);
      arm = arm + 1;
      delay(15);
    }
}
