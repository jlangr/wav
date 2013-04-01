#ifndef Snippet_h
#define Snippet_h

using namespace std;

// START:snippet
class Snippet {
public:
   // ... 
// END:snippet
   Snippet(shared_ptr<FileUtil> fileUtil,
      shared_ptr<WavDescriptor> descriptor,
      const std::string& dest,
      rlog::RLogChannel* channel) 
      : fileUtil_(fileUtil)
      , descriptor_(descriptor)
      , dest_(dest) 
      , channel_(channel) { }

// START:snippet
   void writeSnippet(
         const string& name, istream& file, ostream& out,
         FormatSubchunk& formatSubchunk,
         DataChunk& dataChunk,
         char* data
         ) {
      uint32_t secondsDesired{10};
      if (formatSubchunk.bitsPerSample == 0) formatSubchunk.bitsPerSample = 8;
      uint32_t bytesPerSample{formatSubchunk.bitsPerSample / uint32_t{8}};

      uint32_t samplesToWrite{secondsDesired * formatSubchunk.samplesPerSecond};
      uint32_t totalSamples{dataChunk.length / bytesPerSample};

      samplesToWrite = min(samplesToWrite, totalSamples);

      uint32_t totalSeconds { totalSamples / formatSubchunk.samplesPerSecond };

// START_HIGHLIGHT
      rLog(channel_, "total seconds %i ", totalSeconds);
// END_HIGHLIGHT

      dataChunk.length = dataLength(
            samplesToWrite, 
            bytesPerSample, 
            formatSubchunk.channels);
      out.write(reinterpret_cast<char*>(&dataChunk), sizeof(DataChunk));

      uint32_t startingSample{
         totalSeconds >= 10 ? 10 * formatSubchunk.samplesPerSecond : 0};

      writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

// START_HIGHLIGHT
      rLog(channel_, "completed writing %s", name.c_str());
// END_HIGHLIGHT

      auto fileSize = fileUtil_->size(name);

      descriptor_->add(dest_, name, 
            totalSeconds, formatSubchunk.samplesPerSecond, formatSubchunk.channels,
            fileSize);
      
      //out.close(); // ostreams are RAII
   }
// END:snippet

   uint32_t dataLength(
         uint32_t samples, 
         uint32_t bytesPerSample,
         uint32_t channels
         ) const {
      return samples * bytesPerSample * channels;
   }

// START:snippet
   void writeSamples(ostream* out, char* data, 
         uint32_t startingSample, 
         uint32_t samplesToWrite, 
         uint32_t bytesPerSample,
// START_HIGHLIGHT
         uint32_t channels=1) {
// END_HIGHLIGHT
// START_HIGHLIGHT
      rLog(channel_, "writing %i samples", samplesToWrite);
// END_HIGHLIGHT
      // ...
// END:snippet

      for (auto sample = startingSample; 
           sample < startingSample + samplesToWrite; 
           sample++) {
         auto byteOffsetForSample = sample * bytesPerSample * channels;
         for (uint32_t channel{0}; channel < channels; channel++) {
            auto byteOffsetForChannel =
               byteOffsetForSample + (channel * bytesPerSample);
            for (uint32_t byte{0}; byte < bytesPerSample; byte++) 
               out->put(data[byteOffsetForChannel + byte]);
         }
      }
// START:snippet
   }
// END:snippet

private:
   shared_ptr<FileUtil> fileUtil_;
   shared_ptr<WavDescriptor> descriptor_;
   const string dest_;
   rlog::RLogChannel* channel_;
// START:snippet
};
// END:snippet

#endif
