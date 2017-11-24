#include "clist.h"

CList::CList()
:m_pStartNode(NULL)
,m_pEndNode(NULL)
{

}

CList::CList(const CList& clBaseList)
:m_pStartNode(NULL)
,m_pEndNode(NULL)
{
    if (!clBaseList.m_pStartNode && !clBaseList.m_pEndNode)
        return;

    if (clBaseList.m_pStartNode == clBaseList.m_pEndNode)
    {
        m_pStartNode = new CDoubleLinkedStruct(*clBaseList.m_pStartNode);
        m_pEndNode   = m_pStartNode;
        m_pStartNode->m_pNextNode = NULL;
        m_pStartNode->m_pPrevNode = NULL;
        return;
    }

    CDoubleLinkedStruct* pCurNode = clBaseList.m_pStartNode;

    while (pCurNode)
    {
        push_back(pCurNode->m_iData);
        pCurNode = pCurNode->m_pNextNode;
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

void CList::EraseStruct(CDoubleLinkedStruct *pCurStruct)
{
    CDoubleLinkedStruct* pNextNode = pCurStruct->m_pNextNode;
    CDoubleLinkedStruct* pPrevNode = pCurStruct->m_pPrevNode;

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

    delete pCurStruct;
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

    EraseStruct(curStruct);
}

const int& CList::at(const size_t& uElementNum) const
{
    size_t uCurIndex = 0;

    CDoubleLinkedStruct* curStruct = m_pStartNode;

    while (curStruct)
    {
        if (uCurIndex == uElementNum)
            break;

        curStruct = curStruct->m_pNextNode;
        ++uCurIndex;
    }
    return curStruct->m_iData;
}

int& CList::at(const size_t& uElementNum)
{
     size_t uCurIndex = 0;

     CDoubleLinkedStruct* curStruct = m_pStartNode;

     while (curStruct)
     {
         if (uCurIndex == uElementNum)
             break;

         curStruct = curStruct->m_pNextNode;
         ++uCurIndex;
     }
     return curStruct->m_iData;
}

CList& CList::operator=(const CList& clBaseList)
{
    if (&clBaseList == this)
        return *this;

    CDoubleLinkedStruct* pCurFlushNode = m_pStartNode;
    while (pCurFlushNode)
    {
        CDoubleLinkedStruct* pNextNode = pCurFlushNode->m_pNextNode;
        delete pCurFlushNode;
        pCurFlushNode = pNextNode;
    }
    m_pStartNode = NULL;
    m_pEndNode   = NULL;

    CDoubleLinkedStruct* pCurCopyingNode = clBaseList.m_pStartNode;

    while(pCurCopyingNode)
    {
        push_back(pCurCopyingNode->m_iData);
        pCurCopyingNode = pCurCopyingNode->m_pNextNode;
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

CList& operator+(CList& clList, const CList& clBaseList)
{
    if (clBaseList.m_pStartNode == NULL)
        return clList;

    CDoubleLinkedStruct* pCurNode = clBaseList.m_pStartNode;

    while (pCurNode)
    {
        clList.push_back(pCurNode->m_iData);
        pCurNode = pCurNode->m_pNextNode;
    }

    return clList;
}

int& CList::operator[](const size_t& iIndex)
{
    return at(iIndex);
}

const int& CList::operator[](const size_t& iIndex) const
{
    return at(iIndex);
}
