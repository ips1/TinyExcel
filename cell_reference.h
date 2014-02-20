#ifndef CELL_REFERENCE_H
#define CELL_REFERENCE_H

// Class representing a reference to a cell in a table
// - contains valid positive coordinates
class CellReference
{
private:
    unsigned x, y;
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

#endif // CELL_REFERENCE_H
