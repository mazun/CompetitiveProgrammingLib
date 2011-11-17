import Data.Bits

popCount :: (Bits a, Num t) => a -> t
popCount x = popCount' x 0
  where
    popCount' 0 a = a
    popCount' x a = let b  = x .&. (-x)
                        xx = x `xor` b
                    in popCount' xx (a + 1)

-- 1 => [0], 3 => [1, 0], 5 => [2, 0], 0 => []
bit2lst :: Bits a => a -> [Int]
bit2lst x = bit2lst' x 0 []
  where
    bit2lst' 0 i a = a
    bit2lst' x i a = let ii = shiftL 1 i
                     in if (x .&. ii) == 0
                        then bit2lst' x (i + 1) a
                        else bit2lst' (x `xor` ii) (i + 1) (i:a)

-- elem i bit2lst
bitOf :: Bits a => a -> Int -> Bool
bitOf x i = (x .&. (shiftL 1 i)) /= 0
