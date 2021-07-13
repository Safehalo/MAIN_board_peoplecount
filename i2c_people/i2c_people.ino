#include <Wire.h>
#define Sensor_1_add 0x07
#define Sensor_2_add 0x08
#define Sensor_3_add 0x09
float old_value = 0, 
Sensor_1_new_value = 0, 
Sensor_2_new_value = 0, 
Sensor_3_new_value = 0, 
Sensor_1_old_value = 0, 
Sensor_2_old_value = 0, 
Sensor_3_old_value = 0;
char c[15];
char temp_char;
char x[15];
char v[8];
void setup() {
  Wire.begin(8);       // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

void loop() {
  sensor_read_value(Sensor_1_add, 17);
  parsing_val(Sensor_1_add);
  if(val_comparsion(Sensor_1_old_value, Sensor_1_new_value))
  {
    Sensor_1_old_value = Sensor_1_new_value;  
   }
  delay(100);
  sensor_read_value(Sensor_2_add, 17);
  parsing_val(Sensor_2_add);
  if(val_comparsion(Sensor_2_old_value, Sensor_2_new_value))
  {
    Sensor_2_old_value = Sensor_2_new_value;
  }
  delay(100);
  sensor_read_value(Sensor_3_add, 17);
  parsing_val(Sensor_3_add);
  if(val_comparsion(Sensor_3_old_value, Sensor_3_new_value))
  {
    Sensor_3_old_value = Sensor_3_new_value;
  }
  delay(100);
}

uint8_t sensor_read_value(int _add_, int _rec_byte_val) {
  Wire.requestFrom(_add_, _rec_byte_val, true);  // request 6 bytes from slave device #8
  while (Wire.available()) {                     // slave may send less than requested
    for (int i = 0; i < _rec_byte_val; i++) {
      temp_char = Wire.read();
      if(i<15)
        c[i] =temp_char;   // receive a byte as character
      //Serial.println(c);         // print the character
    }
  }
}

uint8_t parsing_val(int sensor_no) {
  for (int i = 4; i < 15; i++) {
    int j;
    v[j] = c[i];
    j++;
  }
  float new_value = atof(v);
  if (sensor_no == 7)
  {
    Sensor_1_new_value = new_value ;
  }
  if (sensor_no == 8)
  {
    Sensor_2_new_value = new_value ;
  }
  if (sensor_no == 9)
  {
    Sensor_3_new_value = new_value ;
  }
}

bool val_comparsion(int Sensor_old_value, int Sensor_new_value)
{
  if (Sensor_old_value != Sensor_new_value) {
    Sensor_old_value = Sensor_new_value;
    for (int i = 0; i < 15; i++) {
     x[i] = c[i];
  }
  Serial.println(x);
  return true;
}
else {return false;}
}
