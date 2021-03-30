module MyUtils(string_to_float) where

string_to_float :: String -> Float
string_to_float str = if null str then 0.0 else read str :: Float