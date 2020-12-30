from copy import deepcopy
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


def remove_duplicate_rows(matrix):
    """Removes duplicate rows in a matrix"""
    if type(matrix) is not list:
        return matrix
    new_matrix = []
    for line in matrix:
        if line not in new_matrix:
            new_matrix.append(line)
    return new_matrix


def is_matrix(matrix):
    """Checks if argument is matrix"""
    for row in matrix:
        if type(row) is list:
            return True
    return False


class Node:
    def __init__(self, current_formula):
        self.current_formula = current_formula
        self.left = None
        self.right = None

    def evaluate_left(self):
        """Evaluates the current formula when the first variable is False and places the new formula in the left child"""
        formula_copy = deepcopy(self.current_formula)
        left_formula = []
        for clause in formula_copy:
            if len(clause) == 1:    # If the clause contains only one literal, replace the whole clause with it's value (True / False)
                if clause[0] == -1:
                    left_formula.append(True)
                elif clause[0] == 1:
                    left_formula.append(False)
                elif clause[0] == 0:
                    left_formula.append(False)
            # If the first literal in clause is not negated, append the rest of the clause
            elif clause[0] == 1 or clause[0] == 0:
                left_formula.append(clause[1:])

        if left_formula == []:  # If the formula remains empty, it means it is True
            left_formula.append(True)
        # Create the left child with the remaining formula
        self.left = Node(remove_duplicate_rows(left_formula))

    def evaluate_right(self):
        """Evaluates the current formula when the first variable is True and places the new formula in the right child"""
        formula_copy = deepcopy(self.current_formula)
        right_formula = []
        for clause in formula_copy:

            if len(clause) == 1:    # If the clause contains only one literal, replace the whole clause with it's value (True / False)
                if clause[0] == -1:
                    right_formula.append(False)
                elif clause[0] == 1:
                    right_formula.append(True)
                elif clause[0] == 0:
                    right_formula.append(False)
            # If the first literal in clause is negated, append the rest of the clause
            elif clause[0] == -1 or clause[0] == 0:
                right_formula.append(clause[1:])

        if right_formula == []:  # If the formula remains empty, it means it is True
            right_formula.append(True)
        # Create the right child with the remaining formula
        self.right = Node(remove_duplicate_rows(right_formula))


def solver(formula, found_callback, not_found_callback):
    """Checks if a formula is satisfiable and calls the apropriate callback"""

    # Convert the formula into it's matrix form
    variables = extract_variables_from_formula(formula)
    matrix = convert_to_matrix(variables, formula)

    root = Node(matrix)
    is_satisfiable = False

    def dfs(node, depth):
        nonlocal is_satisfiable
        # If the formula is not a matrix anymore, it means it is done with the recursion
        if not is_matrix(node.current_formula):
            if False not in node.current_formula:   # If there is no 'False' in the formula, it's satisfiable
                is_satisfiable = True

        if is_satisfiable == True:
            return

        if depth < len(variables):
            node.evaluate_left()    # Calculate the left child
            node.evaluate_right()   # Calculate the right child

            # Recursive calls to the next level
            dfs(node.left, depth + 1)
            dfs(node.right, depth + 1)

    dfs(root, 0)

    found_callback() if is_satisfiable else not_found_callback()


def found():
    print('1')


def not_found():
    print('0')


def main():
    formula = input()
    solver(formula, found, not_found)


if __name__ == '__main__':
    main()
