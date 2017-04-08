/**************************************************************

                     BLYNK_WRITE

 **************************************************************/
/*
  Usage limit menu selector
*/
BLYNK_WRITE(vPIN_LIMITMENU) {
  switch (param.asInt()) {
    case 1:
      limitType = param.asInt();
      printTask("LIMITED BY", "TIME");
      Blynk.setProperty(vPIN_TAP_LIMIT, "label", "TIME: MINUTES");
      break;
    case 2:
      limitType = param.asInt();
      printTask("LIMITED BY", "WATER");
      Blynk.setProperty(vPIN_TAP_LIMIT, "label", "WATER: LITRES");
      break;
  }
  Blynk.syncVirtual(vPIN_TAP_LIMIT);
}
/*
  Usage limit slider
*/
BLYNK_WRITE(vPIN_TAP_LIMIT) {
  switch (limitType) {
    case 1:
      tap_limit_value = param.asInt() * 60000;
      printTask("TAP LIMIT", String(tap_limit_value / 1000) + String(" SEC"));
      break;
    case 2:
      tap_limit_value = param.asInt() * 10;
      printTask("TAP LIMIT", String(tap_limit_value) + String(" LTRS"));
      break;
  }
}
/*
  Old manual button, I think this is to be erased?
*/
BLYNK_WRITE(vPIN_TAP_MANUAL) {
  TAP_Toggle();
}
/*
  Activate button
*/
BLYNK_WRITE(vPIN_TAP_ACTIVATE) {
  (param.asInt() && digitalRead(TAP)) ? TAP_On() : TAP_Off();
}
/*
  Total water cost month
*/
BLYNK_WRITE(vPIN_WATER_COST_MONTH) {
  waterCost_month = param.asFloat();
  printTask("SYNC WATER COST", String(waterCost_month, 6));
}
/*
  Total water used this month
*/
BLYNK_WRITE(vPIN_WATER_TOTAL_MONTH) {
  totalMilliLitres_month = param.asFloat() * 1000;
  printTask("SYNC WATER USE", String((float)totalMilliLitres_month / 1000));
}
/*
  Last Month Widget
*/
BLYNK_WRITE(vPIN_LAST_MONTH) {
  month_old = param.asInt();
  printTask("SYNC MONTH", String(month_old));
}
/*

*/

