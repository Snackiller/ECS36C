#include"Book.h"
Book::Book()
{
    ISBN=0;
    language="";
    type="";
}
void Book::setISBN(int i)
{
    ISBN=i;
}
void Book::setLanguage(string l)
{
    language=l;
}
void Book::setType(string t)
{
    type=t;
}
int Book::getISBN()
{
    return ISBN;
}
string Book::getLanguage()
{
    return language;
}
string Book::getType()
{
    return type;
}