#include <string>

#include "eventuals/eventual.h"
#include "eventuals/promisify.h"
#include "eventuals/raise.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Eventual<std::string>()
        .start([](auto& k) {
          auto thread = std::thread(
              [&k]() mutable {
                sleep(2);
                k.Start("awake!");
              });
          thread.detach();
          std::cout << "thread will sleep for 2 seconds ..." << std::endl;
        })
        .fail([](auto& k, auto&& e) {
          // "Catch" raised error.
          CHECK_STREQ("error!", e.what());
          k.Start("never slept!");
        })
        .stop([](auto& k) {
          k.Stop(); // Propagate stop.
        });
  };

  CHECK_EQ("never slept!", *(Raise("error!") >> e()));

  return 0;
}
