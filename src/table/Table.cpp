#include "Table.h"
#include <iostream>
#include <cstring>
using namespace std;

Table::Table(const string &filename) : pager(filename)
{
    rowsPerPage = PAGE_SIZE / ROW_SIZE;
    tableMaxRows = rowsPerPage * MAX_PAGES;

    // ---- Load header (page 0) ----
    char *page0 = pager.getPage(0);
    Header header;
    deserializeHeader(page0, header);

    if (header.numRows < 0 || header.numRows > tableMaxRows)
    {
        numRows = 0;
        header.numRows = 0;
        serializeHeader(header, page0);
        pager.markDirty(0);
    }
    else
    {
        numRows = header.numRows;
    }
}

void Table::insertRow(const Row &row)
{
    if (numRows >= tableMaxRows)
    {
        throw runtime_error("Table full");
    }

    int pageNum = 1 + (numRows / rowsPerPage); // page 0 reserved for header
    char *page = pager.getPage(pageNum);

    int rowOffset = numRows % rowsPerPage;
    char *dest = page + rowOffset * ROW_SIZE;

    serializeRow(row, dest);
    pager.markDirty(pageNum);

    // ---- Update header ----
    numRows++;
    Header header;
    header.numRows = numRows;
    serializeHeader(header, pager.getPage(0));
    pager.markDirty(0);
}

void Table::selectAll()
{
    for (int i = 0; i < numRows; i++)
    {
        int pageNum = 1 + (i / rowsPerPage);
        char *page = pager.getPage(pageNum);

        int rowOffset = i % rowsPerPage;
        const char *src = page + rowOffset * ROW_SIZE;

        Row row;
        deserializeRow(src, row);

        cout << "(" << row.id << ", " << row.username << ", " << row.email << ")\n";
    }
}

void Table::close()
{
    // Pager destructor flushes everything
}
