#ifndef BILDSPUR_LOGBOOK_H
#define BILDSPUR_LOGBOOK_H

#include <Arduino.h>

class LogBook {
private:
  static unsigned long baudRate;
  static bool isLogging;

  LogBook();

public:
  static void setup(unsigned long baudRate, bool isLogging = true);

  static void print(String message);
  static void println(String message);
};
#endif
