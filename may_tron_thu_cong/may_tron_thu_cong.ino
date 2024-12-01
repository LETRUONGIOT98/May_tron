
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define Mod D3
#define tang D4
#define giam D5
#define tamdung D6
#define Motor D0
#define StopPin D7
long time1, time2;
int thoigian = 0, oldTime;
int tt, pwm;
int batdau = 0;
int tocdo, Mode;
String chedo = "CHE DO 1";
int val1, val2, val3, val4;
int val11, val22, val33, val44;

const int analogInPin = A0; // chân tín hiệu của pt100 nối với chân A0

const int SensorValueLow = 269;
const int SensorValueDiff = 1;
const int TempValueDiff = 1;
const int TempValueLow = 9;

int sensorValue = 0;
double Temp = 0;
int gioihan = 40;///Giới hạn nhiệt độ
int Tmax = 0, Smax = 0;
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
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("  MAY TRON TU DONG  ");
}
int k;
void hienthi(int M) {
  if (M == 0) {
    if (val1 == 0 || val11 == 1) {
      k = 0;
      Serial.println("DA NHAN D4");
    }
    if (val2 == 0 || val22 == 1) {
      k = 1;
      Serial.println("DA NHAN D5");
    }
    if (k == 0)chedo = "CHE DO 1";
    if (k == 1)chedo = "CHE DO 2";
    lcd.setCursor(0, 0);
    lcd.print(">   CHON CHE DO   ");
    lcd.setCursor(0, 1);
    lcd.print(chedo + String("      "));
    lcd.setCursor(0, 2);
    lcd.print("  NHIET DO:         ");
    lcd.setCursor(12, 2);
    lcd.print(gioihan);
  }
  if (M == 1) {
    if (val1 == 0 || val11 == 1) {
      gioihan = gioihan + 1;
      Serial.println("DA NHAN D4");
    }
    if (val2 == 0 || val22 == 1) {
      gioihan = gioihan - 1;
      Serial.println("DA NHAN D5");
    }
    if (k == 0)chedo = "CHE DO 1";
    if (k == 1)chedo = "CHE DO 2";
    lcd.setCursor(0, 0);
    lcd.print("     CHON CHE DO    ");
    lcd.setCursor(0, 1);
    lcd.print(chedo + String("      "));
    lcd.setCursor(0, 2);
    lcd.print("> NHIET DO:         ");
    lcd.setCursor(12, 2);
    lcd.print(gioihan);
  }


  ////////CHế độ 1;
  if (chedo == "CHE DO 1") {
    if (tt >= 4) tt = 2;
    if (M == 2) {
      if (val1 == 0 || val11 == 1) {
        thoigian = thoigian + 5;
        delay(100);
      }
      if (val2 == 0 || val22 == 1) {
        thoigian = thoigian - 5;
        delay(100);
      }
      if (thoigian <= 0) thoigian = 0;
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
    }
    if (M == 3) {
      if (val1 == 0 || val11 == 1) {
        tocdo = tocdo + 10;
        delay(100);
      }
      if (val2 == 0 || val22 == 1) {
        tocdo = tocdo - 10;
        delay(100);
      }
      if (tocdo <= 0) tocdo = 0;
      if (tocdo >= 915) tocdo = 915;
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
    }
  }
  if (chedo == "CHE DO 2") {
    if (tt >= 7) tt = 4;
    if (M == 4) {
      if (val1 == 0 || val11 == 1) {
        thoigian = thoigian + 10;
        delay(100);
      }
      if (val2 == 0 || val22 == 1) {
        thoigian = thoigian - 10;
        delay(100);
      }
      if (thoigian <= 0) thoigian = 0;
      lcd.setCursor(0, 0);
      lcd.print("      CHE DO 1      ");
      lcd.setCursor(0, 1);
      lcd.print("> TIME:            s");
      lcd.setCursor(8, 1);
      lcd.print(thoigian);
     lcd.setCursor(0, 2);
      lcd.print("  Time max:        s");
      lcd.setCursor(11, 2);
      lcd.print(Tmax);
      lcd.setCursor(0, 3);
      lcd.print("  Speed max:        ");
      lcd.setCursor(12, 3);
      lcd.print(Smax);
    }

    if (M == 5) {
      if (val1 == 0 || val11 == 1) {
        Tmax = Tmax + 5;
        delay(100);
      }
      if (val2 == 0 || val22 == 1) {
        Tmax = Tmax - 5;
        delay(100);
      }
      if (Tmax <= 0) Tmax = 0;
      oldTime = Tmax;
      lcd.setCursor(0, 0);
      lcd.print("      CHE DO 1      ");
      lcd.setCursor(0, 1);
      lcd.print("  TIME:            s");
      lcd.setCursor(8, 1);
      lcd.print(thoigian);
      lcd.setCursor(0, 2);
      lcd.print("> Time max:        s");
      lcd.setCursor(11, 2);
      lcd.print(Tmax);
      lcd.setCursor(0, 3);
      lcd.print("  Speed max:        ");
      lcd.setCursor(12, 3);
      lcd.print(Smax);
    }

    if (M == 6) {
      if (val1 == 0 || val11 == 1) {
        Smax = Smax + 10;
        delay(100);
      }
      if (val2 == 0 || val22 == 1) {
        Smax = Smax - 10;
        delay(100);
      }
      if (Tmax <= 0) Tmax = 0;
      lcd.setCursor(0, 0);
      lcd.print("      CHE DO 1      ");
      lcd.setCursor(0, 1);
      lcd.print("  TIME:            s");
      lcd.setCursor(8, 1);
      lcd.print(thoigian);
      lcd.setCursor(0, 2);
      lcd.print("  Time max:        s");
      lcd.setCursor(11, 2);
      lcd.print(Tmax);
      lcd.setCursor(0, 3);
      lcd.print("> Speed max:        ");
      lcd.setCursor(12, 3);
      lcd.print(Smax);
    }
  }
}
void hienthit() {
  lcd.setCursor(0, 3);
  lcd.print("NHIET DO:         *C");
  lcd.setCursor(10, 3);
  lcd.print(Temp);
}

void loop() {
  val1 =  digitalRead(tang);
  val2 = digitalRead(giam);
  val3 = digitalRead(Mod);
  val4 = digitalRead(tamdung);
  if (digitalRead(StopPin) == 0) {
    analogWrite(Motor, 0);
    batdau = 0;
    tt = 0;
    thoigian = 0;
    tocdo = 0;
    k = 0;
    hienthi(tt);
  }
  if (Temp <= gioihan) {

    if (val4 == 0 || val44 == 1) {
      batdau = !batdau;
      delay(300);
    }
    if (batdau == 0) {
      analogWrite(Motor, 0);
      if (val3 == 0 || val33 == 1) {
        tt = tt + 1;
        delay(300);
      }
      hienthi(tt);
    }

    if (batdau == 1) {
      if (chedo == "CHE DO 1") {
        if (val1 == 0 || val11 == 1) {
        tocdo = tocdo + 10;
        delay(100);
      }
      if (val2 == 0 || val22 == 1) {
        tocdo = tocdo - 10;
        delay(100);
      }
        lcd.setCursor(0, 1);
        lcd.print("TIME:              s");
        lcd.setCursor(8, 1);
        lcd.print(thoigian);
        lcd.setCursor(0, 2);
        lcd.print("SPEED:              ");
        lcd.setCursor(9, 2);
        lcd.print(tocdo);
        pwm = map(tocdo, 0, 915, 0, 255);
        if (thoigian > 0) {
          hienthit();
          lcd.setCursor(0, 0);
          lcd.print("  DANG CHAY MODE 1  ");
          if (millis() - time1 >= 1000) {
            thoigian = thoigian - 1;
            time1 = millis();
          }
          analogWrite(Motor, pwm);
        }
        else {
          hienthit();
          lcd.setCursor(0, 0);
          lcd.print("   DA XONG MODE 1  ");
          analogWrite(Motor, 0);
        }
      }

      if (chedo == "CHE DO 2") {

        if (thoigian > 0) {
          hienthit();
          lcd.setCursor(0, 0);
          lcd.print("  DANG CHAY MODE 2  ");
          if (millis() - time1 >= 1000) {
            thoigian = thoigian - 1;
            if (Tmax > 0) {
              Tmax = Tmax - 1;
            }
            time1 = millis();
          }
          tocdo = map(Tmax, 0, oldTime, Smax, 0);
          pwm = map(tocdo, 0, 915, 0, 255);

          analogWrite(Motor, pwm);
        }
        else {
          hienthit();
          lcd.setCursor(0, 0);
          lcd.print("   DA XONG MODE 2  ");
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
  }
  else {
    analogWrite(Motor, 0);
    lcd.setCursor(0, 0);
    lcd.print("DAT DEN NGUONG NHIET");

  }
  sensorValue = analogRead(analogInPin);
  Temp = sensorValue - SensorValueLow;
  Temp = Temp / SensorValueDiff;
  Temp = Temp * TempValueDiff;
  Temp = Temp + TempValueLow;
  Temp  = Temp - 1; //Cộng trừ cân chỉnh nhiệt độ đúng chuẩn
  Serial.print("C = ");
  Serial.println(Temp);

}
