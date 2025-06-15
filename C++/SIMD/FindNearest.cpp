#include <vector>
#include <iostream>
#include <DirectXMath.h>

using namespace DirectX;

struct Point
{
    float x = 0;
    float y = 0;

    Point(float xx, float yy) : x{xx}, y{yy} {}

    float DistSqr(const Point& other)
    {
        return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
    }
};


Point g_curr{0, 0};

float FindNearest(const std::vector<Point>& points)
{
    int res = -1;
    float min_dist = -1;
    for (int i = 0; i < points.size(); ++i)
    {
        const auto& curr = points[i]; 
        const auto curr_dist = g_curr.DistSqr(curr);
        if (curr_dist < min_dist || res < 0) 
        {
            res = i;
            min_dist = curr_dist;
        }
    }
    //return res;
    return min_dist;
}

float FindNearest_DXMath(const std::vector<Point>& points, const std::vector<float>& simd_data)
{
    int res = -1;
    float min_dist = -1;
    const auto vec4_count = points.size() / 4;
    XMVECTOR center_x = XMVectorSet(g_curr.x, g_curr.x, g_curr.x, g_curr.x);
    XMVECTOR center_y = XMVectorSet(g_curr.y, g_curr.y, g_curr.y, g_curr.y);
    const auto max_f = std::numeric_limits<float>::max();
    XMVECTOR min_dist_v4 = XMVectorSet(max_f, max_f, max_f, max_f);
    DirectX::XMVECTOR VV;
    for (int i = 0; i < vec4_count; ++i)
    {
        //auto curr = XMLoadFloat4(&(simd_data[i * 4 * 2]));
        auto curr_x = XMVectorSet(simd_data[i * 4 * 2 + 0], simd_data[i * 4 * 2 + 1],
            simd_data[i * 4 * 2 + 2], simd_data[i * 4 * 2 + 3]);
        auto curr_y = XMVectorSet(simd_data[i * 4 * 2 + 4], simd_data[i * 4 * 2 + 5],
            simd_data[i * 4 * 2 + 6], simd_data[i * 4 * 2 + 7]);
        auto center_sub_v_x = XMVectorSubtract(center_x, curr_x);
        auto center_sub_v_y = XMVectorSubtract(center_y, curr_y);
        auto sub_sqr_x = XMVectorMultiply(center_sub_v_x, center_sub_v_x);
        auto sub_sqr_y = XMVectorMultiply(center_sub_v_y, center_sub_v_y);
        auto dist_sqr = XMVectorAdd(sub_sqr_x, sub_sqr_y);
        min_dist_v4 = XMVectorMin(dist_sqr, min_dist_v4);
        //auto curr_min_dist = XMVectorMin()
        //if (min_dist < 0 || dist_sqr)
        // const auto& curr = points[i]; 
        // const auto curr_dist = g_curr.DistSqr(curr);
        // if (curr_dist < min_dist || res < 0)
        // {
        //     res = i;
        //     min_dist = curr_dist;
        // }
    }
    float temp[4];
    temp[0] = XMVectorGetX(min_dist_v4);
    temp[1] = XMVectorGetY(min_dist_v4);
    temp[2] = XMVectorGetZ(min_dist_v4);
    temp[3] = XMVectorGetW(min_dist_v4);
    for (int i = 0; i < 4; ++i) {
        if (temp[i] < min_dist || min_dist < 0) {
            min_dist = temp[i];
        }
    }
    for (int i = vec4_count * 4; i < points.size(); ++i)
    {
        const auto& curr = points[i]; 
        const auto curr_dist = g_curr.DistSqr(curr);
        if (curr_dist < min_dist || res < 0)
        {
            res = i;
            min_dist = curr_dist;
        }
    }
    return min_dist;
}

// compile with `cl /EHsc Vector4.cpp` in developer prompt
int main(int argc, const char** argv)
{
    std::vector<Point> points;
    std::vector<float> points_simd;
    {
        srand(time(0));
        for (int i = 0; i < 10000 * 1000; ++i)
        {
            points.emplace_back(rand() / 100.0f, rand() / 100.0f);
            if (i % 4 == 3)
            {
                auto& p0 = points[i - 3];
                auto& p1 = points[i - 2];
                auto& p2 = points[i - 1];
                auto& p3 = points[i - 0];
                points_simd.push_back(p0.x);
                points_simd.push_back(p1.x);
                points_simd.push_back(p2.x);
                points_simd.push_back(p3.x);
                points_simd.push_back(p0.y);
                points_simd.push_back(p1.y);
                points_simd.push_back(p2.y);
                points_simd.push_back(p3.y);
            }
        }
    }
    {
        const auto prev = clock();
        float res = FindNearest(points);
        const auto now = clock();
        std::cout << "simple ver, nearest dist: " << res 
            << ", time: "   << (now - prev) / 1000.0f << " seconds" << std::endl;
    }
    {
        const auto prev = clock();
        float res = FindNearest_DXMath(points, points_simd);
        const auto now = clock();
        std::cout << "simd ver, nearest dist: " << res 
            << ", time: "   << (now - prev) / 1000.0f << " seconds";
    }
    return 0;
}