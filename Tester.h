#pragma once
    
#include <utility>
#include <valarray>

using namespace std;

template <typename T>
inline pair<double, double> mean_std(vector<T> vec) {
    valarray<T> x(vec.data(), vec.size());
    T s = x.sum();
    double mu = double(s) / double(vec.size());
    T q = (x * x).sum();
    double std = double(q) / double(vec.size()) - mu * mu;
    std = sqrt(std);
    return make_pair(mu, std);
}
