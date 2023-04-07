#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<chrono>
#include"Book.h"
using namespace std;
bool readFile(string filename,vector<Book> &nBook);//to get the information from file to the vector, so we can compare those information in files
bool binarySearch(vector<Book> nBook,int ISBN,string language,string type);//a way to search the book
bool compareBook(Book x, Book y);//compare the ISBN, language and type
int main(int argc, char **argv){
    vector<Book> newbooks;
    vector<Book> request;
    if(argc<3)//determine whether the number of file is satisfied 3
    {
        cerr<<"Usage: .SearchNewBooks <newBooks.dat> <request.dat> <result_file.dat>"<<endl;//exit the program
        return -1;
    }
    string file1=argv[1];
    string file2=argv[2];
    if(argc>3)////determine whether the number of file is more than 3
    {
        cerr<<"Error: cannot open file "<<argv[1]<<endl;//exit the program
        return -1;
    }
    if(readFile(file1,newbooks)==false)//determine whether the openfile is what we need to search
    {
        cerr<<"Error: cannot open file "<<file1<< endl;//exit the program
        return -1;
    }
    if (readFile(file2,request)==false)//determine whether the openfile is the file we need to get request books
    {
        cerr<<"Error: cannot open file "<<file2<<endl;//exit the program
        return -1;
    }
    cout<<"Choice of search method ([l]inear, [b]inary)?"<<endl;
    char method;//'l', 'b' or other
    cin>>method;//get your choice
    ofstream out;
    out.open("found.dat");// opens the file
    if(!out){// file couldn't be opened
        cerr<<"Error: cannot open file toto"<< endl;//exit the program
        exit(1);
    }
    int count=0;//how many books we find
    while(true)
    {
        if(method=='l')//linear search
        {
            chrono::high_resolution_clock::time_point start;//counting the number of elapsed microseconds
            start=chrono::high_resolution_clock::now();
            for(uint64_t i=0;i<request.size();i++)//to find the book O(n^2)
            {
                for (uint64_t j=0;j<newbooks.size();j++)
                {
                    if(request[i].getISBN()==newbooks[j].getISBN()&&request[i].getLanguage()==newbooks[j].getLanguage()&&request[i].getType()==newbooks[j].getType())//search the item one by one
                    {
                        count++;
                    }
                }
            }
            auto end=chrono::high_resolution_clock::now();//finish counting
            double elapsed_us=chrono::duration<double, micro>(end-start).count();
            cout<<count<<endl;//the number of book we find
            cout<<"CPU time: "<<elapsed_us<<" microseconds"<<endl;//the time we use
            break;
        }
        else if(method=='b')//binary search
        {
            chrono::high_resolution_clock::time_point start;//counting the number of elapsed microseconds
            start=chrono::high_resolution_clock::now();
            sort(newbooks.begin(), newbooks.end(), compareBook);//sort the list
            for(uint64_t i=0;i<request.size();i++)//to find the book O(nlogn)
            {
                if(binarySearch(newbooks,request[i].getISBN(),request[i].getLanguage(),request[i].getType())==true)////search the item by binary
                {
                    count++;
                }
            }
            auto end=chrono::high_resolution_clock::now();//finish counting
            double elapsed_us=chrono::duration<double, micro>(end-start).count();
            cout<<count<<endl;//the number of book we find
            cout<<"CPU time: "<<elapsed_us<<" microseconds"<<endl;//the time we use
            break;
        }
        else
        {
            cout<<"Incorrect choice"<<endl;//not linear search or binary search
            cin>>method;//get the choice
        }
    }
    out<<count<<endl;//get the number of book we found
    out.close();//close the file
}
bool readFile(string file,vector<Book> &nBook)
{
    ifstream in;
    in.open(file);//open the file
    if(!in)
    {
        return false;
    }
    string str;
    while(!in.eof())//determine whether the file is empty
    {
        Book *o;
        o=new Book;
        if(!getline(in,str,','))//if it is empty line
        {
            break;
        }
        o->setISBN(stoi(str));//get ISBN
        getline(in,str,',');
        o->setLanguage(str);//get language
        getline(in, str);
        o->setType(str);//get type
        nBook.push_back(*o);//push elements into a vector from the back
    }
    in.close();//close the file
    return true;
}
bool compareBook(Book x,Book y){
    if(x.getISBN()>y.getISBN())//compare ISBN
    {
        return true;
    }
    else if(x.getISBN()==y.getISBN())
    {
        if(x.getType()==y.getType())//compare type
        {
            if(x.getLanguage()[0]>=y.getLanguage()[0])//compare language
            {
                return true;
            }
        }
        else if(x.getType()=="new")//compare type
        {
            return true;
        }
        else if(x.getType()=="used"&&y.getType()!="new")//compare type
        {
            return true;
        }
    }
    return false;
}
bool binarySearch(vector<Book> nBook,int ISBN,string language,string type){
    int i=0;//start
    int j=nBook.size()-1;//final
    int m;//middle
    while(i<=j)//determine whether the first one is the last one
    {
        m=(i+j)/2;
        if(ISBN==nBook[m].getISBN())//compare ISBN
        {
            if(language>nBook[m].getLanguage())//compare language
            {
                j=m-1;
            }
            else if(language<nBook[m].getLanguage())
            {
                i=m+1;
            }
            else if(language==nBook[m].getLanguage())
            {
                if(type==nBook[m].getType())//compare type
                {
                    return true;

                }        
                else if(type=="new")
                {
                    j=m-1;
                }
                else if(type=="used"&&nBook[m].getType()!="new")
                {
                    j=m-1;
                }
                else
                {
                    i=m+1;
                }
            }
        }
        else if(ISBN>nBook[m].getISBN())//compare ISBN
        {
            j=m-1;
        }
        else if(ISBN<nBook[m].getISBN())//compare ISBN
        {
            i=m+1;
        }
    }
    return false;
}