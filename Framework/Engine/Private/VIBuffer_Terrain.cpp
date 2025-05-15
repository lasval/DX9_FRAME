#include "VIBuffer_Terrain.h"

CVIBuffer_Terrain::CVIBuffer_Terrain(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CVIBuffer{ pGraphic_Device }
{

}

CVIBuffer_Terrain::CVIBuffer_Terrain(const CVIBuffer_Terrain& Prototype)
	: CVIBuffer{ Prototype }
{

}

HRESULT CVIBuffer_Terrain::Initialize_Prototype()
{
	m_iNumVertices = 6;
	m_iVertexStride = sizeof(VTXPOSTEX);
	m_iFVF = D3DFVF_XYZ | D3DFVF_TEX1;
	m_ePrimitiveType = D3DPT_TRIANGLELIST;
	m_iNumPrimitive = 2;

	/* 정점버퍼를 생성한다. == 정점을 배열로 할당해준다. */
	/* 몇바이트할당해라 == 정점하나의 크기 * 정점의 갯수 */
	/* 0(정적) or D3DUSAGE_DYNAMIC(동적) */
	/* 정적 : 공간에 있는 값을 읽는 속도는 빠르다. 정점을 갱신한다라는 속도는굉장히 느리다. */
	/* 동적 : */
	/* D3DPOOL_MANAGED : 메모리할당 위치(RAM, VRAM)를 알아서 해라. */
	if (FAILED(m_pGraphic_Device->CreateVertexBuffer(m_iVertexStride * m_iNumVertices, 0, m_iFVF, D3DPOOL_MANAGED, &m_pVB, nullptr)))
		return E_FAIL;

	VTXPOSTEX* pVertices = { nullptr };

	/* 공간에 접근하기위한 포인터를 얻어오고 공간을 잠근다.  */
	m_pVB->Lock(0, /*m_iNumVertices * m_iVertexStride*/0, reinterpret_cast<void**>(&pVertices), 0);

	pVertices[0].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[0].vTexcoord = _float2(0.f, 0.f);

	pVertices[1].vPosition = _float3(0.5f, 0.5f, 0.f);
	pVertices[1].vTexcoord = _float2(1.f, 0.f);

	pVertices[2].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[2].vTexcoord = _float2(1.f, 1.f);

	pVertices[3].vPosition = _float3(-0.5f, 0.5f, 0.f);
	pVertices[3].vTexcoord = _float2(0.f, 0.f);

	pVertices[4].vPosition = _float3(0.5f, -0.5f, 0.f);
	pVertices[4].vTexcoord = _float2(1.f, 1.f);

	pVertices[5].vPosition = _float3(-0.5f, -0.5f, 0.f);
	pVertices[5].vTexcoord = _float2(0.f, 1.f);

	m_pVB->Unlock();

	return S_OK;
}

HRESULT CVIBuffer_Terrain::Initialize(void* pArg)
{


	return S_OK;
}

CVIBuffer_Terrain* CVIBuffer_Terrain::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX(TEXT("Failed to Created : CVIBuffer_Rect"));
		Safe_Release(pInstance);
	}
	return pInstance;
}


CComponent* CVIBuffer_Terrain::Clone(void* pArg)
{
	CVIBuffer_Terrain* pInstance = new CVIBuffer_Terrain(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CVIBuffer_Rect"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CVIBuffer_Terrain::Free()
{
	__super::Free();


}
