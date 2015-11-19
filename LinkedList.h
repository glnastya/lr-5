#pragma once

#include <cstddef>           // size_t
#include <initializer_list>  // std::initializer_list<T>
#include <iosfwd>            // std::ostream

typedef double Data;

class LinkedList
{
	// �������������, ����� ��� "copy & swap", ���� �� �������, ��� ���.
	friend void swap(LinkedList& left, LinkedList& right);

	// ������� ��� �������, �����������.
	friend std::ostream& operator<<(std::ostream& output, const LinkedList& xs);

public:
	LinkedList();
	LinkedList(const std::initializer_list<Data> values);

	LinkedList(const LinkedList& source);
	LinkedList& operator=(LinkedList rhs);

	LinkedList(LinkedList&& source);
	LinkedList& operator=(LinkedList&& source);

	virtual ~LinkedList();

public:
	size_t size() const;

	void push_back(const Data& value);
	void push_front(const Data& value);
	void pop_back();
	void pop_front();

	void clear();

	// ��� ������������ ������� ������ ����������� std::out_of_range.
	void remove_at(size_t index);
	void insert_before(size_t index, const Data& value);
	void insert_after(size_t index, const Data& value);
	Data& value_at(size_t index);

	bool operator==(const LinkedList& other) const;
	bool operator!=(const LinkedList& other) const;

private:
	// TODO: ����� �������������� ���������� ��������� ���� Node.
	struct Node;

private:
	// ���������� ��������� �� ���� � �������� ��������.
	Node* node_at(size_t index);

	// ������� � ��������� � ������ ���� �� (�����) ����������.
	// ���� ��������� --- nullptr, ��������� ���� � ������ (� �����).
	Node* insert_before(Node* before);
	Node* insert_after(Node* after);

	// ������� ���� �� ��������� �� ����.
	void erase(const Node* node);

private:
	// TODO: ����� �������� ������-����� (����) LinkedList.
};