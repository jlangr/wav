#include "rlog/rlog.h"

//#define CONCAT2(A,B) A##B
//#define CONCAT(A,B) CONCAT2(A,B)
//#define STR(X) #X

#include <rlog/common.h>


// may be useful for checking from configuration files
#define CURRENT_RLOG_VERSION 20040503
extern "C" int RLogVersion();

namespace rlog
{

    class RLogChannel;
    class RLogPublisher;
    class RLogNode;


    void RLOG_DECL RLogInit(int &argc, char **argv) {}

    RLOG_DECL RLogChannel *GetComponentChannel(const char *component, 
	                             const char *path, LogLevel level ) {}

    RLOG_DECL RLogChannel *GetGlobalChannel( const char *path,
				   LogLevel level) {}

#define DEF_CHANNEL(path,level) RLOG_CHANNEL_IMPL(RLOG_COMPONENT, path, level)
#define RLOG_CHANNEL(path) RLOG_CHANNEL_IMPL(RLOG_COMPONENT, path, rlog::Log_Undef)
#define RLOG_CHANNEL_IMPL(COMPONENT,path,level) rlog::GetComponentChannel(STR(COMPONENT),path,level)

    extern RLOG_DECL RLogChannel *_RLDebugChannel;
    extern RLOG_DECL RLogChannel *_RLInfoChannel;
    extern RLOG_DECL RLogChannel *_RLWarningChannel;
    extern RLOG_DECL RLogChannel *_RLErrorChannel;

//	void (*publish)(PublishLoc *, RLogChannel *, const char *format, ... )
//	    PRINTF_FP(3,4);


   PublishLoc::~PublishLoc() {}

    void RLOG_DECL RLog_Register(PublishLoc *loc, RLogChannel *, 
	               const char *format, ... ) {} // PRINTF(3,4);
//
//    void RLOG_DECL rAssertFailed( const char *component, const char *file, 
//	                const char *function, int line, 
//	                const char *conditionStr );

#if !HAVE_PRINTF_FP && HAVE_PRINTF_ATTR
    void __checkArgs(int, const char *, ... ) PRINTF(2,3);

    inline void __checkArgs(int, const char *, ...)
    { }
#endif
}

#if C99_VARIADAC_MACROS
#include <rlog/rlog-c99.h>
#elif PREC99_VARIADAC_MACROS
#include <rlog/rlog-prec99.h>
#else
#include <rlog/rlog-novariadic.h>
#endif

