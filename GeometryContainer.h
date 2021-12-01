#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

struct IShape
{
	virtual bool read(std::ifstream& stream) = 0;
};

struct Circle: public IShape
{
	bool read(std::ifstream& stream)
	{
		stream >> center.first >> center.second >> radius;
		return true;
	}
	
	std::pair<double, double> center;
	double radius;
};

struct Ellipse: public IShape
{
	bool read(std::ifstream& stream)
	{
		stream >> focus1.first >> focus1.second
			   >> focus2.first >> focus2.second
			   >> eccentricity;
		return true;
	}
	
	std::pair<double, double> focus1;
	std::pair<double, double> focus2;
	double eccentricity;
};

class GeometryContainer
{
public:
	bool readCirclesData(const std::string& fileName)
	{
		return read<Circle>(fileName);
	}
	
	bool readEllipsesData(const std::string& fileName)
	{
		return read<Ellipse>(fileName);
	}
	
	size_t numberOfGeometries() const
	{
		return geometries.size();
	}
	
private:
	template <class Type>
	bool read(const std::string& fileName)
	{
		std::ifstream infile(fileName);
		if (!infile.is_open()) {
			return false;
		}

		while (true) {
			try {
				auto shape = std::make_unique<Type>();
				shape->read(infile);
				geometries.push_back(std::move(shape));
			} catch(std::exception& err) {
				std::cout << "error during reading" << err.what() << std::endl;
			}

			if (infile.eof())
				break;
		}
	
		infile.close();
		return true;
	}
	
private:
	std::vector<std::unique_ptr<IShape>> geometries;
};