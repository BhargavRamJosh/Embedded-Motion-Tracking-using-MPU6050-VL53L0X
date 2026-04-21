#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_VL53L0X.h>

#define SDA_PIN 21
#define SCL_PIN 22

#define BASELINE_MM 1676.0   // Given baseline

MPU6050 mpu;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

// Complementary filter variables
float angle = 0.0;
float alpha = 0.98;
unsigned long prevTime = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  // MPU6050 Init
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed!");
    while (1);
  }

  // VL53L0X Init
  if (!lox.begin()) {
    Serial.println("VL53L0X not detected!");
    while (1);
  }

  prevTime = millis();
  Serial.println("System Initialized Successfully");
}

void loop() {

  // ---------- IMU READ ----------
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Convert accelerometer to angle (pitch)
  float accelAngle = atan2(ax, az) * 180 / PI;

  // Gyro rate (deg/sec)
  float gyroRate = gy / 131.0;

  unsigned long currentTime = millis();
  float dt = (currentTime - prevTime) / 1000.0;
  prevTime = currentTime;

  // Complementary filter
  angle = alpha * (angle + gyroRate * dt) + (1 - alpha) * accelAngle;

  // Convert angle → height difference
  float angleRad = angle * PI / 180.0;
  float heightDiff = BASELINE_MM * sin(angleRad);

  // ---------- VL53L0X READ ----------
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false);

  float displacementMM = 0;

  if (measure.RangeStatus != 4) {
    displacementMM = measure.RangeMilliMeter;
  }

  // ---------- OUTPUT ----------
  Serial.print("Tilt Angle (deg): ");
  Serial.print(angle, 2);

  Serial.print(" | Height Diff (mm): ");
  Serial.print(heightDiff, 2);

  Serial.print(" | Displacement (mm): ");
  Serial.println(displacementMM, 2);

  delay(100);
}
