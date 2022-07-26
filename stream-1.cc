#include <string>

#include "eventuals/loop.h"
#include "eventuals/promisify.h"
#include "eventuals/stream.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Stream<int>()
               .context(/* count = */ 100)
               .next([](auto& count, auto& k) {
                 if (count-- > 0) {
                   k.Emit(1);
                 } else {
                   k.Ended();
                 }
               })
               .done([](auto& count, auto& k) {
                 k.Ended();
               })
        >> Loop<int>()
               .context(/* sum = */ 0)
               .body([](auto& sum, auto& stream, auto&& value) {
                 if (sum < 42) {
                   sum += value;
                   stream.Next();
                 } else {
                   stream.Done();
                 }
               })
               .ended([](auto& sum, auto& k) {
                 k.Start(sum);
               })
               .fail([](auto& sum, auto& k, auto&& e) {
                 k.Fail(std::forward<decltype(e)>(e)); // Propagate error.
               })
               .stop([](auto& sum, auto& k) {
                 k.Stop(); // Propagate stop.
               });
  };

  CHECK_EQ(42, *e());

  return 0;
}
