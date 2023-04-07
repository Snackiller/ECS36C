#include <iostream>
#include "json.hpp"
#include <math.h>

#include "priorityqueue.h"
using json = nlohmann :: json; 

PriorityQueue::PriorityQueue(std::size_t max_size) :
	nodes_(1, KeyValuePair()),
	max_size_(max_size),
	size_(0) {
}

void PriorityQueue::insert(Key k) {
	insert(std::make_pair(k, std::make_pair(0, 0)));
}

void PriorityQueue::insert(KeyValuePair kv){
	// TODO: complete this function
    size_++;
    if(size_ <= max_size_){
        nodes_.push_back(kv);
        heapifyUp(nodes_.size() - 1);
    }
}


KeyValuePair PriorityQueue::min() {
	// TODO: complete this function
    return nodes_[ROOT];
}

KeyValuePair PriorityQueue::removeMin() {
	// TODO: complete this function
    if(!isEmpty()){
        removeNode(ROOT);
    }
    return nodes_[ROOT];
}

bool PriorityQueue::isEmpty() const {
	// TODO: complete this function
    if(size_ == 0){
        std :: cout << "bool is true, queue is empty" << std :: endl;
        return true;
    }
    else{
        return false;
    }
}

size_t PriorityQueue::size() const {
	// TODO: complete this function
    return nodes_.size() - 1;
}

json PriorityQueue::JSON() const {
  json result;
  for (size_t i = 1; i <= size_; i++) {
    json node;
    KeyValuePair kv = nodes_[i];
    node["key"] = kv.first;
    node["value"] = kv.second;
    if (i != ROOT) {
        node["parent"] = std::to_string(i / 2);
    }
    if (2 * i <= size_) {
        node["leftChild"] = std::to_string(2 * i);
    }
    if (2 * i + 1 <= size_) {
        node["rightChild"] = std::to_string(2 * i + 1);
    }
    result[std::to_string(i)] = node;
  }
  result["metadata"]["maxHeapSize"] = max_size_;
  result["metadata"]["max_size"] = max_size_;
  result["metadata"]["size"] = size_;
return result;
}

void PriorityQueue::heapifyUp(size_t i) {
	// TODO: complete this function
    if((i != 1) && (nodes_[i].first < nodes_[floor(i/2)].first)){   //Compare keys between parent and child
        KeyValuePair temp;
        temp = nodes_[i];
        nodes_[i] = nodes_[floor(i/2)];
        nodes_[floor((i/2))] = temp;
        i = floor(i/2);
        heapifyUp(i);
    }
}

void PriorityQueue::heapifyDown(size_t i) {
	// TODO: complete this function
    if(nodes_.size() == 3){
        Key smallest = nodes_[i].first;
        Key leftkey;
        if(i*2<nodes_.size()){
            leftkey = nodes_[i*2].first;
        }
        if(leftkey < smallest){
            smallest = leftkey;
        }
        if(smallest != nodes_[i].first){
            KeyValuePair temp;
            temp = nodes_[i];
            nodes_[i] = nodes_[i*2];
            nodes_[i*2] = temp;
        }
    }
    else if(nodes_.size() > 3){
        Key leftkey;
        if(i*2 < nodes_.size()){
            leftkey = nodes_[i*2].first;
        }
        Key rightkey; 
        if(i*2+1 < nodes_.size()){
            rightkey = nodes_[i*2 + 1].first;
        }
        Key smallest = nodes_[i].first;
        KeyValuePair child = nodes_[i];
        if(leftkey < smallest && ((i*2) < nodes_.size())){
            smallest = leftkey;
            child = nodes_[i*2];
        }
        if(rightkey < smallest && ((i*2+1) < nodes_.size())){
            smallest = rightkey;
            child = nodes_[i*2 + 1];
        }
        if((smallest != nodes_[i].first)){
            KeyValuePair temp;
            temp = nodes_[i];
            nodes_[i] = child;
            if(smallest == leftkey){
                nodes_[i*2] = temp;
                i = i * 2;
            }
            else if(smallest == rightkey){
                nodes_[i*2+1] = temp;
                i = i * 2 + 1;
            }
            heapifyDown(i);
        }
    }
}

void PriorityQueue::removeNode(size_t i) {
	// TODO: complete this function
    size_--;
    KeyValuePair last = nodes_[nodes_.size() - 1];
    if(nodes_[i] != last){
        KeyValuePair temp;
        temp = nodes_[i];
        nodes_[i] = last;
        last = temp;
        nodes_.pop_back();
        heapifyDown(i);
    }
    if(nodes_[i] == last){
        nodes_.pop_back();
    }
} 

Key PriorityQueue::getKey(size_t i) {
	// TODO: complete this function
    return nodes_[i].first;  
}

/*
Value PriorityQueue :: getvalue(size_t i){
    return nodes_[i].second;
}
*/