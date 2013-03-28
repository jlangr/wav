#ifndef FileUtil_h
#define FileUtil_h

#include <ios>
#include <istream>
#include <fstream>
#include <functional>

// START:FileUtil
class FileUtil {
public:
   std::streamsize size(const std::string& name) {
      std::ifstream stream{name, std::ios::in | std::ios::binary};
      stream.seekg(0, std::ios::end);
      return stream.tellg();
   }
// END:FileUtil

// START:execute
   std::streamsize execute(
         const std::string& name, 
         std::function<std::streamsize (std::istream&)> func) {
      std::ifstream stream{name, std::ios::in | std::ios::binary};
      return func(stream);
   }
// END:execute
// START:FileUtil
};
// END:FileUtil
#endif
