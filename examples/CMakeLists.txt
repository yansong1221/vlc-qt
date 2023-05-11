find_package(Qt5 COMPONENTS Widgets Sql DBus REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(COMMON_SRC
  common/common.cpp
  common/Config.cpp
  common/qoptions.cpp
  common/powermanagement/powermanagement.cpp
  common/powermanagement/powermanagement_x11.cpp
)
set(COMMON_HEADERS
  common/common.h
  common/Config.h
  common/qoptions.h
  common/powermanagement/powermanagement.h
  common/powermanagement/powermanagement_x11.h
  common/common_export.h
)
if(APPLE)
  message("apple")
  list(APPEND COMMON_LIBS "-framework CoreServices -framework IOKit")
endif()

SET(COMMON_QRC common/theme/theme.qrc)
SOURCE_GROUP("Resources" FILES ${COMMON_QRC})
qt5_add_resources(COMMON_RES ${COMMON_QRC})
set_source_files_properties(${COMMON_RES} PROPERTIES GENERATED ON)

# add HEADERS for moc
add_library(common STATIC ${COMMON_SRC} ${COMMON_RES} ${COMMON_HEADERS})
target_link_libraries(common
  PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets
  PUBLIC Qt5::Sql Qt5::DBus ${COMMON_LIBS}
)
target_compile_definitions(common PUBLIC -DBUILD_COMMON_STATIC)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set(PLAYER_SRC
    player/main.cpp
    player/MainWindow.cpp
    player/ClickableMenu.cpp
    player/StatisticsView.cpp
    player/Slider.cpp
    player/TVView.cpp
    player/EventFilter.cpp
    player/config/ConfigDialog.cpp
    player/config/ConfigPageBase.cpp
    player/config/CaptureConfigPage.cpp
    player/config/VideoEQConfigPage.cpp
    player/config/DecoderConfigPage.cpp
    player/config/MiscPage.cpp
    player/playlist/PlayListModel.cpp
    player/playlist/PlayListItem.cpp
    player/playlist/PlayListDelegate.cpp
    player/playlist/PlayList.cpp
    player/config/PropertyEditor.cpp
    player/config/AVFormatConfigPage.cpp
    player/config/AVFilterConfigPage.cpp
    player/config/ShaderPage.cpp
)
set(PLAYER_HEADERS
    player/MainWindow.h
    player/ClickableMenu.h
    player/StatisticsView.h
    player/Slider.h
    player/TVView.h
    player/EventFilter.h
    player/config/ConfigDialog.h
    player/config/ConfigPageBase.h
    player/config/CaptureConfigPage.h
    player/config/VideoEQConfigPage.h
    player/config/DecoderConfigPage.h
    player/config/MiscPage.h
    player/playlist/PlayListModel.h
    player/playlist/PlayListItem.h
    player/playlist/PlayListDelegate.h
    player/playlist/PlayList.h
    player/config/PropertyEditor.h
    player/config/AVFormatConfigPage.h
    player/config/AVFilterConfigPage.h
    player/config/ShaderPage.h
)

SET(PLAYER_QRC player/res/player.qrc)
SOURCE_GROUP("Resources" FILES ${PLAYER_QRC})
qt5_add_resources(PLAYER_RES ${PLAYER_QRC})
set_source_files_properties(${PLAYER_RES} PROPERTIES GENERATED ON)

if(Qt5Widgets_FOUND)
  set(MODULE Player)
  add_executable(Player ${EXE_TYPE} ${PLAYER_SRC} ${PLAYER_HEADERS} ${PLAYER_RES})
  target_link_libraries(Player ${VLCQT_CORE} ${VLCQT_WIDGETS} common)
  target_include_directories(Player PRIVATE ${CMAKE_BINARY_DIR}/include)
endif()
