#include "utils.hpp"

float hauteur(float charac)
{
    return (charac * scaling) - minVal;
}

float average(const std::vector<int> &point_adjacent)
{
    if (point_adjacent.empty())
    {
        return 0.;
    }
    float summ = 0.;
    for (auto i : point_adjacent)
    {
        summ += i;
    }
    return summ / point_adjacent.size();
}

float tree_hauteur(int i, int j)
{

    std::vector<int> point_adjacent = {};

    if (i - 1 >= 0)
    {
        int nord = ((i - 1) * width) + j;
        if (static_cast<float>(static_cast<unsigned char>(donnes[nord])) != 0)
        {
            point_adjacent.push_back(static_cast<float>(static_cast<unsigned char>(donnes[nord])));
        }
    }
    if (j - 1 >= 0)
    {
        int ouest = (i * width) + (j - 1);
        if (static_cast<float>(static_cast<unsigned char>(donnes[ouest])) != 0)
        {
            point_adjacent.push_back(static_cast<float>(static_cast<unsigned char>(donnes[ouest])));
        }
    }

    if (i + 1 <= length)
    {
        int sud = ((i + 1) * width) + j;
        if (static_cast<float>(static_cast<unsigned char>(donnes[sud])) != 0)
        {
            point_adjacent.push_back(static_cast<float>(static_cast<unsigned char>(donnes[sud])));
        }
    }
    if (j + 1 <= width)
    {
        int est = (i * width) + (j + 1);
        if (static_cast<float>(static_cast<unsigned char>(donnes[est])) != 0)
        {
            point_adjacent.push_back(static_cast<float>(static_cast<unsigned char>(donnes[est])));
        }
    }
    return average(point_adjacent);
}

void add_points(float x, float y, float h, float u, float v, std::vector<float> &points, std::vector<float> &colors, std::vector<float> &uvs, std::vector<float> &normals, bool isTree)
{
    if (isTree)
        zeroPosition.push_back({-(length / 2) + x, -(width / 2) + y, hauteur(h), (float)7 + (rand() % 14), (float)rand()});
    points.insert(points.end(), {-(length / 2) + x, -(width / 2) + y, hauteur(h)});
    float nx = ((tree_hauteur(x - 1, y) - tree_hauteur(x + 1, y)) * scaling) / (2. * Sp);
    float ny = ((tree_hauteur(x, y - 1) - tree_hauteur(x, y + 1)) * scaling) / (2. * Sp);
    normals.insert(normals.end(), {nx, ny, 1.0f});
    uvs.insert(uvs.end(), {u, v});
    colors.insert(colors.end(), {1.0f, 1.0f, 1.0f});
}
