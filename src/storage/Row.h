#pragma once

#include <string>
#include <cstdint>
#include <cstring>

using namespace std;

const int USERNAME_SIZE = 32;
const int EMAIL_SIZE = 255;

class Row
{
public:
    uint32_t id;
    string username;
    string email;

    Row(uint32_t id, const string &username, const string &email) : id(id), username(username), email(email) {}

    void serialize(char *destination) const
    {
        memcpy(destination, &id, sizeof(id));
        memcpy(destination + sizeof(id), username.c_str(), USERNAME_SIZE);
        memcpy(destination + sizeof(id) + USERNAME_SIZE, email.c_str(), EMAIL_SIZE);
    }

    static Row deserialize(const char *source)
    {
        uint32_t id;
        char uname[USERNAME_SIZE + 1] = {0};
        char mail[EMAIL_SIZE + 1] = {0};

        memcpy(&id, source, sizeof(id));
        memcpy(uname, source + sizeof(id), USERNAME_SIZE);
        memcpy(mail, source + sizeof(id) + USERNAME_SIZE, EMAIL_SIZE);

        string username(uname);
        string email(mail);

        return Row(id, username, email);
    }
};