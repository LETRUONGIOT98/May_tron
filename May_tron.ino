
//maytron24@gmail.com
//Matkhau123
//blynk.jpnet.co.th
/*
 * 1. Set tốc độ và thời gian chạy thì nó chạy hết th gian nó tự dừng. Trong chế độ này, mình tự do tăng tốc độ khuấy nhưng time set ban đầu là k đổi. Này y như dự án cũ.
2. Tương tự như số 1. Nhưng có thể set đc sau th gian bao lâu nó tự tăng tốc lên thêm. Khi hết th gian khuấy hệ thống tự dừng.
3. Có thể nhấn nút stop bất cứ lúc nào nếu ko muốn chạy tiếp, nhấn lại thì nó reset toàn ch trình để mình set up lại. Tương tự như code cụ ở tính năng này

Ngoài lề liên quan 3 tính năng.
1. Th gian có thể set tối đa là bao lâu, còn tốc độ tối đa thì theo động cơ rồi 915v ạ.
2. Tính năng số 3 ngoài vc dừng và reset mình có thể có cách cho máy tiếp tục chạy như thông số đang chạy ko. Ví dụ mình lỡ tay nhấn nhầm hay muốn dừng lại để thêm hóa chất vô rồi tiếp tục khuấy ạ.
3. Đối với TH2 khi tự ý tăng tốc độ lên có đc ko ạ, hay muốn thay đổi thì phải reset để set uo lại. Nếu thay đổi đc thì mấy cái mình đã set thay đổi ntn ạ. Có lẽ câu này là khó nhất với em. Em cảm ơn
 */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
char auth[] = "CmTuwEaK4Efl4M9yB5Eu1hRDWLWpFRTR";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Thu Thao";
char pass[] = "12052002";
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
WidgetLCD lcd1(V0);
WidgetLCD lcd2(V1);
#define Mod D3
#define tang D4
#define giam D5
#define tamdung D6
#define Motor D0
#define StopPin D7
long time1,time2;
int thoigian = 0,oldTime;
int tt,pwm;
int batdau = 0;
int tocdo,Mode;
String chedo = "CHE DO 1";
int val1, val2, val3,val4;
int val11, val22, val33,val44;

const int analogInPin = A0; // chân tín hiệu của pt100 nối với chân A0

const int SensorValueLow = 269; 
const int SensorValueDiff = 1; 
const int TempValueDiff = 1; 
const int TempValueLow = 9;

int sensorValue = 0;
double Temp = 0;
int gioihan = 40;///Giới hạn nhiệt độ
int Tmax = 0, Smax=0;
void setup() {
  // put your setup code here, to run once:
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
  Serial.begin(9600);
  
  pinMode(Mod, INPUT_PULLUP);
  pinMode(tang, INPUT_PULLUP);
  pinMode(giam, INPUT_PULLUP);
  pinMode(tamdung, INPUT_PULLUP);
  pinMode(StopPin, INPUT_PULLUP);
  pinMode(Motor, OUTPUT);
  digitalWrite(Motor, LOW);
  lcd.setCursor(0, 0);
  lcd.print(" DANG KET NOI WIFI ");
  lcd.setCursor(0, 1);
  lcd.print(" XIN VUI LONG CHO ");
  
  delay(1000);
  Blynk.begin(auth, ssid, pass,"blynk.jpnet.co.th",8080);
   Blynk.run();
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 3);
    lcd.print("  MAY TRON TU DONG  ");
  Blynk.virtualWrite(V2,0);
  // attachInterrupt(D0, ReSet, RISING);
 /// attachInterrupt(1, DEM1, RISING);
}
int k;
void hienthi(int M){
  if(M==0){
    if(val1 == 0 || val11 == 1){
        k = 0;
        Serial.println("DA NHAN D4");
      }
      if(val2 == 0 || val22 == 1){
        k = 1;
        Serial.println("DA NHAN D5");
      }
     if(k == 0)chedo = "CHE DO 1";
     if(k == 1)chedo = "CHE DO 2";
    lcd.setCursor(0, 0);
    lcd.print(">   CHON CHE DO   ");
    lcd.setCursor(0, 1);
    lcd.print(chedo + String("      "));
    lcd.setCursor(0, 2);
    lcd.print("                   ");

    lcd1.print(0,0,">  CHON CHE DO  ");
    lcd1.print(0,1,chedo + "   ");
    lcd2.print(0,0,"                ");
  }
 if(M==1){
    if(val1 == 0 || val11 == 1){
        gioihan = gioihan + 1;
        Serial.println("DA NHAN D4");
      }
      if(val2 == 0 || val22 == 1){
        gioihan = gioihan - 1;
        Serial.println("DA NHAN D5");
      }
     if(k == 0)chedo = "CHE DO 1";
     if(k == 1)chedo = "CHE DO 2";
    lcd.setCursor(0, 0);
    lcd.print("     CHON CHE DO    ");
    lcd.setCursor(0, 1);
    lcd.print(chedo + String("      "));
    lcd.setCursor(0, 2);
    lcd.print("> NHIET DO:         ");
    lcd.setCursor(0, 2);
    lcd.print(gioihan);

    lcd1.print(0,0,">  CHON CHE DO  ");
    lcd1.print(0,1,chedo + "   ");
    lcd2.print(0,0,"                ");
  }
 

  ////////CHế độ 1;
  if(chedo == "CHE DO 1"){
    if(tt >= 4) tt = 2;
  if(M==2){
     if(val1 == 0 || val11 == 1){
        thoigian = thoigian + 5;
        delay(50);
      }
      if(val2 == 0 || val22 == 1){
        thoigian = thoigian - 5;
        delay(50);
      }
      if(thoigian <= 0) thoigian = 0;
    lcd.setCursor(0, 0);
    lcd.print("      CHE DO 1      ");
    lcd.setCursor(0, 1);
    lcd.print("> TIME:            s");
    lcd.setCursor(8, 1);
    lcd.print(thoigian);
    lcd.setCursor(0, 2);
    lcd.print("  SPEED:            ");
    lcd.setCursor(9, 2);
    lcd.print(tocdo);

    lcd1.print(0,0,"    CHE DO 1    ");
    lcd1.print(0,1,"> TIME:        s");
    lcd1.print(8,1,thoigian);
    lcd2.print(0,0,"  SPEED:        ");
    lcd2.print(9,0,tocdo);
  }
  if(M==3){
     if(val1 == 0 || val11 == 1){
        tocdo = tocdo + 10;
        delay(50);
      }
      if(val2 == 0 || val22 == 1){
        tocdo = tocdo - 10;
        delay(50);
      }
      if(tocdo <= 0) tocdo = 0;
      if(tocdo >= 915) tocdo = 915;
    lcd.setCursor(0, 0);
    lcd.print("      CHE DO 1      ");
    lcd.setCursor(0, 1);
    lcd.print("  TIME:            s");
    lcd.setCursor(8, 1);
    lcd.print(thoigian);
    lcd.setCursor(0, 2);
    lcd.print("> SPEED:             ");
    lcd.setCursor(9, 2);
    lcd.print(tocdo);

    lcd1.print(0,0,"    CHE DO 1    ");
    lcd1.print(0,1,"  TIME:        s");
    lcd1.print(8,1,thoigian);
    lcd2.print(0,0,"> SPEED:        ");
    lcd2.print(9,0,tocdo);
  }
  }
  if(chedo == "CHE DO 2"){
   if(tt >= 7) tt = 4;
  if(M==4){
     if(val1 == 0 || val11 == 1){
        thoigian = thoigian + 5;
        delay(50);
      }
      if(val2 == 0 || val22 == 1){
        thoigian = thoigian - 5;
        delay(50);
      }
      if(thoigian <= 0) thoigian = 0;
    lcd.setCursor(0, 0);
    lcd.print("      CHE DO 1      ");
    lcd.setCursor(0, 1);
    lcd.print("> TIME:            s");
    lcd.setCursor(8, 1);
    lcd.print(thoigian);
    lcd.setCursor(0, 2);
    lcd.print("Time max:          s");
    lcd.setCursor(0, 3);
    lcd.print("Speed max:         s");
    lcd1.print(0,0,"    CHE DO 1    ");
    lcd1.print(0,1,"> TIME:        s");
    lcd1.print(8,1,thoigian);
    lcd2.print(0,0,"Tmax:           s");
    lcd2.print(0,1,"Smax:            ");
  }

  if(M==5){
     if(val1 == 0 || val11 == 1){
        Tmax = Tmax + 5;
        delay(50);
      }
      if(val2 == 0 || val22 == 1){
        Tmax = Tmax - 5;
        delay(50);
      }
      if(Tmax <= 0) Tmax = 0;
      oldTime = Tmax;
    lcd.setCursor(0, 0);
    lcd.print("      CHE DO 1      ");
    lcd.setCursor(0, 1);
    lcd.print("  TIME:            s");
    lcd.setCursor(8, 1);
    lcd.print(thoigian);
    lcd.setCursor(0, 2);
    lcd.print("> Time max:          s");
    lcd.setCursor(11, 2);
    lcd.print(Tmax);
    lcd.setCursor(0, 3);
    lcd.print("  Speed max:         s");
    lcd.setCursor(11, 2);
    lcd.print(Smax);
    lcd1.print(0,0,"    CHE DO 1    ");
    lcd1.print(0,1,"  TIME:        s");
    lcd1.print(8,1,thoigian);
    lcd2.print(0,0,"> Tmax:        s");
    lcd2.print(6,0,Tmax);
    lcd2.print(0,1,"  Smax:         ");
    lcd1.print(6,1,Smax);
  }

  if(M==6){
     if(val1 == 0 || val11 == 1){
        Smax = Smax + 10;
        delay(50);
      }
      if(val2 == 0 || val22 == 1){
        Smax = Smax - 10;
        delay(50);
      }
      if(Tmax <= 0) Tmax = 0;
    lcd.setCursor(0, 0);
    lcd.print("      CHE DO 1      ");
    lcd.setCursor(0, 1);
    lcd.print("  TIME:            s");
    lcd.setCursor(8, 1);
    lcd.print(thoigian);
    lcd.setCursor(0, 2);
    lcd.print("  Time max:          s");
    lcd.setCursor(11, 2);
    lcd.print(Tmax);
    lcd.setCursor(0, 3);
    lcd.print("> Speed max:         s");
    lcd.setCursor(11, 2);
    lcd.print(Smax);
    lcd1.print(0,0,"    CHE DO 1    ");
    lcd1.print(0,1,"  TIME:        s");
    lcd1.print(8,1,thoigian);
    lcd2.print(0,0,"  Tmax:        s");
    lcd2.print(6,0,Tmax);
    lcd2.print(0,1,"> Smax:         ");
    lcd1.print(6,1,Smax);
  }
}
  }
  void hienthit(){
     lcd.setCursor(0, 3);
    lcd.print("NHIET DO:         *C");
    lcd.setCursor(10, 3);
    lcd.print(Temp);
    lcd2.print(0,1,"T:            *C");
    lcd2.print(3,1,String(Temp,1));
  }
 BLYNK_WRITE(V2)
{
  val11 = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println("DA NHAN LENH");
}
BLYNK_WRITE(V3)
{
  val22 = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println("DA NHAN LENH");
}
BLYNK_WRITE(V4)
{
  val33 = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println("DA NHAN LENH");
}
BLYNK_WRITE(V5)
{
  val44 = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println("DA NHAN LENH");
}
void loop(){
  Blynk.run();
  val1 =  digitalRead(tang);
  val2 = digitalRead(giam);
  val3 = digitalRead(Mod);
  val4 = digitalRead(tamdung);
  if(digitalRead(StopPin) == 0){
    analogWrite(Motor, 0);
    batdau = 0;
    tt =0;
    thoigian = 0;
    tocdo = 0;
    k = 0;
    hienthi(tt);
  }
  if(Temp <= gioihan){
    
  if(val4 == 0 || val44 == 1){
    batdau = !batdau;
    delay(300);
  }
  if(batdau == 0){
    analogWrite(Motor, 0);
  if(val3 == 0 || val33 == 1){
    tt = tt+1;
    delay(300);
  }
  hienthi(tt);
  }
    
  if(batdau == 1){
    if(chedo == "CHE DO 1"){
    lcd.setCursor(0, 1);
    lcd.print("TIME:              s");
    lcd.setCursor(8, 1);
    lcd.print(thoigian);
    lcd.setCursor(0, 2);
    lcd.print("SPEED:              ");
    lcd.setCursor(9, 2);
    lcd.print(tocdo);

    
    lcd1.print(0,1,"TIME:              s");
    lcd1.print(8,1,thoigian);
    lcd2.print(0,0,"SPEED:              ");
    lcd2.print(9,0,tocdo);
    pwm = map(tocdo, 0,915,0,255);
    if(thoigian > 0){
      hienthit();
      lcd.setCursor(0, 0);
    lcd.print("  DANG CHAY MODE 1  ");
    lcd1.print(0,0,"  DANG CHAY MODE 1  ");
      if(millis() - time1 >= 1000){
        thoigian = thoigian - 1;
        time1 = millis();
      }
    analogWrite(Motor, pwm);
    }
    else {
      hienthit();
      lcd.setCursor(0, 0);
    lcd.print("   DA XONG MODE 1  ");
    lcd1.print(0,0,"   DA XONG MODE 1  ");
      analogWrite(Motor, 0);
    }
  }

  if(chedo == "CHE DO 2"){
    
    if(thoigian > 0){
      hienthit();
      lcd.setCursor(0, 0);
    lcd.print("  DANG CHAY MODE 2  ");
    
    lcd1.print(0,0," DANG CHAY MODE 2");
     
      if(millis() - time1 >= 1000){
        thoigian = thoigian - 1;
        if(Tmax > 0){
        Tmax = Tmax - 1;
        }
        time1 = millis();
      }
      tocdo = map(Tmax, 0,oldTime,Smax,0);
      pwm = map(tocdo,0,915,0,255);
      
    analogWrite(Motor, pwm);
    }
    else{
      hienthit();
      lcd.setCursor(0, 0);
    lcd.print("   DA XONG MODE 2  ");
    lcd1.print(0,0," DA XONG MODE 2");
      analogWrite(Motor, 0);
    }
    
    lcd.setCursor(0, 1);
    lcd.print("TIME:              s");
    lcd.setCursor(7, 1);
    lcd.print(thoigian);
    lcd.setCursor(0, 2);
    lcd.print("SPEED:              ");
    lcd.setCursor(8, 2);
    lcd.print(tocdo);
  }
  
}
lcd.setCursor(0, 3);
lcd.print("  MAY TRON TU DONG  ");
}
else {
  analogWrite(Motor, 0);
  
  
}
sensorValue = analogRead(analogInPin);
  Temp = sensorValue-SensorValueLow;
  Temp = Temp/SensorValueDiff;
  Temp = Temp*TempValueDiff;
  Temp = Temp+TempValueLow;
  Temp  = Temp - 1; //Cộng trừ cân chỉnh nhiệt độ đúng chuẩn
  Serial.print("C = ");
  Serial.println(Temp);
 
}
 
