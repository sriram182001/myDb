#ifndef TABLE_H
#define TABLE_H

#include "pager/Pager.h"
#include "row/Row.h"
#include "pager/Header.h"
#include <iostream>

using namespace std;
class Table
{
public:
    Table(const string &filename);

    void insertRow(const Row &row);
    void selectAll();
    void close();

private:
    Pager pager;
    int numRows;

    int rowsPerPage;
    int tableMaxRows;
};

#endif
