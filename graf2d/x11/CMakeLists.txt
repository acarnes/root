############################################################################
# CMakeLists.txt file for building ROOT graf2d/x11 package
# @author Pere Mato, CERN
############################################################################
set(libname GX11)

include_directories(${X11_INCLUDE_DIR})

ROOT_GENERATE_DICTIONARY(G__${libname} T*.h MODULE ${libname} LINKDEF LinkDef.h OPTIONS "-writeEmptyRootPCM")

ROOT_LINKER_LIBRARY(${libname} *.cxx  *.c G__${libname}.cxx LIBRARIES Core ${X11_LIBRARIES} ${X11_Xpm_LIB} ${CMAKE_THREAD_LIBS_INIT})

if(AIX)
  include_directories(AFTER ${CMAKE_CURRENT_SOURCE_DIR}/inc)
endif()

ROOT_INSTALL_HEADERS(FILTER "X11/" FILTER "X11$")
