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
            if literal.startswith("~"):
                line[variables.index(literal[1:])] = -1
            else:
                line[variables.index(literal)] = 1
        matrix.append(line)

    return matrix
