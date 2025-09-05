#include "storage/Pager.h"
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    Pager pager("test.db");

    cout << "Initially, file has " << pager.getNumPages() << " pages\n";

    // Write page 0
    char pageData[PAGE_SIZE];
    strcpy(pageData, "Hello, this is page 0!");
    pager.writePage(0, pageData);

    // Write page 1
    char pageData2[PAGE_SIZE];
    strcpy(pageData2, "This is page 1.");
    pager.writePage(1, pageData2);

    pager.flush();

    cout << "After writing, file has " << pager.getNumPages() << " pages\n";

    // Read back page 0
    char buffer[PAGE_SIZE];
    pager.readPage(0, buffer);
    cout << "Page 0 content: " << buffer << "\n";

    // Read back page 1
    char buffer2[PAGE_SIZE];
    pager.readPage(1, buffer2);
    cout << "Page 1 content: " << buffer2 << "\n";

    return 0;
}
