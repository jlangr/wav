#ifndef Snippet_h
#define Snippet_h

using namespace std;

// START:snippet
class Snippet {
public:
// START_HIGHLIGHT
   Snippet(shared_ptr<FileUtil> fileUtil,
      shared_ptr<WavDescriptor> descriptor,
      const std::string& dest,
      rlog::RLogChannel* channel) 
      : fileUtil_(fileUtil)
      , descriptor_(descriptor)
      , dest_(dest) 
      , channel_(channel) { }
// END_HIGHLIGHT
// ...
// END:snippet

   uint32_t dataLength(
         uint32_t samples, 
         uint32_t bytesPerSample,
         uint32_t channels
         ) const {
      return samples * bytesPerSample * channels;
   }

// START:snippet
// START_HIGHLIGHT
private:
   shared_ptr<FileUtil> fileUtil_;
   shared_ptr<WavDescriptor> descriptor_;
   const string dest_;
   rlog::RLogChannel* channel_;
// END_HIGHLIGHT
};
// END:snippet

#endif
