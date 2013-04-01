#ifndef Snippet_h
#define Snippet_h

using namespace std;

// START:snippet
class Snippet {
public:
// START_HIGHLIGHT
   uint32_t dataLength(
         uint32_t samples, 
         uint32_t bytesPerSample,
         uint32_t channels
         ) const {
      return samples * bytesPerSample * channels;
   }
// END_HIGHLIGHT
};
// END:snippet

#endif
