#pragma once

#ifndef LINKEDLIST_LINKEDLIST_GET_HEAD_HPP
#define LINKEDLIST_LINKEDLIST_GET_HEAD_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>

#include "LinkedList.LL.base.hpp"
/* Begin: Get Head */

template <typename T>
Node<T>* LinkedList<T>::GetHeadData() {
    return Head.get();
}

template <typename T>
T LinkedList<T>::GetHead() {
    return GetHeadData()->Value;
}

template <typename T>
Node<T>* LinkedList<T>::GetHeadData(idx After) {
    Node<T>* Current = Head.get();
    
    while(After-- && Current) {
        Current = Current->Next.get();
    }
    
    if(!Current) {
        throw std::out_of_range("Index too big!");
    }
    
    return Current;
}

template <typename T>
T LinkedList<T>::GetHead(idx After) {
    return GetHeadData(After)->Value;
}

/* End: Get Head */

#endif //LINKEDLIST_LINKEDLIST_GET_HEAD_HPP