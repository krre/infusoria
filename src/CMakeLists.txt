configure_file(config.h.in config.h @ONLY)

add_library(common STATIC
    core/Application.cpp core/Application.h
    settings/FileSettings.cpp settings/FileSettings.h
    settings/Settings.cpp settings/Settings.h
    ui/MainWindow.cpp ui/MainWindow.h
    ui/dialog/NewOrganism.cpp ui/dialog/NewOrganism.h
    ui/dialog/StandardDialog.cpp ui/dialog/StandardDialog.h
    ui/widget/BrowseLayout.cpp ui/widget/BrowseLayout.h
    core/Utils.h core/Utils.cpp
    ui/dialog/Preferences.cpp ui/dialog/Preferences.h
)

# For visibility in IDE (e.g., Qt Creator)
add_custom_target(custom
    SOURCES
    config.h.in
)

target_link_libraries(common PUBLIC Qt6::Widgets )
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
