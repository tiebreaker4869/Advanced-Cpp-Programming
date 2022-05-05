#include <iostream>

using namespace std;

//链表节点
struct Node{    
    Node* next;//前一个节点    
    Node* prev;//后一个节点    
    int val;//该节点存放的数字
    bool isFront;
    bool isRear;
};
//双端队列
struct Deque{    
    int size;//有效节点数    
    Node* front;//虚拟头节点，不作为有效节点    
    Node* rear;//虚拟尾节点，不作为有效节点
};

void push_front (Deque* self, int value){
    Node * p = new Node;
    p->val = value;
    p->next = nullptr;
    p->prev = nullptr;
    p->isFront = false;
    p->isRear = false;
    
    p->next = self->front->next;
    p->prev = self->front;
    self->front->next->prev = p;
    self->front->next = p;
    self->size++;
}

void push_back (Deque* self, int value){
    Node* p = new Node;
    p->val = value;
    p->next = nullptr;
    p->prev = nullptr;
    p->isFront = false;
    p->isRear = false;
    
    p->next = self->rear;
    p->prev = self->rear->prev;
    self->rear->prev->next = p;
    self->rear->prev = p;
    self->size++;
}

void pop_front (Deque* self){
    if(self->front->next->isRear){
        puts("-1");
        return;
    }
    cout << self->front->next->val << endl;
    Node* p = self->front->next;
    self->front->next->next->prev = self->front;
    self->front->next = self->front->next->next;
    delete p;
    self->size --;
}

void pop_back (Deque* self){
    if(self->rear->prev->isFront){
        puts("-1");
        return;
    }
    
    cout << self->rear->prev->val << endl;
    Node* p = self->rear->prev;
    self->rear->prev->prev->next = self->rear;
    self->rear->prev = self->rear->prev->prev;
    delete p;
    self->size --;
}

void release(Deque* self){
    Node* p = self->front;
    while(p != nullptr){
        Node* q = p->next;
        delete p;
        p = q;
    }
    delete self;
}

int main(){
    Deque* dq = new Deque;
    dq->size = 0;
    Node* p = new Node;
    p->val = 0;
    p->isFront = true;
    p->isRear = false;
    p->prev = nullptr;
    p->next = nullptr;
    dq->front = p;
    p = new Node;
    p->val = 0;
    p->isFront = false;
    p->isRear = true;
    p->prev = nullptr;
    p->next = nullptr;
    dq->rear = p;
    dq->front->next = dq->rear;
    dq->rear->prev = dq->front;
    int n, x;
    string s;
    cin >> n;
    while(n--){
        cin >> s;
        if(s == "pushFront"){
            cin >> x;
            push_front(dq, x);
        }else if(s == "pushBack"){
            cin >> x;
            push_back(dq, x);
        }else if(s == "popBack"){
            pop_back(dq);
        }else if(s == "popFront"){
            pop_front(dq);
        }else{
            cout << dq->size << endl;
        }
    }
    
    release(dq);
    
    return 0;
}