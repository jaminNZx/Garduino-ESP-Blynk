/**************************************************************

                       General Functions

 **************************************************************/
/*
  getCurrentTime() -
      - return the time as 'HH:MM:SS'
*/
String getCurrentTime() {
  String extraZeroH = "", extraZeroM = "", extraZeroS = "";
  if (hour() < 10) extraZeroH = '0';
  if (minute() < 10) extraZeroM = '0';
  if (second() < 10) extraZeroS = '0';
  return String(extraZeroH + hour()) + ':' + extraZeroM + minute() + ':' + extraZeroS + second();
}
/*
  getCurrentDate() -
      - return the date as 'DD:MM:YY'
*/
String getCurrentDate() {
  return String(day()) + '-' + monthShortStr(month()) + '-' + (year() - 2000);
}
/*
  curDateTime() -
      - return the dat & time as String 'DD:MM:YYYY HH:MM:SS'
*/
String curDateTime() {
  return getCurrentDate() + String(" ") + getCurrentTime();
}
/*
   printTask() - usage 'printTask(String(abc));'
        - outputs to Serial or Terminal or both depending what is defined in settings
*/
void printTask(String a, String b) {
#if defined(OUTPUT_SERIAL)
  Serial.print(a + String("="));
  Serial.println(b);
#endif
#if defined(OUTPUT_TERMINAL)
  terminal.print(a + String("="));
  terminal.println(b);
  terminal.flush();
#endif
}
/*
  sendUptime() - 
      - 
*/
void sendUptime() {
  Blynk.setProperty(vPIN_TERMINAL, "label", String("WIFI: ") + String(map(WiFi.RSSI(), -105, -40, 0, 100)) + String("% (") + WiFi.RSSI() + String("dB)") + String(" | ") + curDateTime() );
  if (month() != month_old && year() != 1970) {
    waterCost_month = 0;
    totalMilliLitres_month = 0;
    month_old = month();
    Blynk.virtualWrite(vPIN_LAST_MONTH, month());
    Blynk.virtualWrite(vPIN_TABLE, "add", rowIndex, "RESET MONTHLY DATA", " ");
    rowIndex++;
  }
}
/*
  normalSync() - 
      - 
*/
void normalSync() {
  if (year() != 1970) {
    setSyncInterval(300);
    printTask("RTC SYNC", "5 MIN");
    timer.disable(timer2);
  }
}
/**************************************************************

                     Flow Sensor

 **************************************************************/
/*
   pulseCounter() -
      - attached to an interrupt counting the pulses from the sensor then used to calculate the rate
*/
void pulseCounter() {
  pulseCount++;
}
/*
   flowSensor() -
      - uses interrupt on the sensor pin
      - calculates the flowRate in mL/s then converts to L/s
      - update Blynk virtual pins with the data
      - calculate and compile the water cost based on the price set in settings and usage
      - calculate and compile the monthly water cost and usage
*/
void flowSensor() {
  detachInterrupt(FLOW_SENSOR);
  flowRate = pulseCount / FLOW_CALIBRATION;
  pulseCount = 0;
  attachInterrupt(FLOW_SENSOR, pulseCounter, FALLING);
  //calc totals
  flowMilliLitres = (flowRate / 60) * 1000;
  totalMilliLitres += flowMilliLitres;
  totalMilliLitres_month += flowMilliLitres;
  Blynk.virtualWrite(vPIN_WATER_TOTAL, (float)totalMilliLitres / 1000);
  Blynk.virtualWrite(vPIN_WATER_FLOW,  String((float)flowMilliLitres, 0));
  Blynk.virtualWrite(vPIN_WATER_TOTAL_MONTH, (float)totalMilliLitres_month / 1000);
  waterCost = waterCost + ( ( ( (float)flowMilliLitres / 1000 ) * WATER_PRICE ) / 100);
  Blynk.virtualWrite(vPIN_WATER_COST, String(waterCost, 6));
  waterCost_month = waterCost_month + ( ( ( (float)flowMilliLitres / 1000 ) * WATER_PRICE ) / 100);
  Blynk.virtualWrite(vPIN_WATER_COST_MONTH, String(waterCost_month, 6));
}
/**************************************************************

                     Tap Control

 **************************************************************/
/*
  finish_TAP_shutdown() -
      - print to terminal the used stats and cost
      - turn off status led widget
      - write the usage and cost to the table in two lines
*/
void finish_TAP_shutdown() {
  printTask("TAP", "OFF");
  printTask("USED", String((float)totalMilliLitres / 1000) + String("L  COST=$") + String(waterCost, 6));
  Blynk.virtualWrite(vPIN_TAP_LED, 0);
  Blynk.virtualWrite(vPIN_TABLE, "add", rowIndex, curDateTime(), String( (float)totalMilliLitres / 1000, 6) + String(" L"));
  rowIndex++;
  Blynk.virtualWrite(vPIN_TABLE, "add", rowIndex, " ", String("$") + String(waterCost, 6));
  rowIndex++;
}
/*
  TAP_Off() -
      - only trigger if relay is active
      - turn off tap relay
      - dim status led widget to half brightness
      - after 6sec it goes in to it shuts down
*/
void TAP_Off() {
  if (!digitalRead(TAP)) {
    digitalWrite(TAP, HIGH);
    Blynk.virtualWrite(vPIN_TAP_LED, 128);
    printTask("TAP", "SHUTTING DOWN..");
    timer.setTimeout(6000, finish_TAP_shutdown);
  }
}
/*
  tap_limit_value_waterchecker() -
        - A timed function that checks if the use limit is reached and shuts down the tap
*/
void tap_limit_value_waterchecker() {
  if (tap_limit_value <= (float)totalMilliLitres / 1000) {
    timer.disable(timer1);
    TAP_Off();
  }
}
/*
   TAP_On() -
      - reset 'current' used used and cost
      - turn on tap relay
      - turn on led status widget
      - depending on limit type start a timer to stop the tap
*/
void TAP_On() {
  totalMilliLitres = 0;
  waterCost = 0;
  digitalWrite(TAP, LOW);
  Blynk.virtualWrite(vPIN_TAP_LED, 255);
  switch (limitType) {
    case 1:
      printTask("TAP=ON  LIMIT", String(tap_limit_value / 1000) + String(" SEC"));
      timer.setTimeout(tap_limit_value, TAP_Off);
      break;
    case 2:
      printTask("TAP=ON  LIMIT", String(tap_limit_value) + String(" LTRS"));
      timer1 = timer.setInterval(250, tap_limit_value_waterchecker);
      break;
  }
}
/*
  TAP_Toggle() -
      - Toggles the tap state.
*/
void TAP_Toggle() {
  if (digitalRead(TAP)) {
    TAP_On();
  } else {
    TAP_Off();
  }
}



