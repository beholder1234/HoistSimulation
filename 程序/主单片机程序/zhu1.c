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

char SegArray[]={0xff,0xf9,0xa4,0xb0,0x99,0x92};	 //¥����ʾ���������,0����ֵ���ã�Ŀ��������������λ�ñ���(Location)��Ӧ

char DoorRun[4]={0x40,0x80,0x10,0x20};  //��ϵͳ�������Ĺ�����ʽ  ��ת�����ţ�
char DoorRun1[4]={0x20,0x10,0x80,0x40}; //                        ��ת�����ţ�

char HoistRun[4]={0x04,0x08,0x01,0x02};  //���ػ��������Ĺ�����ʽ  ��ת�����У�
char HoistRun1[4]={0x02,0x01,0x08,0x04}; //                        ��ת�����У�

char HoistControlArray[]={0xf0,0xf1,0xf2,0xf3,
                          0xf4,0xf5,0xf6,0xf7,
					      0xf8,0xf9,0xfa,0xfb,
				       	  0xfc,0xfd,0xfe,0xff};
char Zhu_AcceptSaveArray[]={0xFf};					//ֻҪ����λ�����ж��ǻ�������λ��ɸ���λ

char LampControlArray[]={0x0f,0x1f,0x2f,0x3f,
                         0xcf,0xbf,0xaf,0x9f};


char Zhu_SentSaveArray[2]={0x0f};	     //	���ʼ״̬Way=0 Location=1������Ϊ0x0f 
char Location=1,Way=0,Layer=0,DoorStatus=0;    //DoorStatus 1���ſ��ţ�0���Ź���   
void Zhu_Status();
void Zhu_RequestSent();
void delay1ms(void) 
{	  
	   unsigned char a,b,c;
	   for(c=10;c>0;c--)
	        for(b=42;b>0;b--)
	             for(a=2;a>0;a--);	             
}

void delay100ms(void)        //�Źرջ�����ɺ���1s��ʮ�Σ�ÿ�ξ��ж��Ƿ��У����ţ����ţ�������ƽ�㰴��Ҫ��
{
    unsigned char a,b,c;
    for(c=19;c>0;c--)
        for(b=20;b>0;b--)
            for(a=130;a>0;a--);
}
void delay62ms500us(void)   //��� 0us
{
    unsigned char a,b;
    for(b=224;b>0;b--)
        for(a=138;a>0;a--);
}

void delay31ms250us(void)   //��� 0us
{
    unsigned char a,b,c;
    for(c=2;c>0;c--)
        for(b=220;b>0;b--)
            for(a=34;a>0;a--);
}

void delay20ms825us(void)   //��� 0us
{
    unsigned char a,b;
    for(b=58;b>0;b--)
        for(a=178;a>0;a--);
}


void delay300ms(void)   //��� 0us
{
    unsigned char a,b,c;
    for(c=5;c>0;c--)
        for(b=212;b>0;b--)
            for(a=140;a>0;a--);
}
void delay2s(void)   //�ſ�����ȴ����루�û�������
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
void ArriveSound()					         	 // ��������ӳ���
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
void Judge()									// ��λ��¥������Layer���ͷ���Way�������ж�
{
switch(Zhu_AcceptSaveArray[0]<<4)					 //<<:���Ʋ�0    >>:���Ʋ�0(ע������ << ���� >> λ������ͬ��ֵ���䣬��cpu������������������)
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

void HoistSpeed1(char Way)					 //���0m/s--0.5m/s�� ���ٻ������ʻ�ӳ��򣨼��ٶ� 0.75��
{
char time,rotate; 					 // time: ���ѭ������	rotate���������ת����ѭ��
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
    {							 // Way:����ת�ж�	0 ���������� ��ת
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


void HoistSpeed2(char Way)					 // ��� 0.5m/s--1.0m/s�� ���ٻ������ʻ�ӳ��򣨼��ٶ� 0.75��
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
void HoistSpeed3(char Way)					  //��� 1.0m/s--1.5m/s�� ���ٻ������ʻ�ӳ��򣨼��ٶ� 0.75��
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
void HoistSpeed4(char Way,char Special_One,char Special_Two )	  // 1.5m/s ������ʻ�ӳ��򣨼��ٶ� 0��  ��ע����Ϊ0.5s��������ʻ��
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
					  if(Layer!=1 && Special_Two==1 && Special_One==3 && time*rotate==12 )		  //����λ��ȷ��
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


void Hoist()					// ���ص�������ӳ���	 
{											   // Layer:����λ�Ʋ��� Way:����ת�ж�
char i;                                        // i:�����ӳ���ѭ������ (�����н������ı���� i=3+6*(����-1)��  )
char Special_One=0,Special_Two=1;			   //Special��������λ�Ʋ�������һʱ��Ϊʵʱȷ������λ�ã����Դ��ڵı���
The_Lamp_Of_Way();
HoistSpeed1(Way);							   
HoistSpeed2(Way);
HoistSpeed3(Way);
for(i=0;i<3+6*(Layer-1);i++)
    {
	//Seg=HoistControlArray[6*(Layer-1)];
    HoistSpeed4(Way,Special_One,Special_Two);
	Special_One++;						//ֻ���ڵ�һ������λ�üӣ�����һȷ��ʱ����������á�����λ�üӣ�����һȷ����if(i!=3 && (i-3)%6==0)ȷ��
	if(i%3==0)									//ÿ��������������1.5�룬����ɨ��һ�ν������ţ���������ȼ��Ƿ�ı䣻
	    {
		if((Signal<<4) ^ (Zhu_AcceptSaveArray[0]<<4))
		    {
			//Seg=HoistControlArray[Location];
		    Zhu_AcceptSaveArray[0]=Signal;
			Judge();

			}
		if(i!=3 && (i-3)%6==0)					//������λ�Ʋ���Ϊ��ʱ���������1.125m��1.5s����������2.25m+1.125m����1.5s+0.75s����
		    {									//����λ�üӣ�����һ����Ϊ��һ������ȷ������֮������4.5m����3s��������λ�üӣ�����һ��
												//��֮������4.5m����3s�����ټ���1.125m��1.5s��������λ�üӣ�����һ��
			Special_Two=1;					    //i��=3:��֤�ڵڶ��Σ������ϣ�����λ��ȷ��ʱ��Ч��
			Special_One=3;						//(i-3)%6==0����֤�ڵ�һ������ȷ���󣬵�һ������4.5mʱ������λ�üӣ�����һ������λ�Ʋ�Ϊ���ģ�
			}		    						//(i-3)%6==0����֤�ڵ�һ������ȷ���󣬵�һ������������4.5mʱ������λ�üӣ�����һ������λ�Ʋ�Ϊ���ĵģ�
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
char i;					//DoorStatus 1���ſ��ţ�0���Ź���
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
{												   //��λ�����ź�λ������λ�������� ������λ������λ��
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

void Zhu_RequestAccept_two()			   //  ���û���������󣬶������ѡ��û��ʱ���ô��ӳ��������ѭ��ѭ��ɨ�������ź�
{
while(1)
    {
	SwitchJudge();
	Zhu_RequestSent();
    if((Signal<<4) ^ (Zhu_AcceptSaveArray[0]<<4))	 // ^:��λ���
       {
	   Zhu_AcceptSaveArray[0]=Signal;
       Judge();
	   //Seg=HoistControlArray[Layer];
       if(Layer!=0)
		  break;
}}}

void Zhu_RequestAccept()			  
{
if((Signal<<4) ^ (Zhu_AcceptSaveArray[0]<<4))				//---------������������й� ���ڶ�����������(Signal<<4)����
   {
   //Seg=(Zhu_AcceptSaveArray[0]<<4);
   if(DoorStatus==1)
       DoorClose();														 // ^:��λ���,���а�λλ�ƣ�����˫Ŀ�������������
   if((Signal<<4) ^ 0x80)
       Zhu_AcceptSaveArray[0]=Signal;
   Judge();	   
   if(Layer==0)							//�����������¥�㣬ֱ�ӿ���
       {
	   //Seg=(Signal<<4);
       Door();						    	//��ϵͳ�ӳ���
       Zhu_RequestAccept_two();
       }
   
   else							   //�����᲻�����¥�㣬ȥ������¥����û��ƶ�
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

void Zhu_Status()				  //�����Ӧ���̺��޸�ĳЩ״̬
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
         Zhu_RequestAccept();				//���������ź�
		 IndoorRequest(5);
		 if(Layer!=0)
		     {
			  Hoist();			   
	          Door();
			  Judge();						//����ԭ�����෴������ʱ����ƽ�����ı�Way������
			  The_Lamp_Of_Way();
			 }
		 Zhu_RequestSent();
		 
	     }

}
	