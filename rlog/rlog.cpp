#include "rlog/rlog.h"
#include <rlog/common.h>

extern "C" int RLogVersion();

namespace rlog
{
    class RLogChannel;
    class RLogPublisher;
    class RLogNode;

    void RLOG_DECL RLogInit(int &argc, char **argv) {}

    RLOG_DECL RLogChannel *GetComponentChannel(const char *component, 
	                             const char *path, LogLevel level ) { return 0; }

    RLOG_DECL RLogChannel *GetGlobalChannel( const char *path,
				   LogLevel level) { return 0; }

    extern RLOG_DECL RLogChannel *_RLDebugChannel;
    extern RLOG_DECL RLogChannel *_RLInfoChannel;
    extern RLOG_DECL RLogChannel *_RLWarningChannel;
    extern RLOG_DECL RLogChannel *_RLErrorChannel;

   PublishLoc::~PublishLoc() {}

    void RLOG_DECL RLog_Register(PublishLoc *loc, RLogChannel *, 
	               const char *format, ... ) {} // PRINTF(3,4);

#if !HAVE_PRINTF_FP && HAVE_PRINTF_ATTR
    void __checkArgs(int, const char *, ... ) PRINTF(2,3);

    inline void __checkArgs(int, const char *, ...)
    { }
#endif
}

