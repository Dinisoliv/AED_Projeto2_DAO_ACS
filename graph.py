import matplotlib.pyplot as plt

# Data for elapsed times
elapsed_times = [
    {"vertex": 6, "edge": 3, "time_seconds": 0.000067},
    {"vertex": 6, "edge": 8, "time_seconds": 0.000102},
    {"vertex": 15, "edge": 26, "time_seconds": 0.000580},
    {"vertex": 6, "edge": 6, "time_seconds": 0.000136},
    {"vertex": 7, "edge": 9, "time_seconds": 0.000167},
    {"vertex": 7, "edge": 12, "time_seconds": 0.000157},
    {"vertex": 7, "edge": 11, "time_seconds": 0.000158},
    {"vertex": 15, "edge": 25, "time_seconds": 0.000526},
]

# Calculate new variable (vertex * edge)
products = [entry["vertex"] * entry["edge"] for entry in elapsed_times]
times = [entry["time_seconds"] * 1000 for entry in elapsed_times]  # Convert to milliseconds

# Create scatter plot
plt.figure(figsize=(10, 6))
scatter = plt.scatter(products, times, c=times, cmap='plasma', s=100)

# Add colorbar and labels
plt.colorbar(scatter, label="Time (ms)")
plt.title("Elapsed Time vs Product of Vertex and Edge")
plt.xlabel("Vertex * Edge (Product)")
plt.ylabel("Time (ms)")
plt.grid(True)

# Save and display the graph
plt.savefig("product_vs_time.png")  # Saves the graph locally
plt.show()
