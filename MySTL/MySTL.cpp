﻿#include <iostream>
#include <vector>
//#include "DoubleLinkedList.h"
#include "DoubleLinkedList.h"
#include "KGA_MyVector.h"

using namespace std;
int main()
{
    KGA_MyVector mv(5);

    DoubleLinkedList dl;
    dl.push_front(1);

    for (auto i = dl.begin(); i != dl.end(); )
    {
        cout << i->Data << endl;
        i = i->Next;
    }


    //DoubleLinkedList mList(5);
    /*for (auto iter = mList.begin(); iter != mList.end(); ++iter)
    {
        std::cout << iter->Data << std::endl;
    }*/
}
