#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Adafruit_LiquidCrystal.h"
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

#define REPORTING_PERIOD_MS 1000
#define ONE_WIRE_BUS 3
#define ECG_output_Pin A0

uint32_t tsLastReport = 0;
PulseOximeter pox;
Adafruit_MPU6050 mpu;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
Adafruit_LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

void onBeatDetected() {
  Serial.println("Beat detected!");
}

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(ECG_output_Pin, INPUT);
  lcd.begin(16, 2);

  // Initialize MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);

  // Initialize MAX30100
  if (!pox.begin()) {
    Serial.println("FAILED to initialize MAX30100");
    while (1);
  } else {
    Serial.println("MAX30100 initialized successfully");
  }

  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  pox.update();

  // Reporting every REPORTING_PERIOD_MS
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    float heartRate = pox.getHeartRate();
    float spo2 = pox.getSpO2();

    if (isnan(heartRate) || isnan(spo2)) {
      Serial.println("Invalid HR or SpO2 reading.");
      lcd.setCursor(0, 0);
      lcd.print("HR: -- bpm       ");
      lcd.setCursor(0, 1);
      lcd.print("SpO2: -- %       ");
    } else {
      Serial.print("HR: ");
      Serial.print(heartRate);
      Serial.print(" bpm, SpO2: ");
      Serial.print(spo2);
      Serial.println("%");

      lcd.setCursor(0, 0);
      lcd.print("HR: ");
      lcd.print(heartRate);
      lcd.print(" bpm");

      lcd.setCursor(0, 1);
      lcd.print("SpO2: ");
      lcd.print(spo2);
      lcd.print("%        ");
    }
    tsLastReport = millis();
  }

  // Read ECG signal
  int ecgSignal = analogRead(ECG_output_Pin);
  Serial.print("ECG Signal: ");
  Serial.println(ecgSignal);

  // Read Temperature from DS18B20
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);

  Serial.print("Temperature in Celsius: ");
  Serial.println(temperatureC);
  Serial.print("Temperature in Fahrenheit: ");
  Serial.println(temperatureF);

  // Read MPU6050 data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2 ");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  // Fall Detection Logic
  float totalAcceleration = sqrt(
    a.acceleration.x * a.acceleration.x +
    a.acceleration.y * a.acceleration.y +
    a.acceleration.z * a.acceleration.z
  );

  static bool fallDetected = false;

  if (totalAcceleration < 0.5) {
    Serial.println("Possible Free Fall Detected!");
  } else if (totalAcceleration > 20.0) {
    if (!fallDetected) {
      Serial.println("Fall Detected! High impact.");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("FALL DETECTED!");
      fallDetected = true;
    }
  } else {
    fallDetected = false;
  }

  // Display MPU6050 data on LCD (can remove if LCD is used for fall alert only)
  // You can remove these two lines if you only want fall alerts on LCD
  lcd.setCursor(0, 0);
  lcd.print("Ax:");
  lcd.print(a.acceleration.x);
  lcd.print(" Ay:");
  lcd.print(a.acceleration.y);

  lcd.setCursor(0, 1);
  lcd.print("Az:");
  lcd.print(a.acceleration.z);
  lcd.print(" Wx:");
  lcd.print(g.gyro.x);

  delay(1000); // Adjust delay to balance update rates and performance
}
