#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Snippet.h"
#include <sstream>

using namespace std;

class MockWavDescriptor : public WavDescriptor {
public:
   MockWavDescriptor(): WavDescriptor("") {}
   void add(
      const string&, const string&, 
      uint32_t totalSeconds, 
      uint32_t, uint32_t,
      uint32_t fileSize) override {
      mock().actualCall("add")
         .withParameter("totalSeconds", (int)totalSeconds)
         .withParameter("fileSize", (int)fileSize);
   }
};

class MockFileUtil: public FileUtil {
public:
   streamsize size(const string& name) override {
      return mock().actualCall("size").returnValue().getIntValue();
   }
};

TEST_GROUP(Snippet_WriteSamples) 
{
   shared_ptr<MockFileUtil> fileUtil{make_shared<MockFileUtil>()};
   shared_ptr<MockWavDescriptor> descriptor{new MockWavDescriptor};
   rlog::RLogChannel* channel {0};

   Snippet snippet{fileUtil, descriptor, "", channel};

   std::ostringstream out;
};

TEST(Snippet_WriteSamples, WritesSingleSample) {
   char data[] { "abcd" };
   uint32_t bytesPerSample { 1 };
   uint32_t startingSample { 0 };
   uint32_t samplesToWrite { 1 };

   snippet.writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

   CHECK_EQUAL("a", out.str());
}

TEST(Snippet_WriteSamples, WritesMultibyteSampleFromMiddle) {
   char data[] { "0123456789ABCDEFG" };
   uint32_t bytesPerSample { 2 };
   uint32_t startingSample { 4 };
   uint32_t samplesToWrite { 3 };

   snippet.writeSamples(&out, data, startingSample, samplesToWrite, bytesPerSample);

   CHECK_EQUAL("89ABCD", out.str());
}

TEST(Snippet_WriteSamples, IncorporatesChannelCount) {
   char data[] { "0123456789ABCDEFG" };
   uint32_t bytesPerSample { 2 };
   uint32_t startingSample { 0 };
   uint32_t samplesToWrite { 2 };
   uint32_t channels { 2 };

   snippet.writeSamples(
         &out, data, startingSample, samplesToWrite, bytesPerSample, channels);

   CHECK_EQUAL("01234567", out.str());
}


TEST_GROUP(Snippet_DataLength) {
   shared_ptr<MockFileUtil> fileUtil{make_shared<MockFileUtil>()};
   shared_ptr<MockWavDescriptor> descriptor{new MockWavDescriptor};
   rlog::RLogChannel* channel {0};
   
   Snippet snippet{fileUtil, descriptor, "", channel};
};

TEST(Snippet_DataLength, IsProductOfChannels_BytesPerSample_and_Samples) {
   uint32_t bytesPerSample{ 2 };
   uint32_t samples { 5 };
   uint32_t channels { 4 };

   uint32_t length { snippet.dataLength(bytesPerSample, samples, channels) };

   CHECK_EQUAL(2 * 5 * 4, length);
}


TEST_GROUP(Snippet_Write) {
   shared_ptr<MockFileUtil> fileUtil{make_shared<MockFileUtil>()};
   shared_ptr<MockWavDescriptor> descriptor{new MockWavDescriptor};
   rlog::RLogChannel* channel {0};
   
   Snippet snippet{fileUtil, descriptor, "", channel};

   istringstream input{""};
   FormatSubchunk formatSubchunk;
   ostringstream output;
   DataChunk dataChunk;
   char* data;
   uint32_t TwoBytesWorthOfBits{2 * 8};

   const int ArbitraryFileSize{5};

   void setup() override {
      data = new char[4];
   }

   void teardown() override {
      mock().clear();
      delete[] data;
   }
};

TEST(Snippet_Write, SendsFileLengthAndTotalSecondsToDescriptor) {
   dataChunk.length = 8;
   formatSubchunk.bitsPerSample = TwoBytesWorthOfBits;
   formatSubchunk.samplesPerSecond = 1;
   mock().expectOneCall("size").andReturnValue(ArbitraryFileSize);
   mock().expectOneCall("add")
      .withParameter("totalSeconds", 8 / 2 / 1)
      .withParameter("fileSize", ArbitraryFileSize);

   snippet.write("any", input, output, formatSubchunk, dataChunk, data);

   mock().checkExpectations();
}

