#ifndef WavReader_h
#define WavReader_h

#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

#include "WavDescriptor.h"
#include "rlog/StdioNode.h"

bool hasExtension(const std::string& text, const std::string& substring);

class WavReader {
public:
   WavReader(const std::string& source, const std::string& dest);
   virtual ~WavReader();
   void open(const std::string& name, bool trace);
   void list(
         const boost::filesystem::path& dir, 
         const std::string &filename, 
         std::vector<boost::filesystem::path>& found) const;
   void listAll() const;
   void publishSnippets();
// START:writeSamples
public:
   // ...
   void writeSamples(std::ofstream& out, char* data, 
         uint32_t startingSample, 
         uint32_t samplesToWrite, 
         uint32_t bytesPerSample);
// END:writeSamples

private:
   rlog::StdioNode log{STDERR_FILENO};
   WavDescriptor* descriptor_;

   void seekToEndOfHeader(std::ifstream& file, int headerLength);
   std::string toString(int8_t* c, unsigned int size);

   std::string source_;
   std::string dest_;
};

#endif  
