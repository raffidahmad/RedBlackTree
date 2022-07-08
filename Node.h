#pragma once
template <class T>
struct Node {
	Node<T>* left;
	Node<T>* right;
	T data;
	char color;
	int count;
};