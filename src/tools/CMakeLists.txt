target_sources(flameshot PRIVATE arrow/arrowtool.h arrow/arrowtool.cpp)
target_sources(flameshot PRIVATE pixelate/pixelatetool.h pixelate/pixelatetool.cpp)
target_sources(flameshot PRIVATE circle/circletool.h circle/circletool.cpp)
target_sources(flameshot PRIVATE circlecount/circlecounttool.h circlecount/circlecounttool.cpp)
target_sources(flameshot PRIVATE copy/copytool.h copy/copytool.cpp)
target_sources(flameshot PRIVATE exit/exittool.h exit/exittool.cpp)
target_sources(flameshot PRIVATE line/linetool.h line/linetool.cpp)
target_sources(flameshot PRIVATE pencil/penciltool.h pencil/penciltool.cpp)
target_sources(
  flameshot
  PRIVATE pin/pintool.h
          pin/pinwidget.h
          pin/pintool.cpp
          pin/pinwidget.cpp)
target_sources(flameshot PRIVATE rectangle/rectangletool.h rectangle/rectangletool.cpp)
target_sources(flameshot PRIVATE save/savetool.h save/savetool.cpp)
target_sources(flameshot PRIVATE accept/accepttool.h accept/accepttool.cpp)
target_sources(flameshot PRIVATE selection/selectiontool.h selection/selectiontool.cpp)
target_sources(
  flameshot
  PRIVATE text/texttool.h
          text/textwidget.h
          text/texttool.cpp
          text/textwidget.cpp)
target_sources(flameshot PRIVATE undo/undotool.h undo/undotool.cpp)

target_sources(
  flameshot
  PRIVATE abstractactiontool.cpp
          abstractpathtool.cpp
          abstracttwopointtool.cpp
          capturecontext.cpp
          toolfactory.cpp
          abstractactiontool.h
          abstractpathtool.h
          abstracttwopointtool.h
          capturetool.h
          toolfactory.h)
