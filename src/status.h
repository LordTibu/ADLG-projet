#ifndef STATUS_H
#define STATUS_H
#include<iostream>

struct statusInfo
{
    int statIndex;
    int statStrength;
};


class status
{
private:
    int index;
    std::string name, description;
public:
    status();
    status(std::string Nname, std::string Ndescription);
    ~status();
    int getIndex() const;
    std::string getName() const;
    std::string getDescription() const;
    friend std::ostream& operator<<(std::ostream& os, const status& st);
};
#endif