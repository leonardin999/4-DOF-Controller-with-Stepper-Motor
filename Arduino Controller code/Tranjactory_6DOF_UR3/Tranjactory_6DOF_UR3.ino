/* File hoàn chỉnh cho 5 khớp chạy */

#include <DueTimer.h>

#define DIR_1 3
#define PULSE_1 4

#define DIR_2 5
#define PULSE_2 6

#define DIR_3 7
#define PULSE_3 8

#define DIR_4 10
#define PULSE_4 11

#define DIR_5 12
#define PULSE_5 13

#define servoPin 9
//==============================================================
//==============================================================

volatile int count_1, xung_com_1, error_1;
volatile float vitri_1, vitri_dat_1;
volatile float vitri_thuc_1;
volatile int T1;

volatile float the_1, the_1_pre, the_1_flex;
volatile float a1, b1, c1, d1;
volatile float t_count, t_command, t_quyhoach_1;

//==============================================================
//==============================================================

volatile int count_2, xung_com_2, error_2;
volatile float vitri_2, vitri_dat_2;
volatile float vitri_thuc_2;
volatile int T2;

volatile float the_2, the_2_pre, the_2_flex;
volatile float a2, b2, c2, d2;
volatile float t_quyhoach_2;

//==============================================================
//==============================================================

volatile int count_3, xung_com_3, error_3;
volatile float vitri_3, vitri_dat_3;
volatile float vitri_thuc_3;
volatile int T3;

volatile float the_3, the_3_pre, the_3_flex;
volatile float a3, b3, c3, d3;
volatile float t_quyhoach_3;

//==============================================================
//==============================================================

volatile int count_4, xung_com_4, error_4;
volatile float vitri_4, vitri_dat_4;
volatile float vitri_thuc_4;
volatile int T4;

volatile float the_4, the_4_pre, the_4_flex;
volatile float a4, b4, c4, d4;
volatile float t_quyhoach_4;

//==============================================================
//==============================================================

volatile int count_5, xung_com_5, error_5;
volatile float vitri_5, vitri_dat_5;
volatile float vitri_thuc_5;
volatile int T5;

volatile float the_5, the_5_pre, the_5_flex;
volatile float a5, b5, c5, d5;
volatile float t_quyhoach_5;

//==============================================================
//==============================================================
volatile float vitri_dat_6,vitri_thuc_6;
int x6;
//==============================================================
//==============================================================

void setup()
{
  //==============================================================
  //==============================================================
  pinMode(DIR_1, OUTPUT); // CHAN PWM
  pinMode(PULSE_1, OUTPUT); //chan dieu khien dong co
  digitalWrite(PULSE_1, LOW);
  //===============================
  vitri_dat_1 = 0;
  vitri_1 = 0;
  vitri_thuc_1 = vitri_1;
  xung_com_1 = 0;
  count_1 = 0;
  T1 = 8;
  t_count = 0;
  t_command = 0;
  t_quyhoach_1 = 0;
  error_1 = 0;
  //==============================================================
  //==============================================================
  pinMode(DIR_2, OUTPUT); // CHAN PWM
  pinMode(PULSE_2, OUTPUT); //chan dieu khien dong co
  digitalWrite(PULSE_2, LOW);
  //===============================
  vitri_dat_2 = 90;
  vitri_2 = 90;
  vitri_thuc_2 = vitri_2;
  xung_com_2 = 0;
  count_2 = 0;
  T2 = 8;
  t_count = 0;
  t_command = 0;
  t_quyhoach_2 = 0;
  error_2 = 0;
  //==============================================================
  //==============================================================
  pinMode(DIR_3, OUTPUT); // CHAN PWM
  pinMode(PULSE_3, OUTPUT); //chan dieu khien dong co
  digitalWrite(PULSE_3, LOW);
  //===============================
  vitri_dat_3 = 0;
  vitri_3 = 0;
  vitri_thuc_3 = vitri_3;
  xung_com_3 = 0;
  count_3 = 0;
  T3 = 8;
  t_count = 0;
  t_command = 0;
  t_quyhoach_3 = 0;
  error_3 = 0;
  //==============================================================
  //==============================================================
  pinMode(DIR_4, OUTPUT); // CHAN PWM
  pinMode(PULSE_4, OUTPUT); //chan dieu khien dong co
  digitalWrite(PULSE_4, LOW);
  //===============================
  vitri_dat_4 = 90;
  vitri_4 = 90;
  vitri_thuc_4 = vitri_4;
  xung_com_4 = 0;
  count_4 = 0;
  T4 = 8;
  t_count = 0;
  t_command = 0;
  t_quyhoach_4 = 0;
  error_4 = 0;
  //==============================================================
  //==============================================================
  pinMode(DIR_5, OUTPUT); // CHAN PWM
  pinMode(PULSE_5, OUTPUT); //chan dieu khien dong co
  digitalWrite(PULSE_5, LOW);
  //===============================
  vitri_dat_5 = 0;
  vitri_5 = 0;
  vitri_thuc_5 = vitri_5;
  xung_com_5 = 0;
  count_5 = 0;
  T5 = 8;
  t_count = 0;
  t_command = 0;
  t_quyhoach_5 = 0;
  error_5 = 0;
  //==============================================================
  //==============================================================
  pinMode(servoPin,OUTPUT);
  vitri_thuc_6 = 0;
  vitri_dat_6 = 0;
  x6=0;
  //==============================================================
  //==============================================================
  Serial.begin(115200); //khoi tao gui thong tin serial
  Timer1.attachInterrupt(dieu_khien_1);
  Timer2.attachInterrupt(dieu_khien_2);
  Timer3.attachInterrupt(dieu_khien_3);
  Timer4.attachInterrupt(dieu_khien_4);
  Timer5.attachInterrupt(dieu_khien_5);
  Timer6.attachInterrupt(quy_hoach);  // Chu ky 10ms
}

void phat_xung(unsigned int chan_phat_xung, unsigned int timedl)
{
  digitalWrite(chan_phat_xung, HIGH);
  delayMicroseconds(timedl);
  digitalWrite(chan_phat_xung, LOW);
  delayMicroseconds(timedl);
}

void forward(unsigned int chan_chieu)
{
  digitalWrite(chan_chieu, HIGH);
}

void reverse(unsigned int chan_chieu)
{
  digitalWrite(chan_chieu, LOW);
}

void Stop(unsigned int chan_chieu, unsigned int chan_phat_xung)
{
  digitalWrite(chan_chieu, LOW);
  digitalWrite(chan_phat_xung, LOW);
}

void dieu_khien_1()
{
  if ((the_1_flex - the_1_pre) > 0)
  {
    if (count_1 < round(the_1_flex - the_1_pre))
    {
      forward(DIR_1);
      phat_xung(PULSE_1, T1);
      count_1++;
      vitri_thuc_1 = vitri_thuc_1 + 0.01;
    }
    else
    {
      Stop(DIR_1, PULSE_1);
      Timer1.stop();
    }
  }
  else if ((the_1_flex - the_1_pre) < 0)
  {
    if (count_1 < abs(round(the_1_flex - the_1_pre)))
    {
      reverse(DIR_1);
      phat_xung(PULSE_1, T1);
      count_1++;
      vitri_thuc_1 = vitri_thuc_1 - 0.01;
    }
    else
    {
      Stop(DIR_1, PULSE_1);
      Timer1.stop();
    }
  }
  if (t_count > (t_command))
  {
    offset_1();
  }
}

void offset_1()
{
  error_1 = int((vitri_dat_1 - vitri_thuc_1) * 100);
  if (error_1 > 0)
  {
    forward(DIR_1);
    phat_xung(PULSE_1, T1);
    vitri_thuc_1 = vitri_thuc_1 + 0.01;
  }
  else if (error_1 < 0)
  {
    reverse(DIR_1);
    phat_xung(PULSE_1, T1);
    vitri_thuc_1 = vitri_thuc_1 - 0.01;
  }
}

void dieu_khien_2()
{
  if ((the_2_flex - the_2_pre) > 0)
  {
    if (count_2 < round(the_2_flex - the_2_pre))
    {
      forward(DIR_2);
      phat_xung(PULSE_2, T2);
      count_2++;
      vitri_thuc_2 = vitri_thuc_2 + 0.01;
    }
    else
    {
      Stop(DIR_2, PULSE_2);
      Timer2.stop();
    }
  }
  else if ((the_2_flex - the_2_pre) < 0)
  {
    if (count_2 < abs(round(the_2_flex - the_2_pre)))
    {
      reverse(DIR_2);
      phat_xung(PULSE_2, T2);
      count_2++;
      vitri_thuc_2 = vitri_thuc_2 - 0.01;
    }
    else
    {
      Stop(DIR_2, PULSE_2);
      Timer2.stop();
    }
  }
  if (t_count > (t_command))
  {
    offset_2();
  }
}

void offset_2()
{
  error_2 = int((vitri_dat_2 - vitri_thuc_2) * 100);
  if (error_2 > 0)
  {
    forward(DIR_2);
    phat_xung(PULSE_2, T2);
    vitri_thuc_2 = vitri_thuc_2 + 0.01;
  }
  else if (error_2 < 0)
  {
    reverse(DIR_2);
    phat_xung(PULSE_2, T2);
    vitri_thuc_2 = vitri_thuc_2 - 0.01;
  }
}

void dieu_khien_3()
{
  if ((the_3_flex - the_3_pre) > 0)
  {
    if (count_3 < round(the_3_flex - the_3_pre))
    {
      forward(DIR_3);
      phat_xung(PULSE_3, T3);
      count_3++;
      vitri_thuc_3 = vitri_thuc_3 + 0.01;
    }
    else
    {
      Stop(DIR_3, PULSE_3);
      Timer3.stop();
    }
  }
  else if ((the_3_flex - the_3_pre) < 0)
  {
    if (count_3 < abs(round(the_3_flex - the_3_pre)))
    {
      reverse(DIR_3);
      phat_xung(PULSE_3, T3);
      count_3++;
      vitri_thuc_3 = vitri_thuc_3 - 0.01;
    }
    else
    {
      Stop(DIR_3, PULSE_3);
      Timer3.stop();
    }
  }
  if (t_count > (t_command))
  {
    offset_3();
  }
}

void offset_3()
{
  error_3 = int((vitri_dat_3 - vitri_thuc_3) * 100);
  if (error_3 > 0)
  {
    forward(DIR_3);
    phat_xung(PULSE_3, T3);
    vitri_thuc_3 = vitri_thuc_3 + 0.01;
  }
  else if (error_3 < 0)
  {
    reverse(DIR_3);
    phat_xung(PULSE_3, T3);
    vitri_thuc_3 = vitri_thuc_3 - 0.01;
  }
}

void dieu_khien_4()
{
  if ((the_4_flex - the_4_pre) > 0)
  {
    if (count_4 < round(the_4_flex - the_4_pre))
    {
      forward(DIR_4);
      phat_xung(PULSE_4, T4);
      count_4++;
      vitri_thuc_4 = vitri_thuc_4 + 0.01;
    }
    else
    {
      Stop(DIR_4, PULSE_4);
      Timer4.stop();
    }
  }
  else if ((the_4_flex - the_4_pre) < 0)
  {
    if (count_4 < abs(round(the_4_flex - the_4_pre)))
    {
      reverse(DIR_4);
      phat_xung(PULSE_4, T4);
      count_4++;
      vitri_thuc_4 = vitri_thuc_4 - 0.01;
    }
    else
    {
      Stop(DIR_4, PULSE_4);
      Timer4.stop();
    }
  }
  if (t_count > (t_command))
  {
    offset_4();
  }
}

void offset_4()
{
  error_4 = int((vitri_dat_4 - vitri_thuc_4) * 100);
  if (error_4 > 0)
  {
    forward(DIR_4);
    phat_xung(PULSE_4, T4);
    vitri_thuc_4 = vitri_thuc_4 + 0.01;
  }
  else if (error_4 < 0)
  {
    reverse(DIR_4);
    phat_xung(PULSE_4, T4);
    vitri_thuc_4 = vitri_thuc_4 - 0.01;
  }
}

void dieu_khien_5()
{
  if ((the_5_flex - the_5_pre) > 0)
  {
    if (count_5 < round(the_5_flex - the_5_pre))
    {
      forward(DIR_5);
      phat_xung(PULSE_5, T5);
      count_5++;
      vitri_thuc_5 = vitri_thuc_5 + 0.01;
    }
    else
    {
      Stop(DIR_5, PULSE_5);
      Timer5.stop();
    }
  }
  else if ((the_5_flex - the_5_pre) < 0)
  {
    if (count_5 < abs(round(the_5_flex - the_5_pre)))
    {
      reverse(DIR_5);
      phat_xung(PULSE_5, T5);
      count_5++;
      vitri_thuc_5 = vitri_thuc_5 - 0.01;
    }
    else
    {
      Stop(DIR_5, PULSE_5);
      Timer5.stop();
    }
  }
  if (t_count > (t_command))
  {
    offset_5();
  }
}

void offset_5()
{
  error_5 = int((vitri_dat_5 - vitri_thuc_5) * 100);
  if (error_5 > 0)
  {
    forward(DIR_5);
    phat_xung(PULSE_5, T5);
    vitri_thuc_5 = vitri_thuc_5 + 0.01;
  }
  else if (error_5 < 0)
  {
    reverse(DIR_5);
    phat_xung(PULSE_5, T5);
    vitri_thuc_5 = vitri_thuc_5 - 0.01;
  }
}

void dk_servo6()
{
  x6 = map(vitri_dat_6,-90,90,550,2450);
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(x6); 
  digitalWrite(servoPin, LOW);
  delayMicroseconds(20000-x6);
  vitri_thuc_6=vitri_dat_6;
}

void serialEvent()
{
  String test1 = "";
  String test2 = "";
  String test3 = "";
  String test4 = "";
  String test5 = "";
  String test6 = "";
  String test7 = "";
  if (Serial.available() > 0)
  {
    test1 = Serial.readStringUntil(',');
    test2 = Serial.readStringUntil(',');
    test3 = Serial.readStringUntil(',');
    test4 = Serial.readStringUntil(',');
    test5 = Serial.readStringUntil(',');
    test6 = Serial.readStringUntil(',');
    test7 = Serial.readStringUntil('\n');

    vitri_dat_1 = test1.toFloat();    //Goc quay mong muon
    vitri_dat_2 = test2.toFloat();
    vitri_dat_3 = test3.toFloat();
    vitri_dat_4 = test4.toFloat();
    vitri_dat_5 = test5.toFloat();
    vitri_dat_6 = test6.toFloat();
    t_command = test7.toFloat();    // Thoi gian di chuyen mong muon

    if ((vitri_dat_1<-90) || (vitri_dat_1>90))    vitri_dat_1 = vitri_thuc_1;
    xung_com_1 = int((vitri_dat_1 - vitri_thuc_1) * 100);
    the_1 = xung_com_1;

    if ((vitri_dat_2<-20) || (vitri_dat_2>125))   vitri_dat_2 = vitri_thuc_2;
    xung_com_2 = int((vitri_dat_2 - vitri_thuc_2) * 100);
    the_2 = xung_com_2;

    if ((vitri_dat_3<-135) || (vitri_dat_3>135))  vitri_dat_3 = vitri_thuc_3;
    xung_com_3 = int((vitri_dat_3 - vitri_thuc_3) * 100);
    the_3 = xung_com_3;

    if ((vitri_dat_4<-50) || (vitri_dat_4>230))   vitri_dat_4 = vitri_thuc_4;
    xung_com_4 = int((vitri_dat_4 - vitri_thuc_4) * 100);
    the_4 = xung_com_4;

    xung_com_5 = int((vitri_dat_5 - vitri_thuc_5) * 100);
    the_5 = xung_com_5;

    vitri_dat_6=round(vitri_dat_6);
    /* ---- Reset thoi gian bat dau qui hoach quy dao khop 1-----*/
    t_count = 0;
    the_1_pre = 0;
    the_1_flex = 0;
    count_1 = 0;

    a1 = the_1_pre;
    b1 = 0;
    c1 = 3 * (the_1 - the_1_pre) / (t_command * t_command);
    d1 = -2 * (the_1 - the_1_pre) / (t_command * t_command * t_command);
    /* ---- Ket thuc ceset thoi gian bat dau qui hoach quy dao-----*/

    /* ---- Reset thoi gian bat dau qui hoach quy dao khop 2-----*/
    t_count = 0;
    the_2_pre = 0;
    the_2_flex = 0;
    count_2 = 0;

    a2 = the_2_pre;
    b2 = 0;
    c2 = 3 * (the_2 - the_2_pre) / (t_command * t_command);
    d2 = -2 * (the_2 - the_2_pre) / (t_command * t_command * t_command);
    /* ---- Ket thuc ceset thoi gian bat dau qui hoach quy dao-----*/

    /* ---- Reset thoi gian bat dau qui hoach quy dao khop 3-----*/
    t_count = 0;
    the_3_pre = 0;
    the_3_flex = 0;
    count_3 = 0;

    a3 = the_3_pre;
    b3 = 0;
    c3 = 3 * (the_3 - the_3_pre) / (t_command * t_command);
    d3 = -2 * (the_3 - the_3_pre) / (t_command * t_command * t_command);
    /* ---- Ket thuc ceset thoi gian bat dau qui hoach quy dao-----*/

    /* ---- Reset thoi gian bat dau qui hoach quy dao khop 4-----*/
    t_count = 0;
    the_4_pre = 0;
    the_4_flex = 0;
    count_4 = 0;

    a4 = the_4_pre;
    b4 = 0;
    c4 = 3 * (the_4 - the_4_pre) / (t_command * t_command);
    d4 = -2 * (the_4 - the_4_pre) / (t_command * t_command * t_command);
    /* ---- Ket thuc ceset thoi gian bat dau qui hoach quy dao-----*/

    /* ---- Reset thoi gian bat dau qui hoach quy dao khop 5-----*/
    t_count = 0;
    the_5_pre = 0;
    the_5_flex = 0;
    count_5 = 0;

    a5 = the_5_pre;
    b5 = 0;
    c5 = 3 * (the_5 - the_5_pre) / (t_command * t_command);
    d5 = -2 * (the_5 - the_5_pre) / (t_command * t_command * t_command);
    /* ---- Ket thuc ceset thoi gian bat dau qui hoach quy dao-----*/

    Timer6.start(10000);  // Kich hoach qui hoach quy dao
  }
}

void quy_hoach() // Chuong trinh phuc vu ngat cho Timer 6 (10ms)
{
  //  t_count = t_count + 0.01;     // Tang thoi gian dem (buoc 10ms)
  the_1_pre = the_1_flex;           //Luu gia tri truoc
  the_2_pre = the_2_flex;
  the_3_pre = the_3_flex;
  the_4_pre = the_4_flex;
  the_5_pre = the_5_flex;

  if (t_count < t_command)
  {
    t_count = t_count + 0.01;     // Tang thoi gian dem (buoc 10ms)
    /*=============================================================================================================================*/
    the_1_flex = a1 + b1 * t_count + c1 * (t_count * t_count) + d1 * (t_count * t_count * t_count); // Quy hoach quy dao
    count_1 = 0;        // Reset so xung da goi
    if ((the_1_flex - the_1_pre) == 0)    t_quyhoach_1 = 10000;
    else t_quyhoach_1 = round(abs(5000 / (the_1_flex - the_1_pre)));
//    Timer1.start(t_quyhoach_1);
    /*=============================================================================================================================*/
    the_2_flex = a2 + b2 * t_count + c2 * (t_count * t_count) + d2 * (t_count * t_count * t_count); // Quy hoach quy dao
    count_2 = 0;        // Reset so xung da goi
    if ((the_2_flex - the_2_pre) == 0)    t_quyhoach_2 = 10000;
    else t_quyhoach_2 = round(abs(5000 / (the_2_flex - the_2_pre)));
//    Timer2.start(t_quyhoach_2);
    /*=============================================================================================================================*/
    the_3_flex = a3 + b3 * t_count + c3 * (t_count * t_count) + d3 * (t_count * t_count * t_count); // Quy hoach quy dao
    count_3 = 0;        // Reset so xung da goi
    if ((the_3_flex - the_3_pre) == 0)    t_quyhoach_3 = 10000;
    else t_quyhoach_3 = round(abs(5000 / (the_3_flex - the_3_pre)));
//    Timer3.start(t_quyhoach_3);
    /*=============================================================================================================================*/
    the_4_flex = a4 + b4 * t_count + c4 * (t_count * t_count) + d4 * (t_count * t_count * t_count); // Quy hoach quy dao
    count_4 = 0;        // Reset so xung da goi
    if ((the_4_flex - the_4_pre) == 0)    t_quyhoach_4 = 10000;
    else t_quyhoach_4 = round(abs(5000 / (the_4_flex - the_4_pre)));
//    Timer4.start(t_quyhoach_4);
    /*=============================================================================================================================*/
    the_5_flex = a5 + b5 * t_count + c5 * (t_count * t_count) + d5 * (t_count * t_count * t_count); // Quy hoach quy dao
    count_5 = 0;        // Reset so xung da goi
    if ((the_5_flex - the_5_pre) == 0)    t_quyhoach_5 = 10000;
    else t_quyhoach_5 = round(abs(5000 / (the_5_flex - the_5_pre)));
//    Timer5.start(t_quyhoach_5);
    /*=============================================================================================================================*/
    Timer1.start(t_quyhoach_1);
    Timer2.start(t_quyhoach_2);
    Timer3.start(t_quyhoach_3);
    Timer4.start(t_quyhoach_4);
    Timer5.start(t_quyhoach_5);
  }

  if (t_count > (t_command))
  {
//        Timer6.stop();
  }
}

void serial_full()
{
  if (Serial.availableForWrite() > 20)
  {
    Serial.print(vitri_dat_1);
    Serial.print(" === ");
    Serial.print(vitri_thuc_1);
    Serial.print(" === ");
    Serial.print(the_1_flex);
    Serial.print(" === ");
    Serial.print(the_1_pre);
    Serial.print(" === ");
    Serial.print(vitri_dat_2);
    Serial.print(" === ");
    Serial.print(vitri_thuc_2);
    Serial.print(" === ");
    Serial.print(the_2_flex);
    Serial.print(" === ");
    Serial.print(the_2_pre);
    Serial.print(" === ");
    Serial.print(vitri_dat_3);
    Serial.print(" === ");
    Serial.print(vitri_thuc_3);
    Serial.print(" === ");
    Serial.print(the_3_flex);
    Serial.print(" === ");
    Serial.print(the_3_pre);
    Serial.print(" === ");
    Serial.print(vitri_dat_4);
    Serial.print(" === ");
    Serial.print(vitri_thuc_4);
    Serial.print(" === ");
    Serial.print(the_4_flex);
    Serial.print(" === ");
    Serial.print(the_4_pre);
    Serial.print(" === ");
    Serial.print(vitri_dat_5);
    Serial.print(" === ");
    Serial.print(vitri_thuc_5);
    Serial.print(" === ");
    Serial.print(the_5_flex);
    Serial.print(" === ");
    Serial.print(the_5_pre);
    Serial.print(" === ");
    Serial.print(t_count);
    Serial.print(" === ");
    Serial.println(t_command);
  }
}

void serial_quan_sat()
{
  if (Serial.availableForWrite() > 20)
  {
    Serial.print(vitri_dat_1);
    Serial.print(" === ");
    Serial.print(vitri_thuc_1);
    Serial.print(" === ");
    Serial.print(vitri_dat_2);
    Serial.print(" === ");
    Serial.print(vitri_thuc_2);
    Serial.print(" === ");
    Serial.print(vitri_dat_3);
    Serial.print(" === ");
    Serial.print(vitri_thuc_3);
    Serial.print(" === ");
    Serial.print(vitri_dat_4);
    Serial.print(" === ");
    Serial.print(vitri_thuc_4);
    Serial.print(" === ");
    Serial.print(vitri_dat_5);
    Serial.print(" === ");
    Serial.print(vitri_thuc_5);    
    Serial.print(" === ");
    Serial.println(vitri_thuc_6);
  }
}

void serial_C_sharp()
{
  delay(50);
  if (Serial.availableForWrite() > 20)
  {
    Serial.print(vitri_thuc_1);
    Serial.print(",");
    Serial.print(vitri_thuc_2);
    Serial.print(",");
    Serial.print(vitri_thuc_3);
    Serial.print(",");
    Serial.print(vitri_thuc_4);
    Serial.print(",");
    Serial.print(vitri_thuc_5);
    Serial.print(",");
    Serial.println(vitri_thuc_6);
  }
}

void loop()
{
  dk_servo6();
  serial_C_sharp();   //Goi du lieu len C sharp
}
