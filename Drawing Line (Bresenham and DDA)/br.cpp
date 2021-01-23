/*BRESENHAAM ALGORITHM FOR LINE DRAWING*/
#include<iostream>
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<dos.h>
void bhm_line(int,int,int,int,int);
void main()
{
    int ghdriver=DETECT,ghmode,errorcode,x1,x2,y1,y2;
    initgraph(&ghdriver,&ghmode,"..\\bgi");
    errorcode = graphresult();
    if(errorcode !=grOk)
    {
     cout<<"Graphics error:%s\n"<<grapherrormsg(errorcode);
     cout<<"Press any key to halt:";
     getch();
     exit(1);
    }
    clrscr();
    cout<<"Enter the coordinates (x1,y1): ";
    cin>>x1>>y1;
    cout<<"Enter the coordinates (x2,y2): ";
    cin>>x2>>y2;
    bhm_line(x1,y1,x2,y2,1);
    getch();
}
void bhm_line(int x1,int y1,int x2,int y2,int c)
{
    int x,y,dx,dy,dx1,dy1,px,py,xe,ye,i;
    dx=x2-x1;
    dy=y2-y1;
    dx1=fabs(dx);
    dy1=fabs(dy);
    px=2*dy1-dx1;
    py=2*dx1-dy1;
    if(dy1<=dx1)
    {
     if(dx>=0)
     {
      x=x1;
      y=y1;
      xe=x2;
     }
     else
     {
      x=x2;
      y=y2;
      xe=x1;
     }
     putpixel(x,y,c);
     for(i=0;x<xe;i++)
     {
      x=x+1;
      if(px<0)
      {
       px=px+2*dy1;
      }
      else
      {
       if((dx<0 && dy<0) || (dx>0 && dy>0))
       {
        y=y+1;
       }
       else
       {
        y=y-1;
       }
       px=px+2*(dy1-dx1);
      }
      delay(0);
      putpixel(x,y,c);
     }
    }
    else
    {
     if(dy>=0)
     {
      x=x1;
      y=y1;
      ye=y2;
     }
     else
     {
      x=x2;
      y=y2;
      ye=y1;
     }
     putpixel(x,y,c);
     for(i=0;y<ye;i++)
     {
      y=y+1;
      if(py<=0)
      {
       py=py+2*dx1;
      }
      else
      {
       if((dx<0 && dy<0) || (dx>0 && dy>0))
       {
        x=x+1;
       }
       else
       {
        x=x-1;
       }
       py=py+2*(dx1-dy1);
      }
      delay(0);
      putpixel(x,y,c);
     }
    }
}