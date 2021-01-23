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
std::string fl="mono.vlf";

using namespace std;

typedef struct coordenadas{
    short x;
    short y;
    short z;
}coaux;

typedef struct Dcoordenadas{
    double x;
    double y;
    double z;
}dcoaux;

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
 int x1,x2,y1,y2,z1,z2;
 unsigned char r = 0x00;
 unsigned char g = 0x00;
 unsigned char b = 0x00;
 int n = 0;
/*******************************DIBUJO DE LOS EJES DE APOYO********************************************/
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
/*******************************DIBUJO DE LOS EJES DE APOYO********************************************/

    fstream archi;
    FILE *fin;
    string cadvertices="v ", cadcaras="f ";
    string holi, cache;
    coaux aux;
    dcoaux coin;
    vector<coaux> co;
    vector<int> vertices;
    vector<vector<int>> carasT;
    vector<vector<int>> carasN;
    vector<vector<int>> edges;
    float x, y, z;
    int i, j, posn, pos, posv, verticeAux,sz,esz,fsz;


    //archi.open(fl, fstream::in);
    const char *a=fl.c_str();
    fin=fopen(a,"rb");
    int Nv,Nf,Ne;
    fread(&Nv,sizeof(int),1,fin);
    fread(&Ne,sizeof(int),1,fin);
    fread(&Nf,sizeof(int),1,fin);
    //getchar();
    //cout<<""<<Nv<<"|"<<Nf<<endl;
    for(i=0; i<Nv; i++){
        fread(&coin,sizeof(dcoaux),1,fin);

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
                  float Points[4][1] = {{(float)coin.x},{(float)coin.y},{(float)coin.z},{1}};
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
                  coin.x = Scaled[0][0]/Scaled[3][0];
                  coin.y = Scaled[1][0]/Scaled[3][0];
                  coin.z = Scaled[2][0]/Scaled[3][0];
/*transf*/
        aux.x=(int)(coin.x*1000);
        aux.y=(int)(coin.y*1000);
        aux.z=(int)(coin.z*1000);

        co.push_back(aux);
        //cout<<""<<aux.x<<"|"<<aux.y<<"|"<<aux.z<<"+"<<endl;     //Debug
    }   
    //cout<<"---------------------------------"<<endl;            //Debug
    for(i=0;i<Ne;i++){
        for(j=0;j<2;j++){
            fread(&verticeAux,sizeof(int),1,fin);
            vertices.push_back(verticeAux);
            //cout<<""<<verticeAux<<" ";
        }
        edges.push_back(vertices);
        vertices.clear();
        //cout<<endl;
    }
    for(i=0;i<Nf;i++){
        for(j=0;j<3;j++){
            fread(&verticeAux,sizeof(int),1,fin);
            vertices.push_back(verticeAux);
            //cout<<""<<verticeAux<<" ";
        }
        carasT.push_back(vertices);
        vertices.clear();
        //cout<<endl;
    }
    fclose(fin);
    
    
/***************************drawing*******************************/
  /********Auxiliares del dibujo********/
  n=11;
  int mitadx=1920/4, mitady=1080/4;
  int unidadx=mitadx/n; //cada unidad de x son n pixeles
  /********Auxiliares del dibujo********/

  int ajustey=0;
  fsz=carasT.size();
  for(i=0; i<fsz; i++){ //dibujo en plano *************XY**************
    vertices=carasT[i];
    for(j=0; j<3; j++){
      x1 = (int) (co[edges[ vertices[j] ][0]].x*unidadx/1000+mitadx);
      y1 = (int) ((mitady-ajustey)-(co[edges[ vertices[j] ][0]].y*unidadx)/1000);
      x2 = (int) ((co[edges[ vertices[j] ][1]].x*unidadx)/1000+mitadx);
      y2 = (int) ((mitady-ajustey)-(co[edges[ vertices[j] ][1]].y*unidadx/1000)); 
      
      raster->drawLine(x1, y1, x2, y2, 218, 165, 32);  //dorado
    }
  }
  cout<<endl;

  for(i=0; i<fsz; i++){ //dibujo en plano *************ZY**************
    vertices=carasT[i];
    for(j=0; j<3; j++){
      z1 = (int) (co[edges[ vertices[j] ][0]].z*unidadx/1000+(mitadx*3));
      y1 = (int) ((mitady-ajustey)-(co[edges[ vertices[j] ][0]].y*unidadx)/1000);
      z2 = (int) ((co[edges[ vertices[j] ][1]].z*unidadx)/1000+(mitadx*3));
      y2 = (int) ((mitady-ajustey)-(co[edges[ vertices[j] ][1]].y*unidadx/1000)); 

      raster->drawLine(z1, y1, z2, y2, 218, 165, 32);  //dorado
    }
  }

  for(i=0; i<fsz; i++){ //dibujo en plano *************XZ**************
    vertices=carasT[i];
    for(j=0; j<3; j++){
      x1 = (int) (co[edges[ vertices[j] ][0]].x*unidadx/1000+mitadx);
      z1 = (int) ((mitady*3)-(co[edges[ vertices[j] ][0]].z*unidadx)/1000);
      x2 = (int) ((co[edges[ vertices[j] ][1]].x*unidadx)/1000+mitadx);
      z2 = (int) ((mitady*3)-(co[edges[ vertices[j] ][1]].z*unidadx/1000)); 

      raster->drawLine(x1, z1, x2, z2, 218, 165, 32);  //dorado
    }
  }
  

  //****************************Posible normal********************
  /*
  dcoaux va,vb,vc;
  double modulo;
  fsz=carasT.size();
  for(i=0; i<fsz; i++){
    //cout<<"---"<<i+1<<"/"<<fsz<<endl;
    va.x=co[carasT[i][0]-1].x - co[carasT[i][1]-1].x;
    va.y=co[carasT[i][0]-1].y - co[carasT[i][1]-1].y;
    va.z=co[carasT[i][0]-1].z - co[carasT[i][1]-1].z;

    //cout<<"va\t"<<va.x<<", "<<va.y<<endl;

    vb.x=co[carasT[i][1]-1].x - co[carasT[i][2]-1].x;
    vb.y=co[carasT[i][1]-1].y - co[carasT[i][2]-1].y;
    vb.z=co[carasT[i][1]-1].z - co[carasT[i][2]-1].z;
    
    cout<<"vb\t"<<vb.x<<", "<<vb.y<<endl;

    vc.x = (int) ((va.y*vb.z - va.z*vb.y));
    vc.y = (int) ((va.z*vb.x - va.x*vb.z));
    vc.z = (int) ((va.x*vb.y - va.y*vb.x));

    modulo=sqrt(vc.x*vc.x + vc.y*vc.y + vc.z*vc.z);

    vc.x=(int)(vc.x/modulo);
    vc.y=(int)(vc.y/modulo);
    vc.z=(int)(vc.z/modulo);

    cout<<"vc\t"<<vc.x<<", "<<vc.y<<" | "<<modulo<<"\n"<<endl;

    x1 = (int) (vc.x*unidadx/1000+mitadx);
    y1 = (int) ( (mitady-ajustey)-(vc.y*unidadx)/1000 );
    
    //cout<<"xy\t"<<x1<<", "<<y1<<endl;

    raster->drawLine(x1, y1, x1+10, y1+10, 243 ,20 ,51);  //rojo
  }
  */


/***************************drawing*******************************/



 raster->write();
 /*HWND myconsole = GetConsoleWindow();
 HDC mydc = GetDC(myconsole);*/
 if(win==0){
  ReleaseDC(myconsole, mydc);
  getchar();
 }
 return 0;
}