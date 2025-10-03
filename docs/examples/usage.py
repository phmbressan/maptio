import maptio
import numpy as np

dataset = [[x, np.sin(x)] for x in np.linspace(0, 2 * np.pi, 1000)]

print("--- Testing Interpolation ---")

try:
    spline_interpolator = maptio.interpolation_factory("spline", dataset)

    y_val = spline_interpolator.polate(np.pi / 2)
    print(f"Interpolated value at pi/2: {y_val:.4f} (expected: 1.0)")

    deriv = spline_interpolator.derivative(0)
    print(f"Derivative at 0: {deriv:.4f} (expected: 1.0)")

    integral = spline_interpolator.integral(0, np.pi)
    print(f"Integral from 0 to pi: {integral:.4f} (expected: 2.0)")

except Exception as e:
    print(f"An error occurred: {e}")


print("\n--- Testing Extrapolation ---")

try:
    linear_extrapolator = maptio.extrapolation_factory("linear", dataset)

    extrap_val = linear_extrapolator.polate(8.0)
    print(f"Extrapolated value at 8.0: {extrap_val:.4f}")

except Exception as e:
    print(f"An error occurred: {e}")
