#include "spline.hpp"

void Spline::init()
{
    std::vector<double> x, y, z;
        for (auto& p: _pts)
        {
            x.push_back(p.x);
            y.push_back(p.y);
            z.push_back(p.z);
        }
        _Mx = computeSecondDerivatives(x);
        _My = computeSecondDerivatives(y);
        _Mz = computeSecondDerivatives(z);
}

void Spline::update(double dist)
{
    _step += dist * _speed;

    _step = std::fmod(_step, _size);

    _last_pos = _position;
    _position = interpolation(_step);

    auto d = _position - _last_pos;
    d.normalize();

    _yaw = std::atan2(d.x, d.z);
    _pitch = std::atan2(-d.y, std::sqrt(d.x * d.x + d.z * d.z));
}

bool Spline::simule(double dist)
{
    _simul_step += dist * _speed;
    auto is_loop = _simul_step >= _size;

    _simul_step = std::fmod(_simul_step, _size);

    _simul_position = interpolation(_simul_step);

    if (is_loop) _simul_step = 0.0f;
    return is_loop;
}


std::vector<double> Spline::computeSecondDerivatives(const std::vector<double>& y) const
{
    std::vector<double> x(_size);

    std::vector<std::vector<double>> A(_size, std::vector<double>(_size, 0.0f));

    for (int i = 0; i < _size; i++)
    {
        auto h0 = 1.0f;
        auto h1 = 1.0f;

        x[i] = 6.0f * (y[(i + 1) % _size] - 2.0f * y[i] + y[(i - 1 + _size) % _size]);

        A[i][i]                     = 2.0f * (h0 + h1);
        A[i][(i - 1 + _size) % _size] = h0;
        A[i][(i + 1) % _size]        = h1;
    }

    for (int i = 0; i < _size; i++)
    {
        auto pivot = A[i][i];
        for (int k = i; k < _size; k++) A[i][k] /= pivot;
        x[i] /= pivot;

        for (int j = 0; j < _size; j++)
        {
            if (j == i) continue;

            auto factor = A[j][i];
            for (int k = i; k < _size; k++) A[j][k] -= factor * A[i][k];
            x[j] -= factor * x[i];
        }
    }

    return x;
}

STP3D::Vector3D Spline::interpolation(double step) const
{
    auto i = (int) std::floor(step);
    auto u = step - i;
    auto i1 = (i + 1) % _size;

    auto interp = [&](double p0, double p1, double M0, double M1)
    {
        auto a = (1.0f - u);
        auto b = u;
        return 
            a * p0 +
            b * p1 +
            ((a * a * a - a) * M0 +
             (b * b * b - b) * M1) * (1.0f / 6.0f);
    };

    return {
        (float) interp(_pts[i].x, _pts[i1].x, _Mx[i], _Mx[i1]),
        (float) interp(_pts[i].y, _pts[i1].y, _My[i], _My[i1]),
        (float) interp(_pts[i].z, _pts[i1].z, _Mz[i], _Mz[i1])
    };
}
