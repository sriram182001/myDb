#include "Pager.h"
#include <iostream>
using namespace std;

Pager::Pager(const string &filename) : filename(filename)
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

    // Find file length
    file.seekg(0, ios::end);
    file_length = file.tellg();
    file.seekg(0, ios::beg);

    // Calculate pages
    num_pages = file_length / PAGE_SIZE;
    if (file_length % PAGE_SIZE != 0)
    {
        throw std::runtime_error("Corrupt database file: not aligned to PAGE_SIZE");
    }
}

Pager::~Pager()
{
    flush();
    file.close();
}

size_t Pager::getNumPages() const
{
    return num_pages;
}

void *Pager::getPage(size_t page_num)
{
    if (page_num >= num_pages)
    {
        throw out_of_range("Requested page is out of range");
    }

    void *buffer = malloc(PAGE_SIZE);
    file.seekg(page_num * PAGE_SIZE, ios::beg);
    file.read(reinterpret_cast<char *>(buffer), PAGE_SIZE);
    return buffer;
}

void Pager::writePage(size_t page_num, const void *data)
{
    file.seekp(page_num * PAGE_SIZE, ios::beg);
    file.write(reinterpret_cast<const char *>(data), PAGE_SIZE);

    if (page_num >= num_pages)
    {
        num_pages = page_num + 1;
    }
}

void Pager::readPage(size_t page_num, void *destination)
{
    if (page_num >= num_pages)
    {
        throw out_of_range("Page not found");
    }

    file.seekg(page_num * PAGE_SIZE, ios::beg);
    file.read(reinterpret_cast<char *>(destination), PAGE_SIZE);
}

void Pager::flush()
{
    file.flush();
}
