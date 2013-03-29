#ifndef WavDescriptor_h
#define WavDescriptor_h

#include <string>
#include <cstdint>
#include <cstring>
#include <fstream>

struct WavDescriptorRecord {
   int8_t filename[64]; 
   uint32_t seconds;
   uint32_t samplesPerSecond;
   uint32_t channels;
};

class WavDescriptor {
public:

   WavDescriptor(const std::string& dir) {
      outstr = new std::ofstream(dir + "/WavSnippets.dat", std::ios::out | std::ios::binary);
   }

// START:virtual
// START_HIGHLIGHT
   virtual void add(const std::string& dir, const std::string& filename, uint32_t totalSeconds, uint32_t samplesPerSecond, uint32_t channels) {
      // ...
// END_HIGHLIGHT
      WavDescriptorRecord rec;
      cpy(rec.filename, filename.c_str());
      rec.seconds = totalSeconds;
      rec.samplesPerSecond = samplesPerSecond;
      rec.channels = channels;

      outstr->write(reinterpret_cast<char*>(&rec), sizeof(WavDescriptorRecord));
   }
// END:virtual

   void cpy(int8_t* dest, const char* src) {
      for (int i = 0; src[i] != 0; i++) dest[i] = src[i];
   }

   ~WavDescriptor() {
      outstr->close();
      delete outstr;
   }

private:
   std::ofstream* outstr;
};

#endif
