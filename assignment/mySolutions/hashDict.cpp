#include <iostream>
#include <cmath>
#include <cstddef>

using namespace std;

typedef long long ll;

struct Entry{
    ll hashCode;
    ll key;
    string val;
    Entry* next;
};

Entry* hashTable;
size_t length;
size_t sz;

ll hashf(ll);
size_t calpos(ll, size_t);
Entry* add(Entry*, ll, string);
Entry* rehash(Entry*);
void del(Entry*, ll);
void search(Entry*, size_t);
void print(Entry*);
void release(Entry*);

int main(){
    int n;
    cin >> length >> n;
    sz = 0;
    string op;
    ll key;
    string val;
    hashTable = new Entry[length];
    
    for(size_t i = 0; i < length; i ++){
        (hashTable+i)->next = nullptr;
    }
    
    while(n--){
        cin >> op;
        if(op == "add"){
            cin >> key >> val;
            hashTable = add(hashTable, key, val);
        }else if(op == "search"){
            size_t pos;
            cin >> pos;
            search(hashTable, pos);
        }else if(op == "delete"){
            cin >> key;
            del(hashTable, key);
        }
    }
    
    return 0;
}

ll hashf(ll key){
    return abs(3*key*key*key + 5*key*key + 7*key + 11);
}

size_t calpos(ll hashCode, size_t len){
    return hashCode % len;
}

Entry* add(Entry* ht,ll key, string val){
    ll hashCode = hashf(key);
    size_t pos = calpos(hashCode, length);
    Entry* prev = ht+pos;
    Entry* curr = prev->next;
    while(curr != nullptr && curr->key <= key){
        prev = curr;
        curr = curr->next;
    }
    Entry* p = new Entry;
    p->hashCode = hashCode;
    p->key = key;
    p->val = val;
    p->next = prev->next;
    prev->next = p;
    sz++;
    p = (ht+pos)->next;
    size_t cnt = 0;
    while(p != nullptr){
        cnt ++;
        p = p->next;
    }
    if(sz > length || cnt > 4){
        return rehash(ht);
    }
    return ht;
}

Entry* rehash(Entry* old){
    size_t oldLen = length;
    length = (length << 1) + 1;
    Entry* h = new Entry[length];
    sz = 0;
    for(size_t i = 0; i < length; i ++){
        (h+i)->next = nullptr;
    }
    for(size_t i = 0; i < oldLen;i++){
        Entry* p = (old + i)->next;
        while(p != nullptr){
            h = add(h, p->key, p->val);
            p = p->next;
        }
    }
    for(size_t i = 0; i < oldLen; i ++)release(old + i);
    delete[] old;
    old = h;
    
    return old;
}

void del(Entry* ht, ll key){
    ll hashCode = hashf(key);
    size_t pos = calpos(hashCode, length);
    Entry* prev = ht + pos;
    Entry* curr = prev->next;
    while(curr != nullptr && curr->key != key){
        prev = curr;
        curr = curr->next;
    }
    Entry* p = curr;
    prev->next = prev->next->next;
    sz--;
    delete p;
}

void search(Entry* ht, size_t pos){
    Entry* h = ht + pos;
    print(h);
}

void print(Entry* entry){
    Entry* p = entry->next;
    if(p == nullptr){
        puts("null");
        return;
    }
    while(p != nullptr){
        cout << p->key << ":" << p->val;
        if(p->next != nullptr)cout <<"->";
        p = p->next;
    }
    puts("");
}

void release(Entry* h){
    Entry* p = h->next;
    while(p != nullptr){
        Entry* q = p->next;
        delete p;
        p = q;
    }
}