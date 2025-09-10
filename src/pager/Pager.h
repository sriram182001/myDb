#ifndef PAGER_H
#define PAGER_H

#include <fstream>
#include <vector>
#include <string>

using namespace std;
const int PAGE_SIZE = 4096;
const int MAX_PAGES = 100; // cap for simplicity

class Pager
{
public:
    Pager(const string &filename);
    ~Pager();

    char *getPage(int pageNum);
    void markDirty(int pageNum) { dirty[pageNum] = true; }
    void flush(int pageNum);

    int getNumPages() const { return numPages; }

private:
    fstream dbFile;
    int numPages;

    vector<char *> pages;
    vector<bool> dirty;
};

#endif
