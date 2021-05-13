{-
	PP Project 2021

	This is where you will write the implementation for the given tasks.
	You can add other modules aswell.
-}

{-# LANGUAGE ExistentialQuantification #-}
{-# LANGUAGE FlexibleInstances #-}

module Tasks where

import Data.Maybe
import Data.List

import Dataset
import MyUtils

type CSV = String
type Value = String
type Row = [Value]
type Table = [Row]

{-
	TASK SET 1
-}

-- Task 1
compute_exam_grades :: Table -> Table
compute_exam_grades = (["Nume","Punctaj Exam"] :) . map (\line -> head line : [float_to_string $ compute_one_exam_grade $ tail line]) . tail


-- Primeste lista de note si returneaza nota finala din examen
compute_one_exam_grade :: Row -> Float
compute_one_exam_grade exam_grade = compute_one_interview_exam_grade exam_grade + string_to_float (last exam_grade)

-- Primeste lista de note si returneaza nota examenului interviu
compute_one_interview_exam_grade :: Row -> Float
compute_one_interview_exam_grade = (/ 4) . sum . map string_to_float . take 6

-- Task 2
-- Number of students who have passed the exam:
get_passed_students_num :: Table -> Int
get_passed_students_num = length . filter studentPassed . tail . compute_exam_grades
    where
        studentPassed :: Row -> Bool
        studentPassed = (>= 2.5) . string_to_float . head . tail


-- Percentage of students who have passed the exam:
get_passed_students_percentage :: Table -> Float
get_passed_students_percentage grades = fromIntegral (get_passed_students_num grades) / fromIntegral (length (tail grades))

-- Average exam grade
get_exam_avg :: Table -> Float
get_exam_avg grades = sum (map (compute_one_exam_grade . tail) $ tail grades) / fromIntegral (length $ tail grades)

-- Number of students who gained at least 1.5p from homework:
get_passed_hw_num :: Table -> Int
get_passed_hw_num = length . filter (>= 1.5) . map (sum . map string_to_float . take 3 . tail . tail) . tail

-- Task 3
get_avg_responses_per_qs :: Table -> Table
get_avg_responses_per_qs grades = ["Q1","Q2","Q3","Q4","Q5","Q6"] :
    [map (float_to_string . (/ (fromIntegral $ length $ tail grades)))
        (foldl (zipWith (+)) [0.0, 0.0, 0.0, 0.0, 0.0, 0.0] $ map( map string_to_float . take 6 . tail) $ tail grades)]

-- Task 4
get_exam_summary :: Table -> Table
get_exam_summary = construct_table .
    -- foldl-ul are ca acumulator o lista de lista in care sunt tinute punctajele de la fiecare intrebare
    -- zipWith-ul executa functia 'increment_question_numbers' intre fiecare punctaj al fiecarei intrebari si lista din acumulator corespunzatoare intrebarii
    foldl (zipWith increment_question_numbers) [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]] .
    map( map string_to_integer . take 6 . tail) .   -- extrage doar punctajele intrbarilor de la examenul interviu
    tail
    where
        {-
            Incrementeaza campul corespunzator intrebarii in functie de punctajul primit

            acc                     lista de 3 elemente unde sunt contorizate punctajele unei intrebari
            question_points         punctajul obtinut la intrebare
        -}

        increment_question_numbers :: [Integer] -> Integer -> [Integer]
        increment_question_numbers acc question_points
            | question_points == 0 = increment_field 0 acc
            | question_points == 1 = increment_field 1 acc
            | otherwise = increment_field 2 acc

        -- Converteste toate elementele din tabel la String si adauga campurile necesare afisarii
        construct_table :: [[Integer]] -> Table
        construct_table = (["Q","0","1","2"] :) . zipWith (:) ["Q1", "Q2", "Q3", "Q4", "Q5", "Q6"] . map (map show)


-- Task 5
get_ranking :: Table -> Table
get_ranking = (["Nume","Punctaj Exam"] :) . sortBy cmp . tail . compute_exam_grades
    where
        cmp :: Row -> Row -> Ordering
        cmp entry1 entry2
            | entry1 !! 1 < entry2 !! 1 = LT
            | entry1 !! 1 == entry2 !! 1 = if head entry1 < head entry2 then LT else GT
            | otherwise = GT

-- Task 6
get_exam_diff_table :: Table -> Table
get_exam_diff_table = (["Nume","Punctaj interviu","Punctaj scris","Diferenta"] :) .
    sortBy cmp .
    map ((\line -> line ++ [float_to_string $ abs (string_to_float (line !! 1) - string_to_float (line !! 2))]) .
        (\line -> head line : float_to_string (compute_one_interview_exam_grade $ tail line) : [float_to_string $ string_to_float (line !! 7)])) .
    tail
    where
        cmp :: Row -> Row -> Ordering
        cmp entry1 entry2
            | entry1 !! 3 < entry2 !! 3 = LT
            | entry1 !! 3 == entry2 !! 3 = if head entry1 < head entry2 then LT else GT
            | otherwise = GT


{-
	TASK SET 2
-}

read_csv :: CSV -> Table
read_csv = map (splitOn ',') . splitOn '\n'

write_csv :: Table -> CSV
write_csv = tail . concatMap ((++) "\n" . tail . foldr (\el acc -> "," ++ el ++ acc) "")

-- Task 1
as_list :: String -> Table -> [String]
as_list column table = tail $ map (\row -> row !! get_element_index column (head table)) table

-- Task 2
tsort :: String -> Table -> Table
tsort column table = head table : sortBy cmp (tail table)
    where
        cmp :: Row -> Row -> Ordering
        cmp row1 row2
            | row1 !! get_element_index column (head table) == "" && row2 !! get_element_index column (head table) /= "" = LT
            | row1 !! get_element_index column (head table) /= "" && row2 !! get_element_index column (head table) == "" = GT
            | string_to_float (row1 !! get_element_index column (head table)) > string_to_float (row2 !! get_element_index column (head table)) = GT
            | string_to_float (row1 !! get_element_index column (head table)) < string_to_float (row2 !! get_element_index column (head table)) = LT
            | otherwise = if head row1 > head row2 then GT else LT

-- Task 3
vmap :: (Value -> Value) -> Table -> Table
vmap op = map (map op)

-- Task 4
rmap :: (Row -> Row) -> [String] -> Table -> Table
rmap op new_columns = (:) new_columns . map op . tail

get_hw_grade_total :: Row -> Row
get_hw_grade_total row = [head row, float_to_string $ sum $ map string_to_float $ tail $ tail row]

-- Task 5
vunion :: Table -> Table -> Table
vunion table1 table2 = if head table1 == head table2 then table1 ++ tail table2 else table1

-- Task 6
hunion :: Table -> Table -> Table
hunion table1 table2 = if length table1 > length table2 then
                            zipWith (++) table1 (extend_tables table1 table2) else
                            zipWith (++) (extend_tables table2 table1) table2
    where
        -- If a table has less rows than the other one, add rows with empty strings to it
        extend_tables :: Table -> Table -> Table
        extend_tables big_table small_table = small_table ++ replicate (length big_table - length small_table) (replicate (length $ head small_table) "")

-- Task 7
tjoin :: String -> Table -> Table -> Table
tjoin column table1 table2 = map join table1
    where
        -- If there is a matching row in the second table, append it to row1 else add empty string to row1
        join :: Row -> Row
        join row1 = if null (get_matching_row row1 table2) then
            extend_row (length (head table2) - 1) row1 else
            row1 ++ remove_element_at_index (get_element_index column (head table2)) (get_matching_row row1 table2)

        -- Returns the matching row in the second table or empty list if not found
        get_matching_row :: Row -> Table -> Row
        get_matching_row row1 table2 = if not (any (matching_rows row1) table2) then [] else head $ filter (matching_rows row1) table2

        -- Checks if two rows have the same key value
        matching_rows :: Row -> Row -> Bool
        matching_rows row1 row2 = row1 !! get_element_index column (head table1) == row2 !! get_element_index column (head table2)

        -- Creates a list of empty strings
        extend_row :: Int -> Row -> Row
        extend_row additional_values row = row ++ replicate additional_values ""

-- Task 8
cartesian :: (Row -> Row -> Row) -> [String] -> Table -> Table -> Table
cartesian op columns table1 table2 = columns : aux op (tail table1) (tail table2)
    where
        aux :: (Row -> Row -> Row) -> Table -> Table -> Table
        aux op [] _ = []
        aux op (x:xs) [] = aux op xs (tail table2)
        aux op (x:xs) (y:ys) = if null (op x y) then aux op (x:xs) ys else op x y : aux op (x:xs) ys

-- Task 9
projection :: [String] -> Table -> Table
projection columns table = map extract_columns table
    where
        extract_columns :: Row -> Row
        extract_columns row = map (\column -> row !! get_element_index column (head table)) columns

{-
	TASK SET 3
-}

data Query =
    FromCSV CSV
    | ToCSV Query
    | AsList String Query
    | Sort String Query
    | ValueMap (Value -> Value) Query
    | RowMap (Row -> Row) [String] Query
    | VUnion Query Query
    | HUnion Query Query
    | TableJoin String Query Query
    | Cartesian (Row -> Row -> Row) [String] Query Query
    | Projection [String] Query
    | forall a. FEval a => Filter (FilterCondition a) Query
    | Graph EdgeOp Query

type EdgeOp = Row -> Row -> Maybe Value
data QResult = CSV CSV | Table Table | List [String]

data FilterCondition a =
    Eq String a |
    Lt String a |
    Gt String a |
    In String [a] |
    FNot (FilterCondition a) |
    FieldEq String String

type FilterOp = Row -> Bool

class Eval a where
    eval :: a -> QResult

class FEval a where
    feval :: [String] -> FilterCondition a -> FilterOp

-- Task 3.1
instance Show QResult where
    show (Table table) = write_csv table
    show (CSV csv) = show csv
    show (List list) = show list

-- Task 3.2
instance Eval Query where
    eval (FromCSV csv) = Table $ read_csv csv
    eval (ToCSV query) = CSV $ show $ eval query
    eval (AsList colname query) = List $ as_list colname $ read_csv $ show $ eval query
    eval (Sort colname query) = Table $ tsort colname $ read_csv $ show $ eval query
    eval (ValueMap op query) = Table $ vmap op $ read_csv $ show $ eval query
    eval (RowMap op colnames query) = Table $ rmap op colnames $ read_csv $ show $ eval query
    eval (VUnion query1 query2) = Table $ vunion (read_csv $ show $ eval query1) (read_csv $ show $ eval query2)
    eval (HUnion query1 query2) = Table $ hunion (read_csv $ show $ eval query1) (read_csv $ show $ eval query2)
    eval (TableJoin colname query1 query2) = Table $ tjoin colname (read_csv $ show $ eval query1) (read_csv $ show $ eval query2)
    eval (Cartesian op colnames query1 query2) = Table $ cartesian op colnames (read_csv $ show $ eval query1) (read_csv $ show $ eval query2)
    eval (Projection colnames query) = Table $ projection colnames (read_csv $ show $ eval query)
    eval (Filter cond query) = Table $ aux (read_csv $ show $ eval query)
        where
            aux :: Table -> Table
            aux table = head table : filter (feval (head table) cond) (tail table)
    eval (Graph op query) = Table $ (:) ["From", "To", "Value"] $ process_pairs $ generate_pairs (read_csv $ show $ eval query)
        where
            -- Generates all possible pairs of rows
            generate_pairs :: Table -> [(Row, Row)]
            generate_pairs table = [(row1, row2) | row1 <- tail table, row2 <- tail table, row1 /= row2]

            -- Converts the pair of rows into the graph
            process_pairs :: [(Row, Row)] -> Table
            process_pairs pairs = nub $ filter (not . null) $ map (\(row1, row2) -> check_graphop_result row1 row2 (op row1 row2)) pairs
                where
                    check_graphop_result :: Row -> Row -> Maybe Value -> Row
                    check_graphop_result row1 row2 (Just val) = if head row1 < head row2 then [head row1, head row2, val] else [head row2, head row1, val]
                    check_graphop_result row1 row2 Nothing = []


-- Task 3.3
instance FEval Float where
    feval colnames (Eq colname value) = \row -> string_to_float (row !! get_element_index colname colnames) == value
    feval colnames (Gt colname value) = \row -> string_to_float (row !! get_element_index colname colnames) > value
    feval colnames (Lt colname value) = \row -> string_to_float (row !! get_element_index colname colnames) < value
    feval colnames (In colname values) = \row -> list_contains_element (string_to_float $ row !! get_element_index colname colnames) values
    feval colnames (FNot cond) = not . feval colnames cond
    feval colnames (FieldEq col1 col2) = \row -> (row !! get_element_index col1 colnames) == (row !! get_element_index col2 colnames)


instance FEval String where
    feval colnames (Eq colname value) = \row -> (row !! get_element_index colname colnames) == value
    feval colnames (Gt colname value) = \row -> (row !! get_element_index colname colnames) > value
    feval colnames (Lt colname value) = \row -> (row !! get_element_index colname colnames) < value
    feval colnames (In colname values) = \row -> list_contains_element (row !! get_element_index colname colnames) values
    feval colnames (FNot cond) = not . feval colnames cond
    feval colnames (FieldEq col1 col2) = \row -> (row !! get_element_index col1 colnames) == (row !! get_element_index col2 colnames)

-- Task 3.6
similarities_query :: Query
similarities_query = Sort "Value" $ Graph graphop $ Filter (FNot (Eq "Email" "")) $ FromCSV lecture_grades_csv
    where
        -- The graph operation that checks if two students have a distance greater than 5
        graphop :: Row -> Row -> Maybe Value
        graphop row1 row2 = if get_matching_points row1 row2 >= 5 then Just (show $ get_matching_points row1 row2) else Nothing

        -- Counts the number of questions with the same result
        get_matching_points :: Row -> Row -> Integer
        get_matching_points row1 row2 = sum $ zipWith (\value1 value2 -> if value1 == value2 then 1 else 0) (tail row1) (tail row2)