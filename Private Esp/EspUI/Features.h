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

namespace Weak {
/// \brief Panama hash
/// \sa <a href="http://www.weidai.com/scan-mirror/md.html#Panama">Panama Hash</a>
template <class B = LittleEndian>
class PanamaHash : protected Panama<B>, public AlgorithmImpl<IteratedHash<word32, NativeByteOrder, 32>, PanamaHash<B> >
{
public:
	CRYPTOPP_CONSTANT(DIGESTSIZE = 32)
	virtual ~PanamaHash() {}
	PanamaHash() {Panama<B>::Reset();}
	unsigned int DigestSize() const {return DIGESTSIZE;}
	void TruncatedFinal(byte *hash, size_t size);
	CRYPTOPP_STATIC_CONSTEXPR const char* StaticAlgorithmName() {return B::ToEnum() == BIG_ENDIAN_ORDER ? "Panama-BE" : "Panama-LE";}
	std::string AlgorithmProvider() const {return Panama<B>::AlgorithmProvider();} // Fix https://github.com/weidai11/cryptopp/issues/801

protected:
	void Init() {Panama<B>::Reset();}
	void HashEndianCorrectedBlock(const word32 *data) {this->Iterate(1, data);}	// push
	size_t HashMultipleBlocks(const word32 *input, size_t length);
	word32* StateBuf() {return NULLPTR;}

	FixedSizeSecBlock<word32, 8> m_buf;
}

}
