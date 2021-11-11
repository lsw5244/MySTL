#pragma once

#include <algorithm>

class CircularSingleLinkedList
{
public:
    struct Node
    {
        Node(int data = 0, Node* next = nullptr)
            : Data{ data }, Next{ next } { }
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        ~Node() = default;

        int   Data = 0;
        Node* Next = nullptr;
    };

public:
    // 기본 생성자
    CircularSingleLinkedList() = default;

    // 복사 생성자
    CircularSingleLinkedList(const CircularSingleLinkedList& other)
        :CircularSingleLinkedList()
    {
        if (other.empty())
        {
            return;
        }

        auto iter = other.head();
        do
        {
            push_back(iter->Data);
            iter = iter->Next;
        } while (iter != other.head());

    }

    // 할당 연산자
    CircularSingleLinkedList& operator=(const CircularSingleLinkedList& rhs)
    {
        if (this != &rhs)
        {
            CircularSingleLinkedList temp(rhs);
            
            std::swap(_beforeHead, temp._beforeHead);
            std::swap(_beforeTail, temp._beforeTail);
        }

        return   *this;
    }

    // 소멸자
    ~CircularSingleLinkedList();

    // 첫 번째 요소를 반환한다.
    int& front();
    const int& front() const;

    // 마지막 요소를 반환한다.
    int& back();
    const int& back() const;

    // 시작 전 요소를 가리키는 반복자를 반환한다.
    Node* before_head();
    const Node* before_head() const;

    // 끝 전 요소를 가리키는 반복자를 반환한다.
    Node* before_tail();
    const Node* before_tail() const;

    // 시작 요소를 가리키는 반복자를 반환한다.
    Node* head();
    const Node* head() const;

    // 끝 요소를 가리키는 반복자를 반환한다.
    Node* tail();
    const Node* tail() const;

    // pos 다음에 value를 삽입한다.
    // 삽입된 요소를 가리키는 반복자를 반환한다.
    Node* insert_after(Node* pos, int value);

    // pos 다음 요소를 삭제한다.
    // 삭제된 요소의 다음 요소를 가리키는 반복자를 반환한다.
    Node* erase_after(Node* pos);

    // 시작 요소에 value를 삽입한다.
    void      push_front(int value);

    // 마지막 요소에 value를 삽입한다.
    void      push_back(int value);

    // 시작 요소를 제거한다.
    void      pop_front();

    // 마지막 요소를 제거한다.
    void      pop_back();

    // 컨테이너가 비었는지 판단한다.
    bool      empty() const;

    // 컨테이너를 비워버린다.
    void      clear();

    // 컨테이너에 value가 있는지 확인한다.
    bool      contains(int value) const;
private:
    Node* _beforeHead = new Node;
    Node* _beforeTail = _beforeHead;
};
