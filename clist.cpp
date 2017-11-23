#include "clist.h"

CList::CList()
:m_pStartNode(NULL)
,m_pEndNode(NULL)
{

}

CList::CList(const CList& clBaseList)
{
    if (!clBaseList.m_pStartNode && !clBaseList.m_pEndNode)
    {
        m_pStartNode = NULL;
        m_pEndNode   = NULL;
        return;
    }

    if (clBaseList.m_pStartNode == clBaseList.m_pEndNode)
    {
        m_pStartNode = new CDoubleLinkedStruct(*clBaseList.m_pStartNode);
        m_pEndNode   = m_pStartNode;
        m_pStartNode->m_pNextNode = NULL;
        m_pStartNode->m_pPrevNode = NULL;
        return;
    }

    m_pStartNode = new CDoubleLinkedStruct(*clBaseList.m_pStartNode);
    m_pStartNode->m_pNextNode = NULL;
    m_pStartNode->m_pPrevNode = NULL;

    CDoubleLinkedStruct* pCurNode = clBaseList.m_pStartNode->m_pNextNode;
    CDoubleLinkedStruct* pCurNewPrevElement = m_pStartNode;
    CDoubleLinkedStruct* pCurNewElement = NULL;

    while (pCurNode)
    {
        pCurNewElement = new CDoubleLinkedStruct(*pCurNode);

        if (pCurNewPrevElement)
        {
            pCurNewElement->m_pPrevNode = pCurNewPrevElement;
            pCurNewPrevElement->m_pNextNode = pCurNewElement;
        }
        else
            pCurNewElement->m_pPrevNode = NULL;

        m_pEndNode = pCurNewElement;

        pCurNode = pCurNode->m_pNextNode;
        pCurNewPrevElement = pCurNewElement;
    }
}

CList::~CList()
{
    CDoubleLinkedStruct* pCurFlushNode = m_pStartNode;

    while (pCurFlushNode)
    {
        CDoubleLinkedStruct* pNextNode = pCurFlushNode->m_pNextNode;

        delete pCurFlushNode;

        pCurFlushNode = pNextNode;
    }
}

void CList::push_back(const int& iData)
{
    if (!m_pStartNode)
    {
        CDoubleLinkedStruct* pNewElement = new CDoubleLinkedStruct(iData);
        m_pStartNode = pNewElement;
        m_pEndNode   = pNewElement;
    }
    else
    {
        if (m_pStartNode == m_pEndNode)
        {
            CDoubleLinkedStruct* pNewElement = new CDoubleLinkedStruct(iData, m_pStartNode);

            m_pStartNode->m_pNextNode = pNewElement;
            m_pEndNode = pNewElement;
        }
        else
        {
            CDoubleLinkedStruct* pNewElement = new CDoubleLinkedStruct(iData, m_pEndNode);
            m_pEndNode->m_pNextNode = pNewElement;
            m_pEndNode = pNewElement;
        }
    }
}

void CList::RecursiveShowAllElements(CDoubleLinkedStruct* pCurNode)
{
    std::cout << pCurNode->m_iData << std::endl;

    CDoubleLinkedStruct* pNextNode = pCurNode->m_pNextNode;

    if (pNextNode)
        RecursiveShowAllElements(pNextNode);
}

void CList::ShowAllElements()
{
    if (m_pStartNode)
    {
        std::cout << "Next show all elements:" << std::endl;
        RecursiveShowAllElements(m_pStartNode);
    }
}

void CList::EraseLastElement()
{
    if (!m_pStartNode)
        return;

    if (m_pStartNode == m_pEndNode)
    {
        delete m_pStartNode;
        m_pStartNode = NULL;
        m_pEndNode = NULL;
    }
    else
    {
        CDoubleLinkedStruct* pPrevNode = m_pEndNode->m_pPrevNode;
        delete m_pEndNode;

        m_pEndNode = pPrevNode;
        pPrevNode->m_pNextNode = NULL;
    }
}

void CList::EraseByIndex(const int& iElementNum)
{
    int iCurIndex = 0;

    CDoubleLinkedStruct* curStruct = m_pStartNode;

    if (!curStruct)
        return;

    while (curStruct)
    {
        if (iCurIndex == iElementNum)
            break;

        curStruct = curStruct->m_pNextNode;
        ++iCurIndex;
    }

    CDoubleLinkedStruct* pNextNode = curStruct->m_pNextNode;
    CDoubleLinkedStruct* pPrevNode = curStruct->m_pPrevNode;

    if (!pPrevNode)
    {
        if (!pNextNode)
        {
            m_pStartNode = NULL;
            m_pEndNode   = NULL;
        }
        else
        {
            pNextNode->m_pPrevNode = NULL;
            m_pStartNode = pNextNode;
        }
    }
    else
    {
        if (!pNextNode)
        {
            m_pEndNode = pPrevNode;
            pPrevNode->m_pNextNode = NULL;
        }
        else
        {
            pNextNode->m_pPrevNode = pPrevNode;
            pPrevNode->m_pNextNode = pNextNode;
        }
    }

    delete curStruct;
}

const int& CList::at(const int& iElementNum) const
{
    int iCurIndex = 0;

    CDoubleLinkedStruct* curStruct = m_pStartNode;

    while (curStruct)
    {
        if (iCurIndex == iElementNum)
            break;

        curStruct = curStruct->m_pNextNode;
        ++iCurIndex;
    }
    return curStruct->m_iData;
}

int& CList::at(const int& iElementNum)
{
     int iCurIndex = 0;

     CDoubleLinkedStruct* curStruct = m_pStartNode;

     while (curStruct)
     {
         if (iCurIndex == iElementNum)
             break;

         curStruct = curStruct->m_pNextNode;
         ++iCurIndex;
     }
     return curStruct->m_iData;
}

CList& CList::operator=(const CList& clBaseList)
{
    if (&clBaseList == this)
        return *this;

    if (clBaseList.m_pStartNode == NULL && clBaseList.m_pEndNode == NULL)
    {
        m_pStartNode = NULL;
        m_pEndNode   = NULL;
        return *this;
    }

    if (clBaseList.m_pStartNode == clBaseList.m_pEndNode)
    {
        m_pStartNode = new CDoubleLinkedStruct(*clBaseList.m_pStartNode);
        m_pEndNode   = m_pStartNode;
        return *this;
    }

    m_pStartNode = new CDoubleLinkedStruct(*clBaseList.m_pStartNode);
    CDoubleLinkedStruct* pCurCopyingNode = clBaseList.m_pStartNode->m_pNextNode;
    CDoubleLinkedStruct* pCurNewPrevElement = m_pStartNode;
    CDoubleLinkedStruct* pCurNewElement = NULL;

    while (pCurCopyingNode)
    {
        pCurNewElement = new CDoubleLinkedStruct(*pCurCopyingNode);
        pCurNewElement->m_pPrevNode = pCurNewPrevElement;
        pCurNewPrevElement->m_pNextNode = pCurNewElement;

        m_pEndNode = pCurNewElement;

        pCurCopyingNode = pCurCopyingNode->m_pNextNode;
        pCurNewPrevElement = pCurNewElement;
    }

    return *this;
}

CList& CList::operator+(const CList& clBaseList)
{
    if (clBaseList.m_pStartNode == NULL)
        return *this;

    if (clBaseList.m_pStartNode == clBaseList.m_pEndNode)
    {
        push_back(clBaseList.m_pStartNode->m_iData);
        return *this;
    }

    CDoubleLinkedStruct* pCurNode = clBaseList.m_pStartNode;

    while (pCurNode)
    {
        const int& iNewInt = pCurNode->m_iData;
        push_back(iNewInt);
        pCurNode = pCurNode->m_pNextNode;
    }

    return *this;
}

CList& CList::operator+=(const CList& clBaseList)
{
    if (&clBaseList == this)
    {
        const CList cTempCopy(clBaseList);
        return *this + cTempCopy;
    }

    return *this + clBaseList;
}

int& CList::operator[](const int& iIndex)
{
    return at(iIndex);
}

const int& CList::operator[](const int& iIndex) const
{
    return at(iIndex);
}
