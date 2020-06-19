/**
 * Some sort algorithms.
 * Author: LiWentan.
 * First Modified Date: 2019/8/19. 
 */

#ifndef __WTTOOL_SORT_HPP_
#define __WTTOOL_SORT_HPP_

#include <vector>
#include <iostream>

#include "compare.hpp"
#include "systool.hpp"

namespace wttool {

using namespace std;

/**
 * Quick Sort for vector.
 * @param data: The vector need be sorted.
 * @param length: Sort the head N elements.
 * @param compare: The function to compare the elements.
 * @param e, s: The start and end position. Set 0 at the first recursive loop.
 */
template <typename T>
static int qsort(vector<T>* data,
                 int64_t length,
                 int (*compare)(const T& lhs, const T& rhs) = cmp<T>, 
                 int64_t s = 0,
                 int64_t e = 0) {
    if (length == 0 || length == 1) {
        return 0;
    }
    if (length == 2 && compare(data[s], data[e]) > 0) {
        std::swap(data[s], data[e]);
        return 0;
    }
    int64_t head = s;
    int64_t tail = e;
    if (s == 0 && e == 0) {
        // First call.
        s = head = 0;
        e = tail = length - 1;
    }
    T pivot = data[e];
    while (tail > head) {
        while (tail > head && compare(data[head], pivot) <= 0) {
            ++head;
        }
        if (tail > head) {
            data[tail] = data[head];
        }
        while (tail > head && compare(data[tail], pivot) >= 0) {
            --tail;
        }
        if (tail > head) {
            data[head] = data[tail];
        }
    }
    data[tail] = pivot;
    qsort(data, tail - s, compare, s, tail - 1);
    qsort(data, e - tail, compare, tail + 1, e);
    return 0;
}

/**
 * Quick Sort for array.
 * @param data: The array need be sorted.
 * @param length: Sort the head N elements, it should not be bigger than the array length.
 * @param compare: The function to compare the elements.
 * @param e, s: The start and end position. Set 0 at the first recursive loop.
 */
template <typename T>
static int qsort(T* data, 
                 int64_t length, 
                 int (*compare)(const T& lhs, const T& rhs) = cmp<T>, 
                 int64_t s = 0, 
                 int64_t e = 0) {
    if (length == 0 || length == 1) {
        return 0;
    }
    if (length == 2 && compare(data[s], data[e]) > 0) {
        std::swap(data[s], data[e]);
        return 0;
    }
    int64_t head = s;
    int64_t tail = e;
    if (s == 0 && e == 0) {
        // First call.
        s = head = 0;
        e = tail = length - 1;
    }
    T pivot = data[e];
    while (tail > head) {
        while (tail > head && compare(data[head], pivot) <= 0) {
            ++head;
        }
        if (tail > head) {
            data[tail] = data[head];
        }
        while (tail > head && compare(data[tail], pivot) >= 0) {
            --tail;
        }
        if (tail > head) {
            data[head] = data[tail];
        }
    }
    data[tail] = pivot;
    qsort(data, tail - s, compare, s, tail - 1);
    qsort(data, e - tail, compare, tail + 1, e);
    return 0;
}

/**
 * Insertion Sort.
 * @param data: The array need be sorted.
 * @param length: Sort the head N elements, it should not be bigger than the array length.
 * @param compare: The function to compare the elements.
 */
template <typename T>
static int isort(T* data, 
                 int64_t length,
                 int (*compare)(const T& lhs, const T& rhs) = cmp<T>) {
    if (length == 1 || length == 0) {
        return 0;
    }
    
    for (int64_t i = 1; i < length; ++i) {
        T cur_data = data[i];
        int64_t j = i - 1;
        for (; j >= 0; --j) {
            if (cmp(data[j], cur_data) > 0) {
                continue;
            }
            break;
        }
        // wtmemcpy(data + j + 2, data + j + 1, sizeof(T) * (i - j - 1));
        // For string, memcpy cannot work.
        // Thus here, we use "for loop" to finish array movement.
        for (int64_t k = i - 1; k >= j + 1; --k) {
            data[k + 1] = data[k];
        }
        data[j + 1] = cur_data;
    }
    return 0;
}

/**
 * The assist function for Shell Sort.
 * Do not use outside.
 */
template <typename T>
static void _ssort_once(T* data,
                        int64_t length,
                        int (*compare)(const T& lhs, const T& rhs),
                        int64_t begin,
                        int64_t gap) {
    if (length == 0 || length == 1) {
        return;
    }
    
    for (int64_t i = begin + gap; i < length; i = i + gap) {
        T cur_data = data[i];
        int64_t j = i - gap;
        for (; j >= 0 && data[j] > cur_data; j = j - gap) {
            data[j + gap] = data[j];
        }
        data[j + gap] = cur_data;
    }
}

/**
 * Shell Sort.
 * @param data: The array need be sorted.
 * @param length: Sort the head N elements, it should not be bigger than the array length.
 * @param compare: The function to compare the elements.
 */
template <typename T>
static int ssort(T* data, 
                 int64_t length,
                 int (*compare)(const T& lhs, const T& rhs) = cmp<T>) {
    if (length == 0 || length == 1) {
        return 0;
    } 
    int64_t gap = length / 2;
    while (gap > 0) {
        int64_t begin = gap - 1;
        while (begin >= 0) {
            _ssort_once(data, length, cmp, begin, gap);
            begin--;
        }
        gap /= 2;
    }
    return 0;
}

/**
 * Selection Sort.
 * @param data: The array need be sorted.
 * @param length: Sort the head N elements, it should not be bigger than the array length.
 * @param compare: The function to compare the elements.
 */
template <typename T>
static int sel_sort(T* data, 
                 int64_t length,
                 int (*compare)(const T& lhs, const T& rhs) = cmp<T>) {
    for (int64_t i = 0; i < length; ++i) {
        int64_t min_pos = i;
        for (int64_t j = i + 1; j < length; ++j) {
            if (compare(data[min_pos], data[j]) > 0) {
                min_pos = j;
            }
        }
        std::swap(data[min_pos], data[i]);
    }
    return 0;
}

/**
 * Merge Sort.
 * @param data: The array need be sorted.
 * @param length: Sort the head N elements, it should not be bigger than the array length.
 * @param compare: The function to compare the elements.
 * @param e, s: The start and end position. Set 0 at the first recursive loop.
 */
template <typename T>
static int msort(T* data, 
                 int64_t length,
                 int (*compare)(const T& lhs, const T& rhs) = cmp<T>,
                 int64_t s = 0,
                 int64_t e = 0) {
    if (s == 0 && e == 0) {
        // The first loop.
        e = length - 1;
    }
    if (length == 1 || length == 0) {
        return 0;
    }
    if (length == 2) {
        if (compare(data[s], data[e]) > 0) {
            std::swap(data[s], data[e]);
        }
        return 0;
    }
    int64_t middle = length / 2;
    msort(data, length - middle, compare, s, s + middle);
    msort(data, middle, compare, s + middle + 1, e);
    int64_t f_pos = s;
    int64_t s_pos = s + middle + 1;
    int64_t t_pos = 0;
    T* tmp = new T[length];
    while (f_pos <= s + middle && s_pos <= e) {
        if (data[f_pos] > data[s_pos]) {
            tmp[t_pos++] = data[s_pos++];
        } else {
            tmp[t_pos++] = data[f_pos++];
        }
    }
    while (f_pos <= s + middle) {
        tmp[t_pos++] = data[f_pos++];
    }
    while (s_pos <= e) {
        tmp[t_pos++] = data[s_pos++];
    }
    // Do not use memcpy, since type string will have problem.
    for (int64_t i = 0; i < length; ++i) {
        data[s + i] = tmp[i];
    }
    delete[] tmp;
    return 0;
}

// Heap supporting search remove and find, do not finish.
template <typename K, typename V>
class Heap {
private:
    template <typename KEY, typename VAL>
    struct Node {
        KEY key;
        VAL val;
    };
public:
    /**
     * Construction function
     * @param min: If it is a minimum heap.
     * @param compare: Compare function.
     * @param reserved: The reserved capacity, if over, it will automatially expand.
     */
    Heap(bool min = true, int (*compare)(const K& lhs, const K& rhs) = cmp<K>, int64_t reserved = 1000);
    virtual ~Heap();
    
    /**
     * Push element to the heap.
     * @return 0 means successfully.
     */
    int push(const K& key, const V& val);
    
    /**
     * Find the element in the heap.
     * @return 0 means having this element.
     */
    int find(const K& key, V* val = nullptr);
    
    /**
     * Erase the element.
     * @param val: If found this element, copy the element's value to this address.
     * @return 0 means successfully.
     */
    int erase(const K& key, V* val = nullptr);
    
    /**
     * Get the top element.
     * @return 0 means this heap is not empty.
     */
    int top(K* key = nullptr, V* val = nullptr);
    
    /**
     * Pop the top element.
     * @return 0 means this heap is not empty.
     */
    int pop();
    
    /**
     * Return the size of this heap.
     */
    int64_t size();
    
private:
    Node<K, V>* _data;
    int64_t     _length;
    int64_t     _capacity;
    bool        _min_heap;
    int (*_compare)(const K& lhs, const K& rhs);
    std::unordered_map<K, int64_t> _pos;
    
    /**
     * Expand the capacity twice.
     * @return 0 means successfully.
     */
    int _expand();
    
    /**
     * Find the position of node which holding the key.
     * @return -1 means unexisting.
     */
    int64_t _find_node(const T& key);
    
    /**
     * Adjust the element at place pos.
     */
    void _adjust(int64_t pos);
}; 

} // End namespace wttool.

template <typename K, typename V>
Heap<K, V>::Heap(bool min, int (*compare)(const K& lhs, const K& rhs), int64_t reserved) :
    _length(0), _capacity(reserved), _min_heap(min), _compare(compare) {
    _data = new(std::nothrow) T[_capacity];
    if (_data == nullptr) {
        toscreen << "Having problem when initializing the heap: malloc memory failed.\n";
        _capacity = 0;
    }
}

template <typename K, typename V>
int Heap<K, V>::push(const K& key, const V& val) {
    if (_capacity <= _length) {
        if (_expand() != 0) {
            toscreen << "Expand the heap failed. Insert element failed.\n";
            return -1;
        }
    }
    int64_t pos = _find_node(key);
    if (pos == -1) {
        
    }
    _data[_length].key = key;
    _data[_length].val = val;
    _pos[key] = 
    _adjust(_length++);
    return 0;
}

template <typename K, typename V>
int Heap<K, V>::find(const K& key, V* val) {
    int64_t pos = _find_node(key);
    if (pos == -1) {
        // Unexisting key.
        return -1;
    }
    if (val != nullptr) {
        *val = _data[pos].val;
    }
    return 0;
}

template <typename K, typename V>
int Heap<K, V>::erase(const K& key, V* val) {
    int64_t pos = _find_node(key);
    if (pos == -1) {
        // Unexisting key.
        return -1;
    }
    if (val != nullptr) {
        *val = _data[pos].val;
    }
    --_length;
    if (_length == 0) {
        return 0;
    }
    std::swap(_data[_length], _data[pos]);
    if (_length != 1) {
        _adjust(pos);
    }
    return 0;
}

template <typename K, typename V>
int Heap<K, V>::top(K* key, V* val) {
    if (_length == 0) {
        return -1;
    }
    if (key != nullptr) {
        *key = _data[0].key;
    }
    if (val != nullptr) {
        *val = _data[0].val;
    }
    return 0;
}

template <typename K, typename V>
int Heap<K, V>::pop() {
    if (_length == 0) {
        return -1;
    }
    if (_length == 1) {
        _length = 0;
    }
    std::swap(_data[--_length], _data[0]);
    _adjust(0);
    return 0;
}

template <typename K, typename V>
int64_t Heap<K, V>::size() {
    return _length;
}

template <typename K, typename V>
int Heap<K, V>::_expand() {
    Node<K, V>* _new_data = new(std::nothrow) Node<K, V>[_capacity * 2];
    if (_new_data == nullptr) {
        return -1;
    }
    // Do not use memcpy to move the data, since string format will work unproperly.
    // Use the construction function to copy the data.
    for (int64_t i = 0; i < _length; ++i) {
        _new_data[i] = _data[i];
    }
    delete[] _data;
    _data = _new_data;
    _capacity *= 2;
    return 0;
}

template <typename K, typename V>
int64_t Heap<K, V>::_find_node(const T& key) {
    if (_length == 0) {
        return -1;
    }
    int64_t cur_pos = 0;
    while (cur_pos < _length) {
        int cmp_res = _compare(_data[cur_pos].key, key);
        if (cmp_res == 0) {
            return cur_pos;
        }
        if (cmp_res > 0 && ) {
            
        }
    }
}

#endif // End ifdef __WTTOOL_SORT_HPP_.
