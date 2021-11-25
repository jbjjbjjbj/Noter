import Data.Maybe

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
