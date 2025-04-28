#include "Prototype_Manager.h"
#include "GameObject.h"

#include "GameInstance.h"

CPrototype_Manager::CPrototype_Manager()
{
}

HRESULT CPrototype_Manager::Initialize(_uint iNumLevels)
{
	m_pPrototypes = new PROTOTYPES[iNumLevels];

	m_iNumLevels = iNumLevels;

	return S_OK;
}

HRESULT CPrototype_Manager::Add_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, CGameObject* pPrototype)
{
	if (nullptr == m_pPrototypes ||
		m_iNumLevels <= iPrototypeLevelIndex ||
		nullptr != Find_Prototype(iPrototypeLevelIndex, strPrototypeTag))
		return E_FAIL;

	m_pPrototypes[iPrototypeLevelIndex].emplace(strPrototypeTag, pPrototype);

	return S_OK;
}

CGameObject* CPrototype_Manager::Clone_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, void* pArg)
{
	CGameObject* pPrototype = Find_Prototype(iPrototypeLevelIndex, strPrototypeTag);

	if (nullptr == pPrototype)
		return nullptr;

	CGameObject*	pGameObject = pPrototype->Clone(pArg);
	if (nullptr == pGameObject)
		return nullptr;

	return pGameObject;
}

CGameObject* CPrototype_Manager::Find_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag)
{
	auto iter = m_pPrototypes[iPrototypeLevelIndex].find(strPrototypeTag);

	if (iter == m_pPrototypes[iPrototypeLevelIndex].end())
		return nullptr;

	return iter->second;
}

CPrototype_Manager* CPrototype_Manager::Create(_uint iNumLevels)
{
	CPrototype_Manager* pInstance = new CPrototype_Manager();

	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX(TEXT("Failed to Created : CPrototype_Manager"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CPrototype_Manager::Free()
{
	__super::Free();

	for (size_t i = 0; i < m_iNumLevels; i++)
	{
		for (auto& Pair : m_pPrototypes[i])
			Safe_Release(Pair.second);
		m_pPrototypes[i].clear();
	}

	Safe_Delete_Array(m_pPrototypes);
}
