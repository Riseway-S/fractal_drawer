struct point
{
    int x;
    int y;
};

point
make_point(int x, int y);

struct line
{
    point P1;
    point P2;
    int dx() {return P2.x - P1.x;}
    int dy() {return P2.y - P1.y;}
};

line
make_line(int x1, int y1, int x2, int y2);

line
make_line(point P1, point P2);

point
operator +(point A, point B);

point
operator -(point A, point B);

int
operator ==(point A, point B);

int
operator !=(point A, point B);

int
disp(point K);

int
dispe(point K);

int
disp(line L);

int
dispe(line L);
