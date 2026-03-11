-- Finding the first odd number in the Collatz sequence
nextCollatz :: Integer -> Integer
nextCollatz n = findNextOdd (3*n + 1)
  where
    findNextOdd x
      | odd x     = x
      | otherwise = findNextOdd (x `div` 2)

-- Generating the path from a given x to 1
edgesForNumber :: Integer -> [(Integer, Integer)]
edgesForNumber x
  | x == 1    = []
  | otherwise = (x, next) : edgesForNumber next
  where next = nextCollatz x

-- Generating the full edge list
allEdges :: [Integer] -> [(Integer, Integer)]
allEdges = foldr ((++) . edgesForNumber) []

-- Removing duplicates from the edge list
remove :: (Integer, Integer) -> [(Integer, Integer)] -> [(Integer, Integer)]
remove _ [] = []
remove x (y:ys)
  | x == y    = remove x ys
  | otherwise = y : remove x ys

removeDuplicates :: [(Integer, Integer)] -> [(Integer, Integer)]
removeDuplicates [] = []
removeDuplicates (x:xs) = x : removeDuplicates (remove x xs)

-- Building the graph
buildGraph :: Integer -> [(Integer, Integer)]
buildGraph n = removeDuplicates (allEdges [1,3..n])

-- Formatting the edge list as text
edgesToString :: [(Integer, Integer)] -> String
edgesToString [] = ""
edgesToString ((from, to):xs) = show from ++ " -> " ++ show to ++ "\n" ++ edgesToString xs

-- Generating the DOT representation of the graph (Graphviz: https://dreampuf.github.io/GraphvizOnline/)
toGraphviz :: String -> String
toGraphviz edges = "digraph G {\n" ++ edges ++ "}"

main :: IO ()
main = do
  putStrLn "Enter n:"
  n <- readLn
  putStrLn "Enter filename (leave empty to skip saving):"
  fileName <- getLine

  let edges = buildGraph n
  let result = edgesToString edges

  putStrLn "\n==== Edges ===="
  putStrLn result

  if fileName == "" 
    then return ()
    else writeFile fileName (toGraphviz result)