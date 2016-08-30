//#ifndef __ALEGROSTART__
//#define __ALEGROSTART__
class allegroStart
{
    private:
        ALLEGRO_DISPLAY *al_okno;
        ALLEGRO_BITMAP  *al_bitmapa;

    public:
        int screenW;
        int screenH;

        allegroStart(int, int);
        ~allegroStart();
        ALLEGRO_DISPLAY *openWindow();
        ALLEGRO_BITMAP  *openBitmap(int, int);

};

//#endif
