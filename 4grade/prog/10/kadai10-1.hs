-- フィボナッチ数列 --
fibonacci n
  | n == 0 = 0
  | n == 1 = 1
  | otherwise = fibonacci(n-1) + fibonacci(n-2)

-- 要素数を返す --
my_length [] = 0
my_length (x:xs) = 1 + my_length(xs)

-- 合計を返す --
my_sum [] = 0
my_sum (x:xs) = x + my_sum(xs)

-- 逆順に返す --
my_reverse [] = []
my_reverse (x:xs) = my_reverse xs  ++ [x] 


main = do
    print $ fibonacci 8 --21
    print $ my_length [2,2,2,2] -- 4
    print $ my_sum [2,2,2,2] -- 8 
    print $ my_reverse [1,2,3,4] -- 4,3,2,1