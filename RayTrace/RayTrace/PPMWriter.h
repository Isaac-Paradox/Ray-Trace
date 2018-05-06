#pragma once
#include<string>
#include <fstream>
#include "Render/RenderTarget.h"

bool WritePPMFile(std::string filePath, const RenderTarget& target);

void _WritePPMFile(std::ofstream& fStream, const RenderTarget& target);

