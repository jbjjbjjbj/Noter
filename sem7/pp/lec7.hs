import Data.List
import Data.Maybe

data SimpleType = TInt | TPair SimpleType SimpleType | TAbst SimpleType SimpleType deriving (Show, Eq)
isTAbst (TAbst _ _) = True
isTAbst _ = False

int2int = TAbst TInt TInt

data Term = Num Int | Var String | Pair Term Term | App Term Term | Abst String SimpleType Term

intIdent = Abst "x" TInt (Var "x")

freevars :: Term -> [String]
freevars (Num _) = []
freevars (Var name) = [name]
freevars (Pair e1 e2) = freevars e1 `union` freevars e2
freevars (App e1 e2) = freevars e1 `union` freevars e2
freevars (Abst arg t e) = freevars e \\ [arg]

isclosed :: Term -> Bool
isclosed = null . freevars

envlook :: Eq a => [(a, b)] -> a -> Maybe b
envlook [] _ = Nothing
envlook ((name,value):rest) search | name == search = Just value
                                   | otherwise = envlook rest search

envupd :: Eq a => [(a, b)] -> (a, b) -> [(a, b)]
-- Wait why should i check that, seems stupid
envupd env (name,value) | isNothing (envlook env name) = (name,value) : env
                        | otherwise = map upd env
                                        where upd (cname, cvalue) | cname == name = (cname, value)
                                                                  | otherwise = (cname, cvalue)

selectMaybe :: (a -> Bool) -> Maybe a -> Maybe a
selectMaybe _ Nothing = Nothing
selectMaybe func (Just thing) | func thing = Just thing
                              | otherwise = Nothing

findtype :: [(String, SimpleType)] -> Term -> Maybe SimpleType
findtype _ (Num _) = Just TInt
findtype env (Var name) = envlook env name
findtype env (Pair a b) = do
  at <- findtype env a
  bt <- findtype env b
  return (TPair at bt)
findtype env (App a b) = case findtype env a of
  (Just (TAbst targ tbody)) -> selectMaybe (==targ) (findtype env b) *> Just tbody
  _ -> Nothing
findtype env (Abst arg t a) = findtype (envupd env (arg,t)) a
  >>= Just . TAbst t

someFunction = Abst "x" TInt (Var "x")
