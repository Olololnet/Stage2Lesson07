#ifndef CLIST_H
#define CLIST_H

#include <iostream>

struct CDoubleLinkedStruct
{
    int m_iData;
    CDoubleLinkedStruct* m_pNextNode;
    CDoubleLinkedStruct* m_pPrevNode;

    CDoubleLinkedStruct(const int& iData, CDoubleLinkedStruct* pPrevNode = NULL)
    :m_iData(iData)
    ,m_pNextNode(NULL)
    ,m_pPrevNode(pPrevNode)
    {

    }

    CDoubleLinkedStruct(const CDoubleLinkedStruct& cdlBaseStruct)
    :m_iData(cdlBaseStruct.m_iData)
    ,m_pNextNode(NULL)
    ,m_pPrevNode(NULL)
    {

    }
};

class CList
{
public:
    CList();
    explicit CList(const CList& clBaseList);
    ~CList();
    void push_back(const int& iData);
    void ShowAllElements();
    void EraseLastElement();
    void EraseByIndex(const int& iElementNum);

    const int& at(const int& iElementNum) const;
    int& at(const int &iElementNum);

    CList& operator=(const CList& clBaseList);
    CList& operator+(const CList& clBaseList);
    CList& operator+=(const CList& clBaseList);

    int& operator[](const int& iIndex);
    const int& operator[](const int& iIndex) const;

protected:
    CDoubleLinkedStruct* m_pStartNode;
    CDoubleLinkedStruct* m_pEndNode;

    void RecursiveShowAllElements(CDoubleLinkedStruct* pCurNode);
};

#endif
