/**************************************************************

                            Globals

 **************************************************************/
SimpleTimer timer;

WidgetTerminal terminal(vPIN_TERMINAL);
WidgetRTC rtc;

int limitType, tap_limit_value, timer1, timer2, timer3, rowIndex = 0, month_old;
volatile byte pulseCount = 0;
float flowRate = 0.00, waterCost, waterCost_month;
float flowMilliLitres;
float totalMilliLitres, totalMilliLitres_month;

