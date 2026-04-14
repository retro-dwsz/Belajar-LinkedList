#pragma once

#ifndef LINKEDLIST_LINKEDLIST_OPERATORS_HPP
#define LINKEDLIST_LINKEDLIST_OPERATORS_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>

#include "LinkedList.LL.base.hpp"

/* Begin: Operators */

template <typename T>
T LinkedList<T>::operator[](idx Index) {
    return this->GetHead(Index);
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& Other) {
    if (this == &Other) {
        return *this;
    }

    Head.reset();

    Node<T>* Current = Other.Head.get();
    while(Current != nullptr) {
        PushBack(Current->Value);
        Current = Current->Next.get();
    }

    return *this;
}

template <typename T>
LinkedIterator<T> LinkedList<T>::begin() {
    return LinkedIterator<T>(Head.get());
}

template <typename T>
LinkedIterator<T> LinkedList<T>::end() {
    return LinkedIterator<T>(nullptr);
}

/* End: Operators */

#endif //LINKEDLIST_LINKEDLIST_OPERATORS_HPP