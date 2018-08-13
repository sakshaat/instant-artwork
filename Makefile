CXX=g++
CFLAGS=`pkg-config --cflags --libs opencv`

instant_artwork: instant_artwork.o
	$(CXX) $(CFLAGS) -o instant_artwork instant_artwork.cpp 
