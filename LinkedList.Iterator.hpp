#pragma once

#ifndef LINKEDLIST_LINKEDLIST_ITERATOR_HPP
#define LINKEDLIST_LINKEDLIST_ITERATOR_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>
#include "LinkedList.Node.hpp"

/* Begin: LinkedIterator */
template <typename T>
class LinkedIterator {
    Node<T>* Now;

    public:
    explicit LinkedIterator(Node<T>* node);

    T& operator*();
    T* operator->();
    LinkedIterator& operator++();

    bool operator==(const LinkedIterator& other) const;
    bool operator!=(const LinkedIterator& other) const;
};

template <typename T>
LinkedIterator<T>::LinkedIterator(Node<T>* node) {
    LinkedIterator<T>::Now = node;
};

template <typename T>
T& LinkedIterator<T>::operator*() {
    return Now->Value;
}

template <typename T>
T* LinkedIterator<T>::operator->() {
    return &Now->Value;
}

template <typename T>
LinkedIterator<T>& LinkedIterator<T>::operator++() {
    Now = Now->Next.get();
    return *this->Now;
}

template <typename T>
bool LinkedIterator<T>::operator==(const LinkedIterator& other) const {
    return Now == other.Now;
}

template <typename T>
bool LinkedIterator<T>::operator!=(const LinkedIterator& other) const {
    return Now != other.Now;
}

/* End: LinkedIterator */

#endif //LINKEDLIST_LINKEDLIST_ITERATOR_HPP