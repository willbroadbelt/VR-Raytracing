#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/camera.o \
	${OBJECTDIR}/canvas.o \
	${OBJECTDIR}/display.o \
	${OBJECTDIR}/framebuffer.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/mesh.o \
	${OBJECTDIR}/obj_loader.o \
	${OBJECTDIR}/shader.o \
	${OBJECTDIR}/shaderloader.o \
	${OBJECTDIR}/stb_image.o \
	${OBJECTDIR}/texture.o \
	${OBJECTDIR}/transform.o \
	${OBJECTDIR}/vrsystem.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/Cellar/glew/2.1.0/lib -L/usr/local/Cellar/sdl2/2.0.7/lib -L/usr/local/Cellar/glm/0.9.8.5/lib -L/System/Library/Frameworks/OpenGL.framework/Libraries -L../openvr-master/bin/osx64 -lGL -lGLEW -lSDL2

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vr_raytracing

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vr_raytracing: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/vr_raytracing ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/camera.o: camera.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/camera.o camera.cpp

${OBJECTDIR}/canvas.o: canvas.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/canvas.o canvas.cpp

${OBJECTDIR}/display.o: display.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/display.o display.cpp

${OBJECTDIR}/framebuffer.o: framebuffer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/framebuffer.o framebuffer.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/mesh.o: mesh.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mesh.o mesh.cpp

${OBJECTDIR}/obj_loader.o: obj_loader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/obj_loader.o obj_loader.cpp

${OBJECTDIR}/shader.o: shader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/shader.o shader.cpp

${OBJECTDIR}/shaderloader.o: shaderloader.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/shaderloader.o shaderloader.cpp

${OBJECTDIR}/stb_image.o: stb_image.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/stb_image.o stb_image.c

${OBJECTDIR}/texture.o: texture.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/texture.o texture.cpp

${OBJECTDIR}/transform.o: transform.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/transform.o transform.cpp

${OBJECTDIR}/vrsystem.o: vrsystem.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I/usr/local/Cellar/sdl2/2.0.7/include/SDL2 -I/usr/local/Cellar/glew/2.1.0/include -I/usr/local/Cellar/glm/0.9.8.5/include/glm -I../openvr-master/bin/osx64/OpenVR.framework/Headers -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrsystem.o vrsystem.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
