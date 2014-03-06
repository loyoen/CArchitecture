Architecture:main.o Architecture.o CMgrJob.o CThread.o CLock.o\
	Hypergraph.o Simplex.o TestCase.o TestFile.o
	g++ main.o Architecture.o CMgrJob.o CThread.o CLock.o\
		Hypergraph.o Simplex.o TestCase.o TestFile.o\
		-o Architecture -lpthread
main.o:main.cpp Architecture.h
	g++ -c main.cpp -o main.o
Architecture.o:Architecture.cpp Architecture.h TestCase.h CMgrJob.h
	g++ -c Architecture.cpp -o Architecture.o
CMgrJob.o:CMgrJob.cpp CMgrJob.h CLock.h CThread.h TestCase.h define.h
	g++ -c CMgrJob.cpp -o CMgrJob.o
CThread.o:CThread.cpp CThread.h
	g++ -c CThread.cpp -o CThread.o -lpthread
CLock.o:CLock.cpp CLock.h
	g++ -c CLock.cpp -o CLock.o
Hypergraph.o:Hypergraph.cpp Hypergraph.h Simplex.h
	g++ -c Hypergraph.cpp -o Hypergraph.o
Simplex.o:Simplex.cpp Simplex.h define.h
	g++ -c Simplex.cpp -o Simplex.o
TestCase.o:TestCase.cpp TestCase.h TestFile.h define.h Hypergraph.h
	g++ -c TestCase.cpp -o TestCase.o
TestFile.o:TestFile.cpp TestFile.h Simplex.h define.h
	g++ -c TestFile.cpp -o TestFile.o
clean:
	rm -rf *.o Architecture
