#pragma once

#include "Base.h"

BEGIN(Engine)

class CPrototype_Manager final : public CBase
{
private:
	CPrototype_Manager();
	virtual ~CPrototype_Manager() = default;

public:
	HRESULT Initialize(_uint iNumLevels);
	HRESULT Add_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, class CGameObject* pPrototype );
	class CGameObject* Clone_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag, void* pArg);

private:
	_uint										m_iNumLevels = { };
	map<const _wstring, class CGameObject*>*	m_pPrototypes = { nullptr };
	typedef map<const _wstring, class CGameObject*> PROTOTYPES;

private:
	class CGameObject* Find_Prototype(_uint iPrototypeLevelIndex, const _wstring& strPrototypeTag);

public:
	static CPrototype_Manager* Create(_uint iNumLevels);
	virtual void Free() override;

};

END