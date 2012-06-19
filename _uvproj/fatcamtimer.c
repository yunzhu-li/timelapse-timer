	
#include <XSTC89.H>
#include <stdio.h>
#include <lcd1602.h>
#include <delayms.h>


unsigned int _setTime;
unsigned int _remainingTime;
unsigned int _timerStatus;




void _showNum(char _row)
{
	char _msg[32];

	if(!_row){
		//Print SetTime
		if(_setTime < 10){
			sprintf(_msg, "SET TIMER: %d s  ", _setTime);
		}else
		if(_setTime >= 10 && _setTime <= 99){
			sprintf(_msg, "SET TIMER: %d s ", _setTime);
		}else
		if(_setTime > 99){
			sprintf(_msg, "SET TIMER: %d s", _setTime);
		}
		lcdshowstring(0, _msg);	
	}
	
	if(_row){
		if(!_timerStatus){
			sprintf(_msg, "    OFF         ", _remainingTime);
		}else{
			//Print RemainingTime
			if(_remainingTime < 10){
				sprintf(_msg, "    ON     %d s  ", _remainingTime);
			}else
			if(_remainingTime >= 10 && _remainingTime <= 99){
				sprintf(_msg, "    ON     %d s ", _remainingTime);		
			}else
			if(_remainingTime > 99){
				sprintf(_msg, "    ON     %d s", _remainingTime);	
			}
		}
		lcdshowstring(1, _msg);	
	}

}

void _releaseShutter()
{
	char _msg[32];

	sprintf(_msg, "    ON  R  0 s  ");
	lcdshowstring(1, _msg);	
	P1_5 = 0x01;
	DelayMs(100);
	P1_5 = 0x00;


}


void _timerFunc()
{
	unsigned char _lastCtrlKeyStat;
	_lastCtrlKeyStat = 1;

	_remainingTime++;
	
	while(1)
	{
		if(!--_remainingTime){
		_releaseShutter();
		_remainingTime = _setTime;
		}
		if((_lastCtrlKeyStat == 0) && (P1_2 == 0x00)){break;}
		_lastCtrlKeyStat = P1_2;
		showNum(1);
		DelayMs(1000);
	}
	
	_timerStatus = 0;
	showNum(1);
	
	DelayMs(2000);
	
}


void main()
{
	char _msg[32];
		
	P1_5 = 0x00;
		
	_setTime = 10;
	_remainingTime = 20;
	_timerStatus = 0;

	lcdinit();


	
	sprintf(_msg, "FAT TIMER Ver 2 ");
	lcdshowstring(0, _msg);	
	sprintf(_msg, "Starting...     ");
	lcdshowstring(1, _msg);	

	DelayMs(2000);

	_showNum(0);
	_showNum(1);


	while(1)
	{
		//Start / Stop
		if(P1_2 == 0x00)
		{
			DelayMs(2);
			if(P1_2 == 0x00){
				_timerStatus = 1;
				_remainingTime = _setTime;
				showNum(1);
				_timerFunc();
			}
		}
		
	
	
	
		//+ / -
		if(P1_0 == 0x00)
		{
			DelayMs(2);
			if(P1_0 == 0x00)
				{
					if(_setTime > 1)
					{
						_setTime--;
						showNum(0);
						DelayMs(15);
						continue;
					}
				}
		}else
		if(P1_1 == 0x00)
			DelayMs(2);
			if(P1_1 == 0x00)
				{
					if(_setTime < 999)
					{
						_setTime++;
						showNum(0);
						DelayMs(15);
						continue;
					}
				}
	}//while

}







