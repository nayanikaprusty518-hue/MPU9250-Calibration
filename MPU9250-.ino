#include <Wire.h>
#include <MPU9250_asukiaaa.h>

MPU9250_asukiaaa mpu(0x68);

#define SDA_PIN 6
#define SCL_PIN 7

// ===== Your calibration values =====
float gx_off = -0.83;
float gy_off = -2.97;
float gz_off = -1.65;

float ax_off = 0.12;
float ay_off = 0.03;
float az_off = -10.79;

// Complementary filter variables
float roll = 0, pitch = 0, yaw = 0;
unsigned long lastTime;

// ===== Angle wrapping function =====
float wrapAngle(float angle) {
  while (angle > PI)  angle -= 2 * PI;
  while (angle < -PI) angle += 2 * PI;
  return angle;
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginGyro();

  delay(2000);
  lastTime = millis();

  Serial.println("=== MPU6500 IMU Fusion Started (FINAL) ===");
}

void loop() {
  mpu.accelUpdate();
  mpu.gyroUpdate();

  float dt = (millis() - lastTime) / 1000.0;
  lastTime = millis();

  // Apply calibration
  float ax = mpu.accelX() - ax_off;
  float ay = mpu.accelY() - ay_off;
  float az = mpu.accelZ() - az_off;

  float gx = (mpu.gyroX() - gx_off) * PI / 180.0;
  float gy = (mpu.gyroY() - gy_off) * PI / 180.0;
  float gz = (mpu.gyroZ() - gz_off) * PI / 180.0;

  // Roll & Pitch from accel
  float rollAcc  = atan2(ay, az);
  float pitchAcc = atan2(-ax, sqrt(ay * ay + az * az));

  // Complementary filter
  roll  = 0.98 * (roll  + gx * dt) + 0.02 * rollAcc;
  pitch = 0.98 * (pitch + gy * dt) + 0.02 * pitchAcc;
  yaw   = yaw + gz * dt;

  // ===== Wrap angles after update =====
  roll  = wrapAngle(roll);
  pitch = wrapAngle(pitch);
  yaw   = wrapAngle(yaw);

  // Convert to degrees
  float rollDeg  = roll  * 180.0 / PI;
  float pitchDeg = pitch * 180.0 / PI;
  float yawDeg   = yaw   * 180.0 / PI;

  Serial.print("Roll: ");
  Serial.print(rollDeg);
  Serial.print("  Pitch: ");
  Serial.print(pitchDeg);
  Serial.print("  Yaw(gyro): ");
  Serial.println(yawDeg);

  delay(20);
}
