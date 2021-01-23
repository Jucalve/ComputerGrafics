#include<cstring>
#include<iostream>
#include<random>
#include<windows.h>
#include<math.h>
#define PI 3.14159265
using namespace std;

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

class FHDRaster {
  unsigned char data[1920][1080][3];
  public:
  FHDRaster(void) {
    memset(data, 0, 1920*1080*3);  
  }
  void
  setPixel(unsigned int x, unsigned int y, 
            unsigned char r, 
            unsigned char g, 
            unsigned char b) {
      if( x >= 1920 || y >= 1080) {
        return;
      }
      data[x][y][0] = r;
      data[x][y][1] = g;
      data[x][y][2] = b;
  }
  void
  write(void) {
   int x = 0;
   int y = 0;
   COLORREF COLOR;
   int pixel =0;
   cout<<"P6\n1920 1080 255\n";
   for(y=0;y<1080;y++) {
     for(x=0;x<1920;x++) {
      COLOR = RGB(data[x][y][0],data[x][y][1],data[x][y][2]); 
      SetPixel(mydc,x,y,COLOR);
      
      
     } 
   }
  }
//Obtiene el signo del entero recibido
sgn(int x){
	if (x >= 0) return 1;
if (x < 0) return -1;

}
//Usando el algoritmo DDA Digital Differential Analyzer 
drawLine( int x1, int y1, int x2, int y2, int r, int g, int b)
{
    float d, x, y;

    float dx = (x2-x1);
    float dy = (y2-y1);

    if ( abs(dx) > abs(dy) )		//Obtiene el número de pasos necesarios
       d = abs(dx);
    else
       d = abs(dy);
    float vx = dx / d;				//Obtine los incrementos de x y y
    float vy = dy / d;
    x = x1+sgn(x1)*0.5;				//obtiene el punto inicial
    y = y1+sgn(y1)*0.5;
    for (int i = 0; i <= d; i++)

    {	setPixel(floor(x),floor(y),r,g,b);	//Coloca el pixel e incrementa
        x = x + vx;
        y = y + vy;
    }
}

circle (){
  int x=960;
  int y=540;
  int d=500;
  int x1,y1;
  for (float i = 0; i < 360; i+=0.00005)
  {
    /* code */
    x1= (( sin (i*PI/180))*d)+960;
   y1= ((cos (i*PI/180))*d)+540;
    drawLine(x,y,x1,y1,(int)i%255,(int)i%255,(int)i%255);

  }
}
};
int main(void) {
 FHDRaster * raster = new FHDRaster();
 unsigned int x = 0;
 unsigned int y = 0;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;
 int n = 0;


 raster->circle();//dorado


 raster->write();
 
 ReleaseDC(myconsole, mydc);
 getchar();
 return 0;
}