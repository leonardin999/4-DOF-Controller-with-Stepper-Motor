#include <AccelStepper.h>

#define gioihantraithe1 136
#define gioihanphaithe1 -136
#define gioihantrenthe2 101
#define gioihanduoithe2 15
#define gioihantrenthe3 -40
#define gioihanduoithe3 -166

#define SWthe1 10
#define SWthe2 11
#define SWthe3 12
#define BTstop 3

#define homethe1 0
#define homethe2 90
#define homethe3 -165

float gocdatthe1,gocdatthe2,gocdatthe3,vantocgocdatthe1,vantocgocdatthe2,vantocgocdatthe3;
float dthe3,thoigian;
float gochtthe1,gochtthe2,gochtthe3;    //góc đặt phải nằm trong giới hạn và vân tốc góc phải lớn lơn 10 do/s

long vitrithe1,vitrithe2,vitrithe3,vantocstepthe1,vantocstepthe2,vantocstepthe3;
bool chaythe1,chaythe2,chaythe3,newdata,ethe3;
char kitu;

#define timessqhqd 3

float the1qhqd[200];
float the2qhqd[200];
float the3qhqd[200];
int i,lengthqh;
bool eqhqd;
float timeqh;



AccelStepper stepper1(1, 4, 5); //the1       //(1 ,chân xung, chân chiều)
AccelStepper stepper2(1, 6, 7); //the2
AccelStepper stepper3(1, 8, 9); //the3

void setup() {

  Serial.begin(9600);
  pinMode(SWthe1,INPUT);            //khai báo ngõ vào cho công tắc hành trình
  pinMode(SWthe2,INPUT);
  pinMode(SWthe3,INPUT);
  pinMode(BTstop,INPUT_PULLUP);

  chaythe1 = false;
  chaythe2 = false;
  chaythe3 = false;
  
  stepper1.setAcceleration(10000);  // đặt gia tốc 10000 step/s2
  stepper2.setAcceleration(10000);
  stepper3.setAcceleration(10000);
  
  stepper1.disableOutputs();        // vô hiệu hóa động cơ step để không gây nóng
  stepper2.disableOutputs();
  stepper3.disableOutputs();
  
  stepper1.setCurrentPosition(0);   //xét vị trí bắt đầu cho 3 step = 0
  stepper2.setCurrentPosition(0);
  stepper3.setCurrentPosition(0);
  
  gochtthe1 = homethe1;                    //đặt giá trị góc khi bắt đầu, nếu làm thủ công, thì có thể kê các góc vào đúng vị trí,
  gochtthe2 = homethe2;                    //rồi sét theo giá trị thực tế
  gochtthe3 = homethe3;

  Serial.print("the1 ");
  Serial.println(gochtthe1);
  Serial.print("the2 ");
  Serial.println(gochtthe2);
  Serial.print("the3 ");
  Serial.println(gochtthe3);

  eqhqd = false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktserial()
{
  if (Serial.available() > 0)
  {
    kitu = Serial.read();
    newdata = true;
  }
  if (newdata == true)
  {
    newdata = false;
    if (kitu == 'v')
    {
      gocdatthe1 = Serial.parseFloat();
      vantocgocdatthe1 = Serial.parseFloat();
      gocdatthe2 = Serial.parseFloat();
      vantocgocdatthe2 = Serial.parseFloat();
      gocdatthe3 = Serial.parseFloat();
      vantocgocdatthe3 = Serial.parseFloat();
    
      ktgiatridatthe1_theovantoc();
      ktgiatridatthe2_theovantoc();
      ktgiatridatthe3_theovantoc();
    }
    else if (kitu == 't')
    {
      thoigian = Serial.parseFloat();
      gocdatthe1 = Serial.parseFloat();
      gocdatthe2 = Serial.parseFloat();
      gocdatthe3 = Serial.parseFloat();


      ktgiatridatthe1_theothoigian();
      ktgiatridatthe2_theothoigian();
      ktgiatridatthe3_theothoigian();
    }
    else if (kitu == 'd')
    {
      Serial.print("the1 ");
      Serial.println(gochtthe1);
      Serial.print("the2 ");
      Serial.println(gochtthe2);
      Serial.print("the3 ");
      Serial.println(gochtthe3);
    }
    else if (kitu == 'b')
    {
      lengthqh = Serial.parseFloat();
      timeqh = Serial.parseFloat();
      for (i=0;i<lengthqh;i++)
      {
        the1qhqd[i] = Serial.parseFloat();
      }
      for (i=0;i<lengthqh;i++)
      {
        the2qhqd[i] = Serial.parseFloat();
      }
      for (i=0;i<lengthqh;i++)
      {
        the3qhqd[i] = Serial.parseFloat();
      }

      thoigian = timessqhqd;
      gocdatthe1 = the1qhqd[0];
      gocdatthe2 = the2qhqd[0];
      gocdatthe3 = the3qhqd[0];

      ktgiatridatthe1_theothoigian();
      ktgiatridatthe2_theothoigian();
      ktgiatridatthe3_theothoigian();
      
      i = 1;
      eqhqd = true;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktgiatridatthe1_theovantoc()
{
  stepper1.setCurrentPosition(0);
  if ((gocdatthe1 <= gioihantraithe1) && (gocdatthe1 >= gioihanphaithe1) && (gocdatthe1 != gochtthe1) && (vantocgocdatthe1 >= 10))    //vận tốc đơn vị là (độ/s)
  {
    vitrithe1 = long((gocdatthe1 - gochtthe1)*80/9);
    if (vitrithe1 != 0)
    {
      vantocstepthe1 = abs(long(vantocgocdatthe1*80/9));
      stepper1.enableOutputs();
      stepper1.setMaxSpeed(vantocstepthe1);
      stepper1.move(vitrithe1);
      chaythe1 = true;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktgiatridatthe2_theovantoc()
{
  stepper2.setCurrentPosition(0);
  dthe3 = 0;
  if ((gocdatthe2 <= gioihantrenthe2) && (gocdatthe2 >= gioihanduoithe2) && (vantocgocdatthe2 >= 10) && (gocdatthe2 != gochtthe2))
  {
    vitrithe2 = long((gocdatthe2 - gochtthe2)*760/33);
    if (vitrithe2 != 0)
    {    
      dthe3 = gocdatthe2 - gochtthe2;
      vantocstepthe2 = abs(long(vantocgocdatthe2*760/33));
      stepper2.enableOutputs();
      stepper2.setMaxSpeed(vantocstepthe2);
      stepper2.move(vitrithe2);
      chaythe2 = true;
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktgiatridatthe3_theovantoc()
{
  stepper3.setCurrentPosition(0);
  if ((dthe3 == 0) && (gocdatthe3 == gochtthe3))
    ethe3 = false;
  else
    ethe3 = true;
    
  if ((gocdatthe3 <= gioihantrenthe3) && (gocdatthe3 >= gioihanduoithe3) && (vantocgocdatthe3 >= 10) && (ethe3 == true))
  {
    vitrithe3 = long((gocdatthe3 - (gochtthe3 - dthe3))*760/33);
    if (vitrithe3 != 0)
    { 
      vantocstepthe3 = abs(long(vantocgocdatthe3*760/33));
      stepper3.enableOutputs();
      stepper3.setMaxSpeed(vantocstepthe3);
      stepper3.move(vitrithe3);
      chaythe3 = true;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktgiatridatthe1_theothoigian()
{
  stepper1.setCurrentPosition(0);
  if ((gocdatthe1 <= gioihantraithe1) && (gocdatthe1 >= gioihanphaithe1) && (gocdatthe1 != gochtthe1))   
  {
    vitrithe1 = long((gocdatthe1 - gochtthe1)*80/9);
    if (vitrithe1 != 0)
    { 
      vantocstepthe1 = abs(long(vitrithe1/thoigian));
      stepper1.enableOutputs();
      stepper1.setMaxSpeed(vantocstepthe1);
      stepper1.move(vitrithe1);
      chaythe1 = true;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktgiatridatthe2_theothoigian()
{
  stepper2.setCurrentPosition(0);
  dthe3 = 0;
  if ((gocdatthe2 <= gioihantrenthe2) && (gocdatthe2 >= gioihanduoithe2) && (gocdatthe2 != gochtthe2))
  {    
    vitrithe2 = long((gocdatthe2 - gochtthe2)*760/33);
    if (vitrithe2 != 0)
    {    
      dthe3 = gocdatthe2 - gochtthe2;
      vantocstepthe2 = abs(long(vitrithe2/thoigian));
      stepper2.enableOutputs();
      stepper2.setMaxSpeed(vantocstepthe2);
      stepper2.move(vitrithe2);
      chaythe2 = true;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktgiatridatthe3_theothoigian()
{
  stepper3.setCurrentPosition(0);
  if ((dthe3 == 0) && (gocdatthe3 == gochtthe3))
    ethe3 = false;
  else
    ethe3 = true;
  if ((gocdatthe3 <= gioihantrenthe3) && (gocdatthe3 >= gioihanduoithe3) && (ethe3 == true))
  {
    vitrithe3 = long((gocdatthe3 - (gochtthe3 - dthe3))*760/33);
    if (vitrithe3 != 0)
    {   
      vantocstepthe3 = abs(long(vitrithe3/thoigian));
      stepper3.enableOutputs();
      stepper3.setMaxSpeed(vantocstepthe3);
      stepper3.move(vitrithe3);
      chaythe3 = true;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktchaythe1()
{
  if (chaythe1 == true)
  {
    if (stepper1.currentPosition() != vitrithe1 )
    {
      stepper1.run();
    }
    else
    {  
      chaythe1 = false;
      stepper1.disableOutputs();  
      gochtthe1 = gochtthe1 + stepper1.currentPosition()*0.1125*vitrithe1/vitrithe1;
      Serial.print("the1 ");
      Serial.println(gochtthe1);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktchaythe2()
{
  if (chaythe2 == true)
  {
    if (stepper2.currentPosition() != vitrithe2 )
    {
      stepper2.run();
    }
    else
    {  
      chaythe2 = false;
      stepper2.disableOutputs();  
      gochtthe2 = gochtthe2 + stepper2.currentPosition()*0.04342*vitrithe2/vitrithe2;
      Serial.print("the2 ");
      Serial.println(gochtthe2);

      if (stepper3.currentPosition()== 0)
      {
          gochtthe3 = gochtthe3 - dthe3;
          Serial.print("the3 ");
          Serial.println(gochtthe3);
      }
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktchaythe3()
{
  if (chaythe3 == true)
  {
    if (stepper3.currentPosition() != vitrithe3 )
    {
      stepper3.run();
    }
    else
    {  
      chaythe3 = false;
      stepper3.disableOutputs();  
      gochtthe3 = gochtthe3 - dthe3 + stepper3.currentPosition()*0.04342*vitrithe3/vitrithe3;
      Serial.print("the3 ");
      Serial.println(gochtthe3);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktstop()
{
  if (((digitalRead(BTstop)) == 0)||(kitu == 'p'))
  {
    if (kitu == 'p')
      kitu = '0';
    eqhqd = false;
    if (chaythe1 == true)
    {
      chaythe1 = false;
      stepper1.disableOutputs();  
      gochtthe1 = gochtthe1 + stepper1.currentPosition()*0.1125*vitrithe1/vitrithe1;
      Serial.print("the1 ");
      Serial.println(gochtthe1);
    }
    if (chaythe2 == true)
    {
      chaythe2 = false;
      stepper2.disableOutputs();  
      gochtthe2 = gochtthe2 + stepper2.currentPosition()*0.04342*vitrithe2/vitrithe2;
      Serial.print("the2 ");
      Serial.println(gochtthe2);

      if (stepper3.currentPosition()==0)
      {
        gochtthe3 = gochtthe3 - stepper2.currentPosition()*0.04342*vitrithe2/vitrithe2;
        Serial.print("the3 ");
        Serial.println(gochtthe3);
      }
    }
    if (chaythe3 == true)
    {
      chaythe3 = false;
      stepper3.disableOutputs();  
      gochtthe3 = gochtthe3 - stepper2.currentPosition()*0.04342*vitrithe2/vitrithe2 + stepper3.currentPosition()*0.04342*vitrithe3/vitrithe3;
      Serial.print("the3 ");
      Serial.println(gochtthe3);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ktgiatridattheqhqd()
{
  if ((chaythe1 == false) && (chaythe2 == false) && (chaythe3 == false))
  {
    if (i < lengthqh)
    {
      ///////////////////////////////////////////////////////////////////  
      thoigian = timeqh;
      gocdatthe1 = the1qhqd[i];
      gocdatthe2 = the2qhqd[i];
      gocdatthe3 = the3qhqd[i];
      
      ktgiatridatthe1_theothoigian();
      ktgiatridatthe2_theothoigian();
      ktgiatridatthe3_theothoigian();
      ///////////////////////////////////////////////////////////////////
      i++;
    }
    else
    {
      thoigian = timessqhqd;
      gocdatthe1 = homethe1;
      gocdatthe2 = homethe2;
      gocdatthe3 = homethe3;
      
      ktgiatridatthe1_theothoigian();
      ktgiatridatthe2_theothoigian();
      ktgiatridatthe3_theothoigian();
      
      eqhqd = false;
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  ktserial();
  ktstop();
  ktchaythe1();
  ktchaythe2();
  ktchaythe3();
  if (eqhqd == true)
  {
    ktgiatridattheqhqd();
  }
}
