#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/Dense>

#include "camera_help.h"
#include "kontiki/sensors/atan_camera.h"

namespace py = pybind11;

namespace C = kontiki::sensors;

PYBIND11_MODULE(_atan_camera, m) {
//  py::module::import("kontiki.sensors._pinhole_camera");

  using Class = C::AtanCamera;
//  using BaseClass = C::PinholeCamera;
  auto cls = py::class_<Class, std::shared_ptr<Class>>(m, "AtanCamera");
  cls.doc() = R"pbdoc( Arc-tan camera model for wide-angle cameras

  Implementation of the 3-parameter FOV model of [Devernay2001]_.

  Subclass of :class:`PinholeCamera`.

  References
  -------------------------
  .. [Devernay2001]
     Devernay, F. and Faugeras, O.
     *Straight lines have to be straight: Automatic calibration and removal of distortion
     from scenes of structured environments*
     Machie Vision and Applications, Vol 13., 2001

)pbdoc";

  cls.def(py::init<size_t, size_t, double, const Class::CameraMatrix&, const Eigen::Vector2d&, double >());
  cls.def_property("wc", &Class::wc, &Class::set_wc, "Distortion center");
  cls.def_property("gamma", &Class::gamma, &Class::set_gamma, "Distortion parameter");

  // All templated common functions must be explicitly created since they are not inherited
  // from the Pinhole base class.
  cls.def_property("camera_matrix", &Class::camera_matrix, &Class::set_camera_matrix);

  // Common functions
  declare_camera_common<Class>(cls);
}