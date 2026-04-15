#pragma once

#include <vector>
#include "tools/vector3d.hpp"

class Spline
{
public:
    Spline(const std::vector<STP3D::Vector3D>& pts)
    : _pts  { pts }
    , _size { (int) pts.size() - 1 }
    , _position { _pts.at(0) }
    { init(); }

    void update(double dist);
    const STP3D::Vector3D& getPosition() const { return _position; }
    double getAzimuthal() const { return _azimuthal; }
    double getElevation() const { return _elevation; }

    bool simule(double dist);
    const STP3D::Vector3D& getSimulPosition() const { return _simul_position; }

private:
    std::vector<STP3D::Vector3D> _pts;
    std::vector<double> _Mx, _My, _Mz;
    int _size;
    double _speed = 1.0f;

    double _step = 0.0f;
    STP3D::Vector3D _position;
    STP3D::Vector3D _last_pos;
    double _azimuthal, _elevation;

    double _simul_step = 0.0f;
    STP3D::Vector3D _simul_position;

    void init();

    std::vector<double> computeSecondDerivatives(const std::vector<double>& y) const;

    STP3D::Vector3D interpolation(double step) const;
};
