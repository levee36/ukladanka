#ifndef CGUIMSG_H
#define CGUIMSG_H

#include <string>

class CGUIMsg
{

public:
    CGUIMsg();
    CGUIMsg(std::string opis);
    virtual std::string getOpis();
protected:
    std::string opis;
};

#endif // CGUIMSG_H
