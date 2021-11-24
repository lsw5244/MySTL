#include <iostream>
#include <set>
#include "Set.h"

using namespace std;

int main()
{
	set<int> set = { 8, 3, 2, 5, 4,10, 14, 11, 16 };
	// 중위순회함 (오름차순)
	for (int data : set)
	{
		cout << data << ' ';
	}
	cout << endl;

	if (set.end() != set.find(2))
	{
		cout << "2찾음 !" << endl;
	}

	if (set.end() == set.find(12))
	{
		cout << "12못찾음 !" << endl;
	}

	cout << "size : " << set.size() << endl; //9

	cout << boolalpha << set.empty();  // false

	auto iter = set.begin(); // 2
	++iter;	// 3
	++iter;	// 4

	set.erase(iter); // 4가 사라짐
	cout << "size : " << set.size() << endl; // 8

	if (set.end() == set.find(4))
	{
		cout << "4 못찾음" << endl;
	}

	set.clear();

	cout << set.empty() << endl;	// true

	puts("-----------------------");

	Set mySet;
	mySet.insert(8);
	mySet.insert(3);
	mySet.insert(2);
	mySet.insert(5);
	mySet.insert(4);
	mySet.insert(10);
	mySet.insert(14);
	mySet.insert(11);
	mySet.insert(16);

	if (mySet.find(2))
	{
		cout << "2 찾음 !!!" << endl;
	}

	if (mySet.find(12) == nullptr)
	{
		cout << "12 못찾음 !!!" << endl;
	}

	cout << mySet.size() << endl; // 9

	cout << mySet.empty() << endl;	//false

	mySet.erase(4);

	cout << "size : " << mySet.size() << endl;

	if (mySet.find(4) == nullptr)
	{
		cout << "4 못찾음 !!!" << endl;
	}
	// 8 3 2 5 10 14 11 16	(전위)
	cout << "전위 순회" << endl;
	mySet.traverseByPreOrder();
	puts("");
	// 2 3 5 8 10 11 14 16 정렬됨(오름차순) (중위)
	cout << "중위 순회" << endl;
	mySet.traverseByInOrder();		// 오류 !
	puts("");
	// 2 5 3 11 16 4 10 8 (후위)
	cout << "후위 순회" << endl;
	mySet.traverseByPostOrder();		// 오류 !
	puts("");
	// 8 3 10 2 5 14 11 16(레벨)
	cout << "레벨 순회" << endl;
	mySet.traverseByLevelOrder();
	puts("");
	// 3
	cout << "Height : " << mySet.height() << ' ' << mySet.height2() << endl;

	mySet.clear();

	cout << mySet.empty() << endl; // true
}


//#include <iostream>
//#include <vector>
////#include "DoubleLinkedList.h"
//#include "DoubleLinkedList.h"
//#include "KGA_MyVector.h"
//
//using namespace std;
//int main()
//{
//    KGA_MyVector mv(5);
//
//    DoubleLinkedList dl;
//    //dl.pop_back();
//    dl.push_front(1);
//    dl.push_front(2);
//    dl.push_front(3);
//    dl.push_back(1);
//    dl.push_back(2);
//    dl.push_back(3);
//    dl.pop_back();
//
//
//    for (auto i = dl.begin(); i != dl.end(); )
//    {
//        cout << i->Data << endl;
//        i = i->Next;
//    }
//
//    cout << dl.size() << endl;
//    cout << boolalpha << dl.contains(2) << endl;
//
//    cout << "CLEAR !" << endl;
//    dl.clear();
//    dl.push_front(3);
//    for (auto i = dl.begin(); i != dl.end(); )
//    {
//        cout << i->Data << endl;
//        i = i->Next;
//    }
//    //DoubleLinkedList mList(5);
//    /*for (auto iter = mList.begin(); iter != mList.end(); ++iter)
//    {
//        std::cout << iter->Data << std::endl;
//    }*/
//}
