import Data.Array

make2DArray :: [[a]] -> Array (Int, Int) a
make2DArray lst = let len1 = (length lst) - 1
                      len2 = (length $ lst !! 0) - 1
                  in  array ((0, 0), (len1, len2))
                    [ ((i, j), (lst !! i) !! j) | i <- [0..len1], j <- [0..len2] ]
