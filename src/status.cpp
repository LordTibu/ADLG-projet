#include"status.h"
using namespace std;

status::status(){}
status::status(std::string Nname, std::string Ndescription){
    name = Nname;
    description = Ndescription;
}
status::~status(){}

std::string status::getName() const{
    return name;
}

std::string status::getDescription() const{
    return description;
}

ostream& operator<<(ostream& os, const status& st)
{
    os << st.name << ": " << endl;
    os << st.description << endl;
    return os;
}