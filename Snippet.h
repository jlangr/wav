// START:snippet
#ifndef Snippet_h
#define Snippet_h

class Snippet {
public:
   void writeSnippet(
         const string& name, istream& file, ostream& out,
         FormatSubchunk& formatSubchunk,
         DataChunk& dataChunk,
         char* data
         ) {
      // ...
   uint32_t secondsDesired{10};
   if (formatSubchunk.bitsPerSample == 0) formatSubchunk.bitsPerSample = 8;
   uint32_t bytesPerSample{formatSubchunk.bitsPerSample / uint32_t{8}};

   uint32_t samplesToWrite{secondsDesired * formatSubchunk.samplesPerSecond};
   uint32_t totalSamples{dataChunk.length / bytesPerSample};

   samplesToWrite = min(samplesToWrite, totalSamples);

   uint32_t totalSeconds { totalSamples / formatSubchunk.samplesPerSecond };

   rLog(channel, "total seconds %i ", totalSeconds);

   dataChunk.length = dataLength(
         samplesToWrite, 
         bytesPerSample, 
         formatSubchunk.channels);
   out.write(reinterpret_cast<char*>(&dataChunk), sizeof(DataChunk));

   uint32_t startingSample{
      totalSeconds >= 10 ? 10 * formatSubchunk.samplesPerSecond : 0};

   writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

   rLog(channel, "completed writing %s", name.c_str());

   auto fileSize = fileUtil_->size(name);

   descriptor_->add(dest_, name, 
         totalSeconds, formatSubchunk.samplesPerSecond, formatSubchunk.channels,
         fileSize);
   
   //out.close(); // ostreams are RAII
// END:snippet
// START:snippet
   }
};

#endif
// END:snippet
