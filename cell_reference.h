#pragma once

struct CellReference
{
    int x, y;
    CellReference(int nx, int ny): x(nx), y(ny) { }
    CellReference(): x(0), y(0) { }
};
