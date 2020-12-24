from formula_parser import extract_variables_from_formula, convert_to_matrix
from copy import deepcopy


def remove_duplicate_rows(matrix):
    if type(matrix) is not list:
        return matrix
    new_matrix = []
    for line in matrix:
        if line not in new_matrix:
            new_matrix.append(line)
    return new_matrix


def matrix_contains_lists(matrix):
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
        formula_copy = deepcopy(self.current_formula)
        left_formula = []
        for clause in formula_copy:
            if type(clause) is not list:
                continue

            if len(clause) == 1:
                if clause[0] == -1:
                    left_formula.append(True)
                elif clause[0] == 1:
                    left_formula.append(False)
                elif clause[0] == 0:
                    left_formula.append(False)
            elif clause[0] == 1 or clause[0] == 0:
                left_formula.append(clause[1:])

        if left_formula == []:
            left_formula.append(True)
        self.left = Node(remove_duplicate_rows(left_formula))

    def evaluate_right(self):
        formula_copy = deepcopy(self.current_formula)
        right_formula = []
        for clause in formula_copy:
            if type(clause) is not list:
                continue
            if len(clause) == 1:
                if clause[0] == -1:
                    right_formula.append(False)
                elif clause[0] == 1:
                    right_formula.append(True)
                elif clause[0] == 0:
                    right_formula.append(False)
            elif clause[0] == -1 or clause[0] == 0:
                right_formula.append(clause[1:])

        if right_formula == []:
            right_formula.append(True)
        self.right = Node(remove_duplicate_rows(right_formula))


def solver(formula, found_callback, not_found_callback):
    variables = extract_variables_from_formula(formula)
    matrix = convert_to_matrix(variables, formula)

    root = Node(matrix)
    is_satisfiable = False

    def dfs(node, depth):
        nonlocal is_satisfiable
        if not matrix_contains_lists(node.current_formula):
            if False not in node.current_formula:
                is_satisfiable = True

        if is_satisfiable == True:
            return

        if depth < len(variables):
            node.evaluate_left()
            node.evaluate_right()

            dfs(node.left, depth + 1)
            dfs(node.right, depth + 1)

    dfs(root, 0)

    found_callback() if is_satisfiable else not_found_callback()
