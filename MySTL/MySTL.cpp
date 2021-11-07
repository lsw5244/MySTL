#include <iostream>
#include <vector>
//#include "DoubleLinkedList.h"
#include "DoubleLinkedList.h"
#include "KGA_MyVector.h"

using namespace std;
int main()
{
    KGA_MyVector mv(5);

    DoubleLinkedList dl;
    //dl.pop_back();
    dl.push_front(1);
    dl.push_front(2);
    dl.push_front(3);
    dl.push_back(1);
    dl.push_back(2);
    dl.push_back(3);
    dl.pop_back();


    for (auto i = dl.begin(); i != dl.end(); )
    {
        cout << i->Data << endl;
        i = i->Next;
    }

    cout << dl.size() << endl;

    //DoubleLinkedList mList(5);
    /*for (auto iter = mList.begin(); iter != mList.end(); ++iter)
    {
        std::cout << iter->Data << std::endl;
    }*/
}
