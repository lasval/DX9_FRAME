#include "BackGround.h"
#include "GameObject.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphic_Device)
    : CGameObject { pGraphic_Device }
{
}

CBackGround::CBackGround(const CBackGround& Prototype)
    : CGameObject { Prototype }
{
}

HRESULT CBackGround::Initialize_ProtoType()
{
    return S_OK;
}

HRESULT CBackGround::Initialize(void* pArg)
{
    return S_OK;
}

void CBackGround::Priority_Update(_float fTimeDelta)
{
}

void CBackGround::Update(_float fTimeDelta)
{
}

void CBackGround::Late_Update(_float fTimeDelta)
{
}

HRESULT CBackGround::Render()
{
    return S_OK;
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
    CBackGround* pInstance = new CBackGround(pGraphic_Device);

    if (FAILED(pInstance->Initialize_ProtoType()))
    {
        MSG_BOX(TEXT("Failde to Created : CBackGround"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

CGameObject* CBackGround::Clone(void* pArg)
{
    CBackGround* pInstance = new CBackGround(*this);

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX(TEXT("Failde to Cloned : CBackGround"));
        Safe_Release(pInstance);
    }

    return pInstance;
}

void CBackGround::Free()
{
    __super::Free();
}
