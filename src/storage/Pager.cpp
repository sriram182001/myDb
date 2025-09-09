#include "Pager.h"
#include <iostream>
using namespace std;

Pager::Pager(const string &filename)
{
    file.open(filename, ios::in | ios::out | ios::binary);

    // If file doesn’t exist, create it
    if (!file.is_open())
    {
        file.clear();
        file.open(filename, ios::out | ios::binary);
        file.close();
        file.open(filename, ios::in | ios::out | ios::binary);
    }
}

Pager::~Pager()
{
    for (size_t i = 0; i < pages.size(); i++)
    {
        if (pages[i] != nullptr)
        {
            flush(i);
            delete[] pages[i];
        }
    }
    file.close();
}

char *Pager::getPage(uint32_t pageNum)
{
    if (pageNum >= pages.size())
    {
        pages.resize(pageNum + 1, nullptr);
    }

    if (pages[pageNum] == nullptr)
    {
        pages[pageNum] = new char[PAGE_SIZE]();
        file.seekg(pageNum * PAGE_SIZE);
        file.read(pages[pageNum], PAGE_SIZE);
    }
    return pages[pageNum];
}

void Pager::flush(uint32_t pageNum)
{
    if (pageNum >= pages.size() || pages[pageNum] == nullptr)
        return;

    file.seekp(pageNum * PAGE_SIZE);
    file.write(pages[pageNum], PAGE_SIZE);
    file.flush();
}
