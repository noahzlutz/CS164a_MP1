#include "naivebayes.h"

#include <fstream>
#include <sstream>
#include <string>
#include <math.h>


naiveBayes::naiveBayes(){
    for(int i = 0 ; i < 12; i++){
        vector<double> feature;
        features.push_back(feature);
    }

    total_ones = 0;
    total_zeros = 0;
    total_dataPoints = 0;

    prob_of_one = 0.0;
    prob_of_zero = 0.0;
}

double naiveBayes::find_means(vector<double> feature){

    double sum = 0.0;
    for(auto it = begin(feature); it != end(feature); ++it) {
        sum += *it;
    }

    double size = feature.size();

    return sum/size;
}

double naiveBayes::find_variance(vector<double> feature, double mean){

    double summation = 0.0;
    for(auto it = begin(feature); it != end(feature); ++it) {
        summation += pow((*it - mean), 2.0);
    }
    
    double n = feature.size();

    return summation/n;

}

void naiveBayes::split_into_classes(){
    int j = 0;
    for(auto it = begin(features.back()); it != end(features.back()); ++it){
        //cout<< *it;
        if(*it == 0.0){
            for(int i = 0; i < 11; i++){
                class0[i].push_back(features[i][j]);
            }

            total_zeros ++;
        }else{
            for(int i = 0; i < 11; i++){
                class1[i].push_back(features[i][j]);
            }
            total_ones ++;
        }
        total_dataPoints ++;
        j++;
    }

}



void naiveBayes::fit(string trainingData){


    //get data into vectors
    ifstream trainfile;
    trainfile.open(trainingData);

    string line;
    while(getline(trainfile, line)){
        
        stringstream s(line);

        string data;

        int i = 0;
        while(getline(s,data,',')){
            
            if(i == 1){ //gender
                if(data == "M"){
                    features[i].push_back(1.0);
                }else{
                    features[i].push_back(0.0);
                }
            }else{
                features[i].push_back(stod(data));
            }
            /*
            if(data == "M"){ //gender 
                person.push_back(1.0);
            
            }else if(data == "F"){
                person.push_back(0.0);

            }else{
                person.push_back(stod(data));
            
            }*/
            i++;
        }
    }



    //split into class 0 and 1
    
    split_into_classes();
    /*int j = 0;
    for(auto it = begin(features.back()); it != end(features.back()); ++it){
        if(*it == 0.0){
            int k = 0;
            for(auto jt = begin(features); jt != end(features); ++jt){
                class0[k].push_back((*jt)[j]);
                k++;
            }
        }else{
            int k = 0;
            for(auto jt = begin(features); jt != end(features); ++jt){
                class1[k].push_back((*jt)[j]);
                k++;
            }
        }
        j++;
    }*/
    
    //find means
    for(auto it = begin(class0); it != end(class0); ++it) {
        means0.push_back(find_means(*it));
    }

    for(auto it = begin(class1); it != end(class1); ++it) {
        means1.push_back(find_means(*it));
    }


    //find standard deviations
    for(int i = 0; i < 12; i++){
        variance0.push_back(find_variance(class0[i],means0[i]));
    }

    for(int i = 0; i < 12; i++){
       variance1.push_back(find_variance(class1[i],means1[i]));
    }

    //cout<< "Total data points: " << total_dataPoints <<endl;
    //cout<< "Total 1's: " << total_ones << " and that over total = " << (double)total_ones/(double)total_dataPoints << endl;
    //cout<< "Total 0's: " << total_zeros << " and that over total = " << (double)total_zeros/(double)total_dataPoints << endl;

    prob_of_one = (double)total_ones/(double)total_dataPoints;
    prob_of_zero = (double)total_zeros/(double)total_dataPoints;

}

double naiveBayes::conditional_prob(double val, int classifier, int feature){
    if(classifier == 0){

        double exponenet = (-1.0 * pow((val - means0[feature]),2)) / (2* variance0[feature]);
        double A = 1/sqrt(2* M_PI * variance0[feature]);

        return A * exp(exponenet);

    }else{

        double exponenet = (-1.0 * pow((val - means1[feature]),2)) / (2 * variance1[feature]);
        double A = 1/sqrt(2* M_PI * variance1[feature]);

        return A * exp(exponenet);
    }


}


//todo
void naiveBayes::predict(string predict_data){

    ifstream trainfile;
    trainfile.open(predict_data);

    string line;

    while(getline(trainfile, line)){

        stringstream s(line);

        string data;

        double probclass1 = prob_of_one;
        double probclass0 = prob_of_zero;

        int i = 0;

        while(getline(s,data,',')){
            
            double val;
            

            //if(i == 1) cout << "This is gender:";

            //cout << conditional_prob(val, 0, i) <<endl;

            if(i < 11){
                if(data == "M"){
                    val = 1.0;
                }else if(data == "F"){
                    val = 0.0;
                }else{
                    val = stod(data);
                }

                probclass0 = probclass0 * conditional_prob(val, 0, i);
                //cout << "Conditional0 prob of "<< i << ":  " << conditional_prob(val, 0, i) <<endl;
                probclass1 = probclass1 * conditional_prob(val, 1, i);

                
            }
            
            i++;
        
        }

        //cout << "  Prob0: " << probclass0 <<"   Prob1: " << probclass1;

        if(probclass0 > probclass1){
            cout<< 0 << endl;
            
        }else{
            cout<< 1 << endl;
            
        }

        
    }

}