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


with open("input.txt") as f:
    formula = f.read()
    matrix = convert_to_matrix(formula)
    print(matrix)
