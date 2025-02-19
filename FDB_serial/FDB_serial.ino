const byte connect_pin = 2;
const byte publish_pin = 1;
void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 18, 17);
  pinMode(connect_pin, OUTPUT); 
  pinMode(publish_pin, OUTPUT); 
}

void loop() {
  read_METTLER_TOLEDO();

}

void read_METTLER_TOLEDO() {
  digitalWrite(connect_pin, HIGH);
  digitalWrite(publish_pin, LOW);
  if (Serial1.available() > 0) { 
    String data = Serial1.readStringUntil('\n');        // อ่านข้อมูลจนถึงตัวขึ้นบรรทัดใหม่
    int pos_g = data.indexOf("g");                      // หาตำแหน่งของ "g"
    if (pos_g != -1) {                                  // ถ้าพบ "g"
      String value_str = data.substring(0, pos_g + 1);  // ดึงข้อมูลตั้งแต่ต้นถึงตำแหน่งที่ "g" อยู่
      value_str.trim();                                 // ตัดช่องว่างหน้า-หลังข้อมูล
      float measure_data = value_str.toFloat();         // แปลงเป็น float
      Serial.println(String(measure_data, 4));          //ทศนิยม
      digitalWrite(publish_pin, HIGH);
      delay(300);
      digitalWrite(publish_pin, LOW);
    }
  }
}