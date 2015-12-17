#ifndef BASECLASS_H_INCLUDED
#define BASECLASS_H_INCLUDED

#include <fstream>

class Base
{
public:
            Base(){};
            ~Base(){};
            virtual void doFilter(std::ifstream &in, std::ofstream &out);
            virtual char transform(char ch) const = 0;
};

/*******************************************************************************************
Copy Class
*******************************************************************************************/

class BaseCopy: public Base
{
 public:

        char transform(char ch) const;
};

/******************************************************************************************
UpperCase Class
******************************************************************************************/

class UpperCase: public virtual BaseCopy
{
public:
        UpperCase(){};
        ~UpperCase(){};

        virtual char transform(char ch) const;
};

/******************************************************************************************
Encryption Class
******************************************************************************************/

class Encrypt: public virtual BaseCopy
{
protected:
    int key;
public:
    Encrypt()
    {
        this -> key = 0;
    }
    Encrypt(int key)
    {
        this -> key = key;
    }
    ~Encrypt(){};
    //virtual void doFilter(std::ifstream &in, std::ofstream &out);
    char transform(char ch) const;
};

/*******************************************************************************************
Ciphertext Class
*******************************************************************************************/

class Ciphertext: public UpperCase
{
public:
    Ciphertext(){};
    ~Ciphertext(){};
    void cipherFile(std::ifstream &in, std::ofstream &out);
};
#endif // BASECLASS_H_INCLUDED
