# 编译器和参数
CXX := g++
CXXFLAGS := -std=c++17 -Wall -g

# SDL 和 OpenGL 库
LIBS := `sdl2-config --cflags --libs` -lGLEW -lGL -lglut

# 构建和执行
%.show:
	@echo "Building and running $*..."

	$(CXX) $(shell find $* -name "*.cpp") -o $*/out $(CXXFLAGS) $(LIBS)

	@cd $* && ./out


