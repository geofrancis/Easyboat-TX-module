void Telemetry(){
  
val = tel1;
angle =  tel2;
avoidmode = tel3;
  
 // Set airspeed sensor (ASS) data
  ass.setData(76.5);  // Airspeed in km/h

  // Set ESC sensor data
  esc.setData(12.6,   // ESC voltage in volts
              22.1,   // ESC current draw in amps
              10900,  // ESC motor rotations per minute
              20000,  // ESC current consumtion in mAh
              45.6,   // ESC temperature in degrees Celsius (can be negative, will be rounded)
              6.7,    // ESC SBEC voltage in volts
              0.10);  // ESC SBEC current draw in amps

  // Set current/voltage sensor (FCS) data
  // (set Voltage source to FAS in menu to use this data for battery voltage,
  //  set Current source to FAS in menu to use this data for current readins)
  fcs.setData(25.3,   // Current consumption in amps
              12.6);  // Battery voltage in volts

  // Set LiPo voltage sensor (FLVSS) data (we use two sensors to simulate 8S battery 
  // (set Voltage source to Cells in menu to use this data for battery voltage)
  flvss1.setData(4.07, 4.08, 4.09, 4.10, 4.11, 4.12);  // Cell voltages in volts (cells 1-6)
  flvss2.setData(4.13, 4.14);                          // Cell voltages in volts (cells 7-8)

  // Set GPS sensor data
  gps.setData(48.858289, 2.294502,  // Latitude and longitude in degrees decimal (positive for N/E, negative for S/W)
              245.5,                // Altitude in m (can be negative)
              100.0,                // Speed in m/s
              90.23,                // Course over ground in degrees (0-359, 0 = north)
              14, 9, 14,            // Date (year - 2000, month, day)
              12, 00, 00);          // Time (hour, minute, second) - will be affected by timezone setings in your radio

  // Set RPM/temperature sensor data
  // (set number of blades to 2 in telemetry menu to get correct rpm value)
  rpm.setData(200,    // Rotations per minute
              25.6,   // Temperature #1 in degrees Celsuis (can be negative, will be rounded)
              -7.8);  // Temperature #2 in degrees Celsuis (can be negative, will be rounded)

  // Set SP2UART sensor data
  // (values from 0.0 to 3.3 are accepted)
  sp2uart.setData(1.5,   // ADC3 voltage in volts
                  3.3);  // ADC4 voltage in volts

  // Set variometer data
  // (set Variometer source to VSpd in menu to use the vertical speed data from this sensor for variometer).
  vario.setData(250.5,  // Altitude in meters (can be negative)
                -1.5);  // Vertical speed in m/s (positive - up, negative - down)

#ifdef POLLING_ENABLED
  // Set receiver data to be sent in case the polling is enabled (so no actual receiver is used)
  telemetry.setData(90,    // RSSI value (0-100, 0 = no telemetry, 100 = full signal)
                    4.9);  // RxBatt (voltage supplied to the receiver) value in volts (0.0-13.2)
#endif

  // Send the telemetry data, note that the data will only be sent for sensors
  // that are being polled at given moment
  telemetry.send();





}
