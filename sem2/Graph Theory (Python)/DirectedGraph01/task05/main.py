from task05.graph2 import Graph

def read_activities_from_file(file_path, graph):
    """
    Reads activities, durations, and prerequisites from a file and builds the graph.
    :param file_path: Path to the input file.
    :param graph: The graph object to populate.
    """
    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines[1:]:  # Skip the header
            parts = line.strip().split(',')
            activity = int(parts[0].strip())
            duration = int(parts[1].strip())
            prerequisites = parts[2].strip().split() if parts[2].strip() else []

            for prereq in prerequisites:
                graph.add_prerequisite(int(prereq), activity, duration)

if __name__ == "__main__":
    # Create a new graph instance
    graph = Graph()

    # Read activities and prerequisites from the input file
    input_file = "activities.txt"
    read_activities_from_file(input_file, graph)

    # Print the graph
    print("Graph structure:")
    graph.print_graph()

    # Check if the graph is a DAG
    if graph.is_dag():
        print("\nThe graph is a Directed Acyclic Graph (DAG).")
    else:
        print("\nThe graph is not a DAG.")

    # Perform topological sorting
    top_order = graph.topological_sort()
    if top_order:
        print("\nTopological order of the graph:")
        print(top_order)
    else:
        print("\nTopological sorting is not possible (graph is not a DAG).")

    # Calculate earliest and latest start times
    earliest_start, latest_start, total_time = graph.calculate_earliest_and_latest_start_times()
    if earliest_start and latest_start:
        print("\nEarliest start times:")
        print(earliest_start)
        print("\nLatest start times:")
        print(latest_start)
        print(f"\nTotal project time: {total_time}")

    # Get critical activities
    critical_activities = graph.get_critical_activities()
    print("\nCritical activities (edges):")
    for u, v, duration in critical_activities:
        print(f"{u} -> {v} with duration {duration}")

    # TODO: Assignment 3)