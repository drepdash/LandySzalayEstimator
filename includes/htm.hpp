#pragma once

#include <fstream>
#include <string>
#include <unordered_map>
#include <queue>
#include <Eigen/Dense>

namespace htm {

struct PointInfo;
struct Octahedron;
struct Constraint;
struct trixel;

class HTMAsciiParser;

class HTM
{
 private:
  Octahedron* _octahedron;

  std::unordered_map<std::string, PointInfo*>	_points;

 public:
  /// Add a new point to the working list
  void AddPoint(const double& ra, const double& dec);

  /// Assign a point (single operation) to the HTM
  std::string AssignPoint(PointInfo *pt);

  /// Create the base octahedron
  void CreateOctahedron();

  /// Delete the base Octahedron
  void DeleteOctahedron();

  /// Get number of pairs a the radius -+ delta from the given object
  unsigned int TwoPointsCorrelation(double &radius, double &delta);

 private:

  ///
  void constraintNotInside(trixel* trixel, const Eigen::Vector3d& p, Constraint*);

  ///
  void SelectRootTrixel(PointInfo* pt);

  ///
  inline std::pair<double, double>
      CalcCoordPoint(std::pair<double, double>& a,
                     std::pair<double, double>& b);

  ///
  inline double
      Scal(std::pair<double, double>& v1,
           std::pair<double, double>& v2) const;

  ///
  bool
      CheckPointInTriangle(std::pair<double, double> A,
                           std::pair<double, double> B,
                           std::pair<double, double> C,
                           std::pair<double, double> P);

  /// Check if a point is in a triangle describe by the given boundaries
  bool PointInTriangle(const double& ra,
                       const double& dec,
                       double* boundaries);

  /// Select the first level trixel in the given octahedron
  trixel* SelectRootOctahedronTrixel(const double& ra,
                                     const double& dec);

  /// send all trixels from the given one into the given output stream
  void Display(std::ofstream& fstream);

  /// Free all trixels
  void FreeAllTrixels(trixel* current);

  /// BOUNDARIES
  /// Double[4] = decMin, decMax, raMin, raMax
  double* ComputeRootTrixelBounds(trixel* trixel);

  /// Compute new bounds of a trixel's child from it's parent bounds and index
  double* ComputeTrixelBounds(const double* fatherBounds,
                              unsigned int& index,
                              bool& reverse);

  /// get the index an point using the parent trixel bounds
  unsigned int getIndex(double* boundaries,
                        bool& reverse,
                        const double& ra,
                        const double& dec);

 public:
  HTM();
  ~HTM();
};

}
