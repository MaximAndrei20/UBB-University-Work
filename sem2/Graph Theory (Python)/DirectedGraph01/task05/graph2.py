class Graph:
    def __init__(self):
        self._outbound_list = {}
        self._inbound_list = {}
        self._edge_costs = {}
        self._size = 0

    def add_vertex(self):
        """
        Adds a new vertex to the graph.
        """
        self._outbound_list[self._size] = []
        self._inbound_list[self._size] = []
        self._size += 1

    def add_edge(self, start, end, cost):
        """
        Adds a directed edge with a cost between two vertices.
        :param start: Starting vertex.
        :param end: Ending vertex.
        :param cost: Cost of the edge.
        """
        if start not in self._outbound_list or end not in self._inbound_list:
            raise ValueError("Invalid vertices.")
        self._outbound_list[start].append(end)
        self._inbound_list[end].append(start)
        self._edge_costs[(start, end)] = cost

    def add_activity(self, activity):
        """
        Adds an activity (node) to the graph.
        :param activity: The index of the activity to add.
        """
        if activity not in self._outbound_list:
            self._outbound_list[activity] = []
            self._inbound_list[activity] = []
            self._size = max(self._size, activity + 1)

    def add_prerequisite(self, prerequisite, activity, duration):
        """
        Adds a prerequisite (edge) to the graph.
        :param prerequisite: The prerequisite activity.
        :param activity: The dependent activity.
        :param duration: The duration of the activity.
        """
        self.add_activity(prerequisite)
        self.add_activity(activity)
        self.add_edge(prerequisite, activity, duration)

    def is_dag(self):
        """
        Checks if the graph is a Directed Acyclic Graph (DAG).
        :return: True if the graph is a DAG, False otherwise.
        """
        in_degree = {v: 0 for v in self._outbound_list}
        for u in self._outbound_list:
            for v in self._outbound_list[u]:
                in_degree[v] += 1

        queue = [v for v in in_degree if in_degree[v] == 0]
        count = 0

        while queue:
            u = queue.pop(0)
            count += 1
            for v in self._outbound_list[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    queue.append(v)

        return count == self._size

    def topological_sort(self):
        """
        Performs topological sorting of the graph.
        :return: List of vertices in topological order if the graph is a DAG, None otherwise.
        """
        if not self.is_dag():
            return None

        in_degree = {v: 0 for v in self._outbound_list}
        for u in self._outbound_list:
            for v in self._outbound_list[u]:
                in_degree[v] += 1

        queue = [v for v in in_degree if in_degree[v] == 0]
        top_order = []

        while queue:
            u = queue.pop(0)
            top_order.append(u)
            for v in self._outbound_list[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    queue.append(v)

        return top_order

    def calculate_earliest_and_latest_start_times(self):
        """
        Calculates the earliest and latest start times for each activity.
        :return: Earliest start times, latest start times, and total project time.
        """
        top_order = self.topological_sort()
        if not top_order:
            return None, None, None

        earliest_start = {v: 0 for v in self._outbound_list}
        for u in top_order:
            for v in self._outbound_list[u]:
                duration = self._edge_costs[(u, v)]
                earliest_start[v] = max(earliest_start[v], earliest_start[u] + duration)

        total_time = max(earliest_start.values())

        latest_start = {v: total_time for v in self._outbound_list}
        for u in reversed(top_order):
            for v in self._outbound_list[u]:
                duration = self._edge_costs[(u, v)]
                latest_start[u] = min(latest_start[u], latest_start[v] - duration)

        return earliest_start, latest_start, total_time

    def get_critical_activities(self):
        """
        Finds all critical activities in the graph.
        :return: List of critical activities (edges) as tuples (u, v, duration).
        """
        earliest_start, latest_start, _ = self.calculate_earliest_and_latest_start_times()
        if earliest_start is None:
            return []

        critical_activities = []
        for u in self._outbound_list:
            for v in self._outbound_list[u]:
                duration = self._edge_costs[(u, v)]
                if earliest_start[u] == latest_start[u] and earliest_start[v] - earliest_start[u] == duration:
                    critical_activities.append((u, v, duration))

        return critical_activities

    def print_graph(self):
        """
        Prints the graph in a readable format.
        """
        print(f"Graph with {self._size} vertices:")
        for u in self._outbound_list:
            for v in self._outbound_list[u]:
                cost = self._edge_costs[(u, v)]
                print(f"{u} -> {v} with cost {cost}")