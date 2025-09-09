#include "storage/Pager.h"
#include "storage/Table.h"
#include <iostream>
using namespace std;

int main()
{
    Pager pager("mydb.db");
    Table table(&pager);

    table.insertRow(Row(1, "alice", "alice@example.com"));
    table.insertRow(Row(2, "bob", "bob@example.com"));

    pager.flush(0);

    cout << "\nAll rows in DB:\n";
    table.selectAll();

    return 0;
}
