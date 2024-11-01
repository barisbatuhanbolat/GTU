# Custom class for represent basic graph
class Graph:
    def __init__(self):
        self.graph = {}

    def add_edge(self, u, v, latency):
        if u not in self.graph:
            self.graph[u] = []
        if v not in self.graph:
            self.graph[v] = []

        self.graph[u].append((v, latency))
        self.graph[v].append((u, latency))

# The function uses DFS algorithm to find path and the minimum latency between to points we wanted.
def findMinLatency(graph, start, end):
    stack = [(start, [start], 0)]
    min_latency = float('inf')
    best_path = []

    while stack:
        current_node, current_path, current_latency = stack.pop()

        if current_node == end and current_latency < min_latency:
            min_latency = current_latency
            best_path = list(current_path)

        for neighbor_node, neighbor_latency in graph[current_node]:
            if neighbor_node not in current_path:
                stack.append((neighbor_node, current_path + [neighbor_node], current_latency + neighbor_latency))

    return best_path, min_latency

# Test Example
network = Graph()
network.add_edge('A', 'B', 2)
network.add_edge('A', 'C', 5)
network.add_edge('B', 'D', 3)
network.add_edge('C', 'D', 1)
network.add_edge('D', 'E', 4)

start_node = 'A'
end_node = 'E'

best_path, min_latency = findMinLatency(network.graph, start_node, end_node)

print(f"The best path from {start_node} to {end_node}: {best_path}")
print(f"Minimum latency: {min_latency}")