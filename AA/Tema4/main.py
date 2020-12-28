class Graph:
    def __init__(self, vertex_number, edges_number, edges):
        self.vertex_number = vertex_number
        self.edges_number = edges_number
        self.edges = edges

def get_variable_matrix(k, graph):
    """Generate a graph.vertex_number by k matrix that store the name of the variable in the formula"""
    X = []
    var_number = 1
    for i in range(graph.vertex_number):
        line = []
        for j in range(k):
            line.append(var_number)
            var_number += 1
        X.append(line)
    return X


# Every slot must be occupied
def generate_first_condition(X, k, graph):
    formula = ""
    for j in range(k):
        clause = "("
        for i in range(graph.vertex_number):
            clause += str(X[i][j]) + "V"
        clause = clause[:-1]
        clause += ")"
        formula += clause + "^"
    return formula[0:-1]


# No node can appear in more than one slot
def generate_second_condition(X, k, graph):
    formula = ""
    for i in range(graph.vertex_number):
        for j in range(k-1):
            clause = "("
            for l in range(j + 1, k):
                clause += '~' + str(X[i][j]) + 'V' + '~' + str(X[i][l]) + 'V'
            clause = clause[:-1]
            clause += ")"
            formula += clause + "^"
    return formula[:-1]

# The nodes must generate a k vertex cover
def generate_third_condition(X, k, graph):
    formula = ""
    for edge in graph.edges:
        clause = "("
        for vertex in edge:
            for i in range(k):
                clause += str(X[vertex - 1][i]) + 'V'
        clause = clause[:-1]
        clause += ')'
        formula += clause + '^'
    return formula[:-1]

# Two vertices can not occupy the same slot
def generate_fourth_condition(X, k, graph):
    formula = ""
    for i in range(k):
        for j in range(graph.vertex_number-1):
            for l in range(j + 1, graph.vertex_number):
                formula += '(~' + str(X[j][i]) + 'V' + '~' + str(X[l][i]) + ')^'
    return formula[:-1]


def transform(k, graph):
    X = get_variable_matrix(k, graph)   # Matrix that stores the selected vertices and their slots
    formula = ""
    # Append the clauses generated by each condition
    formula += generate_first_condition(X, k, graph)
    formula += "^"
    formula += generate_second_condition(X, k, graph)
    formula += "^"
    formula += generate_third_condition(X, k, graph)
    formula += "^"
    formula += generate_fourth_condition(X, k, graph)

    return formula


def main():
    # Read the input data
    k = int(input())
    vertex_number = int(input())
    edges_number = int(input())
    edges = []
    for i in range(edges_number):
        edge_string = input()
        edges.append(tuple([int(vertex) for vertex in edge_string.split(' ')]))

    print(transform(k, Graph(vertex_number, edge_string, edges)))   # Prints the final formula


if __name__ == "__main__":
    main()
