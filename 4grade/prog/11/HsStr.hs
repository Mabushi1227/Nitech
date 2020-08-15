-- 要素数を返す --
my_length [] = 0
my_length(x:xs) = 1 + my_length(xs)

-- 合計を返す --
my_sum [] = 0
my_sum (x:xs) = x + my_sum(xs)

-- 文字列を連結する --
str_chain [x] = x
str_chain (x:xs) = x ++ str_chain(xs)

main = do
    print $ (my_sum.map_length) a
    print $ (str_chain.str_filter) a
    where
        a = ["apple", "banana", "orange"]
        map_length a = (map (\x -> my_length x) a)
        str_filter a = (filter(\x -> my_length x >= 6) a)