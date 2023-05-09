#include <iostream>
#include <array>
#include <cmath>

struct Point
{
    float x, y;
};

struct Triangle
{
    std::array<Point, 3> points;
};

bool IsColliding(const Triangle& triangle1, const Triangle& triangle2)
{
    for(int i = 0; i < 3; i++)
    {
        float x1 = triangle1.points[i].x; 
        float y1 = triangle1.points[i].y;
        float x2 = triangle1.points[(i + 1) % 3].x; 
        float y2 = triangle1.points[(i + 1) % 3].y;

        for(int h = 0; h < 3; h++)
        {
            float x3 = triangle2.points[h].x;
            float y3 = triangle2.points[h].y;
            float x4 = triangle2.points[(h + 1) % 3].x;
            float y4 = triangle2.points[(h + 1) % 3].y;

            float denominator = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

            if(denominator == 0)
            {
                return false;
            }

            float a = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / denominator;
            float b = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / denominator;

            if (a >= 0 && a <= 1 && b >= 0 && b <= 1)
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    Triangle triangle1;
    triangle1.points[0] = {1, 1};
    triangle1.points[1] = {3, 1};
    triangle1.points[2] = {2, 3};

    Triangle triangle2;
    triangle2.points[0] = {3, -1};
    triangle2.points[1] = {5, -1};
    triangle2.points[2] = {4, 2};

    if(IsColliding(triangle1, triangle2))
    {
        std::cout << "Collides." << std::endl;
    }
    else
    {
        std::cout << "Don't Collide." << std::endl;
    }
}