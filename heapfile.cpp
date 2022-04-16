#include<bits/stdc++.h>
using namespace std;

#define ll long long int

ll intsize = 4;

class Page
{
private:
    ll spaceleft;
    ll prevpage;
    ll nextpage;
    ll count;
    ll freeptr;
    vector<ll> Data;
    vector<ll> Book_keeping;

public:
    Page(ll x);
    int Insert(ll datasize, ll key);
    int Search(ll key);
    int Displaycount();
    ~Page();
};



class File
{
private:
    ll sizeofpage;
    vector<Page*> Pages;
public:
    File(ll x);
    void AddPage();
    void InsertData(ll datasize, ll key);
    void Search(ll key);
    void Status();
    ~File();
};

// File functions:

File::File(ll x)
{
    sizeofpage = x;
}

void File::AddPage(){

    Page * temp = new Page(sizeofpage);
    Pages.push_back(temp);
}
void File::InsertData(ll datasize, ll key){
    
    ll chk=0;
    for (ll i = 0; i < Pages.size(); i++)
    {
        chk = Pages[i]->Insert(datasize, key);
        if(chk==1){
            break;
        }
    }

    if(chk==0){
        AddPage();
        Pages[Pages.size()-1]->Insert(datasize, key);
    }
    

}
void File::Search(ll key){

    ll chk = -1;
    for (ll i = 0; i < Pages.size(); i++)
    {
        chk = Pages[i]->Search(key);
        if(chk!=-1){
            cout<< i << ' ' << chk <<endl;
            break;
        }
    }
    if(chk==-1){
        cout<<-1<<' '<<-1<<endl;
    }    
}
void File::Status(){

    cout<<Pages.size()<<' ';
    for(ll i=0; i<Pages.size();i++){
        cout<<Pages[i]->Displaycount()<<' ';
    }
    cout<<endl;

}
File::~File()
{
}

// Page functions:

Page::Page(ll x)
{   
    spaceleft = x - 4*intsize;
    count = 0;
    freeptr = 0;

}

int Page::Insert(ll datasize, ll key){

    if(datasize+intsize <= spaceleft){
        Data.push_back(key);
        Book_keeping.push_back(freeptr);
        freeptr+= datasize;
        spaceleft -= (datasize + intsize);
        count++;
        return 1;
    }else{
        return 0;
    }
}
 
int Page::Search(ll key){

    for (ll i = 0; i < Data.size(); i++)
    {
        if(Data[i]==key){
            return i;
        }
    }

    return -1;
    
}
int Page::Displaycount(){
    return count;
}

Page::~Page()
{
}



int main()
{
    ll temp;
    cin>>temp;

    File f(temp);

    while(cin>>temp){
        switch (temp)
        {
        case 1:
            ll datasize, key;
            cin>>datasize>>key;
            f.InsertData(datasize, key);
            break;
        case 2:
            f.Status();
            break;
        case 3:
            cin>>key;
            f.Search(key);
            break;
        case 4:
            return 0;
            break;
        }
    }

    return 0;
}
