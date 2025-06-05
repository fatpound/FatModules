#pragma once

#if IN_DEBUG
    #define FAT_WNDSTYLE_EX WS_CAPTION bitor WS_MINIMIZEBOX bitor WS_OVERLAPPED bitor WS_SYSMENU
#else
    #define FAT_WNDSTYLE_EX WS_POPUP
#endif
