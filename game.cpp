#include "game.h"

timer g_timer;
burger burgerdata[6][3];
order orderlist[6];

bool happy = true;

int score = 0;
int numorders = 0;
int currentItem = BURGER;


burger::burger()
{
	blinked = false;
	blinker = false;
	blink = 0.0;
	text = NONE;
	time = 0.0;
	type = NONE;
	currentState = NONE;
}

order::order()
{
	type = NONE;
	time = 0.0;
}

void DrawBackground(gfx* GFX)
{
	//draw the bars
	GFX->DrawImage(64,32,LU_BAR);
	GFX->DrawImage(64,32*5,LD_BAR);
	GFX->DrawImage(32*9,32,RU_BAR);
	GFX->DrawImage(32*9,32*5,RD_BAR);

	for(int i = 96;i<32*9;i+=32)
		GFX->DrawImage(i,32,U_BAR);

	for(int i = 96;i<32*9;i+=32)
		GFX->DrawImage(i,32*5,D_BAR);

	for(int i = 64;i<32*5;i+=32)
		GFX->DrawImage(64,i,L_BAR);

	for(int i = 64;i<32*5;i+=32)
		GFX->DrawImage(32*9,i,R_BAR);
}
void UpdateBurgers()
{

	for(int i = 0;i<6;i++)
		for(int j = 0;j<3;j++)
		{
			if(burgerdata[i][j].blinker)
				if((g_timer.GetTime()-burgerdata[i][j].blink)>BLINKTIME)
				{
					burgerdata[i][j].blink = g_timer.GetTime();
					burgerdata[i][j].blinked = !burgerdata[i][j].blinked;
				}

			switch(burgerdata[i][j].currentState)
			{
			case RAW:
				if(g_timer.GetTime()-burgerdata[i][j].time>=COOKTIME)
				{
						burgerdata[i][j].currentState = BCOOKED;
						burgerdata[i][j].text = FLIP;
						burgerdata[i][j].blink = g_timer.GetTime();
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].blinker = true;
						burgerdata[i][j].time = g_timer.GetTime();
				}
			break;

			case TCOOKED:
				
				if(g_timer.GetTime()-burgerdata[i][j].time>=COOKTIME)
				{
					if(burgerdata[i][j].type==BURGER)
					{
						burgerdata[i][j].currentState = COOKED;
						burgerdata[i][j].text = SERVE;
						burgerdata[i][j].blink = g_timer.GetTime();
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].blinker = true;
						burgerdata[i][j].time = g_timer.GetTime();
					}
					else {
						burgerdata[i][j].currentState = COOKED;
						burgerdata[i][j].text = CHEESE;
						burgerdata[i][j].blink = g_timer.GetTime();
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].blinker = true;
						burgerdata[i][j].time = g_timer.GetTime();
					}
				}
			break;

			//burning states
			case BCOOKED:
			case COOKED:
			case CHEESED:
			if(g_timer.GetTime()-burgerdata[i][j].time>=COOKTIME)
			{
						burgerdata[i][j].currentState = BURNING;
						burgerdata[i][j].text = NONE;
						burgerdata[i][j].blink = 0.0;
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].blinker = false;
						burgerdata[i][j].time = g_timer.GetTime();
			}
			break;

			case BURNING:
			if(g_timer.GetTime()-burgerdata[i][j].time>=BURNTIME)
			{
						burgerdata[i][j].currentState = BURNT;
						burgerdata[i][j].text = NONE;
						burgerdata[i][j].blink = 0.0;
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].blinker = false;
						burgerdata[i][j].time = g_timer.GetTime();
			}
			break;

			case BURNT:
			if(g_timer.GetTime()-burgerdata[i][j].time>=BURNTIME)
			{
						burgerdata[i][j].currentState = NONE;
						burgerdata[i][j].text = NONE;
						burgerdata[i][j].blink = 0.0;
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].blinker = false;
						burgerdata[i][j].time = g_timer.GetTime();
						score--;
			}
			break; 
			
			case RAWEGG:
			if(g_timer.GetTime()-burgerdata[i][j].time>=EGGTIME)
			{
						burgerdata[i][j].currentState = COOKEDEGG;
						burgerdata[i][j].text = SERVE;
						burgerdata[i][j].blink = g_timer.GetTime();
						burgerdata[i][j].blinked = true;
						burgerdata[i][j].blinker = true;
						burgerdata[i][j].time = g_timer.GetTime();
			}

			case COOKEDEGG:
			if(g_timer.GetTime()-burgerdata[i][j].time>=EGGTIME)
			{
						burgerdata[i][j].currentState = BURNT;
						burgerdata[i][j].text = NONE;
						burgerdata[i][j].blink = 0.0;
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].blinker = false;
						burgerdata[i][j].time = g_timer.GetTime();
			}
			
			}
		}

}
void MouseBurgers(int x, int y, int mouseState)
{
	
	if(mouseState == RIGHT)
	{
		currentItem++;
		if(currentItem>EGG)
			currentItem = BURGER;
	}

	for(int i = 0;i<6;i++)
		for(int j = 0;j<3;j++)
		{
			switch(burgerdata[i][j].currentState)
			{
			case NONE:
				if(mouseState==UP)
				{
					if((x>i*32+96)&&(x<i*32+128)&&(y<j*32+96)&&(y>j*32+64))
					{	
						if(currentItem == BURGER || currentItem == CHEESEBURGER)
						{
							burgerdata[i][j].currentState = RAW;
							burgerdata[i][j].type = currentItem;
							burgerdata[i][j].text = NONE;
							burgerdata[i][j].blink = 0.0;
							burgerdata[i][j].blinked = false;
							burgerdata[i][j].blinker = false;
							burgerdata[i][j].time = g_timer.GetTime();
						}
						else 
						{
							burgerdata[i][j].currentState = RAWEGG;
							burgerdata[i][j].type = currentItem;
							burgerdata[i][j].text = NONE;
							burgerdata[i][j].blink = 0.0;
							burgerdata[i][j].blinked = false;
							burgerdata[i][j].blinker = false;
							burgerdata[i][j].time = g_timer.GetTime();
						}
					}
				}
			break;

			case BCOOKED:
				if(mouseState==UP)
				{
					if((x>i*32+96)&&(x<i*32+128)&&(y<j*32+96)&&(y>j*32+64))
					{					
						burgerdata[i][j].currentState = TCOOKED;
						burgerdata[i][j].text = NONE;
						burgerdata[i][j].blink = 0.0;
						burgerdata[i][j].blinked = false;
						burgerdata[i][j].time = g_timer.GetTime();
					}
				}
			break;

			case COOKED:
				if(mouseState==UP)
				{
					if((x>i*32+96)&&(x<i*32+128)&&(y<j*32+96)&&(y>j*32+64))
					{
						if(burgerdata[i][j].type == CHEESEBURGER)
						{
							burgerdata[i][j].currentState = CHEESED;
							burgerdata[i][j].text = SERVE;
							burgerdata[i][j].blink = g_timer.GetTime();
							burgerdata[i][j].blinked = false;
							burgerdata[i][j].time = g_timer.GetTime();
						}
						else if(burgerdata[i][j].type == BURGER)
						{
							burgerdata[i][j].currentState = NONE;
							burgerdata[i][j].text = NONE;
							burgerdata[i][j].type = NONE;
							burgerdata[i][j].blink = 0.0;
							burgerdata[i][j].blinked = false;
							burgerdata[i][j].time = g_timer.GetTime();

							CheckOrders(BURGER);
						}
					}
				}
			break;
			case CHEESED:
			if(mouseState==UP)
			{
				if((x>i*32+96)&&(x<i*32+128)&&(y<j*32+96)&&(y>j*32+64))
				{
				if(burgerdata[i][j].type == CHEESEBURGER)
				{
					burgerdata[i][j].currentState = NONE;
					burgerdata[i][j].text = NONE;
					burgerdata[i][j].type = NONE;
					burgerdata[i][j].blink = 0.0;
					burgerdata[i][j].blinked = false;
					burgerdata[i][j].time = g_timer.GetTime();

					CheckOrders(CHEESEBURGER);
				}
				}
			}
			break;
			
			case COOKEDEGG:
			if(mouseState == UP)
			{
				if((x>i*32+96)&&(x<i*32+128)&&(y<j*32+96)&&(y>j*32+64))
				{
					burgerdata[i][j].currentState = NONE;
					burgerdata[i][j].text = NONE;
					burgerdata[i][j].type = NONE;
					burgerdata[i][j].blink = 0.0;
					burgerdata[i][j].blinked = false;
					burgerdata[i][j].time = g_timer.GetTime();	

					CheckOrders(EGG);
				}		
			}
			break;

			}
		}
}

void DrawBurgers(gfx* GFX)
{
	for(int i = 0;i<6;i++)
		for(int j = 0;j<3;j++)
		{
			if(burgerdata[i][j].currentState!=NONE)
			{
				
				GFX->DrawImage(i*32+96,j*32+64,SHADOW);
				GFX->DrawImage(i*32+96,j*32+64,burgerdata[i][j].currentState);

				if(burgerdata[i][j].text!=NONE)
					if(!burgerdata[i][j].blinked)
						GFX->DrawImage(i*32+96,j*32+64,burgerdata[i][j].text);
			}
			else GFX->DrawImage(i*32+96,j*32+64,burgerdata[i][j].currentState);
		}
}
//draws orders and other misc gui stuff
void DrawOrders(gfx* GFX)
{
	GFX->DrawImage(0,0,ORDER1);
	GFX->DrawImage(32,0,ORDER2);

	for(int i=0;i<6;i++)
	{
		switch(orderlist[i].type)
		{
		case BURGER:
			GFX->DrawImage(0,32*i+32,COOKED);
		break;
		case CHEESEBURGER:
			GFX->DrawImage(0,32*i+32,CHEESED);
		break;
		case EGG:
			GFX->DrawImage(0,32*i+32,COOKEDEGG);
			break;
		}
	}

	if(happy)
		GFX->DrawImage(96,0,HAPPY);
	else GFX->DrawImage(96,0,SAD);

	GFX->DrawImage(128,32*6,ITEM);

	switch(currentItem)
	{
		case BURGER:
			GFX->DrawImage(160,32*6,COOKED);
		break;
		case CHEESEBURGER:
			GFX->DrawImage(160,32*6,CHEESED);
		break;
		case EGG:
			GFX->DrawImage(160,32*6,COOKEDEGG);
			break;
	}
}

void init()
{
	srand(g_timer.GetTime());
}

void CheckOrders(int type)
{
	for(int i=0;i<6;i++)
	{
		if(orderlist[i].type==type)
		{
			orderlist[i].time = 0.0;
			orderlist[i].type = NONE;
			numorders--;
			happy = true;
			score+=5;
			return;
		}
	}
}

void UpdateOrders()
{
	//start up
	static double lastupdate = g_timer.GetTime();
	
	for(int i=0;i<6;i++)
	{
		if(g_timer.GetTime()-lastupdate>ORDERUPDATE&&(numorders<6))
		{
			if(orderlist[i].type == NONE)
			{
				orderlist[i].time = g_timer.GetTime();
				orderlist[i].type = rand()%3;
			
				lastupdate = g_timer.GetTime();

				numorders++;
			}
		}

		if((g_timer.GetTime()-orderlist[i].time>ORDERTIME)&&orderlist[i].type!=NONE)
		{
			orderlist[i].type = NONE;
			orderlist[i].time = 0.0;
			numorders--;
			score -= 5;
			happy = false; //customer is not happy
		}
	}		
}

void DrawScore(gfx* GFX)
{
	char scoretxt[20];

	wsprintf(scoretxt,"%d",score);

	for(int i = 0; i<strlen(scoretxt)||i<6;i++)
	{
		switch(scoretxt[i])
		{
		case '-':
			GFX->DrawImage(32*i+128,0,MINUS);
		break;
		
		case '0':
			GFX->DrawImage(32*i+128,0,ZERO);
		break;
		case '1':
			GFX->DrawImage(32*i+128,0,ONE);
		break;
		case '2':
			GFX->DrawImage(32*i+128,0,TWO);
		break;
		case '3':
			GFX->DrawImage(32*i+128,0,THREE);
		break;
		case '4':
			GFX->DrawImage(32*i+128,0,FOUR);
		break;
		case '5':
			GFX->DrawImage(32*i+128,0,FIVE);
		break;
		case '6':
			GFX->DrawImage(32*i+128,0,SIX);
		break;
		case '7':
			GFX->DrawImage(32*i+128,0,SEVEN);
		break;
		case '8':
			GFX->DrawImage(32*i+128,0,EIGHT);
		break;
		case '9':
			GFX->DrawImage(32*i+128,0,NINE);
		break;
		}
	}
}

