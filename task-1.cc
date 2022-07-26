#include "eventuals/just.h"
#include "eventuals/promisify.h"
#include "eventuals/task.h"
#include "eventuals/then.h"

using namespace eventuals;

Task::Of<std::string> SomeFunction() {
  return []() {
    return Just(42)
        >> Then([](int i) {
             return Just(std::to_string(i));
           });
  };
}

int main(int argc, char** argv) {
  CHECK_EQ("42", *SomeFunction());

  return 0;
}
