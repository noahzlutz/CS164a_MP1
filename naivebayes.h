#ifndef NAIVEBAYES_H
#define NAIVEBAYES_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class naiveBayes{

    public:

        naiveBayes();

        void fit(string trainingData);
        void predict(string predict_data);

    private:

        vector<vector<double>> features; //vector of vectors of features

        double find_means(vector<double> feature);
        double find_variance(vector<double> feature, double mean);

        double conditional_prob(double val, int classifier, int feature);

        void split_into_classes();

        int total_ones;
        int total_zeros;
        int total_dataPoints;

        double prob_of_one;
        double prob_of_zero;

        vector<double> means;
        vector<double> variance;

        vector <double> class0[11];
        vector <double> class1[11];
        //vector<vector<double>> class0;
        //vector<vector<double>> class1;

        vector<double> means0;
        vector<double> variance0;

        vector<double> means1;
        vector<double> variance1;

        


};

#endif


