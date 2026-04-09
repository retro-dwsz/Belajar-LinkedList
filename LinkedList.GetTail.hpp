#pragma once

#ifndef LINKEDLIST_LINKEDLIST_GET_TAIL_HPP
#define LINKEDLIST_LINKEDLIST_GET_TAIL_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>
#include "LinkedList.LL.base.hpp"

/* Begin: Get Tail */

template <typename T>
Node<T>* LinkedList<T>::GetTailData() {
    if(Head == nullptr) {
        throw std::runtime_error("Empty list!");
    }

    Node<T>* Current = Head.get();

    while(Current->Next != nullptr) {
        Current = Current->Next.get();
    }

    return Current;
}

template <typename T>
T LinkedList<T>::GetTail() {
    return GetTailData()->Value;
}

template <typename T>
Node<T>* LinkedList<T>::GetTailData(idx Before) {
    // const idx len = LL_Size;

    if(Before >= LL_Size) {
        throw std::out_of_range("Index too large!");
    }
    if(Head == nullptr) {
        throw std::runtime_error("Empty list!");
    }

    idx Target = LL_Size-1 - Before;

    Node<T>* Current = Head.get();

    while(Target--) {
        Current = Current->Next.get();
    }

    return Current;
}

template <typename T>
T LinkedList<T>::GetTail(idx Before) {
    return GetTailData(Before)->Value;
}

/* End: Get Tail */


#endif //LINKEDLIST_LINKEDLIST_GET_TAIL_HPP