fact 0 = 1
fact n = n * fact(n-1)

-- fact 4~8 で実行 --
main = do
    print $ fact 4
    print $ fact 5
    print $ fact 6
    print $ fact 7
    print $ fact 8