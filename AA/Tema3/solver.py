import re


def extract_variables_from_formula(formula):
    return list(
        set(
            [variable.replace('~', '')
             for sublist
             in [literal.split("V")
                 for literal in
                 [re.sub("[()]", "", clause)
                  for clause in
                  formula.split("^")]] for
             variable in sublist]
        )
    )


def convert_to_matrix(variables, formula):
    matrix = []

    clauses = formula.split("^")
    for clause in clauses:
        line = [0] * len(variables)
        for literal in re.sub("[()]", "", clause).split("V"):
            if(literal.startswith("~")):
                line[variables.index(literal[1:])] = -1
            else:
                line[variables.index(literal)] = 1
        matrix.append(line)

    return matrix


def solver(formula, found_callback, not_found_callback):
    variables = extract_variables_from_formula(formula)
    matrix = convert_to_matrix(variables, formula)

    found = False

    def check_clause(clause, interpretation):
        for literal_index, literal_value in enumerate(clause):
            if literal_value == 1 and variables[literal_index] in interpretation:
                return True
            elif literal_value == -1 and variables[literal_index] not in interpretation:
                return True
        return False

    def check_interpretation(interpretation):
        for clause in matrix:
            if not check_clause(clause, interpretation):
                return False
        return True

    def backtracking(s, index):
        nonlocal found
        if found:
            return
        if check_interpretation(s):
            found = True
        for i in range(index, len(variables)):
            s.append(variables[i])
            backtracking(s, i + 1)
            s.pop()

    backtracking([], 0)

    found_callback() if found else not_found_callback()


def found_interpretation():
    print("Found interpretation")


def not_found_interpretation():
    print("Not found")


with open("input.txt") as f:
    formula = f.read()
    solver(formula, found_interpretation, not_found_interpretation)
