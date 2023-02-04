#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <math.h>

using namespace std;

// Finds the sum of a vector
double sum(vector<double> data){
    double sum;
    for (double num : data){
        sum += num;
    }
    return sum;
}

// Finds the mean of a vector,
// Also calls the sum function
double mean(vector<double> data){
    // Divides sum of data by num of observations
    return sum(data) / data.size();
}

// Finds the median of a vector,
// Also sorts the data automatically
double median(vector<double> data){
    // sorts data before finding median
    sort(data.begin(), data.end());

    // if num of observations is odd
    if (data.size() % 2 == 1){
        return data.at(data.size()/2);
    }

    // if num of observations is even
    else {
        return (data.at(data.size()/2) + data.at(data.size()/2 + 1)) / 2;
    }
}

// Finds the range of the vector
double range(vector<double> data){
    double low = data.at(0);
    double high = data.at(0);
    for (double num : data){
        if (num < low){
            low = num;
        }
        if (num > high){
            high = num;
        }
    }
    return high-low;
}

// Prints out the sum, mean, median, and range of a vector
void print_stats(vector<double> data){
    cout << "Sum: " << sum(data) << endl;
    cout << "Mean: " << mean(data) << endl;
    cout << "Median: " << median(data) << endl;
    cout << "Range: " << range(data) << endl;
    return;
}

// Finds the correlation of a data set
double cor(vector<double> x, vector<double> y){
    double numerator = 0;
    double denominator1 = 0;
    double denominator2 = 0;
    double xmean = mean(x);
    double ymean = mean(y);

    // Cycles through each observation to calculate the sigma values
    for (int i = 0; i < x.size(); i++){
        numerator += (x.at(i) - xmean) * (y.at(i) - ymean);
        denominator1 += pow((x.at(i) - xmean),2);
        denominator2 += pow((y.at(i) - ymean),2);
    }

    return numerator/sqrt(denominator1*denominator2);
}

// Finds the covariance of a data set
double covar(vector<double> x, vector<double> y){
    double numerator = 0;
    double xmean = mean(x);
    double ymean = mean(y);

    // Cycles through each observation to calculate the sigma values
    for (int i = 0; i < x.size(); i++){
        numerator += (x.at(i) - xmean)*(y.at(i) - ymean);
    }

    return numerator / (x.size() - 1);
}

int main(int argc, char** argv){

    ifstream inFS;  // Input file stream
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);

    // Try to open file
    cout << "Opening file Boston.csv." << endl;

    inFS.open("Boston.csv");
    if (!inFS.is_open()){
        cout << "Could not open file Boston.csv." << endl;
        return 1; // Returns error
    }
    
    // Can now use inFS stream like cin stream
    // Boston.csv should contain two doubles

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    // echo heading
    cout << "Heading: " << line << endl;

    int numObservations = 0;

    while(inFS.good()) {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "New length: " << rm.size() << endl;

    cout << "Closing file Boston.csv." << endl;
    inFS.close();

    cout << "Number of records: " << numObservations << endl;

    // Prints sum, mean, median, and range for rm and medv
    cout << "\nStats for rm:" << endl;
    print_stats(rm);
    cout << "\nStats for medv:" << endl;
    print_stats(medv);

    // Print covariance and correlation for rm and medv
    cout << "\n Covariance = " << covar(rm, medv) << endl;
    cout << "\n Correlation = " << cor(rm, medv) << endl;

    cout << "\nProgram terminated.";
    return 0;
}