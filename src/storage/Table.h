#pragma once
#include "Pager.h"
#include "Row.h"

class Table
{
private:
    Pager *pager;
    uint32_t numRows;

public:
    Table(Pager *p);

    void insertRow(const Row &row);
    void selectAll();
};
