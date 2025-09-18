import maptio
import numpy as np # Using numpy for easy data creation

# 1. Create a dataset
# This can be any list of lists or numpy array of shape (n_points, 2)
dataset = [[x, np.sin(x)] for x in np.linspace(0, 2 * np.pi, 1000)]

print("--- Testing Interpolation ---")
# 2. Use the factory to create an interpolator object
# You can use "linear", "spline", "poly", or "akima"
try:
    spline_interpolator = maptio.interpolation_factory("spline", dataset)

    # 3. Use the object's methods
    # Get a single value
    y_val = spline_interpolator.polate(np.pi / 2)
    print(f"Interpolated value at pi/2: {y_val:.4f} (expected: 1.0)")

    # Get the derivative
    deriv = spline_interpolator.derivative(0)
    print(f"Derivative at 0: {deriv:.4f} (expected: 1.0)")

    # Get the integral
    integral = spline_interpolator.integral(0, np.pi)
    print(f"Integral from 0 to pi: {integral:.4f} (expected: 2.0)")

except Exception as e:
    print(f"An error occurred: {e}")


print("\n--- Testing Extrapolation ---")
# 4. Use the extrapolation factory
try:
    # Use 'linear' or 'constant' for extrapolation
    linear_extrapolator = maptio.extrapolation_factory("linear", dataset)

    # Extrapolate a value outside the original data range
    extrap_val = linear_extrapolator.polate(8.0)
    print(f"Extrapolated value at 8.0: {extrap_val:.4f}")

except Exception as e:
    print(f"An error occurred: {e}")