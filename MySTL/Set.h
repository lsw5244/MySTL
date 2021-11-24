#pragma once

#include	 <utility>
#include <iostream>
#include <queue>

using namespace std;
// 이진 검색 트리 사용
class Set
{
	// 연결 구조로 만들 것
	struct Node
	{
		Node(int data = 0, Node* parent = nullptr, Node* right = nullptr, Node* left = nullptr)
			: Data{ data }, Parent{ parent }, Left{ left }, Right{ right }{}
		// 복사 생성자
		Node(const Node&/* other*/) = delete;
		// 할당 연산자
		Node& operator=(const Node&/* rhs*/) = delete;
		~Node() { Parent = Left = Right = nullptr; }

		int Data = 0;
		Node* Parent = nullptr;	// 없어도 되기는 함 있으면 구현하기 용이함
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

	// 트리의 높이
	// 너비우선(BFS)
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
	//깊이우선 (DFS)
	int height2() const
	{
		return heightHelper(_root);
	}


	// 트리가 비었는지 확인
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

	// 삽입
	// pari<삽입 된 위치를 가르키는 반복자, 삽입이 되었는지>
	pair<Node*, bool> insert(int value)
	{
		if (empty())	// 루트가 없을 때( 트리가 비어있을 때)
		{
			_root = new Node(value);
			++_size;
			return make_pair(_root, true);
		}

		Node* inserted = _root;			// 어디다 삽입 할 지(삽입 될 위치)
		Node* parent = nullptr;	// 삽입할 노드의 부모
		// 삽입 할 위치 찾기
		while (inserted)
		{
			parent = inserted;

			if (inserted->Data == value)	// set의 value는 유일하기 때문에 같은 값을 발견하면 삽입하지 않는다.
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

		inserted = new Node(value, parent); // 삽입 될 위치에 노드 생성

		if (parent->Data > value)	// 부모 한번 더 검증 ?
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

	// 삭제
	void erase(Node* pos)		// 특정 위치삭제
	{
		// 트리가 비어있을 때
		if (empty())
		{
			return;
		}
		/*------------------------------------*/
		// 루트 노드를 삭제할 때
		if (pos->Parent == nullptr)
		{
			// 자식 없을 때
			if (pos->Left == nullptr && pos->Right == nullptr)
			{
				_root = nullptr;

				delete pos;
				pos = nullptr;

				--_size;
				return;
			}

			// 자식이 하나일 때
			if (pos->Left == nullptr)	// 오른족 자식만 있을 때
			{
				_root = pos->Right;		// 루트 노드 변경하기
				_root->Parent = nullptr;	// 부모 노드 없애기

				delete pos;
				pos = nullptr;

				--_size;
				return;
			}
			else if (pos->Right == nullptr) // 왼쪽 자식만 있을 때
			{
				_root = pos->Left;			// 루트 노드 변경
				_root->Parent = nullptr;	// 부모 노드 없애기

				delete pos;
				pos = nullptr;

				--_size;
				return;
			}
			// 자식이 2개일 때
			// 왼쪽에서 max값을 찾는다
			// 찾은 값을 root와 바꾸고 찾은 값이 있던 노드를 지운다.
			Node* successor = _root->Left;

			while (successor->Right != nullptr)	// 루트 기준 왼쪽 노드 중 값이 가장 큰 노드를 successor를 넣는다.
			{
				successor = successor->Right;
			}

			swap(successor->Data, _root->Data); // 데이터 교환

			erase(successor);	// successor삭제

			return;
		}
		/*------------------------------------*/
		/*------------------------------------*/
		// 자식이 없을 때 -> 단말 노드일 때 
		if (pos->Left == nullptr && pos->Right == nullptr)
		{
			// 부모의 상태 변경
			if (pos->Parent->Left == pos)
			{
				pos->Parent->Left = nullptr;
			}
			else
			{
				pos->Parent->Right = nullptr;
			}
			// 본인삭제
			delete pos;
			pos = nullptr;

			--_size;

			return;
		}
		/*------------------------------------*/
		/*------------------------------------*/
		// 자식이 하나일 때
		if (pos->Left == nullptr)	// 오른쪽에만 자식이 있을 때
		{
			if (pos->Parent->Left == pos)	// 내가 부모의 왼쪽 자식일 때
			{
				pos->Parent->Left = pos->Right;
			}
			else										// 내가 부모의 오른쪽 자식일 때
			{
				pos->Parent->Right = pos->Right;
			}
			// 내 자식(오른쪽)의 부모를 내 부모로 바꾸어 줌
			pos->Right->Parent = pos->Parent;
			// 본인 삭제
			delete pos;
			pos = nullptr;

			--_size;

			return;
		}
		else if (pos->Right == nullptr)	// 왼쪽에만 자식이 있을 때
		{
			if (pos->Parent->Left == pos)	// 내가 부모의 왼쪽 자식일 때
			{
				pos->Parent->Left = pos->Left;	// 부모의 왼쪽자식은 내 왼쪽 자식으로 변경
			}
			else										// 내가 부모의 오른쪽 자식일 때
			{
				pos->Parent->Right = pos->Left;	// 부모의 오른쪽자식은 내 왼쪽 자식으로 변경
			}
			// 내 자식(왼쪽)의 부모를 내 부모로 바꾸어 줌
			pos->Left->Parent = pos->Parent;
			// 본인 삭제
			delete pos;
			pos = nullptr;

			--_size;

			return;
		}
		/*------------------------------------*/
		/*------------------------------------*/
		// 자식이 2개일 때
		// 왼쪽의 max 혹은 오른쪽의 min을 원래 자리로 보내기
		// 왼쪽 갔다가 오른쪽 쭉 가면 왼쪽의 max
		// 오른쪽 갔다가 왼쪽 쭉 가면 오른쪽의 min
		Node* successor = pos->Left;

		while (successor->Right)	// 오른쪽으로 쭉 내려감(max값 찾기)
		{
			successor = successor->Right;
		}

		swap(pos->Data, successor->Data); // 데이터 바꾸기
		erase(successor);	// 단말노드 지우기
		/*------------------------------------*/
	}
	// 특정 값 삭제(삭제 하면 1(삭제된 개수) 못하면 0 반환)(set은 모든 수가 유일 함)
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

	// 검색
	Node* find(int value)
	{
		//find(value);
		//									static_cast는 형 변환 할 때 쓰는것
		//			const 떼기               나 자신을 const화 시킴      const.find부르기
		return const_cast<Node*>(static_cast<const Set&>(*this).find(value));
	}
	/*
		const 매소드란 ?
		내 멤버를 바꾸지 않겠다고 선언 할 때
		(root나 size를 변경할 수 없다)
		우리가 만든 타입에 const한정자 붙였을 때 호출되는 것을 방지하기 위해 ?
		const 한정자 안붙여도 cnst메소드를 부를 수 있음
		const 매소드인 경우 반환값에도 const를 붙여줘야 함 ( const안붙여서 반환하면 외부에서 변경 가능하기에 const붙인 이유가 없어짐)
	*/
	// 매개변수 const일 때
	const Node* find(int value) const
	{
		const Node* result = _root;

		while (result)
		{
			if (result->Data == value)	// 데이터 찾았을 때
			{
				return result;
			}
			else if (result->Data < value) // 찾을 값이 더 크면
			{
				result = result->Right; // 오른쪽으로 내려가기
			}
			else
			{
				result = result->Left;	// 왼쪽으로 내려가기
			}
		}

		return result;	// 못찾으면 nullptr반환
	}

	// 순회
	// 전위 순회
	void traverseByPreOrder()
	{
		// 현재 -> L - > R
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
	// 중위 순회
	void traverseByInOrder()
	{
		// L -> 현재 - > R 
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
	// 후위 순회
	void traverseByPostOrder()
	{
		// L -> R -> 현재
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
	// 큐(레벨)순회
	void traverseByLevelOrder()
	{
		if (empty() == true)
		{
			return;
		}

		// 레벨 순으로 순회
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

		int left = heightHelper(node->Left) + 1;		// 레프트 서브트리의 높이 + 1 = 왼쪽 트리의 높이
		int right = heightHelper(node->Right) + 1; // 오른족 서브트리의 높이 + 1 = 오른쪽 트리의 높이

		return max(left, right);
	}



private:
	Node* _root = nullptr;
	size_t _size = 0;

};