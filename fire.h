class fire
{

private:
    void point(int , int ,int , int , int );
    int **buf1;
    int **buf2;
    float dkol;
    unsigned char *ptr_to_bitmap;
    int screenW, screenH;
    int maxX, maxY;
    int rgb[257][3];

public:
    fire(int, int, int, int);
    ~fire();
    void rysuj(unsigned char *);
    void pobierz_bitmape();
    void dodaj_bitmape(int, int, unsigned char *, ALLEGRO_BITMAP *);


};
