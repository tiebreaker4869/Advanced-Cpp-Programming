#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <stack>
#include <queue>

class Data {
    private:
        int data;
    public:
        Data();
};

Data::Data(){
    this->data = 0;
}
// 除了 TODO 标出的部分，不要修改原有的声明和定义，否则后果自负！
class MemoryContext {
 public:
  /**
   * @param parent 父节点，可能为 nullptr
   */
  MemoryContext(MemoryContext *parent);

  ~MemoryContext();

  // 禁止拷贝和移动
  MemoryContext(const MemoryContext &) = delete;
  MemoryContext &operator=(const MemoryContext &) = delete;
  MemoryContext(MemoryContext &&) = delete;
  MemoryContext &operator=(MemoryContext &&) = delete;

  using chunk_id_t = std::string;

  void alloc(const chunk_id_t &chunk_id);

 private:
  // TODO: your code
  MemoryContext* parent;
  std::stack<Data*> stk;
  std::unordered_map<Data*, chunk_id_t> record;
  std::queue<MemoryContext*> children;
};

MemoryContext::MemoryContext(MemoryContext *parent) {
  // TODO: your code
  this->parent = parent;
  if(parent != nullptr)this->parent->children.push(this);
}

MemoryContext::~MemoryContext() {
  // TODO: your code
  while(!children.empty()){
    MemoryContext* child = children.front();
    children.pop();
    delete child;
  }

  while(!stk.empty()){
    Data* data = stk.top();
    stk.pop();
    std::cout << "Chunk " << record[data] << " freed." << std::endl; 
    delete data;
  }
}

void MemoryContext::alloc(const chunk_id_t &chunk_id) {
  // TODO: your code
  Data* data = new Data;
  record[data] = chunk_id;
  stk.push(data);
}

void test_1() {
  std::unique_ptr<MemoryContext> A = std::make_unique<MemoryContext>(nullptr);
  A->alloc("1");
  A->alloc("2");
  A->alloc("3");
}

void test_2() {
  std::unique_ptr<MemoryContext> A = std::make_unique<MemoryContext>(nullptr);
  MemoryContext *B = new MemoryContext(A.get());
  MemoryContext *C = new MemoryContext(B);

  A->alloc("1");
  A->alloc("2");
  A->alloc("3");
  B->alloc("1/1");
  B->alloc("1/2");
  B->alloc("1/3");
  C->alloc("1/1/1");
  C->alloc("1/1/2");
  C->alloc("1/1/3");
}

void test_3() {
  std::unique_ptr<MemoryContext> A = std::make_unique<MemoryContext>(nullptr);
  MemoryContext *B = new MemoryContext(A.get());
  MemoryContext *C = new MemoryContext(A.get());
  MemoryContext *D = new MemoryContext(B);
  MemoryContext *E = new MemoryContext(C);
  MemoryContext *F = new MemoryContext(C);
  MemoryContext *G = new MemoryContext(E);

  A->alloc("1");
  A->alloc("2");
  A->alloc("3");
  B->alloc("1/1");
  C->alloc("1/2");
  D->alloc("1/1/1");
  D->alloc("1/1/2");
  G->alloc("1/2/1/1");
}

void test_4() {
  std::unique_ptr<MemoryContext> A = std::make_unique<MemoryContext>(nullptr);
  MemoryContext *B = new MemoryContext(A.get());
  MemoryContext *C = new MemoryContext(A.get());
  MemoryContext *D = new MemoryContext(B);
  MemoryContext *E = new MemoryContext(B);
  MemoryContext *F = new MemoryContext(C);
  MemoryContext *G = new MemoryContext(C);

  A->alloc("1");
  A->alloc("2");
  A->alloc("3");
  B->alloc("1/1");
  C->alloc("1/2");
  D->alloc("1/1/1");
  D->alloc("1/1/3");
  E->alloc("1/1/2");
  F->alloc("1/2/1");
  G->alloc("1/2/3");
  G->alloc("1/2/5");
  G->alloc("1/2/2");
  G->alloc("1/2/4");
}

void test_5() {
  std::unique_ptr<MemoryContext> A = std::make_unique<MemoryContext>(nullptr);
  MemoryContext *B = new MemoryContext(A.get());
  MemoryContext *C = new MemoryContext(A.get());
  MemoryContext *D = new MemoryContext(B);
  MemoryContext *G = new MemoryContext(C);

  A->alloc("2");
  A->alloc("1");
  A->alloc("3");
  A->alloc("4");
  B->alloc("2/1");
  B->alloc("3/5");
  C->alloc("1024/2");
  C->alloc("1024/1");
  G->alloc("8192/1/4095");
}

#define REGISTER_TEST_CASE(name) \
  { #name, name }

int main() {
  std::unordered_map<std::string, std::function<void()>>
      test_functions_by_name = {
          REGISTER_TEST_CASE(test_1), REGISTER_TEST_CASE(test_2),
          REGISTER_TEST_CASE(test_3), REGISTER_TEST_CASE(test_4),
          REGISTER_TEST_CASE(test_5),
      };

  std::string test_case_name;
  std::cin >> test_case_name;
  auto it = test_functions_by_name.find(test_case_name);
  assert(it != test_functions_by_name.end());
  auto fn = it->second;
  fn();
}