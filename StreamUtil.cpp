#include "StreamUtil.h"

namespace StreamUtil {
// START:size
   std::streamsize size(std::istream& stream) {
      stream.seekg(0, std::ios::end);
      return stream.tellg();
   } 
// END:size
}
