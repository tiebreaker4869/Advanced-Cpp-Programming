#include <iostream>
#include <cassert>

using namespace std;

struct Node{
    int val;
    Node* next;
};

void release(Node* head){
    assert(head != nullptr);
    
    Node* p = head;
    while (p != nullptr){
        Node * q = p->next;
        delete p;
        p = q;
    }
}

void print(const Node* head){
    assert(head != nullptr);
    if(head->next == nullptr){
        cout << "<null>" << endl;
        return;
    }
    const Node* p = head->next;
    while(p != nullptr){
        cout << p->val << " "; 
        p = p->next;
    }
    cout << endl;
}

Node* reverseList(Node* head){
    if(head == nullptr || head->next == nullptr)return head;
    
    Node* newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    
    return newHead;
}

int main(){
    int x;
    Node* dummy = new Node;
    dummy->val = -1;
    dummy->next = nullptr;
    Node* tail = dummy;
    while(cin >> x){
        Node* p = new Node;
        p->val = x;
        p->next = nullptr;
        
        p->next = tail->next;
        tail->next = p;
        tail = tail->next;
    }
    
    dummy->next = reverseList(dummy->next);
    
    print(dummy);
    
    return 0;
}
