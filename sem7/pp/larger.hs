import Data.Maybe

-- Fra lec5
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


data LTree = LLeaf String | LNode LTree LTree
data LTreeRoot = LTreeRoot LTree Float

treemerge :: LTreeRoot -> LTreeRoot -> LTreeRoot
treemerge (LTreeRoot ta la) (LTreeRoot tb lb) = LTreeRoot (LNode ta tb) (la + lb)

data Bit = Zero | One

instance Show Bit where
  show Zero = "0"
  show One = "1"

createBitList :: String -> Maybe [Bit]
createBitList [] = Just []
createBitList (c:rest) | c == '0' = createBitList rest >>= Just . (:) Zero
                       | c == '1' = createBitList rest >>= Just . (:) One
                       | otherwise = Nothing

maketable :: LTree -> [([Bit], String)]
maketable = recur []
            where recur prefix (LLeaf val) = [(reverse prefix, val)]
                  recur prefix (LNode left right) =
                    recur (Zero : prefix) left ++
                    recur (One : prefix) right


testTree = LNode (LLeaf "Hej") (LNode (LLeaf "Med") (LLeaf "Dig"))
