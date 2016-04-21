#ifndef GAME_H
#define GAME_H

#include "gfx.h"
#include "timer.h"

//item types
#define BURGER 0 //4 stages, raw, bottom cooked, top cooked, cooked
#define CHEESEBURGER  1 //5 stages, raw, bottom cooked, top cooked, cooked, cheesed
#define EGG 2 // 2 stages, raw, cooked

//mouse states
#define UP 0
#define DOWN 1
#define RIGHT 2

//image indices and burger states

#define LU_BAR 0 
#define U_BAR 1
#define RU_BAR 2

#define SERVED 3
#define SERVING 4
#define COOKED 5
#define CHEESED 6
#define BCOOKED 7
#define TCOOKED 8
#define RAW 9 

#define L_BAR 10
#define NONE 11
#define R_BAR 12

#define FLIP 13
#define SERVE 14
#define CHEESE 15

#define SHADOW 16
#define BURNING 17
#define BURNT 18
#define COOKEDEGG 19

#define LD_BAR 20
#define D_BAR 21
#define RD_BAR 22

#define RAWEGG 23

#define CURSOR 24
#define ORDER1 25
#define ORDER2 26

#define ITEM 27
#define HAPPY 28
#define SAD 29

#define ZERO 30
#define ONE 31 
#define TWO 32
#define THREE 33
#define FOUR 34
#define FIVE 35
#define SIX 36
#define SEVEN 37
#define EIGHT 38
#define NINE 39
#define MINUS 40

#define COOKTIME 1.75 
#define EGGTIME 1.0
#define BURNTIME 0.25
#define BLINKTIME 0.1

#define ORDERTIME 11.0
#define ORDERUPDATE 1.0

extern timer g_timer;

class burger
{
public:
	burger();

	int currentState; //burger state
	int text; // the text on the burger, flip, 
	double time; //time of last update
	double blink; //time till the blink state changes
	bool blinked; //whether or not to draw the burger or text blinked
	bool blinker; //should we check for blinking?

	int type; //burger, chesse burger, egg 
};

class order
{
public:
	order();
	int type;
	double time;
};

//burger burgerdata[6][3];

void init();
void UpdateOrders();
void CheckOrders(int type);
void DrawOrders(gfx* GFX);
void DrawScore(gfx* GFX);

void UpdateBurgers();
void MouseBurgers(int x, int y, int mouseState);
void DrawBackground(gfx* GFX);
void DrawBurgers(gfx* GFX);

#endif 