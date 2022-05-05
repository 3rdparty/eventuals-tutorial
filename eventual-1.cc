#include <string>

#include "eventuals/eventual.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Eventual<std::string>([](auto& k) {
      auto thread = std::thread(
          [&k]() mutable {
            sleep(2);
            k.Start("awake!");
          });
      thread.detach();
      std::cout << "thread will sleep for 2 seconds ..." << std::endl;
    });
  };

  CHECK_EQ("awake!", *e());

  return 0;
}
