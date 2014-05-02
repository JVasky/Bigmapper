#include "image.xbm"
#include<stdio.h>
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
int main(){
  int i = 0;
  int widthCount = 0;
  while(i < sizeof(image_bits)/sizeof(image_bits[0])){
    int j;
    for(j = 0;j<8;j++){
      printf("%hu", bitRead(image_bits[i],j));
      widthCount++;
      if(widthCount % image_width == 0){
	printf("\n");
      }
    }
    i++;
  }
  return 0;
}
