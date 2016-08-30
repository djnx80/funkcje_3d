#ifndef __FIRE__
#define __FIRE__

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <allegro5/allegro_color.h>
#include <math.h>
#include "fire.h"

using namespace std;

fire::fire(int sW, int sH, int maxXX, int maxYY)    {
    cout <<"zadzialasz?"<<endl;
    float r,g,b;
    float h, s, v;

    maxX = maxXX;
    maxY = maxYY;

   // dynamiczna alokacja
    buf1 = new int*[maxX];
    for(int i = 0; i < maxX; ++i)
    buf1[i] = new int[maxY];

// bufer2
    buf2 = new int*[maxX];
    for(int i = 0; i < maxX; ++i)
    buf2[i] = new int[maxY];


    for(int i = 0; i < maxX-1; ++i)
    for(int j = 0; j < maxY-1; ++j)
         buf1[i][j] = 0;

    // definicja palety
     for (int k=0; k<256; k++)   {
        h = ((float)k / 2);
        s = 1;
        v = ((float)k/255);
        if (k>130) v=1;
        al_color_hsl_to_rgb(h,s,v,&r, &g, &b);
        r=r*255;
        g=g*255;
        b=b*255;
        cout <<k<<" "<<(int)r<<" "<<(int)g<<" "<<(int)b<<"\n";
        rgb[k][0]=(int)r;
        rgb[k][1]=(int)g;
        rgb[k][2]=(int)b;
        if (rgb[k][0]>255) rgb[k][0]=255;
        if (rgb[k][1]>255) rgb[k][1]=255;
        if (rgb[k][2]>255) rgb[k][2]=255;
     }
    for (int x=0; x<maxX-1; x++)    {
        buf1[x][maxY-1]=(rand() % 100)+150;
        buf1[x][maxY-2]=(rand() % 100)+150;
        buf1[x][maxY-3]=(rand() % 100)+150;
    }
    screenW=sW;
    screenH=sH;
    dkol=1;
}

fire::~fire()   {
    for(int i = 0; i < maxX; ++i)
    delete [] buf1[i];
    delete [] buf1;

    for(int i = 0; i < maxX; ++i)
    delete [] buf2[i];
    delete [] buf2;
    cout <<"usuniete";
}


void fire::pobierz_bitmape()
{

}

void fire::dodaj_bitmape(int bitmapX, int bitmapY, unsigned char *pt, ALLEGRO_BITMAP *bitmapa )
{
 ALLEGRO_COLOR tkolor;
    int pixel, kolor, r, g, b;
        unsigned char *ptr;
    ptr=pt;

    unsigned char rr,gg,bb;

cout <<bitmapX<<bitmapY<<"dodaje\n";

 for (int y=1; y<bitmapY; y++)  {
    for (int x=1; x<bitmapX; x++)   {
        tkolor = al_get_pixel (bitmapa , x , y);
        al_unmap_rgb(tkolor, &rr, &gg, &bb);
        r=(int)rr;
        g=(int)gg;
        b=(int)bb;
        kolor=0;
        if (r>0 || g>0 || b>0)  {
        kolor=max(r,g);
        kolor=max(kolor,b);
        for (int i=0; i<255; i++)   {
            if (rgb[i][0]==r && rgb[i][1]==g && rgb[i][2]==b)
            {   kolor=i;
    //            cout <<r<<g<<b<<" "<<kolor<<"\n";
            }
        }
        }

        buf1[x][y]=kolor;

    }
//cout <<bitmapX<<" "<<bitmapY<<" "<<y<<" "<<pixel<<"\n";

 }


}

void fire::rysuj(unsigned char *pt)  {
   int kolor,r,g,b;
   ptr_to_bitmap = pt;

//      dodawanie losowo "oliwy" do ognia
    for(int x = 0; x < maxX; x++)   buf1[x][maxY-2]=(rand()%250)+5;

    //oblicz piksele od gory do dolu
    for(int y = 2; y < maxY-2; y++) {
        for(int x = 2; x < maxX-2; x++) {
            buf1[x][y] = (( buf1[x-1][y+1] + buf1[x][y+1] + buf1[x+1][y+1] + buf1[x][y+2] ) * 32) /128.3;
 //           buf1[x][y] = (buf1[x-1][y+1] + buf1[x+1][y+1] + buf1[x][y+1] + buf1[x][y+2])/4-1;
            //     Buffer2 [x,y-1] = (Buffer1 [x-1,y] + Buffer1 [x+1,y]+ Buffer1 [x,y-1] + Buffer1 [x,y+1]) / 4 - 1
            if (buf1[x][y] < 0) buf1[x][y]=0;
            if (buf1[x][y] >255) buf1[x][y]=255;
        }
    }

    // wyswietlanie bufora
    for (int x=0; x<maxX-1; x++)    {
        for (int y=0; y<maxY-5; y++)    {
            kolor = buf1[x][y];
    //        if (kolor < (int)dkol) kolor=255;
            r=rgb[kolor][0];
            g=rgb[kolor][1];
            b=rgb[kolor][2];
            if (r>0 || g>0 || b>0) point(x,y,r,g,b);
        }
    }

    dkol=dkol-0.05;
}

void fire::point(int xx, int yy,int rr, int gg, int bb)
{
    if (rr<0) rr=0;
    if (rr>255) rr=255;

    if (xx<screenW && yy<screenH && xx>0 && yy>0) {
        int pixel;
        pixel = xx+yy*screenW;
        ptr_to_bitmap[pixel*4] = rr;
        ptr_to_bitmap[pixel*4+1] = gg;
        ptr_to_bitmap[pixel*4+2] = bb;
        ptr_to_bitmap[pixel*4+3] = 250;
    }
}

#endif
