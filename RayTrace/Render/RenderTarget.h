#pragma once
#include "../CoreDefine/CommonDefine.h"

class RenderTarget {
	protected:
	Color * * m_pFrameBuffer = nullptr;
	unsigned int m_nWidth = 0;
	unsigned int m_nHeight = 0;

	public:
	RenderTarget(unsigned int width, unsigned int height) 
		: m_nWidth(width), m_nHeight(height) {
		CreateBuffer();
	};
	~RenderTarget() {
		ReleaseBuffer();
	};

	inline Color** GetFrameBuffer() const {
		return m_pFrameBuffer;
	}

	inline unsigned int Width() const {
		return m_nWidth;
	}

	inline unsigned int Height() const {
		return m_nHeight;
	}

	void ReBuildRenderTarget(unsigned int width, unsigned int height) {
		ReleaseBuffer();
		m_nWidth = width;
		m_nHeight = height;
		CreateBuffer();
	}

	protected:
	void CreateBuffer() {
		m_pFrameBuffer = new Color*[m_nHeight];
		for (unsigned int i = 0; i < m_nHeight; i++)
			m_pFrameBuffer[i] = new Color[m_nWidth];
	}

	void ReleaseBuffer() {
		for (unsigned int i = 0; i < m_nHeight; ++i)
			delete[]m_pFrameBuffer[i];
		delete[]m_pFrameBuffer;
	}
};