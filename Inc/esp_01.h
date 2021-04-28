#ifndef ESP_01_H
#define ESP_01_H
#define DEBUG 1 
#define restart       "AT+RST\r\n"      //Restart module
#include <stdint.h>
extern const char at_test[];
extern const char echoOff[];      //6 disable repetition of entered commands
extern const char restore[];      //Restore factory default settings
extern const char uart_baud[];    //Baudrate range
extern const char uartFastbaud[]; //Baudrate range//921600
extern const char station_mode[]; //station mode

extern const char conect_to_AP [];
//const char conect_to_AP [] =  "AT+CWJAP=\"360WiFi\",\"amkhalyawa\"\r\n";
extern const char disconectAP [];
extern const char conect_AP_status[];
extern const char NoMultConn[];
extern const char rst [];
extern const char get_IP [];
extern const char conn_TCP [];
extern const char send_TSP [];
extern const char getStream [];
extern const char show_mac [];
extern const char multip_Conn[];
extern const char esp_Mode[];
extern const char esp_Mode_AP[];
extern const char esp_Mode_ST[];
extern const char start_AP[];
extern const char start_Server[];
extern const char chek_ip [];
extern const char text []; 
extern const char info[];
extern const char delete_Server[];
extern const char close_conn[];
extern const char new_IP[];
extern const char *close_All_Connections[];
//extern const char chek_ip[];
void start_ap_server(void);
void esp_01_ini(void);
void clear_rx_buf(void);
void esp_01_usart_setup(uint32_t baud);
void usart_recive_str(char* str);
void usart1_send_string(const char* str);
#endif



/*
while(1){
	if(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_13)==Bit_SET)led=1;
	else led = 0;
		
	if(check_answer("GET / HTTP/1.1",100)==1){
			if (led==LED_ON)sprintf(sendbuf,"%s%d%c%d%s","AT+CIPSEND=",0,',',led_On_Web_Page_len,"\r\n");//437
			else if(led==LED_OFF) sprintf(sendbuf,"%s%d%c%d%s","AT+CIPSEND=",0,',',led_Off_Web_Page_len,"\r\n");//437
			if(DEBUG)printf("usart1_send_string(sendbuf) \r\n");
			usart1_send_string(sendbuf);
		if(check_answer(">",500)==1){//???? ??????????? ?? ???????? ??????
							if(DEBUG)printf("usart1_send_string(web_Page) \r\n");
					if (led==LED_ON){
							send_page(led_ON,7);
							GPIO_ResetBits(GPIOC, GPIO_Pin_13);
					}
					else if(led==LED_OFF){
							GPIO_SetBits(GPIOC, GPIO_Pin_13);
							send_page(led_OFF,7);
					}
					if(check_answer("SEND OK",1000)==1){
						 if(DEBUG)printf("_SEND OK_ \r\n");
					}	
			}
		  lastTimeMs = currentTimeMs;
			close_conections();	//???????? ??? ?????????? 
			//?? ????? ????????? ?? ?????????? ???? ?????????? ????????	
		 }
	  if(currentTimeMs - lastTimeMs  >	2500){//???? ??? ???? ?? ??????? ??? ??????????
        if(DEBUG)printf("status?\r\n");
				usart1_send_string("AT+CIPSTATUS\r\n");
			  //close_conections();		
			  lastTimeMs = currentTimeMs;
	   }
	 }//end while

	 
	 
	 
void service_AP(void){
	char *p1 = NULL,*p2 = NULL;
	char  *debug_p;
	u8  send_page_flag=0;
	char str[33];
	char *pstr=str;
	debug_p=debug_str;
	if(check_answer("GET / HTTP/1.1",100)==1)send_page_flag = 1;//?????? ?????? ?? ????????
  else if(check_answer("GET /AP?",100)==1){
	    send_page_flag = 1;
//+++++++++++++++++++++++++++++++++++++apName+++++++++++++++++++++++++++++++++++//
	   	p1=strstr(rx_buf,"apName=");
		  p2=strstr(rx_buf,"&apPass=");
	    if(p1!=NULL&&p2!=NULL){
		     p1+=sizeof("apName=")-1;
		     while(p1!=p2)*pstr++=*p1++;
	       }*pstr=0;
     if(DEBUG)printf("catch str = %s \r\n",str);	 
		 if(pstr!=str){//???? ???? ??????
			  pstr=str;
			  p1=&(flash_radio_ini.apName[0]);
			  clear_str(p1,'\0',sizeof(flash_radio_ini.apName));//??????? ?? ??????? ?????? ?????? ?? ???????????)
			  strcpy(p1,pstr);//???????? ? ????????? ???????? ????? ????????
			 }
		 //while(*pstr)*p1++=*pstr++;
		 //*p1=0;
			
//++++++++++++++++++++++++++++++++++++++apPass+++++++++++++++++++++++++++++++++//				 
	    pstr=str;
	    p1=p2;
		  p2=strstr(rx_buf," HTTP/1.1");
	    if(p1!=NULL&&p2!=NULL){
		     p1+=sizeof("apPass=");
		     while(p1!=p2)*pstr++=*p1++;
	      }*pstr=0;
	    if(DEBUG)printf("catch str = %s \r\n",str);
				if(pstr!=str){//???? ???? ??????
					 pstr=str;
			     p1=&(flash_radio_ini.apPass[0]);
					 clear_str(p1,'\0',sizeof(flash_radio_ini.apPass));
			     strcpy(p1,pstr);//???????? ? ????????? ???????? ????? ????????
					 write_flash(page_Addr,radio_Setting_Size,&flash_radio_ini);
					 sprintf(debug_p,"%s%s%c%s%c","DEBUG|",flash_radio_ini.apName,'|',flash_radio_ini.apPass,'|');
			    }
			clear_rx_buf();
	}
	else if(check_answer("GET /?radioN",100)==1){
	        send_page_flag = 1;
//++++++++++++++++++++++++++++++++++++++radioN=+++++++++++++++++++++++++++++++++//			
			pstr=str;
		  p1=strstr(rx_buf,"radioN=");
		  p2=strstr(rx_buf,"&ip=");
	    if(p1!=NULL&&p2!=NULL){
		     p1+=sizeof("radioN=")-1;
		     while(p1!=p2)*pstr++=*p1++;
	       *pstr=0;	
			   radioN=atoi(str);
			   if(radioN<N_OF_RADIO)sprintf(debug_p,"%c%d%c%s%c%d%c%s%c",'|',radioN,'|',flash_radio_ini.m_stations[radioN].ipAddr,'|'\
			  ,flash_radio_ini.m_stations[radioN].port,'|',flash_radio_ini.m_stations[radioN].message,'|');
		 }
     if(DEBUG)printf("catch str radioN = %s \r\n",str);
//+++++++++++++++++++++++++++++++++++++++++IP++++++++++++++++++++++++++++++++++//	
      pstr=str;
			p1=p2;
		  p2=strstr(rx_buf,"&port=");
	    if(p1!=NULL&&p2!=NULL){
		     p1+=sizeof("&ip=")-1;
		     while(p1!=p2)*pstr++=*p1++;
	       *pstr=0;
         if(DEBUG)printf("catch str IP = %s \r\n",str);	
				 if(pstr!=str){//???? ???? ??????
					  pstr=str;  
			      p1=&(flash_radio_ini.m_stations[radioN].ipAddr[0]);
					  clear_str(p1,'\0',sizeof(flash_radio_ini.m_stations[radioN].ipAddr));
			      strcpy(p1,pstr);//???????? ? ????????? ???????? ????? ????????
			    } 
			}				 
//+++++++++++++++++++++++++++++++++++++++port+++++++++++++++++++++++++++++++++//	
		  pstr=str;
			p1=p2;
		  p2=strstr(rx_buf,"&message=");
	    if(p1!=NULL&&p2!=NULL){
		     p1+=sizeof("&port=")-1;
		     while(p1!=p2)*pstr++=*p1++;
	       *pstr=0;
			   if(DEBUG)printf("catch str port = %s \r\n",str);
         if(pstr!=str){//???? ???? ??????
			      flash_radio_ini.m_stations[radioN].port=atoi(str);			     
			   } 
			}					 
//++++++++++++++++++++++++++++++++++++message+++++++++++++++++++++++++++++++++//	
			pstr=str;
			p1=p2;
		  p2=strstr(rx_buf," HTTP/1.1");
	    if(p1!=NULL&&p2!=NULL){
		     p1+=sizeof("&message=")-1;
		     while(p1!=p2)*pstr++=*p1++;
	       *pstr=0;
			
			   if(DEBUG)printf("catch str message = %s \r\n",str);	
			   if(pstr!=str){//???? ???? ??????
				    pstr=str;
				    parse_GET (str,"%2F",'/');//???????? ???????? ?? ??????
			      p1=&(flash_radio_ini.m_stations[radioN].message[0]);
				    clear_str(p1,'\0',sizeof(flash_radio_ini.m_stations[radioN].message));
				    strcpy(p1,pstr);//???????? ? ????????? ???? ? ?????
				    sprintf(debug_p,"%c%d%c%s%c%d%c%s%c",'|',radioN,'|',flash_radio_ini.m_stations[radioN].ipAddr,'|'\
				    ,flash_radio_ini.m_stations[radioN].port,'|',flash_radio_ini.m_stations[radioN].message,'|');
				     write_flash(page_Addr,radio_Setting_Size,&flash_radio_ini);
			    }
			}
			if(DEBUG)printf("parse str message = %s \r\n",str);	
			clear_rx_buf();	 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//					 
	}
		 if(send_page_flag){
				send_page_flag = 0;
				sprintf(sendbuf,"%s%d%c%d%s","AT+CIPSEND=",0,',',(strlen(web_Page[0])+strlen(web_Page[1])+ strlen(web_Page[2])),"\r\n");//437!!!!!!!!!!!!!!!!!!!!!!!
				if(DEBUG)printf("usart1_send_string(web_Page_len) \r\n");
				usart1_send_string(sendbuf);// ?????????? ?????? ????????
				if(check_answer(">",500)==1){//???? ??????????? ?? ???????? ??????
						if(DEBUG)printf("usart1_send_string(web_Page) \r\n");
						 usart1_send_string(web_Page[0]);//?? 
					   usart1_send_string(web_Page[1]);//?
					   usart1_send_string(web_Page[2]);//??????!!! ??? ????) ????? ????????
						 if(check_answer("SEND OK",1000)==1)if(DEBUG)printf("rx_SEND OK\r\n");	
			}
			close_conections(4);	//???????? ??? ?????????? !!!!!!!!!!!!!!!!!!!!!!!1
			clear_rx_buf();
		 	 
		 
		 }
		  
	   if(currentTimeMs-lastTimeMs>4000){//1s rutine
			  //if(DEBUG) usart1_send_string(status);
			  //close_conections(4);
			  lastTimeMs = currentTimeMs;
		 }
	 }	 
*/	 

	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 
	 