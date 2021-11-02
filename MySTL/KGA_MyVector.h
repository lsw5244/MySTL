#pragma once
class KGA_MyVector
{

public:
    // �⺻ ������
    KGA_MyVector() = default;

    // explicit ��������(����ȯ �ȵǵ��� ���°�)
    // �����ڿ��� ���� �� ����
    // count��ŭ ������ �Ҵ�� ������
    explicit KGA_MyVector(size_t count);

    // ���� ������. ���� ����(deep copy)�� �̷����� �Ѵ�.
    KGA_MyVector(const KGA_MyVector& other);

    // �Ҵ� ������. ���� ����(deep copy)�� �̷����� �Ѵ�.
    KGA_MyVector& operator=(const KGA_MyVector& rhs);

    // �̵� ������ 
    KGA_MyVector(KGA_MyVector&& other);
    // �̵� �Ҵ� ������
    KGA_MyVector& operator=(KGA_MyVector&& other);

    // �Ҹ���
    ~KGA_MyVector();

    // ù ��° ��Ҹ� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    int* begin();
    const int* begin() const;

    // ������ ����� ���� ��°�� ����Ű�� �ݺ��ڸ� ��ȯ�Ѵ�.
    int* end();
    const int* end() const;

    // �����̳ʰ� ������� �˻��Ѵ�.
    bool                empty() const;

    // ������ ������ ��ȯ�Ѵ�.
    size_t              size() const;

    // ���� �Ҵ�� ������ ũ�⸦ ��ȯ�Ѵ�.
    size_t              capacity() const;

    // pos�� ��ġ�� ������ ������ ��ȯ�Ѵ�.
    // ���� pos�� �������� ����� std::out_of_range ���ܰ� ��������.
    int& at(size_t pos);
    const int& at(size_t pos) const;

    // pos�� ��ġ�� ������ ������ ��ȯ�Ѵ�.
    int& operator[](size_t pos);
    const int& operator[](size_t pos) const;

    // �����̳��� ù ��° ������ ������ ��ȯ�Ѵ�.
    int& front();
    const int& front() const;

    // �����̳��� ������ ������ ������ ��ȯ�Ѵ�.
    int& back();
    const int& back() const;
    // �����̳ʸ� ����.
    void                clear();

    // pos ���� ��ġ�� value�� �����Ѵ�.
    // value�� ���Ե� ���� ����Ű�� �����͸� ��ȯ�Ѵ�.
    int* insert(int* pos, int value);

    // pos�� ��ġ�� ���Ҹ� �����.
    // ������ ����� ���� �����͸� ��ȯ�Ѵ�.
    int* erase(int* pos);

    // �����̳��� �� ���� ���Ҹ� �߰��Ѵ�.
    void                push_back(int value);

    // �����̳��� ������ ���Ҹ� �����Ѵ�.
    void                pop_back();

    // value�� �����ϴ��� �˻��Ѵ�.
    bool                contains(int value);

    // �����̳��� �뷮�� newCapacity���� ���ų� ũ�� �ø���.
    // newCapacity > _capacity��� ���ο� �޸𸮸� �Ҵ��ϰ�,
    // �׷��� �ʴٸ� �ƹ� ���۵� �������� �ʴ´�.
    void                reserve(size_t newCapacity);
private:
    int* _container = nullptr;               // �����̳�
    size_t              _size = 0;             // �� ��� ��
    size_t              _capacity = 0;      //���� �� �ִ� �ִ�
};
