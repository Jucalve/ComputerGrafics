#include <process.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

string toS(int &i){
    stringstream ss;
    ss<<i;
    return ss.str();
}

int main(){
    string in;
    int i,j=0;
    int grados=5;
    /*in="g++ bresenhamVLF.cpp -o a -lgdi32";
    const char *c=in.c_str();
    system(c);/**/
    in="del lel.avi";
    const char *a=in.c_str();
    system(a);
    for(i=0; i<=360; i+=grados){
        in="a " + toS(i) + " > ob" + toS(j) + ".ppm";
        cout<<in<<" | "<<endl;
        const char *a=in.c_str();
        system(a);
        j++;
    }

    in="ffmpeg -i ob%d.ppm -vcodec ppm lel.avi";
    const char *b=in.c_str();
    system(b);
    cout<<"---------------LIMPIANDO--------------"<<endl;
    
    for(i=0; i<=360; i+=grados){
        in="del  ob" + toS(--j) + ".ppm";
        cout<<in<<" | "<<endl;
        const char *a=in.c_str();
        system(a);
    }/**/

    cout<<"------------ABRIENDO VIDEO-------------"<<endl;
    in="lel.avi";
    const char *d=in.c_str();
    system(d);

}