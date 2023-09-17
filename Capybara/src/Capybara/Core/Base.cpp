#include "precomp.h"
#include "Base.h"

#include "Log.h"

#define CAPYBARA_BUILD_ID "v0.1a"

namespace Capybara {

    void InitializeCore()
    {
        Capybara::Log::Init();

        CPBR_CORE_TRACE("Capybara Engine {}", CAPYBARA_BUILD_ID);
        CPBR_CORE_TRACE("Initializing...");
    }

    void ShutdownCore()
    {
        CPBR_CORE_TRACE("Shutting down...");
    }

}