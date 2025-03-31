import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file
data = pd.read_csv("benchmark_results.csv")

# Plot Response Time
plt.figure(figsize=(10, 6))
plt.plot(data["Iteration"], data["ResponseTime(ms)"], label="Response Time (ms)", color="blue")
plt.xlabel("Iteration")
plt.ylabel("Response Time (ms)")
plt.title("API Response Time")
plt.legend()
plt.grid()
plt.savefig("response_time.png")
plt.show()

# Plot CPU Usage
plt.figure(figsize=(10, 6))
plt.plot(data["Iteration"], data["CPUUsage(s)"], label="CPU Usage (s)", color="green")
plt.xlabel("Iteration")
plt.ylabel("CPU Usage (s)")
plt.title("CPU Usage Over Iterations")
plt.legend()
plt.grid()
plt.savefig("cpu_usage.png")
plt.show()

# Plot Memory Usage
plt.figure(figsize=(10, 6))
plt.plot(data["Iteration"], data["MemoryUsage(MB)"], label="Memory Usage (MB)", color="red")
plt.xlabel("Iteration")
plt.ylabel("Memory Usage (MB)")
plt.title("Memory Usage Over Iterations")
plt.legend()
plt.grid()
plt.savefig("memory_usage.png")
plt.show()