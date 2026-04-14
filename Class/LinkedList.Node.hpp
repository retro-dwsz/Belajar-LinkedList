#pragma once

#ifndef LINKEDLIST_LINKEDLIST_NODE_HPP
#define LINKEDLIST_LINKEDLIST_NODE_HPP

#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/color.h>

#include <Tools/Types.hpp>

/* Begin: Node struct */

template <typename T>
struct Node {
    T Value;
    uptr<Node<T>> Next;

    explicit Node(T Value, uptr<Node<T>> Next = nullptr);
};

template <typename T>
Node<T>::Node(T Value, uptr<Node<T>> Next) {
    this->Value = std::move(Value);
    this->Next = std::move(Next);
}

/* End: Node struct */

#endif //LINKEDLIST_LINKEDLIST_NODE_HPP