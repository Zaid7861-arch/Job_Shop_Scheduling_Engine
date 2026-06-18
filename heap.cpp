#pragma once // 
#include <vector>
#include <functional>
#include<stdexcept>
#include<utility>

template <typename T>
class Heap {
private:
    // You can add your private member variables and helper functions here
    std::vector<T> data;
    std::function<bool(const T&, const T&)> compare;
    void heapify(int currentid){
        int targetindex = currentid;
        int leftchild = 2*currentid+1;
        int rightchild = 2*currentid+2;
        int n = data.size();
        if(leftchild<n && compare(data[leftchild],data[currentid])){
            targetindex = leftchild;
        }
         if(rightchild<n && compare(data[rightchild],data[targetindex])){
            targetindex = rightchild;
        }
       if(targetindex!=currentid){
          std::swap(data[currentid],data[targetindex]);
          heapify(targetindex);
       }
    }
    void shift_up(int idx){
        while(idx > 0){
            int parent_idx = (idx-1)/2;
            if(compare(data[idx],data[parent_idx])){
                std::swap(data[idx],data[parent_idx]);
                idx = parent_idx;
            }
            else{
                break;
            }
        }
    }
public:
    /**
     * Arguments:
     * comparison_function : std::function<bool(const T&, const T&)> : A function that takes in two arguments and returns a boolean value
     * init_array : std::vector<T> : The initial array to be inserted into the heap
     * Returns:
     * None
     * Description:
     * Initializes a heap with a comparison function
     * Details of Comparison Function:
     * The comparison function should take in two arguments and return a boolean value
     * If the comparison function returns true, it means that the first argument is to be considered smaller than the second argument
     * If the comparison function returns false, it means that the first argument is to be considered greater than or equal to the second argument
     * Time Complexity:
     * O(n) where n is the number of elements in init_array
     */
    Heap(std::function<bool(const T&, const T&)> comparison_function, const std::vector<T>& init_array) {
        // Write your code here
        compare = comparison_function;
        data = init_array;
        int n = data.size();
        for(int i =(n/2)-1 ; i>=0;i--){
            heapify(i);
        }
    }

    /**
     * Arguments:
     * value : const T& : The value to be inserted into the heap
     * Returns:
     * None
     * Description:
     * Inserts a value into the heap
     * Time Complexity:
     * O(log(n)) where n is the number of elements currently in the heap
     */
    void insert(const T& value) {
        // Write your code here
        data.push_back(value);
        int idx = data.size()-1;
        shift_up(idx);
    }
    bool is_empty() const {
        return data.empty();
    }

    /**
     * Arguments:
     * None
     * Returns:
     * T : The value extracted from the top of heap
     * Description:
     * Extracts the value from the top of heap, i.e. removes it from heap
     * Time Complexity:
     * O(log(n)) where n is the number of elements currently in the heap
     */
    T extract() {
        // Write your code here
        if(data.empty()){
            throw std::out_of_range("Heap is empty");
        }
        int n = data.size();
        T value = data[0];
        data[0] = data[n-1];
        data.pop_back();
        if(!data.empty()){
        heapify(0);
        }
        return value; // Placeholder return
    }

    /**
     * Arguments:
     * None
     * Returns:
     * T : The value at the top of heap
     * Description:
     * Returns the value at the top of heap
     * Time Complexity:
     * O(1)
     */
    T top() const {
        // Write your code here
        if(data.empty()){
            throw std::out_of_range("Heap is empty");
        }
        return data[0];
    }
};