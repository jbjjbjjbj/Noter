import Data.Maybe

-- Probably not the fastest way
ones :: Integral a => [a]
ones = 1 : ones

allnums :: Integral a => [a]
allnums = 0 : zipWith (+) allnums ones

threes :: Integral a => [a]
threes = filter ((==0) . flip rem 3) allnums 

data Doll = Shell Doll | Infant

size' :: Doll -> Int
size' Infant = 1
size' (Shell d) = 1 + size' d

yeahVeryCool = size' . Shell . Shell . Shell $ Infant

data BExp = BTrue | BFalse | Or BExp BExp | And BExp BExp | Not BExp

yoyo = Not (Or (And BTrue BFalse) BTrue)

eval' :: BExp -> Bool
eval' BTrue = True
eval' BFalse = False
eval' (Not e) = not . eval' $ e
eval' (And a b) = eval' a && eval' b
eval' (Or a b) = eval' a || eval' b


perfectSq = flip take [x * x | x <- [0..]]
-- Alternative
perfectSq' n = [x * x | x <- [0..n]]

isprime :: Integral a => a -> Bool
isprime x = not . any ((==0) . rem x) $ [2..(x-1)]
isprime' x = null [x | n <- [2..(x-1)], rem x n == 0]

data Nat = Zero | Suc Nat

nat2int :: Nat -> Int
nat2int Zero = 0
nat2int (Suc n) = 1 + nat2int n

int2nat :: Int -> Nat
int2nat 0 = Zero
int2nat x | x > 0 = Suc . int2nat $ (x-1)
          | otherwise = Zero

fibs :: [Int]
fibs = 1 : 1 : fibsfunc 1 1
  -- from lastlast and last (sorry)
  where fibsfunc ll l = e : fibsfunc l e
          where e = l + ll


fib :: Int -> [Int]
fib = flip take fibs

data Tree a = Leaf a | Node (Tree a) (Tree a)

mzipThing :: (a -> b -> Maybe c) -> Maybe a -> Maybe b -> Maybe c
mzipThing _ Nothing _ = Nothing
mzipThing _ _ Nothing = Nothing
mzipThing func (Just a) (Just b) = func a b

nodeCompare :: Int -> Int -> Maybe Int
nodeCompare a b | a == b = Just (a+1)
          | otherwise = Nothing

balancedWithLen :: Tree a -> Maybe Int
balancedWithLen (Leaf _) = Just 0
balancedWithLen (Node a b) = mzipThing nodeCompare (balancedWithLen a) (balancedWithLen b)

balanced :: Tree a -> Bool
balanced = isJust . balancedWithLen
 
notCoolTree = Node (Node (Leaf 1) (Node (Leaf 1) (Leaf 1))) (Leaf 1)
coolTree = Node (Leaf 1) (Leaf 1)


any' :: (a -> Bool) -> [a] -> Bool
any' _ [] = False
any' func (x:xs) = func x || any' func xs

anyWithFold :: (a -> Bool) -> [a] -> Bool
anyWithFold func = foldl (\x y -> x || func y) False

filterWithFold :: (a -> Bool) -> [a] -> [a]
filterWithFold func = foldr (\new pre -> if func new
                                            then new:pre
                                            else pre
                            ) []

