#include<cstring>
#include<iostream>
#include<random>
#include<windows.h>
#include<math.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <array>

#define  pi 3.14159
#define Inf -9999999999999999999999999999.99

const int win=0, w=1920/2, h=1080/2; //win 0 == true;
int GopMat=2; //0=scale; 1=trans; 2=rot;
int GopRot=1; //0=x; 1=y; 2=z;
std::string fl="Omono.vlf";

using namespace std;
array<array<float, h>, w> MatrixZBuffer = {}; //w,h,double
float OpMatrix[4][4];

typedef struct coordenadas{
    double x;
    double y;
    double z;
}coaux;

typedef struct szbuffer{
    float A;
    float B;
    float C;
    float D;
}zbuffer;

typedef struct norm{
  double x;
  double y;
  double z;
  int   face; //indice de la cara
  double   dotx;
  double   doty;
  double   dotz;
}normal;

typedef struct Dcoordenadas{
    double x;
    double y;
    double z;
}dcoaux;

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

class FHDRaster {
  unsigned char data[w][h][3];
  public:
  FHDRaster(void) {
    memset(data, 0, w*h*3);  
  }
  void
  setPixel(unsigned int x, unsigned int y, 
            unsigned char r, 
            unsigned char g, 
            unsigned char b) {
    if( x >= w || y >= h) {
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
   for(y=0;y<h;y++) {
     for(x=0;x<w;x++) {
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

/*Transf*/
  vector<coaux> Transf(int opMat, int ang, int opRot,vector<coaux> co, int NNv, float ScaleX, float ScaleY, float ScaleZ){
    coaux temp;
    vector<coaux> vcoaux;
    for(int i=0; i<NNv; i++){
      dcoaux coin;
      coin.x=(double)co[i].x;
      coin.y=(double)co[i].y;
      coin.z=(double)co[i].z;

      float Theta= ang*pi/180;

      

      if(opMat==0){
        OpMatrix[0][0]=ScaleX;
        OpMatrix[0][1]=0;
        OpMatrix[0][2]=0;
        OpMatrix[0][3]=0;

        OpMatrix[1][0]=0;
        OpMatrix[1][1]=ScaleY;
        OpMatrix[1][2]=0;
        OpMatrix[1][3]=0;

        OpMatrix[2][0]=0;
        OpMatrix[2][1]=0;
        OpMatrix[2][2]=ScaleZ;
        OpMatrix[2][3]=0;

        OpMatrix[3][0]=0;
        OpMatrix[3][1]=0;
        OpMatrix[3][2]=0;
        OpMatrix[3][3]=1;
      }
      else if(opMat==1){

        OpMatrix[0][0]=1;
        OpMatrix[0][1]=0;
        OpMatrix[0][2]=0;
        OpMatrix[0][3]=ScaleX;

        OpMatrix[1][0]=0;
        OpMatrix[1][1]=1;
        OpMatrix[1][2]=0;
        OpMatrix[1][3]=ScaleY;

        OpMatrix[2][0]=0;
        OpMatrix[2][1]=0;
        OpMatrix[2][2]=1;
        OpMatrix[2][3]=ScaleZ;

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
      temp.x = (Scaled[0][0]/Scaled[3][0]);
      temp.y = (Scaled[1][0]/Scaled[3][0]);
      temp.z = (Scaled[2][0]/Scaled[3][0]);

      vcoaux.push_back(temp);
    }
    return vcoaux;
  }
/*Transf*/

/*ScanLine*/
  auto ScanLine(int x1, int y1, int x2, int y2, int x3, int y3){
            double i,j,k,dy,dx;
            double x,y, temp;
            vector<double> PointsX={0,0};
            vector<double> slope;
            vector<vector<double>> Coord;
            vector<double> Aux;

                Aux.push_back(x1);
                Aux.push_back(y1);
                Coord.push_back(Aux);
                Aux.clear();
                
                Aux.push_back(x2);
                Aux.push_back(y2);
                Coord.push_back(Aux);
                Aux.clear();
                
                Aux.push_back(x3);
                Aux.push_back(y3);
                Coord.push_back(Aux);
                Aux.clear();

                Aux.push_back(x1);
                Aux.push_back(y1);
                Coord.push_back(Aux);
                Aux.clear();

            for(i=0;i<3;i++){ 
                dy=Coord[i+1][1]-Coord[i][1];//distancia x
                dx=Coord[i+1][0]-Coord[i][0];// distancia y
                
                if(dy==0) slope.push_back(1.0);

                if(dx==0) slope.push_back(0.0);
                 /*- calculate inverse slope -*/
                if((dy!=0)&&(dx!=0)) slope.push_back(dx/dy);
            }
            
            for(y=0;y< 1000;y++){
              PointsX.clear();
              //slope.clear();
              k=0;
              for(i=0;i<3;i++){
                
                  if( ((Coord[i][1]<=y)&&(Coord[i+1][1]>y))|| ((Coord[i][1]>y)&&(Coord[i+1][1]<=y))){
                      PointsX.push_back(Coord[i][0]+slope[i]*(y-Coord[i][1]));
                      k++;
                  }   
              }
              
              for(j=0;j<k-1;j++) {/*- Arrange x-intersections in order -*/
                for(i=0;i<k-1;i++){
                  if(PointsX[i] > PointsX[i+1]){
                    temp= PointsX[i];
                    PointsX[i]=PointsX[i+1];
                    PointsX[i+1]=temp;
                  }
                }
              }
                for(i=0;i<k;i+=2){
                drawLine(PointsX[i], y, PointsX[i+1]+1 ,y,0,255,255); 
              }
            }

            for(i=0; i < 3;i++){
              drawLine(Coord[i][0],Coord[i][1],Coord[i+1][0],Coord[i+1][1],255,0,0);    
            }
  }
/*ScanLine*/
/* testing */


/*ZBuffer*/
  zbuffer czbuffer(int x1, int y1, int z1 ,int x2,int y2,  int z2, int x3, int y3, int z3)
  {

      zbuffer coef;
      //Point.A = (pt2.z - pt3.z) * (pt1.y - pt2.y) - (pt1.z - pt2.z) * (pt2.y - pt3.y);
      coef.A = (z2 - z3) * (y1 - y2) - (z1 - z2) * (y2 - y3);
      coef.B = (x2 - x3) * (z1 - z2) - (x1 - x2) * (z2 - z3);
      coef.C = (y2 - y3) * (x1 - x2) - (y1 - y2) * (x2 - x3);
      coef.D = - x1 * (y2 * z3 - z2 * y3) + y1 * (x2 * z3 - z2 * x3) - z1 * (x2 * y3 - y2 * x3);
      return coef;

  }

  auto vzbuffer(zbuffer coef,int x,int y)
  {
      double z = 0;
      if (coef.B != 0)
          z = (-coef.A * x - coef.B * y - coef.D) / coef.C;
      return z;
  }
  auto drawLineZBuffer(zbuffer coef, unsigned int x,unsigned int y,unsigned int x2, unsigned int y2,unsigned int r, unsigned int g, unsigned int b) {
      int DeltaX = x2 - x ;
      int DeltaY = y2 - y ;

      int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
      float z, cosarara;
      bool temp;

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
        temp=0;

    /*ZBuffer*/
        z= vzbuffer(coef, x, y);
      
          //Quien es el mejor :v
          if (MatrixZBuffer[x][y]<z)
          { 

            //cout<<z<<" x "<<x<<" y "<<y<<" "<<MatrixZBuffer[x][y]<<endl;
            //cosarara=MatrixZBuffer[x][y];
            MatrixZBuffer[x][y]=z;
          // cout<<z<<" x "<<x<<" y "<<y<<" "<<MatrixZBuffer[x][y]<<endl;
            //if(cosarara==MatrixZBuffer[x][y])
              //cout<<"cosas raras pasan";
            temp=1;
          }
          else{

            temp = 0;
            // cout<<"sali else"<<endl;
          }
          /* code */
        
    /**/
        if (temp)
        {
          // cout<<"entre temp"<<endl;
          setPixel(x,y,r,g,b) ;
          numerator += shortest ;
        }
        
        
          
          
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
  auto ScanLineZBuffer(zbuffer coef, int x1, int y1, int x2, int y2, int x3, int y3,int r,int g,int b){
    
    double i,j,k,dy,dx;
    double x,y, temp;
    vector<double> PointsX={0,0};
    vector<double> slope;
    vector<vector<double>> Coord;
    vector<double> Aux;

        Aux.push_back(x1);
        Aux.push_back(y1);
        Coord.push_back(Aux);
        Aux.clear();
        
        Aux.push_back(x2);
        Aux.push_back(y2);
        Coord.push_back(Aux);
        Aux.clear();
        
        Aux.push_back(x3);
        Aux.push_back(y3);
        Coord.push_back(Aux);
        Aux.clear();

        Aux.push_back(x1);
        Aux.push_back(y1);
        Coord.push_back(Aux);
        Aux.clear();

    for(i=0;i<3;i++){ 
        dy=Coord[i+1][1]-Coord[i][1];// distancia x
        dx=Coord[i+1][0]-Coord[i][0];// distancia y
        
        if(dy==0) slope.push_back(1.0);

        if(dx==0) slope.push_back(0.0);
        /*- calculate inverse slope -*/
        if((dy!=0)&&(dx!=0)) slope.push_back(dx/dy);
    }
    
    for(y=0;y< 1000;y++){
      PointsX.clear();
      k=0;
      for(i=0;i<3;i++){
        
          if( ((Coord[i][1]<=y)&&(Coord[i+1][1]>y))|| ((Coord[i][1]>y)&&(Coord[i+1][1]<=y))){
              PointsX.push_back(Coord[i][0]+slope[i]*(y-Coord[i][1]));
              k++;
          }   
      }
      
      for(j=0;j<k-1;j++) {/*- Arrange x-intersections in order -*/
        for(i=0;i<k-1;i++){
          if(PointsX[i] > PointsX[i+1]){
            temp= PointsX[i];
            PointsX[i]=PointsX[i+1];
            PointsX[i+1]=temp;
          }
        }
      }
      
        for(i=0;i<k;i+=2){
        drawLineZBuffer(coef ,PointsX[i], y, PointsX[i+1] ,y,r,g,b);
      }
    }
    /*for(i=0; i < 3;i++){
      drawLineZBuffer(coef ,Coord[i][0],Coord[i][1],Coord[i+1][0],Coord[i+1][1],0,0,0); //Dibujo de las lineas
    }/**/
  }


  auto ZBufferFunction(int x1, int y1, int z1 ,int x2,int y2,  int z2, int x3, int y3, int z3,int r, int g, int b){
    //cout<<z1<<" "<<z2<<" "<<z3<<endl;
    zbuffer FaceCoefficents;
    FaceCoefficents= czbuffer(x1,y1,z1,x2,y2,z2,x3,y3,z3);
    //Face XY
    ScanLineZBuffer(FaceCoefficents, x1,y1,x2,y2,x3,y3,r,g,b);
    //cout<<"Te odio ZBufferFunction"<<endl;

  }
/*ZBuffer*/  

  void printCosas(vector<coaux> co){
    for(int i=0; co.size(); i++){
      cout<<co[i].x<<"\t, "<<co[i].y<<"\t, "<<co[i].z<<endl;
    }
  }

  void printCosasV(vector<vector<int>> vv){
    for(int i=0; i<vv.size(); i++){
      for(int j=0; j<vv[i].size(); j++){
        cout<<vv[i][j]<<"\t";
      }
      cout<<endl;
    }
  }
  
};


/*****************MAIN****************/
int main(int argc, char * argv []) {
  for (int i = 0; i < w; i++)
	{
		for(int j=0; j<h; j++){
      MatrixZBuffer[i][j]=Inf;
    }
	}
  char *p;
  int ang=strtol(argv[1], &p, 10);
  FHDRaster * raster = new FHDRaster();
  int x1,x2,y1,y2,z1,z2;
  unsigned char r = 0x00;
  unsigned char g = 0x00;
  unsigned char b = 0x00;
  int n = 0;

/*******************************DIBUJO DE LOS EJES DE APOYO********************************************/
 //raster->drawLine(0,270,960,270,255,87,51); //vista superior naranja
 //raster->drawLine(480,0,480,540,243,20,51); //vista superior rojo

 //raster->drawLine(961,270,1920,270,35,20,243); //vista lateral azul
 //raster->drawLine(1440,0,1440,540,20,243,241); //vista lateral celeste

 //raster->drawLine(0,810,960,810,56,227,17);     //vista frontal verde
 //raster->drawLine(480,541,480,1080,20,247,100); //vista frontal verde claro
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
    vector<vector<int>> carasNv, carasv;
    vector<vector<int>> edges;
    float x, y, z;
    int i, j, posn, pos, posv, verticeAux,sz,esz,fsz;
    int xmin=99999, xmax=-99999, ymin=99999, ymax=-99999, zmin=99999, zmax=-99999;


    vector<int> auxZbuffer;

    const char *a=fl.c_str();
    fin=fopen(a,"rb");
    int Nv,Nf,Ne;
    fread(&Nv,sizeof(int),1,fin);
    fread(&Ne,sizeof(int),1,fin);
    fread(&Nf,sizeof(int),1,fin);

    for(i=0; i<Nv; i++){
        fread(&coin,sizeof(dcoaux),1,fin);

        aux.x=coin.x;
        aux.y=coin.y;
        aux.z=coin.z;

        if(aux.x>xmax)
          xmax=aux.x;
        if(aux.y>ymax)
          ymax=aux.y;
        if(aux.z>zmax)
          zmax=aux.z;

        if(aux.x<xmin)
          xmin=aux.x;
        if(aux.y<ymin)
          ymin=aux.y;
        if(aux.z<zmin)
          zmin=aux.z;

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
    
//****************************Posible normal********************
  fsz=carasT.size();
  vector<normal> normales;
  vector<normal> nnormales, vnormales;
  coaux vecX, vecY, vecZ;
  vecX.x=6; vecX.y=0; vecX.z=0;
  vecY.x=0; vecY.y=6; vecY.z=0;
  vecZ.x=0; vecZ.y=0; vecZ.z=6;

  for(i=0; i<fsz; i++){
    normal auxnormal;
    coaux A,B,C;
    A=co[carasT[i][0]];
    B=co[carasT[i][1]];
    C=co[carasT[i][2]];
    //B-A
    x1=B.x-A.x;
    y1=B.y-A.y;
    z1=B.z-A.z;
    //C-A
    x2=C.x-A.x;
    y2=C.y-A.y;
    z2=C.z-A.z;

    auxnormal.x=y1*z2-z1*y2;
    auxnormal.y=z1*x2-x1*z2;
    auxnormal.z=x1*y2-y1*x2;
    auxnormal.face=i;

    double modn=sqrt( auxnormal.x*auxnormal.x + auxnormal.y*auxnormal.y + auxnormal.z*auxnormal.z );
    auxnormal.dotx=auxnormal.x/modn;
    auxnormal.doty=auxnormal.y/modn;
    auxnormal.dotz=auxnormal.z/modn;

    normales.push_back(auxnormal);
  }
  
//****************************Posible normal********************

/***************************drawing*******************************/
  /********Auxiliares del dibujo********/
  n=8;
  int mitadx=w/4, mitady=h/4;
  int unidadx=mitadx/n; //cada unidad de x son n pixeles
  int ajustey=0;
  /********Auxiliares del dibujo********/
  //GopMat 0=scale; 1=trans; 2=rot;
  //GopRot 0=x; 1=y; 2=z;
  /*Ajustar*/
    int dax, day, daz, d0x, d0y, d0z;
    dax=(int)((xmax-xmin)/2);
    day=(int)((ymax-ymin)/2);
    daz=(int)((zmax-zmin)/2);
    d0x=dax-xmax;
    d0y=day-ymax;
    d0z=daz-zmax;
    
    co=raster->Transf(2, 180, 0, co, Nv, 0, 0, 0);                                  //Rotar 180°
    co=raster->Transf(2, 180, 1, co, Nv, 0, 0, 0);                                  //Rotar 180°
    co=raster->Transf(2, ang, GopRot, co, Nv, 0, 0, 0);                             //Rotar en el angulo solicitado
    co=raster->Transf(1, ang, GopRot, co, Nv, (float)d0x, (float)d0y, (float)d0z);  //Centrar el objeto en el origen
  /*Ajustar*/

  co=raster->Transf(0, ang, GopRot, co, Nv, (float)unidadx, (float)unidadx, (float)unidadx); //Escalar tamaño de pixeles
  co=raster->Transf(1, ang, GopRot, co, Nv, mitadx*2, mitady*2, 0);                          //Mover a mitad de pantalla
  for(i=0;i<fsz; i++){//XY
    auxZbuffer.clear();
      for(j=0; j<3; j++){
        x1 = (int) (co[ carasT[i][   j   ] ].x);
        y1 = (int) (co[ carasT[i][   j   ] ].y); 
        z1 = (int) (co[ carasT[i][   j   ] ].z); 

        auxZbuffer.push_back(x1);
        auxZbuffer.push_back(y1);
        auxZbuffer.push_back(z1);
      }
      raster->ZBufferFunction(auxZbuffer[0],auxZbuffer[1],auxZbuffer[2],auxZbuffer[3],auxZbuffer[4],auxZbuffer[5],auxZbuffer[6],auxZbuffer[7],auxZbuffer[8],(1*rand()*100+10)%255,((1*rand()*100+10)%255),((1*rand()*100+10)%10));
  }  

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