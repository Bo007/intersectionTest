#pragma once

#include <cmath>
#include <limits>

#include "GeometryContainer.h"

class GeometryUtility
{
public:
    bool computeIntersectionPoints(
        const GeometryContainer& geometryContainer,
        size_t firstShapeIndex,
        size_t secondShapeIndex,
        std::vector<std::pair<double,double>>& intersectionPoints)
    {
        intersectionPoints.clear();
        auto firstShape = geometryContainer.getShape(firstShapeIndex);
        auto secondShape = geometryContainer.getShape(secondShapeIndex);

        if (!firstShape || !secondShape)
        {
            return false;
        }

        auto firstCircle = dynamic_cast<const Circle *>(firstShape);
        auto secondCircle = dynamic_cast<const Circle *>(secondShape);
        if (firstCircle && secondCircle)
        {
            intersectionPoints = intersectCircles(firstCircle, secondCircle);
        }

        return !intersectionPoints.empty();
    }

private:
    std::vector<std::pair<double,double>>
    intersectCircles(const Circle* circle1, const Circle* circle2)
    {
        std::vector<std::pair<double,double>> result;
        // d is a line between circle centers
        double d = distanceBetweenPoints(circle1->center, circle2->center);
        if (valueIsNull(d) ||
            compareDouble(d, circle1->radius + circle2->radius) == 1 ||
            d < std::abs(circle1->radius - circle2->radius))
        {
            return result;
        }


        auto centersDelta = getDeltaPoint(circle1->center, circle2->center);

        double r1 = circle1->radius;
        double r2 = circle2->radius;

        // a is a distance on that orthogonale to which one contains both points
        double a = (r1 * r1 - r2 * r2 + d * d ) / (2 * d);

        std::pair<double,double> deltaPoint =
            {centersDelta.first * a / d, centersDelta.second * a / d};
        std::pair<double,double> intersectionPoint =
            {
                circle1->center.first + deltaPoint.first,
                circle1->center.second + deltaPoint.second
            };

        if (compareDouble(d, r1 + r2) != 0 &&
            compareDouble(d, std::abs(r1 - r2)) != 0)
        {
            // h is a distance from d line to intersection points
            double h = sqrt(r1 * r1 - a * a);
            result.push_back(
                {
                    intersectionPoint.first + h / d * centersDelta.second,
                    intersectionPoint.second - h / d * centersDelta.first
                });

            result.push_back(
                {
                    intersectionPoint.first - h / d * centersDelta.second,
                    intersectionPoint.second + h / d * centersDelta.first
                });
        }
        else
        {
            result.push_back(intersectionPoint);
        }

        return result;
    }

    static std::pair<double, double> getDeltaPoint(const std::pair<double, double>& point1,
                                                   const std::pair<double, double>& point2)
    {
        return {point2.first - point1.first,
                point2.second - point1.second};
    }
    static double distanceBetweenPoints(const std::pair<double, double>& point1,
                                        const std::pair<double, double>& point2)
    {
        return vecLenght(getDeltaPoint(point1, point2));
    }

    static double vecLenght(const std::pair<double, double>& vec)
    {
        return sqrt(vec.first * vec.first + vec.second * vec.second);
    }

    static bool valueIsNull(double value)
    {
        return value < std::numeric_limits<double>::epsilon();
    }

    static int compareDouble(double value1, double value2)
    {
        if (!valueIsNull(value1 - value2))
            return 1;

        if (!valueIsNull(value2 - value1))
            return -1;

        return 0;
    }
};
