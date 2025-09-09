#ifndef PAGER_H
#define PAGER_H

#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

const size_t PAGE_SIZE = 4096; // 4 KB per page

class Pager
{
private:
    fstream file;
    vector<char *> pages;

public:
    Pager(const string &filename);
    ~Pager();

    char *getPage(uint32_t pageNum);
    void flush(uint32_t pageNum);
};

#endif
