import Data.Set (Set, empty, member, insert)

-- Opgaver før lecture
sum' x | x > 0 = x + sum' (x-1)
       | otherwise = 0

flip' = map (\(x, y) -> (y, x))
-- Here i would guess that the type is [(a, b)] -> [(b, a)]
-- When quering i get flip' :: [(b, a)] -> [(a, b)]
-- Yeah they are the same


-- I would say the type of fib is (Eq a, Num a, Num b) => a -> b
-- Okay det vil nok være bedre at bruge Integral, eftersom fib tal kun er integer

fib 0 = 1
fib 1 = 1
fib n = fib (n-1) + fib (n-2)


-- I would say that the complexity is O(2^n), because we apply
-- fib two times for every invocation of fib.
-- Which does kind of suck

reverse' [] = []
reverse' (x : xs) = reverse' xs ++ [x]


-- Okay so it's clear that we accept lists.
-- However it's a bit unclear which types we accept.
-- Fortunately it does not really matter as do not do anything with x itself.
-- I would therefore way that the type of reverse' :: [a] -> [a].

-- Running `:t` on reverse' reveals that we where correct.

-- Hmm i would say that a ispalindrome function would have type (Eq c) => [c] -> Bool

ispalindrome x = x == reverse' x


-- Okay assuming that a are all integers, i
-- would say that the fype of cfrac :: (Real a, Integral b) -> a -> b -> [b]

cfrac _ 0 = []
cfrac x n = let intPart = truncate x in
              intPart : cfrac (1 / (x - fromIntegral intPart)) (n-1)
-- REMEMBER fromInteger for ***'s sake.
-- Without it, x will be tagged with (RealFrac a, Integral a) => a,
-- which destroys everything.

-- Hmm it does not really work perfectly because of the rounding errors


-- Lets just create the last function instead. It must extract the last element of a list.
-- It's type is probably last :: [a] -> maybe a

last' [] = Nothing
last' (x:[]) = Just x
last' (_:xs) = last' xs

-- Flatten a two level deep list.
flatten' [] = []
flatten' (x:xs) = x ++ flatten' xs

-- Okay so we can with curtianty say that the function takes an array of something.
-- This is clear by the pattern matches.
-- However because we use ++ we also know that we return a list, as it's signature is [a] -> [a] -> [a].
-- From this we can also infer that x must be a list.
-- The function type is therefore flatten' :: [[a]] -> [a]

-- When running :t on flatten' we get the same.


valid :: (Integral a, Ord a) => [(a, b)] -> Bool
valid = recur empty
  where recur _ [] = True
        recur known (pair:rest) =
          if key `member` known
          then False
          else recur (insert key known) rest
          where key = fst pair


-- TODO, case where key is not in is unhandled
lookup' :: (Integral a, Ord a) => [(a, b)] -> a -> b
lookup' (pair:rest) key = if (fst pair) == key
                          then (snd pair)
                          else lookup' rest key

-- I dont see how findfun and lookup are not the same
findfun = lookup'
