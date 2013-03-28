#include "CppUTest/TestHarness.h"

#include <fstream>
#include <istream>
#include <stdio.h>

#include "FileUtil.h"
#include "StreamUtil.h"

using namespace std;

class FileUtilTests: public Utest  {
protected:
   const string TempFileName{"FileUtil_SizeTest.dat"};
   FileUtil util;

   void teardown() {
      remove(TempFileName.c_str());
   }

   void createTempFile(const std::string& content) {
      ofstream stream{TempFileName, ios::out | ios::binary};
      stream << content << endl;
      stream.close();
   }
};

// START:tests
// slow tests that must interact with the filesystem
TEST_GROUP_BASE(FileUtil_Size, FileUtilTests) {
};

TEST(FileUtil_Size, AnswersFileContentSize) {
   string content("12345");
   createTempFile(content);

   size_t expectedSize { content.length() + sizeof('\0') };
   CHECK_EQUAL(expectedSize, (unsigned)util.size(TempFileName));
}
// END:tests

TEST_GROUP_BASE(FileUtil_Execute, FileUtilTests) {
};

TEST(FileUtil_Execute, IsPassedStreamFromFile) {
   string content("abcdefg");
   streamsize returnValue{999};
   createTempFile(content);
   string buffer;

   auto func = [&](istream& stream) { 
      getline(stream, buffer);
      return returnValue; 
   };
   auto result = util.execute(TempFileName, func);

   CHECK_EQUAL(returnValue, result);
   CHECK_EQUAL(content, buffer);
}

TEST(FileUtil_Execute, DemonstratedWithStreamUtilSizeFunction) {
   string content("abcdefg");
   createTempFile(content);

// START:clientDemo
   streamsize size = util.execute(TempFileName, 
                  [&](istream& s) { return StreamUtil::size(s); });
// END:clientDemo

   CHECK_EQUAL(content.length() + sizeof('\0'), (unsigned)size);
}

