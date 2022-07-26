#include <string>

#include "eventuals/collect.h"
#include "eventuals/iterate.h"
#include "eventuals/map.h"
#include "eventuals/promisify.h"

using namespace eventuals;

int main(int argc, char** argv) {
  auto e = []() {
    return Iterate({"hello", " ", "world", "!"})
        >> Map([](std::string&& s) {
             s[0] = std::toupper(s[0]);
             return std::move(s);
           })
        >> Collect<std::vector<std::string>>()
        >> Then([](std::vector<std::string>&& v) {
             std::string result;
             for (std::string& s : v) {
               result += std::move(s);
             }
             return result;
           });
  };

  CHECK_EQ("Hello World!", *e());

  return 0;
}
