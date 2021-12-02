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
        return static_cast<bool>(stream >> center.first >> center.second >> radius);
	}
	
	std::pair<double, double> center;
	double radius;
};

struct Ellipse: public IShape
{
	bool read(std::ifstream& stream)
	{
        return static_cast<bool>(stream >> focus1.first >> focus1.second
               >> focus2.first >> focus2.second
               >> eccentricity);
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

    const IShape* getShape(size_t index) const
    {
        return index < geometries.size() ? geometries[index].get() : nullptr;
    }

private:
	template <class Type>
	bool read(const std::string& fileName)
	{
		std::ifstream infile(fileName);
		if (!infile.is_open()) {
			return false;
		}

        // TODO: because the first row contains columm headers we skip it for now
        // we can parse it and adjust columns order
        char tempData[1024];
        infile.getline(tempData, 1024);

        do{
            auto shape = std::make_unique<Type>();
            if (!shape->read(infile)){
                break;
            }
            geometries.push_back(std::move(shape));
        }while(true);
	
		infile.close();
		return true;
    }
	
private:
	std::vector<std::unique_ptr<IShape>> geometries;
};
