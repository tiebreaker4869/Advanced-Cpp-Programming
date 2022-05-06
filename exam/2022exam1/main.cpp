#include <iostream>
#include <cstdio>

using namespace std;

struct DoneTask {
    int oid;
    DoneTask* next;
};

DoneTask* globalDoneList;

struct Order {
    int oid;
    int priority;
    int time_;
    int type;
};

struct Worker {
    int uid;
    int type;
    int currentTaskId;//-1 if resting
    int currentTaskLeftTime;//-1 if resting
    DoneTask* doneList;

    bool isWorking(){
        return currentTaskId > 0;
    }

    void pickTask(Order* order){
        if(type != order->type)cout << "type not match" << endl;
        currentTaskId = order->oid;
        currentTaskLeftTime = order->time_;
    }


    void working(){
        currentTaskLeftTime --;
        if(currentTaskLeftTime == 0){
            DoneTask* d = new DoneTask;
            d->oid = currentTaskId;
            d->next = doneList->next;
            doneList->next = d;
            d = new DoneTask;
            d->oid = currentTaskId;
            d->next = globalDoneList->next;
            globalDoneList->next = d;
            currentTaskId = -1;
            currentTaskLeftTime = -1;

        }
    }
};


struct Scheduler {
    Order* orderLst;
    int capacity;
    int curSize;
    Scheduler(int capacity){
        this->capacity = capacity;
        orderLst = new Order[capacity];
        curSize = 0;
    }

    void removeLeastPriority(){
        int minId = 0;
        int minPriority = orderLst[0].priority;
        for(int i = 1; i < capacity; i ++){
            if(orderLst[i].priority < minPriority){
                minId = i;
                minPriority = orderLst[i].priority;
            }
        }
        if(minId == capacity-1)curSize --;
        else {
            for(int i = minId; i < capacity-1; i ++)orderLst[i] = orderLst[i+1];
            curSize --;
        }
    }

    void add(Order* order){
        if(curSize == capacity)removeLeastPriority();
        orderLst[curSize++] = *order;
    }

    Order* poll(int type){
        if(curSize == 0)return nullptr;
        int maxId = -1, maxPriority = -1;
        for(int i = 0; i < curSize; i ++){
            if(orderLst[i].type == type){
                if(orderLst[i].priority > maxPriority){
                    maxPriority = orderLst[i].priority;
                    maxId = i;
                }
            }
        }
        if(maxId == -1)return nullptr;
        Order* task = new Order;
        *task = {orderLst[maxId].oid, orderLst[maxId].priority, orderLst[maxId].time_, orderLst[maxId].type};

        for(int i = maxId; i < curSize; i ++)orderLst[i] = orderLst[i+1];
        curSize --;
        return task;
    }

    bool contains(int oid){
        for(int i = 0; i < curSize; i ++){
            if(orderLst[i].oid == oid)return true;
        }

        return false;
    }
};

int main(){
    //IO and preparation
    int numOfWorkers, stageLimit;
    cin >> numOfWorkers >> stageLimit;
    Worker* workers = new Worker[numOfWorkers];
    Scheduler scheduler(stageLimit);
    //dummy node
    globalDoneList = new DoneTask;
    globalDoneList->oid = -1;
    globalDoneList->next = nullptr;
    for(int i = 0; i < numOfWorkers; i ++){
        int uid, type;
        cin >> uid >> type;
        DoneTask* dummy = new DoneTask;
        dummy->next = nullptr;
        workers[i] = {uid, type, -1, -1,dummy};
    }
    int cmdNum;
    cin >> cmdNum;
    string cmd;

    //doing task
    while(cmdNum --){
        bool justDone = false;
        int justDoneId = 0;
        //do scheduling first
        for(int i = 0; i < numOfWorkers; i ++){
            if(workers[i].isWorking()){
                justDoneId = workers[i].currentTaskId;
                workers[i].working();
                if(!workers[i].isWorking())justDone = true;
            }
            else {
                Order* task = scheduler.poll(workers[i].type);
                if(task != nullptr){
                    workers[i].pickTask(task);
                    workers[i].working();
                }
            }
        }
        //do cmd
        cin >> cmd;
        if(cmd == "add"){
            int oid, priority, time_, type;
            cin >> oid >> priority >> time_ >> type;
            //handle task
            Order* order = new Order;
            *order = {oid, priority, time_, type};
            scheduler.add(order);
        }else if(cmd == "queryUser"){
            int uid;
            cin >> uid;
            for(int i = 0; i < numOfWorkers; i ++){
                if(workers[i].uid == uid){
                    if(workers[i].isWorking()){
                        printf("worker %d doing order %d\n", uid, workers[i].currentTaskId);
                    }else if(justDone){
                        printf("worker %d doing order %d\n", uid, justDoneId);
                    }
                    else {
                        printf("worker %d is resting\n", uid);
                    }
                    break;
                }
            }
        }else if(cmd == "queryOrder"){
            int oid;
            cin >> oid;
            //handle task
            bool pending = scheduler.contains(oid);
            bool done = false;
            DoneTask* cur = globalDoneList;
            while(cur!= nullptr && cur->oid != oid)cur = cur->next;
            done = (cur != nullptr);
            bool doing = false;
            for(int i = 0; i < numOfWorkers; i ++){
                if(workers[i].currentTaskId == oid){
                    doing = true;
                    break;
                }
            }
            if(pending)printf("order %d pending\n", oid);
            else if(done)printf("order %d done\n", oid);
            else if(doing)printf("order %d doing\n", oid);
            else printf("order %d discarded\n", oid);
        }else if(cmd == "queryOrders"){

            int uid;
            cin >> uid;
            //handle task
            int cnt = 0;
            int index = 0;
            for(int i = 0; i < numOfWorkers; i ++){
                if(workers[i].uid == uid){
                    index = i;
                    break;
                }
            }
            DoneTask* cur = workers[index].doneList->next;
            while(cur != nullptr){
                cur = cur->next;
                cnt ++;
            }
            if(cnt == 0)cout << endl;
            int* tmp = new int[cnt];
            cur = workers[index].doneList->next;
            cnt = 0;
            while(cur != nullptr){
                tmp[cnt++] = cur->oid;
                cur = cur->next;
            }
            for(int i = cnt-1; i >= 0; i --){
                printf("%d", tmp[i]);
                if(i > 0)cout << " ";
            }
            cout << endl;
            delete[] tmp;
        }else {
            cout << "invalid command !" << endl;
        }
        fflush(stdout);
    }

    //free space
    delete[] workers;

    return 0;
}