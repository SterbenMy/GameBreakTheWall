class Brick
{
public:

    bool active;
    short row,col; // coordonatele
    float w,h;    // marimea
    short hit;
    Brick(short r_, short c_, float w_, float h_, short hit_):
        row(r_), col(c_), hit(hit_), w(w_), h(h_), active(false) {};
    Brick(): row(),col(), w(20),h(20), hit(1), active(false){}
};
