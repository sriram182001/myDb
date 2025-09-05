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
    string filename;
    size_t file_length;
    size_t num_pages;

public:
    Pager(const string &filename);
    ~Pager();

    size_t getNumPages() const;
    void *getPage(size_t page_num);

    void writePage(size_t page_num, const void *data);
    void readPage(size_t page_num, void *destination);

    void flush();
};

#endif
