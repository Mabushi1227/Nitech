

main = do
    print $ (sum.m.f) d
    where
        d = [0..9]
        f a = (filter (\x -> x `mod` 2 == 0) a)
        m a = (map (\x -> x*2) a)