#ifndef WavReader_h
#define WavReader_h

#include <boost/filesystem.hpp>

#include "WavDescriptor.h"
#include "WavStructs.h"
#include "FileUtil.h"
#include "rlog/StdioNode.h"
#include "rlog/RLogChannel.h"

bool hasExtension(const std::string& text, const std::string& substring);

struct FormatSubchunkHeader;

class WavReader {
public:
   WavReader(
         const std::string& source, 
         const std::string& dest,
         std::shared_ptr<WavDescriptor> descriptor=0);
   virtual ~WavReader();
   void open(const std::string& name, bool trace);
   void list(
         const boost::filesystem::path& dir, 
         const std::string &filename, 
         std::vector<boost::filesystem::path>& found) const;
   void listAll() const;
   void publishSnippets();

   void useFileUtil(std::shared_ptr<FileUtil>);

private:
   rlog::StdioNode log{STDERR_FILENO};

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
   std::shared_ptr<WavDescriptor> descriptor_;
   std::shared_ptr<FileUtil> fileUtil_;
};

#endif  
