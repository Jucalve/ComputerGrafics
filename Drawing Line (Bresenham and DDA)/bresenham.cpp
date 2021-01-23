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
   /*HWND myconsole = GetConsoleWindow();
   HDC mydc = GetDC(myconsole);*/
   COLORREF COLOR;
   int pixel =0;
  
   for(y=0;y<1080;y++) {
     for(x=0;x<1920;x++) {
      COLOR = RGB(data[x][y][0],data[x][y][1],data[x][y][2]); 
      SetPixel(mydc,x,y,COLOR);
      /*cout<<data[x][y][0];
      cout<<data[x][y][1];
      cout<<data[x][y][2];*/
      
     } 
   }
  }



void drawLine(unsigned int x,unsigned int y,unsigned int x2, unsigned int y2,unsigned int r, unsigned int g, unsigned int b) {
    int DeltaX = x2 - x ;
    int DeltaY = y2 - y ;

    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;

    if (DeltaX<0){
      dx1 = -1 ; 
      dx2 = -1 ; 

    }
    else if (DeltaX>0){
      dx1 = 1 ;
      dx2 = 1 ;
    }


    if (DeltaY<0) dy1 = -1 ; 

    else if (DeltaY>0) dy1 = 1 ;


    int longest = abs(DeltaX) ;
    int shortest = abs(DeltaY) ;

    if (!(longest>shortest)) {
        longest = abs(DeltaY) ;
        shortest = abs(DeltaX) ;

        if (DeltaY<0) dy2 = -1 ; 

        else if (DeltaY>0) dy2 = 1 ;
        
        dx2 = 0 ;            
    }

   
    int numerator = longest >> 1 ; //Dividir entre 2 :v

    for (int i=0;i<=longest;i++) {
        setPixel(x,y,r,g,b) ;
        numerator += shortest ;
        
        if (!(numerator<longest)) {
            numerator -= longest ;
            x += dx1 ;
            y += dy1 ;
        } 
        else {
            x += dx2 ;
            y += dy2 ;
        }
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



/* void drawLine( 
  unsigned int x1, unsigned int y1, 
   unsigned int x2, unsigned int y2, 
    unsigned char r,
    unsigned char g,
    unsigned char b) {
      /* Line drawing algorithm: Bresenham (middle point) */
     
      //    y = m*x + b    line eq. -> DDA -> Bresenham 

      // Bresenham: integer operations
      //  observation: the decision is binary
      /// decision is made using the distance between:
      ///     next pixel and the middle point.
      ////   two distances: d1 and d2
      //    d1 from the upper option and middle point
      //    d2 from the lower option and middle point.
      // d2 == d1?   choose the lower, deltaY = 0
      // d2  > d1     choose the upper, 
      // d2  < d1     choose the lower.
      //  (d1 - d2) >= 0, lower option
      //  (d1 - d2) < 0, upper option
      //  just need to check the sign of (d1-d2)
      //  using 'improvements' he reach:  C*(d1-d2)
      //     ->>>  result is:   just integer operation, and does not 
      //                        change the sign. 
     /* cout<<"bruh\n";
      double m = (double)(y2-y1)/(double)(x2-x1); //slope
      double be = (double)y1 - (m*x1) ;
      unsigned int x = 0;
      unsigned int y = 0;
      int dx = x2 - x1;
      int dy = y2 - y1;  
      int p = 2*dy-dx;  /// change 2* using bit operation.
      int updateUp    = 2*dy;          // -
      int updateRight = 2*dy-2*dx;     // +

 // (0,0) -> (1000,  500) 
 // dx = 1000,   dy = 500
 // Up = 1000 - 2000 = -1000 (-)
 // Ri =             =  1000 (+)

      setPixel(x1, y1, r, g, b);
      setPixel(x2, y2, r, g, b);    //            ***  
                                    ///        ***
      y = m*x1 + be;                ///y1-> ***
      for( x = x1 + 1 ; x < x2 ; x++ ) {   // deltaX = 1
                                    // deltaY = 0 or 1
        /// p = 0
        if( p < 0 ) { // < decision parameter
          y++;
          p += updateUp;    // < update
        } else {
          p += updateRight; // < update
        }   // p = -++-++---+++-+++---  /// <<< goal
            // p = +++++++++++++++++++  /// <<< wrong
        setPixel(x, y, r, g, b); /// raster space array[0][0];
                                 /// image space: -y
      } 
   }
};

/* testing */
};

int main(void) {
 FHDRaster * raster = new FHDRaster();
 unsigned int x = 0;
 unsigned int y = 0;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;
 int n = 0;
 /*
 default_random_engine generator;
 uniform_int_distribution<unsigned int> distX(0,1919);
 uniform_int_distribution<unsigned int> distY(0,1079);
 uniform_int_distribution<unsigned char> distC(0x00,0xff);
 for(n=0; n<100000; n++) {
   x = distX(generator);
   y = distY(generator);
   r = distC(generator);
   g = distC(generator);
   b = distC(generator);
   raster->setPixel(x,y, r, g, b);
 }
 */
raster->circle();
 raster->write();
 /*HWND myconsole = GetConsoleWindow();
 HDC mydc = GetDC(myconsole);*/
 ReleaseDC(myconsole, mydc);
 getchar();
 return 0;
}