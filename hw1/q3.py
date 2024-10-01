import matplotlib.pyplot as plt

x = []
y = []

# Open file as read-only
with open('profiling_data.txt', 'r') as file:
    next(file)                                  # skip header line
    for line in file:
        length, timePerInsert = line.split()    # split at variables into x and y at whitespace
        x.append(int(length))
        y.append(int(timePerInsert))

# Create Scatter plot
plt.scatter(x, y, color='green', label="Seconds per Insert")

# Label the axes
plt.xlabel("Array length")
plt.ylabel("Seconds per Insert")
plt.title("Seconds per insert vs. Array Length")
plt.show()