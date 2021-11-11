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
    ~CircularSingleLinkedList()
    {
        clear();
        // 더미로 만든 beforeHead삭제
        delete _beforeHead;
        _beforeHead = nullptr;
        _beforeTail = nullptr;
    }

    // 첫 번째 요소를 반환한다.
    int& front() { return head()->Data; }
    const int& front() const { return head()->Data; }

    // 마지막 요소를 반환한다.
    int& back() { return tail()->Data; }
    const int& back() const { return tail()->Data; }

    // 시작 전 요소를 가리키는 반복자를 반환한다.
    Node* before_head() { return _beforeHead; }
    const Node* before_head() const { return _beforeHead; }

    // 끝 전 요소를 가리키는 반복자를 반환한다.
    Node* before_tail() { return _beforeTail; }
    const Node* before_tail() const { return _beforeTail; }

    // 시작 요소를 가리키는 반복자를 반환한다.
    Node* head() { return before_head()->Next; }
    const Node* head() const { return before_head()->Next; }

    // 끝 요소를 가리키는 반복자를 반환한다.
    Node* tail() { return before_tail()->Next; }
    const Node* tail() const { return before_tail()->Next; }

    // pos 다음에 value를 삽입한다.
    // 삽입된 요소를 가리키는 반복자를 반환한다.
    Node* insert_after(Node* pos, int value)
    {
        /*
            예외상황
            1. 첫 번째(처음) 원소가 삽입될 때       ==  삽입된 노드의 Next는 자기 자신이어야 함
            2. 두 번째 원소가 삽입될 때       == _beforeTail의 위치를 옮겨줘야 함
            3. pos가 beforeTail || tail일 때 == beforeTail을 미뤄 줘야함(beforeTail = beforeTail->Next)
            4. 첫부분(head)에 원소가 삽입될 때(pos가 beforeTail일 때)     ==  tail의 next를 바꿔주어야 함
        */
        Node* newNode = new Node(value);
        newNode->Next = pos->Next;
        pos->Next = newNode;

        if (head() == nullptr)  // 아무것도 없을 때(원소가 처음 삽입됨)
        {
            //before_head()->Next = newNode;
            newNode->Next = newNode;
        }
        else if (before_head() == before_tail())    // 두 번째 원소가 삽입됨
        {
            _beforeTail = head();
            tail()->Next = head();
        }
        else if (pos == before_tail() || pos == tail())  //pos가 beforeTail || tail일 때       beforeTail한 칸 밀어주기
        {
            _beforeTail = _beforeTail->Next;
            //tail()->Next = head();
        }
        else if (pos == before_head()) //첫부분(head)에 원소가 삽입될 때(pos == beforehead)
        {
            tail()->Next = head();
        }

        return newNode;
    }

    // pos 다음 요소를 삭제한다.
    // 삭제된 요소의 다음 요소를 가리키는 반복자를 반환한다.
    Node* erase_after(Node* pos);

    // 시작 요소에 value를 삽입한다.
    void      push_front(int value)
    {
        insert_after(before_head(), value);
    }

    // 마지막 요소에 value를 삽입한다.
    void      push_back(int value)
    {
        insert_after(tail(), value);
    }

    // 시작 요소를 제거한다.
    void      pop_front()
    {
        Node* eraseNode = erase_after(before_head());
        delete eraseNode;
    }

    // 마지막 요소를 제거한다.
    void      pop_back()
    {
        Node* eraseNode = erase_after(tail());
        delete eraseNode;
    }

    // 컨테이너가 비었는지 판단한다.
    bool      empty() const
    {
        return head() == nullptr;
    }

    // 컨테이너를 비워버린다.
    void      clear()
    {
        while (empty() == false)
        {
            pop_front();
        }
    }

    // 컨테이너에 value가 있는지 확인한다.
    bool      contains(int value) const
    {
        auto iter = head();
        do
        {
            if (iter->Data == value)
            {
                return true;
            }
            iter = iter->Next;
        } while (iter != head());
        return false;
    }
private:
    Node* _beforeHead = new Node;
    Node* _beforeTail = _beforeHead;
};
