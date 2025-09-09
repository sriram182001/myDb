#include "Table.h"
#include <iostream>
using namespace std;

const int ROW_SIZE = sizeof(uint32_t) + USERNAME_SIZE + EMAIL_SIZE;
const int ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;

Table::Table(Pager *p) : pager(p), numRows(0) {}

void Table::insertRow(const Row &row)
{
    uint32_t pageNum = numRows / ROWS_PER_PAGE;
    uint32_t rowOffset = numRows % ROWS_PER_PAGE;
    uint32_t byteOffset = rowOffset * ROW_SIZE;

    char *page = pager->getPage(pageNum);
    row.serialize(page + byteOffset);

    numRows++;
    cout << "Inserted row " << row.id
         << " at page " << pageNum
         << ", slot " << rowOffset << endl;
}

void Table::selectAll()
{
    for (uint32_t i = 0; i < numRows; i++)
    {
        uint32_t pageNum = i / ROWS_PER_PAGE;
        uint32_t rowOffset = i % ROWS_PER_PAGE;
        uint32_t byteOffset = rowOffset * ROW_SIZE;

        char *page = pager->getPage(pageNum);
        Row row = Row::deserialize(page + byteOffset);

        cout << "Row " << row.id
             << " | " << row.username
             << " | " << row.email << endl;
    }
}
