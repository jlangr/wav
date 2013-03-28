#include "WavReader.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
   cout << "argc = " << argc << endl;
   if (argc != 3) {
      cout << "USAGE:" << endl <<
         "\tSnippetPublisher [sourceDir] [destDir]" << endl;
      return 1;
   }

   auto source = argv[1];
   auto dest = argv[2];  

   WavReader reader(source, dest);
   reader.publishSnippets();
}

