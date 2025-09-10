#include <iostream>
#include <sstream>
#include "table/Table.h"
#include "row/Row.h"
using namespace std;

int main()
{
    Table table("data/test.db");

    string input;
    cout << "db > ";
    while (getline(cin, input))
    {
        if (input.empty())
        {
            cout << "db > ";
            continue;
        }

        if (input[0] == '.')
        {
            if (input == ".exit")
            {
                table.close();
                cout << "Bye!\n";
                break;
            }
            else
            {
                cout << "Unrecognized command: " << input << "\n";
            }
        }
        else
        {
            istringstream iss(input);
            string keyword;
            iss >> keyword;

            if (keyword == "insert")
            {
                int id;
                string username, email;
                iss >> id >> username >> email;
                try
                {
                    table.insertRow(Row(id, username, email));
                }
                catch (const exception &e)
                {
                    cout << "Error: " << e.what() << "\n";
                }
            }
            else if (keyword == "select")
            {
                table.selectAll();
            }
            else
            {
                cout << "Unrecognized keyword at start of input: " << keyword << "\n";
            }
        }
        cout << "db > ";
    }

    return 0;
}
