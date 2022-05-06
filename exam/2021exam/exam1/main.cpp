#include <iostream>
#include <cstdio>

using namespace std;


uint32_t * mapping;
bool * st;
uint32_t input(int heap_size, uint32_t* &heap){
    int block_num = (heap_size % 8 == 0) ? heap_size / 8 : heap_size / 8 + 1;
    heap = new uint32_t [2 * block_num];
    return block_num* 2;
}

void init(uint32_t* heap, uint32_t line_no){
    heap[0] = (line_no-2) << 2;
    heap[line_no-1] = (line_no-2) << 2;
    for(uint32_t i = 1; i < line_no-1; i ++){
        heap[i] = 0xdfdfdfdf;
    }
}

bool alloc(uint32_t* heap, uint32_t max_line_no, uint32_t size, int id){
    size = size % 8 == 0 ? size / 8 : size / 8 + 1;
    for(uint32_t i = 0; i < max_line_no; i ++){

        if(heap[i] != 0xdfdfdfdf && !(heap[i] & 1) && (heap[i]>>3) >= size){
            uint32_t original_size = heap[i] >> 3;
            mapping[id] = i;
            uint32_t line_count = size << 1;
            heap[i] = (size << 3) | 0x1;
            heap[i + line_count + 1] = (size << 3) | 0x1;
            if(original_size > size){
                heap[i + line_count + 2] = (original_size - size - 1) << 3;
                uint32_t tmp = i + line_count + 3;
                while(heap[tmp] == 0xdfdfdfdf){
                    tmp ++;
                }
                heap[tmp] = (original_size - size - 1) << 3;
            }
            st[id] = true;
            return true;
        }
    }

    return false;
}

bool do_free(uint32_t * heap,int obj_id){
    if(!st[obj_id])return false;
    uint32_t line_no = mapping[obj_id];
    uint32_t header = line_no;
    if(!(heap[header] & 1))return false;
    uint32_t tail = line_no + 1;
    while(heap[tail] == 0xdfdfdfdf)tail ++;
    heap[header] = heap[header] & 0xfffffffe;
    heap[tail] = heap[tail] & 0xfffffffe;
    st[obj_id] = false;

    return true;
}

void show(const uint32_t* heap, const uint32_t max_line_no){
    for(uint32_t i = 0; i < max_line_no; i ++){
        if(heap[i] == 0xdfdfdfdf)
            cout << hex << heap[i] << endl;
        else {
            int len = 0;
            int tmp = heap[i];
            while(tmp){
                len ++;
                tmp = tmp >> 4;
            }
            if(heap[i] == 0)len = 1;
            string stuff = "00000000";
            stuff = stuff.substr(0, 8-len);
            cout << stuff << hex << heap[i] << endl;
        }
    }
}

int main() {
    int heap_size, obj_num, cmd_num;
    cin >> heap_size >> obj_num;

    uint32_t * heap = nullptr;
    uint32_t  line_no = input(heap_size, heap);
    mapping = new uint32_t [obj_num + 1];
    st = new bool [obj_num+1];
    for(int i = 1; i <= obj_num; i ++){
        st[i] = false;
    }
    init(heap, line_no);

    cin >> cmd_num;
    while(cmd_num --){
        string cmd;
        int obj_id, obj_size;
        cin >> cmd;

        if(cmd == "ALLOC"){
            cin >> obj_id >> obj_size;
            if(obj_id > obj_num){
                cout << "failed to alloc object " << obj_id << endl;
                continue;
            }
            bool success = alloc(heap, line_no, obj_size, obj_id);
            if(success)cout << "succeeded to alloc object " << obj_id << endl;
            else cout << "failed to alloc object " << obj_id << endl;
        }else if(cmd == "FREE"){
            cin >> obj_id;
            if(obj_id > obj_num){
                cout << "invalid memory access" << endl;
                continue;
            }
            bool success = do_free(heap ,obj_id);
            if(!success)cout << "invalid memory access" << endl;
            else printf("succeeded to free object %d\n", obj_id);
        }else {
            show(heap, line_no);
        }

    }

    return 0;
}
