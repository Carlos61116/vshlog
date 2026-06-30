#include "vshlog/Logger.h"
#include <format>
#include "../vshlog/include/vshlog/vshlog.h"

int main()
{
    VSH_INIT_DEV();
    VSH_LOG_INFO("Hola","ktal");

    for (size_t i = 0; i < 50; i++)
    {
            
        VSH_LOG_INFO("Hola", "ktal");
    }

    vsh::shutdown();
    return 0;
}