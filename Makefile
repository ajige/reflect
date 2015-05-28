SOURCE:=$(wildcard *.cpp) \
		 $(wildcard src/*.cpp)

OBJS:=$(patsubst %.cpp, %.o, $(SOURCE))

INCLUDE=-Isrc/

LIBRARY=libreflect.a

all:$(LIBRARY) testmain

$(LIBRARY):$(OBJS)
#	echo $(SOURCE)
#	echo $(OBJS)
	rm -f $@
	ar -rs $@ $(OBJS)

testmain: test/main.o
	g++ -g test/main.o $(LIBRARY) -o $@

.c.o:
	gcc -g -c $< -o $@

.cpp.o:
	g++ -g -c $< -o $@ $(INCLUDE)

clean:
	rm -f $(OBJS) $(LIBRARY) testmain
