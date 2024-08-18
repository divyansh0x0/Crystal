#include "crystal/core/Core.h"
#include "crystal/core/window.h"
#include "crystal/layout/Size.h"
#include "crystal/geometry/Vector3.h"
crystal::Size window_size = crystal::Size(800, 600);

int main() {
    crystal::Window window = crystal::Window("Crystal", window_size, crystal::Color(255, 255, 255, 255));
    // crystal::geometry::Matrix I =crystal::geometry::Matrix::identity(3,3);
    // crystal::geometry::Matrix m3(3,3,0);

    // crystal::geometry::Matrix m4 = m2.getSubMatrix(0,1);
    // logger::Success((m2.getAdjoint()).toString());
    // logger::Success((m4).toString());
    // logger::Success(std::to_string(m2.getDeterminant()));

    // logger::Success(m3.toString());

    // crystal::geometry::Vector3 v1 = crystal::geometry::Vector3(0, 1, 0);
    // crystal::geometry::Vector2 v2 = crystal::geometry::Vector2(1, 0);

    // logger::Success((v1*v2).toString());
    // logger::Success((v1/32).toString());
    // logger::Success(std::to_string(v1.magnitude()));
    // logger::Success(std::to_string(v1.magnitude()));
    // logger::Success(std::to_string(v1.magnitude()));
    // logger::Success(std::to_string(v1.magnitude()));
    window.show();
    return 0;
}
