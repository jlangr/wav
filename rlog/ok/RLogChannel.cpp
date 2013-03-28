// steps:
//  add include of X.h
//  watch namespaces
//  for a const & return simply declare a global variable
//  remove class { };
//  remove virtual
//  add scoping


#include "rlog/RLogChannel.h"

#include <string>

#include <iostream>
//#include <map>
//
//#include <rlog/rlog.h>
//#include <rlog/RLogNode.h>

namespace rlog
{
//    class RLOG_DECL RLogPublisher;
//    class RLOG_DECL RLogChannel;
//    typedef std::map<std::string, RLogChannel*> ComponentMap;

    // documentation in implementation file
//    class RLOG_DECL RLogChannel : public RLogNode
//    {
   std::string nameReturn("");

   RLogChannel::RLogChannel( const std::string &name, LogLevel level ){
      std::cout << "creating a log channel" << std::endl;
   }

	RLogChannel::~RLogChannel(){}
	void RLogChannel::publish(const RLogData &data){}
	const std::string &RLogChannel::name() const { return nameReturn; }
	LogLevel RLogChannel::logLevel() const { return LogLevel(); }
	void RLogChannel::setLogLevel(LogLevel level) {}

	RLogChannel *getComponent(RLogChannel *componentParent, 
		                  const char *component){ return 0; }


//	RLogChannel( const RLogChannel & );
//	RLogChannel &operator = ( const RLogChannel & );
//    };

}

