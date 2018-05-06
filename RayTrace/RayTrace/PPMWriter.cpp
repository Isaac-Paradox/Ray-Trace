#include "PPMWriter.h"

extern bool WritePPMFile(std::string filePath, const RenderTarget& target) {
	std::ofstream fStream(filePath);
	if (fStream.is_open()) {
		_WritePPMFile(fStream, target);
		fStream.close();
		return true;
	} else {
		return false;
	}
}

extern void _WritePPMFile(std::ofstream& fStream, const RenderTarget& target) {
	int height = (int)target.Height();
	int width = (int)target.Width();
	fStream << "P3" << std::endl;
	fStream << width << " " << height << std::endl << "255" << std::endl;
	Color** framebuffer = target.GetFrameBuffer();
	for (int i = height - 1; i >= 0; --i) {
		for (int j = 0; j < width; ++j) {
			Color& col = framebuffer[i][j];
			fStream << col.R() << " " << col.G() << " " << col.B() << std::endl;
		}
	}
}
