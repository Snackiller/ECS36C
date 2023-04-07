#pragma once
#include<iostream>
#include<string>
using namespace std;
class Book{
    int ISBN;
    string language;
    string type;
    public:
        Book();
        void setISBN(int ISBN);
        void setLanguage(string language);
        void setType(string type);
        int getISBN();
        string getLanguage();
        string getType();
};