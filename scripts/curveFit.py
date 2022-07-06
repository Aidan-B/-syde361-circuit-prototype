import numpy as np
import matplotlib.pyplot as plt

# Measured light and analogRead() values
reading = np.array([0, 180, 280, 660, 1000, 1500, 1800, 2250, 2360, 2500, 2650, 3350, 4150, 5750, 5870])
lux     = np.array([0, 1,   5,   21,  42,   75,   92,   133,  165,  200,  215,  420,  700,  2840, 3370])

#
# polyfit (weighted)
#
# Fit a weighted polynomial of degree 1 (a linear function) to the data
p = np.polyfit(reading, np.log1p(lux), 1, w=np.sqrt(lux))
# Convert the polynomial back into an exponential
a = np.expm1(p[1])
b = p[0]
x_fitted_weighted = np.linspace(np.min(reading), np.max(reading), 100)
y_fitted_weighted = a * np.expm1(b * x_fitted_weighted)
# print equation
print(f"{a} * (exp({b} * x) - 1)")

# Plot
ax = plt.axes()
ax.scatter(reading, lux, label='Raw data')
ax.plot(x_fitted_weighted, y_fitted_weighted, 'g', label='polyfit - weighted')
ax.set_title('Exponential fit of collected lux readings')
ax.set_ylabel('Lux')
ax.set_xlabel('analogRead()')
ax.legend()

plt.show()