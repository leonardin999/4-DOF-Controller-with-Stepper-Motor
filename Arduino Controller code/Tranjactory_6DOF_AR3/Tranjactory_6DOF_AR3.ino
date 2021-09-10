#include <DueTimer.h>

const int  pulse_1 = 22; 
const int dir_1 = 2; 

const int pulse_2 =24; 
const int dir_2 = 3; 

const int pulse_3 = 26; 
const int dir_3 = 4; 

const int pulse_4 = 28; //TRANG
const int dir_4 = 5;    //DEN
const int enPin_4 = 30;  // DO GND:nau

const int pulse_5 = 32; 
const int dir_5 = 6; 
const int enPin_5 = 34; 

const int pulse_6 = 36; 
const int dir_6 = 7;
const int enPin_6 = 38; 

long v1 = 0, v2 = 0, v3 = 0 ,v4 = 0, v5 = 0, v6 = 0;

long the1_pre, the2_pre, the3_pre ,the4_pre, the5_pre, the6_pre;
long the1_flex, the2_flex, the3_flex,the4_flex, the5_flex, the6_flex;
long the1, the2, the3,the4, the5 , the6;
int a=0, b=0, c=0;

//float  tam1 =  3969  ;
//float  tam2 =289 ;
//float tam3 = tam1/tam2 ;
float   vt1 = 0 ,  vt2= 0, vt3=0 ,vt4=0 ,vt5=0 , vt6=0 ; 
float vtmm1,vtmm2 ,vtmm3 ,vtmm4,vtmm5,vtmm6, t_int ,tc, abc;
float z1,z2,z3,z4,z5,z6;
float a1,a2,a3,a4,a5,a6,c1,c2,c3,c4,c5,c6,b1,b2,b3,b4,b5,b6,d1,d2,d3,d4,d5,d6;
float delta1, delta2, delta3;
double gt1, gt2, gt3;
double n1, n2, n3, tp1, tp2, tp3;

void setup() 
 {
 // Serial.begin(9600);
 Serial.setTimeout(50);
 Serial.begin(9600);
 while (!Serial) 
 {
    ; // wait for serial port to connect. Needed for native USB port only
 }


  vtmm1=0;
  vtmm2=0;
  vtmm3=0;
  vtmm4=0;
  vtmm5=0;
  vtmm6=0;
  pinMode(pulse_1,OUTPUT); 
  pinMode(dir_1,OUTPUT);
 
  pinMode(pulse_2,OUTPUT); 
  pinMode(dir_2,OUTPUT);

  pinMode(pulse_3,OUTPUT); 
  pinMode(dir_3,OUTPUT);

  pinMode(pulse_4,OUTPUT);
  pinMode(dir_4,OUTPUT);
  pinMode(enPin_4,OUTPUT);
  digitalWrite(enPin_4,LOW);

  pinMode(pulse_5,OUTPUT); 
  pinMode(dir_5,OUTPUT);
  pinMode(enPin_5,OUTPUT);
  digitalWrite(enPin_5,LOW);
  
  pinMode(pulse_6,OUTPUT); 
  pinMode(dir_6,OUTPUT);
  pinMode(enPin_6,OUTPUT);
  digitalWrite(enPin_6,LOW);

//  Timer5.initialize(100000);
//  Timer5.attachInterrupt(qhqd);
//  Timer5.stop();

  Timer5.attachInterrupt(quyhoach).start(100000);
  Timer5.stop();
}
void quyhoach ()
{

  t_int++;
  //Serial.println(abc);
  the1_pre = the1_flex;   // luu gia tri
  the2_pre = the2_flex;
  the3_pre = the3_flex;
  the4_pre = the4_flex;
  the5_pre = the5_flex;
  the6_pre = the6_flex;
  // tinh toan qui hoach qui dao va dong toc do
  if(t_int > (abc))
  { 
//     Serial.println("Done");
//     delay(50);
//       Serial.println(t_int);
   
    
    if (the2_flex - the2_pre == 0) 
    v2 = 100000;
    else 
    v2 = (100000/abs(the2_flex - the2_pre)-5);
    
    if (the3_flex - the3_pre == 0) 
    v3 = 100000;
    else 
    v3 = (100000/abs(the3_flex - the3_pre)-5);
    
    if (the4_flex - the4_pre == 0)
    v4 = 100000;
    else 
    v4 = (100000/abs(the4_flex - the4_pre)-5);
    
    if (the5_flex - the5_pre == 0) 
    v5 = 100000;
    else 
    v5 = (100000/abs(the5_flex - the5_pre)-5);
    
    if (the6_flex - the6_pre == 0) 
    v6 = 100000;
    else 
    v6 = (100000/abs(the6_flex - the6_pre)-5);
    // khai báo timer
   
    Timer1.attachInterrupt(step1).start(v1);
    
    Timer2.attachInterrupt(step2).start(v2);
    
    Timer3.attachInterrupt(step3).start(v3);

    Timer4.attachInterrupt(step4).start(v4);
    
    Timer6.attachInterrupt(step5).start(v5);
    
    Timer7.attachInterrupt(step6).start(v6);
    
    Timer1.start();
    Timer2.start();
    Timer3.start();
    Timer4.start();
    Timer6.start();
    Timer7.start();
  }  

  }
void step1()
{ 
  
  if(the1_flex - the1_pre>0) // so sánh để chọn chiều quay step
   {
    digitalWrite(dir_1,HIGH); // cho phep step di theo chieu qui dinh 
    delta1 = the1_flex - the1_pre + tp1;
    tp1 = modf(delta1, &n1);
    if(delta1 < 1)
    {}
    else
    {
      if(a<(n1))
      {
        digitalWrite(pulse_1,!digitalRead(pulse_1));
        a++;
        vt1++;
      }
      else 
      {
        Timer1.stop();
      }
    }
   }
  else
   {
    digitalWrite(dir_1,LOW); // cho phep step di theo chieu qui dinh
    delta1 = the1_flex - the1_pre + tp1;
    tp1 = modf(delta1, &n1);
    if(abs(delta1) < 1)
    {}
    else
    {
      if(a<abs(n1))
      {
        digitalWrite(pulse_1,!digitalRead(pulse_1));
        a++;
        vt1--;
      }
      else 
      {
        Timer1.stop();
      }
    }
   }
}

void step2()
{ 
  if(the2_flex - the2_pre>0)// so sánh để chọn chiều quay step
   {
    digitalWrite(dir_2,HIGH); // cho phep step di theo chieu qui dinh 
    delta2 = the2_flex - the2_pre + tp2;
    tp2 = modf(delta2, &n2);
    if(delta2 < 1)
    {}
    else
    {
      if(b<(n2))
      {
        digitalWrite(pulse_2,!digitalRead(pulse_2));
        b++;
        vt2++;
      }
      else 
      {
        Timer2.stop();
        delta2 = 0;
      }
    }
   }
  else
   {
    digitalWrite(dir_2,LOW); // cho phep step di theo chieu qui dinh 
    delta2 = the2_flex - the2_pre + tp2;
    tp2 = modf(delta2, &n2);
    if(abs(delta2) < 1)
    {}
    else
    {
      if(b<abs(n2))
      {
        digitalWrite(pulse_2,!digitalRead(pulse_2));
        b++;
        vt2--;
      }
      else 
      {
        Timer3.stop();
        delta2 = 0;
      }
    }
   }
}
void step3()
{ 
  if(the3_flex - the3_pre>0)// so sánh để chọn chiều quay step
   {
    digitalWrite(dir_3,LOW); // cho phep step di theo chieu qui dinh 
    if(c<=(the3_flex - the3_pre))
    {
      digitalWrite(pulse_3,!digitalRead(pulse_3));
      c++;
      vt3++;
    }
    else 
    {
      Timer3.stop();
    }
   }
  else
   {
    digitalWrite(dir_3,HIGH); // cho phep step di theo chieu qui dinh 
    if(c<=abs((the3_flex - the3_pre)))
    {
      digitalWrite(pulse_3,!digitalRead(pulse_3));
      c++;
      vt3--;
    }
    else 
    {
      Timer3.stop();
    }
   }
}

void step4()
{ 
  if(the4_flex - the4_pre>0)// so sánh để chọn chiều quay step
   {
    digitalWrite(dir_4,HIGH); // cho phep step di theo chieu qui dinh 
    if(c<=(the4_flex - the4_pre))
    {
      digitalWrite(pulse_4,!digitalRead(pulse_4));
      c++;
      vt4++;
    }
    else 
    {
      Timer4.stop();
    }
   }
  else
   {
    digitalWrite(dir_4,LOW); // cho phep step di theo chieu qui dinh 
    if(c<=abs((the4_flex - the4_pre)))
    {
      digitalWrite(pulse_4,!digitalRead(pulse_4));
      c++;
      vt4--;
    }
    else 
    {
      Timer4.stop();
    }
   }
}

void step5()
{ 
  if(the5_flex - the5_pre>0)// so sánh để chọn chiều quay step
   {
    digitalWrite(dir_5,HIGH); // cho phep step di theo chieu qui dinh 
    if(c<=(the5_flex - the5_pre))
    {
      digitalWrite(pulse_5,!digitalRead(pulse_5));
      c++;
      vt5++;
    }
    else 
    {
      Timer6.stop();
    }
   }
  else
   {
    digitalWrite(dir_5,LOW); // cho phep step di theo chieu qui dinh 
    if(c<=abs((the5_flex - the5_pre)))
    {
      digitalWrite(pulse_5,!digitalRead(pulse_5));
      c++;
      vt5--;
    }
    else 
    {
      Timer6.stop();
    }
   }
}

void step6()
{ 
  if(the6_flex - the6_pre>0)// so sánh để chọn chiều quay step
   {
    digitalWrite(dir_6,LOW); // cho phep step di theo chieu qui dinh 
    if(c<=(the6_flex - the6_pre))
    {
      digitalWrite(pulse_6,!digitalRead(pulse_6));
      c++;
      vt6++;
    }
    else 
    {
      Timer7.stop();
    }
   }
  else
   {
    digitalWrite(dir_6,HIGH); // cho phep step di theo chieu qui dinh 
    if(c<=abs((the6_flex - the6_pre)))
    {
      digitalWrite(pulse_6,!digitalRead(pulse_6));
      c++;
      vt6--;
    }
    else 
    {
      Timer7.stop();
    }
   }
}

void  recieve()
  {
   int j=0,k[7];
 String symbol ;
 String readStringt;
 float y1,y2,y3,y4,y5,y6,tc;
char buffer[50]= {}; 
// while(Serial.available())
// {
  if(Serial.available()>0)
   {

     Serial.readBytes(buffer,50);// s1 is String type variable.
     String data = buffer;
    int lengthdata = data.length();
   // Serial.println(symbolw);
    for (int i=0 ; i< lengthdata ; i++ )
    {
          symbol = data.charAt(i);
          
          if( symbol.equals(",") == true )
          { 
              k[j]=i+1;
             j++;
            }
      }
      String  x1 = data.substring(0,k[0]);
      String  x2 = data.substring(k[0],k[1]);
      String  x3 = data.substring(k[1],k[2]);
      String  x4 = data.substring(k[2],k[3]);
      String  x5 = data.substring(k[3],k[4]);
      String  x6 = data.substring(k[4],k[5]);
      String  x7 = data.substring(k[5],lengthdata);
        y1=x1.toFloat();
        y2=x2.toFloat();
        y3=x3.toFloat();
        y4=x4.toFloat();
        y5=x5.toFloat();
        y6=x6.toFloat();
        tc=x7.toFloat();

//        Serial.println(y1);
//        Serial.println(y2);
//        Serial.println(y3);
//        Serial.println(tc);
         
     
      z1 =(y1*(3600*30 )/360); // 1800*2 ( 1800 set trong driver)
      z2 =(y2*(3600*400 )/360) ; 
      z3 = (y3*(4000*10 )/(360));
      z4 = (y4*(800*4*3696/289)/360);
      z5 = (y5*(800*2*2*3696/289)/360);   
      z6 = (y6*(4000*12 )/360);
      abc=tc*10;
       
      vtmm1=(z1-vt1);
      vtmm2=(z2-vt2);
      vtmm3=(z3-vt3);
      vtmm4=(z4-vt4);
      vtmm5=(z5-vt5);
      vtmm6=(z6-vt6);
  
   the1 = vtmm1;
   the2 = vtmm2;
   the3 = vtmm3;
   the4 = vtmm4;
   the5 = vtmm5;
   the6 = vtmm6;
   the1_pre = 0, the2_pre = 0, the3_pre = 0 ,the4_pre = 0, the5_pre = 0, the6_pre = 0;
   t_int = 0;
   the1_flex = 0, the2_flex = 0, the3_flex = 0,the4_flex = 0, the5_flex = 0, the6_flex = 0;
  
   a1 = the1_pre;
   b1 = 0;
   c1 = 3*(the1 - the1_pre)/pow(tc,2);
   d1 = -2*(the1 - the1_pre)/pow(tc,3);
    
   a2 = the2_pre;
   b2 = 0;
   c2 = 3*(the2 - the2_pre)/pow(tc,2);
   d2 = -2*(the2 - the2_pre)/pow(tc,3);
   
   a3 = the3_pre;
   b3 = 0;
   c3 = 3*(the3 - the3_pre)/pow(tc,2);
   d3 = -2*(the3 - the3_pre)/pow(tc,3);

   a4 = the4_pre;
   b4 = 0;
   c4 = 3*(the4 - the4_pre)/pow(tc,2);
   d4 = -2*(the4 - the4_pre)/pow(tc,3);
  
   a5 = the5_pre;
   b5 = 0;
   c5 = 3*(the5 - the5_pre)/pow(tc,2);
   d5 = -2*(the5 - the5_pre)/pow(tc,3);

   a6 = the6_pre;
   b6 = 0;
   c6 = 3*(the6 - the6_pre)/pow(tc,2);
   d6 = -2*(the6 - the6_pre)/pow(tc,3);

      Timer5.start(); 
//    Serial.println(y1);
//    Serial.println(y2);
//    Serial.println(y3);
//    Serial.println(tc);

    }
  }
void loop() 
{  
 recieve();   
//  String s,p;
//  float vt1x ,vt2x ,vt3x ;
//  vt1x =(vt1*360)/(10000*2) ;
//  vt2x =(vt2*360)/(800*13.73*2*4*1.5 ) ;
//  vt3x =(vt3*360)/(800*13.73*2*4*1.5 ) ;
//  p = " " ;
//  p= p+"*";
//  p= p+ vt1x ;
//   //p= p+ vt1;
//  p= p+"*";
//p= p+ vt2x  ;
//   //p= p+ vt2;
//  p= p+"*";
//  p= p+ vt3x  ;
// // p= p+ vt3;
//  p= p+"*";
//  s = p ;
  Serial.print(vt1);
  Serial.print(" ");
  Serial.print(vt2);
  Serial.print(" ");
  Serial.print(vt3);
  Serial.print(" ");
  Serial.print(vt4);
  Serial.print(" ");
  Serial.print(vt5);
  Serial.print(" ");
  Serial.println(vt6);
  Serial.print(" ");
  delay(100);
  
}
