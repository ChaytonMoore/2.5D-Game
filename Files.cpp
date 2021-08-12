#include "files.h"

std::vector<Line> LoadWallsText(std::string File)
{
	std::vector<Line> Output;


	std::string FileData;
	std::ifstream Data(File);

	std::vector<std::string> LineData;

	int a, b, c, d;
	std::string::size_type sz;

	while (std::getline(Data, FileData))
	{
		LineData = SplitString(FileData,",");

		a = std::stoi(LineData[0], &sz);
		b = std::stoi(LineData[1], &sz);
		c = std::stoi(LineData[2], &sz);
		d = std::stoi(LineData[3], &sz);
		Output.push_back(Line(a,b,c,d));
	}


	Data.close();

	return Output;
}
