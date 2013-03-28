#include "CppUTest/TestHarness.h"

#include "WavReader.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

TEST_GROUP(WavReader) {
};

TEST(WavReader, HasExtension) {
   string s{"a.bcd"};
   CHECK(!hasExtension(s, "xxxx"));
   CHECK(hasExtension(s, "bcd"));
   string bigger{"aaabcd"};
   CHECK(!hasExtension(s, bigger));
}

// START:test
TEST_GROUP(WavReader_WriteSamples) 
{
   WavReader reader{"",""};
   ostringstream out;
};

void writeSamples(ostream* out, char* data, 
// END_HIGHLIGHT
      uint32_t startingSample, 
      uint32_t samplesToWrite, 
      uint32_t bytesPerSample) {
//   rLog(channel, "writing %i samples", samplesToWrite);

   for (auto sample = startingSample; 
        sample < startingSample + samplesToWrite; 
        sample++) {
      auto byteOffsetForSample = sample * bytesPerSample;
      for (uint32_t byte{0}; byte < bytesPerSample; byte++) 
// START_HIGHLIGHT
         out->put(data[byteOffsetForSample + byte]);
// END_HIGHLIGHT
   }
}

TEST(WavReader_WriteSamples, WritesSingleSample) {
   char data[] { "abcd" };
   uint32_t bytesPerSample { 1 };
   uint32_t startingSample { 0 };
   uint32_t samplesToWrite { 1 };

   /* reader.*/writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

   CHECK_EQUAL("a", out.str());
}

TEST(WavReader_WriteSamples, WritesMultibyteSampleFromMiddle) {
   char data[] { "0123456789ABCDEFG" };
   uint32_t bytesPerSample { 2 };
   uint32_t startingSample { 4 };
   uint32_t samplesToWrite { 3 };

   /*reader.*/writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

   CHECK_EQUAL("89ABCD", out.str());
}
// END:test

