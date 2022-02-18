CXX=g++

CXXFLAGS = -std=c++11

BINARIES=naivebayes

all: ${BINARIES}

naivebayes: naivebayes.o naivebayesclassifier.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o