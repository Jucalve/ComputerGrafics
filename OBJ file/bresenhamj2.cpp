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

int win=0, h=1080, w=1920;
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
int main(void) {
 FHDRaster * raster = new FHDRaster();
 //unsigned int x = 0;
 //unsigned int y = 0;
 int n=11;
 int mitadx=1920/4, mitady=1080/4;
 int unidadx=mitadx/n; //cada unidad de x son n pixeles
 int x1,x2,y1,y2,z1,z2;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;
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
 raster->drawLine(0,th,w,th,255,255,255); //Eje X linea blanca
 raster->drawLine(tw,0,tw,h,255,255,255); //Eje Y linea blanca

    fstream archi;
    string cadvertices="v ", cadcaras="f ";
    string holi, cache;
    coaux aux;
    vector<coaux> co;
    vector<int> vertices;
    vector<vector<int>> carasT;
    vector<vector<int>> carasN;
    float x, y, z;
    int i=1, j, posn, pos, posv, verticeAux,sz,fsz;

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
    while(getline(archi, holi)){ //Leemos linea x linea al archivo
        if(holi.size()>15){ //Ignorar formatos tipo: f 1 2 4 3
            if(holi.compare(0,2,cadcaras) == 0){ //Buscamos las cadenas que empiezen con "f "
                pos=2;
                sz=holi.size();
                while(pos<sz){
                    posn=holi.find(" ",pos);
                    posv=holi.find("/",pos);
                    cache=holi.substr(pos,posv-pos);
                    istringstream isc(cache);
                    //cout << "" << cache << endl;
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
                sz=vertices.size(); //numero de lineas del poligono
              if(sz==3)
                carasT.push_back(vertices);
              else
                carasN.push_back(vertices);

              vertices.clear();
            }
        }
    } //FIN de leer el archivo linea x linea
    
/***************************drawing*******************************/
  fsz=carasN.size();
  for(i=0; i<fsz; i++){
    vertices.push_back(carasN[i][0]); vertices.push_back(carasN[i][1]); vertices.push_back(carasN[i][2]);
    carasT.push_back(vertices);
    vertices.clear();

    vertices.push_back(carasN[i][2]); vertices.push_back(carasN[i][3]); vertices.push_back(carasN[i][0]);
    carasT.push_back(vertices);
    vertices.clear();
  }
  
  fsz=carasT.size();
  for(i=0; i<fsz; i++){
    vertices=carasT[i];
    sz=vertices.size();
    for(j=0; j<sz; j++){
      //480 x
      //270 y
      x1 = (int) ((co[vertices[j]-1].x*unidadx)/1000+mitadx);
      y1 = (int) (mitady-(co[vertices[j]-1].y*unidadx)/1000);
      x2 = (int) ((co[vertices[(j+1)%sz]-1].x*unidadx)/1000+mitadx);
      y2 = (int) (mitady-(co[vertices[(j+1)%sz]-1].y*unidadx/1000));    

      raster->drawLine(x1, y1, x2, y2, 218, 165, 32);  //dorado
    }
    
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
    
    vertices.clear();
  }
/***************************drawing*******************************/

 
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