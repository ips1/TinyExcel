#pragma once

class CellReference
{
private:
    int x, y;
public:
    CellReference(int nx, int ny)
    {
        x = 1;
        y = 1;
        if (nx > 0)
        {
            x = nx;
        }

        if (ny > 0)
        {
            y = ny;
        }
    }
    CellReference(): x(1), y(1) { }
    int get_x() const { return x; }
    int get_y() const { return y; }
    void set_x(int nx)
    {
        if (nx > 0) x = nx;
    }
    void set_y(int ny)
    {
        if (ny > 0) y = ny;
    }
};
