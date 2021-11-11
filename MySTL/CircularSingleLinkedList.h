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
    // �⺻ ������
    CircularSingleLinkedList() = default;

    // ���� ������
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

    // �Ҵ� ������
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

    // �Ҹ���
    ~CircularSingleLinkedList()
    {
        clear();
        // ���̷� ���� beforeHead����
        delete _beforeHead;
        _beforeHead = nullptr;
        _beforeTail = nullptr;
    }

    // ù ��° ��Ҹ� ��ȯ�Ѵ�.
    int& front() { return head()->Data; }
    const int& front() const { return head()->Data; }

    // ������ ��Ҹ� ��ȯ�Ѵ�.
    int& back() { return tail()->Data; }
    const int& back() const { return tail()->Data; }

    // ���� �� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* before_head() { return _beforeHead; }
    const Node* before_head() const { return _beforeHead; }

    // �� �� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* before_tail() { return _beforeTail; }
    const Node* before_tail() const { return _beforeTail; }

    // ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* head() { return before_head()->Next; }
    const Node* head() const { return before_head()->Next; }

    // �� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* tail() { return before_tail()->Next; }
    const Node* tail() const { return before_tail()->Next; }

    // pos ������ value�� �����Ѵ�.
    // ���Ե� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* insert_after(Node* pos, int value)
    {
        /*
            ���ܻ�Ȳ
            1. ù ��°(ó��) ���Ұ� ���Ե� ��       ==  ���Ե� ����� Next�� �ڱ� �ڽ��̾�� ��
            2. �� ��° ���Ұ� ���Ե� ��       == _beforeTail�� ��ġ�� �Ű���� ��
            3. pos�� beforeTail || tail�� �� == beforeTail�� �̷� �����(beforeTail = beforeTail->Next)
            4. ù�κ�(head)�� ���Ұ� ���Ե� ��(pos�� beforeTail�� ��)     ==  tail�� next�� �ٲ��־�� ��
        */
        Node* newNode = new Node(value);
        newNode->Next = pos->Next;
        pos->Next = newNode;

        if (head() == nullptr)  // �ƹ��͵� ���� ��(���Ұ� ó�� ���Ե�)
        {
            //before_head()->Next = newNode;
            newNode->Next = newNode;
        }
        else if (before_head() == before_tail())    // �� ��° ���Ұ� ���Ե�
        {
            _beforeTail = head();
            tail()->Next = head();
        }
        else if (pos == before_tail() || pos == tail())  //pos�� beforeTail || tail�� ��       beforeTail�� ĭ �о��ֱ�
        {
            _beforeTail = _beforeTail->Next;
            //tail()->Next = head();
        }
        else if (pos == before_head()) //ù�κ�(head)�� ���Ұ� ���Ե� ��(pos == beforehead)
        {
            tail()->Next = head();
        }

        return newNode;
    }

    // pos ���� ��Ҹ� �����Ѵ�.
    // ������ ����� ���� ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    Node* erase_after(Node* pos)
    {
        /*
            ���ܻ���
            1. ����Ʈ�� ������� ��  == tail�����ϱ�
            2. ���Ұ� �ϳ��ۿ� ���� ��  == �ʱ� ���·� �����ֱ�(beforeHead->next�ʱ�ȭ)
            3. ���Ұ� 2���� ��              == head�� next�� head�� ����, beforeTail�� beforeHead�� ����
            4. tail�� �����Ϸ� �� ��               == beforeTail����ֱ�
            5. beforeTail�� �����Ϸ� �� ��     == beforeTail ����ֱ�
            6. ó�� �κ�(head)�� ���ŵ� ��       == tail�� next�����ϱ�

            7. ���� �����ֱ�
        */
        if (empty())
        {
            return tail();
        }

        Node* removeNode = pos->Next;
        if (head()->Next == head())     // ���� �ϳ��� ��
        {
            before_head()->Next = nullptr;
        }
        else if (_beforeTail == head())     // ���� 2���� ��
        {
            before_head()->Next = removeNode->Next;
            _beforeTail = before_head();
            head()->Next = head();
        }
        else if (pos == before_tail())  // tail�� ����� �� ��
        {
            _beforeTail->Next = removeNode->Next;
            do
            {
                _beforeTail = _beforeTail->Next;
            } while (tail()->Next != head());
        }
        else if (pos->Next = before_tail()) // beforeTail�� ����� �� ��
        {
            pos->Next = removeNode->Next;
            _beforeTail = pos;
        }
        else if (pos->Next == head())    // ù �κ�(head)�� ���ŵ� ��
        {
            before_head()->Next = removeNode->Next;
            tail()->Next = removeNode->Next;
        }
        else    // �Ϲ����� ����  (��� �̾��ֱ�)
        {
            pos->Next = removeNode->Next;
        }


        return removeNode;
    }

    // ���� ��ҿ� value�� �����Ѵ�.
    void      push_front(int value)
    {
        insert_after(before_head(), value);
    }

    // ������ ��ҿ� value�� �����Ѵ�.
    void      push_back(int value)
    {
        insert_after(tail(), value);
    }

    // ���� ��Ҹ� �����Ѵ�.
    void      pop_front()
    {
        Node* eraseNode = erase_after(before_head());
        delete eraseNode;
    }

    // ������ ��Ҹ� �����Ѵ�.
    void      pop_back()
    {
        Node* eraseNode = erase_after(tail());
        delete eraseNode;
    }

    // �����̳ʰ� ������� �Ǵ��Ѵ�.
    bool      empty() const
    {
        return head() == nullptr;
    }

    // �����̳ʸ� ���������.
    void      clear()
    {
        while (empty() == false)
        {
            pop_front();
        }
    }

    // �����̳ʿ� value�� �ִ��� Ȯ���Ѵ�.
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
