#include <fstream>

#include <zl_log.h>

#include "applogic.h"

#include <boost/filesystem/path.hpp>

#include "tracecategories.h"

using namespace boost::asio;

int main(int, char**){

#ifdef USING_PERFETTO_LIBRARY
    perfetto::TracingInitArgs args;
    args.backends |= perfetto::kInProcessBackend;
    args.backends |= perfetto::kSystemBackend;
    perfetto::Tracing::Initialize(args);
    perfetto::TrackEvent::Register();
#endif

    logInit("HMIC");

    AppLogic appLogic;

    appLogic.appRun();
}
