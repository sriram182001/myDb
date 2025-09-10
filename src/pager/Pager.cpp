#include "Pager.h"
#include <iostream>
#include <cstring>

using namespace std;
Pager::Pager(const string &filename) : pages(MAX_PAGES, nullptr), dirty(MAX_PAGES, false)
{
    dbFile.open(filename, ios::in | ios::out | ios::binary);

    if (!dbFile.is_open())
    {
        // If file doesn't exist, create it
        dbFile.open(filename, ios::out | ios::binary);
        dbFile.close();
        dbFile.open(filename, ios::in | ios::out | ios::binary);
    }

    // Get file size
    dbFile.seekg(0, ios::end);
    streampos fileSize = dbFile.tellg();
    numPages = fileSize / PAGE_SIZE;
    if (fileSize % PAGE_SIZE != 0)
    {
        cerr << "DB file is not page aligned!\n";
    }
}

Pager::~Pager()
{
    for (int i = 0; i < MAX_PAGES; i++)
    {
        if (pages[i] != nullptr && dirty[i])
        {
            flush(i);
        }
        delete[] pages[i];
    }
    dbFile.close();
}

char *Pager::getPage(int pageNum)
{
    if (pageNum >= MAX_PAGES)
    {
        throw runtime_error("Page number out of bounds");
    }

    if (pages[pageNum] == nullptr)
    {
        // Allocate page
        pages[pageNum] = new char[PAGE_SIZE];
        memset(pages[pageNum], 0, PAGE_SIZE);

        if (pageNum < numPages)
        {
            dbFile.seekg(pageNum * PAGE_SIZE, ios::beg);
            dbFile.read(pages[pageNum], PAGE_SIZE);
        }
        else
        {
            numPages = pageNum + 1;
        }
    }
    return pages[pageNum];
}

void Pager::flush(int pageNum)
{
    if (pages[pageNum] == nullptr)
        return;

    dbFile.seekp(pageNum * PAGE_SIZE, ios::beg);
    dbFile.write(pages[pageNum], PAGE_SIZE);
    dbFile.flush();
    dirty[pageNum] = false;
}
