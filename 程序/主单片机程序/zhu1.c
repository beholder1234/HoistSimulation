#include "reg51.h"
#define uchar unsigned char
sfr Seg=0x80;
sfr Motor=0xa0;
sfr Signal=0xb0;
sbit OpenDoor=P1^0;
sbit CloseDoor=P1^1;
sbit Warning=P1^2;
sbit UP=P1^3;
sbit DOWN=P1^4;
sbit Switch=P1^5;
sbit OverWeight=P1^6;
sbit beep=P1^7;

char SegArray[]={0xff,0xf9,0xa4,0xb0,0x99,0x92};	 //楼层显示数码管数组,0项数值作用，目的让项数和桥厢位置变量(Location)对应

char DoorRun[4]={0x40,0x80,0x10,0x20};  //门系统四相四拍工作方式  反转（关门）
char DoorRun1[4]={0x20,0x10,0x80,0x40}; //                        正转（开门）

char HoistRun[4]={0x04,0x08,0x01,0x02};  //起重机四相四拍工作方式  反转（下行）
char HoistRun1[4]={0x02,0x01,0x08,0x04}; //                        正转（上行）

char HoistControlArray[]={0xf0,0xf1,0xf2,0xf3,
                          0xf4,0xf5,0xf6,0xf7,
					      0xf8,0xf9,0xfa,0xfb,
				       	  0xfc,0xfd,0xfe,0xff};
char Zhu_AcceptSaveArray[]={0xFf};					//只要底四位，在判断是会左移四位变成高四位

char LampControlArray[]={0x0f,0x1f,0x2f,0x3f,
                         0xcf,0xbf,0xaf,0x9f};


char Zhu_SentSaveArray[2]={0x0f};	     //	因初始状态Way=0 Location=1，所以为0x0f 
char Location=1,Way=0,Layer=0,DoorStatus=0;    //DoorStatus 1表门开着，0表门关着   
void Zhu_Status();
void Zhu_RequestSent();
void delay1ms(void) 
{	  
	   unsigned char a,b,c;
	   for(c=10;c>0;c--)
	        for(b=42;b>0;b--)
	             for(a=2;a>0;a--);	             
}

void delay100ms(void)        //门关闭或开启完成后，用1s分十次，每次均判断是否有，开门，关门，警报，平层按键要求
{
    unsigned char a,b,c;
    for(c=19;c>0;c--)
        for(b=20;b>0;b--)
            for(a=130;a>0;a--);
}
void delay62ms500us(void)   //误差 0us
{
    unsigned char a,b;
    for(b=224;b>0;b--)
        for(a=138;a>0;a--);
}

void delay31ms250us(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=2;c>0;c--)
        for(b=220;b>0;b--)
            for(a=34;a>0;a--);
}

void delay20ms825us(void)   //误差 0us
{
    unsigned char a,b;
    for(b=58;b>0;b--)
        for(a=178;a>0;a--);
}


void delay300ms(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=5;c>0;c--)
        for(b=212;b>0;b--)
            for(a=140;a>0;a--);
}
void delay2s(void)   //门开启后等待两秒（用户进出）
{
    unsigned char a,b,c;
    for(c=127;c>0;c--)
        for(b=235;b>0;b--)
            for(a=32;a>0;a--);
}
void SwitchJudge()
{
while(1)
    {
	 if(Switch==0)
	     break;
	
	
	}
}
void ArriveSound()					         	 // 到达蜂鸣子程序
{ 

    unsigned char a,b,c;
        for(c=3;c>0;c--)
            for(b=2;b>0;b--)
                for(a=10;a>0;a--)
					{
			 		 beep=~beep;
	 	    		 delay1ms();
					}			 

}


void OverWeightSound()
{
while(OverWeight==0)
    {
	beep=~beep;
	delay1ms();	 	
	}
}
void The_Lamp_Of_Way()
{
if(Way==0 && Layer!=0)
    {
    UP=1;
	DOWN=0;
	}
else if(Way==4 && Layer!=0)
    {
	UP=0;
	DOWN=1;	
	}
else if(Layer==0)
    {
	 UP=0;
	 DOWN=0;	
	}
} 
void Judge()									// 对位移楼层数（Layer）和方向（Way）进行判断
{
switch(Zhu_AcceptSaveArray[0]<<4)					 //<<:左移补0    >>:右移补0(注：先用 << 再用 >> 位移数相同，值不变，因cpu将左移数储存起来了)
	{
	case 0x00:
	    {
	     if((Layer=Location-1)>0) Way=4;
		 else {Way=0;}			 
		 break;
	    }

    case 0x10:
	    {
		if((Layer=Location-2)>0) Way=4;
		else {Layer=2-Location;Way=0;}
		break;
		}
	case 0x20:
	    {
		if((Layer=Location-3)>0) Way=4;
		else {Layer=3-Location;Way=0;}
		break;
		}
	case 0x30:
	    {
		if((Layer=Location-4)>0) Way=4;
		else {Layer=4-Location;Way=0;}
		break;
		}
	case 0x40:
	    {
		if((Layer=5-Location)>0) Way=0;
		else Way=4;
		break;
		}
	case 0x50:
	    {
		if((Layer=4-Location)>0) Way=0;
		else {Layer=Location-4;Way=4;}
		break;
		}
	case 0x60:
	    {
		if((Layer=3-Location)>0) Way=0;
		else {Layer=Location-3;Way=4;}
		break;
		}
	case 0x70:
	    {
		if((Layer=2-Location)>0) Way=0;
		else {Layer=Location-2;Way=4;}
		break;
		}
	case 0x80:
	    {
		Layer=0;
		
		
		}
	}

//Seg=(Zhu_AcceptSaveArray[0]<<4);
//Seg=HoistControlArray[Location];
}

void HoistSpeed1(char Way)					 //电机0m/s--0.5m/s间 加速或减速行驶子程序（加速度 0.75）
{
char time,rotate; 					 // time: 电机循环次数	rotate：电机正反转数组循环
	if(Warning==0)
	   {
	  	Switch=1;
		while(1)
		    {
		     beep=~beep;
	         delay1ms();
		    }
	   }
switch(Way)
    {							 // Way:正反转判断	0 正传，否则 反转
    case 0:
	     {
         for(time=0;time<2;time++)
             for(rotate=0;rotate<4;rotate++)
                 {
		          Motor=HoistRun1[rotate];
	              delay62ms500us();			 
	             }
	     break;
	     }
	default :
	     {
	     for(time=0;time<2;time++)
             for(rotate=0;rotate<4;rotate++)
                 {
		          Motor=HoistRun[rotate];
	              delay62ms500us();	
	             }
	     }
    }
}


void HoistSpeed2(char Way)					 // 电机 0.5m/s--1.0m/s间 加速或减速行驶子程序（加速度 0.75）
{
char time,rotate;
	if(Warning==0)
	   {
	  	Switch=1;
		while(1)
		    {
		     beep=~beep;
	         delay1ms();
		    }
	   } 
switch(Way)
    {
    case 0:
	     {
         for(time=0;time<4;time++)
             for(rotate=0;rotate<4;rotate++)
             {
		         Motor=HoistRun1[rotate];
	             delay31ms250us();				 
	         }
		 break;
	     }
    default:
	     {
         for(time=0;time<4;time++)
             for(rotate=0;rotate<4;rotate++)
             {
		         Motor=HoistRun[rotate];
	             delay31ms250us();				 
	         }
	     }
    }
}
void HoistSpeed3(char Way)					  //电机 1.0m/s--1.5m/s间 加速或减速行驶子程序（加速度 0.75）
{
char time,rotate;
	if(Warning==0)
	   {
	  	Switch=1;
		while(1)
		    {
		     beep=~beep;
	         delay1ms();
		    }
	   }
switch(Way)
    {
    case 0:
	     { 
              for(time=0;time<6;time++)
                  for(rotate=0;rotate<4;rotate++)
                  {
		              Motor=HoistRun1[rotate];
	                  delay20ms825us();
	              }
		 break;
		 }
    default:
	     { 
              for(time=0;time<6;time++)
                  for(rotate=0;rotate<4;rotate++)
                  {
		              Motor=HoistRun[rotate];
	                  delay20ms825us();
	              }
		 }
    }
}
void HoistSpeed4(char Way,char Special_One,char Special_Two )	  // 1.5m/s 匀速行驶子程序（加速度 0）  （注：此为0.5s的匀速行驶）
{
char time,rotate;
	if(Warning==0)
	   {
	  	Switch=1;
		while(1)
		    {
		     beep=~beep;
	         delay1ms();
		    }
	   }
switch(Way)
    {

    case 0:
	     { 
              for(time=0;time<6;time++)
                  for(rotate=0;rotate<4;rotate++)
                  {
		              Motor=HoistRun1[rotate];
	                  delay20ms825us();
					  if(Layer!=1 && Special_Two==1 && Special_One==3 && time*rotate==12 )		  //桥厢位置确定
					      {
					      Seg=SegArray[++Location];
						  Special_One=0;
						  Special_Two=0;

						  }	
	              }
		 break;
		 }
    default:
	     { 
              for(time=0;time<6;time++)
                  for(rotate=0;rotate<4;rotate++)
                  {
		              Motor=HoistRun[rotate];
	                  delay20ms825us();
					  if(Layer!=1 && Special_Two==1 && Special_One==3 && time*rotate==12 )
					      {
					      Seg=SegArray[--Location];
						  Special_One=0;
						  Special_Two=0;

						  }	
	              }
		 }
    }
}


void Hoist()					// 起重电机控制子程序	 
{											   // Layer:桥厢位移层数 Way:正反转判断
char i;                                        // i:匀速子程序循环次数 (根据行进层数改变次数 i=3+6*(层数-1)；  )
char Special_One=0,Special_Two=1;			   //Special：当桥厢位移层数大于一时，为实时确定桥厢位置，所以存在的变量
The_Lamp_Of_Way();
HoistSpeed1(Way);							   
HoistSpeed2(Way);
HoistSpeed3(Way);
for(i=0;i<3+6*(Layer-1);i++)
    {
	//Seg=HoistControlArray[6*(Layer-1)];
    HoistSpeed4(Way,Special_One,Special_Two);
	Special_One++;						//只有在第一次桥厢位置加（减）一确定时，此语句有用。其余位置加（减）一确定由if(i!=3 && (i-3)%6==0)确定
	if(i%3==0)									//每当电梯匀速运行1.5秒，从新扫描一次接收引脚，看最高优先级是否改变；
	    {
		if((Signal<<4) ^ (Zhu_AcceptSaveArray[0]<<4))
		    {
			//Seg=HoistControlArray[Location];
		    Zhu_AcceptSaveArray[0]=Signal;
			Judge();

			}
		if(i!=3 && (i-3)%6==0)					//例：当位移层数为三时，桥厢加速1.125m（1.5s），再匀速2.25m+1.125m（即1.5s+0.75s），
		    {									//桥厢位置加（减）一（此为第一次桥厢确定）。之后匀速4.5m（即3s），桥厢位置加（减）一。
												//再之后匀速4.5m（即3s），再减速1.125m（1.5s），桥厢位置加（减）一。
			Special_Two=1;					    //i！=3:保证在第二次（或以上）桥厢位置确定时生效，
			Special_One=3;						//(i-3)%6==0：保证在第一次桥厢确定后，第一次匀速4.5m时，桥厢位置加（减）一（对于位移层为三的）
			}		    						//(i-3)%6==0：保证在第一次桥厢确定后，第一（二）次匀速4.5m时，桥厢位置加（减）一（对于位移层为三四的）
		}
	//Seg=HoistControlArray[Layer];
	}
HoistSpeed3(Way);
HoistSpeed2(Way);
HoistSpeed1(Way);
SwitchJudge();
//Seg=HoistControlArray[6*(Layer-1)];
ArriveSound();
Zhu_Status();
if(Way==0)
    Seg=SegArray[++Location];
else
    Seg=SegArray[--Location];    
}

void DoorOpen()
{
char z;
    for(z=0;z<8;z++)
        {
        Motor=DoorRun1[z%4];
        delay300ms();
        }

}
void DoorClose()
{
char z;
    if(DoorStatus==1)
        for(z=0;z<8;z++)
            {
             Motor=DoorRun[z%4];
             delay300ms();
            }
}
void IndoorRequest(char Long)
{
char i;					//DoorStatus 1表门开着，0表门关着
for(i=0;i<Long;i++)
    {
	OverWeightSound();
	if(Warning==0)
	   {
	  	Switch=1;
		while(1)
		    {
		     beep=~beep;
	         delay1ms();
		    }
	   }
	if(OpenDoor==0  && DoorStatus==1)
	   {
	    Signal=0x4f; 
	   }
	if(CloseDoor==0  && DoorStatus==0)
	   {
	    Signal=0x5f; 
	   }
	if(OpenDoor==0 && DoorStatus==0)
	   {
	   DoorOpen();
	   Signal=0x4f;
	   DoorStatus=1;
	   }
	if(CloseDoor==0 && DoorStatus==1)
	   {
	   DoorClose();
	   Signal=0x5f;
	   DoorStatus=0;
	   }
	delay100ms();
	}
}
void Door()
{
DoorOpen();
DoorStatus=1;
IndoorRequest(20);
DoorClose();
DoorStatus=0;
IndoorRequest(2);
}
void Zhu_RequestSent()
{												   //四位发送信号位，最左位：上下行 ，右三位：桥厢位置
if(Location==1 )
    {
	Zhu_SentSaveArray[0]=LampControlArray[0]; 
	Signal=Zhu_SentSaveArray[0];
	}
										
else if(Location==2 && Way==0)
    {
	Zhu_SentSaveArray[0]=LampControlArray[1]; 
	Signal=Zhu_SentSaveArray[0];
	}

else if(Location==3 && Way==0)
    {
	Zhu_SentSaveArray[0]=LampControlArray[2]; 
	Signal=Zhu_SentSaveArray[0];
	}

else if(Location==4 && Way==0)
    {
	Zhu_SentSaveArray[0]=LampControlArray[3]; 
	Signal=Zhu_SentSaveArray[0];
	}

else if(Location==5 )
    {
	Zhu_SentSaveArray[0]=LampControlArray[4]; 
	Signal=Zhu_SentSaveArray[0];
	}

else if(Location==4 && Way==4)
    {
	Zhu_SentSaveArray[0]=LampControlArray[5]; 
	Signal=Zhu_SentSaveArray[0];
	}

else if(Location==3 && Way==4)
    {
	Zhu_SentSaveArray[0]=LampControlArray[6]; 
	Signal=Zhu_SentSaveArray[0];
	}

else if(Location==2 && Way==4)
    {
	Zhu_SentSaveArray[0]=LampControlArray[7]; 
	Signal=Zhu_SentSaveArray[0];
	}
}

void Zhu_RequestAccept_two()			   //  当用户进入桥厢后，而外呼内选都没有时，用此子程序进行死循环循环扫描请求信号
{
while(1)
    {
	SwitchJudge();
	Zhu_RequestSent();
    if((Signal<<4) ^ (Zhu_AcceptSaveArray[0]<<4))	 // ^:按位异或
       {
	   Zhu_AcceptSaveArray[0]=Signal;
       Judge();
	   //Seg=HoistControlArray[Layer];
       if(Layer!=0)
		  break;
}}}

void Zhu_RequestAccept()			  
{
if((Signal<<4) ^ (Zhu_AcceptSaveArray[0]<<4))				//---------连续开门与此有关 当第二次以上请求(Signal<<4)变了
   {
   //Seg=(Zhu_AcceptSaveArray[0]<<4);
   if(DoorStatus==1)
       DoorClose();														 // ^:按位异或,因有按位位移，所以双目运算符不能用了
   if((Signal<<4) ^ 0x80)
       Zhu_AcceptSaveArray[0]=Signal;
   Judge();	   
   if(Layer==0)							//当桥厢在外呼楼层，直接开门
       {
	   //Seg=(Signal<<4);
       Door();						    	//门系统子程序
       Zhu_RequestAccept_two();
       }
   
   else							   //当桥厢不在外呼楼层，去到请求楼层或用户移动
       {
	    //Seg=HoistControlArray[Layer];
        Hoist();			   
		Door();
		Judge();
		The_Lamp_Of_Way();
		//Zhu_RequestAccept_two();

       }		
   }
}

void Zhu_Status()				  //完成响应过程后，修改某些状态
{
//Zhu_AcceptSaveArray[0]=0xff;
Layer=0;

}
void main()
{
Seg=SegArray[Location];
//Seg=Zhu_AcceptSaveArray[0];
UP=0;
DOWN=0;
Switch=1;
Signal=0x0f;
Motor=0xdd;
beep=0;
	 while(1)
    	 {
		 SwitchJudge();
         Zhu_RequestAccept();				//接受请求信号
		 IndoorRequest(5);
		 if(Layer!=0)
		     {
			  Hoist();			   
	          Door();
			  Judge();						//有与原方向相反的请求时，当平层后起改变Way的作用
			  The_Lamp_Of_Way();
			 }
		 Zhu_RequestSent();
		 
	     }

}
	