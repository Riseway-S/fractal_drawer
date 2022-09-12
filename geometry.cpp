point
make_point(int x, int y)
{
    point P;
    P.x = x; P.y = y;
    return P;
}

line
make_line(int x1, int y1, int x2, int y2)
{
    line L;
    L.P1 = make_point(x1, y1);
    L.P2 = make_point(x2, y2);
    return L;
}

line
make_line(point P1, point P2)
{
    line L;
    L.P1 = P1; L.P2 = P2;
    return L;
}

point
operator +(point A, point B)
{
    point AB;
    AB.x = A.x + B.x;
    AB.y = A.y + B.y;
    return AB;
}

point
operator -(point A, point B)
{
    point AB;
    AB.x = A.x - B.x;
    AB.y = A.y - B.y;
    return AB;
}

int
operator ==(point A, point B)
{
    return ((A.x == B.x) & (A.y == B.y));
}

int
operator !=(point A, point B)
{
    return !(A == B);
}

int
disp(point K)
{
    printf("(%d,%d)", K.x, K.y);
    return 0;
}

int
dispe(point K)
{
    int a = disp(K);
    printf("\n");
    return a;
}

int
disp(line L)
{
    printf("(%d,%d)-(%d,%d)", L.P1.x, L.P1.y, L.P2.x, L.P2.y);
    return 0;
}

int
dispe(line L)
{
    int a = disp(L);
    printf("\n");
    return a;
}
