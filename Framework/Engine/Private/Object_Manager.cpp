#include "Object_Manager.h"
#include "GameInstance.h"

#include "GameObject.h"
#include "Layer.h"

CObject_Manager::CObject_Manager()
    : m_pGameInstance{ CGameInstance::GetInstance() }
{
    Safe_AddRef(m_pGameInstance);
}

HRESULT CObject_Manager::Initialize(_uint iNumLevels)
{
    m_pLayers = new map<const _wstring, CLayer*>[iNumLevels];

    m_iNumLevels = iNumLevels;

    return S_OK;
}

HRESULT CObject_Manager::Add_GameObject_ToLayer(_uint iLayerLevelIndex, const _wstring& strLayerTag, _uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, void* pArg)
{
    CGameObject* pGameObject = m_pGameInstance->Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg);
    if (nullptr == pGameObject)
        return E_FAIL;

    CLayer* pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);
    if (nullptr == pLayer)
    {
        pLayer = CLayer::Create();
        pLayer->Add_GameObject(pGameObject);
        m_pLayers[iLayerLevelIndex].emplace(strLayerTag, pLayer);
    }
    else
        pLayer->Add_GameObject(pGameObject);

    return S_OK;
}

CLayer* CObject_Manager::Find_Layer(_uint iLayerLevelIndex, const _wstring& strLayerTag)
{
    auto iter = m_pLayers[iLayerLevelIndex].find(strLayerTag);

    if (iter == m_pLayers[iLayerLevelIndex].end())
        return nullptr;

    return iter->second;
}

CObject_Manager* CObject_Manager::Create(_uint iNumLevels)
{
    CObject_Manager* pInstance = new CObject_Manager();

    if (FAILED(pInstance->Initialize(iNumLevels)))
    {
        MSG_BOX(TEXT("Failed to Created : CObject_Manager"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CObject_Manager::Free()
{
    __super::Free();

    for (size_t i = 0; i < m_iNumLevels; i++)
    {
        for (auto& Pair : m_pLayers[i])
            Safe_Release(Pair.second);

        m_pLayers[i].clear();
    }
}
