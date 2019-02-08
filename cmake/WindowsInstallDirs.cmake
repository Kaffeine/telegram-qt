# GNUInstallDirs analog for Windows

if (WIN32)
    # define install prefix
    if (NOT DEFINED CMAKE_INSTALL_PREFIX)
        if (${CMAKE_SYSTEM_PROCESSOR} STREQUAL "AMD64")
            set(CMAKE_INSTALL_PREFIX "C:/Program Files/TelegramQt")
        else()
            set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/TelegramQt")
        endif()
    endif()

    set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")
    set(CMAKE_INSTALL_SBINDIR "${CMAKE_INSTALL_PREFIX}/sbin")
    set(CMAKE_INSTALL_LIBEXECDIR "${CMAKE_INSTALL_PREFIX}/libexec")
    set(CMAKE_INSTALL_SYSCONFDIR "${CMAKE_INSTALL_PREFIX}/etc")
    set(CMAKE_INSTALL_SHAREDSTATEDIR "${CMAKE_INSTALL_PREFIX}/com")
    set(CMAKE_INSTALL_LOCALSTATEDIR "${CMAKE_INSTALL_PREFIX}/var")
    
    set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")
    set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
    set(CMAKE_INSTALL_DATAROOTDIR "${CMAKE_INSTALL_PREFIX}/share")
    
    set(CMAKE_INSTALL_INFODIR "${CMAKE_INSTALL_PREFIX}/info")
    set(CMAKE_INSTALL_MANDIR "${CMAKE_INSTALL_PREFIX}/man")
endif()
