#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer abstract : public CComponent
{
protected:
	CVIBuffer(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer(const CVIBuffer& Prototype);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

protected:
	LPDIRECT3DDEVICE9				m_pVB = { nullptr };

public:
	virtual CVIBuffer* Clone(void* pArg) = 0;
	virtual void Free() override;
};

END