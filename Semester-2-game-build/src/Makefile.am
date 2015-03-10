EXTRA_DIST = loadShaders.h level.h camera.h cube.h gameAssetManager.h gameAsset.h

bin_PROGRAMS = shaderexample
shaderexample_SOURCES = main.cpp loadShaders.cpp level.cpp camera.cpp cube.cpp gameAssetManager.cpp

AM_CPPFLAGS = -DGL_GLEXT_PROTOTYPES -DGL3_PROTOTYPES
AM_CPPFLAGS += -std=c++11
AM_CPPFLAGS += $(gl_CFLAGS) $(glew_CFLAGS) $(sdl2_CFLAGS) $(BOOST_CPPFLAGS)
LIBS += $(gl_LIBS) $(glew_LIBS) $(sdl2_LIBS) $(BOOST_THREAD_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS)
