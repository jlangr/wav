#ifndef WavReader_h
#define WavReader_h

#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

#include "WavDescriptor.h"
#include "rlog/StdioNode.h"
#include "rlog/RLogChannel.h"

bool hasExtension(const std::string& text, const std::string& substring);

struct FormatSubchunk;
struct FormatSubchunkHeader;
struct DataChunk;

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
public:
   void writeSamples(std::ostream* out, char* data, 
         uint32_t startingSample, 
         uint32_t samplesToWrite, 
         uint32_t bytesPerSample,
         uint32_t channels=1);

   uint32_t dataLength(
         uint32_t samples, 
         uint32_t bytesPerSample,
         uint32_t channels) const;

   void writeSnippet(
         const std::string& name, std::istream& file, std::ostream& out,
         FormatSubchunk& formatSubchunk,
         DataChunk& dataChunk,
         char* data);

private:
   rlog::StdioNode log{STDERR_FILENO};
   WavDescriptor* descriptor_;

   void readAndWriteHeaders(
         const std::string& name,
         std::istream& file,
         std::ostream& out,
         FormatSubchunk&,
         FormatSubchunkHeader&);
   void read(
         std::istream& file,
         DataChunk&);
   char* readData(std::istream& file, int32_t length);

   void seekToEndOfHeader(std::ifstream& file, int headerLength);
   std::string toString(int8_t* c, unsigned int size);

   rlog::RLogChannel* channel;

   std::string source_;
   std::string dest_;
};

#endif  
