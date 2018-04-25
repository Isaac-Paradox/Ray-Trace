#pragma once
#include<string>
#include <fstream>
#include"CommonDefine.h"

class PPMWriter
{
protected:
	Color ** m_pFrameBuffer = nullptr;
	unsigned int m_nWidth = 0;
	unsigned int m_nHeight = 0;

public:
	PPMWriter(unsigned int width, unsigned int height) :
		m_nWidth(width), m_nHeight(height)
	{
		m_pFrameBuffer = new Color* [m_nHeight];
		for (int i = 0; i < m_nHeight; i++)
			m_pFrameBuffer[i] = new Color[width];
	}

	~PPMWriter()
	{
		for (int i = 0; i < m_nHeight; ++i)
			delete[]m_pFrameBuffer[i];
		delete[]m_pFrameBuffer;
	}

	inline Color** GetFrameBuffer()
	{
		return m_pFrameBuffer;
	}

	bool WritePPMFile(std::string filePath);

private:

	void _WritePPMFile(std::ofstream& fStream);
};

