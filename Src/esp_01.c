#include "esp_01.h"
#include <stdio.h> 
#include <main.h> 
const char at_test[] =         "AT\r\n";
const char echoOff[] =         "ATE0\r\n";    //6 disable repetition of entered commands
const char restore [] =        "AT+RESTORE\r\n";  //Restore factory default settings
const char uart_baud [] =      "AT+UART=921600,8,1,0,0\r\n" ;//Baudrate range
const char uartFastbaud [] =   "AT+UART_CUR=230400,8,1,0,0\r\n" ;//Baudrate range//921600
const char station_mode [] =   "AT+CWMODE=1\r\n"; //station mode
const char conect_to_AP [] =  "AT+CWJAP=\"onlime72\",\"kka13j8l9v\"\r\n";
const char disconectAP [] =    "AT+ CWQAP\r\n";
const char conect_AP_status [] = "AT+CWJAP?\r\n";
const char NoMultConn[] =        "AT+CIPMUX=0\r\n";
const char rst [] =              "AT+RESTORE\r\n";
const char get_IP [] =           "AT+CIFSR\r\n";
const char conn_TCP [] =         "AT+CIPSTART=\"TCP\",\"82.209.230.70\",88\r\n";
const char send_TSP [] =         "AT+CIPSEND=";
//const char start_AP[] =          "AT+CWSAP=\"ESP01\",\"12345678\",5,3\r\n";        //OK
const char start_AP[] =          "AT+CWSAP=\"ESP01\","",5,0\r\n";        //OK
const char multip_Conn[] =       "AT+CIPMUX=1\r\n";//allow multiple connections    //OK
const char esp_Mode[] =          "AT+CWMODE=3\r\n";//softAP(2) + station mode(1)   //OK
const char esp_Mode_AP[] =          "AT+CWMODE=2\r\n";//softAP(2) + station mode(1)   //OK
const char esp_Mode_ST[] =          "AT+CWMODE=1\r\n";//softAP(2) + station mode(1)   //OK
const char start_Server[] =      "AT+CIPSERVER=1,80\r\n";//start server at HTTP port 80 //OK
const char delete_Server[] =      "AT+CIPSERVER=0\r\n";//start server at HTTP port 80 //OK
const char send_Data_Comand[] =  "AT+CIPSEND=0,5\r\n";
const char show_mac[] = 				 "AT+CIPSTAMAC_CUR\r\n";//show mac adress
const char show_AP_around[] =		 "AT+CWLAP\r\n";
const char new_IP[] =						 "AT+CIPAP_CUR=\"192.168.4.5\"\r\n";
const char info[] =		 					 "AT+CWLIF\r\n"; //"AT+CIPSTATUS\r\n";
//const char chek_ip []	= 				 "AT+CIFSR\r\n";// chek ip softAP	
const char close_conn[] = 			 "AT+CIPCLOSE=0\r\n";//clos TCP connection
const char *close_All_Connections[]={"AT+CIPCLOSE=0\r\n","AT+CIPCLOSE=1\r\n","AT+CIPCLOSE=2\r\n","AT+CIPCLOSE=3\r\n","AT+CIPCLOSE=4\r\n"};
const char chek_ip[] = 			 		 "AT+CIPAP_CUR?\r\n";//clos TCP connection




/*
const char text [] ={"\
<!DOCTYPE html>\
<html>\
<head>\
<link rel=\"icon\" href=\"data:;base64,=\">\
<meta charset=\"UTF8\">\
<title>\
ElectroHobby\
</title>\
</head>\
<body>\
<h1 style=\"text-align: center;\">\
STM32/ESP01 Wi-Fi RADIO WEB SERVER\
</h1>\
<center><a title=\"My YouTube channel\"href=\"https://www.youtube.com/c/ElectroHobby1\">ElectroHobby on YouTube</a></center><br/><br/>\
<form action=\"AP\" method=\"GET\">\
Access point name :<input type=\"text\" size=\"15\"name=\"apName\"/>\
Access point pass :<input type=\"text\" size=\"15\"name=\"apPass\"/>\
<input type=\"submit\"value=\"Submit\"/>\
</form><br/>\
<form action=\"/\"method=\"GET\">\
Radio_N 0-3 :&nbsp;&nbsp;&nbsp;\
<input name=\"radioN\" size=\"1\" value=\"\"type=\"text\"/><br/><br/>\
Radio IP addr :&nbsp;&nbsp;\
<input name=\"ip\"size=\"15\"value=\"\"type=\"text\"/>&nbsp;&nbsp;&nbsp;\
Server Port :&nbsp;&nbsp;&nbsp;\
<input name=\"port\"size=\"4\"value=\"\"type=\"text\"/><br/><br/>\
Radio Get Msg:&nbsp;\
<input name=\"message\"size=\"100\"value=\"\"type=\"text\"/>\
<input value=\"SAVE\"type=\"submit\"/>\
</form>\
<br/><hr><br/>"
"</body>\
</html>"};
*/


const char text [] ={"\
<!DOCTYPE html>\
<html>\
<head>\
<link rel=\"icon\" href=\"data:;base64,=\">\
<meta charset=\"UTF8\">\
<title>\
Parker settings\
</title>\
</head>\
<body>\
<h1 style=\"text-align: center;\">\
STM32/ESP01 Wi-Fi  WEB SERVER\
</h1>\
<form action=\"AP\" method=\"GET\">\
Access point name :<input type=\"text\" size=\"15\" name=\"apName\"/><br/>\
Access point pass :<input type=\"text\" size=\"15\" name=\"apPass\"/><br/>\
Access point ip	  :<input type=\"text\" size=\"15\" name=\"apIP\"/><br/>\
Station: <input type=\"radio\" value=\"ST\" name=\"type\"/><br/>\
Access point :<input type=\"radio\" value=\"AP\" name=\"type\"/><br/>\
<input type=\"submit\"value=\"Submit\"/>\
</form><br/>\
<br/><hr><br/>"
"</body>\
</html>"};
