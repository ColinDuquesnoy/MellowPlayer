SUBDIRLIST(subdirs ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${subdirs})
    install(DIRECTORY ${subdir} DESTINATION ${CMAKE_INSTALL_DATADIR}/mellowplayer/plugins)
endforeach()
