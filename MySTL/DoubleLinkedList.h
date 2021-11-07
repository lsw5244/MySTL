#pragma once
#include <algorithm>

class DoubleLinkedList
{
public:
    struct Node
    {
        Node(int data = 0, Node* prev = nullptr, Node* next = nullptr)
            :Data(data), Prev(prev), Next(next) {}
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        ~Node()
        {
            //Data = {};
            Next = nullptr;
            Prev = nullptr;
        }

        int     Data;   // 실제 들어있는 데이터
        Node* Next; // 다음 노드의 주소
        Node* Prev; // 이전 노드의 주소
    };

public:
    // 기본 생성자
    DoubleLinkedList() = default;

    // count만큼의 요소를 갖고 있는 컨테이너를 만드는 생성자
    explicit DoubleLinkedList(size_t count)
       // : DoubleLinkedList()
    {
        for (int i = 0; i < count; ++i)
        {
            push_front(0);
        }
    }

    // 복사 생성자. (값 복사하기)
    DoubleLinkedList(const DoubleLinkedList& other)
       // : DoubleLinkedList()
        //: _end{other._end}, _head{other._head}, _size{other._size}
    {
        for (auto iter = other.begin(); iter != other.end(); ++iter)
        {
            push_back(iter->Data);
        }
    }

    // 할당 연산자
    DoubleLinkedList& operator=(const DoubleLinkedList& rhs)
        //: DoubleLinkedList()
    {
        if (this != &rhs)   // 자가 자신 할당 막기
        {
            DoubleLinkedList temp = rhs;
            std::swap(_head, temp._head);
            std::swap(_end, temp._end);
            std::swap(_size, temp._size);
        }
        return *this;
    }

    // 소멸자
    ~DoubleLinkedList()
    {
        clear();
        _end = nullptr;
        _head = nullptr;
        _size = {};
     /*   Node* _end;
        Node* _head;
        size_t          _size;*/
    }

    // 첫 번째 요소를 반환한다.
    int& front()
    {
        return _head->Data;
    }
    const int& front() const
    {
        return _head->Data;
    }

    // 마지막 요소를 반환한다.
    int& back()
    {
        return _end->Prev->Data;
    }
    const int& back() const
    {
        return _end->Prev->Data;
    }

    // 시작 요소를 가리키는 반복자를 반환한다.
    // 리스트가 비어있다면 end()와 같다.
    Node* begin()
    {
        if (_size == 0)
        {
            return _end;
        }
        else
        {
            return _head;
        }
    }
    const Node* begin() const
    {
        if (_size == 0)
        {
            return _end;
        }
        else
        {
            return _head;
        }
    }

    // 끝 다음 요소를 가리키는 반복자를 반환한다.
    Node* end()
    {
        return _end;
    }
    const Node* end() const
    {
        return _end;
    }

    // pos 이전에 value를 삽입한다.
    // 삽입된 요소를 가리키는 반복자를 반환한다.
    Node* insert(Node* pos, int value)
    {
        // []  []  []  []
        // []  []  [o] [] []
        /*
            할 일
            1. value값을 가진 새로운 노드 생성
            2. 새로운 노드를 끼워줘야함
            new.next = pos
            new.prev = pos.prev
            pos.prev.next = new
            pos.prev = new
            ---제일 처음에 노드 추가 할 때---
            new.prev = nullptr
            new.next = pos
            pos.prev = new
        */
        
        Node* newNode = new Node(value);
        if (/*pos->Prev == nullptr*/pos == _head)  // pos가 제일 head일 때 예외처리
        {
            newNode->Prev = nullptr;
            newNode->Next = pos;
            pos->Prev = newNode;
        }
        else
        {
            newNode->Next = pos;
            newNode->Prev = pos->Prev;
            pos->Prev->Next = newNode;
            pos->Prev = newNode;
        }
        if (pos == _head) // 헤드 변경
        {
            _head = newNode;
        }

        ++_size;
        return newNode;
    }

    // pos 요소를 삭제한다.
    // 삭제된 요소의 다음 요소를 가리키는 반복자를 반환한다.
    // 아무 요소도 없으면 end()를 반환한다.
    Node* erase(Node* pos)
    {
        if (_size == 0)
        {
            return end();
        }
        Node* prevNode = pos->Prev;
        Node* nextNode = pos->Next;

        if (prevNode != nullptr)
        {
            prevNode->Next = nextNode;
        }
        if (nextNode != nullptr)
        {
            nextNode->Prev = prevNode;
        }

        if (pos == _head)       // 지우려는 노드가 첫번째 노드일 때 헤드 변경
        {
            _head = nextNode;       
        }

        delete pos;
        pos = nullptr;

        return nextNode;
        
    }

    // 시작에 value를 삽입한다.
    void            push_front(int value)
    {
        insert(_head, value);
    }

    // 끝에 value를 삽입한다.
    void            push_back(int value);

    // 시작 요소를 제거한다.
    void            pop_front()
    {
        erase(_head);
    }

    // 끝 요소를 제거한다.
    void            pop_back()
    {
        erase(_end);
    }

    // 컨테이너가 비었는지 판단한다.
    bool            empty() const
    {
        if (_size == 0)
        {
            return true;
        }
        return false;
    }

    // 리스트 안에 있는 요소의 개수를 반환한다.
    size_t          size() const
    {
        return _size;
    }

    // 컨테이너를 비워버린다.
    void            clear()
    {
        while (_size <= 0/* empty() == true*/)
        {
            pop_front();
        }
    }

    // 해당 value가 있는지 체크한다.
    bool            contains(int value) const
    {
        Node* nowNode = _head;
        while (nowNode != end())
        {
            if (nowNode->Data == value)
            {
                return true;
            }
            nowNode = nowNode->Next;
        }
        return false;
    }
private:
    // 첫번째 노드의 prev = nullptr, next는 다음 노드의 주소
    // _end에는 직접적인 값이 들어있지 않음(제일 끝의 다음 주소)
    Node*         _end;
    Node*         _head;        
    size_t          _size;
};
