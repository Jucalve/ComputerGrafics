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
#include <map>
#include <queue>

std::string fi="cubo.vlf";
std::string fo="Ocubo.vlf";

using namespace std;

typedef struct coordenadas{
    double x;
    double y;
    double z;
}coaux;

struct p3{
  int x;
  int y;
  int z;
};

struct edg{
  int v;
  bool same;
};

bool operator<(p3 p, p3 q){
  return tie(p.x, p.y, p.z) < tie(q.x, q.y, q.z);
}

int main(){
  const char *cc=fi.c_str();
  FILE *fin;
  fin=fopen(cc,"rb");
  int NNv,NNf,NNe,n;
  coaux coin;
  vector<coaux> vertex;
  vector<int> vaux;
  vector<vector<int>> edges;
  vector<vector<int>> faces;
  fread(&NNv,sizeof(int),1,fin);
  fread(&NNe,sizeof(int),1,fin);
  fread(&NNf,sizeof(int),1,fin);
  for(int i=0;i<NNv;i++){
    fread(&coin,sizeof(coaux),1,fin);
    vertex.push_back(coin);
  }
  for(int i=0; i<NNe; i++){
    for(int j=0; j<2; j++){
      fread(&n,sizeof(int),1,fin);
      vaux.push_back(n);
    }
    edges.push_back(vaux);
    vaux.clear();
  }
  for(int i=0; i<NNf; i++){
    for(int j=0; j<3; j++){
      fread(&n,sizeof(int),1,fin);
      vaux.push_back(n);
    }
    faces.push_back(vaux);
    vaux.clear();
  }
  fclose(fin);

  

  //vamos a trabajar con faces
  //NNf = numero de faces
  //cout<<"xd1 "<<NNv<<" | "<<NNf<<" | "<<NNe<<endl;

  vector<vector<edg>> g(NNf);
  map<pair<p3,p3>,int> es;
  p3 a,b;
  int cambios=0; //numero de posibles cambios
  for(int u=0; u<NNf; u++){
    for(int xd=0; xd<3; xd++){
      //cout<<"xd1_1: "<<u<<", "<<xd<<endl;
      //a=p1 b=p2;
      a.x=vertex[faces[u][xd]].x; a.y=vertex[faces[u][xd]].y; a.z=vertex[faces[u][xd]].z;
      b.x=vertex[faces[u][(xd+1)%3]].x; b.y=vertex[faces[u][(xd+1)%3]].y; b.z=vertex[faces[u][(xd+1)%3]].z;
      //cout<<"a: "<<a.x<<", "<<a.y<<", "<<a.z<<endl;
      //cout<<"b: "<<b.x<<", "<<b.y<<", "<<b.z<<endl;
      
      if(es.count({a,b})){
        int v=es[{a,b}];
        g[u].push_back({v,true});
        g[v].push_back({u,true});
        cambios++;
        //cout<<"extra: "<<u<<" | true |"<<v<<endl; //Debug
      } else if (es.count({b,a})){
        int v=es[{b,a}];
        g[u].push_back({v,false});
        g[v].push_back({u,false});
        //cout<<"extra: "<<u<<" | false |"<<v<<endl; //Debug
      } else{
        es[{a,b}] = u;
        //cout<<"extra "<<u<<"xd"<<endl; //Debug
      }/**/
    }
  }
  //Debug
  /*
  for(int u=0; u<NNf; u++){
    cout<<g[u].size()<<endl;
    for(int otro=0; otro<g[u].size(); otro++){
      cout<<"\t"<<g[u][otro].v<<", "<<g[u][otro].same<<"\t("<<u<<")"<<endl;
    }
  }
/**/  //Debug

/*  //Debug SHOW faces
  for(int u=0; u<NNf; u++){
    for(int otro=0; otro<3; otro++){
      cout<<faces[u][otro]<<" ";
    }
    cout<<"("<<u<<")\n";
  }
/**/
  //cout<<"xd2"<<endl;
  //BFS para encontrar las caras que deben ser cambiadas.

  n=NNf;
  vector<bool> vis(n,false), flip(n);
  flip[0]=false;
  queue<int> q;
  q.push(0);
  while(!q.empty()){
    int u=q.front();
    //cout<<u<<endl;
    q.pop();
    for(edg e : g[u]){
      if(!vis[e.v]){
        vis[e.v] = true;
        flip[e.v]=(flip[u]^e.same);
        
        q.push(e.v);
      }
    }
  }
  
/* //Debug
  for(int u=0; u<n; u++){
    cout<<"vis: "<<vis[u]<<"| flip: "<<flip[u]<<" ("<<u<<")"<<endl;
  }
  cout<<endl;
/**/ //Debug

  //FLIP
  for(int u=0; u<n; u++)
    if(flip[u]){
      int q1, q2, q3;
      q1=faces[u][0];
      q2=faces[u][1];
      q3=faces[u][2];
      faces[u][2]=q1;
      faces[u][1]=q2;
      faces[u][0]=q3;
    }

  //cout<<"xd3"<<endl;
  //Debug SHOW vertex
  /*
  for(int i=0; i<NNv; i++){
    cout<<vertex[i].x<<"|"<<vertex[i].y<<"|"<<vertex[i].z<<endl;
  }

  //Debug SHOW edges
  for(int i=0; i<NNe; i++){
    cout<<edges[i][0]<<" "<<edges[i][1]<<endl;
  }

   //Debug SHOW faces
  for(int u=0; u<NNf; u++){
    for(int otro=0; otro<3; otro++){
      cout<<faces[u][otro]<<" ";
    }
    cout<<"("<<u<<")\n";
  }
/**/

  FILE *fout;
  const char *cco=fo.c_str();
  fout=fopen(cco,"wb");
  if(fout==NULL){
      cout<<"xd"<<endl;
      return -1;
  }

  fwrite(&NNv,sizeof(int),1,fout);
  fwrite(&NNe,sizeof(int),1,fout);
  fwrite(&NNf,sizeof(int),1,fout);
  

  for(int i=0; i<NNv; i++){
    fwrite(&vertex[i],sizeof(coaux),1,fout);
  }

  for(int i=0; i<NNe; i++){
    vaux=edges[i];
    n=vaux.size();
    for(int j=0; j<n; j++){
      fwrite(&vaux[j],sizeof(int),1,fout);
    }
  }

  for(int i=0; i<NNf; i++){
    vaux=faces[i];
    n=vaux.size();
    for(int j=0; j<n; j++){
      fwrite(&vaux[j],sizeof(int),1,fout);
    }
  }

  fclose(fout);
  cout<<cambios<<endl;
  cout<<cco<<endl;
  /******INICIO********PRUEBA*************************/
  /*
  *fin;
  fin=fopen(cco,"rb");
  NNv,NNf,NNe;
  coin;
  vector<coaux> auxco;
  fread(&NNv,sizeof(int),1,fin);
  fread(&NNe,sizeof(int),1,fin);
  fread(&NNf,sizeof(int),1,fin);
  
  cout<<"NNv: "<<NNv<<" | NNe: "<<NNe<<" | NNf: "<<NNf<<endl;
  //double x,y,z;
  int face;
  for(int i=0; i<NNv; i++){
      fread(&coin,sizeof(coaux),1,fin);
      //fread(&x,sizeof(double),1,fin);
      //fread(&y,sizeof(double),1,fin);
      //fread(&z,sizeof(double),1,fin);
      auxco.push_back(coin);
      cout<<""<<coin.x<<"|"<<coin.y<<"|"<<coin.z<<endl;
  }
  //getchar();
  for(int i=0; i<NNe; i++){
      for(int j=0; j<2; j++){
          fread(&face,sizeof(int),1,fin);
          cout<<""<<face<<" ";
      }
      cout<<"  ("<<i<<")"<<endl;
  }
  for(int i=0; i<NNf; i++){
      for(int j=0; j<3; j++){
          fread(&face,sizeof(int),1,fin);
          cout<<""<<face<<" ";
      }
      cout<<endl;
  }
  cout<<fo<<endl;
  fclose(fin);
  /**/
  /*******FIN**********PRUEBA*************************/
  
}
