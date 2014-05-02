#define image_width 16
#define image_height 16

static unsigned char image_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x20, 0x04, 0x10, 0x08, 0x00, 0x00, 0x20, 0x04,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x08, 0x30, 0x0c, 0xd0, 0x0b,
   0x20, 0x04, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00 };

void setup(){
  Serial.begin(9600);
  int i = 0;
  int widthCount = 0;
  while(i < sizeof(image_bits)/sizeof(image_bits[0])){
    int j;
    for(j = 0;j<8;j++){
      Serial.print(bitRead(image_bits[i],j));
      widthCount++;
      if(widthCount % image_width == 0){
        Serial.print("\n");
      }
    }
    i++;
  }
}

void loop(){
}
