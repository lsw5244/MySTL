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

        int     Data;   // ���� ����ִ� ������
        Node* Next; // ���� ����� �ּ�
        Node* Prev; // ���� ����� �ּ�
    };

public:
    // �⺻ ������
    DoubleLinkedList() = default;

    // count��ŭ�� ��Ҹ� ���� �ִ� �����̳ʸ� ����� ������
    explicit DoubleLinkedList(size_t count)
       // : DoubleLinkedList()
    {
        for (int i = 0; i < count; ++i)
        {
            push_front(0);
        }
    }

    // ���� ������. (�� �����ϱ�)
    DoubleLinkedList(const DoubleLinkedList& other)
       // : DoubleLinkedList()
        //: _end{other._end}, _head{other._head}, _size{other._size}
    {
        for (auto iter = other.begin(); iter != other.end(); ++iter)
        {
            push_back(iter->Data);
        }
    }

    // �Ҵ� ������
    DoubleLinkedList& operator=(const DoubleLinkedList& rhs)
        //: DoubleLinkedList()
    {
        if (this != &rhs)   // �ڰ� �ڽ� �Ҵ� ����
        {
            DoubleLinkedList temp = rhs;
            std::swap(_head, temp._head);
            std::swap(_end, temp._end);
            std::swap(_size, temp._size);
        }
        return *this;
    }

    // �Ҹ���
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

    // ù ��° ��Ҹ� ��ȯ�Ѵ�.
    int& front()
    {
        return _head->Data;
    }
    const int& front() const
    {
        return _head->Data;
    }

    // ������ ��Ҹ� ��ȯ�Ѵ�.
    int& back()
    {
        return _end->Prev->Data;
    }
    const int& back() const
    {
        return _end->Prev->Data;
    }

    // ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    // ����Ʈ�� ����ִٸ� end()�� ����.
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

    // �� ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* end()
    {
        return _end;
    }
    const Node* end() const
    {
        return _end;
    }

    // pos ������ value�� �����Ѵ�.
    // ���Ե� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* insert(Node* pos, int value)
    {
        // []  []  []  []
        // []  []  [o] [] []
        /*
            �� ��
            1. value���� ���� ���ο� ��� ����
            2. ���ο� ��带 ���������
            new.next = pos
            new.prev = pos.prev
            pos.prev.next = new
            pos.prev = new
            ---���� ó���� ��� �߰� �� ��---
            new.prev = nullptr
            new.next = pos
            pos.prev = new
        */
        
        Node* newNode = new Node(value);
        if (/*pos->Prev == nullptr*/pos == _head)  // pos�� ���� head�� �� ����ó��
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
        if (pos == _head) // ��� ����
        {
            _head = newNode;
        }

        ++_size;
        return newNode;
    }

    // pos ��Ҹ� �����Ѵ�.
    // ������ ����� ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    // �ƹ� ��ҵ� ������ end()�� ��ȯ�Ѵ�.
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

        if (pos == _head)       // ������� ��尡 ù��° ����� �� ��� ����
        {
            _head = nextNode;       
        }

        delete pos;
        pos = nullptr;

        return nextNode;
        
    }

    // ���ۿ� value�� �����Ѵ�.
    void            push_front(int value)
    {
        insert(_head, value);
    }

    // ���� value�� �����Ѵ�.
    void            push_back(int value);

    // ���� ��Ҹ� �����Ѵ�.
    void            pop_front()
    {
        erase(_head);
    }

    // �� ��Ҹ� �����Ѵ�.
    void            pop_back()
    {
        erase(_end);
    }

    // �����̳ʰ� ������� �Ǵ��Ѵ�.
    bool            empty() const
    {
        if (_size == 0)
        {
            return true;
        }
        return false;
    }

    // ����Ʈ �ȿ� �ִ� ����� ������ ��ȯ�Ѵ�.
    size_t          size() const
    {
        return _size;
    }

    // �����̳ʸ� ���������.
    void            clear()
    {
        while (_size <= 0/* empty() == true*/)
        {
            pop_front();
        }
    }

    // �ش� value�� �ִ��� üũ�Ѵ�.
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
    // ù��° ����� prev = nullptr, next�� ���� ����� �ּ�
    // _end���� �������� ���� ������� ����(���� ���� ���� �ּ�)
    Node*         _end;
    Node*         _head;        
    size_t          _size;
};
