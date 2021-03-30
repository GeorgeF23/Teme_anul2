{-
	PP Project 2021

	This is where you will write the implementation for the given tasks.
	You can add other modules aswell.
-}

module Tasks where

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
compute_exam_grades = (["Nume","Punctaj Exam"] :) . map (\line -> head line : [show $ compute_one_exam_grade $ tail line]) . tail 


-- Primeste lista de note si returneaza nota finala din examen
compute_one_exam_grade :: Row -> Float
compute_one_exam_grade = foldr (\el acc -> if acc == (-1) then string_to_float el else string_to_float el / 4 + acc) (-1)

-- Task 2
-- Number of students who have passed the exam:
get_passed_students_num :: Table -> Int
get_passed_students_num = undefined

-- Percentage of students who have passed the exam:
get_passed_students_percentage :: Table -> Float
get_passed_students_percentage = undefined

-- Average exam grade
get_exam_avg :: Table -> Float
get_exam_avg = undefined

-- Number of students who gained at least 1.5p from homework:
get_passed_hw_num :: Table -> Int
get_passed_hw_num = undefined

-- Task 3
get_avg_responses_per_qs :: Table -> Table
get_avg_responses_per_qs = undefined

-- Task 4
get_exam_summary :: Table -> Table
get_exam_summary = undefined

-- Task 5
get_ranking :: Table -> Table
get_ranking = undefined

-- Task 6
get_exam_diff_table :: Table -> Table
get_exam_diff_table = undefined
