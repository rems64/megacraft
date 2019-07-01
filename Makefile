#Programme : main.o RedgeScene.o Shader.o
#	g++ main.o RedgeScene.o Shader.o -o Programme -lGL -lGLU `sdl2-config --libs`
#main.o : main.cpp RedgeScene.cpp
#	g++ -c main.cpp -o main.o
#RedgeSceneScene.o : RedgeScene.cpp Shader.cpp
#	g++ -c RedgeScene.cpp -o RedgeScene.o  -lGL -lGLU `sdl2-config --cflags`
#Shader.o : Shader.cpp
#	g++ -c Shader.cpp -o Shader.o -lGL -lGLU `sdl2-config --cflags`

#main.o : main.cpp
#	g++ -c main.cpp -o main.o -lGL -lGLU `sdl2-config --libs` -I/glew-1.13.0/include
#megacraft : main.o
#	g++ main.o -o megacraft -lGL -lGLU `sdl2-config --libs`


#shaders.o : shader.cpp
#	g++ -c shader.cpp -o shaders.o -lGL -ldl -I/home/remy/Data/Documents/programmation/minecraft/megacraft/glew-1.13.0/include

shader.o : shader.cpp
	g++ -c shader.cpp -o shader.o -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl

texture.o : texture.cpp
	g++ -c texture.cpp -o texture.o -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl

controls.o : controls.cpp
	g++ -c controls.cpp -o controls.o -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl

objloader.o : objloader.cpp
	g++ -c objloader.cpp -o objloader.o -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl

vboindexer.o : vboindexer.cpp
	g++ -c vboindexer.cpp -o vboindexer.o -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl

main.o : main.cpp shader.cpp texture.cpp controls.cpp objloader.cpp vboindexer.cpp
	#g++ main.cpp -o test -lglfw3 -pthread -I/home/remy/Data/Documents/programmation/minecraft/megacraft/glew-1.13.0/include -lGLU -lGL -lrt -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -ldl
	#g++ main.cpp -o test -lglfw3 -pthread -I/home/remy/Data/Documents/programmation/minecraft/megacraft/glew-1.13.0/include -lGLU -lGL -lX11 -ldl -DGLEW_STATIC
	g++ main.cpp -o test -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl
	#g++ main.cpp -o test -lGL -lGLU -lglfw3 -lrt -lm -ldl -lXrandr -lXinerama -lXcursor -lXext -lXrender -lXfixes -lX11 -lpthread -lxcb -lXau -lXdmcp -I/home/remy/Data/Documents/programmation/minecraft/megacraft/glew-1.13.0/include -lGLU -lGL -lm -ldl -ldrm -lXdamage -lX11-xcb -lxcb-glx -lxcb-dri2 -lxcb-dri3 -lxcb-present -lxcb-sync -lxshmfence -lXxf86vm -lXfixes -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp

Programme : shader.o texture.o controls.o objloader.o vboindexer.o
	g++ main.cpp shader.o texture.o controls.o objloader.o vboindexer.o -o Programme -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl


test.o : test1.cpp
		#g++ test1.cpp -o test1 -lglfw3 -pthread -I/home/remy/Data/Documents/programmation/minecraft/megacraft/glew-1.13.0/include -lGLU -lGL -lX11 -ldl -DGLEW_STATIC
		#g++ test1.cpp -o test1 -lGL -lGLU -lglut -lglfw3 -pthread -Iglew-1.13.0/include -lGLU -lGL -lX11 -ldl -DGLEW_STATIC
		g++ `pkg-config --cflags glfw3` test1.cpp -o testglfw -lGL -lGLU -lglut `pkg-config --static --libs glfw3` -lGLEW

simpleCube : simpleCube.cpp texture.o shader.o
	#g++ simpleCube.cpp -o simpleCube -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl
	g++ simpleCube.cpp texture.o shader.o -o simpleCube -lglfw3 -lGL -lGLU -lglut -lGLEW -lpthread -lX11 -ldl
