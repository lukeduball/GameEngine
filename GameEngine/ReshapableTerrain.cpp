#include "ReshapableTerrain.h"
#include <math.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <map>
#include <list>

ReshapableTerrain::ReshapableTerrain() {}

void ReshapableTerrain::triangleReshape(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	int size = vertices.size();
	std::vector<Line> triangleBounds = { Line{ point1, point2}, Line{ point2, point3 }, Line{ point1, point3 } };
	std::vector<Line> newLineList;
	for (int i = 0; i < size; i++)
	{
		glm::vec3 point = vertices[i];
		Line toPoint1{ point, point1 };
		Line toPoint2{ point, point2 };
		Line toPoint3{ point, point3 };
		if (!doesLineIntersectWithShapeBounds(triangleBounds, toPoint1) && !doesLineIntersectWithShapeBounds(newLineList, toPoint1))
		{
			newLineList.push_back(toPoint1);
		}
		if (!doesLineIntersectWithShapeBounds(triangleBounds, toPoint2) && !doesLineIntersectWithShapeBounds(newLineList, toPoint2))
		{
			newLineList.push_back(toPoint2);
		}
		if (!doesLineIntersectWithShapeBounds(triangleBounds, toPoint3) && !doesLineIntersectWithShapeBounds(newLineList, toPoint3))
		{
			newLineList.push_back(toPoint3);
		}
	}
	for (Line line : triangleBounds)
	{
		
	}
	for (Line line : newLineList)
	{
		std::cout << glm::to_string(line.point1) << ":" << glm::to_string(line.point2) << "\n";
	}
	
	
}

float ReshapableTerrain::distanceBetweenPoints(glm::vec3 point1, glm::vec3 point2)
{
	float distanceX = point1.x - point2.x;
	float distanceY = point1.y - point2.y;
	float distanceZ = point1.z - point2.z;
	float hypoXZ = sqrt(distanceX * distanceX + distanceZ * distanceZ);
	float distance = sqrt(distanceY * distanceY + hypoXZ * hypoXZ);
	return distance;
}

bool ReshapableTerrain::doLinesIntersect(Line line1, Line line2)
{
	return doLinesIntersect(line1.point1, line1.point2, line2.point1, line2.point2);
}

bool ReshapableTerrain::doLinesIntersect(glm::vec3 line1Point1, glm::vec3 line1Point2, glm::vec3 line2Point1, glm::vec3 line2Point2)
{
	glm::vec3 line1Heading = glm::normalize(line1Point1 - line1Point2);
	glm::vec3 line2Heading = glm::normalize(line2Point1 - line2Point2);
	float ratioX = line1Heading.x / line2Heading.x;
	float ratioY = line1Heading.y / line2Heading.y;
	float ratioZ = line1Heading.z / line2Heading.z;
	if (ratioX == ratioY && ratioY == ratioZ)
	{
		//std::cout << "PARRALEL" << std::endl;
		return false;
	}

	//Finds the x1 - x2 and y1 - y2 values
	float differenceX = line1Point1.x - line2Point1.x;
	float differenceY = line1Point1.y - line2Point1.y;
	//Sets the cooeficients of the unknowns for both values
	float V2xCo = line2Heading.x;
	float V2yCo = line2Heading.y;
	//Finds the multiplier to get rid of a unknown when the equations are added together
	float oppasiteMultiplier = (-V2xCo) / V2yCo;
	float differenceEquY = differenceY * oppasiteMultiplier;
	float yEquHeading = (-line1Heading.y) * oppasiteMultiplier;
	//Adds the two parts of the equations together
	float addedInitials = differenceX + differenceEquY;
	float addedHeadings = -line1Heading.x + yEquHeading;

	float unknown1 = addedInitials / addedHeadings;
	float unknown2 = (differenceY - (-line1Heading.y)*unknown1) / line2Heading.y;

	float x1 = line1Point1.x + line1Heading.x * unknown1;
	float y1 = line1Point1.y + line1Heading.y * unknown1;
	float z1 = line1Point1.z + line1Heading.z * unknown1;

	float x2 = line2Point1.x + line2Heading.x * unknown2;
	float y2 = line2Point1.y + line2Heading.y * unknown2;
	float z2 = line2Point1.z + line2Heading.z * unknown2;
	if (std::fabsf(x1 - x2) < 0.0001 && std::fabsf(y1 - y2) < 0.0001 && std::fabsf(z1 - z2) < 0.0001)
	{
		if (isPointBetweenRange(glm::vec3(x1, y1, z1), Line{ line1Point1, line1Point2 }, Line{line2Point1, line2Point2}))
		{
			//std::cout << glm::to_string(line1Point1) << ":" << glm::to_string(line1Point2) << "\n";
			//std::cout << "intersection1:" << glm::to_string(glm::vec3(x1, y1, z1)) << "\n";
			//std::cout << glm::to_string(line2Point1) << ":" << glm::to_string(line2Point2) << "\n";
			//std::cout << "intersection2:" << glm::to_string(glm::vec3(x2, y2, z2)) << "\n";
			//std::cout << "LINES INTERSECT" << "\n";
			return true;
		}
		//std::cout << "Intersection Not Within Segment" << std::endl;
		return false;
	}
	//std::cout << "Lines Don't Intersect" << std::endl;
	return false;
}

bool ReshapableTerrain::isPointBetweenRange(glm::vec3 point, Line line1, Line line2)
{
	float minX, maxX;
	float minY, maxY;
	float minZ, maxZ;
	sortHighLowPoints(minX, maxX, line1.point1.x, line1.point2.x);
	sortHighLowPoints(minY, maxY, line1.point1.y, line1.point2.y);
	sortHighLowPoints(minZ, maxZ, line1.point1.z, line1.point2.z);
	bool l1Segment = (minX == maxY || (minX < point.x  && maxX > point.x)) && (minY == maxY || (minY < point.y && maxY > point.y)) && (minZ == maxZ || (minZ < point.z && maxZ > point.z));
	sortHighLowPoints(minX, maxX, line2.point1.x, line2.point2.x);
	sortHighLowPoints(minY, maxY, line2.point1.y, line2.point2.y);
	sortHighLowPoints(minZ, maxZ, line2.point1.z, line2.point2.z);
	bool l2Segment = (minX == maxY || (minX < point.x  && maxX > point.x)) && (minY == maxY || (minY < point.y && maxY > point.y)) && (minZ == maxZ || (minZ < point.z && maxZ > point.z));
	return l1Segment && l2Segment;
}

void ReshapableTerrain::sortHighLowPoints(float & min, float & max, float rangeVal1, float rangeVal2)
{
	if (std::fabsf(rangeVal1 - rangeVal2) < 0.0001)
	{
		max = min = rangeVal1;
	}
	else if (rangeVal1 < rangeVal2)
	{
		min = rangeVal1;
		max = rangeVal2;
	}
	else
	{
		min = rangeVal2;
		max = rangeVal1;
	}
}

bool ReshapableTerrain::doesLineIntersectWithShapeBounds(std::vector<Line> shapeBounds, Line line)
{
	for (Line shapeLine : shapeBounds)
	{
		if (doLinesIntersect(shapeLine, line))
		{
			return true;
		}
	}
	return false;
}
