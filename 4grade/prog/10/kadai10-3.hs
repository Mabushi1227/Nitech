-- map関数 --
my_map f [] = []
my_map f (x:xs) = f x : my_map f (xs)

-- filter関数 s--
my_filter c [] = []
my_filter c (x:xs) = if c(x)  then (x : my_filter c (xs)) else my_filter c (xs) 

main = do
    print $ my_map(+1)[1..10]
    print $ my_map(\x -> x*x)[1..10]
    print $ my_filter(\x -> x `mod` 2 == 0)[1..10]