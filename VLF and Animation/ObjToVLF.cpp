#include<cstring>
#include<iostream>
#include<random>
#include<windows.h>
#include<math.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#define  pi 3.14159

int win=1, h=1080, w=1920; //win 0 == true;
int opMat=2; //0=scale; 1=trans; 2=rot;
int opRot=2; //0=x; 1=y; 2=z;
std::string fl="mono.obj";
std::string fo="mono.vlf";

using namespace std;

typedef struct coordenadas{
    double x;
    double y;
    double z;
}coaux;

int main(int argc, char * argv []) {
 char *p;
 int ang=strtol(argv[1], &p, 10);
 int x1,x2,y1,y2,z1,z2,n;
 fstream archi;
    string cadvertices="v ", cadcaras="f ";
    string holi, cache;
    coaux aux;
    vector<coaux> co;
    vector<int> vertices;
    vector<vector<int>> carasT;
    vector<vector<int>> carasN;
    vector<vector<int>> edges;
    double x, y, z;
    int i=1, j, posn, pos, posv, verticeAux,sz,fsz;

    archi.open(fl, fstream::in);
    while(getline(archi, holi)){
        if(holi.size()>1){
            if(holi.compare(0,2,cadvertices) == 0){
                istringstream isv(holi);
                if(!(isv >> cache >> x >> y >> z)){
                    cout<<"ERROR";
                    break;
                }
                aux.x=x;
                aux.y=y;
                aux.z=z;

                co.push_back(aux);
                i++;
            }
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
                    //cout << "" << cache << endl;            //Debug
                    if(!(isc >> verticeAux)){
                        cout << "  " << pos << "<" << sz;
                        cout << " -> ERROR";
                        break;
                    }
                    //cout<< " " << verticeAux;               //Debug 
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
    archi.close();
    fsz=carasN.size();
    for(i=0; i<fsz; i++){
        vertices.push_back(carasN[i][0]); vertices.push_back(carasN[i][1]); vertices.push_back(carasN[i][2]);
        carasT.push_back(vertices);
        vertices.clear();

        vertices.push_back(carasN[i][2]); vertices.push_back(carasN[i][3]); vertices.push_back(carasN[i][0]);
        carasT.push_back(vertices);
        vertices.clear();
    }

    int Nv, Nf, Ne;
    Nv=co.size();
    Nf=carasT.size();
    Ne=Nf*3;

    //cout<<"|"<<vertices.size()<<endl; //Debug
    for(i=0; i<Nf; i++){
        vertices.push_back(carasT[i][0]-1); vertices.push_back(carasT[i][1]-1);
        edges.push_back(vertices);
        vertices.clear();

        vertices.push_back(carasT[i][1]-1); vertices.push_back(carasT[i][2]-1);
        edges.push_back(vertices);
        vertices.clear();

        vertices.push_back(carasT[i][2]-1); vertices.push_back(carasT[i][0]-1);
        edges.push_back(vertices);
        vertices.clear();
    }

    int k=0;
    for(i=0; i<Nf; i++){
        for(j=0; j<3; j++){
            carasT[i][j]=k++;
        }
    }

  /******INICIO******DYSPLAY*********************/
  FILE *fout;
  const char *a=fo.c_str();
  fout=fopen(a,"wb");
  if(fout==NULL){
      cout<<"xd"<<endl;
      return -1;
  }

  fwrite(&Nv,sizeof(int),1,fout);
  fwrite(&Ne,sizeof(int),1,fout);
  fwrite(&Nf,sizeof(int),1,fout);
  
  for(i=0; i<Nv; i++){
      fwrite(&co[i],sizeof(coaux),1,fout);
  }
  
  for(i=0; i<Ne; i++){
      vertices=edges[i];
      sz=vertices.size();
      for(j=0;j<sz;j++){
          fwrite(&vertices[j],sizeof(int),1,fout);
      }
  }

  for(i=0; i<Nf; i++){
      vertices=carasT[i];
      sz=vertices.size();
      for(j=0;j<sz;j++){
          fwrite(&vertices[j],sizeof(int),1,fout);
      }
  }
  fclose(fout);
  /*******FIN*******DYSPLAY*********************/
  /******INICIO********PRUEBA*************************/
  /*
  FILE *fin;
  fin=fopen(a,"rb");
  int NNv,NNf,NNe;
  coaux coin;
  fread(&NNv,sizeof(int),1,fin);
  fread(&NNe,sizeof(int),1,fin);
  fread(&NNf,sizeof(int),1,fin);
  cout<<"NNv: "<<NNv<<" | NNe: "<<NNe<<" | NNf: "<<NNf<<endl;
  //double x,y,z;
  int face;
  for(i=0; i<NNv; i++){
      fread(&coin,sizeof(coaux),1,fin);
      //fread(&x,sizeof(double),1,fin);
      //fread(&y,sizeof(double),1,fin);
      //fread(&z,sizeof(double),1,fin);
      cout<<""<<coin.x<<"|"<<coin.y<<"|"<<coin.z<<endl;
  }
  for(i=0; i<NNe; i++){
      for(j=0; j<2; j++){
          fread(&face,sizeof(int),1,fin);
          cout<<""<<face<<" ";
      }
      cout<<"  ("<<i<<")"<<endl;
  }
  for(i=0; i<NNf; i++){
      for(j=0; j<3; j++){
          fread(&face,sizeof(int),1,fin);
          cout<<""<<face<<" ";
      }
      cout<<endl;
  }
  fclose(fin);
  */
  /*******FIN**********PRUEBA*************************/
}
