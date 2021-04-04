module MyUtils(string_to_float, string_to_integer, increment_field, float_to_string) where

import Text.Printf

string_to_float :: String -> Float
string_to_float str = if null str then 0.0 else read str :: Float

string_to_integer :: String -> Integer
string_to_integer str = if null str then 0 else read str :: Integer

float_to_string :: Float -> String
float_to_string = printf "%.2f"


increment_field :: Int -> [Integer] -> [Integer]
increment_field field_no list = take field_no list ++ [list !! max 0 field_no + 1] ++ drop (min (length list) field_no + 1) list
