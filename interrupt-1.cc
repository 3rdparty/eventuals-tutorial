#include <iostream>
#include <string>

#include "eventuals/eventual.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Eventual<std::string>()
        .interruptible()
        .context("interrupted!")
        .start([](auto& context, auto& k, Interrupt::Handler& handler) {
          handler.Install([&]() {
            k.Start(context);
          });
          std::cout << "nothing happening until interrupt ..." << std::endl;
        });
  };

  auto [future, k]  = Promisify("[interrupt-1]", e());

  Interrupt interrupt;

  k.Register(interrupt);

  k.Start();

  std::cout << "interrupting in 2 seconds ..." << std::endl;

  sleep(2);

  interrupt.Trigger();

  CHECK_EQ("interrupted!", future.get());

  return 0;
}
