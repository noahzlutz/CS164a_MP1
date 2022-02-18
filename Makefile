CXX=g++

CXXFLAGS = -std=c++11

BINARIES=NaiveBayesClassifier

all: ${BINARIES}

NaiveBayesClassifier: naivebayes.o naivebayesclassifier.o
	${CXX} $^ -o $@

clean:
	/bin/rm -f ${BINARIES} *.o