#include<cstring>
#include<iostream>
#include<random>
#include<windows.h>
#include<math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define  pi 3.14159

int win=0, h=1080, w=1920; //win 0 == true;
int opMat=2; //0=scale; 1=trans; 2=rot;
int opRot=1; //0=x; 1=y; 2=z;
std::string fl="mono.obj";

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
      if(win==0){
        COLOR = RGB(data[x][y][0],data[x][y][1],data[x][y][2]); 
        SetPixel(mydc,x,y,COLOR);
      }
      else{
        cout<<data[x][y][0];
        cout<<data[x][y][1];
        cout<<data[x][y][2];
      }
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

/* testing */
};
int main(int argc, char * argv []) {
  char *p;
  int ang=strtol(argv[1], &p, 10);
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

 /*raster->drawLine(0,270,960,270,255,87,51); //vista superior naranja
 raster->drawLine(480,0,480,540,243,20,51); //vista superior rojo

 raster->drawLine(961,270,1920,270,35,20,243); //vista lateral azul
 raster->drawLine(1440,0,1440,540,20,243,241); //vista lateral celeste

 raster->drawLine(0,810,960,810,56,227,17);     //vista frontal verde
 raster->drawLine(480,541,480,1080,20,247,100); //vista frontal verde claro
/**/
 int th=h/2, tw=w/2;
 raster->drawLine(0,th,w,th,255,255,255);
 raster->drawLine(tw,0,tw,h,255,255,255);

    fstream archi;
    string cadvertices="v ", cadcaras="f ";
    string holi, cache;
    coaux aux;
    vector<coaux> co;
    vector<int> vertices;
    float x, y, z;
    int i=1, j, posn, pos, posv, verticeAux;

    archi.open(fl, fstream::in);
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

                /*transf*/
                  float ScaleRateX=0.5;
                  float ScaleRateY=0.5;
                  float ScaleRateZ=0.5;

                  float TranslationX=2;
                  float TranslationY=2;
                  float TranslationZ=2;

                  float Theta= ang*pi/180;

                  float OpMatrix[4][4];

                  if(opMat==0){
                    OpMatrix[0][0]=ScaleRateX;
                    OpMatrix[0][1]=0;
                    OpMatrix[0][2]=0;
                    OpMatrix[0][3]=0;

                    OpMatrix[1][0]=0;
                    OpMatrix[1][1]=ScaleRateY;
                    OpMatrix[1][2]=0;
                    OpMatrix[1][3]=0;

                    OpMatrix[2][0]=0;
                    OpMatrix[2][1]=0;
                    OpMatrix[2][2]=ScaleRateZ;
                    OpMatrix[2][3]=0;

                    OpMatrix[3][0]=0;
                    OpMatrix[3][1]=0;
                    OpMatrix[3][2]=0;
                    OpMatrix[3][3]=1;
                  }
                  else if(opMat==1){
                    OpMatrix[0][0]=TranslationX;
                    OpMatrix[0][1]=0;
                    OpMatrix[0][2]=0;
                    OpMatrix[0][3]=0;

                    OpMatrix[1][0]=0;
                    OpMatrix[1][1]=TranslationY;
                    OpMatrix[1][2]=0;
                    OpMatrix[1][3]=0;

                    OpMatrix[2][0]=0;
                    OpMatrix[2][1]=0;
                    OpMatrix[2][2]=TranslationZ;
                    OpMatrix[2][3]=0;

                    OpMatrix[3][0]=0;
                    OpMatrix[3][1]=0;
                    OpMatrix[3][2]=0;
                    OpMatrix[3][3]=1;
                  }
                  else{
                    if(opRot==0){
                      OpMatrix[0][0]=1;
                      OpMatrix[0][1]=0;
                      OpMatrix[0][2]=0;
                      OpMatrix[0][3]=0;

                      OpMatrix[1][0]=0;
                      OpMatrix[1][1]=cos(Theta);
                      OpMatrix[1][2]=sin(Theta)*-1;
                      OpMatrix[1][3]=0;

                      OpMatrix[2][0]=0;
                      OpMatrix[2][1]=sin(Theta);
                      OpMatrix[2][2]=cos(Theta);
                      OpMatrix[2][3]=0;

                      OpMatrix[3][0]=0;
                      OpMatrix[3][1]=0;
                      OpMatrix[3][2]=0;
                      OpMatrix[3][3]=1;
                    }
                    else if(opRot==1){
                      OpMatrix[0][0]=cos(Theta);
                      OpMatrix[0][1]=0;
                      OpMatrix[0][2]=-sin(Theta);
                      OpMatrix[0][3]=0;

                      OpMatrix[1][0]=0;
                      OpMatrix[1][1]=1;
                      OpMatrix[1][2]=0;
                      OpMatrix[1][3]=0;

                      OpMatrix[2][0]=sin(Theta);
                      OpMatrix[2][1]=0;
                      OpMatrix[2][2]=cos(Theta);
                      OpMatrix[2][3]=0;

                      OpMatrix[3][0]=0;
                      OpMatrix[3][1]=0;
                      OpMatrix[3][2]=0;
                      OpMatrix[3][3]=1;
                    }
                    else{
                      OpMatrix[0][0]=cos(Theta);
                      OpMatrix[0][1]=-sin(Theta);
                      OpMatrix[0][2]=0;
                      OpMatrix[0][3]=0;

                      OpMatrix[1][0]=sin(Theta);
                      OpMatrix[1][1]=cos(Theta);
                      OpMatrix[1][2]=0;
                      OpMatrix[1][3]=0;

                      OpMatrix[2][0]=0;
                      OpMatrix[2][1]=0;
                      OpMatrix[2][2]=1;
                      OpMatrix[2][3]=0;

                      OpMatrix[3][0]=0;
                      OpMatrix[3][1]=0;
                      OpMatrix[3][2]=0;
                      OpMatrix[3][3]=1;
                    }
                  }
                  float Points[4][1] = {{(float)aux.x},{(float)aux.y},{(float)aux.z},{1}};
                  float Scaled[4][1] = {{0},{0},{0},{0}};

                  for (int row = 0; row < 4; row++) {
                    for (int col = 0; col < 1; col++) {
                        // Multiply the row of A by the column of B to get the row, column of product.
                        for (int inner = 0; inner < 4; inner++) {
                            //std::cout<< "Scaled en  Es= "<< OpMatrix[row][inner]<<" * "<<Points[0][col]<<" Posicion ";
                            Scaled[row][col] += OpMatrix[row][inner] * Points[inner][col];
                        }
                        //std::cout << Scaled[row][col] << " ";
                    }
                    //std::cout << "\n";
                  }
                  aux.x = (int) Scaled[0][0]/Scaled[3][0];
                  aux.y = (int) Scaled[1][0]/Scaled[3][0];
                  aux.z = (int) Scaled[2][0]/Scaled[3][0];
                  /*transf*/

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
    archi.open(fl, fstream::in);
    while(getline(archi, holi)){
        if(holi.size()>15){
            if(holi.compare(0,2,cadcaras) == 0){
                pos=2;
                int sz=holi.size();
                int n=10;
                int mitadx=1920/2, mitady=1080/2;
                int unidadx=mitadx/n; //cada unidad de x son n pixeles

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

                  x1 = (int) ((co[vertices[j]-1].x*unidadx)/1000+mitadx);
                  y1 = (int) (mitady-(co[vertices[j]-1].y*unidadx)/1000);
                  x2 = (int) ((co[vertices[(j+1)%sz]-1].x*unidadx)/1000+mitadx);
                  y2 = (int) (mitady-(co[vertices[(j+1)%sz]-1].y*unidadx/1000));    

                  raster->drawLine(x1, y1, x2, y2, 218, 165, 32);  //dorado
                    //cout<<""<<vertices[j]<<" ";
                }
                /*
                for(j=0; j<sz; j++){
                  z1 = (int) ((co[vertices[j]-1].z*48)/1000+1440);
                  y1 = (int) (270-(co[vertices[j]-1].y*48)/1000);
                  z2 = (int) ((co[vertices[(j+1)%sz]-1].z*48)/1000+1440);
                  y2 = (int) (270-(co[vertices[(j+1)%sz]-1].y*48/1000));                
                  raster->drawLine(z1, y1, z2, y2, 218, 165, 32);  //dorado
                }
                for(j=0; j<sz; j++){
                  x1 = (int) ((co[vertices[j]-1].x*48)/1000+480);
                  z1 = (int) (810-(co[vertices[j]-1].z*48)/1000);
                  x2 = (int) ((co[vertices[(j+1)%sz]-1].x*48)/1000+480);
                  z2 = (int) (810-(co[vertices[(j+1)%sz]-1].z*48/1000));                
                  raster->drawLine(x1, z1, x2, z2, 218, 165, 32);  //dorado
                }
                
                */
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
 /*HWND myconsole = GetConsoleWindow();
 HDC mydc = GetDC(myconsole);*/
 if(win==0){
  ReleaseDC(myconsole, mydc);
  getchar();
 }
 return 0;
}