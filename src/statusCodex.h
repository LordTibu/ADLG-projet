#ifndef STATUSCODEX_H
#define STATUSCODEX_H
#include"status.h"
#include<vector>
#include<fstream>
#include<assert.h>
#include<string>

class statusCodex
{
private:
    std::vector<status> codex;
public:
    statusCodex();
    void init(const std::string& filename);
    ~statusCodex();
    void afficher() const;
    status& operator[](int index);
};
#endif