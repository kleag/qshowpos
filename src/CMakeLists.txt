
########### next target ###############

SET(qshowpos_SRCS
           main.cpp
           qshowpos.cpp
           qshowposWidget.cpp
           QRecentFilesMenu.cpp)

set (qshowpos_MOC_HEADERS qshowpos.h
           qshowposWidget.h QRecentFilesMenu.h)
qt5_wrap_cpp (qshowpos_MOC_OUTFILES ${qshowpos_MOC_HEADERS})

qt5_add_resources(qshowpos_QRCS qshowpos.qrc)

add_executable(qshowpos ${qshowpos_SRCS} ${qshowpos_QRCS} ${qshowpos_MOC_OUTFILES})

target_link_libraries(qshowpos ${QT_LIBRARIES})


########### install files ###############
install(TARGETS qshowpos DESTINATION bin)
