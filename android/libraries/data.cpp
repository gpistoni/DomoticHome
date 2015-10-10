#include "data.h"

CData* CData::m_pInstance = NULL;

void CData::init()
{
    m_pInstance = new CData;
}
