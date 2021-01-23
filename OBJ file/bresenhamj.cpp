#include<cstring>
#include<iostream>
#include<random>
#include<windows.h>
#include<math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

typedef struct coordenadas{
    short x;
    short y;
    short z;
}coaux;

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
   cout<<"P6\n1920 1080 255\n";
   for(y=0;y<1080;y++) {
     for(x=0;x<1920;x++) {
      COLOR = RGB(data[x][y][0],data[x][y][1],data[x][y][2]); 
      SetPixel(mydc,x,y,COLOR);
      //cout<<data[x][y][0];
      //cout<<data[x][y][1];
      //cout<<data[x][y][2];
      
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
 //unsigned int x = 0;
 //unsigned int y = 0;
 int x1,x2,y1,y2,z1,z2;
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

 
 raster->drawLine(0,270,960,270,255,87,51); //vista superior naranja
 raster->drawLine(480,0,480,540,243,20,51); //vista superior rojo

 raster->drawLine(961,270,1920,270,35,20,243); //vista lateral azul
 raster->drawLine(1440,0,1440,540,20,243,241); //vista lateral celeste

 raster->drawLine(0,810,960,810,56,227,17);     //vista frontal verde
 raster->drawLine(480,541,480,1080,20,247,100); //vista frontal verde claro

 raster->drawLine(0,540,1920,540,255,255,255);
 raster->drawLine(960,0,960,1080,255,255,255);
 

    fstream archi;
    string cadvertices="v ", cadcaras="f ";
    string holi, cache;
    coaux aux;
    vector<coaux> co;
    vector<int> vertices;
    float x, y, z;
    int i=1, j, posn, pos, posv, verticeAux;

    archi.open("test1.obj", fstream::in);
    while(getline(archi, holi)){
        if(holi.size()>1){
            if(holi.compare(0,2,cadvertices) == 0){
                //cout << ":v" << endl;
                istringstream isv(holi);
                if(!(isv >> cache >> x >> y >> z)){
                    cout<<"ERROR";
                    break;
                }
                aux.x=(int)(x*1000);
                aux.y=(int)(y*1000);
                aux.z=(int)(z*1000);/**/
                /*aux.x=(int)(x);
                aux.y=(int)(y);
                aux.z=(int)(z);*/
                co.push_back(aux);
                //cout << "(" << i << ") " << x << " " << y << " " << z << endl;
                i++;
            }
            /*else{
                cout << "char: " << holi << endl;
            }/**/
        }
    }
    archi.close();
    archi.open("test1.obj", fstream::in);
    int unidadChida=300;
    while(getline(archi, holi)){
        if(holi.size()>15){
            if(holi.compare(0,2,cadcaras) == 0){
                pos=2;
                int sz=holi.size();
                while(pos<sz){
                    posn=holi.find(" ",pos);
                    posv=holi.find("/",pos);
                    cache=holi.substr(pos,posv-pos);
                    istringstream isc(cache);
                    //cout << "  " << pos << "<" << holi.size() << endl;
                    if(!(isc >> verticeAux)){
                        cout << "  " << pos << "<" << sz;
                        cout << " -> ERROR";
                        break;
                    }
                    //cout<< " " << verticeAux;
                    vertices.push_back(verticeAux);
                    pos=posn+1;
                    if(pos == 0)
                        pos=sz;
                }
                sz=vertices.size();
                for(j=0; j<sz; j++){
                  //480 x

                  //270 y
                  x1 = (int) ((co[vertices[j]-1].x*unidadChida)/1000+480);
                  y1 = (int) (470-(co[vertices[j]-1].y*unidadChida)/1000); //270
                  x2 = (int) ((co[vertices[(j+1)%sz]-1].x*unidadChida)/1000+480);
                  y2 = (int) (470-(co[vertices[(j+1)%sz]-1].y*unidadChida/1000));                 //270
                  raster->drawLine(x1, y1, x2, y2, 218, 165, 32);  //dorado
                    //cout<<""<<vertices[j]<<" ";
                }
                for(j=0; j<sz; j++){
                  z1 = (int) ((co[vertices[j]-1].z*unidadChida)/1000+1440);
                  y1 = (int) (470-(co[vertices[j]-1].y*unidadChida)/1000); //270
                  z2 = (int) ((co[vertices[(j+1)%sz]-1].z*unidadChida)/1000+1440);
                  y2 = (int) (470-(co[vertices[(j+1)%sz]-1].y*unidadChida/1000));                 //270
                  raster->drawLine(z1, y1, z2, y2, 218, 165, 32);  //dorado
                }
                for(j=0; j<sz; j++){
                  x1 = (int) ((co[vertices[j]-1].x*unidadChida)/1000+480);
                  z1 = (int) (810-(co[vertices[j]-1].z*unidadChida)/1000);
                  x2 = (int) ((co[vertices[(j+1)%sz]-1].x*unidadChida)/1000+480);
                  z2 = (int) (810-(co[vertices[(j+1)%sz]-1].z*unidadChida/1000));                
                  raster->drawLine(x1, z1, x2, z2, 218, 165, 32);  //dorado
                }
                //cout << endl;
                vertices.clear();
                //istringstream isc(holi);
                //if(!(isv >> cache >> ))
            }
        }
    }


 
 /*raster->drawLine(0,500,1000,0,218,165,32);//dorado

 raster->drawLine(1500,1000,0,0,64,224,208);//verde
 raster->drawLine(500,100,1000,100,255,105,180);//azul

 raster->drawLine(0,0, 1000,  500, 220, 20, 60);//rojo*/



 raster->write();
 HWND myconsole = GetConsoleWindow();
 HDC mydc = GetDC(myconsole);
 ReleaseDC(myconsole, mydc);
 getchar();
 return 0;
}