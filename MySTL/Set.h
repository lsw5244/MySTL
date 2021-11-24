#pragma once

#include	 <utility>
#include <iostream>
#include <queue>

using namespace std;
// ���� �˻� Ʈ�� ���
class Set
{
	// ���� ������ ���� ��
	struct Node
	{
		Node(int data = 0, Node* parent = nullptr, Node* right = nullptr, Node* left = nullptr)
			: Data{ data }, Parent{ parent }, Left{ left }, Right{ right }{}
		// ���� ������
		Node(const Node&/* other*/) = delete;
		// �Ҵ� ������
		Node& operator=(const Node&/* rhs*/) = delete;
		~Node() { Parent = Left = Right = nullptr; }

		int Data = 0;
		Node* Parent = nullptr;	// ��� �Ǳ�� �� ������ �����ϱ� ������
		Node* Right = nullptr;
		Node* Left = nullptr;
	};
public:
	Set() = default;
	~Set()
	{
		clear();
		_root = nullptr;
		_size = 0;
	}

	// Ʈ���� ����
	// �ʺ�켱(BFS)
	int height() const
	{
		if (empty())
		{
			return -1;
		}
		/*return _size;*/
		queue<Node*> q;
		q.push(_root);

		int h = -1;
		while (q.empty() == false)
		{
			size_t sz = q.size();
			for (size_t i = 0; i < sz; i++)
			{
				Node* node = q.front();
				q.pop();

				if (node->Left != nullptr)
				{
					q.push(node->Left);
				}
				if (node->Right != nullptr)
				{
					q.push(node->Right);
				}
			}
			h++;
		}
		return h;
	}
	//���̿켱 (DFS)
	int height2() const
	{
		return heightHelper(_root);
	}


	// Ʈ���� ������� Ȯ��
	bool empty() const
	{
		return /*_size == 0 or */_root == nullptr;
	}

	size_t size() const
	{
		return _size;
	}

	void clear()
	{
		while (empty() == false)
		{
			erase(_root);
		}
	}

	// ����
	// pari<���� �� ��ġ�� ����Ű�� �ݺ���, ������ �Ǿ�����>
	pair<Node*, bool> insert(int value)
	{
		if (empty())	// ��Ʈ�� ���� ��( Ʈ���� ������� ��)
		{
			_root = new Node(value);
			++_size;
			return make_pair(_root, true);
		}

		Node* inserted = _root;			// ���� ���� �� ��(���� �� ��ġ)
		Node* parent = nullptr;	// ������ ����� �θ�
		// ���� �� ��ġ ã��
		while (inserted)
		{
			parent = inserted;

			if (inserted->Data == value)	// set�� value�� �����ϱ� ������ ���� ���� �߰��ϸ� �������� �ʴ´�.
			{
				return make_pair(inserted, false);
			}
			else if (inserted->Data < value)
			{
				inserted = inserted->Right;
			}
			else
			{
				inserted = inserted->Left;
			}
		}

		inserted = new Node(value, parent); // ���� �� ��ġ�� ��� ����

		if (parent->Data > value)	// �θ� �ѹ� �� ���� ?
		{
			parent->Left = inserted;
		}
		else
		{
			parent->Right = inserted;
		}

		++_size;

		return make_pair(inserted, true);
	}

	// ����
	void erase(Node* pos)		// Ư�� ��ġ����
	{
		// Ʈ���� ������� ��
		if (empty())
		{
			return;
		}
		/*------------------------------------*/
		// ��Ʈ ��带 ������ ��
		if (pos->Parent == nullptr)
		{
			// �ڽ� ���� ��
			if (pos->Left == nullptr && pos->Right == nullptr)
			{
				_root = nullptr;

				delete pos;
				pos = nullptr;

				--_size;
				return;
			}

			// �ڽ��� �ϳ��� ��
			if (pos->Left == nullptr)	// ������ �ڽĸ� ���� ��
			{
				_root = pos->Right;		// ��Ʈ ��� �����ϱ�
				_root->Parent = nullptr;	// �θ� ��� ���ֱ�

				delete pos;
				pos = nullptr;

				--_size;
				return;
			}
			else if (pos->Right == nullptr) // ���� �ڽĸ� ���� ��
			{
				_root = pos->Left;			// ��Ʈ ��� ����
				_root->Parent = nullptr;	// �θ� ��� ���ֱ�

				delete pos;
				pos = nullptr;

				--_size;
				return;
			}
			// �ڽ��� 2���� ��
			// ���ʿ��� max���� ã�´�
			// ã�� ���� root�� �ٲٰ� ã�� ���� �ִ� ��带 �����.
			Node* successor = _root->Left;

			while (successor->Right != nullptr)	// ��Ʈ ���� ���� ��� �� ���� ���� ū ��带 successor�� �ִ´�.
			{
				successor = successor->Right;
			}

			swap(successor->Data, _root->Data); // ������ ��ȯ

			erase(successor);	// successor����

			return;
		}
		/*------------------------------------*/
		/*------------------------------------*/
		// �ڽ��� ���� �� -> �ܸ� ����� �� 
		if (pos->Left == nullptr && pos->Right == nullptr)
		{
			// �θ��� ���� ����
			if (pos->Parent->Left == pos)
			{
				pos->Parent->Left = nullptr;
			}
			else
			{
				pos->Parent->Right = nullptr;
			}
			// ���λ���
			delete pos;
			pos = nullptr;

			--_size;

			return;
		}
		/*------------------------------------*/
		/*------------------------------------*/
		// �ڽ��� �ϳ��� ��
		if (pos->Left == nullptr)	// �����ʿ��� �ڽ��� ���� ��
		{
			if (pos->Parent->Left == pos)	// ���� �θ��� ���� �ڽ��� ��
			{
				pos->Parent->Left = pos->Right;
			}
			else										// ���� �θ��� ������ �ڽ��� ��
			{
				pos->Parent->Right = pos->Right;
			}
			// �� �ڽ�(������)�� �θ� �� �θ�� �ٲپ� ��
			pos->Right->Parent = pos->Parent;
			// ���� ����
			delete pos;
			pos = nullptr;

			--_size;

			return;
		}
		else if (pos->Right == nullptr)	// ���ʿ��� �ڽ��� ���� ��
		{
			if (pos->Parent->Left == pos)	// ���� �θ��� ���� �ڽ��� ��
			{
				pos->Parent->Left = pos->Left;	// �θ��� �����ڽ��� �� ���� �ڽ����� ����
			}
			else										// ���� �θ��� ������ �ڽ��� ��
			{
				pos->Parent->Right = pos->Left;	// �θ��� �������ڽ��� �� ���� �ڽ����� ����
			}
			// �� �ڽ�(����)�� �θ� �� �θ�� �ٲپ� ��
			pos->Left->Parent = pos->Parent;
			// ���� ����
			delete pos;
			pos = nullptr;

			--_size;

			return;
		}
		/*------------------------------------*/
		/*------------------------------------*/
		// �ڽ��� 2���� ��
		// ������ max Ȥ�� �������� min�� ���� �ڸ��� ������
		// ���� ���ٰ� ������ �� ���� ������ max
		// ������ ���ٰ� ���� �� ���� �������� min
		Node* successor = pos->Left;

		while (successor->Right)	// ���������� �� ������(max�� ã��)
		{
			successor = successor->Right;
		}

		swap(pos->Data, successor->Data); // ������ �ٲٱ�
		erase(successor);	// �ܸ���� �����
		/*------------------------------------*/
	}
	// Ư�� �� ����(���� �ϸ� 1(������ ����) ���ϸ� 0 ��ȯ)(set�� ��� ���� ���� ��)
	size_t erase(int value)
	{
		Node* removed = find(value);

		if (removed == nullptr)
		{
			return 0;
		}

		erase(removed);

		return 1;
	}

	// �˻�
	Node* find(int value)
	{
		//find(value);
		//									static_cast�� �� ��ȯ �� �� ���°�
		//			const ����               �� �ڽ��� constȭ ��Ŵ      const.find�θ���
		return const_cast<Node*>(static_cast<const Set&>(*this).find(value));
	}
	/*
		const �żҵ�� ?
		�� ����� �ٲ��� �ʰڴٰ� ���� �� ��
		(root�� size�� ������ �� ����)
		�츮�� ���� Ÿ�Կ� const������ �ٿ��� �� ȣ��Ǵ� ���� �����ϱ� ���� ?
		const ������ �Ⱥٿ��� cnst�޼ҵ带 �θ� �� ����
		const �żҵ��� ��� ��ȯ������ const�� �ٿ���� �� ( const�Ⱥٿ��� ��ȯ�ϸ� �ܺο��� ���� �����ϱ⿡ const���� ������ ������)
	*/
	// �Ű����� const�� ��
	const Node* find(int value) const
	{
		const Node* result = _root;

		while (result)
		{
			if (result->Data == value)	// ������ ã���� ��
			{
				return result;
			}
			else if (result->Data < value) // ã�� ���� �� ũ��
			{
				result = result->Right; // ���������� ��������
			}
			else
			{
				result = result->Left;	// �������� ��������
			}
		}

		return result;	// ��ã���� nullptr��ȯ
	}

	// ��ȸ
	// ���� ��ȸ
	void traverseByPreOrder()
	{
		// ���� -> L - > R
		traverseByPreOrderHelper(_root);
	}
	void traverseByPreOrderHelper(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}

		cout << node->Data << ' ';
		traverseByPreOrderHelper(node->Left);
		traverseByPreOrderHelper(node->Right);
	}
	//------------------------------------
	// ���� ��ȸ
	void traverseByInOrder()
	{
		// L -> ���� - > R 
		traverseByInOrderHelper(_root);
	}
	void traverseByInOrderHelper(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		traverseByInOrderHelper(node->Left);
		cout << node->Data << ' ';
		traverseByInOrderHelper(node->Right);
	}
	//------------------------------------
	// ���� ��ȸ
	void traverseByPostOrder()
	{
		// L -> R -> ����
		traverseByPostOrderHelper(_root);
	}
	void traverseByPostOrderHelper(Node* node)
	{
		if (node == nullptr)
		{
			return;
		}
		traverseByPostOrderHelper(node->Left);
		traverseByPostOrderHelper(node->Right);
		cout << node->Data << ' ';
	}
	//------------------------------------
	// ť(����)��ȸ
	void traverseByLevelOrder()
	{
		if (empty() == true)
		{
			return;
		}

		// ���� ������ ��ȸ
		queue<Node*> q;
		q.push(_root);

		size_t h = 0;

		while (q.empty() == false)
		{
			cout << "Level " << h << " : ";

			size_t sz = q.size();
			for (size_t i = 0; i < sz; i++)
			{
				Node* node = q.front();
				q.pop();

				cout << node->Data << ' ';

				if (node->Left != nullptr)
				{
					q.push(node->Left);
				}
				if (node->Right != nullptr)
				{
					q.push(node->Right);
				}
			}

			h++;

		}
	}

private:
	int heightHelper(const Node* node) const
	{
		if (node == nullptr)
		{
			return -1;
		}

		int left = heightHelper(node->Left) + 1;		// ����Ʈ ����Ʈ���� ���� + 1 = ���� Ʈ���� ����
		int right = heightHelper(node->Right) + 1; // ������ ����Ʈ���� ���� + 1 = ������ Ʈ���� ����

		return max(left, right);
	}



private:
	Node* _root = nullptr;
	size_t _size = 0;

};