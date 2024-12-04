#include <iostream>
#include <vector>

namespace vectorized_std
{
    template <typename T>
    std::vector<T> move(std::vector<T> arg)
    {
        std::vector<T> output; 
        for (T value: arg){
            output.push_back(std::move(value));
        }
        return output;
    };
};





