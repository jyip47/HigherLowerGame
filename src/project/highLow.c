/*
 * Higher or Lower Game
 * created by Jessica Yip and Dennis Lin
 * ENGR 478 Spring 2018
 *
 * Lab 10 of Tiva LaunchPad Workshop Workbook was used as a template.
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "grlib/grlib.h"
#include "grlib/widget.h"
#include "grlib/canvas.h"
#include "grlib/pushbutton.h"
#include "Kentec320x240x16_ssd2119_8bit.h"
#include "touch.h"

int randomNum();
void highPress(tWidget *pWidget);
void lowPress(tWidget *pWidget);
int currNum;
int nextNum;
int numArray[5] = {7, 8, 1, 4, 9};
char numStr[5];
int counter;
char strCurrNum [12];
char strNextNum [12];
bool isGameOver = true;

RectangularButton(g_sHigh, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 0, 190,
                  50, 50, (PB_STYLE_IMG | PB_STYLE_TEXT | PB_STYLE_FILL), ClrWhite, ClrGray, ClrRed, ClrRed,
                  &g_sFontCm20, "High", 0, 0, 0, 0, highPress);

Canvas(g_sTitle, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 50, 0, 220, 50,
       CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_OPAQUE | CANVAS_STYLE_FILL, ClrGray, ClrBlue, ClrBlue,
       &g_sFontCm20, "Higher or Lower?", 0, 0);


RectangularButton(g_scurrNum, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 50, 100,
                  220, 50, (PB_STYLE_IMG | PB_STYLE_TEXT | PB_STYLE_FILL), ClrBlack, ClrBlack, ClrBlack,
                  ClrWhite, &g_sFontCm20, strCurrNum, 0,
                  0, 0, 0, lowPress);

RectangularButton(g_sLow, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 270, 190,
                  50, 50, (PB_STYLE_IMG | PB_STYLE_TEXT | PB_STYLE_FILL), ClrWhite, ClrGray, ClrSilver,
                  ClrSilver, &g_sFontCm20, "Low", 0, 0, 0, 0, lowPress);

/* Canvas(g_sGameOver, 0, 0, 0, &g_sKentec320x240x16_SSD2119, 50, 50, 220, 50,
       CANVAS_STYLE_TEXT | CANVAS_STYLE_TEXT_OPAQUE | PB_STYLE_FILL, 0, 0, ClrWhite,
       &g_sFontCm20, numStr , 0, 0);

       */


void highPress (tWidget *pWidget){

	 if (currNum < numArray[counter + 1]){
		 currNum = numArray [counter + 1];
		 	 sprintf (strNextNum, "%i", currNum);
		 	PushButtonTextSet (&g_scurrNum, strNextNum);
		 	WidgetPaint(WIDGET_ROOT);
		 	 counter++;
		 	//PushButtonTextSet (&g_sHigh, "Win");
	 }
	 else{
		 PushButtonTextSet (&g_sHigh, "Game");
		 PushButtonTextSet (&g_sLow, "Over");
		 isGameOver = true;
	 }



}

void lowPress (tWidget *pWidget){
	if (currNum > numArray [counter + 1]){

		 currNum = numArray [counter + 1];
		 	 sprintf (strNextNum, "%i", currNum);
		 	 PushButtonTextSet (&g_scurrNum, strNextNum);
		 	WidgetPaint(WIDGET_ROOT);
		 	 counter++;
		 	//PushButtonTextSet (&g_sLow, "Win");
	 }
	 else{
		 PushButtonTextSet (&g_sLow, "Over");
		 PushButtonTextSet (&g_sHigh, "Game");
		 isGameOver = true;
	 }


}

int randomNum(){
	int temp;
	temp = (rand() % 10) + 1;
	if (temp == currNum){
		randomNum();
	}
	 return temp;
	}


int main(void)
{
SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0x00);
Kentec320x240x16_SSD2119Init();
TouchScreenInit();
TouchScreenCallbackSet(WidgetPointerMessage);

	counter = 0;
	currNum =  numArray[counter];
	sprintf (strCurrNum, "%i", currNum);


WidgetAdd(WIDGET_ROOT, (tWidget *)(&g_sHigh));
WidgetAdd(WIDGET_ROOT, (tWidget *)(&g_sLow));
WidgetAdd(WIDGET_ROOT, (tWidget *)(&g_sTitle));
WidgetAdd(WIDGET_ROOT, (tWidget *)(&g_scurrNum));

WidgetPaint(WIDGET_ROOT);

while(1)
{
WidgetMessageQueueProcess();
WidgetPaint(WIDGET_ROOT);
}


}
