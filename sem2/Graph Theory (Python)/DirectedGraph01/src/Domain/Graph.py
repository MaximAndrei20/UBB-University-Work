from copy import deepcopy
from collections import deque

class Graph:
    def __init__(self, size):
        # size is the number of vertices
        self._size = size

        self._inbound_list = {i: [] for i in range(self._size)}
        self._outbound_list = {i: [] for i in range(self._size)}

        # (u,v) -> cost
        self._edge_costs = {}

        # edge_id -> (u,v,cost)
        self._edges = {}

        # (u,v) -> edge_id
        self._edge_ids = {}

        #counter for edge_id
        self._next_edge_id = 0

    def get_number_of_vertices(self):
        """
        :return: the number of vertices in the graph
        """
        return self._size

    def parse_vertices(self):
        """

        :return: an iterator over the vertices in the graph
        """
        return iter(self._outbound_list.keys())

    def add_vertex(self):
        """
        Adds a new vertex to the graph
        """
        self._size += 1
        self._outbound_list[self._size - 1] = []
        self._inbound_list[self._size - 1] = []

    def remove_vertex(self, vertex):
        """
        Removes a vertex from the graph
        :param vertex: the index of the vertex to be removed
        """
        if not (0 <= vertex < self._size):
            raise Exception("Invalid vertex index.")

        # go through self._edge_ids and if u or v is vertex add edge_id to list
        edge_ids_to_delete = []
        edges_to_delete = []
        for u, v in self._edge_ids:
            if u == vertex or v == vertex:
                edge_id = self._edge_ids[(u,v)]
                edge_ids_to_delete.append(edge_id)
                edges_to_delete.append((u,v))
                #del self._edge_ids[(u,v)]
                #del self._edges[edge_id]
        for i in range(len(edge_ids_to_delete)):
            del self._edge_ids[edges_to_delete[i]]
            del self._edges[edge_ids_to_delete[i]]

        del self._outbound_list[vertex]
        del self._inbound_list[vertex]

        for vertice in range(vertex + 1, self._size):
            self._outbound_list[vertice - 1] = self._outbound_list.pop(vertice)
            self._inbound_list[vertice - 1] = self._inbound_list.pop(vertice)

        new_edges = {}
        new_edge_ids = {}
        new_edge_costs = {}
        for edge_id, (start, end, cost) in self._edges.items():
            new_start = start - 1 if start > vertex else start
            new_end = end - 1 if end > vertex else end
            new_edges[edge_id] = (new_start, new_end, cost)
            new_edge_ids[(new_start, new_end)] = edge_id
            new_edge_costs[(new_start, new_end)] = cost

        self._edges = new_edges
        self._edge_ids = new_edge_ids
        self._edge_costs = new_edge_costs
        self._size -= 1




    def read_from_file(self, file_name):
        """
        Reads a graph from a file
        :param file_name: the filename of the file to read from
        """
        with open(file_name, 'r') as file:
            n, m = map(int, file.readline().split())
            self._size = n
            self._inbound_list = {i: [] for i in range(n)}
            self._outbound_list = {i: [] for i in range(n)}
            for _ in range(m):
                u, v, w = map(int, file.readline().split())
                self.add_edge(u, v, w)

    def write_to_file(self, file_name):
        """
        Writes the graph to a file
        :param file_name: the name of the file to write to
        :return:
        """
        with open(file_name, 'w') as file:
            file.write(f'{self._size} {len(self._edges)}\n')
            for edge_id, (u, v, w) in self._edges.items():
                file.write(f'{u} {v} {w}\n')

    def add_edge(self, u, v, w):
        """
        Adds an edge to the graph
        :param u: first vertex
        :param v: second vertex
        :param w: weight of the edge
        :return:
        """
        if u >= self._size or v >= self._size or u < 0 or v < 0:
            raise ValueError("Invalid vertex index")
        if v in self._outbound_list[u]:
            raise ValueError("Edge already exists")
        self._outbound_list[u].append(v)
        self._inbound_list[v].append(u)
        self._edge_costs[(u, v)] = w
        self._edges[self._next_edge_id] = (u, v, w)
        self._edge_ids[(u, v)] = self._next_edge_id
        self._next_edge_id += 1
        return True

    def remove_edge(self, edge_id):
        """
        Removes an edge from the graph
        :param edge_id: edge id to be removed
        """
        if edge_id not in self._edges:
            raise ValueError("Invalid edge id")
        u, v, _ = self._edges[edge_id]
        self._outbound_list[u].remove(v)
        self._inbound_list[v].remove(u)
        del self._edges[edge_id]
        del self._edge_ids[(u, v)]
        del self._edge_costs[(u, v)]

    def get_edge_id(self, u, v):
        """
        Returns the edge id of an edge
        :param u: first vertex
        :param v: second vertex
        """
        return self._edge_ids.get((u, v))

    def get_edge_endpoints(self, edge_id):
        """
        Returns the endpoints of an edge by edge id
        """
        return self._edges[edge_id][:2]

    def get_edge_by_edge_id(self, edge_id):
        """
        Returns the edge by edge id
        """
        if edge_id is None or edge_id not in self._edges:
            raise ValueError("Invalid edge id")
        return self._edges[edge_id]

    def set_edge_info(self, edge_id, new_cost):
        """
        Sets the cost of an edge
        :return:
        """
        u, v, _ = self._edges[edge_id]
        self._edges[edge_id] = (u, v, new_cost)
        self._edge_costs[(u, v)] = new_cost

    def _is_vertex(self, vertex):
        """
        Checks if a vertex is valid
        """
        return 0 <= vertex < self._size

    def get_in_degree(self, vertex):
        """
        Returns the in degree of a vertex
        """
        if not self._is_vertex(vertex):
            raise ValueError("Invalid vertex index")
        return len(self._inbound_list[vertex])

    def get_out_degree(self, vertex):
        """
        Returns the out degree of a vertex
        """
        if not self._is_vertex(vertex):
            raise ValueError("Invalid vertex index")
        return len(self._outbound_list[vertex])

    def parse_outbound_edges(self, vertex):
        """
        Returns an iterator over the outbound edges of a vertex
        """
        if not self._is_vertex(vertex):
            raise ValueError("Invalid vertex index")
        return iter(self._outbound_list[vertex])

    def parse_inbound_edges(self, vertex):
        """
        Returns an iterator over the inbound edges of a vertex
        """
        if not self._is_vertex(vertex):
            raise ValueError("Invalid vertex index")
        return iter(self._inbound_list[vertex])

    def copy_graph(self):
        """
        Returns a copy of the graph
        """
        copy = deepcopy(self)
        return copy

    def bfs(self, start, end):
        """

        :param start: first vertex
        :param end: second vertex
        :return: a list with the path from start to end, empty if no path found
        """
        if not self._is_vertex(start) or not self._is_vertex(end):
            raise ValueError("Invalid vertex index")
        queue = [[start]]
        visited = [False] * self._size
        while queue:
            path = queue.pop(0)
            node = path[-1]
            if visited[node]:
                continue
            visited[node] = True
            if node == end:
                return path
            for adjacent in self._outbound_list[node]:
                new_path = list(path)
                new_path.append(adjacent)
                queue.append(new_path)
        return []

    def generate_random_graph(self, number_of_vertices, number_of_edges):
        """
        Generates a random graph
        :param number_of_vertices: number of vertices of the new graph
        :param number_of_edges: number of edges of the new graph
        """
        import random
        self._size = number_of_vertices
        self._inbound_list = {i: [] for i in range(number_of_vertices)}
        self._outbound_list = {i: [] for i in range(number_of_vertices)}
        self._edge_costs = {}
        self._edges = {}
        self._edge_ids = {}
        self._next_edge_id = 0
        added = 0
        while added < number_of_edges:
            u = random.randint(0, number_of_vertices - 1)
            v = random.randint(0, number_of_vertices - 1)
            if u == v:
                continue
            if v in self._outbound_list[u]:
                continue
            w = random.randint(1, 100)
            self.add_edge(u, v, w)
            added += 1

    def get_strongly_connected_components(self):
        """
        TODO: Implement this
        :return:
        """
        visited = [False] * self._size
        onStack = [False] * self._size
        ids = [0] * self._size
        low = [0] * self._size
        id = [0]
        STC = []
        S = []
        for i in range(self._size):
            if not visited[i]:
                self._dfs_sct(i, visited, onStack, ids, low, id, STC, S)
        return STC

    def _dfs_sct(self, vertex, visited, onStack, ids, low, id, STC, S):
        """
        TODO: Implement this
        :param vertex:
        :param visited:
        :param onStack:
        :param ids:
        :param low:
        :param id:
        :return:
        """
        visited[vertex] = True
        S.append(vertex)
        onStack[vertex] = True
        id[0] += 1
        ids[vertex] = id[0]
        low[vertex] = id[0]

        for adj in self._outbound_list[vertex]:
            if not visited[adj]:
                self._dfs_sct(adj, visited, onStack, ids, low, id, STC, S)
            if onStack[adj]:
                low[vertex] = min(low[vertex], low[adj])

        if ids[vertex] == low[vertex]:
            component = []
            while S[-1] != vertex:
                node = S.pop()
                onStack[node] = False
                component.append(node)
                if node == vertex:
                    break
            # Add component to list of strongly connected components
            if len(component) > 0:
                STC.append(component)

    def bellman_ford(self, start, end):
        """
        Bellman-Ford algorithm to find the shortest path from start to end
        :param start: starting vertex
        :param end: ending vertex
        :return: a list with the path from start to end, empty if no path found
        """

        n = self.get_number_of_vertices()
        d = [[float('inf')] * (n + 1) for _ in range(n)]
        d[start][0] = 0  # Cost to reach the start vertex with 0 edges is 0

        # Dynamic programming to fill the matrix
        for k in range(1, n + 1):
            for u in range(n):
                for v in self.parse_outbound_edges(u):
                    cost = self.get_edge_by_edge_id(self.get_edge_id(u, v))[2]
                    d[v][k] = min(d[v][k], d[u][k - 1] + cost)

        # Check for negative-cost cycles on the path to end vertex
        for u in range(n):
            for v in self.parse_outbound_edges(u):
                cost = self.get_edge_by_edge_id(self.get_edge_id(u, v))[2]
                if d[u][n] != float('inf') and d[v][n] > d[u][n] + cost:
                    return "Negative cost cycle detected!"

        # Find the minimum cost to reach the destination vertex
        min_cost = min(d[end])
        if min_cost == float('inf'):
            return "No path exists between the given vertices."
        return f"The lowest cost walk from {start} to {end} is {min_cost}."


        # if not self._is_vertex(start) or not self._is_vertex(end):
        #     raise ValueError("Invalid vertex index")
        # distance = [float('inf')] * self._size
        # parent = [None] * self._size
        # distance[start] = 0
        #
        # for _ in range(self._size - 1):
        #     for u, v in self._edge_costs:
        #         if distance[u] + self._edge_costs[(u, v)] < distance[v]:
        #             distance[v] = distance[u] + self._edge_costs[(u, v)]
        #             parent[v] = u
        #
        # # Check for negative cycles
        # for u, v in self._edge_costs:
        #     if distance[u] + self._edge_costs[(u, v)] < distance[v]:
        #         raise Exception("Graph contains a negative-weight cycle")
        #
        # # Reconstruct the path
        # path = []
        # current = end
        # while current is not None:
        #     path.append(current)
        #     current = parent[current]
        # path.reverse()
        #
        # return path if path[0] == start else []

    def is_dag(self):
        """
        Checks if the graph is a Directed Acyclic Graph (DAG)
        :return: True if the graph is a DAG, False otherwise
        """
        in_degree = {v: 0 for v in range(self._size)}
        for u in range(self._size):
            for v in self._outbound_list[u]:
                in_degree[v] += 1

        queue = deque()
        for v in range(self._size):
            if in_degree[v] == 0:
                queue.append(v)

        count = 0
        top_order = []

        while queue:
            u = queue.popleft()
            top_order.append(u)
            count += 1

            for v in self._outbound_list[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    queue.append(v)

        return count == self._size, top_order

    def topological_sort(self):
        """
        Performs topological sorting of the graph
        :return: list of vertices in topological order if graph is DAG, None otherwise
        """
        is_dag, top_order = self.is_dag()
        if is_dag:
            print("Topological order:", top_order)
            return top_order
        else:
            print("Graph is not a DAG, cannot perform topological sort")
            return None

    def calculate_earliest_and_latest_start_times(self):
        is_dag, top_order = self.is_dag()
        if not is_dag:
            return None, None, None

        # Initialize earliest start times for all vertices
        earliest_start = {v: 0 for v in range(self._size)}

        # Forward pass to calculate earliest start times
        for u in top_order:
            for v in self._outbound_list[u]:
                duration = self._edge_costs[(u, v)]
                if earliest_start[v] < earliest_start[u] + duration:
                    earliest_start[v] = earliest_start[u] + duration

        total_time = max(earliest_start.values())

        # Initialize latest start times for all vertices
        latest_start = {v: total_time for v in range(self._size)}

        # Backward pass to calculate latest start times
        for u in reversed(top_order):
            for v in self._outbound_list[u]:
                duration = self._edge_costs[(u, v)]
                if latest_start[u] > latest_start[v] - duration:
                    latest_start[u] = latest_start[v] - duration

        return earliest_start, latest_start, total_time

    def get_critical_activities(self):
        """
        Finds all critical activities in the graph
        :return: list of critical activities (edges) as tuples (u, v, duration)
        """
        earliest_start, latest_start, total_time = self.calculate_earliest_and_latest_start_times()
        if earliest_start is None:
            return []

        critical_activities = []
        for u in range(self._size):
            for v in self._outbound_list[u]:
                edge_id = self.get_edge_id(u, v)
                duration = self.get_edge_by_edge_id(edge_id)[2]
                if earliest_start[u] == latest_start[u] and earliest_start[v] == latest_start[v] and earliest_start[v] - \
                        earliest_start[u] == duration:
                    critical_activities.append((u, v, duration))

        return critical_activities

    def add_activity(self, activity):
        """
        Adds an activity (node) to the graph.
        :param activity: The index of the activity to add.
        """
        if activity in self._outbound_list:
            raise ValueError(f"Activity {activity} already exists.")
        if activity >= self._size:
            self._size = activity + 1  # Update the size if the activity index is larger than the current size
        self._outbound_list[activity] = []
        self._inbound_list[activity] = []

    def add_prerequisite(self, prerequisite, activity, duration):
        """
        Adds a prerequisite (edge) to the graph.
        :param prerequisite: The prerequisite activity.
        :param activity: The dependent activity.
        :param duration: The duration of the activity.
        """
        self.add_activity(prerequisite)
        self.add_activity(activity)
        self._outbound_list[prerequisite].append(activity)
        self._inbound_list[activity].append(prerequisite)
        self._edge_costs[(prerequisite, activity)] = duration

    def is_safe(self, vertex, color, colors):
        for neighbor in self._outbound_list[vertex]:
            if colors[neighbor] == color:
                return False
        return True

    def graph_coloring_backtracking(self, m, colors, vertex):
        if vertex == self._size:
            return True

        for color in range(1, m+1):
            if self.is_safe(vertex, color, colors):
                colors[vertex] = color
                if self.graph_coloring_backtracking(m, colors, vertex + 1):
                    return True
                colors[vertex] = 0
        return False

    def find_minimum_colors(self):
        n = self._size
        for m in range(1, n + 1):
            colors = [0] * n
            if self.graph_coloring_backtracking(m, colors, 0):
                return m, colors
        return None, None

    def find_vertex_coloring(self):
        """
        Finds a vertex coloring with minimum number of colors
        :return: list of colors for each vertex
        """
        colors = [-1] * self._size
        available_colors = [True] * self._size
        for vertex in range(self._size):
            # Reset available colors
            for i in range(self._size):
                available_colors[i] = True

            # Check colors of adjacent vertices
            for neighbor in self._outbound_list[vertex]:
                if colors[neighbor] != -1:
                    available_colors[colors[neighbor]] = False

            # Find the first available color
            for color in range(self._size):
                if available_colors[color]:
                    colors[vertex] = color
                    break
        return colors

    def __str__(self):
        string = f'Graph with {self.get_number_of_vertices()} vertices\n'
        for i in range(self._size):
            for j in self._outbound_list[i]:
                string += f'{i} -> {j} with cost {self._edge_costs[(i, j)]}\n'
        return string