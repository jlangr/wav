#ifndef Snippet_h
#define Snippet_h

#include "FileUtil.h"
#include "WavDescriptor.h"
#include "WavStructs.h"
#include "rlog/RLogChannel.h"
#undef RLOG_SECTION
#define RLOG_SECTION
// see https://code.google.com/p/rlog/issues/detail?id=13

#include <string>
#include <memory>
#include <algorithm>

class Snippet {
public:
   Snippet(std::shared_ptr<FileUtil> fileUtil,
      std::shared_ptr<WavDescriptor> descriptor,
      const std::string& dest,
      rlog::RLogChannel* channel) 
      : fileUtil_(fileUtil)
      , descriptor_(descriptor)
      , dest_(dest) 
      , channel_(channel) { }

   void write(
         const std::string& name, std::istream& file, std::ostream& out,
         FormatSubchunk& formatSubchunk,
         DataChunk& dataChunk,
         char* data
         ) {
      uint32_t secondsDesired{10};
      if (formatSubchunk.bitsPerSample == 0) formatSubchunk.bitsPerSample = 8;
      uint32_t bytesPerSample{formatSubchunk.bitsPerSample / uint32_t{8}};

      uint32_t samplesToWrite{secondsDesired * formatSubchunk.samplesPerSecond};
      uint32_t totalSamples{dataChunk.length / bytesPerSample};

      samplesToWrite = std::min(samplesToWrite, totalSamples);

      uint32_t totalSeconds { totalSamples / formatSubchunk.samplesPerSecond };

      rLog(channel_, "total seconds %u ", totalSeconds);

      dataChunk.length = dataLength(
            samplesToWrite, 
            bytesPerSample, 
            formatSubchunk.channels);
      out.write(reinterpret_cast<char*>(&dataChunk), sizeof(DataChunk));

      uint32_t startingSample{
         totalSeconds >= 10 ? 10 * formatSubchunk.samplesPerSecond : 0};

      writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

      rLog(channel_, "completed writing %s", name.c_str());

      auto fileSize = fileUtil_->size(name);

      descriptor_->add(dest_, name, 
            totalSeconds, formatSubchunk.samplesPerSecond, formatSubchunk.channels,
            fileSize);
   }

   uint32_t dataLength(
         uint32_t samples, 
         uint32_t bytesPerSample,
         uint32_t channels
         ) const {
      return samples * bytesPerSample * channels;
   }

   void writeSamples(std::ostream* out, char* data, 
         uint32_t startingSample, 
         uint32_t samplesToWrite, 
         uint32_t bytesPerSample,
         uint32_t channels=1) {
      rLog(channel_, "writing %u samples", samplesToWrite);

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
   }

private:
   std::shared_ptr<FileUtil> fileUtil_;
   std::shared_ptr<WavDescriptor> descriptor_;
   const std::string dest_;
   rlog::RLogChannel* channel_;
};

#endif

