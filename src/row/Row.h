#ifndef ROW_H
#define ROW_H

#include <string>
#include <cstring>

using namespace std;
const int ID_SIZE = sizeof(int);
const int USERNAME_SIZE = 32;
const int EMAIL_SIZE = 255;
const int ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;

class Row
{
public:
    int id;
    char username[USERNAME_SIZE];
    char email[EMAIL_SIZE];

    Row(int i = 0, const string &u = "", const string &e = "")
    {
        id = i;
        strncpy(username, u.c_str(), USERNAME_SIZE);
        username[USERNAME_SIZE - 1] = '\0';
        strncpy(email, e.c_str(), EMAIL_SIZE);
        email[EMAIL_SIZE - 1] = '\0';
    }
};

inline void serializeRow(const Row &src, char *dest)
{
    memcpy(dest, &(src.id), ID_SIZE);
    memcpy(dest + ID_SIZE, src.username, USERNAME_SIZE);
    memcpy(dest + ID_SIZE + USERNAME_SIZE, src.email, EMAIL_SIZE);
}

inline void deserializeRow(const char *src, Row &dest)
{
    memcpy(&(dest.id), src, ID_SIZE);
    memcpy(dest.username, src + ID_SIZE, USERNAME_SIZE);
    memcpy(dest.email, src + ID_SIZE + USERNAME_SIZE, EMAIL_SIZE);
}

#endif
