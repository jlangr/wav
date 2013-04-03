#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "WavReader.h"
#include <string>

TEST_GROUP(WavReader) {
};

TEST(WavReader, HasExtension) {
   std::string s{"a.bcd"};
   CHECK(!hasExtension(s, "xxxx"));
   CHECK(hasExtension(s, "bcd"));

   std::string bigger{"aaabcd"};
   CHECK(!hasExtension(s, bigger));
}

