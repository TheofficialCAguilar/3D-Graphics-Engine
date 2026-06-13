# ─────────────────────────────────────────────
#  3D Graphics Engine — Makefile (OpenGL + SDL2)
#  Carlos Aguilar
# ─────────────────────────────────────────────

CXX      = g++
CXXFLAGS = -std=c++17 -Wall \
           -I/opt/homebrew/include \
           -I/opt/homebrew/opt/glew/include \
           -I/opt/homebrew/opt/sdl2/include/SDL2

LDFLAGS  = -L/opt/homebrew/lib \
           -L/opt/homebrew/opt/glew/lib \
           -L/opt/homebrew/opt/sdl2/lib

LIBS     = -lSDL2 \
           -lGLEW \
           -framework OpenGL

TARGET = engine

SRCS =  Engine.cpp \
        Shader.cpp \
        Camera.cpp \
        Mesh.cpp \
        Vector3D.cpp \
        Rotation.cpp \
        EulerRotation.cpp \
        AxisAngleRotation.cpp \
        QuaternionRotation.cpp \
        RotationRegistry.cpp \
        Translation.cpp \
        Scale.cpp \
        TransformPipeline.cpp \
        SpatialNode.cpp \
        SpatialRegistry.cpp \
        Renderer.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) render.ppm

rebuild: clean all


