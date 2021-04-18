module MyUtils(string_to_float, string_to_integer, increment_field, float_to_string, get_column_index) where

import Text.Printf
import Data.Maybe
import Data.List

-- Converts string to float
string_to_float :: String -> Float
string_to_float str = if null str then 0.0 else read str :: Float

-- Converts string to integer
string_to_integer :: String -> Integer
string_to_integer str = if null str then 0 else read str :: Integer

-- Converts float to string with 2 decimal
float_to_string :: Float -> String
float_to_string = printf "%.2f"

-- Increments the field from the index 'field_no' from a list of integers
increment_field :: Int -> [Integer] -> [Integer]
increment_field field_no list = take field_no list ++ [list !! max 0 field_no + 1] ++ drop (min (length list) field_no + 1) list

get_column_index :: (Eq a) => a -> [a] -> Int
get_column_index column row = fromJust $ elemIndex column row