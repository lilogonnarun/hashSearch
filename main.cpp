#include <iostream>
using namespace std;
#define SUCCESS 1
#define FAIL 0
#define NULLKEY -32768
#define HASHSIZE 11
typedef struct
{
    int *elem;
    int count;
}HashTable;
bool initHashTable(int len,HashTable *hashTable)
{
    hashTable->count=len;
    hashTable->elem=new int[len];
    for (int i = 0; i < len; ++i) {
        hashTable->elem[i]=NULLKEY;
    }
    return true;
}
int hashCal(int key)
{
    return key%HASHSIZE;
}
void insertHash(HashTable *hashTable,int key)
{
    int addr=hashCal(key);
    while(hashTable->elem[addr]!=NULLKEY)
    {
        addr=(addr+1)%hashTable->count;
    }
    hashTable->elem[addr]=key;
}
bool hashShow(HashTable *hashTable)
{
    for (int i = 0; i <hashTable->count; ++i) {
        if(hashTable->elem[i]!=NULLKEY)
        {
            cout<<hashTable->elem[i]<<' ';
        }
        else cout<<"NULL ";
    }
    cout<<endl;
}
bool hashSearch(HashTable *hashTable,int key,int *addr,int &time)
{
    *addr=hashCal(key);
    time++;
    if(hashTable->elem[*addr]==NULLKEY)
    {
        return FAIL;
    }
    while (hashTable->elem[*addr]!=key)
    {
        *addr=(*addr+1)%hashTable->count;
        time++;
        if(hashTable->elem[*addr]==NULLKEY||*addr==hashCal(key))
        {
            return FAIL;
        }
    }
    return SUCCESS;
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int len,hashNum;
        cin>>len>>hashNum;
        HashTable *hashTable=new HashTable;
        int key;
        initHashTable(len,hashTable);
        for (int i = 0; i < hashNum; ++i) {
            cin>>key;
            insertHash(hashTable,key);
        }
        hashShow(hashTable);
        int n;
        cin>>n;
        while(n--)
        {
            cin>>key;
            int *addr=new int;
            *addr=0;
            int time=0;
            if(hashSearch(hashTable,key,addr,time)==SUCCESS)
            {
                cout<<SUCCESS<<' '<<time<<' '<<*addr+1<<endl;
            }
            else
            {
                cout<<FAIL<<' '<<time<<endl;
            }
        }
    }
}