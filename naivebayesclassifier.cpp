#include "naivebayes.h"



int main(int argc, char *argv[]) {

    naiveBayes classifier = naiveBayes();

    //cout<< "Starting to fit:" <<endl;

    classifier.fit(argv[1]);

    //cout<< "Has been fit" << endl;

    classifier.predict(argv[2]);


    return 0;

}