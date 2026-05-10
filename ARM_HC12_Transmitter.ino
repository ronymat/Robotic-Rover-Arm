#include <Wire.h>

int uart2[] = {17, 16}; // (Tx, Rx)

const int MPU_addr = 0x68;
int sdaPin = 18;
int sclPin = 22;
int shoulderAngle = 90;
int elbowAngle = 90;
int baseAngle = 90;
int16_t AcX, AcY, AcZ;

long pmillis = 0;
long cmillis = 0;
void setup()
{
    Serial.begin(9600);
    Serial2.begin(9600, SERIAL_8N1, uart2[1], uart2[0]);
    Serial2.setTimeout(50);

    Serial.println("The device started, now you can pair it with bluetooth!");
    Serial.println("Initializing I2C devices...");

    Wire.begin(sdaPin, sclPin);
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x6B); // PWR_MGMT_1 register
    Wire.write(0);    // set to zero (wakes up the MPU-6050)
    Wire.endTransmission(true);
}

void loop()

{

    getacceldata();
    // Map MPU6050 data to angles (optional, adjust as needed)
    int pitch = map(AcY, -17000, 17000, 0, 180); // Example mapping
    int roll = map(AcX, -17000, 17000, 0, 180);  // Example mapping
    int yaw = map(AcZ, -17000, 17000, 0, 180);   // Example mapping
    baseAngle = constrain(pitch, 0, 180);
    shoulderAngle = constrain(roll, 0, 180);
    elbowAngle = constrain(yaw, 0, 180);

    // Prepare data to send
    String data = String(baseAngle) + "," + String(shoulderAngle) + "," + String(elbowAngle);
    Serial.println(data);
    Serial2.println(data);
    delay(200);
}

void getacceldata()
{
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers

    // reading accelerometer data
    AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    // Serial.println((String) "X:" + AcX + "\tY:" + AcY + "\tZ:" + AcZ);
}
