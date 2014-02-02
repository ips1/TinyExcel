#pragma once




class Cell
{
private:
    bool is_dirty;
    bool error;
    double cache;

public:
    bool error()
    {
        return error;
    }
    virtual double evaluate(std::vector<CellReference> &current_stack) = 0;
    virtual std::vector<CellReference> get_dependencies() = 0;
};
