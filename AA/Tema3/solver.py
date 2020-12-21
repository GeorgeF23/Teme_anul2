def extract_variables_from_formula(formula):
    return list(set([variable.replace('~', '') for sublist in [literal.split("V") for literal in [clause[1:-1] for clause in formula.split("^")]] for variable in sublist]))

def convert_to_matrix(formula):
    matrix = []
    variables = extract_variables_from_formula(formula)

    clauses = formula.split("^")
    for clause in clauses:
        line = [0] * len(variables)
        for literal in clause[1:-1].split("V"):
            if(literal.startswith("~")):
                line[variables.index(literal[1:])] = -1
            else:
                line[variables.index(literal)] = 1
        matrix.append(line)

    return matrix


def solver(formula):
    variables = extract_variables_from_formula(formula)

    def backtracking(s, index):
        
        print(s)

        for i in range(index, len(variables)):
            s.append(variables[i])
            backtracking(s, i + 1)
            s.pop()

    backtracking([], 0)


with open("input.txt") as f:
    formula = f.read()
    matrix = convert_to_matrix(formula)
    solver(formula)
