#include "LogBook.h"
#include <Arduino.h>

unsigned long LogBook::baudRate;
bool LogBook::isLogging;

void LogBook::setup(unsigned long baudRate, bool isLogging) {
  LogBook::isLogging = isLogging;
  LogBook::baudRate = baudRate;

  Serial.begin(baudRate);
}

void LogBook::print(String message) {
  if (isLogging)
    Serial.print(message);
}

void LogBook::println(String message) {
  if (isLogging)
    Serial.println(message);
}

LogBook::LogBook() = default;
