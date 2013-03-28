#include <rlog/StdioNode.h>

class RLogNode;
class RLogData;

using namespace std;

namespace rlog {
   StdioNode::StdioNode(int _fdOut, int flags)
       : RLogNode() {}
   StdioNode::StdioNode(int _fdOut, bool colorizeIfTTY)
       : RLogNode(), fdOut( _fdOut ) { }
   StdioNode::~StdioNode() { }
   void StdioNode::subscribeTo( RLogNode *node ) { }
   void StdioNode::publish( const RLogData &data ) { }
}
