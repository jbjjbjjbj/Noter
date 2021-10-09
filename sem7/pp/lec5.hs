
-- Opgaver før lecture
sum' 0 = 0
sum' x = x + sum' (x-1)

flip' = map (\(x, y) -> (y, x))
-- Here i would guess that the type is [(a, b)] -> [(b, a)]
-- When quering i get flip' :: [(b, a)] -> [(a, b)]
-- Yeah they are the same
