#include <stdio.h>
#include <vector>
#include <array>
#include <math.h>
#include<cstring>
#include<iostream>
#include<random>
#include<windows.h>

using namespace std;

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

class FHDRaster {
  unsigned char data[1920][1080][3];
  public:
  FHDRaster(void) {
    memset(data, 0, 1920*1080*3);  
  }
  void setPixel(unsigned int x, unsigned int y, 
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
  void write(void) {
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
};

typedef vector<float> TPointList1D;
typedef vector<array<float,2>> TPointList2D;
typedef vector<array<float,3>> TPointList3D;

float CubicHermite (float A, float B, float C, float D, float t)
{
  float a = -A/2.0f + (3.0f*B)/2.0f - (3.0f*C)/2.0f + D/2.0f;
  float b = A - (5.0f*B)/2.0f + 2.0f*C - D / 2.0f;
  float c = -A/2.0f + C/2.0f;
  float d = B;

  return a*t*t*t + b*t*t + c*t + d;
}
 
template <typename T>
inline T GetIndexClamped(const vector<T>& points, int index)
{
  if (index < 0)
      return points[0];
  else if (index >= int(points.size()))
      return points.back();
  else
      return points[index];
}
 
int main (int argc, char **argv)
{
  FHDRaster * raster = new FHDRaster();
  const float Steps = 1000;//13

  const TPointList2D points =
  {
      { 300.0f, 100.0f},
      { 500.0f, 300.0f},
      { 300.0f, 500.0f},
      { 100.0f, 300.0f},
      { 300.0f, 100.0f}
  };

  for (int i = 0; i < Steps; ++i)
  {
    float percent = ((float)i) / (float(Steps - 1));
    float x = 0.0f;
    float y = 0.0f;

    float tx = (points.size() -1) * percent;
    int index = int(tx);
    float t = tx - floor(tx);

    array<float, 2> A = GetIndexClamped(points, index - 1);
    array<float, 2> B = GetIndexClamped(points, index + 0);
    array<float, 2> C = GetIndexClamped(points, index + 1);
    array<float, 2> D = GetIndexClamped(points, index + 2);
    x = CubicHermite(A[0], B[0], C[0], D[0], t);
    y = CubicHermite(A[1], B[1], C[1], D[1], t);

    raster-> setPixel(x,y,235,0,50);
  }
   
  raster->write();
 
  ReleaseDC(myconsole, mydc);

  getchar();
  return 0;
}