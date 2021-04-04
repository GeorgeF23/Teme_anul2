{-
	PP Project 2021

	This is where you will write the implementation for the given tasks.
	You can add other modules aswell.
-}

module Tasks where

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
get_avg_responses_per_qs grades = ["Q1","Q2","Q3","Q4","Q5","Q6"] : [map (float_to_string . (/ (fromIntegral $ length $ tail grades))) (foldl (zipWith (+)) [0.0, 0.0, 0.0, 0.0, 0.0, 0.0] $ map( map string_to_float . take 6 . tail) $ tail grades)]

-- Task 4
-- get_exam_summary :: Table -> Table
get_exam_summary = construct_table . foldl (zipWith increment_question_numbers) [[0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0], [0, 0, 0]] . map( map string_to_integer . take 6 . tail) . tail
    where
        increment_question_numbers :: [Integer] -> Integer -> [Integer]
        increment_question_numbers acc question_points
            | question_points == 0 = increment_field 0 acc
            | question_points == 1 = increment_field 1 acc
            | otherwise = increment_field 2 acc

        construct_table :: [[Integer]] -> Table
        construct_table = (["Q","0","1","2"] :) . zipWith (:) ["Q1", "Q2", "Q3", "Q4", "Q5", "Q6"] . map (map show)


-- Task 5
-- get_ranking :: Table -> Table
get_ranking = (["Nume","Punctaj Exam"] :) . sortBy cmp . tail . compute_exam_grades
    where
        cmp :: Row -> Row -> Ordering
        cmp entry1 entry2
            | entry1 !! 1 < entry2 !! 1 = LT
            | entry1 !! 1 == entry2 !! 1 = if head entry1 < head entry2 then LT else GT
            | otherwise = GT

-- Task 6
get_exam_diff_table :: Table -> Table
get_exam_diff_table = (["Nume","Punctaj interviu","Punctaj scris","Diferenta"] :) . sortBy cmp . map ((\line -> line ++ [float_to_string $ abs (string_to_float (line !! 1) - string_to_float (line !! 2))]) . (\line -> head line : float_to_string (compute_one_interview_exam_grade $ tail line) : [float_to_string $ string_to_float (line !! 7)])) . tail
    where
        cmp :: Row -> Row -> Ordering
        cmp entry1 entry2
            | entry1 !! 3 < entry2 !! 3 = LT
            | entry1 !! 3 == entry2 !! 3 = if head entry1 < head entry2 then LT else GT
            | otherwise = GT
