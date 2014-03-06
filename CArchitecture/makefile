Architecture:main.o Architecture.o CMgrJob.o CThread.o CLock.o\
	CHypergraph.o Multilevel.o TestCase.o ReadCpp.o ReadH.o HeapSort.o CLog.o
	g++ main.o Architecture.o CMgrJob.o CThread.o CLock.o\
		CHypergraph.o Multilevel.o TestCase.o ReadCpp.o ReadH.o HeapSort.o CLog.o\
		-o Architecture ./libhmetis.a -lpthread
main.o:main.cpp Architecture.h
	g++ -c main.cpp -o main.o
Architecture.o:Architecture.cpp Architecture.h TestCase.h CMgrJob.h CLog.h
	g++ -c Architecture.cpp -o Architecture.o
CMgrJob.o:CMgrJob.cpp CMgrJob.h CLock.h CThread.h TestCase.h define.h
	g++ -c CMgrJob.cpp -o CMgrJob.o
CThread.o:CThread.cpp CThread.h
	g++ -c CThread.cpp -o CThread.o -lpthread
CLock.o:CLock.cpp CLock.h
	g++ -c CLock.cpp -o CLock.o
CLog.o:CLog.cpp CLog.h
	g++ -c CLog.cpp -o CLog.o
CHypergraph.o:CHypergraph.cpp CHypergraph.h
	g++ -c CHypergraph.cpp -o CHypergraph.o
Multilevel.o:Multilevel.cpp Multilevel.h CHypergraph.h hmetis.h HeapSort.h
	g++ -c Multilevel.cpp -o Multilevel.o
TestCase.o:TestCase.cpp TestCase.h CHypergraph.h define.h Multilevel.h ReadCpp.h ReadH.h CLog.h
	g++ -c TestCase.cpp -o TestCase.o
ReadCpp.o:ReadCpp.cpp ReadCpp.h
	g++ -c ReadCpp.cpp -o ReadCpp.o
ReadH.o:ReadH.cpp ReadH.h
	g++ -c ReadH.cpp -o ReadH.o
HeapSort.o:HeapSort.cpp HeapSort.h
	g++ -c HeapSort.cpp -o HeapSort.o
clean:
	rm -rf *.o Architecture
