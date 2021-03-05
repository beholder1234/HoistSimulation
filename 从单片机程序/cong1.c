#include <reg51.h>

//**********************-------���Ŷ��岿��--------*********************//
sfr Lamp=0x80;
sfr Lamp0=0xa0;			     
sfr Keyboard=0xb0;
sfr Signal=0x90; 

sbit Lamp1UP=P0^0;			//p1����Ϊ��������
sbit Lamp2UP=P0^1;
sbit Lamp3UP=P0^2;
sbit Lamp4UP=P0^3;
sbit Lamp5DOWN=P0^4;
sbit Lamp2DOWN=P0^5;
sbit Lamp3DOWN=P0^6;
sbit Lamp4DOWN=P0^7;

sbit Lamp1=P2^0;		   //p2����Ϊ��ѡ�����
sbit Lamp2=P2^1;
sbit Lamp3=P2^2;
sbit Lamp4=P2^3;
sbit Lamp5=P2^4;
sbit LampOpen=P2^5;
sbit LampClose=P2^6;
sbit LampDanger=P2^7;


//**********************-------ȫ�ֱ������岿��--------*********************//
char KeyboardArray[]={0xfe,0xfd,0xfb,0xf7};	                                     //���м��̼�������

char ButtonArray[]={0xee,0xde,0xbe,0x7e,
				  0xed,0xdd,0xbd,0x7d,
				  0xeb,0xdb,0xbb,0x7b,
				  0xe7,0xd7,0xb7,0x77};                                          //���̰����ж�����	  ��һ�������а����������ң�

char HoistControlArray[]={0xf0,0xf1,0xf2,0xf3,
                          0xf4,0xf5,0xf6,0xf7,									//0Xf8��ͬ��
					      0xf8,0xf9,0xfa,0xfb,
				       	  0xfc,0xfd,0xfe,0xff};
char Cong_SentSaveArray[8]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
char LampControlArray[]={0x0f,0x1f,0x2f,0x3f,
                         0xcf,0xbf,0xaf,0x9f};

char Cong_AcceptSaveArray[2]={0xff,0xff};
char Location=1,Way=0;

//**********************-------�����ӳ���--------*********************//
void Cong_RequestSent(char Location,char Way);
void Cong_RequestAccept();
void BrightLamp()						  
{
 char H,L,i=10;
     for(H=0;H<4;H++)
	     {		                                                                   	// H:��ѡ
	     Keyboard=KeyboardArray[H];			                                      // ���м��̼������
	     for(L=0;L<4;L++)	            	                                      // L:��ѡ
	          {
	          if(Keyboard==ButtonArray[H*4+L])
			      {
				   switch(H*4+L)				                                 	//����������Ӧ�����
				       {
					    case 0:
						    {
						     if(Location==1)
							     Signal=0xf8;
							 else Lamp1UP=1;
							 break;
							 }
						case 1:
						     {
							  if(Location==2)
							      Signal=0xf8;
							  else Lamp2UP=1;
							  break;
							 }
						case 2:
						      {
							   if(Location==3)
							      Signal=0xf8;
							   else Lamp3UP=1; 
					           break;
							  }
						case 3:
						      {
							   if(Location==4)
							      Signal=0xf8;
							   else Lamp4UP=1;
							   break;
							  }
						case 4:
						      {
							   if(Location==5)
							      Signal=0xf8;
							   else Lamp5DOWN=1; 
							   break;
							  }
						case 5:
						      {
							  if(Location==2)
							      Signal=0xf8;
							  //else {Lamp2DOWN=1;Lamp0=0xf0;}
							  else Lamp2DOWN=1;
							  break;
							  }
						case 6:
						      {
							  if(Location==3)
							      Signal=0xf8;
							  else Lamp3DOWN=1; 
							  break;
							  }
						case 7:
						      {
							  if(Location==4)
							      Signal=0xf8;
							  else Lamp4DOWN=1; 
							  break;
							  }
						case 8:
						      {
							  if(Location==1)
							      Signal=0xf8;
							  else Lamp1=1;
							  break;
							  }
						case 9:
						      {
							  if(Location==2)
							      Signal=0xf8;
							  //else {Lamp2=1;Lamp0=0xf0;}
							  else Lamp2=1; 
							  break;
							  }
						case 10:
						      {
							  if(Location==3)
							      Signal=0xf8;
							  else Lamp3=1; 
							  break;
							  }
						case 11:
						      {
							  if(Location==4)
							      Signal=0xf8;
							  else Lamp4=1;
							  break;
							  }
						case 12:
						      {
							  if(Location==5)
							      Signal=0xf8;
							  else Lamp5=1;
							  break;
							  }
						case 13:
						      {
							  LampOpen=1;
							  break;
							  }
						case 14:
						      {
							  LampClose=1;
							  break;
							  }
						case 15:
						      {
							  LampDanger=1;
							  break;
							  }
}}
//Lamp0=HoistControlArray[Lamp2DOWN]<<4;
        }
    }

}


void Cong_RequestAccept()
{
Cong_AcceptSaveArray[0]=Signal;
if(Cong_AcceptSaveArray[0]==0x08)
    Signal=0xff;    
switch((((Cong_AcceptSaveArray[0]>>4)<<4)+0x0f))							 //������ʱ����λ�᲻�ϱ仯�����ڵ���λ�ڴ˲������ж�
    {																		//��Ϊ�������λ���մ���Ӱ���ж�������λ
     case 0x0f:{Location=1;Way=0;Lamp1UP=0;Lamp1=0;Cong_SentSaveArray[0]=0xff;break;}
	 case 0x1f:{Location=2;Way=0;Lamp2UP=0;Lamp2=0;Cong_SentSaveArray[1]=0xff;break;} 
	 case 0x2f:{Location=3;Way=0;Lamp3UP=0;Lamp3=0;Cong_SentSaveArray[2]=0xff;break;}
	 case 0x3f:{Location=4;Way=0;Lamp4UP=0;Lamp4=0;Cong_SentSaveArray[3]=0xff;break;}
	 case 0xcf:{Location=5;Way=4;Lamp5DOWN=0;Lamp5=0;Cong_SentSaveArray[4]=0xff;break;}
	 case 0xbf:{Location=4;Way=4;Lamp4DOWN=0;Lamp4=0;Cong_SentSaveArray[5]=0xff;break;}
	 case 0xaf:{Location=3;Way=4;Lamp3DOWN=0;Lamp3=0;Cong_SentSaveArray[6]=0xff;break;}
	 case 0x9f:{Location=2;Way=4;Lamp2DOWN=0;Lamp2=0;Cong_SentSaveArray[7]=0xff;break;}
	 case 0x4f:{LampOpen=0;}
	 case 0x5f:{LampClose=0;}
	 case 0x6f:{LampDanger=0;}


	}

//Lamp0=Cong_AcceptSaveArray[0]>>4<<4;
}
void Cong_RequestActivate()			   //���� ����if�жϿ����д�
{
if(Lamp1 || Lamp1UP)									//��û��Lamp1DOWN�Ĵ��ڣ�û��Ҫ��Ҳ�����ж�Way
    Cong_SentSaveArray[0]=HoistControlArray[0];			

if((Lamp2 && Way==0 ) || Lamp2UP)			// Lamp2 && Way==0 �ж�������һ¥ʱ�����ں���¥��������Ч
	Cong_SentSaveArray[1]=HoistControlArray[1];		//�������������5¥����ʱ����Lamp1��Lamp2��������Ӧ��ͣ�ڶ��㣬��ͣ��һ��
													//������Lamp1UP��Lamp2UP��������Ӧ��ͣ��һ�㣬��ͣ�ڶ���
if((Lamp3 && Way==0) || Lamp3UP)							//ֻ�а���Lamp1DOWN��Lamp2DOWN���밴��Lamp1��Lamp2���ȼ���ͬ��
    Cong_SentSaveArray[2]=HoistControlArray[2];		//���Լ���Way==0�������ж����������л����У��Ӷ��жϰ�����ѡLampʱ��
													//Ӧ��������ȼ���ʽ�жϷ���
if((Lamp4 && Way==0) || Lamp4UP)				
    Cong_SentSaveArray[3]=HoistControlArray[3];

if(Lamp5 || Lamp5DOWN)			               //��û��Lamp5UP�Ĵ��ڣ�û��Ҫ��Ҳ�����ж�Way
//if(Lamp5DOWN)									   //======Ϊ�˵��ԣ�Lamp0��ʱ����λ���Ų�����Ч��
    Cong_SentSaveArray[4]=HoistControlArray[4];

if((Lamp4 && Way==4) || Lamp4DOWN)
    Cong_SentSaveArray[5]=HoistControlArray[5];

if((Lamp3 && Way==4) || Lamp3DOWN)
    Cong_SentSaveArray[6]=HoistControlArray[6];

if((Lamp2 && Way==4) || Lamp2DOWN)
    Cong_SentSaveArray[7]=HoistControlArray[7];


}

void Cong_RequestSent(char Location,char Way)	    	// Location:��������¥�� Way���������з��� 	0:���� 4:����
{
char i;						                    	   // i:��RequestSaveArray���е���ɨ��ı���
    for(i=0;i<8;i++)
	    {                                            		  // (Location-1+i)%8 ���ã�����ȷ���ȴ�������ȼ���ʼɨ��
	    if(Way==0 && (Cong_SentSaveArray[(Location-1+i)%8] ^ 0xff))
			{
		    Signal=Cong_SentSaveArray[(Location-1+i)%8];
		    break;														 
            //Lamp0=Cong_AcceptSaveArray[0]>>4<<4;
		    }
		else if(Location==5 && (Cong_SentSaveArray[(Location-1+i)%8] ^ 0xff))
		    {
			Signal=Cong_SentSaveArray[(Location-1+i)%8];
		    break;													
			
			}
        else if(Way==4  && (Cong_SentSaveArray[(Way+5-Location+i)%8] ^ 0xff)  && Location!=5)		  // (Way+5-Location+i)%8 ���ã�����ȷ���ȴ�������ȼ���ʼɨ��
	        {
		    Signal=Cong_SentSaveArray[(Way+5-Location+i)%8];
			//LampDanger=1;
		    break;												
		    }
	    }
}

//**********************-------�����򲿷�--------*********************//
   
void main()
{
Lamp=0x00;
Lamp0=0x00;
Signal=0xff;
while(1)
    {
     BrightLamp();
	 Cong_RequestActivate();
	 Cong_RequestSent(Location,Way);
	 Cong_RequestAccept();	                                                             //�����ӳ������
		   		 
	
	}

}
