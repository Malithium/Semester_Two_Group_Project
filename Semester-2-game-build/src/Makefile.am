EXTRA_DIST = level.h camera.h gameAssetManager.h gameAsset.h events.h diamondAsset.h largeCubeAsset.h medCubeAsset.h smallCubeAsset.h boundingBox.h
 
bin_PROGRAMS = shaderexample
shaderexample_SOURCES = main.cpp level.cpp camera.cpp gameAssetManager.cpp events.cpp diamondAsset.cpp largeCubeAsset.cpp  medCubeAsset.cpp  smallCubeAsset.cpp boundingBox.cpp

AM_CPPFLAGS = -DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES
AM_CPPFLAGS += -std=c++11
AM_CPPFLAGS += $(gl_CFLAGS) $(glew_CFLAGS) $(sdl2_CFLAGS) $(BOOST_CPPFLAGS)
LIBS += $(gl_LIBS) $(glew_LIBS) $(sdl2_LIBS) $(BOOST_THREAD_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS)
