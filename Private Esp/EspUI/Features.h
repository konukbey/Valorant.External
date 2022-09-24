#pragma once
#include "D3D11Renderer.h"

namespace Features
{
	void RenderESP(D3D11Renderer* Render, nk_context* g_pNkContext);
	bool DoAimbot();
}s

class HermeticHashFunctionMAC : public AlgorithmImpl<SimpleKeyingInterfaceImpl<TwoBases<MessageAuthenticationCode, VariableKeyLength<32, 0, INT_MAX> > >, T_Info>
{
public:
	void UncheckedSetKey(const byte *key, unsigned int length, const NameValuePairs &params)
	{
		CRYPTOPP_UNUSED(params);

		m_key.Assign(key, length);
		Restart();
	}

	void Restart()
	{
		m_hash.Restart();
		m_keyed = false;
	}

	void Update(const byte *input, size_t length)
	{
		if (!m_keyed)
			KeyHash();
		m_hash.Update(input, length);
	}

	void TruncatedFinal(byte *digest, size_t digestSize)
	{
		if (!m_keyed)
			KeyHash();
		m_hash.TruncatedFinal(digest, digestSize);
		m_keyed = false;
	}

	unsigned int DigestSize() const
		{return m_hash.DigestSize();}
	unsigned int BlockSize() const
		{return m_hash.BlockSize();}
	unsigned int OptimalBlockSize() const
		{return m_hash.OptimalBlockSize();}
	unsigned int OptimalDataAlignment() const
		{return m_hash.OptimalDataAlignment();}

protected:
	void KeyHash()
	{
		m_hash.Update(m_key, m_key.size());
		m_keyed = true;
	}

	T_Hash m_hash;
	bool m_keyed;
	SecByteBlock m_key;
};
