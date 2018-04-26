#include "PPMWriter.h"

bool PPMWriter::WritePPMFile(std::string filePath)
{
	std::ofstream fStream(filePath);
	if (fStream.is_open())
	{
		_WritePPMFile(fStream);
		fStream.close();
		return true;
	}
	else
	{
		return false;
	}
}

void PPMWriter::_WritePPMFile(std::ofstream& fStream)
{
	fStream << "P3" << std::endl;
	fStream << m_nWidth << " " << m_nHeight << std::endl << "255" << std::endl;
	for (int i = m_nHeight - 1; i >= 0 ; --i)
	{
		for (int j = 0; j < m_nWidth; ++j)
		{
			Color& col = m_pFrameBuffer[i][j];
			fStream << unsigned int(255.99 * col.r) << " " << unsigned int(255.99 * col.g) << " " << unsigned int(255.99 * col.b) << std::endl;
		}
	}
}
